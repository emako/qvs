#include "preview_dialog.h"
#include "../mainwindow.h"
#include "ui_preview_dialog.h"
#include "ui_mainwindow.h"

PreviewDialog::PreviewDialog(QWidget *parent) :
    QMainWindow(parent),
    m_pPlayTimer(new QTimer(this)),
    m_frameShown(eINDEX_0),
    m_playing(false),
    m_bigFrameStep(eINDEX_24),
    m_reloadTitleShown(true),
    ui(new Ui::PreviewDialog),
    m_statusBarLabel(new QLabel)
{
    ui->setupUi(this);
    this->setup();
}

PreviewDialog::~PreviewDialog()
{
    delete m_statusBarLabel;
    delete m_pPlayTimer;
    delete ui;
}

void PreviewDialog::setup(void)
{
    setUpZoomPanel();
    setUpTimeLinePanel();

    this->installEventFilter(this);
    ui->previewArea->installEventFilter(this);

    this->setAttribute(Qt::WA_DeleteOnClose, true);
    this->setWindowIcon(QIcon(":/buttons/film.png"));
    this->setWindowTitle(tr("Preview"));

    ui->statusBar->addPermanentWidget(m_statusBarLabel, eINDEX_1);
    ui->previewArea->setAlignment(Qt::AlignTop | Qt::AlignLeft);

    ui->frameNumberSlider->setBigStep(m_bigFrameStep);
    ui->frameNumberSlider->setDisplayMode(TimeLineSlider::Frames);

    m_pPlayTimer->setSingleShot(true);
    m_pPlayTimer->setTimerType(Qt::PreciseTimer);
    connect(m_pPlayTimer, SIGNAL(timeout()), this, SLOT(slotPlayNext()));
    connect(ui->frameNumberSlider, SIGNAL(signalFrameChanged(int)), this, SLOT(slotShowFrame(int)));
    connect(ui->frameNumberSpinBox, SIGNAL(valueChanged(int)), this, SLOT(slotShowFrame(int)));
    connect(ui->playButton, SIGNAL(clicked(bool)), this, SLOT(slotPlay(bool)));
    connect(ui->frameToClipboardButton, SIGNAL(clicked()), this, SLOT(slotFrameToClipboard()));
    connect(ui->saveSnapshotButton, SIGNAL(clicked()), this, SLOT(slotSaveSnapshot()));
}

void PreviewDialog::setUpZoomPanel(void)
{
    ui->zoomRatioSpinBox->setLocale(QLocale("C"));

    ui->zoomModeComboBox->addItem(QIcon(":/buttons/zoom_actual.png"), tr("No zoom"), static_cast<int>(ZoomMode::NoZoom));
    ui->zoomModeComboBox->addItem(QIcon(":/buttons/zoom_in.png"), tr("Fixed ratio"), static_cast<int>(ZoomMode::FixedRatio));
    ui->zoomModeComboBox->addItem(QIcon(":/buttons/zoom_fit.png"), tr("Fit to frame"), static_cast<int>(ZoomMode::FitToFrame));

    ZoomMode zoomMode = static_cast<ZoomMode>(g_pConfig->getConfig(Config::eCONFIG_COMMON_PREVIEW_ZOOM_MODE).toInt());
    int comboIndex = ui->zoomModeComboBox->findData(static_cast<int>(zoomMode));
    if(comboIndex != eINDEX_NONE)
    {
        ui->zoomModeComboBox->setCurrentIndex(comboIndex);
    }
    bool fixedRatio(zoomMode == ZoomMode::FixedRatio);
    ui->zoomRatioSpinBox->setEnabled(fixedRatio);

    double zoomRatio = 2.0;
    ui->zoomRatioSpinBox->setValue(zoomRatio);

    ui->scaleModeComboBox->addItem(tr("Nearest"), static_cast<int>(Qt::FastTransformation));
    ui->scaleModeComboBox->addItem(tr("Bilinear"), static_cast<int>(Qt::SmoothTransformation));
    bool noZoom = (zoomMode == ZoomMode::NoZoom);
    ui->scaleModeComboBox->setEnabled(!noZoom);

    Qt::TransformationMode scaleMode = static_cast<Qt::TransformationMode>(g_pConfig->getConfig(Config::eCONFIG_COMMON_PREVIEW_SCALE_MODE).toInt());
    comboIndex = ui->scaleModeComboBox->findData(static_cast<int>(scaleMode));
    if(comboIndex != eINDEX_NONE)
    {
        ui->scaleModeComboBox->setCurrentIndex(comboIndex);
    }

    connect(ui->zoomCheckButton, SIGNAL(clicked(bool)), this, SLOT(slotShowZoomPanel(bool)));
    connect(ui->zoomModeComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(slotZoomModeChanged(int)));
    connect(ui->zoomRatioSpinBox, SIGNAL(valueChanged(double)), this, SLOT(slotZoomRatioChanged(double)));
    connect(ui->scaleModeComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(slotScaleModeChanged(int)));
}


