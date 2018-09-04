#include "audio_config.h"
#include "audio_enc.h"
#include "std_watcher.h"

#include "../mainwindow.h"
#include "../com/style_sheet.h"

#include "ui_mainwindow.h"
#include "ui_audio_config.h"
#include "ui_audio_enc.h"

#define QAAC_BITRATE_MAX (1280)   /* 0~1280 kbps */
#define QAAC_QUALITY_MAX (127)    /* 0~127 */
#define FDKAAC_BITRATE_MAX (320)  /* 0~320 kbps */
#define FDKAAC_QUALITY_MAX (5)    /* 1~5 */
#define NEROAAC_BITRATE_MAX (640) /* 16~640 kbps */
#define NEROAAC_QUALITY_MAX (100) /* 0.0~1.0 */
#define FLAC_QUALITY_MAX (8)      /* 0~8 */
#define OPUS_BITRATE_MAX (512)    /* 6~512 */
#define VORBIS_QUALITY_MAX (100)  /* -2.0~10.0 */
#define MP3_BITRATE_MAX (320)     /* 32~320, 8~320 */
#define MP3_QUALITY_MAX (9)       /* 0~9 */
#define AC3_BITRATE_MAX (640)     /* 64~640 */
#define NEROAAC_BITRATE_DIFF_MULTIPLIER (1000)

static const QString c_audio_config_bitrate = QObject::tr("Bitrate");
static const QString c_audio_config_quality = QObject::tr("Quality");
static const QString c_template_key_default = QObject::tr("<Default>");

AudioConfig::AudioConfig(QDialog *parent) :
    QDialog(parent),
    ui(new Ui::AudioConfig),
    m_advancedMode(false)
{
    ui->setupUi(this);
    this->setup();
}

AudioConfig::~AudioConfig()
{
    delete ui;
}

void AudioConfig::setup(void)
{
    ui->comboBoxTemplate->addItem(c_template_key_default);
    ui->comboBoxAacAppleMode->installEventFilter(this);
    this->installEventFilter(this);
    this->setStyleSheet(c_qss_slider_white_circle);

    emit ui->comboBoxAacAppleProfile->currentIndexChanged(ui->comboBoxAacAppleProfile->currentIndex());
}

AudioAdvancedConfig AudioConfig::creatDefaultConfig(const uint &a_type, const QVariant &a_value)
{
    AudioAdvancedConfig advanced_config;

    advanced_config.type = a_type;
    advanced_config.mode = (uint)NUL;
    advanced_config.profile = (uint)NUL;
    advanced_config.value = a_value;

    switch(static_cast<AudioEnc::EENCODE_TYPE>(a_type))
    {
    case AudioEnc::eENCODE_TYPE_AAC_APPLE:
    default:
        advanced_config.mode = (uint)eQAAC_MODE_LC_AAC_CBR;
        advanced_config.profile = (uint)eQAAC_PROFILE_LC_AAC;
        break;
    case AudioEnc::eENCODE_TYPE_AAC_FDK:
        advanced_config.mode = (uint)eFDKAAC_MODE_CBR;
        advanced_config.profile = (uint)eFDKAAC_PROFILE_MPEG_4_LC_AAC;
        break;
    case AudioEnc::eENCODE_TYPE_AAC_NERO:
        advanced_config.mode = (uint)eNEROAAC_MODE_ABR;
        advanced_config.profile = (uint)eNEROAAC_PROFILE_LC_AAC;
        break;
    case AudioEnc::eENCODE_TYPE_ALAC:
        break;
    case AudioEnc::eENCODE_TYPE_FLAC:
        advanced_config.value = (uint)eINDEX_5;
        break;
    case AudioEnc::eENCODE_TYPE_OPUS:
        advanced_config.mode = (uint)eOPUS_MODE_VBR;
        break;
    case AudioEnc::eENCODE_TYPE_OGG_VORBIS:
        advanced_config.value = (uint)(eINDEX_3 * eINDEX_100);
        break;
    case AudioEnc::eENCODE_TYPE_MP3:
        advanced_config.mode = (uint)eMP3_MODE_CBR;
        break;
    case AudioEnc::eENCODE_TYPE_AC3:
        break;
    case AudioEnc::eENCODE_TYPE_WAV:
        break;
    }
    return advanced_config;
}

