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

const QList<QPair<AudioAdvancedConfig::ECONFIG, QString>> c_list_config_encode_audio = {
    { AudioAdvancedConfig::eCONFIG_ADVANCED, "Advanced" },
    { AudioAdvancedConfig::eCONFIG_TYPE, "Type" },
    { AudioAdvancedConfig::eCONFIG_MODE, "Mode" },
    { AudioAdvancedConfig::eCONFIG_PROFILE, "Profile" },
    { AudioAdvancedConfig::eCONFIG_VALUE, "Value" },
    { AudioAdvancedConfig::eCONFIG_VALUE2, "Value2" },
};

AudioConfig::AudioConfig(QDialog *parent) :
    QDialog(parent),
    ui(new Ui::AudioConfig),
    m_advancedMode(false),
    m_pSpinBox(new QDoubleSpinBox(this)),
    m_pTimerValueHidden(new QTimer(this))
{
    ui->setupUi(this);
    this->setup();
}

AudioConfig::~AudioConfig()
{
    delete m_pTimerValueHidden;
    delete m_pSpinBox;
    delete ui;
}

void AudioConfig::setup(void)
{
    this->setupUi();
    this->setValueHidden();
    this->installEventFilter(this);
    this->setStyleSheet(c_qss_slider_white_circle);
    this->loadConfig();

    m_pTimerValueHidden->connect(m_pTimerValueHidden, SIGNAL(timeout()), this, SLOT(setValueHidden()));
    m_pTimerValueHidden->setInterval(eINDEX_100);
    m_pTimerValueHidden->setSingleShot(true);

    ui->comboBoxAacAppleMode->installEventFilter(this);
    m_pSpinBox->installEventFilter(this);
    m_pSpinBox->raise();
    m_pSpinBox->setStyleSheet(c_qss_spin_box_background_alpha_half);
    m_pSpinBox->connect(m_pSpinBox, SIGNAL(valueChanged(double)), this, SLOT(valueChanged(double)));
}

void AudioConfig::setupUi(void)
{
    /* Group: AAC(APPLE) */
    emit ui->comboBoxAacAppleProfile->currentIndexChanged(ui->comboBoxAacAppleProfile->currentIndex());
    emit ui->comboBoxAacAppleMode->currentIndexChanged(ui->comboBoxAacAppleMode->currentIndex());

    /* Group: AAC(FDK) */
    emit ui->comboBoxAacFdkMode->currentIndexChanged(ui->comboBoxAacFdkMode->currentIndex());
    emit ui->comboBoxAacFdkProfile->currentIndexChanged(ui->comboBoxAacFdkProfile->currentIndex());

    /* Group: AAC(NERO) */
    emit ui->comboBoxAacNeroMode->currentIndexChanged(ui->comboBoxAacNeroMode->currentIndex());
    emit ui->comboBoxAacNeroProfile->currentIndexChanged(ui->comboBoxAacNeroProfile->currentIndex());

    /* Group: ALAC */
    PASS;

    /* Group: FLAC */
    ui->horizontalSliderFlac->setMinimum(eINDEX_0);
    ui->horizontalSliderFlac->setMaximum(FLAC_QUALITY_MAX);
    ui->horizontalSliderFlac->setTickInterval(eINDEX_1);
    ui->horizontalSliderFlac->setPageStep(eINDEX_1);

    /* Group: OPUS */
    emit ui->comboBoxOpusMode->currentIndexChanged(ui->comboBoxOpusMode->currentIndex());

    /* Group: OGG_VORBIS */
    PASS;

    /* Group: MP3 */
    emit ui->comboBoxMp3Mode->currentIndexChanged(ui->comboBoxMp3Mode->currentIndex());

    /* Group: AC3 */
    PASS;

    /* Group: WAV */
    PASS;

    static const QList<QPair<AudioEnc::EENCODE_TYPE, QVariant>> s_config_default_value = {
        { AudioEnc::eENCODE_TYPE_AAC_APPLE,  DEFAULT_BITRATE },
        { AudioEnc::eENCODE_TYPE_AAC_FDK,    DEFAULT_BITRATE },
        { AudioEnc::eENCODE_TYPE_AAC_NERO,   DEFAULT_BITRATE },
        { AudioEnc::eENCODE_TYPE_ALAC,       QVariant()      },
        { AudioEnc::eENCODE_TYPE_FLAC,       eINDEX_5        },
        { AudioEnc::eENCODE_TYPE_OPUS,       DEFAULT_BITRATE },
        { AudioEnc::eENCODE_TYPE_OGG_VORBIS, eINDEX_100      },
        { AudioEnc::eENCODE_TYPE_MP3,        DEFAULT_BITRATE },
        { AudioEnc::eENCODE_TYPE_AC3,        DEFAULT_BITRATE },
        { AudioEnc::eENCODE_TYPE_WAV,        QVariant()      },
    };
    for(uint i = eINDEX_0; i < AudioEnc::eENCODER_MAX; i++)
    {
        setDefaultConfig(getDefaultConfig(i, s_config_default_value.at(static_cast<int>(i)).second));
    }

    s_value_sliders = {
        ui->horizontalSliderAacApple,    /* eENCODE_TYPE_AAC_APPLE */
        ui->horizontalSliderAacFdk,      /* eENCODE_TYPE_AAC_FDK */
        ui->horizontalSliderAacNero,     /* eENCODE_TYPE_AAC_NERO */
        nullptr,                         /* eENCODE_TYPE_ALAC */
        ui->horizontalSliderFlac,        /* eENCODE_TYPE_FLAC */
        ui->horizontalSliderOpus,        /* eENCODE_TYPE_OPUS */
        ui->horizontalSliderOggVorbis,   /* eENCODE_TYPE_OGG_VORBIS */
        ui->horizontalSliderMp3,         /* eENCODE_TYPE_MP3 */
        ui->horizontalSliderAc3,         /* eENCODE_TYPE_AC3 */
        nullptr,                         /* eENCODE_TYPE_WAV */
    };
    for(int i = eINDEX_0; i < s_value_sliders.length(); i++)
    {
        if(s_value_sliders[i] != nullptr)
        {
            s_value_sliders[i]->installEventFilter(this);
            s_value_sliders[i]->connect(static_cast<QSlider *>(s_value_sliders[i]), SIGNAL(valueChanged(int)), this, SLOT(setValueValue()));
        }
    }
}

