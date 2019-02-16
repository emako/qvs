#include "preview_dialog.h"
#include "../mainwindow.h"
#include "ui_preview_dialog.h"
#include "ui_mainwindow.h"

PreviewDialog::PreviewDialog(QWidget *parent) :
    QMainWindow(parent),
    m_mediainfoProber(new MediaInfoProber),
	m_pStatisticsView(nullptr),
    m_isLocked(false),
    m_frameShown(eINDEX_0),
    m_playing(false),
    m_bigFrameStep(eINDEX_24),
    m_reloadTitleShown(true),
    ui(new Ui::PreviewDialog),
    m_pContextMenu(nullptr),
    m_statusBarLabel(new QLabel)
{
    ui->setupUi(this);
    this->setup();
}

PreviewDialog::~PreviewDialog()
{
	if (m_pStatisticsView)
	{
		m_pStatisticsView->close();
		delete m_pStatisticsView;
	}

#if !USING_OPENCV
	delete m_pPlayer;
	delete m_pVideoOutput;
#endif

    delete m_statusBarLabel;
    delete m_pPlayTimer;
    delete m_pContextMenu;
    delete ui;
}

void PreviewDialog::setup(void)
{
    m_pPlayTimer = new QTimer(this);

	//--
	m_pPlayer = new AVPlayer(this);
    m_pVideoOutput = new PreviewRenderer(this);

#if USING_PAINTER
    m_pPreviewPainter = new QPainter(ui->previewArea->previewArea());
    m_pPreviewPainter->setRenderHint(QPainter::HighQualityAntialiasing);
#endif

    m_pVideoOutput->setQuality(VideoRenderer::QualityFastest);
	m_pPlayer->setRenderer(m_pVideoOutput);
    m_pPlayer->setMediaEndAction(MediaEndAction_Default);
    qRegisterMetaType<AVPlayer::State>("AVPlayer::State");

    connect(m_pPlayer, SIGNAL(positionChanged(qint64)), this, SLOT(slotPositionChanged(qint64)));
    connect(m_pPlayer, SIGNAL(stateChanged(AVPlayer::State)), this, SLOT(stateChanged(AVPlayer::State)));

    isInitialing = false;

    setUpZoomPanel();
    setUpTimeLinePanel();

    this->installEventFilter(this);
    this->setAttribute(Qt::WA_DeleteOnClose, true);

    ui->statusBar->addPermanentWidget(m_statusBarLabel, eINDEX_1);
    ui->previewArea->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    ui->previewArea->installEventFilter(this);
    ui->previewArea->previewArea()->installEventFilter(this);

    ui->frameNumberSlider->setBigStep(m_bigFrameStep);
    ui->frameNumberSlider->setDisplayMode(TimeLineSlider::Time);

    m_pPlayTimer->setSingleShot(true);
    m_pPlayTimer->setTimerType(Qt::PreciseTimer);
	connect(ui->previewArea, SIGNAL(customContextMenuRequested(const QPoint &)), this, SLOT(previewContextMenuRequested(const QPoint &)));
    connect(m_pPlayTimer, SIGNAL(timeout()), this, SLOT(slotPlayNext()));
    connect(ui->frameNumberSlider, SIGNAL(signalFrameChanged(int)), this, SLOT(slotShowFrame(int)));
    connect(ui->frameNumberSpinBox, SIGNAL(valueChanged(int)), this, SLOT(slotShowFrame(int)));
    connect(ui->playButton, SIGNAL(clicked(bool)), this, SLOT(slotPlay(bool)));
    connect(ui->frameToClipboardButton, SIGNAL(clicked()), this, SLOT(slotFrameToClipboard()));
    connect(ui->saveSnapshotButton, SIGNAL(clicked()), this, SLOT(slotSaveSnapshot()));
    connect(ui->soundButton, SIGNAL(clicked(bool)), this, SLOT(slotSoundMuted(bool)));

    /* ContextMenu */
    m_pContextMenu = new QMenu(ui->previewArea);
    QAction *at_action_load = new QAction(QIcon(":/buttons/folder_add.png"), tr("Open media..."), ui->previewArea);
    QAction *at_action_external_audio_track = new QAction(QIcon(":/buttons/inbox_document_music.png"), tr("External audio..."), ui->previewArea);
    QAction *at_action_media_info = new QAction(QIcon(":/buttons/error_log.png"), tr("MediaInfo"), ui->previewArea);
    m_pContextMenu->addActions(QList<QAction*>() << at_action_load << at_action_external_audio_track);
    m_pContextMenu->addSeparator();
    m_pContextMenu->addActions(QList<QAction*>() << at_action_media_info);
    connect(at_action_load, SIGNAL(triggered()), this, SLOT(slotOpenMediaFile()));
    connect(at_action_external_audio_track, SIGNAL(triggered()), this, SLOT(slotSetExternalAudio()));
    connect(at_action_media_info, SIGNAL(triggered()), this, SLOT(slotShowVideoInfo()));

    ui->sliderSound->setValue(g_pConfig->getConfig(Config::eCONFIG_COMMON_PREVIEW_SOUND_VALUME).toInt());
    emit ui->sliderSound->valueChanged(ui->sliderSound->value());
    ui->soundButton->setChecked(g_pConfig->getConfig(Config::eCONFIG_COMMON_PREVIEW_SOUND_IS_MUTE).toBool());
    emit ui->soundButton->clicked(ui->soundButton->isChecked());
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
#if false
    ui->playFpsLimitModeComboBox->addItem(tr("No limit"), static_cast<int>(NoLimit));
    ui->playFpsLimitModeComboBox->addItem(tr("Custom"), static_cast<int>(Custom));
#endif

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

#if USING_OPENCV
    if(!m_videoCapture.open(a_filename))
    {
        return false;
    }
#endif

    if(m_mediainfoLoader.open(QString::fromStdString(a_filename)) <= eINDEX_0)
    {
        return false;
    }
    if(!m_mediainfoProber->open(QString::fromStdString(a_filename)))
    {
        return false;
    }

    m_pPlayer->audio()->setVolume(qreal(eINDEX_0));
    disconnect(m_pVideoOutput, SIGNAL(updatePreview(const QImage &)), this, SLOT(updatePreview(const QImage &)));

    m_pPlayer->setFile(QString::fromStdString(a_filename));

    if(!m_pPlayer->load())
    {
        QMessageBox::critical(this, MESSAGE_ERROR, tr("Load the media file failed!"));
        return false;
    }
    isInitialing = true;
    m_pPlayer->play(); // cause only played state is seekable.
    m_pPlayer->audio()->setVolume(qreal(ui->sliderSound->value()) / eINDEX_100);
    m_pPlayer->setPosition(m_pPlayer->startPosition()); // seek to start frame.

    getVideoInfo();
    slotSetPlayFPSLimit();

    int lastFrameNumber = m_videoInfo.frameCount - eINDEX_1;
    ui->frameNumberSpinBox->setMaximum(lastFrameNumber);
    ui->frameNumberSlider->setFramesNumber(m_videoInfo.frameCount);
    ui->frameNumberSlider->setFPS(m_videoInfo.fps);

#if USING_OPENCV
    m_videoCapture >> m_mat;
    if(!setMat(m_mat))
    {
        return false;
    }
#endif

    if(m_reloadTitleShown)
    {
        setWindowTitle(tr("Preview - ") + QString::fromStdString(a_filename));
    }

    m_filename = a_filename;
    return true;
}