void AudioConfig::setDefaultConfig(const uint &a_type, const AudioAdvancedConfig &advanced_config)
{
    switch(static_cast<AudioEnc::EENCODE_TYPE>(a_type))
    {
    case AudioEnc::eENCODE_TYPE_AAC_APPLE:
    default:
        break;
    case AudioEnc::eENCODE_TYPE_AAC_FDK:
        break;
    case AudioEnc::eENCODE_TYPE_AAC_NERO:
        break;
    case AudioEnc::eENCODE_TYPE_ALAC:
        break;
    case AudioEnc::eENCODE_TYPE_FLAC:
        break;
    case AudioEnc::eENCODE_TYPE_OPUS:
        break;
    case AudioEnc::eENCODE_TYPE_OGG_VORBIS:
        break;
    case AudioEnc::eENCODE_TYPE_MP3:
        break;
    case AudioEnc::eENCODE_TYPE_AC3:
        break;
    case AudioEnc::eENCODE_TYPE_WAV:
        break;
    }
}

void AudioConfig::on_comboBoxAudioEncoder_currentIndexChanged(int a_index)
{
    ui->stackedWidgetMode->setCurrentIndex(a_index);
}

void AudioConfig::on_checkBoxAdvancedOption_stateChanged(int a_state)
{
    switch(Qt::CheckState(a_state))
    {
    case Qt::Unchecked:
    default:
        m_advancedMode = false;
        break;
    case Qt::PartiallyChecked:
    case Qt::Checked:
        m_advancedMode = true;
        break;
    }
    ui->stackedWidgetMode->setEnabled(m_advancedMode);
}

void AudioConfig::setMode(bool a_advancedMode)
{
    Qt::CheckState state = Qt::PartiallyChecked;

    if(a_advancedMode)
    {
        state = Qt::Checked;
    }
    else
    {
        state = Qt::Unchecked;
    }

    ui->checkBoxAdvancedOption->setCheckState(state);
    if(state == ui->checkBoxAdvancedOption->checkState())
    {
        emit ui->checkBoxAdvancedOption->stateChanged((int)state);
    }
}

void AudioConfig::contextMenuEvent(QContextMenuEvent *e)
{
    e->accept();
#if 0
    QMenu *menu = new QMenu();
    QAction *action = menu->addAction("Edit value");

    connect(action, SIGNAL(triggered()), this, SLOT(slotEditValue()));
    menu->exec(QCursor::pos());
    delete menu;
#endif
}

bool AudioConfig::eventFilter(QObject *o, QEvent *e)
{
    if(e->type() == QEvent::Show)
    {
        if(o == ui->comboBoxAacAppleMode)
        {
            resizeEvent();
        }
        else if(o == this)
        {
            resizeEventMinimum();
        }
    }
    return false;
}

void AudioConfig::resizeEvent(QResizeEvent *e)
{
    /* Make Combo Box width the same.*/
    ui->comboBoxAudioEncoder->resize(ui->comboBoxTemplate->size().width(), ui->comboBoxAudioEncoder->size().height());
    ui->comboBoxAacAppleMode->resize(ui->comboBoxAacAppleProfile->size().width(), ui->comboBoxAacAppleMode->size().height());
    e->accept();
}

void AudioConfig::resizeEvent(void)
{
    resize(width() + eINDEX_1, height());
    resize(width() - eINDEX_1, height());
}

void AudioConfig::resizeEventMinimum(void)
{
    resize(minimumWidth() + eINDEX_1, minimumHeight());
    resize(minimumWidth(), minimumHeight());
}

///->QAAC_START

void AudioConfig::on_comboBoxAacAppleProfile_currentIndexChanged(int a_index)
{
    QStringList items;

    switch((EAUDIO_CONFIG_PROFILE)a_index)
    {
    case eQAAC_PROFILE_LC_AAC:
    default:
        ui->checkBoxAacAppleNoDelay->setEnabled(true);
        items << tr("True VBR") << tr("Constrained VBR") << tr("ABR") << tr("CBR");
        break;
    case eQAAC_PROFILE_HE_AAC:
        ui->checkBoxAacAppleNoDelay->setEnabled(false);
        items << tr("Constrained VBR") << tr("ABR") << tr("CBR");
        break;
    }
    ui->comboBoxAacAppleMode->clear();
    ui->comboBoxAacAppleMode->addItems(items);
}

