#include "preview_image_dialog.h"
#include "../mediainfo/mediainfo_id3.h"
#include "ui_preview_image_dialog.h"

PreviewImageDialog::PreviewImageDialog(QWidget *parent) :
    QMainWindow(parent),
    m_frameImageIndex(eINDEX_NONE),
    ui(new Ui::PreviewImageDialog),
    m_pEventLoop(nullptr),
    m_pContextMenu(nullptr),
    m_statusBarLabel(new QLabel)
{
    ui->setupUi(this);
    this->setup();
}

PreviewImageDialog::~PreviewImageDialog()
{
    delete m_pContextMenu;
    delete ui;
}

void PreviewImageDialog::setup(void)
{
    this->installEventFilter(this);
    this->setWindowModality(Qt::ApplicationModal);
    this->setAttribute(Qt::WA_DeleteOnClose, false); // Disable attribute `DeleteOnClose`

    ui->widgetJumpPage->setVisible(false);
    ui->statusBar->addPermanentWidget(m_statusBarLabel, eINDEX_1);
    ui->previewArea->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    ui->previewArea->installEventFilter(this);
    ui->previewArea->previewArea()->installEventFilter(this);

	connect(ui->previewArea, SIGNAL(customContextMenuRequested(const QPoint &)), this, SLOT(previewContextMenuRequested(const QPoint &)));
    connect(ui->buttonPagePrev, SIGNAL(clicked()), this, SLOT(slotJumpPagePrev()));
    connect(ui->buttonPageNext, SIGNAL(clicked()), this, SLOT(slotJumpPageNext()));
    connect(ui->frameToClipboardButton, SIGNAL(clicked()), this, SLOT(slotFrameToClipboard()));

    /* ContextMenu */
    m_pContextMenu = new QMenu(ui->previewArea);
}

int PreviewImageDialog::exec()
{
    this->show();

    if (m_pEventLoop == nullptr)
    {
        m_pEventLoop = new QEventLoop(this);
    }
    return m_pEventLoop->exec();
}

void PreviewImageDialog::updateStatus(void)
{
    if (m_frameImages.length() > eINDEX_0)
    {
        m_statusBarLabel->setText(getStatus());
        m_statusBarLabel->adjustSize();
    }
}

QString PreviewImageDialog::getStatus(void)
{
    QString statusString = tr("[%1/%2]").arg(m_frameImageIndex + eINDEX_1).arg(m_frameImages.length());

    QImage currentImage = getFrameImage();

    if (!currentImage.isNull())
    {
        statusString += QObject::tr(" Size: %1x%2").arg(currentImage.width()).arg(currentImage.height());
    }
    return statusString;
}

void PreviewImageDialog::updateTitle(const QString& a_filename)
{
    this->setWindowTitle(QString("Preview - %1").arg(a_filename));
}

bool PreviewImageDialog::reloadFromImageFile(const QString& a_filename)
{
    QImage image(a_filename);

    if(reload(image))
    {
        updateTitle(a_filename);
        updateStatus();
        return true;
    }
    return false;
}

bool PreviewImageDialog::reloadFromAudioFile(const QString& a_filename)
{
    AudioInfo audioInfo = getAudioInfo(a_filename);

    if(reload(audioInfo.m_infoImages))
    {
        updateTitle(a_filename);
        updateStatus();
        return true;
    }
    return false;
}

bool PreviewImageDialog::reload(QImage a_iamge)
{
    if (a_iamge.isNull())
    {
        return false;
    }

    return reload(QList<QImage>() << a_iamge);
}