void AudioConfig::loadConfig(void)
{
    ui->comboBoxTemplate->addItem(c_template_key_default);
    ui->comboBoxTemplate->addItems(getTemplateKeys());
}

AudioAdvancedConfig AudioConfig::getDefaultConfig(const uint &a_type, const QVariant &a_value)
{
    AudioAdvancedConfig advanced_config;

    advanced_config.type = a_type;
    advanced_config.mode = static_cast<uint>(NUL);
    advanced_config.profile = static_cast<uint>(NUL);
    advanced_config.value = a_value;

    switch(static_cast<AudioEnc::EENCODE_TYPE>(a_type))
    {
    case AudioEnc::eENCODE_TYPE_AAC_APPLE:
    default:
        advanced_config.mode = static_cast<uint>(eQAAC_MODE_LC_AAC_CBR);
        advanced_config.profile = static_cast<uint>(eQAAC_PROFILE_LC_AAC);
        advanced_config.value2 = false; /* No delay flag (default: true) */
        break;
    case AudioEnc::eENCODE_TYPE_AAC_FDK:
        advanced_config.mode = static_cast<uint>(eFDKAAC_MODE_CBR);
        advanced_config.profile = static_cast<uint>(eFDKAAC_PROFILE_MPEG_4_LC_AAC);
        break;
    case AudioEnc::eENCODE_TYPE_AAC_NERO:
        advanced_config.mode = static_cast<uint>(eNEROAAC_MODE_ABR);
        advanced_config.profile = static_cast<uint>(eNEROAAC_PROFILE_LC_AAC);
        break;
    case AudioEnc::eENCODE_TYPE_ALAC:
        break;
    case AudioEnc::eENCODE_TYPE_FLAC:
        advanced_config.value = static_cast<uint>(eINDEX_5);
        break;
    case AudioEnc::eENCODE_TYPE_OPUS:
        advanced_config.mode = static_cast<uint>(eOPUS_MODE_VBR);
        break;
    case AudioEnc::eENCODE_TYPE_OGG_VORBIS:
        advanced_config.value = static_cast<uint>(eINDEX_3 * eINDEX_100);
        break;
    case AudioEnc::eENCODE_TYPE_MP3:
        advanced_config.mode = static_cast<uint>(eMP3_MODE_CBR);
        break;
    case AudioEnc::eENCODE_TYPE_AC3:
        break;
    case AudioEnc::eENCODE_TYPE_WAV:
        break;
    }
    return advanced_config;
}