void AudioConfig::on_comboBoxAacAppleMode_currentIndexChanged(int a_index)
{
    if( (ui->comboBoxAacAppleProfile->currentIndex() == (int)eQAAC_PROFILE_LC_AAC) && (a_index == (int)eQAAC_MODE_LC_AAC_TRUE_VBR) )
    {
        if(ui->horizontalSliderAacApple->maximum() != QAAC_QUALITY_MAX)
        {
            ui->horizontalSliderAacApple->setValue(ui->horizontalSliderAacApple->minimum());
        }
        ui->horizontalSliderAacApple->setMinimum((int)eINDEX_0);
        ui->horizontalSliderAacApple->setMaximum(QAAC_QUALITY_MAX);
    }
    else
    {
        if(ui->horizontalSliderAacApple->maximum() != QAAC_BITRATE_MAX)
        {
            ui->horizontalSliderAacApple->setValue(ui->horizontalSliderAacApple->minimum());
        }
        ui->horizontalSliderAacApple->setMinimum((int)eINDEX_0);
        ui->horizontalSliderAacApple->setMaximum(QAAC_BITRATE_MAX);
    }
    ui->horizontalSliderAacApple->setTickInterval(ui->horizontalSliderAacApple->maximum() / (int)eINDEX_10);
}

void AudioConfig::on_horizontalSliderAacApple_valueChanged(int a_value)
{
    QString mode = c_audio_config_bitrate;

    if( (ui->comboBoxAacAppleProfile->currentIndex() == (int)eQAAC_PROFILE_LC_AAC) && (ui->comboBoxAacAppleMode->currentIndex() == (int)eQAAC_MODE_LC_AAC_TRUE_VBR) )
    {
        mode = c_audio_config_quality;
    }
    ui->groupBoxAacApple->setTitle(QString("QAAC - (%1=%2)").arg(mode).arg(a_value));
}

///->QAAC_END

///->FDKAAC_START

void AudioConfig::on_comboBoxAacFdkMode_currentIndexChanged(int a_index)
{
    switch((EAUDIO_CONFIG_MODE)a_index)
    {
    case eFDKAAC_MODE_CBR:
    default:
        if(ui->horizontalSliderAacFdk->maximum() != FDKAAC_BITRATE_MAX)
        {
            ui->horizontalSliderAacFdk->setValue(ui->horizontalSliderAacFdk->minimum());
        }
        ui->horizontalSliderAacFdk->setMinimum((int)eINDEX_0);
        ui->horizontalSliderAacFdk->setMaximum(FDKAAC_BITRATE_MAX);
        ui->horizontalSliderAacFdk->setTickInterval(ui->horizontalSliderAacFdk->maximum() / (int)eINDEX_10);
        ui->horizontalSliderAacFdk->setPageStep((int)eINDEX_10);
        break;
    case eFDKAAC_MODE_VBR:
        if(ui->horizontalSliderAacFdk->maximum() != FDKAAC_QUALITY_MAX)
        {
            ui->horizontalSliderAacFdk->setValue((int)eINDEX_1);
        }
        ui->horizontalSliderAacFdk->setMinimum((int)eINDEX_1);
        ui->horizontalSliderAacFdk->setMaximum(FDKAAC_QUALITY_MAX);
        ui->horizontalSliderAacFdk->setTickInterval((int)eINDEX_1);
        ui->horizontalSliderAacFdk->setPageStep((int)eINDEX_1);
        break;
    }
}

void AudioConfig::on_horizontalSliderAacFdk_valueChanged(int a_value)
{
    QString mode = c_audio_config_bitrate;

    if(ui->comboBoxAacFdkMode->currentIndex() == (int)eFDKAAC_MODE_VBR)
    {
        mode = c_audio_config_quality;
    }
    ui->groupBoxAacFdk->setTitle(QString("FDKAAC - (%1=%2)").arg(mode).arg(a_value));
}

///->FDKAAC_END

///->NEROAAC_START