void PreviewDialog::setUpTimeLinePanel(void)
{
    ui->playFpsLimitModeComboBox->addItem(tr("From video"), static_cast<int>(FromVideo));
    ui->playFpsLimitModeComboBox->addItem(tr("No limit"), static_cast<int>(NoLimit));
    ui->playFpsLimitModeComboBox->addItem(tr("Custom"), static_cast<int>(Custom));

    ui->playFpsLimitSpinBox->setLocale(QLocale("C"));
    double customFPS = g_pConfig->getConfig(Config::eCONFIG_COMMON_PREVIEW_FPS_LIMIT_CUSTOM).toDouble();
    ui->playFpsLimitSpinBox->setValue(customFPS);

    slotSetPlayFPSLimit();

    ui->timeLineModeComboBox->addItem(QIcon(":/buttons/timeline.png"), tr("Time"), static_cast<int>(TimeLineSlider::DisplayMode::Time));
    ui->timeLineModeComboBox->addItem(QIcon(":/buttons/timeline_frames.png"), tr("Frames"), static_cast<int>(TimeLineSlider::DisplayMode::Frames));

    TimeLineSlider::DisplayMode timeLineMode = static_cast<TimeLineSlider::DisplayMode>(g_pConfig->getConfig(Config::eCONFIG_COMMON_PREVIEW_TIMELINE_DISPLAY_MODE).toInt());
    int comboIndex = ui->timeLineModeComboBox->findData(static_cast<int>(timeLineMode));
    if(comboIndex != eINDEX_NONE)
    {
        ui->timeLineModeComboBox->setCurrentIndex(comboIndex);
    }

    connect(ui->timeLineModeComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(slotTimeLineModeChanged(int)));
    connect(ui->playFpsLimitModeComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(slotSetPlayFPSLimit()));
    connect(ui->playFpsLimitSpinBox, SIGNAL(valueChanged(double)), this, SLOT(slotSetPlayFPSLimit()));
}

bool PreviewDialog::reload(const std::string &a_filename)
{
    if(!QFileInfo(QString::fromStdString(a_filename)).isFile())
    {
        return false;
    }

    if(!m_videoCapture.open(a_filename))
    {
        return false;
    }

    if(m_mediainfoLoader.open(QString::fromStdString(a_filename)) <= eINDEX_0)
    {
        return false;
    }

    getVideoInfo();
    slotSetPlayFPSLimit();

    int lastFrameNumber = m_videoInfo.frameCount - eINDEX_1;
    ui->frameNumberSpinBox->setMaximum(lastFrameNumber);
    ui->frameNumberSlider->setFramesNumber(m_videoInfo.frameCount);
    ui->frameNumberSlider->setFPS(m_videoInfo.fps);


    m_videoCapture >> m_mat;
    if(!setMat(m_mat))
    {
        return false;
    }

    if(m_reloadTitleShown)
    {
        setWindowTitle(tr("Preview - ") + QString::fromStdString(a_filename));
    }

    m_filename = a_filename;
    return true;
}