void AudioConfig::setDefaultConfig(const AudioAdvancedConfig &advanced_config)
{
    uint type = advanced_config.type;
    int mode = static_cast<int>(advanced_config.mode);
    int profile = static_cast<int>(advanced_config.profile);
    int value = advanced_config.value.toInt();

    switch(static_cast<AudioEnc::EENCODE_TYPE>(type))
    {
    case AudioEnc::eENCODE_TYPE_AAC_APPLE:
    default:
        ui->comboBoxAacAppleMode->setCurrentIndex(mode);
        ui->comboBoxAacAppleProfile->setCurrentIndex(profile);
        ui->horizontalSliderAacApple->setValue(value);
        break;
    case AudioEnc::eENCODE_TYPE_AAC_FDK:
        ui->comboBoxAacFdkMode->setCurrentIndex(mode);
        ui->comboBoxAacFdkProfile->setCurrentIndex(profile);
        ui->horizontalSliderAacFdk->setValue(value);
        break;
    case AudioEnc::eENCODE_TYPE_AAC_NERO:
        ui->comboBoxAacNeroMode->setCurrentIndex(mode);
        ui->comboBoxAacNeroProfile->setCurrentIndex(profile);
        ui->horizontalSliderAacNero->setValue(value);
        break;
    case AudioEnc::eENCODE_TYPE_ALAC:
        break;
    case AudioEnc::eENCODE_TYPE_FLAC:
        ui->horizontalSliderFlac->setValue(value);
        break;
    case AudioEnc::eENCODE_TYPE_OPUS:
        ui->comboBoxOpusMode->setCurrentIndex(mode);
        ui->horizontalSliderOpus->setValue(value);
        break;
    case AudioEnc::eENCODE_TYPE_OGG_VORBIS:
        ui->horizontalSliderOggVorbis->setValue(value);
        break;
    case AudioEnc::eENCODE_TYPE_MP3:
        ui->comboBoxMp3Mode->setCurrentIndex(mode);
        ui->horizontalSliderMp3->setValue(value);
        break;
    case AudioEnc::eENCODE_TYPE_AC3:
        ui->horizontalSliderAc3->setValue(value);
        break;
    case AudioEnc::eENCODE_TYPE_WAV:
        break;
    }
}

void AudioConfig::setDefaultConfig(const uint &a_type, const QVariant &a_value)
{
    setDefaultConfig(getDefaultConfig(a_type, a_value));
}

void AudioConfig::reloadConfig(const QString &a_key)
{
    AudioAdvancedConfig advanced_config;

    if(a_key == c_template_key_default)
    {
        advanced_config = getDefaultConfig();
    }
    else
    {
        advanced_config = g_pConfig->getConfigAudioEncodeTemplate(a_key);
    }

    setConfig(advanced_config);
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
        emit ui->checkBoxAdvancedOption->stateChanged(static_cast<int>(state));
    }

    m_advancedMode = a_advancedMode;
}

bool AudioConfig::eventFilter(QObject *o, QEvent *e)
{
    switch(e->type())
    {
    case QEvent::Show:
        if(o == ui->comboBoxAacAppleMode)
        {
            resizeEvent();
        }
        else if(o == this)
        {
            resizeEventMinimum();
        }
        break;
    case QEvent::Enter:
        if(containsValue(o))
        {
            if(m_advancedMode)
            {
                if(o != m_pSpinBox)
                {
                    this->moveValue();
                }
                this->setValueVisible(true);
            }
        }
        break;
    case QEvent::Leave:
        if(containsValue(o))
        {
            this->setValueVisible(false);
        }
        break;
    default:
        break;
    }
    return false;
}

bool AudioConfig::containsValue(QObject *a_object)
{
    if(a_object == m_pSpinBox)
    {
        return true;
    }

    for(int i = eINDEX_0; i < s_value_sliders.length(); i++)
    {
        if(s_value_sliders[i] != nullptr)
        {
            if(s_value_sliders[i] == a_object)
            {
                return true;
            }
        }
    }
    return false;
}

void AudioConfig::setValueHidden(void)
{
    m_pSpinBox->setVisible(false);
}

void AudioConfig::moveValue(void)
{
    int type = ui->comboBoxAudioEncoder->currentIndex();
    int x = QCursor::pos().x() - pos().x() - m_pSpinBox->width() / eINDEX_2 + eINDEX_5;
    int y = s_value_sliders[type]->y() + s_value_sliders[type]->height() + ui->stackedWidgetMode->y();

    if(x + m_pSpinBox->width() > this->width())
    {
        x = this->width() - m_pSpinBox->width() - eINDEX_2;
    }
    else if(x < eINDEX_0)
    {
        x = eINDEX_2;
    }
    m_pSpinBox->move(x, y);
}

