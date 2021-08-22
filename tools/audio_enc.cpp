#include "audio_enc.h"
#include "audio_config.h"
#include "std_manager.h"
#include "mainwindow.h"
#include "../com/style_sheet.h"
#include "../mediainfo/mediainfo_enum.h"
#include "ui_audio_enc.h"
#include "ui_audio_config.h"
#include "ui_mainwindow.h"

extern QMap<QUuid, StdWatcher*> g_pStdWatch;

AudioEnc::AudioEnc(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AudioEnc),
    m_pAdvancedConfig(new AudioAdvancedConfig(false)),
    m_validatorBitrate(new QRegExpValidator(QRegExp("(\\d?){0,6}"), nullptr))
{
    ui->setupUi(this);
    this->setup();
}

AudioEnc::~AudioEnc()
{
    delete m_pAdvancedConfig;
    delete m_validatorBitrate;
    delete ui;
}

void AudioEnc::setup(void)
{
    this->setAcceptDrops(false);
    this->setAttribute(Qt::WA_DeleteOnClose, true);
    setDefaultConfig();
    setMode(m_pAdvancedConfig->isEnable());
    ui->editAudioInput->setStyleSheet(c_qss_line_edit_read_only);
    ui->comboBoxAudioBitrate->lineEdit()->setValidator(m_validatorBitrate);
}

