#include "audio_enc.h"
#include "audio_config.h"
#include "std_manager.h"
#include "mainwindow.h"
#include "ui_audio_enc.h"
#include "ui_audio_config.h"
#include "ui_mainwindow.h"

extern QMap<QUuid, StdWatcher*> g_pStdWatch;

AudioEnc::AudioEnc(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AudioEnc)
{
    ui->setupUi(this);
    this->setupUi();
}

AudioEnc::~AudioEnc()
{
    delete ui;
}

void AudioEnc::setupUi(void)
{
    setMode(true);
}

void AudioEnc::setMode(bool a_bitrateMode)
{
    if(a_bitrateMode)
    {
        ui->labelAudioBitrate->setVisible(true);
        ui->comboBoxAudioBitrate->setVisible(true);
        ui->labelAudioKbps->setVisible(true);
        ui->labelAudioQuarity->setVisible(false);
        ui->comboBoxAudioQuarity->setVisible(false);
    }
    else
    {
        ui->labelAudioBitrate->setVisible(false);
        ui->comboBoxAudioBitrate->setVisible(false);
        ui->labelAudioKbps->setVisible(false);
        ui->labelAudioQuarity->setVisible(true);
        ui->comboBoxAudioQuarity->setVisible(true);
    }
}

void AudioEnc::reload(QString a_filename)
{
    ui->editAudioInput->setText(a_filename);
    ui->editAudioOutput->setText(getAudioOutputPath((EENCODE_TYPE)ui->comboBoxAudioEncoder->currentIndex(), a_filename));
}

void AudioEnc::reload(void)
{
    QString filename = ui->editAudioInput->text();
    ui->editAudioOutput->setText(getAudioOutputPath((EENCODE_TYPE)ui->comboBoxAudioEncoder->currentIndex(), filename));
}

QString AudioEnc::getAudioOutputPath(EENCODE_TYPE a_type, QString a_filename)
{
    QString filename = chgFileExt(a_filename, getAudioOutputExt(a_type));

    if(filename == a_filename)
    {
        filename = chgFileExt(a_filename, "qvs" + QString(QT_EXT_SPLITE) + getAudioOutputExt(a_type));
    }
    return filename;
}

QString AudioEnc::getAudioOutputExt(EENCODE_TYPE a_type)
{
    QString ext;

    switch(a_type)
    {
    case eENCODE_TYPE_AAC_APPLE:
    case eENCODE_TYPE_AAC_FDK:
    case eENCODE_TYPE_AAC_NERO:
        ext = "aac";
        break;
    case eENCODE_TYPE_FLAC:
        ext = "flac";
        break;
    case eENCODE_TYPE_ALAC:
        ext = "alac";
        break;
    case eENCODE_TYPE_OPUS:
        ext = "opus";
        break;
    case eENCODE_TYPE_OGG_VORBIS:
        ext = "ogg";
        break;
    case eENCODE_TYPE_MP3:
        ext = "mp3";
        break;
    case eENCODE_TYPE_AC3:
        ext = "ac3";
        break;
    case eENCODE_TYPE_WAV:
        ext = "wav";
        break;
    default:
        break;
    }
    return ext;
}

StdWatcherCmd AudioEnc::getEncodeCmd(QString a_input, QString a_output, QString a_bitrate)
{
    StdWatcherCmd job_cmd;
    QString pipe = QString("%1 -i \"%2\" -vn -sn -v 0 -c:a pcm_s16le -f wav pipe: ").arg(mainUi->m_com->findFirstFilePath(getPiperFilename())).arg(a_input);
    QString cmd;

    switch((EENCODE_TYPE)ui->comboBoxAudioEncoder->currentIndex())
    {
    case eENCODE_TYPE_AAC_APPLE:
        cmd = QString("%1 -q 2 --ignorelength -c %2 - -o \"%3\"").arg(mainUi->m_com->findFirstFilePath("qaac")).arg(a_bitrate).arg(a_output);
        break;
    case eENCODE_TYPE_AAC_FDK:
        cmd = QString("%1 --ignorelength -b %2 - -o \"%3\"").arg(mainUi->m_com->findFirstFilePath("fdkaac")).arg(a_bitrate).arg(a_output);
        break;
    case eENCODE_TYPE_AAC_NERO:
        cmd = QString("%1 -ignorelength -lc -br %2 -if - -of \"%3\"").arg(mainUi->m_com->findFirstFilePath("neroAacEnc")).arg(QString::number(a_bitrate.toInt()*1000)).arg(a_output);
        break;
    case eENCODE_TYPE_FLAC:
        cmd = QString("%1 -f --ignore-chunk-sizes -5 - -o \"%2\"").arg(mainUi->m_com->findFirstFilePath("flac")).arg(a_output);
        break;
    case eENCODE_TYPE_ALAC:
        cmd = QString("%1 --ignorelength - -o \"%2\"").arg(mainUi->m_com->findFirstFilePath("refalac")).arg(a_output);
        break;
    case eENCODE_TYPE_OPUS:
        cmd = QString("%1 --ignorelength --bitrate %2 - \"%3\"").arg(mainUi->m_com->findFirstFilePath("opusenc")).arg(a_bitrate).arg(a_output);
        break;
    case eENCODE_TYPE_OGG_VORBIS:
        cmd = QString("%1 - --ignorelength --bitrate %2 -o \"%3\"").arg(mainUi->m_com->findFirstFilePath("oggenc2")).arg(a_bitrate).arg(a_output);
        break;
    case eENCODE_TYPE_MP3:
        cmd = QString("%1 -q 3 -b %2 - \"%3\"").arg(mainUi->m_com->findFirstFilePath("lame")).arg(a_bitrate).arg(a_output);
        break;
    case eENCODE_TYPE_AC3:
        cmd = QString("%1 -i \"%2\" -c:a ac3 -b:a %3k \"%4\" -y").arg(mainUi->m_com->findFirstFilePath(getPiperFilename())).arg(a_input).arg(a_bitrate).arg(a_output);
        pipe.clear();
        break;
    case eENCODE_TYPE_WAV:
        cmd = QString("%1 -i \"%2\" -f wav \"%3\" -y").arg(mainUi->m_com->findFirstFilePath(getPiperFilename())).arg(a_input).arg(a_output);
        pipe.clear();
        break;
    default:
        break;
    }
    job_cmd.pipe = pipe;
    job_cmd.cmd = cmd;

#ifdef QT_DEBUG
    qDebug() << pipe << "|" << cmd;
#endif

    return job_cmd;
}