void AudioConfig::setValueValue(void)
{
    /* From Signal: Slider valueChanged(int) */
    int type = ui->comboBoxAudioEncoder->currentIndex();
    QSlider *at_pSlider = static_cast<QSlider *>(s_value_sliders[type]);
    int decimals = eINDEX_0;
    double minimum = at_pSlider->minimum();
    double maximum = at_pSlider->maximum();
    double value = at_pSlider->value();
    double singleStep = at_pSlider->singleStep();

    switch(static_cast<AudioEnc::EENCODE_TYPE>(type))
    {
    case AudioEnc::eENCODE_TYPE_AAC_APPLE:
    case AudioEnc::eENCODE_TYPE_AAC_FDK:
    case AudioEnc::eENCODE_TYPE_ALAC:
    case AudioEnc::eENCODE_TYPE_FLAC:
    case AudioEnc::eENCODE_TYPE_OPUS:
    case AudioEnc::eENCODE_TYPE_MP3:
    case AudioEnc::eENCODE_TYPE_AC3:
    case AudioEnc::eENCODE_TYPE_WAV:
    default:
        break;
    case AudioEnc::eENCODE_TYPE_AAC_NERO:
        if(ui->comboBoxAacNeroMode->currentIndex() == static_cast<int>(eNEROAAC_MODE_VBR))
        {
            decimals = eINDEX_2;
            minimum /= eINDEX_100;
            maximum /= eINDEX_100;
            singleStep /= eINDEX_100;
            value /= eINDEX_100;
        }
        break;
    case AudioEnc::eENCODE_TYPE_OGG_VORBIS:
        decimals = eINDEX_2;
        minimum /= eINDEX_100;
        maximum /= eINDEX_100;
        singleStep /= eINDEX_100;
        value /= eINDEX_100;
        break;
    }

    m_pSpinBox->setDecimals(decimals);
    m_pSpinBox->setMinimum(minimum);
    m_pSpinBox->setMaximum(maximum);
    m_pSpinBox->setSingleStep(singleStep);

    at_pSlider->disconnect(at_pSlider, SIGNAL(valueChanged(int)), this, SLOT(setValueValue()));

    m_pSpinBox->setValue(value);

    at_pSlider->connect(at_pSlider, SIGNAL(valueChanged(int)), this, SLOT(setValueValue()));
}

void AudioConfig::setValueVisible(const bool &a_visible)
{
    if(a_visible)
    {
        if(m_pTimerValueHidden->isActive())
        {
            m_pTimerValueHidden->stop();
        }
        setValueValue();
        m_pSpinBox->setVisible(true);
    }
    else
    {
        m_pTimerValueHidden->start();
    }
}

void AudioConfig::valueChanged(double a_value)
{
    /* From Signal: DoubleSpinBox valueChanged(double) */
    double value = a_value;

    switch(static_cast<AudioEnc::EENCODE_TYPE>(ui->comboBoxAudioEncoder->currentIndex()))
    {
    case AudioEnc::eENCODE_TYPE_AAC_NERO:
        if(ui->comboBoxAacNeroMode->currentIndex() == static_cast<int>(eNEROAAC_MODE_VBR))
        {
            value *= eINDEX_100;
        }
        break;
    case AudioEnc::eENCODE_TYPE_OGG_VORBIS:
        value *= eINDEX_100;
        break;
    default:
        break;
    }

    m_pSpinBox->disconnect(m_pSpinBox, SIGNAL(valueChanged(double)), this, SLOT(valueChanged(double)));

    static_cast<QSlider *>(s_value_sliders[ui->comboBoxAudioEncoder->currentIndex()])->setValue(static_cast<int>(value));

    m_pSpinBox->connect(m_pSpinBox, SIGNAL(valueChanged(double)), this, SLOT(valueChanged(double)));
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

    switch(static_cast<EAUDIO_CONFIG_PROFILE>(a_index))
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
    if( (ui->comboBoxAacAppleProfile->currentIndex() == static_cast<int>(eQAAC_PROFILE_LC_AAC)) && (a_index == static_cast<int>(eQAAC_MODE_LC_AAC_TRUE_VBR)) )
    {
        fitValue(ui->horizontalSliderAacApple, QAAC_QUALITY_MAX);
    }
    else
    {
        fitValue(ui->horizontalSliderAacApple, QAAC_BITRATE_MAX);
    }
    ui->horizontalSliderAacApple->setTickInterval(ui->horizontalSliderAacApple->maximum() / eINDEX_10);
}

void AudioConfig::on_horizontalSliderAacApple_valueChanged(int a_value)
{
    QString mode = c_audio_config_bitrate;

    if( (ui->comboBoxAacAppleProfile->currentIndex() == static_cast<int>(eQAAC_PROFILE_LC_AAC)) && (ui->comboBoxAacAppleMode->currentIndex() == static_cast<int>(eQAAC_MODE_LC_AAC_TRUE_VBR)) )
    {
        mode = c_audio_config_quality;
    }
    ui->groupBoxAacApple->setTitle(QString("QAAC (%1=%2)").arg(mode).arg(a_value));
}