void AudioConfig::on_comboBoxAacNeroMode_currentIndexChanged(int a_index)
{
    switch((EAUDIO_CONFIG_MODE)a_index)
    {
    case eNEROAAC_MODE_ABR:
    case eNEROAAC_MODE_CBR:
    default:
        if(ui->horizontalSliderAacNero->maximum() != NEROAAC_BITRATE_MAX)
        {
            ui->horizontalSliderAacNero->setValue(ui->horizontalSliderAacNero->minimum());
        }
        ui->horizontalSliderAacNero->setMinimum((int)eINDEX_16);
        ui->horizontalSliderAacNero->setMaximum(NEROAAC_BITRATE_MAX);
        ui->horizontalSliderAacNero->setTickInterval(ui->horizontalSliderAacNero->maximum() / (int)eINDEX_10);
        ui->horizontalSliderAacNero->setPageStep((int)eINDEX_10);
        ui->labelAacNeroProfile->setEnabled(true);
        ui->comboBoxAacNeroProfile->setEnabled(true);
        break;
    case eNEROAAC_MODE_VBR:
        if(ui->horizontalSliderAacNero->maximum() != NEROAAC_QUALITY_MAX)
        {
            ui->horizontalSliderAacNero->setValue(ui->horizontalSliderAacNero->minimum());
        }
        ui->horizontalSliderAacNero->setMinimum((int)eINDEX_0);
        ui->horizontalSliderAacNero->setMaximum(NEROAAC_QUALITY_MAX);
        ui->horizontalSliderAacNero->setTickInterval((int)eINDEX_10);
        ui->horizontalSliderAacNero->setPageStep((int)eINDEX_1);
        ui->labelAacNeroProfile->setDisabled(true);
        ui->comboBoxAacNeroProfile->setDisabled(true);
        break;
    }
}

void AudioConfig::on_horizontalSliderAacNero_valueChanged(int a_value)
{
    QString mode = c_audio_config_bitrate;
    double value = a_value;

    if(ui->comboBoxAacNeroMode->currentIndex() == (int)eNEROAAC_MODE_VBR)
    {
        mode = c_audio_config_quality;
        value /= (int)eINDEX_100;
    }
    ui->groupBoxAacNero->setTitle(QString("NeroAAC - (%1=%2)").arg(mode).arg(value));
}

///->NEROAAC_END

///->FLAC_START

void AudioConfig::reloadFlac(void)
{
    ui->horizontalSliderFlac->setMinimum((int)eINDEX_0);
    ui->horizontalSliderFlac->setMaximum(FLAC_QUALITY_MAX);
    ui->horizontalSliderFlac->setTickInterval((int)eINDEX_1);
    ui->horizontalSliderFlac->setPageStep((int)eINDEX_1);
    ui->horizontalSliderFlac->setValue((int)eINDEX_5); /*Default*/
}

void AudioConfig::on_horizontalSliderFlac_valueChanged(int a_value)
{
    QString mode = c_audio_config_quality;

    ui->groupBoxFlac->setTitle(QString("FLAC - (%1=%2)").arg(mode).arg(a_value));
}

///->FLAC_END

///->OPUS_START

void AudioConfig::on_horizontalSliderOpus_valueChanged(int a_value)
{
    QString mode = c_audio_config_bitrate;

    ui->groupBoxOpus->setTitle(QString("OPUS - (%1=%2)").arg(mode).arg(a_value));
}

///->OPUS_END

///->OGG_VORBIS_START

void AudioConfig::on_horizontalSliderOggVorbis_valueChanged(int a_value)
{
    QString mode = c_audio_config_quality;
    double value = a_value;

    value /= (int)eINDEX_100;
    ui->groupBoxOggVorbis->setTitle(QString("Ogg Vorbis - (%1=%2)").arg(mode).arg(value));
}

///->OGG_VORBIS_END

///->MP3_START

void AudioConfig::on_comboBoxMp3Mode_currentIndexChanged(int a_index)
{
    switch((EAUDIO_CONFIG_MODE)a_index)
    {
    case eMP3_MODE_CBR:
    default:
        if(ui->horizontalSliderMp3->maximum() != MP3_BITRATE_MAX)
        {
            ui->horizontalSliderMp3->setValue((int)eINDEX_32);
        }
        ui->horizontalSliderMp3->setMinimum((int)eINDEX_32);
        ui->horizontalSliderMp3->setMaximum(MP3_BITRATE_MAX);
        ui->horizontalSliderMp3->setTickInterval((int)eINDEX_8);
        ui->horizontalSliderMp3->setPageStep((int)eINDEX_8);
        break;
    case eMP3_MODE_ABR:
        if(ui->horizontalSliderMp3->maximum() != MP3_BITRATE_MAX)
        {
            ui->horizontalSliderMp3->setValue((int)eINDEX_8);
        }
        ui->horizontalSliderMp3->setMinimum((int)eINDEX_8);
        ui->horizontalSliderMp3->setMaximum(MP3_BITRATE_MAX);
        ui->horizontalSliderMp3->setTickInterval((int)eINDEX_8);
        ui->horizontalSliderMp3->setPageStep((int)eINDEX_8);
        break;
    case eMP3_MODE_VBR:
        if(ui->horizontalSliderMp3->maximum() != MP3_QUALITY_MAX)
        {
            ui->horizontalSliderMp3->setValue((int)eINDEX_0);
        }
        ui->horizontalSliderMp3->setMinimum((int)eINDEX_0);
        ui->horizontalSliderMp3->setMaximum(MP3_QUALITY_MAX);
        ui->horizontalSliderMp3->setTickInterval((int)eINDEX_1);
        ui->horizontalSliderMp3->setPageStep((int)eINDEX_1);
        break;
    }
}

