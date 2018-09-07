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
    ui(new Ui::AudioEnc),
    m_pAdvancedConfig(new AudioAdvancedConfig(false))
{
    ui->setupUi(this);
    this->setup();
}

AudioEnc::~AudioEnc()
{
    delete m_pAdvancedConfig;
    delete ui;
}

void AudioEnc::setup(void)
{
    setDefaultConfig();
    setMode(m_pAdvancedConfig->isEnable());
}

void AudioEnc::setDefaultConfig(void)
{
    /* @AudioConfig::getDefaultConfig */

    m_pAdvancedConfig->setDisable(true);
    m_pAdvancedConfig->type = (uint)eENCODE_TYPE_AAC_APPLE;
    m_pAdvancedConfig->mode = (uint)AudioConfig::eQAAC_MODE_LC_AAC_CBR;
    m_pAdvancedConfig->profile = (uint)AudioConfig::eQAAC_PROFILE_LC_AAC;
    m_pAdvancedConfig->value = DEFAULT_BITRATE;
    m_pAdvancedConfig->value2 = false;
}

void AudioEnc::setConfig(const AudioAdvancedConfig &a_advancedConfig)
{
    bool enable = a_advancedConfig.isEnable();
    setMode(enable);
    m_pAdvancedConfig->name = a_advancedConfig.name;
    m_pAdvancedConfig->cmd = a_advancedConfig.cmd;
    m_pAdvancedConfig->type = a_advancedConfig.type;
    m_pAdvancedConfig->mode = a_advancedConfig.mode;
    m_pAdvancedConfig->profile = a_advancedConfig.profile;
    m_pAdvancedConfig->value = a_advancedConfig.value;
    m_pAdvancedConfig->value2 = a_advancedConfig.value2;

#ifndef QT_DEBUG
    m_pAdvancedConfig->print();
#endif
}

void AudioEnc::setMode(const bool &a_advancedMode)
{
    if(a_advancedMode)
    {
        ui->labelAudioBitrate->setVisible(false);
        ui->comboBoxAudioBitrate->setVisible(false);
        ui->labelAudioKbps->setVisible(false);
        ui->labelAudioEncoder->setEnabled(false);
        ui->comboBoxAudioEncoder->setEnabled(false);
    }
    else
    {
        ui->labelAudioBitrate->setVisible(true);
        ui->comboBoxAudioBitrate->setVisible(true);
        ui->labelAudioKbps->setVisible(true);
        ui->labelAudioEncoder->setEnabled(true);
        ui->comboBoxAudioEncoder->setEnabled(true);
    }
    m_pAdvancedConfig->setEnable(a_advancedMode);
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
    QString filename = qvs::chgFileExt(a_filename, getAudioOutputExt(a_type));

    if(filename == a_filename)
    {
        filename = qvs::chgFileExt(a_filename, "qvs" + QString(QT_EXT_SPLITE) + getAudioOutputExt(a_type));
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
    EENCODE_TYPE encode_type = static_cast<EENCODE_TYPE>(ui->comboBoxAudioEncoder->currentIndex());

    switch(encode_type)
    {
    case eENCODE_TYPE_AAC_APPLE:
        cmd = QString("%1 --ignorelength -c %2 - -o \"%3\"").arg(mainUi->m_com->findFirstFilePath(AUDIO_CONFIG_EXEC_AAC_APPLE)).arg(a_bitrate).arg(a_output);
        break;
    case eENCODE_TYPE_AAC_FDK:
        cmd = QString("%1 --ignorelength -b %2 - -o \"%3\"").arg(mainUi->m_com->findFirstFilePath(AUDIO_CONFIG_EXEC_AAC_FDK)).arg(a_bitrate).arg(a_output);
        break;
    case eENCODE_TYPE_AAC_NERO:
        cmd = QString("%1 -ignorelength -lc -br %2 -if - -of \"%3\"").arg(mainUi->m_com->findFirstFilePath(AUDIO_CONFIG_EXEC_AAC_NERO)).arg(QString::number(a_bitrate.toInt()*1000)).arg(a_output);
        break;
    case eENCODE_TYPE_FLAC:
        cmd = QString("%1 -5 - -o \"%2\"").arg(mainUi->m_com->findFirstFilePath(AUDIO_CONFIG_EXEC_FLAC)).arg(a_output);
        break;
    case eENCODE_TYPE_ALAC:
        cmd = QString("%1 --ignorelength - -o \"%2\"").arg(mainUi->m_com->findFirstFilePath(AUDIO_CONFIG_EXEC_ALAC)).arg(a_output);
        break;
    case eENCODE_TYPE_OPUS:
        cmd = QString("%1 --ignorelength --vbr --bitrate %2 - \"%3\"").arg(mainUi->m_com->findFirstFilePath(AUDIO_CONFIG_EXEC_OPUS)).arg(a_bitrate).arg(a_output);
        break;
    case eENCODE_TYPE_OGG_VORBIS:
        cmd = QString("%1 - --ignorelength --bitrate %2 -o \"%3\"").arg(mainUi->m_com->findFirstFilePath(AUDIO_CONFIG_EXEC_OGG_VORBIS)).arg(a_bitrate).arg(a_output);
        break;
    case eENCODE_TYPE_MP3:
        cmd = QString("%1 -b %2 --cbr -h - \"%3\"").arg(mainUi->m_com->findFirstFilePath(AUDIO_CONFIG_EXEC_MP3)).arg(a_bitrate).arg(a_output);
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
    if(m_pAdvancedConfig->isEnable())
    {
        if(encode_type == eENCODE_TYPE_AC3)
        {
            cmd = m_pAdvancedConfig->cmd.arg(mainUi->m_com->findFirstFilePath(getPiperFilename())).arg(a_input).arg(a_output);
        }
        else
        {
            cmd = m_pAdvancedConfig->cmd.arg(a_output);
        }
    }
    job_cmd.pipe = pipe;
    job_cmd.cmd = cmd;

#ifdef QT_DEBUG
    qDebug() << pipe << QT_PIPE << cmd;
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
    QString filename = AUDIO_CONFIG_EXEC_PIPER;

    if(g_pConfig->getConfig(Config::eCONFIG_COMMON_PREFER_AVS_32BIT).toBool())
    {
        filename = AUDIO_CONFIG_EXEC_PIPER_32;
    }
    return filename;
}

void AudioEnc::on_buttonAudioConfig_clicked()
{
    AudioConfig audioConfig;

    audioConfig.mainUi = mainUi;
    audioConfig.setConfig(m_pAdvancedConfig);

    switch(audioConfig.exec())
    {
    case QDialog::Accepted:
        break;
    case QDialog::Rejected:
    default:
        break;
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

void AudioEnc::on_comboBoxAudioEncoder_currentIndexChanged(int a_index)
{
    emit ui->comboBoxAudioEncoder->activated(a_index);

    bool bitrateMode = true;

    switch((EENCODE_TYPE)a_index)
    {
    case eENCODE_TYPE_ALAC:
    case eENCODE_TYPE_FLAC:
    case eENCODE_TYPE_WAV:
        bitrateMode = false;
        break;
    default:
        break;
    }
    ui->labelAudioBitrate->setEnabled(bitrateMode);
    ui->comboBoxAudioBitrate->setEnabled(bitrateMode);
    ui->labelAudioKbps->setEnabled(bitrateMode);

    m_pAdvancedConfig->type = (uint)a_index;
}