void AudioEnc::on_buttonAudioStart_clicked()
{
    QString input = ui->editAudioInput->text();
    QString output = ui->editAudioOutput->text();
    QString bitrate = ui->comboBoxAudioBitrate->currentText();

    if(input.isEmpty())
    {
        QMessageBox::warning(this, tr("Warning"), tr("Input file is empty!"), QMessageBox::Ok);
        return;
    }
    if(output.isEmpty())
    {
        QMessageBox::warning(this, tr("Warning"), tr("Output file is empty!"), QMessageBox::Ok);
        return;
    }
    if(mainUi->m_com->isFile(output))
    {
        if(output == input)
        {
            QMessageBox::critical(this, tr("Are you BAKA?"), tr("Output file can't be the same as source file!"), QMessageBox::Cancel);
            return;
        }

        int reply = QMessageBox::question(this, tr("Question"), tr("Output file already exists! Overwrite?"), QMessageBox::Yes | QMessageBox::Cancel);

        if(reply == QMessageBox::Cancel)
        {
            return;
        }
    }

    StdWatcherCmd job_cmd = getEncodeCmd(input, output, bitrate);

    QUuid uid = StdManager::createStdWatch();
    g_pStdWatch[uid]->show();
    g_pStdWatch[uid]->initJob(uid);

    if(job_cmd.pipe.isEmpty())
    {
        g_pStdWatch[uid]->startJob(job_cmd.cmd);
    }
    else
    {
        g_pStdWatch[uid]->startJob(job_cmd);
    }
}

void AudioEnc::on_comboBoxAudioEncoder_activated(int a_index)
{
    QString input = ui->editAudioInput->text();

    if(input.isEmpty())
    {
        return;
    }
    ui->editAudioOutput->setText(getAudioOutputPath((EENCODE_TYPE)a_index, input));
}

void AudioEnc::on_buttonAudioInput_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Open Audio file"), NULL, tr("Audio (*.*)"));

    if(!filename.isEmpty())
    {
        filename = QDir::toNativeSeparators(filename);
        reload(filename);
    }
}

void AudioEnc::on_buttonAudioOutput_clicked()
{
    QString filename = QFileDialog::getSaveFileName(this, tr("Save Audio file"), ui->editAudioOutput->text(), tr("Audio (*.*)"));

    if(!filename.isEmpty())
    {
        filename = QDir::toNativeSeparators(filename);
        ui->editAudioOutput->setText(filename);
    }
}

QString AudioEnc::getPiperFilename(void)
{
    QString filename = "ffmpeg";

    if(g_pConfig->getConfig(Config::eCONFIG_COMMON_PREFER_AVS_32BIT).toBool())
    {
        filename = "ffmpeg32";
    }
    return filename;
}

void AudioEnc::on_buttonAudioConfig_clicked()
{
    AudioConfig audioConfig;

    audioConfig.mainUi = mainUi;
    audioConfig.ui->comboBoxAudioEncoder->setCurrentIndex(ui->comboBoxAudioEncoder->currentIndex());
    emit audioConfig.ui->comboBoxAudioEncoder->currentIndexChanged(ui->comboBoxAudioEncoder->currentIndex());

    switch(audioConfig.exec())
    {
    case QDialog::Accepted:
        break;
    case QDialog::Rejected:
    default:
        break;
    }
}