///->QAAC_END

///->FDKAAC_START

void AudioConfig::on_comboBoxAacFdkMode_currentIndexChanged(int a_index)
{
    switch(static_cast<EAUDIO_CONFIG_MODE>(a_index))
    {
    case eFDKAAC_MODE_CBR:
    default:
        fitValue(ui->horizontalSliderAacFdk, FDKAAC_BITRATE_MAX);
        ui->horizontalSliderAacFdk->setTickInterval(ui->horizontalSliderAacFdk->maximum() / eINDEX_10);
        ui->horizontalSliderAacFdk->setPageStep(eINDEX_10);
        break;
    case eFDKAAC_MODE_VBR:
        fitValue(ui->horizontalSliderAacFdk, FDKAAC_QUALITY_MAX);
        ui->horizontalSliderAacFdk->setTickInterval(eINDEX_1);
        ui->horizontalSliderAacFdk->setPageStep(eINDEX_1);
        break;
    }
}

void AudioConfig::on_horizontalSliderAacFdk_valueChanged(int a_value)
{
    QString mode = c_audio_config_bitrate;

    if(ui->comboBoxAacFdkMode->currentIndex() == static_cast<int>(eFDKAAC_MODE_VBR))
    {
        mode = c_audio_config_quality;
    }
    ui->groupBoxAacFdk->setTitle(QString("FDKAAC (%1=%2)").arg(mode).arg(a_value));
}

///->FDKAAC_END

///->NEROAAC_START

void AudioConfig::on_comboBoxAacNeroMode_currentIndexChanged(int a_index)
{
    switch(static_cast<EAUDIO_CONFIG_MODE>(a_index))
    {
    case eNEROAAC_MODE_ABR:
    case eNEROAAC_MODE_CBR:
    default:
        fitValue(ui->horizontalSliderAacNero, NEROAAC_BITRATE_MAX, eINDEX_16);
        ui->horizontalSliderAacNero->setTickInterval(ui->horizontalSliderAacNero->maximum() / eINDEX_10);
        ui->horizontalSliderAacNero->setPageStep(eINDEX_10);
        ui->labelAacNeroProfile->setEnabled(true);
        ui->comboBoxAacNeroProfile->setEnabled(true);
        break;
    case eNEROAAC_MODE_VBR:
        fitValue(ui->horizontalSliderAacNero, NEROAAC_QUALITY_MAX, eINDEX_0);
        ui->horizontalSliderAacNero->setTickInterval(eINDEX_10);
        ui->horizontalSliderAacNero->setPageStep(eINDEX_1);
        ui->labelAacNeroProfile->setDisabled(true);
        ui->comboBoxAacNeroProfile->setDisabled(true);
        break;
    }
}

void AudioConfig::on_horizontalSliderAacNero_valueChanged(int a_value)
{
    QString mode = c_audio_config_bitrate;
    double value = a_value;

    if(ui->comboBoxAacNeroMode->currentIndex() == static_cast<int>(eNEROAAC_MODE_VBR))
    {
        mode = c_audio_config_quality;
        value /= eINDEX_100;
    }
    ui->groupBoxAacNero->setTitle(QString("NeroAAC (%1=%2)").arg(mode).arg(value));
}

///->NEROAAC_END

///->FLAC_START

void AudioConfig::on_horizontalSliderFlac_valueChanged(int a_value)
{
    QString mode = c_audio_config_quality;

    ui->groupBoxFlac->setTitle(QString("FLAC (%1=%2)").arg(mode).arg(a_value));
}

///->FLAC_END

///->OPUS_START

void AudioConfig::on_horizontalSliderOpus_valueChanged(int a_value)
{
    QString mode = c_audio_config_bitrate;

    ui->groupBoxOpus->setTitle(QString("OPUS (%1=%2)").arg(mode).arg(a_value));
}

///->OPUS_END

///->OGG_VORBIS_START

void AudioConfig::on_horizontalSliderOggVorbis_valueChanged(int a_value)
{
    QString mode = c_audio_config_quality;
    double value = a_value;

    value /= eINDEX_100;
    ui->groupBoxOggVorbis->setTitle(QString("Ogg Vorbis (%1=%2)").arg(mode).arg(value));
}

///->OGG_VORBIS_END

///->MP3_START