void PreviewDialog::slotSeek(double a_secs)
{
	if (!m_pPlayer->isPlaying())
	{
		return;
	}
	m_pPlayer->seek(a_secs * 1000LL); // to msecs
}

void PreviewDialog::slotPositionChanged(qint64 a_pos)
{
    int frameNumber = static_cast<int>(a_pos / m_videoInfo.fps);

    ui->frameNumberSpinBox->setValue(frameNumber);
    ui->frameNumberSlider->setFrame(frameNumber);
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
    if(!m_pPlayer->isPaused() && m_pPlayer->isPlaying())
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
#if USING_OPENCV
    m_videoInfo.frameCount  = static_cast<int>(m_videoCapture.get(CV_CAP_PROP_FRAME_COUNT));
    m_videoInfo.frameWidth  = static_cast<int>(m_videoCapture.get(CV_CAP_PROP_FRAME_WIDTH));
    m_videoInfo.frameHeight = static_cast<int>(m_videoCapture.get(CV_CAP_PROP_FRAME_HEIGHT));
    m_videoInfo.fpsCV       = m_videoCapture.get(CV_CAP_PROP_FPS);
	m_videoInfo.AviRatio = m_videoCapture.get(CV_CAP_PROP_POS_AVI_RATIO);
	m_videoInfo.fps = m_mediainfoLoader.get(MediaInfoLoader::eMEDIA_PROP_FRAME_RATE).toDouble();
	m_videoInfo.time = qvs::convertFramesToTimecode(m_videoInfo.frameCount, m_videoInfo.fps);
	m_videoInfo.format = m_mediainfoLoader.get(MediaInfoLoader::eMEDIA_PROP_FORMAT);
	m_videoInfo.fpsNum = m_mediainfoLoader.get(MediaInfoLoader::eMEDIA_PROP_FRAME_RATE_NUM).toInt();
	m_videoInfo.fpsDen = m_mediainfoLoader.get(MediaInfoLoader::eMEDIA_PROP_FRAME_RATE_DEN).toInt();
#else
#if true
    const AVFormatContext *pFormatCtx = m_mediainfoProber->get();

    if (pFormatCtx && (pFormatCtx->nb_streams > eINDEX_0))
    {
        const AVStream *pStreamFirst = pFormatCtx->streams[eINDEX_0];
        const AVCodecParameters *pAVCodecParameters = nullptr;

        if (pStreamFirst)
        {
            pAVCodecParameters = pStreamFirst->codecpar;

            m_videoInfo.frameCount = static_cast<int>(pStreamFirst->nb_frames);
            if(m_videoInfo.frameCount == eINDEX_0)
            {
                /* Retry get frame count. */
                m_videoInfo.frameCount = m_mediainfoLoader.get(MediaInfoLoader::eMEDIA_PROP_FRAME_COUNT).toInt();
            }
            m_videoInfo.frameWidth = pAVCodecParameters->width;
            m_videoInfo.frameHeight = pAVCodecParameters->height;
            m_videoInfo.fpsNum = m_mediainfoLoader.get(MediaInfoLoader::eMEDIA_PROP_FRAME_RATE_NUM).toInt();
            m_videoInfo.fpsDen = m_mediainfoLoader.get(MediaInfoLoader::eMEDIA_PROP_FRAME_RATE_DEN).toInt();
            m_videoInfo.fps = m_mediainfoLoader.get(MediaInfoLoader::eMEDIA_PROP_FRAME_RATE).toDouble();
            m_videoInfo.fpsFF = av_q2d(pStreamFirst->avg_frame_rate);
            m_videoInfo.format = m_mediainfoProber->getPixfmt(static_cast<AVPixelFormat>(pAVCodecParameters->format));
            m_videoInfo.time = qvs::convertFramesToTimecode(m_videoInfo.frameCount, m_videoInfo.fps);
            m_statusBarLabel->setText(m_videoInfo.getStatus());
        }
    }
#else
    const Statistics statistics = m_pPlayer->statistics();
    m_videoInfo.frameCount = static_cast<int>(statistics.video.frames);
    m_videoInfo.frameWidth = statistics.video_only.width;
    m_videoInfo.frameHeight = statistics.video_only.height;
    m_videoInfo.fpsFF = statistics.video.frame_rate;
    m_videoInfo.fps = m_mediainfoLoader.get(MediaInfoLoader::eMEDIA_PROP_FRAME_RATE).toDouble();
    m_videoInfo.time = qvs::convertFramesToTimecode(m_videoInfo.frameCount, m_videoInfo.fps);
    m_videoInfo.format = statistics.video_only.pix_fmt.toUpper();
    m_videoInfo.fpsNum = m_mediainfoLoader.get(MediaInfoLoader::eMEDIA_PROP_FRAME_RATE_NUM).toInt();
    m_videoInfo.fpsDen = m_mediainfoLoader.get(MediaInfoLoader::eMEDIA_PROP_FRAME_RATE_DEN).toInt();
#endif
#endif
    m_statusBarLabel->setText(m_videoInfo.getStatus());
}