void AudioEnc::setDefaultConfig(void)
{
    /* @AudioConfig::getDefaultConfig */

    m_pAdvancedConfig->setDisable(true);
    m_pAdvancedConfig->type = static_cast<uint>(eENCODE_TYPE_AAC_APPLE);
    m_pAdvancedConfig->mode = static_cast<uint>(AudioConfig::eQAAC_MODE_LC_AAC_CBR);
    m_pAdvancedConfig->profile = static_cast<uint>(AudioConfig::eQAAC_PROFILE_LC_AAC);
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

    g_pConfig->setConfig(Config::eCONFIG_COMMON_ENCODING_AUDIO_CURRENT_PRESETS, qvs::getStringFromJson(g_pConfig->audioConfigToJson(a_advancedConfig)).simplified());

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

void AudioEnc::init(void)
{
    QString jsonStr = g_pConfig->getConfig(Config::eCONFIG_COMMON_ENCODING_AUDIO_CURRENT_PRESETS).toString();
    AudioAdvancedConfig config;

    if(jsonStr.isEmpty())
    {
        return;
    }

    config = g_pConfig->jsonToAudioConfig(qvs::getJsonFromString(jsonStr));

    if( config.isEnable() || (true) )
    {
        AudioConfig widgetAudioConfig;

        widgetAudioConfig.mainUi = mainUi;
        widgetAudioConfig.hide();
        widgetAudioConfig.setConfig(config);
        emit widgetAudioConfig.ui->buttonAccept->clicked();
    }

    /* AudioConfig will not set the value on disable. */
    if(!config.isEnable())
    {
        m_pAdvancedConfig->value = config.value;
        ui->comboBoxAudioBitrate->setCurrentText(config.value.toString());
    }
}

void AudioEnc::reload(QString a_filename)
{
    ui->editAudioInput->setText(a_filename);
    ui->editAudioOutput->setText(getAudioOutputPath(static_cast<EENCODE_TYPE>(ui->comboBoxAudioEncoder->currentIndex()), a_filename));
}

void AudioEnc::reload(void)
{
    QString filename = ui->editAudioInput->text();
    ui->editAudioOutput->setText(getAudioOutputPath(static_cast<EENCODE_TYPE>(ui->comboBoxAudioEncoder->currentIndex()), filename));
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
    QString pipe = QString("%1 -i \"%2\" -vn -sn -v 0 -c:a pcm_s16le -f wav pipe: ").arg(qvs::findFirstFilePath(getPiperFilename())).arg(a_input);
    QString cmd;
    EENCODE_TYPE encode_type = static_cast<EENCODE_TYPE>(ui->comboBoxAudioEncoder->currentIndex());

    switch(encode_type)
    {
    case eENCODE_TYPE_AAC_APPLE:
        cmd = QString("%1 --ignorelength -c %2 - -o \"%3\"").arg(qvs::findFirstFilePath(AUDIO_CONFIG_EXEC_AAC_APPLE)).arg(a_bitrate).arg(a_output);
        break;
    case eENCODE_TYPE_AAC_FDK:
        cmd = QString("%1 --ignorelength -b %2 - -o \"%3\"").arg(qvs::findFirstFilePath(AUDIO_CONFIG_EXEC_AAC_FDK)).arg(a_bitrate).arg(a_output);
        break;
    case eENCODE_TYPE_AAC_NERO:
        cmd = QString("%1 -ignorelength -lc -br %2 -if - -of \"%3\"").arg(qvs::findFirstFilePath(AUDIO_CONFIG_EXEC_AAC_NERO)).arg(QString::number(a_bitrate.toInt()*1000)).arg(a_output);
        break;
    case eENCODE_TYPE_FLAC:
        cmd = QString("%1 -5 - -o \"%2\"").arg(qvs::findFirstFilePath(AUDIO_CONFIG_EXEC_FLAC)).arg(a_output);
        break;
    case eENCODE_TYPE_ALAC:
        cmd = QString("%1 --ignorelength - -o \"%2\"").arg(qvs::findFirstFilePath(AUDIO_CONFIG_EXEC_ALAC)).arg(a_output);
        break;
    case eENCODE_TYPE_OPUS:
        cmd = QString("%1 --ignorelength --vbr --bitrate %2 - \"%3\"").arg(qvs::findFirstFilePath(AUDIO_CONFIG_EXEC_OPUS)).arg(a_bitrate).arg(a_output);
        break;
    case eENCODE_TYPE_OGG_VORBIS:
        cmd = QString("%1 - --ignorelength --bitrate %2 -o \"%3\"").arg(qvs::findFirstFilePath(AUDIO_CONFIG_EXEC_OGG_VORBIS)).arg(a_bitrate).arg(a_output);
        break;
    case eENCODE_TYPE_MP3:
        cmd = QString("%1 -b %2 --cbr -h - \"%3\"").arg(qvs::findFirstFilePath(AUDIO_CONFIG_EXEC_MP3)).arg(a_bitrate).arg(a_output);
        break;
    case eENCODE_TYPE_AC3:
        cmd = QString("%1 -i \"%2\" -c:a ac3 -b:a %3k \"%4\" -y").arg(qvs::findFirstFilePath(getPiperFilename())).arg(a_input).arg(a_bitrate).arg(a_output);
        pipe.clear();
        break;
    case eENCODE_TYPE_WAV:
        cmd = QString("%1 -i \"%2\" -f wav \"%3\" -y").arg(qvs::findFirstFilePath(getPiperFilename())).arg(a_input).arg(a_output);
        pipe.clear();
        break;
    default:
        break;
    }
    if(m_pAdvancedConfig->isEnable())
    {
        if(encode_type == eENCODE_TYPE_AC3)
        {
            cmd = m_pAdvancedConfig->cmd.arg(qvs::findFirstFilePath(getPiperFilename())).arg(a_input).arg(a_output);
        }
        else if (encode_type == eENCODE_TYPE_MP3 && m_pAdvancedConfig->value2.toBool())
        {
            QStringList cmds = m_pAdvancedConfig->cmd.split('|');

            MediaInfoLoader mi = MediaInfoLoader(a_input);
            QString format = mi.get(MI_AUDIO_FORMAT, stream_t::Stream_Audio);

            if (format == "MPEG Audio")
            {
                pipe = QString();
                cmd = QString("cmd /c echo It's already in MP3 format, so only copy. & copy \"%1\" \"%2\" /y").arg(a_input).arg(a_output);
            }
            else
            {
                QString bitRateMode = mi.get(MI_AUDIO_BITRATE_MODE, stream_t::Stream_Audio);
                int bitRateSrc = qRound(mi.get(MI_AUDIO_BITRATE, stream_t::Stream_Audio).toInt() / 1000.0);
                int bitRateTar = 192;
                AudioConfig::EAUDIO_CONFIG_MODE formatTar = AudioConfig::eMP3_MODE_ABR;

                if (bitRateMode == "VBR" || bitRateMode == "Variable")
                {
                    int bitRateMaxSrc = qRound(mi.get(MI_AUDIO_BITRATE_MAXIMUM, stream_t::Stream_Audio).toInt() / 1000.0);

                    bitRateTar = qMax(bitRateMaxSrc, bitRateSrc);
                    formatTar = AudioConfig::eMP3_MODE_CBR;
                }
                else
                {
                    // -----------------------------------------------------------------------------------------------------------------------
                    // 0   24       24    64     88        88     128    152       152    192    216       216    256    280       280    320
                    //     64VBR    64CBR        128ABR    128CBR        192ABR    192CBR        256ABR    256CBR        320ABR    320CBR
                    // -----------------------------------------------------------------------------------------------------------------------

                    // 280~ -> 320C
                    if (bitRateSrc >= 280)
                    {
                        bitRateTar = 320;
                        formatTar = AudioConfig::eMP3_MODE_CBR;
                    }
                    // 256~280 -> 320V
                    else if (bitRateSrc >= 256 && bitRateSrc < 280)
                    {
                        bitRateTar = 320;
                        formatTar = AudioConfig::eMP3_MODE_ABR;
                    }
                    // 216~256 -> 256C
                    else if (bitRateSrc >= 216 && bitRateSrc < 256)
                    {
                        bitRateTar = 256;
                        formatTar = AudioConfig::eMP3_MODE_CBR;
                    }
                    // 192~216 -> 256V
                    else if (bitRateSrc >= 192 && bitRateSrc < 216)
                    {
                        bitRateTar = 256;
                        formatTar = AudioConfig::eMP3_MODE_ABR;
                    }
                    // 152~192 -> 192C
                    else if (bitRateSrc >= 152 && bitRateSrc < 192)
                    {
                        bitRateTar = 192;
                        formatTar = AudioConfig::eMP3_MODE_CBR;
                    }
                    // 128~152 -> 192V
                    else if (bitRateSrc >= 128 && bitRateSrc < 152)
                    {
                        bitRateTar = 192;
                        formatTar = AudioConfig::eMP3_MODE_ABR;
                    }
                    // 88~128 -> 128C
                    else if (bitRateSrc >= 88 && bitRateSrc < 128)
                    {
                        bitRateTar = 128;
                        formatTar = AudioConfig::eMP3_MODE_CBR;
                    }
                    // 64~88 -> 128V
                    else if (bitRateSrc >= 64 && bitRateSrc < 88)
                    {
                        bitRateTar = 128;
                        formatTar = AudioConfig::eMP3_MODE_ABR;
                    }
                    // 24~64 -> 64C
                    else if (bitRateSrc >= 24 && bitRateSrc < 64)
                    {
                        bitRateTar = 64;
                        formatTar = AudioConfig::eMP3_MODE_CBR;
                    }
                    // 0~24 -> 64V
                    else if (bitRateSrc >= 0 && bitRateSrc < 24)
                    {
                        bitRateTar = 64;
                        formatTar = AudioConfig::eMP3_MODE_ABR;
                    }
                }
                cmd = QString().sprintf(cmds[static_cast<int>(formatTar)].toUtf8(), bitRateTar).arg(a_output);
            }
            mi.close();
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

StdWatcher::EDATA_TYPE AudioEnc::getDataType(void)
{
    StdWatcher::EDATA_TYPE dataType = StdWatcher::eDATA_TYPE_UTF8;
    EENCODE_TYPE encode_type = static_cast<EENCODE_TYPE>(ui->comboBoxAudioEncoder->currentIndex());

    switch(encode_type)
    {
    case eENCODE_TYPE_MP3:
        dataType = StdWatcher::eDATA_TYPE_LOCAL;
        break;
    default:
        break;
    }

    return dataType;
}

void AudioEnc::on_buttonAudioStart_clicked()
{
    QString input = ui->editAudioInput->text();
    QString output = ui->editAudioOutput->text();
    QString bitrate = ui->comboBoxAudioBitrate->currentText();

    if(input.isEmpty())
    {
        QMessageBox::warning(this, MESSAGE_WARNING, tr("Input file is empty!"), QMessageBox::Ok);
        return;
    }
    if(output.isEmpty())
    {
        QMessageBox::warning(this, MESSAGE_WARNING, tr("Output file is empty!"), QMessageBox::Ok);
        return;
    }
    if(qvs::isFile(output))
    {
        if(output == input)
        {
            QMessageBox::critical(this, MESSAGE_ARE_YOU_BAKA, tr("Output file can't be the same as source file!"), QMessageBox::Cancel);
            return;
        }

        int reply = QMessageBox::question(this, MESSAGE_QUESTION, tr("Output file already exists! Overwrite?"), QMessageBox::Yes | QMessageBox::Cancel);

        if(reply == QMessageBox::Cancel)
        {
            return;
        }
    }

    StdWatcherCmd job_cmd = getEncodeCmd(input, output, bitrate);

    QUuid uid = StdManager::createStdWatch();
    g_pStdWatch[uid]->show();
    g_pStdWatch[uid]->initJob(uid);
    g_pStdWatch[uid]->setDataType(getDataType());

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
    QString filename = QFileDialog::getOpenFileName(this, tr("Open Audio file"), NULLSTR, tr("Audio (*.*)"));

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
    ui->editAudioOutput->setText(getAudioOutputPath(static_cast<EENCODE_TYPE>(a_index), input));
}

void AudioEnc::on_comboBoxAudioEncoder_currentIndexChanged(int a_index)
{
    emit ui->comboBoxAudioEncoder->activated(a_index);

    bool bitrateMode = true;

    switch(static_cast<EENCODE_TYPE>(a_index))
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

    m_pAdvancedConfig->type = static_cast<uint>(a_index);
    saveCurrentAdvancedConfig();
}

void AudioEnc::on_comboBoxAudioBitrate_currentTextChanged(const QString &)
{
    saveCurrentAdvancedConfig();
}

void AudioEnc::saveCurrentAdvancedConfig(void)
{
    AudioAdvancedConfig config;

    config.setEnable(false);
    config.type = static_cast<uint>(ui->comboBoxAudioEncoder->currentIndex());
    config.value = ui->comboBoxAudioBitrate->currentText().toInt();
    config.value2 = NULLSTR;

    g_pConfig->setConfig(Config::eCONFIG_COMMON_ENCODING_AUDIO_CURRENT_PRESETS, qvs::getStringFromJson(g_pConfig->audioConfigToJson(config)).simplified());
}