void AudioConfig::on_comboBoxMp3Mode_currentIndexChanged(int a_index)
{
    switch(static_cast<EAUDIO_CONFIG_MODE>(a_index))
    {
    case eMP3_MODE_CBR:
    default:
        fitValue(ui->horizontalSliderMp3, MP3_BITRATE_MAX, eINDEX_32);
        ui->horizontalSliderMp3->setTickInterval(eINDEX_8);
        ui->horizontalSliderMp3->setPageStep(eINDEX_8);
        break;
    case eMP3_MODE_ABR:
        fitValue(ui->horizontalSliderMp3, MP3_BITRATE_MAX, eINDEX_8);
        ui->horizontalSliderMp3->setTickInterval(eINDEX_8);
        ui->horizontalSliderMp3->setPageStep(eINDEX_8);
        break;
    case eMP3_MODE_VBR:
        fitValue(ui->horizontalSliderMp3, MP3_QUALITY_MAX, eINDEX_0);
        ui->horizontalSliderMp3->setTickInterval(eINDEX_1);
        ui->horizontalSliderMp3->setPageStep(eINDEX_1);
        break;
    }
}

void AudioConfig::on_horizontalSliderMp3_valueChanged(int a_value)
{
    QString mode = c_audio_config_bitrate;

    if(ui->comboBoxMp3Mode->currentIndex() == static_cast<int>(eMP3_MODE_VBR))
    {
        mode = c_audio_config_quality;
    }
    ui->groupBoxMp3->setTitle(QString("Lame MP3 (%1=%2)").arg(mode).arg(a_value));
}

///->MP3_END

///->AC3_START

void AudioConfig::on_horizontalSliderAc3_valueChanged(int a_value)
{
    QString mode = c_audio_config_bitrate;

    ui->groupBoxAc3->setTitle(QString("AC3 (%1=%2)").arg(mode).arg(a_value));
}

///->AC3_END

void AudioConfig::on_buttonCancel_clicked()
{
    this->reject();
}

void AudioConfig::on_buttonAccept_clicked()
{
    AudioAdvancedConfig config = getConfig();

    mainUi->ui->widgetAudioEnc->ui->comboBoxAudioEncoder->setCurrentIndex(static_cast<int>(config.type));
    emit mainUi->ui->widgetAudioEnc->ui->comboBoxAudioEncoder->currentIndexChanged(static_cast<int>(config.type));

    mainUi->ui->widgetAudioEnc->setConfig(config);
    this->accept();
}

AudioAdvancedConfig AudioConfig::getConfig(void)
{
    AudioAdvancedConfig config;

    config.setEnable(m_advancedMode);
    config.type = static_cast<uint>(ui->comboBoxAudioEncoder->currentIndex());

    switch(static_cast<AudioEnc::EENCODE_TYPE>(config.type))
    {
    case AudioEnc::eENCODE_TYPE_AAC_APPLE:
    default:
        config.name = ui->groupBoxAacApple->title();
        config.cmd = processAccApple();
        config.mode = static_cast<uint>(ui->comboBoxAacAppleMode->currentIndex());
        config.profile = static_cast<uint>(ui->comboBoxAacAppleProfile->currentIndex());
        config.value = ui->horizontalSliderAacApple->value();
        config.value2 = ui->checkBoxAacAppleNoDelay->isChecked();
        break;
    case AudioEnc::eENCODE_TYPE_AAC_FDK:
        config.name = ui->groupBoxAacFdk->title();
        config.cmd = processAccFdk();
        config.mode = static_cast<uint>(ui->comboBoxAacFdkMode->currentIndex());
        config.profile = static_cast<uint>(ui->comboBoxAacFdkProfile->currentIndex());
        config.value = ui->horizontalSliderAacFdk->value();
        break;
    case AudioEnc::eENCODE_TYPE_AAC_NERO:
        config.name = ui->groupBoxAacNero->title();
        config.cmd = processAccNero();
        config.mode = static_cast<uint>(ui->comboBoxAacNeroMode->currentIndex());
        config.profile = static_cast<uint>(ui->comboBoxAacNeroProfile->currentIndex());
        config.value = ui->horizontalSliderAacNero->value();
        break;
    case AudioEnc::eENCODE_TYPE_ALAC:
        config.name = ui->groupBoxAlac->title();
        config.cmd = processAlac();
        break;
    case AudioEnc::eENCODE_TYPE_FLAC:
        config.name = ui->groupBoxFlac->title();
        config.cmd = processFlac();
        config.value = ui->horizontalSliderFlac->value();
        break;
    case AudioEnc::eENCODE_TYPE_OPUS:
        config.name = ui->groupBoxOpus->title();
        config.cmd = processOpus();
        config.mode = static_cast<uint>(ui->comboBoxOpusMode->currentIndex());
        config.value = ui->horizontalSliderOpus->value();
        break;
    case AudioEnc::eENCODE_TYPE_OGG_VORBIS:
        config.name = ui->groupBoxOggVorbis->title();
        config.cmd = processOggVorbis();
        config.value = ui->horizontalSliderOggVorbis->value();
        break;
    case AudioEnc::eENCODE_TYPE_MP3:
        config.name = ui->groupBoxMp3->title();
        config.cmd = processMp3();
        config.mode = static_cast<uint>(ui->comboBoxMp3Mode->currentIndex());
        config.value = ui->horizontalSliderMp3->value();
        break;
    case AudioEnc::eENCODE_TYPE_AC3:
        config.name = ui->groupBoxAc3->title();
        config.cmd = processAc3();
        config.value = ui->horizontalSliderAc3->value();
        break;
    case AudioEnc::eENCODE_TYPE_WAV:
        config.name = ui->groupBoxWav->title();
        config.cmd = processWav();
        break;
    }
    return config;
}