void AudioConfig::on_horizontalSliderMp3_valueChanged(int a_value)
{
    QString mode = c_audio_config_bitrate;

    if(ui->comboBoxMp3Mode->currentIndex() == (int)eMP3_MODE_VBR)
    {
        mode = c_audio_config_quality;
    }
    ui->groupBoxMp3->setTitle(QString("Lame MP3 - (%1=%2)").arg(mode).arg(a_value));
}

///->MP3_END

///->AC3_START

void AudioConfig::on_horizontalSliderAc3_valueChanged(int a_value)
{
    QString mode = c_audio_config_bitrate;

    ui->groupBoxAc3->setTitle(QString("AC3 - (%1=%2)").arg(mode).arg(a_value));
}

///->AC3_END

void AudioConfig::on_buttonCancel_clicked()
{
    this->reject();
}

void AudioConfig::on_buttonAccept_clicked()
{
    QString cmd;
    int index = ui->comboBoxAudioEncoder->currentIndex();

    switch(index)
    {
    case AudioEnc::eENCODE_TYPE_AAC_APPLE:
    default:
        cmd = processAccApple();
        break;
    case AudioEnc::eENCODE_TYPE_AAC_FDK:
        cmd = processAccFdk();
        break;
    case AudioEnc::eENCODE_TYPE_AAC_NERO:
        cmd = processAccNero();
        break;
    case AudioEnc::eENCODE_TYPE_ALAC:
        cmd = processAlac();
        break;
    case AudioEnc::eENCODE_TYPE_FLAC:
        cmd = processFlac();
        break;
    case AudioEnc::eENCODE_TYPE_OPUS:
        cmd = processOpus();
        break;
    case AudioEnc::eENCODE_TYPE_OGG_VORBIS:
        cmd = processOggVorbis();
        break;
    case AudioEnc::eENCODE_TYPE_MP3:
        cmd = processMp3();
        break;
    case AudioEnc::eENCODE_TYPE_AC3:
        cmd = processAc3();
        break;
    case AudioEnc::eENCODE_TYPE_WAV:
        cmd = processWav();
        break;
    }

    mainUi->m_pAudioEnc->ui->comboBoxAudioEncoder->setCurrentIndex(index);
    emit mainUi->m_pAudioEnc->ui->comboBoxAudioEncoder->currentIndexChanged(index);
    mainUi->m_pAudioEnc->setMode(m_advancedMode);
    mainUi->m_pAudioEnc->setModeCmd(cmd);
    this->accept();
}