void PreviewDialog::slotShowFrame(int a_frameNumber)
{
    if((m_frameShown == a_frameNumber) && (!m_framePixmap.isNull()))
    {
        return;
    }
    if(m_playing)
    {
        return;
    }

    ui->frameNumberSpinBox->setValue(a_frameNumber);
    ui->frameNumberSlider->setFrame(a_frameNumber);

    bool requested = requestShowFrame(a_frameNumber);
    if(requested)
    {
        m_frameShown = a_frameNumber;
        requestShowFrame(m_frameShown);
    }
}

void PreviewDialog::getVideoInfo(void)
{
    m_videoInfo.frameCount  = static_cast<int>(m_videoCapture.get(CV_CAP_PROP_FRAME_COUNT));
    m_videoInfo.frameWidth  = static_cast<int>(m_videoCapture.get(CV_CAP_PROP_FRAME_WIDTH));
    m_videoInfo.frameHeight = static_cast<int>(m_videoCapture.get(CV_CAP_PROP_FRAME_HEIGHT));
    m_videoInfo.fpsCV       = m_videoCapture.get(CV_CAP_PROP_FPS);
    m_videoInfo.fps         = m_mediainfoLoader.get(MediaInfoLoader::eMEDIA_PROP_FRAME_RATE).toDouble();
    m_videoInfo.AviRatio    = m_videoCapture.get(CV_CAP_PROP_POS_AVI_RATIO);
    m_videoInfo.time        = qvs::convertFramesToTimecode(m_videoInfo.frameCount, m_videoInfo.fps);
    m_videoInfo.format      = m_mediainfoLoader.get(MediaInfoLoader::eMEDIA_PROP_FORMAT);
    m_videoInfo.fpsNum      = m_mediainfoLoader.get(MediaInfoLoader::eMEDIA_PROP_FRAME_RATE_NUM).toInt();
    m_videoInfo.fpsDen      = m_mediainfoLoader.get(MediaInfoLoader::eMEDIA_PROP_FRAME_RATE_DEN).toInt();
    m_statusBarLabel->setText(m_videoInfo.getStatus());
}

inline void PreviewDialog::printVideoInfo(void)
{
    m_videoInfo.posMsec     =  m_videoCapture.get(CV_CAP_PROP_POS_MSEC);
    m_videoInfo.posFrames   =  static_cast<int>(m_videoCapture.get(CV_CAP_PROP_POS_FRAMES));
    m_videoInfo.AviRatio    =  m_videoCapture.get(CV_CAP_PROP_POS_AVI_RATIO);
    m_videoInfo.printStatus();
}

void PreviewDialog::slotPlayNext(void)
{
    m_videoCapture >> m_mat;
    if(!setMat(m_mat))
    {
        emit ui->playButton->clicked(false);
        return;
    }
    printVideoInfo();
    ui->frameNumberSpinBox->setValue(m_videoInfo.posFrames);
    ui->frameNumberSlider->setFrame(m_videoInfo.posFrames);
    m_pPlayTimer->start(static_cast<int>(std::ceil(m_secondsBetweenFrames * SECOND_TO_MILLISECOND_UNIT)));
}

inline QImage PreviewDialog::convertMatToImage(const Mat& a_mat)
{
    if(a_mat.type() == CV_8UC1)
    {
        QImage image(a_mat.cols, a_mat.rows, QImage::Format_Indexed8);
        uchar *pSrc = a_mat.data;

        image.setColorCount(256);
        for(int i = 0; i < 256; i++)
        {
            image.setColor(i, qRgb(i, i, i));
        }
        for(int row = 0; row < a_mat.rows; row ++)
        {
            uchar *pDest = image.scanLine(row);
            memcpy(pDest, pSrc, static_cast<size_t>(a_mat.cols));
            pSrc += static_cast<int>(a_mat.step);
        }
        return image;
    }
    else if(a_mat.type() == CV_8UC3)
    {
        const uchar *pSrc = const_cast<uchar*>(a_mat.data);
        QImage image(pSrc, a_mat.cols, a_mat.rows, static_cast<int>(a_mat.step), QImage::Format_RGB888);

        return image.rgbSwapped();
    }
    else if(a_mat.type() == CV_8UC4)
    {
        const uchar *pSrc = const_cast<uchar*>(a_mat.data);
        QImage image(pSrc, a_mat.cols, a_mat.rows, static_cast<int>(a_mat.step), QImage::Format_ARGB32);

        return image.copy();
    }
    else
    {
        return QImage();
    }
}