void AudioConfig::setConfig(AudioAdvancedConfig *a_pAdvancedConfig)
{
    setMode(a_pAdvancedConfig->isEnable());

    AudioAdvancedConfig at_advancedConfig;

    ui->comboBoxAudioEncoder->setCurrentIndex(static_cast<int>(a_pAdvancedConfig->type));
    emit ui->comboBoxAudioEncoder->currentIndexChanged(static_cast<int>(a_pAdvancedConfig->type));

    if(!m_advancedMode)
    {
        at_advancedConfig = getDefaultConfig(static_cast<uint>(a_pAdvancedConfig->type));
        a_pAdvancedConfig = &at_advancedConfig;
    }

    switch(static_cast<AudioEnc::EENCODE_TYPE>(a_pAdvancedConfig->type))
    {
    case AudioEnc::eENCODE_TYPE_AAC_APPLE:
    default:
        ui->comboBoxAacAppleMode->setCurrentIndex(static_cast<int>(a_pAdvancedConfig->mode));
        ui->comboBoxAacAppleProfile->setCurrentIndex(static_cast<int>(a_pAdvancedConfig->profile));
        ui->horizontalSliderAacApple->setValue(a_pAdvancedConfig->value.toInt());
        ui->checkBoxAacAppleNoDelay->setChecked(a_pAdvancedConfig->value2.toBool());
        break;
    case AudioEnc::eENCODE_TYPE_AAC_FDK:
        ui->comboBoxAacFdkMode->setCurrentIndex(static_cast<int>(a_pAdvancedConfig->mode));
        ui->comboBoxAacFdkProfile->setCurrentIndex(static_cast<int>(a_pAdvancedConfig->profile));
        ui->horizontalSliderAacFdk->setValue(a_pAdvancedConfig->value.toInt());
        break;
    case AudioEnc::eENCODE_TYPE_AAC_NERO:
        ui->comboBoxAacNeroMode->setCurrentIndex(static_cast<int>(a_pAdvancedConfig->mode));
        ui->comboBoxAacNeroProfile->setCurrentIndex(static_cast<int>(a_pAdvancedConfig->profile));
        ui->horizontalSliderAacNero->setValue(a_pAdvancedConfig->value.toInt());
        break;
    case AudioEnc::eENCODE_TYPE_ALAC:
        break;
    case AudioEnc::eENCODE_TYPE_FLAC:
        ui->horizontalSliderFlac->setValue(a_pAdvancedConfig->value.toInt());
        break;
    case AudioEnc::eENCODE_TYPE_OPUS:
        ui->comboBoxOpusMode->setCurrentIndex(static_cast<int>(a_pAdvancedConfig->mode));
        ui->horizontalSliderOpus->setValue(a_pAdvancedConfig->value.toInt());
        break;
    case AudioEnc::eENCODE_TYPE_OGG_VORBIS:
        ui->horizontalSliderOggVorbis->setValue(a_pAdvancedConfig->value.toInt());
        break;
    case AudioEnc::eENCODE_TYPE_MP3:
        ui->comboBoxMp3Mode->setCurrentIndex(static_cast<int>(a_pAdvancedConfig->mode));
        ui->horizontalSliderMp3->setValue(a_pAdvancedConfig->value.toInt());
        break;
    case AudioEnc::eENCODE_TYPE_AC3:
        ui->horizontalSliderAc3->setValue(a_pAdvancedConfig->value.toInt());
        break;
    case AudioEnc::eENCODE_TYPE_WAV:
        break;
    }
}

void AudioConfig::setConfig(AudioAdvancedConfig a_pAdvancedConfig)
{
    setConfig(&a_pAdvancedConfig);
}

