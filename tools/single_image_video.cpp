#include "single_image_video.h"
#include "std_watcher.h"
#include "std_manager.h"
#include "../preview/preview_image_dialog.h"
#include "../mediainfo/mediainfo_id3.h"
#include "../mediainfo/mediainfo_prober.h"
#include "ui_single_image_video.h"

SingleImageVideo::SingleImageVideo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SingleImageVideo),
    m_pAudioContextMenu(nullptr)
{
    ui->setupUi(this);
    this->setup();
}

SingleImageVideo::~SingleImageVideo()
{
    delete m_pAudioContextMenu;
    delete ui;
}

void SingleImageVideo::setup(void)
{
    ui->editAudioInput->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->editImageInput->installEventFilter(this);
    ui->editAudioInput->installEventFilter(this);

    connect(ui->buttonImageInput, SIGNAL(clicked()), this, SLOT(showInOutDialog()));
    connect(ui->buttonAudioInput, SIGNAL(clicked()), this, SLOT(showInOutDialog()));
    connect(ui->buttonVideoOutput, SIGNAL(clicked()), this, SLOT(showInOutDialog()));
    connect(ui->buttonPreviewImage, SIGNAL(clicked()), this, SLOT(previewImage()));

    /* AudioInputMenu */
    m_pAudioContextMenu = new QMenu(this);
    QAction *at_action_input_image_from_id3 = new QAction(QIcon(":/buttons/slideshow_full_screen.png"), tr("Preview and input from cover"), this);
    m_pAudioContextMenu->addActions(QList<QAction*>() << at_action_input_image_from_id3);
    connect(at_action_input_image_from_id3, SIGNAL(triggered()), this, SLOT(previewImageFromAudioFile()));
}

void SingleImageVideo::reload(const QString &a_imageFilename, const QString &a_audioFilename)
{
    if(a_imageFilename != nullptr && !a_imageFilename.isEmpty())
    {
        ui->editImageInput->setText(QDir::toNativeSeparators(a_imageFilename));
        ui->editVideoOutput->setText(getOutputFilename(QDir::toNativeSeparators(a_imageFilename)));
    }

    if (a_audioFilename != nullptr && !a_audioFilename.isEmpty())
    {
        ui->editAudioInput->setText(QDir::toNativeSeparators(a_audioFilename));
    }
}

void SingleImageVideo::previewImage()
{
    QString imageFilename = ui->editImageInput->text();
    QString audioFilename = ui->editAudioInput->text();

    if (imageFilename.isEmpty() && !audioFilename.isEmpty())
    {
        int ret = QMessageBox::question(this, MESSAGE_FAILED, tr("Would you like to preview and input from the cover?"), QMessageBox::Yes | QMessageBox::No);

        if (ret == QMessageBox::Yes)
        {
            previewImageFromAudioFile();
        }
        return;
    }
    else if (imageFilename.isEmpty())
    {
        QMessageBox::critical(this, MESSAGE_FAILED, tr("Please input the image file firstly."), QMessageBox::Ok);
        return;
    }

    PreviewImageDialog dialog;

    if (dialog.reloadFromImageFile(imageFilename))
    {
        dialog.exec();
    }
    else
    {
        QMessageBox::critical(this, MESSAGE_FAILED, tr("Parse the image file failed."), QMessageBox::Ok);
        return;
    }
}