inline void PreviewDialog::printVideoInfo(void)
{
#if USING_OPENCV
    m_videoInfo.posMsec     =  m_videoCapture.get(CV_CAP_PROP_POS_MSEC);
    m_videoInfo.posFrames   =  static_cast<int>(m_videoCapture.get(CV_CAP_PROP_POS_FRAMES));
    m_videoInfo.AviRatio    =  m_videoCapture.get(CV_CAP_PROP_POS_AVI_RATIO);
#else
#endif
    m_videoInfo.printStatus();
}

void PreviewDialog::slotShowVideoInfo(void)
{
	if (!m_pStatisticsView)
	{
		m_pStatisticsView = new StatisticsView();
	}
	if (m_pPlayer)
	{
		m_pStatisticsView->setStatistics(m_pPlayer->statistics());
	}
	m_pStatisticsView->show();
}

void PreviewDialog::slotPlayNext(void)
{
#if USING_OPENCV
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
#else
#endif
}

#if USING_OPENCV
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
#endif

#if USING_OPENCV
inline QPixmap PreviewDialog::convertMatToPixmap(const Mat& a_mat)
{
    return QPixmap::fromImage(convertMatToImage(a_mat), Qt::NoAlpha);
}
#endif

#if USING_OPENCV
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
#endif