QString AudioConfig::processAccApple(void)
{
    QString cmd;
    QByteArray exec = mainUi->m_com->findFirstFilePath(AUDIO_CONFIG_EXEC_AAC_APPLE).toUtf8();
    QByteArray delay = ui->checkBoxAacAppleNoDelay->isChecked() ? "--no-delay" : QT_EMPTY;
    EAUDIO_CONFIG_PROFILE profile = static_cast<EAUDIO_CONFIG_PROFILE>(ui->comboBoxAacAppleProfile->currentIndex());
    EAUDIO_CONFIG_MODE mode = static_cast<EAUDIO_CONFIG_MODE>(ui->comboBoxAacAppleMode->currentIndex());

    switch(profile)
    {
    case eQAAC_PROFILE_LC_AAC:
    default:
        if(mode == eQAAC_MODE_LC_AAC_TRUE_VBR) /* not variant value */
        {
            cmd.sprintf("%s --ignorelength --threading -V %d %s - -o \"%1\"", exec.data(), ui->horizontalSliderAacApple->value(), delay.data());
        }
        else if(mode == eQAAC_MODE_LC_AAC_CONSTRAINED_VBR)
        {
            cmd.sprintf("%s --ignorelength --threading -v %d %s - -o \"%1\"", exec.data(), ui->horizontalSliderAacApple->value(), delay.data());
        }
        else if(mode == eQAAC_MODE_LC_AAC_ABR)
        {
            cmd.sprintf("%s --ignorelength --threading -a %d %s - -o \"%1\"", exec.data(), ui->horizontalSliderAacApple->value(), delay.data());
        }
        else if(mode == eQAAC_MODE_LC_AAC_CBR)
        {
            cmd.sprintf("%s --ignorelength --threading -c %d %s - -o \"%1\"", exec.data(), ui->horizontalSliderAacApple->value(), delay.data());
        }
        break;
    case eQAAC_PROFILE_HE_AAC:
        if(mode == eQAAC_MODE_HE_AAC_CONSTRAINED_VBR)
        {
            cmd.sprintf("%s --ignorelength --threading -he -v %d - -o \"%1\"", exec.data(), ui->horizontalSliderAacApple->value());
        }
        else if(mode == eQAAC_MODE_HE_AAC_ABR)
        {
            cmd.sprintf("%s --ignorelength --threading -he -a %d - -o \"%1\"", exec.data(), ui->horizontalSliderAacApple->value());
        }
        else if(mode == eQAAC_MODE_HE_AAC_CBR)
        {
            cmd.sprintf("%s --ignorelength --threading -he -c %d - -o \"%1\"", exec.data(), ui->horizontalSliderAacApple->value());
        }
        break;
    }
    return cmd;
}

QString AudioConfig::processAccFdk(void)
{
    QString cmd;
    QByteArray exec = mainUi->m_com->findFirstFilePath(AUDIO_CONFIG_EXEC_AAC_FDK).toUtf8();
    EAUDIO_CONFIG_PROFILE profile = static_cast<EAUDIO_CONFIG_PROFILE>(ui->comboBoxAacFdkProfile->currentIndex());
    EAUDIO_CONFIG_MODE mode = static_cast<EAUDIO_CONFIG_MODE>(ui->comboBoxAacFdkMode->currentIndex());

    switch(profile)
    {
    case eFDKAAC_PROFILE_MPEG_4_LC_AAC:
        if(mode == eFDKAAC_MODE_CBR)
        {
            cmd.sprintf("%s --ignorelength -m 0 -b %d -p 2 - -o \"%1\"", exec.data(), ui->horizontalSliderAacFdk->value());
        }
        else if(mode == eFDKAAC_MODE_VBR)
        {
            cmd.sprintf("%s --ignorelength -m %d -p 2 - -o \"%1\"", exec.data(), ui->horizontalSliderAacFdk->value());
        }
        break;
    case eFDKAAC_PROFILE_MPEG_4_HE_AAC:
        if(mode == eFDKAAC_MODE_CBR)
        {
            cmd.sprintf("%s --ignorelength -m 0 -b %d -p 5 - -o \"%1\"", exec.data(), ui->horizontalSliderAacFdk->value());
        }
        else if(mode == eFDKAAC_MODE_VBR)
        {
            cmd.sprintf("%s --ignorelength -m %d -p 5 - -o \"%1\"", exec.data(), ui->horizontalSliderAacFdk->value());
        }
        break;
    case eFDKAAC_PROFILE_MPEG_4_HE_AAC_V2:
        if(mode == eFDKAAC_MODE_CBR)
        {
            cmd.sprintf("%s --ignorelength -m 0 -b %d -p 29 - -o \"%1\"", exec.data(), ui->horizontalSliderAacFdk->value());
        }
        else if(mode == eFDKAAC_MODE_VBR)
        {
            cmd.sprintf("%s --ignorelength -m %d -p 29 - -o \"%1\"", exec.data(), ui->horizontalSliderAacFdk->value());
        }
        break;
    case eFDKAAC_PROFILE_MPEG_4_AAC_LD:
        if(mode == eFDKAAC_MODE_CBR)
        {
            cmd.sprintf("%s --ignorelength -m 0 -b %d -p 23 - -o \"%1\"", exec.data(), ui->horizontalSliderAacFdk->value());
        }
        else if(mode == eFDKAAC_MODE_VBR)
        {
            cmd.sprintf("%s --ignorelength -m %d -p 23 - -o \"%1\"", exec.data(), ui->horizontalSliderAacFdk->value());
        }
        break;
    case eFDKAAC_PROFILE_MPEG_4_AAC_ELD:
        if(mode == eFDKAAC_MODE_CBR)
        {
            cmd.sprintf("%s --ignorelength -m 0 -b %d -p 39 - -o \"%1\"", exec.data(), ui->horizontalSliderAacFdk->value());
        }
        else if(mode == eFDKAAC_MODE_VBR)
        {
            cmd.sprintf("%s --ignorelength -m %d -p 39 - -o \"%1\"", exec.data(), ui->horizontalSliderAacFdk->value());
        }
        break;
    case eFDKAAC_PROFILE_MPEG_2_LC_AAC:
        if(mode == eFDKAAC_MODE_CBR)
        {
            cmd.sprintf("%s --ignorelength -m 0 -b %d -p 129 - -o \"%1\"", exec.data(), ui->horizontalSliderAacFdk->value());
        }
        else if(mode == eFDKAAC_MODE_VBR)
        {
            cmd.sprintf("%s --ignorelength -m %d -p 129 - -o \"%1\"", exec.data(), ui->horizontalSliderAacFdk->value());
        }
        break;
    case eFDKAAC_PROFILE_MPEG_2_HE_AAC:
        if(mode == eFDKAAC_MODE_CBR)
        {
            cmd.sprintf("%s --ignorelength -m 0 -b %d -p 132 - -o \"%1\"", exec.data(), ui->horizontalSliderAacFdk->value());
        }
        else if(mode == eFDKAAC_MODE_VBR)
        {
            cmd.sprintf("%s --ignorelength -m %d -p 132 - -o \"%1\"", exec.data(), ui->horizontalSliderAacFdk->value());
        }
        break;
    case eFDKAAC_PROFILE_MPEG_2_HE_AAC_V2:
        if(mode == eFDKAAC_MODE_CBR)
        {
            cmd.sprintf("%s --ignorelength -m 0 -b %d -p 156 - -o \"%1\"", exec.data(), ui->horizontalSliderAacFdk->value());
        }
        else if(mode == eFDKAAC_MODE_VBR)
        {
            cmd.sprintf("%s --ignorelength -m %d -p 156 - -o \"%1\"", exec.data(), ui->horizontalSliderAacFdk->value());
        }
        break;
    }
    return cmd;
}