QImage SingleImageVideo::makeImageDivisibleBy2(const QImage &a_image, bool isShowQuestionBox)
{
    QImage image;

    if (a_image.isNull())
    {
        return a_image;
    }

    if ((a_image.width() % 2 != 0) || (a_image.height() % 2 != 0))
    {
        QSize recommendSize(a_image.size());

        if (a_image.width() % 2 != 0)
        {
            recommendSize.setWidth(recommendSize.width() + eINDEX_1);
        }
        if (a_image.height() % 2 != 0)
        {
            recommendSize.setHeight(recommendSize.height() + eINDEX_1);
        }

        int ret = QMessageBox::Ignore;

        if (isShowQuestionBox)
        {
            QString message = tr("Image size(%1x%2) is not divisible by 2.\nWould you like scale to size(%3x%4)?")
                                .arg(a_image.width()).arg(a_image.height())
                                .arg(recommendSize.width()).arg(recommendSize.height());
            ret = QMessageBox::question(this, MESSAGE_FAILED, message, QMessageBox::Yes | QMessageBox::Cancel);
        }

        if (ret == QMessageBox::Yes || !isShowQuestionBox)
        {
            image = a_image.scaled(recommendSize, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        }
    }
    else
    {
        return a_image;
    }

    return image;
}

void SingleImageVideo::previewImageFromAudioFile()
{
    QString audioFilename = ui->editAudioInput->text();

    if (audioFilename.isEmpty())
    {
        QMessageBox::critical(this, MESSAGE_FAILED, tr("Please input the audio file firstly."), QMessageBox::Ok);
        return;
    }

    PreviewImageDialog dialog;

    if (dialog.reloadFromAudioFile(audioFilename))
    {
        dialog.exec();
        dialog.close();

        QImage image = dialog.getFrameImage();

        if (image.isNull())
        {
            qDebug() << "Single Image Video: Cover image is null!";
            return;
        }

        image = makeImageDivisibleBy2(image, true);

        QString outputFilename = QString("%1_cover.%2").arg(audioFilename).arg(OUTPUT_EXT_JPG);

        if (!image.save(outputFilename, OUTPUT_EXT_JPG, 100))
        {
            QMessageBox::critical(this, MESSAGE_FAILED, tr("Save image file '%1' failed.").arg(outputFilename), QMessageBox::Ok);
            return;
        }

        reload(outputFilename, nullptr);
    }
    else
    {
        QMessageBox::critical(this, MESSAGE_FAILED, tr("There is no cover for this audio."), QMessageBox::Ok);
        return;
    }
}

QString SingleImageVideo::getOutputFilename(const QString &a_path)
{
    return QString("%1_siv.%2").arg(qvs::delFileExt(a_path)).arg(OUTPUT_EXT_MP4);
}

bool SingleImageVideo::eventFilter(QObject *o, QEvent *e)
{
    if(o == ui->editImageInput && e->type() == QEvent::MouseButtonDblClick)
    {
        ui->editImageInput->clear();
        ui->editVideoOutput->clear();
    }
    else if(o == ui->editAudioInput && e->type() == QEvent::MouseButtonDblClick)
    {
        ui->editAudioInput->clear();
    }
    return false;
}

void SingleImageVideo::showInOutDialog()
{
    if (sender() == nullptr)
    {
        return;
    }

    if (sender() == ui->buttonImageInput)
    {
        QString filename = QFileDialog::getOpenFileName(this, tr("Open Image"), NULLSTR, tr("Image file (*.bmp *.jpg *.jpeg *.png *.pbm *.pgm *.ppm *.xbm *.xpm)"));

        if(!filename.isEmpty())
        {
            filename = QDir::toNativeSeparators(filename);
            reload(filename, nullptr);
        }
    }
    else if (sender() == ui->buttonAudioInput)
    {
        QString filename = QFileDialog::getOpenFileName(this, tr("Open Audio"), NULLSTR, tr("Audio file (*.*)"));

        if(!filename.isEmpty())
        {
            filename = QDir::toNativeSeparators(filename);
            reload(nullptr, filename);
        }
    }
    else if (sender() == ui->buttonVideoOutput)
    {
        QString filename = QFileDialog::getSaveFileName(this, tr("Edit Filename"), NULLSTR, tr("Video file (*.mp4)"));

        if(!filename.isEmpty())
        {
            filename = QDir::toNativeSeparators(filename);
            ui->editVideoOutput->setText(QDir::toNativeSeparators(filename));
        }
    }
}

void SingleImageVideo::on_editAudioInput_customContextMenuRequested(const QPoint &)
{
    m_pAudioContextMenu->exec(QCursor::pos());
}

void SingleImageVideo::on_buttonImageVideoStart_clicked()
{
    QString imageFilename = ui->editImageInput->text();
    QString audioFilename = ui->editAudioInput->text();
    QString videoFilename = ui->editVideoOutput->text();

    if (imageFilename.isEmpty() && !audioFilename.isEmpty())
    {
        previewImage();

        imageFilename = ui->editImageInput->text();
        audioFilename = ui->editAudioInput->text();
        videoFilename = ui->editVideoOutput->text();

        if (imageFilename.isEmpty())
        {
            return;
        }
    }

    if (imageFilename.isEmpty())
    {
        QMessageBox::critical(this, MESSAGE_FAILED, tr("Please input the image file."), QMessageBox::Ok);
        return;
    }

    if (videoFilename.isEmpty())
    {
        QMessageBox::critical(this, MESSAGE_FAILED, tr("Please edit the output video path."), QMessageBox::Ok);
        return;
    }
    else if (qvs::isFileExist(videoFilename))
    {
        int reply = QMessageBox::question(this, MESSAGE_QUESTION, tr("Output file already exists! Overwrite?"), QMessageBox::Yes | QMessageBox::Cancel);

        if(reply == QMessageBox::Cancel)
        {
            return;
        }
    }

    QImage image(imageFilename);

    if (image.isNull())
    {
        QMessageBox::critical(this, MESSAGE_FAILED, tr("Parse image file failed!"), QMessageBox::Ok);
        return;
    }

    QSize sizeBeforeDivisibleCheck = image.size();

    image = makeImageDivisibleBy2(image, false);

    if (image.size() != sizeBeforeDivisibleCheck || qvs::getFileExt(imageFilename) != OUTPUT_EXT_JPG)
    {
        imageFilename = QString("%1_qvs.jpg").arg(imageFilename);
        image.save(imageFilename, OUTPUT_EXT_JPG, 100);
    }

    QString output2 = videoFilename;
    QString output1 = QString("%1_tmp.%2").arg(qvs::delFileExt(imageFilename)).arg(OUTPUT_EXT_MP4);
    long time = 0; // Unit is sec.

    if (audioFilename.isEmpty())
    {
        output1 = output2;

        bool ok;

        time = QInputDialog::getInt(this, tr("Enter"), tr("Audio file is empty.\nPlease enter the output length(sec.):"), 100, 0, 2147483647, 1, &ok);

        if (!ok)
        {
            return;
        }
    }
    else
    {
        MediaInfoProber *mediainfoProber = new MediaInfoProber();

        if (!mediainfoProber->open(audioFilename))
        {
            mediainfoProber->close();
            QMessageBox::critical(this, MESSAGE_FAILED, tr("Parse audio media info failed!"), QMessageBox::Ok);
            return;
        }

        time = static_cast<long>(mediainfoProber->getDuration());
        mediainfoProber->close();
    }

    QString cmdString1 = QString("%1 -loop 1 -r %2 -t %3 -f image2 -i \"%4\" -c:v libx264 -crf %5 -y \"%6\"")
            .arg(qvs::findFirstFilePath(SIGNLE_IMAGE_VIDEO_EXEC_FFMPEG)) // 1
            .arg(ui->spinBoxFPS->value()) // 2
            .arg(time) // 3
            .arg(imageFilename) // 4
            .arg(ui->doubleSpinBoxCRF->value()) // 5
            .arg(output1); // 6
    QString cmdString2;
    QString cmdString3;

    qDebug() << cmdString1;
    if (!audioFilename.isEmpty())
    {
        cmdString2 = QString("%1 -i \"%2\" -i \"%3\" -c:v copy -c:a copy -y \"%4\"")
                .arg(qvs::findFirstFilePath(SIGNLE_IMAGE_VIDEO_EXEC_FFMPEG)) // 1
                .arg(output1) // 2
                .arg(audioFilename) // 3
                .arg(output2); // 4
        qDebug() << cmdString2;

        cmdString3 = QString("cmd /c del \"%1\"").arg(output1);
        qDebug() << cmdString3;
    }


    QList<StdWatcherCmd> cmds;

    if (!cmdString1.isEmpty())
    {
        StdWatcherCmd cmd1;

        cmd1.cmd = cmdString1;
        cmds << cmd1;
    }
    if (!cmdString2.isEmpty())
    {
        StdWatcherCmd cmd2;

        cmd2.cmd = cmdString2;
        cmds << cmd2;
    }
    if (!cmdString3.isEmpty())
    {
        StdWatcherCmd cmd3;

        cmd3.cmd = cmdString3;
        cmds << cmd3;
    }

    if(cmds.isEmpty())
    {
        return;
    }

    QUuid uid = StdManager::createStdWatch();

    g_pStdWatch[uid]->show();
    g_pStdWatch[uid]->initJob(uid);
    g_pStdWatch[uid]->startJob(cmds);
}