void PreviewDialog::updatePreview(const QImage &a_image)
{
#if USING_PAINTER
    drawPreviewImage(a_image);
#else
    setPreviewPixmap(a_image);
#endif
}

void PreviewDialog::slotPlay(bool a_checked)
{
#if USING_OPENCV
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
#else

    if(a_checked)
    {
        m_pPlayer->setState(AVPlayer::PlayingState);
        m_playing = true;
    }
    else
    {
        m_pPlayer->setState(AVPlayer::PausedState);
        m_playing = false;
    }
#endif

	if (m_pStatisticsView && m_pStatisticsView->isVisible())
	{
		m_pStatisticsView->setStatistics(m_pPlayer->statistics());
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
    #if USING_OPENCV || !USING_PAINTER
        setPreviewPixmap();
    #else
        drawPreviewImage();
    #endif
    }
    g_pConfig->setConfig(Config::eCONFIG_COMMON_PREVIEW_ZOOM_MODE, a_index);
}

void PreviewDialog::slotScaleModeChanged(int)
{
    if(!m_framePixmap.isNull())
    {
#if USING_OPENCV || !USING_PAINTER
        setPreviewPixmap();
#else
        drawPreviewImage();
#endif
    }

    if(static_cast<Qt::TransformationMode>(ui->scaleModeComboBox->currentIndex()) == Qt::FastTransformation)
    {
        m_pVideoOutput->setQuality(VideoRenderer::QualityFastest);
    }
    else
    {
        m_pVideoOutput->setQuality(VideoRenderer::QualityDefault);
    }

    g_pConfig->setConfig(Config::eCONFIG_COMMON_PREVIEW_SCALE_MODE, ui->scaleModeComboBox->currentIndex());
}

void PreviewDialog::drawPreviewImage()
{
    if(m_frameImage.isNull())
    {
        qDebug() << "drawPreviewImage: image is null.";
        return;
    }
    ui->previewArea->previewArea()->update();
}

void PreviewDialog::drawPreviewImage(const QImage &a_image)
{
    if(a_image.isNull())
    {
        qDebug() << "drawPreviewImage: image is null.";
        return;
    }
    m_frameImage = a_image;
    ui->previewArea->previewArea()->update();
}