QString AudioConfig::processAccApple(void)
{
    QString cmd;
    QByteArray exec = qvs::findFirstFilePath(AUDIO_CONFIG_EXEC_AAC_APPLE).toUtf8();
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
    QByteArray exec = qvs::findFirstFilePath(AUDIO_CONFIG_EXEC_AAC_FDK).toUtf8();
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
    QByteArray exec = qvs::findFirstFilePath(AUDIO_CONFIG_EXEC_AAC_NERO).toUtf8();
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
        cmd.sprintf("%s -ignorelength -q %.2f -if - -of \"%1\"", exec.data(), static_cast<double>(value) / eINDEX_100);
        break;
    }
    return cmd;
}

QString AudioConfig::processAlac(void)
{
    QString cmd;
    QByteArray exec = qvs::findFirstFilePath(AUDIO_CONFIG_EXEC_ALAC).toUtf8();

    cmd.sprintf("%s --ignorelength - -o \"%1\"", exec.data());
    return cmd;
}

QString AudioConfig::processFlac(void)
{
    QString cmd;
    QByteArray exec = qvs::findFirstFilePath(AUDIO_CONFIG_EXEC_FLAC).toUtf8();

    cmd.sprintf("%s -%d - -o \"%1\"", exec.data(), ui->horizontalSliderFlac->value());
    return cmd;
}

QString AudioConfig::processOpus(void)
{
    QString cmd;
    QByteArray exec = qvs::findFirstFilePath(AUDIO_CONFIG_EXEC_OPUS).toUtf8();
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
    QByteArray exec = qvs::findFirstFilePath(AUDIO_CONFIG_EXEC_OGG_VORBIS).toUtf8();

    /* not support for bitrate mode in advanced config */
    cmd.sprintf("%s - --ignorelength --quality %.2fk -o \"%1\"", exec.data(), ui->horizontalSliderOggVorbis->value() / static_cast<double>(eINDEX_100));
    return cmd;
}

QString AudioConfig::processMp3(void)
{
    QString cmd;
    QByteArray exec = qvs::findFirstFilePath(AUDIO_CONFIG_EXEC_MP3).toUtf8();
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
    PASS;
    return QString();
}

void AudioConfig::fitValue(QSlider *a_slider, const int &a_maxValue, const int &a_minValue)
{
    a_slider->setMinimum(a_minValue);
    a_slider->setMaximum(a_maxValue);
    if(a_slider->value() > a_maxValue)
    {
        a_slider->setValue(a_maxValue);
    }
    if(a_slider->value() < a_minValue)
    {
        a_slider->setValue(a_minValue);
    }
}

QStringList AudioConfig::getTemplateKeys(void)
{
    QMap<QString, AudioAdvancedConfig> at_config_audio_encode_templates = g_pConfig->m_config_audio_encode_templates;
    QStringList at_templete_keys;

    for(QMap<QString, AudioAdvancedConfig>::iterator i = at_config_audio_encode_templates.begin(); i != at_config_audio_encode_templates.end(); i++)
    {
        at_templete_keys << i.key();
    }
    return at_templete_keys;
}

void AudioConfig::on_buttonSaveTemplate_clicked()
{
    QString key = ui->comboBoxTemplate->currentText();

    if(key.isEmpty())
    {
        return;
    }

    if(key == c_template_key_default)
    {
        QMessageBox::warning(this, tr("Rejection"), tr("Can't save as default template!\nPlease rename template."), QMessageBox::Ok);
        return;
    }

    if(!g_pConfig->containsConfigAudioEncodeTemplate(key))
    {
        ui->comboBoxTemplate->addItem(key);
    }
    g_pConfig->setConfigAudioEncodeTemplate(key, getConfig());
    QMessageBox::information(this, tr("Information"), tr("Template saved!"), QMessageBox::Ok);
}

void AudioConfig::on_buttonDeleteTemplate_clicked()
{
    QString key = ui->comboBoxTemplate->currentText();
    int index = ui->comboBoxTemplate->currentIndex();

    if(key.isEmpty())
    {
        return;
    }

    if( (key == c_template_key_default) || (index == eINDEX_0) )
    {
        QMessageBox::warning(this, tr("Rejection"), tr("Can't delete the default template!"), QMessageBox::Ok);
        return;
    }

    if(!g_pConfig->containsConfigAudioEncodeTemplate(key))
    {
        return;
    }
    g_pConfig->removeConfigAudioEncodeTemplate(key);
    ui->comboBoxTemplate->removeItem(index);
}

void AudioConfig::on_comboBoxTemplate_activated(const QString &a_key)
{
    reloadConfig(a_key);
}