inline QPixmap PreviewDialog::convertMatToPixmap(const Mat& a_mat)
{
    return QPixmap::fromImage(convertMatToImage(a_mat), Qt::NoAlpha);
}

inline bool PreviewDialog::setMat(const Mat& a_mat)
{
    QPixmap pixmap = convertMatToPixmap(a_mat);

    if(pixmap.isNull())
    {
        return false;
    }
    m_framePixmap = pixmap;
    setPreviewPixmap();
    return true;
}

void PreviewDialog::slotPlay(bool a_checked)
{
    if(a_checked)
    {
        if(!m_videoCapture.isOpened())
        {
            return;
        }
        m_pPlayTimer->start();
        m_playing = true;
    }
    else
    {
        m_pPlayTimer->stop();
        m_playing = false;
    }
    ui->playButton->setChecked(a_checked);
}

void PreviewDialog::slotShowZoomPanel(bool a_checked)
{
    ui->zoomModeComboBox->setVisible(a_checked);
    ui->zoomRatioSpinBox->setVisible(a_checked);
    ui->scaleModeComboBox->setVisible(a_checked);
}

void PreviewDialog::slotZoomModeChanged(int a_index)
{
    switch(static_cast<ZoomMode>(a_index))
    {
    case NoZoom:
        ui->zoomRatioSpinBox->setEnabled(false);
        ui->scaleModeComboBox->setEnabled(false);
        break;
    case FixedRatio:
        ui->zoomRatioSpinBox->setEnabled(true);
        ui->scaleModeComboBox->setEnabled(true);
        break;
    case FitToFrame:
        ui->zoomRatioSpinBox->setEnabled(false);
        ui->scaleModeComboBox->setEnabled(true);
        break;
    }
    if(!m_framePixmap.isNull())
    {
        setPreviewPixmap();
    }
    g_pConfig->setConfig(Config::eCONFIG_COMMON_PREVIEW_ZOOM_MODE, a_index);
}

void PreviewDialog::slotScaleModeChanged(int)
{
    if(!m_framePixmap.isNull())
    {
        setPreviewPixmap();
    }
    g_pConfig->setConfig(Config::eCONFIG_COMMON_PREVIEW_SCALE_MODE, ui->scaleModeComboBox->currentIndex());
}

inline void PreviewDialog::setPreviewPixmap(void)
{
    ZoomMode zoomMode = static_cast<ZoomMode>(ui->zoomModeComboBox->currentData().toInt());
    if(zoomMode == ZoomMode::NoZoom)
    {
        ui->previewArea->setPixmap(m_framePixmap);
        return;
    }

    QPixmap previewPixmap;
    int frameWidth = 0;
    int frameHeight = 0;
    Qt::TransformationMode scaleMode = static_cast<Qt::TransformationMode>(ui->scaleModeComboBox->currentData().toInt());

    if(zoomMode == ZoomMode::FixedRatio)
    {
        double ratio = ui->zoomRatioSpinBox->value();

        frameWidth = static_cast<int>(m_framePixmap.width() * ratio);
        frameHeight = static_cast<int>(m_framePixmap.height() * ratio);
    }
    else
    {
        QRect previewRect = ui->scrollArea->geometry();
        int cropSize = ui->previewArea->lineWidth() * 2;

        frameWidth = previewRect.width() - cropSize;
        frameHeight = previewRect.height() - cropSize;
    }
    previewPixmap = m_framePixmap.scaled(frameWidth, frameHeight, Qt::KeepAspectRatio, scaleMode);
    ui->previewArea->setPixmap(previewPixmap);
}