void PreviewDialog::setPreviewPixmap(const QImage &a_image)
{
#if USING_OPENCV
    m_framePixmap = QPixmap::fromImage(a_image, Qt::NoAlpha);
#else
    m_framePixmap = QPixmap::fromImage(a_image);
#endif
    setPreviewPixmap();
}

void PreviewDialog::setPreviewPixmap(void)
{
    if(m_framePixmap.isNull())
    {
        return;
    }

    if(m_isLocked == true)
    {
        return;
    }
    m_isLocked = true;

    ZoomMode zoomMode = static_cast<ZoomMode>(ui->zoomModeComboBox->currentData().toInt());
    if(zoomMode == ZoomMode::NoZoom)
    {
        ui->previewArea->setPixmap(m_framePixmap);
        m_isLocked = false;
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
        QRect previewRect = ui->previewArea->geometry();
        int cropSize = ui->previewArea->frameWidth() * 2;

        frameWidth = previewRect.width() - cropSize;
        frameHeight = previewRect.height() - cropSize;
    }

    previewPixmap = m_framePixmap.scaled(frameWidth, frameHeight, Qt::KeepAspectRatio, scaleMode);

    ui->previewArea->setPixmap(previewPixmap);

    m_isLocked = false;
}

void PreviewDialog::slotZoomRatioChanged(double)
{
#if USING_OPENCV || !USING_PAINTER
    setPreviewPixmap();
#else
    drawPreviewImage();
#endif
}

QRect PreviewDialog::getVideoOutputRect(void)
{
    /* Called by preview painter's paint event. */
    int frameWidth = 0;
    int frameHeight = 0;
    ZoomMode zoomMode = static_cast<ZoomMode>(ui->zoomModeComboBox->currentData().toInt());

    if(zoomMode == FixedRatio)
    {
        double ratio = ui->zoomRatioSpinBox->value();

        frameWidth = static_cast<int>(m_framePixmap.width() * ratio);
        frameHeight = static_cast<int>(m_framePixmap.height() * ratio);
    }
    else if(zoomMode == FitToFrame)
    {
        QRect previewRect = ui->previewArea->geometry();
        int cropSize = ui->previewArea->lineWidth() * 2;
        int maxWidth = previewRect.width() - cropSize;
        int maxHeight = previewRect.height() - cropSize;

        if(maxWidth < maxHeight)
        {
            /* Resing base on preview-ui-width. */
            frameWidth = maxWidth;
            frameHeight = static_cast<int>(frameWidth * m_framePixmap.height() / m_framePixmap.width());
        }
        else
        {
            /* Resing base on preview-ui-height. */
            frameHeight = maxHeight;
            frameWidth = static_cast<int>(frameHeight * (static_cast<double>(m_framePixmap.width()) / m_framePixmap.height()));
        }
    }
    else
    {
        frameWidth = m_framePixmap.width();
        frameHeight = m_framePixmap.height();
    }
    return QRect(0, 0, frameWidth, frameHeight);
}

void PreviewDialog::resizeEvent(QResizeEvent *a_pEvent)
{
    a_pEvent->accept();
#if USING_OPENCV
    if(m_videoCapture.isOpened())
    {
        setPreviewPixmap();
    }
#else
    if(!m_pPlayer->isPlaying())
    {
        setPreviewPixmap();
    }
#endif
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
    else if(o == ui->previewArea->previewArea())
    {
        if(e->type() == QEvent::KeyPress)
        {
            QT_PASS;
        }
#if USING_PAINTER
        else if(e->type() == QEvent::Paint)
        {
            if(!m_frameImage.isNull())
            {
                m_pPreviewPainter->begin(ui->previewArea->previewArea());
                m_pPreviewPainter->drawImage(getVideoOutputRect(), m_frameImage, m_frameImage.rect(), Qt::NoAlpha);
                m_pPreviewPainter->end();
                //qDebug() << getVideoOutputRect() << m_frameImage.rect();
            }
        }
#endif
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
        snapshotFilePath += QString("/%1").arg(m_frameShown);
    }
    else
    {
        snapshotFilePath += QString(" - %1").arg(m_frameShown);
    }
    snapshotFilePath += fileExtension;

    QStringList saveFormatsList;
    for(const std::pair<QString, QString> pair : extensionToFilterMap)
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
            QMessageBox::critical(this, MESSAGE_ERROR, tr("Error on saving image ") + snapshotFilePath);
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
        Q_ASSERT(false);
    }
}