bool PreviewImageDialog::reload(QList<QImage> a_iamges)
{
    m_frameImages = a_iamges;

    if (m_frameImages.length() > 0)
    {
        setPreviewPixmap(m_frameImages.first());

        ui->widgetJumpPage->setVisible(true);
        m_frameImageIndex = eINDEX_0;

        ui->buttonPagePrev->setEnabled(false);

        if (m_frameImages.length() == eINDEX_1)
        {
            ui->buttonPageNext->setEnabled(false);
            ui->widgetJumpPage->setVisible(false);
        }
        else
        {
            ui->buttonPageNext->setEnabled(true);
        }
        updateStatus();

        return true;
    }
    else
    {
        ui->widgetJumpPage->setVisible(false);
        ui->buttonPagePrev->setEnabled(false);
        ui->buttonPageNext->setEnabled(false);
    }

    return false;
}

AudioInfo PreviewImageDialog::getAudioInfo(const QString& a_filename)
{
    MediaInfoID3 id3;
    AudioInfo audioInfo;

    id3.open(a_filename);

    audioInfo.m_infoMap = id3.m_infoMap;
    audioInfo.m_infoImages = id3.m_infoImages;

    return audioInfo;
}

QImage PreviewImageDialog::getFrameImage()
{
    if (m_frameImages.length() > 0 && m_frameImageIndex >= eINDEX_0 && m_frameImageIndex < m_frameImages.length())
    {
        return m_frameImages[m_frameImageIndex];
    }

    return QImage();
}

void PreviewImageDialog::setPreviewPixmap(const QImage &a_image)
{
    m_framePixmap = QPixmap::fromImage(a_image);
    setPreviewPixmap();
}

void PreviewImageDialog::setPreviewPixmap(void)
{
    if(m_framePixmap.isNull())
    {
        return;
    }

    QPixmap previewPixmap;
    int frameWidth = 0;
    int frameHeight = 0;

    {
        QRect previewRect = ui->previewArea->geometry();
        int cropSize = ui->previewArea->frameWidth() * 2;

        frameWidth = previewRect.width() - cropSize;
        frameHeight = previewRect.height() - cropSize;
    }

    previewPixmap = m_framePixmap.scaled(frameWidth, frameHeight, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    ui->previewArea->setPixmap(previewPixmap);
}

QRect PreviewImageDialog::getPreviewRect(void)
{
    /* Called by preview painter's paint event. */
    int frameWidth = 0;
    int frameHeight = 0;
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
    return QRect(0, 0, frameWidth, frameHeight);
}

void PreviewImageDialog::slotJumpPagePrev(void)
{
    if (m_frameImageIndex - eINDEX_1 >= eINDEX_0)
    {
        m_frameImageIndex--;
        setPreviewPixmap(getFrameImage());
        updateStatus();

        ui->buttonPageNext->setEnabled(true);
        if (m_frameImageIndex == eINDEX_0)
        {
            ui->buttonPagePrev->setEnabled(false);
        }
    }
}

void PreviewImageDialog::slotJumpPageNext(void)
{
    if (m_frameImageIndex + eINDEX_1 < m_frameImages.length())
    {
        m_frameImageIndex++;
        setPreviewPixmap(getFrameImage());
        updateStatus();

        ui->buttonPagePrev->setEnabled(true);
        if (m_frameImageIndex == m_frameImages.length() - eINDEX_1)
        {
            ui->buttonPageNext->setEnabled(false);
        }
    }
}

void PreviewImageDialog::slotFrameToClipboard(void)
{
    if(m_framePixmap.isNull())
    {
        return;
    }

    QClipboard * pClipboard = QApplication::clipboard();
    pClipboard->setPixmap(m_framePixmap);
}

void PreviewImageDialog::showEvent(QShowEvent *e)
{
    setPreviewPixmap(getFrameImage());
    e->accept();
}

void PreviewImageDialog::closeEvent(QCloseEvent *e)
{
    if(m_pEventLoop != nullptr)
    {
        m_pEventLoop->exit();
    }
    e->accept();
}

void PreviewImageDialog::resizeEvent(QResizeEvent *a_pEvent)
{
    setPreviewPixmap(getFrameImage());
    a_pEvent->accept();
}

void PreviewImageDialog::previewContextMenuRequested(const QPoint &)
{
    m_pContextMenu->exec(QCursor::pos());
}