QString AudioConfig::processAccNero(void)
{
    QString cmd;
    QByteArray exec = mainUi->m_com->findFirstFilePath(AUDIO_CONFIG_EXEC_AAC_NERO).toUtf8();
    EAUDIO_CONFIG_PROFILE profile = static_cast<EAUDIO_CONFIG_PROFILE>(ui->comboBoxAacNeroProfile->currentIndex());
    EAUDIO_CONFIG_MODE mode = static_cast<EAUDIO_CONFIG_MODE>(ui->comboBoxAacNeroMode->currentIndex());
    int value = ui->horizontalSliderAacNero->value();

    switch(mode)
    {
    case eNEROAAC_MODE_ABR:
    default:
        value *= NEROAAC_BITRATE_DIFF_MULTIPLIER;
        if(profile == eNEROAAC_PROFILE_AUTO)
        {
            cmd.sprintf("%s -ignorelength -br %d -if - -of \"%1\"", exec.data(), value);
        }
        else if(profile == eNEROAAC_PROFILE_HE_AAC_PS)
        {
            cmd.sprintf("%s -ignorelength -hev2 -br %d -if - -of \"%1\"", exec.data(), value);
        }
        else if(profile == eNEROAAC_PROFILE_HE_AAC)
        {
            cmd.sprintf("%s -ignorelength -he -br %d -if - -of \"%1\"", exec.data(), value);
        }
        else if(profile == eNEROAAC_PROFILE_LC_AAC)
        {
            cmd.sprintf("%s -ignorelength -lc -br %d -if - -of \"%1\"", exec.data(), value);
        }
        break;
    case eNEROAAC_MODE_CBR:
        value *= NEROAAC_BITRATE_DIFF_MULTIPLIER;
        if(profile == eNEROAAC_PROFILE_AUTO)
        {
            cmd.sprintf("%s -ignorelength -cbr %d -if - -of \"%1\"", exec.data(), value);
        }
        else if(profile == eNEROAAC_PROFILE_HE_AAC_PS)
        {
            cmd.sprintf("%s -ignorelength -hev2 -cbr %d -if - -of \"%1\"", exec.data(), value);
        }
        else if(profile == eNEROAAC_PROFILE_HE_AAC)
        {
            cmd.sprintf("%s -ignorelength -he -cbr %d -if - -of \"%1\"", exec.data(), value);
        }
        else if(profile == eNEROAAC_PROFILE_LC_AAC)
        {
            cmd.sprintf("%s -ignorelength -lc -cbr %d -if - -of \"%1\"", exec.data(), value);
        }
        break;
    case eNEROAAC_MODE_VBR:
        cmd.sprintf("%s -ignorelength -q %.2f -if - -of \"%1\"", exec.data(), (double)value / (int)eINDEX_100);
        break;
    }
    return cmd;
}