bool PreviewDialog::requestShowFrame(int a_frameNumber)
{
#if USING_OPENCV
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
#else
    m_pPlayer->setSeekType(AccurateSeek);
    m_pPlayer->seek(qint64(a_frameNumber * m_videoInfo.fps));
    m_pPlayer->setState(AVPlayer::PausedState);

#endif
    return true;
}

void PreviewDialog::closeEvent(QCloseEvent *e)
{
    m_mediainfoLoader.close();
#if USING_OPENCV
    m_videoCapture.release();
    m_mat.release();
#else
#endif
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

void PreviewDialog::previewContextMenuRequested(const QPoint &)
{
    m_pContextMenu->exec(QCursor::pos());
}

void PreviewDialog::stateChanged(AVPlayer::State a_state)
{
    switch(a_state)
    {
    case AVPlayer::StoppedState:
        ui->playButton->setChecked(false);
        break;
    case AVPlayer::PlayingState:
        ui->playButton->setChecked(true);
        if(isInitialing)
        {
            m_pPlayer->setState(AVPlayer::PausedState);
            m_pPlayer->setPosition(m_pPlayer->startPosition());
            isInitialing = false;
        }
        connect(m_pVideoOutput, SIGNAL(updatePreview(const QImage &)), this, SLOT(updatePreview(const QImage &)));
        break;
    case AVPlayer::PausedState:
        ui->playButton->setChecked(false);
        break;
    }
}

void PreviewDialog::slotSoundMuted(bool a_checked)
{
    if(a_checked)
    {
        /* To be muxted */
        ui->sliderSound->hide();
        m_pPlayer->audio()->setMute(true);
    }
    else
    {
        ui->soundButton->setIcon(QIcon(":/buttons/sound.png"));
        ui->sliderSound->show();
        m_pPlayer->audio()->setMute(false);
    }

    g_pConfig->setConfig(Config::eCONFIG_COMMON_PREVIEW_SOUND_IS_MUTE, a_checked);
    updateSoundButtonIcon();
}

void PreviewDialog::updateSoundButtonIcon(void)
{
    if(ui->soundButton->isChecked())
    {
        ui->soundButton->setIcon(QIcon(":/buttons/sound_mute.png"));
    }
    else
    {
        if( ( ui->sliderSound->value() >    ui->sliderSound->minimum() )
         && ( ui->sliderSound->value() <= ( ui->sliderSound->maximum() / 3 ) ) )
        {
            ui->soundButton->setIcon(QIcon(":/buttons/sound_low.png"));
        }
        else if(ui->sliderSound->value() == ui->sliderSound->minimum())
        {
            ui->soundButton->setIcon(QIcon(":/buttons/sound_none.png"));
        }
        else
        {
            ui->soundButton->setIcon(QIcon(":/buttons/sound.png"));
        }
    }
}

void PreviewDialog::slotOpenMediaFile(void)
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Open Media file"), QString(), tr("Media (*.*)"));

    if(!filename.isEmpty())
    {
        reload(filename.toStdString());
    }
}

void PreviewDialog::slotSetExternalAudio(void)
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Open External Audio file"), QString(), tr("External Audio (*.*)"));

     if(!filename.isEmpty())
     {
         m_pPlayer->setExternalAudio(filename);
     }
}

void PreviewDialog::on_sliderSound_valueChanged(int a_value)
{
    m_pPlayer->audio()->setVolume(qreal(a_value) / eINDEX_100);
    g_pConfig->setConfig(Config::eCONFIG_COMMON_PREVIEW_SOUND_VALUME, a_value);
    updateSoundButtonIcon();
}