void PreviewDialog::slotZoomRatioChanged(double)
{
    setPreviewPixmap();
}

void PreviewDialog::resizeEvent(QResizeEvent *a_pEvent)
{
    a_pEvent->accept();
    if(m_videoCapture.isOpened())
    {
        setPreviewPixmap();
    }
}

bool PreviewDialog::eventFilter(QObject *o, QEvent *e)
{
    if(o == this)
    {
        if(e->type() == QEvent::KeyPress)
        {
            QT_PASS;
        }
    }
    else if(o == ui->previewArea)
    {
        if(e->type() == QEvent::KeyPress)
        {
            QT_PASS;
        }
    }
    return false;
}

void PreviewDialog::keyPressEvent(QKeyEvent * a_pEvent)
{
    if(a_pEvent->modifiers() != Qt::NoModifier)
    {
        QWidget::keyPressEvent(a_pEvent);
        return;
    }

    int key = a_pEvent->key();
    if(key == Qt::Key_Left)
    {
        slotShowFrame(m_frameShown - eINDEX_1);
        a_pEvent->accept();
        return;
    }
    else if(key == Qt::Key_Right)
    {
        slotShowFrame(m_frameShown + eINDEX_1);
        a_pEvent->accept();
        return;
    }
    else if(key == Qt::Key_PageUp || (key == Qt::Key_Down))
    {
        slotShowFrame(m_frameShown + m_bigFrameStep);
        a_pEvent->accept();
        return;
    }
    else if(key == Qt::Key_PageDown || (key == Qt::Key_Up))
    {
        slotShowFrame(m_frameShown - m_bigFrameStep);
        a_pEvent->accept();
        return;
    }
    else if(key == Qt::Key_Home)
    {
        ui->frameNumberSlider->setFrame(eINDEX_0);
        a_pEvent->accept();
        return;
    }
    else if(key == Qt::Key_End)
    {
        ui->frameNumberSlider->setFrame(m_videoInfo.frameCount);
        a_pEvent->accept();
        return;
    }
    else if(key == Qt::Key_F5)
    {
        slotPlay(!ui->playButton->isChecked());
        a_pEvent->accept();
        return;
    }

    QWidget::keyPressEvent(a_pEvent);
}

void PreviewDialog::slotTimeLineModeChanged(int a_index)
{
    ui->frameNumberSlider->setDisplayMode(static_cast<TimeLineSlider::DisplayMode>(a_index));
    g_pConfig->setConfig(Config::eCONFIG_COMMON_PREVIEW_TIMELINE_DISPLAY_MODE, a_index);
}

void PreviewDialog::dragEnterEvent(QDragEnterEvent* e)
{
    if(e->mimeData()->hasText())
    {
        e->acceptProposedAction();
    }
}

void PreviewDialog::dropEvent(QDropEvent* e)
{
    const QMimeData* mime = e->mimeData();

    if(mime->hasUrls())
    {
        foreach(QUrl url, e->mimeData()->urls())
        {
            QFileInfo file(url.toLocalFile());
            QString filename = file.canonicalFilePath();
            filename = QDir::toNativeSeparators(filename);
            if(!QFileInfo(filename).isFile())
            {
                continue;
            }
            if(!reload(filename.toStdString()))
            {
                qDebug() << "Reload file failed.";
            }
            break;
        }
    }
    e->acceptProposedAction();
}

void PreviewDialog::slotFrameToClipboard(void)
{
    if(m_framePixmap.isNull())
    {
        return;
    }

    QClipboard * pClipboard = QApplication::clipboard();
    pClipboard->setPixmap(m_framePixmap);
}