QString AudioConfig::processAlac(void)
{
    QString cmd;
    QByteArray exec = mainUi->m_com->findFirstFilePath(AUDIO_CONFIG_EXEC_ALAC).toUtf8();

    cmd.sprintf("%s --ignorelength - -o \"%1\"", exec.data());
    return cmd;
}

QString AudioConfig::processFlac(void)
{
    QString cmd;
    QByteArray exec = mainUi->m_com->findFirstFilePath(AUDIO_CONFIG_EXEC_FLAC).toUtf8();

    cmd.sprintf("%s -%d - -o \"%1\"", exec.data(), ui->horizontalSliderFlac->value());
    return cmd;
}

QString AudioConfig::processOpus(void)
{
    QString cmd;
    QByteArray exec = mainUi->m_com->findFirstFilePath(AUDIO_CONFIG_EXEC_OPUS).toUtf8();
    EAUDIO_CONFIG_MODE mode = static_cast<EAUDIO_CONFIG_MODE>(ui->comboBoxOpusMode->currentIndex());

    switch(mode)
    {
    case eOPUS_MODE_VBR:
    default:
        cmd.sprintf("%s --ignorelength --vbr --bitrate %d - \"%1\"", exec.data(), ui->horizontalSliderOpus->value());
        break;
    case eOPUS_MODE_CONSTRAINED_VBR:
        cmd.sprintf("%s --ignorelength --cvbr --bitrate %d - \"%1\"", exec.data(), ui->horizontalSliderOpus->value());
        break;
    case eOPUS_MODE_HARD_CBR:
        cmd.sprintf("%s --ignorelength --hard-cbr --bitrate %d - \"%1\"", exec.data(), ui->horizontalSliderOpus->value());
        break;
    }
    return cmd;
}

QString AudioConfig::processOggVorbis(void)
{
    QString cmd;
    QByteArray exec = mainUi->m_com->findFirstFilePath(AUDIO_CONFIG_EXEC_OGG_VORBIS).toUtf8();

    /* not support for bitrate mode in advanced config */
    cmd.sprintf("%s - --ignorelength --quality %.2fk -o \"%1\"", exec.data(), ui->horizontalSliderOggVorbis->value() / (double)eINDEX_100);
    return cmd;
}

QString AudioConfig::processMp3(void)
{
    QString cmd;
    QByteArray exec = mainUi->m_com->findFirstFilePath(AUDIO_CONFIG_EXEC_MP3).toUtf8();
    EAUDIO_CONFIG_MODE mode = static_cast<EAUDIO_CONFIG_MODE>(ui->comboBoxMp3Mode->currentIndex());
    int value = ui->horizontalSliderMp3->value();

    switch(mode)
    {
    case eMP3_MODE_CBR:
    default:
        cmd.sprintf("%s -b %d --cbr -h - \"%1\"", exec.data(), value);
        break;
    case eMP3_MODE_ABR:
        cmd.sprintf("%s --abr %d -h - \"%1\"", exec.data(), value);
        break;
    case eMP3_MODE_VBR:
        cmd.sprintf("%s -V%d - \"%1\"", exec.data(), value);
        break;
    }
    return cmd;
}

QString AudioConfig::processAc3(void)
{
    QString cmd;

    cmd.sprintf("%1 -i \"%2\" -c:a ac3 -b:a %dk \"%3\" -y", ui->horizontalSliderAc3->value());
    return cmd;
}

QString AudioConfig::processWav(void)
{
    QString cmd;

    /* no config */
    return cmd;
}