void PreviewDialog::slotSaveSnapshot(void)
{
    if((m_frameShown < 0) || m_framePixmap.isNull())
    {
        return;
    }

    std::map<QString, QString> extensionToFilterMap =
    {
        {"png", tr("PNG image (*.png)")},
    };

    QString fileExtension = g_pConfig->getConfig(Config::eCONFIG_COMMON_PREVIEW_LAST_SNAPSHOT_EXT).toString();

    QList<QByteArray> supportedFormats = QImageWriter::supportedImageFormats();
    bool webpSupported = (supportedFormats.indexOf("webp") > eINDEX_NONE);

    if(webpSupported)
        extensionToFilterMap["webp"] = tr("WebP image (*.webp)");

    QString snapshotFilePath = QString::fromStdString(m_filename);
    if(snapshotFilePath.isEmpty())
    {
        snapshotFilePath = QStandardPaths::writableLocation(QStandardPaths::PicturesLocation);
        snapshotFilePath += QString("/%1.").arg(m_frameShown);
    }
    else
    {
        snapshotFilePath += QString(" - %1.").arg(m_frameShown);
    }
    snapshotFilePath += fileExtension;

    QStringList saveFormatsList;
    for(const std::pair<QString, QString> & pair : extensionToFilterMap)
    {
        saveFormatsList << pair.second;
    }

    QString selectedFilter = extensionToFilterMap[fileExtension];

    snapshotFilePath = QFileDialog::getSaveFileName(this, tr("Save frame as image"), snapshotFilePath, saveFormatsList.join(";;"), &selectedFilter);

    QFileInfo fileInfo(snapshotFilePath);
    QString suffix = fileInfo.suffix().toLower();

    QByteArray format("png");
    if((suffix == "webp") && webpSupported)
    {
        format = "webp";
    }

    if(!snapshotFilePath.isEmpty())
    {
        bool success = m_framePixmap.save(snapshotFilePath, format, 100);
        if(success)
        {
            g_pConfig->setConfig(Config::eCONFIG_COMMON_PREVIEW_LAST_SNAPSHOT_EXT, suffix);
        }
        else
        {
            QMessageBox::critical(this, tr("Image save error"), tr("Error while saving image ") + snapshotFilePath);
        }
    }
}


void PreviewDialog::slotSetPlayFPSLimit(void)
{
    double limit = ui->playFpsLimitSpinBox->value();

    PlayFPSLimitMode mode = static_cast<PlayFPSLimitMode>(ui->playFpsLimitModeComboBox->currentIndex());
    if(mode == PlayFPSLimitMode::NoLimit)
    {
        m_secondsBetweenFrames = 0.0;
        ui->playFpsLimitSpinBox->setEnabled(false);
    }
    else if(mode == PlayFPSLimitMode::Custom)
    {
        m_secondsBetweenFrames = 1.0 / limit;
        ui->playFpsLimitSpinBox->setEnabled(true);
        g_pConfig->setConfig(Config::eCONFIG_COMMON_PREVIEW_FPS_LIMIT_CUSTOM, limit);
    }
    else if(mode == PlayFPSLimitMode::FromVideo)
    {
        m_secondsBetweenFrames = 1.0 / m_videoInfo.fps;
        ui->playFpsLimitSpinBox->setValue(m_videoInfo.fps);
        ui->playFpsLimitSpinBox->setEnabled(true);
    }
    else
    {
        assert(false);
    }
}

bool PreviewDialog::requestShowFrame(int a_frameNumber)
{
    if(!m_videoCapture.isOpened())
    {
        return false;
    }

    m_videoCapture.set(CV_CAP_PROP_POS_FRAMES, a_frameNumber);

    m_videoCapture >> m_mat;
    if(!setMat(m_mat))
    {
        return false;
    }
    return true;
}

void PreviewDialog::closeEvent(QCloseEvent *e)
{
    m_mediainfoLoader.close();
    m_videoCapture.release();
    m_mat.release();
    if(m_pPlayTimer->isActive())
    {
        m_pPlayTimer->stop();
    }
    mainUi->slotChildWindowClosed(m_uid);
    e->accept();
}

void PreviewDialog::wheelEvent(QWheelEvent *e)
{
    e->accept();
}
