#ifndef AUDIO_CONFIG_H
#define AUDIO_CONFIG_H

#include "../com/common.h"

#include <QDialog>
#include <QDoubleSpinBox>
#include <QDebug>

#define DEFAULT_BITRATE (160)

class MainWindow;
class AudioEnc;

namespace Ui {
class AudioConfig;
}

class AudioAdvancedConfig
{
public:
    AudioAdvancedConfig(bool a_advanced = false)
        : advanced(a_advanced)
    {
    }

    enum ECONFIG {
        eCONFIG_ADVANCED,
        eCONFIG_TYPE,
        eCONFIG_MODE,
        eCONFIG_PROFILE,
        eCONFIG_VALUE,
        eCONFIG_VALUE2,
        eCONFIG_MAX,
    };

public:
    QString name;               /* advanced config name */
    QString cmd;                /* encoder cmd */
    uint type = eINDEX_0;       /* encoder type */
    uint mode = eINDEX_0;       /* encoder mode */
    uint profile = eINDEX_0;    /* encoder profile */
    QVariant value;             /* encoder value: bitrate/quality */
    QVariant value2;            /* encoder value: flag */

public:
    QString toString(void) const
    {
        return QString("%1:name=%2,type=%3,mode=%4,profile=%5,value=%6,value2=%7,cmd=%8").arg(advanced ? "Enable" : "Disable").arg(name).arg(type).arg(mode).arg(profile).arg(value.toString()).arg(value2.toString()).arg(cmd);
    }

    void print(void) const
    {
        qDebug() << this->toString();
    }

    void setDisable(bool a_advanced = true)
    {
        advanced = !a_advanced;
    }

    void setEnable(bool a_advanced = true)
    {
        advanced = a_advanced;
    }

    bool isEnable(void) const
    {
        return advanced;
    }

private:
    bool advanced;              /* advanced flag */
};

class AudioConfig : public QDialog
{
    Q_OBJECT

public:
    explicit AudioConfig(QDialog *parent = 0);
    ~AudioConfig();
    friend class MainWindow;
    friend class AudioEnc;
    class MainWindow *mainUi;

    enum EAUDIO_CONFIG_MODE {
        eDEFAULT_MODE = eINDEX_0,

        eQAAC_MODE_LC_AAC_TRUE_VBR = eINDEX_0,
        eQAAC_MODE_LC_AAC_CONSTRAINED_VBR,
        eQAAC_MODE_LC_AAC_ABR,
        eQAAC_MODE_LC_AAC_CBR,

        eQAAC_MODE_HE_AAC_CONSTRAINED_VBR = eINDEX_0,
        eQAAC_MODE_HE_AAC_ABR,
        eQAAC_MODE_HE_AAC_CBR,

        eFDKAAC_MODE_CBR = eINDEX_0,
        eFDKAAC_MODE_VBR,

        eNEROAAC_MODE_ABR = eINDEX_0,
        eNEROAAC_MODE_CBR,
        eNEROAAC_MODE_VBR,

        eOPUS_MODE_VBR = eINDEX_0,
        eOPUS_MODE_CONSTRAINED_VBR,
        eOPUS_MODE_HARD_CBR,

        eMP3_MODE_CBR = eINDEX_0,
        eMP3_MODE_ABR,
        eMP3_MODE_VBR,
    };

    enum EAUDIO_CONFIG_PROFILE {
        eDEFAULT_PROFILE = eINDEX_0,

        eQAAC_PROFILE_LC_AAC = eINDEX_0,
        eQAAC_PROFILE_HE_AAC,

        eFDKAAC_PROFILE_MPEG_4_LC_AAC = eINDEX_0,
        eFDKAAC_PROFILE_MPEG_4_HE_AAC,
        eFDKAAC_PROFILE_MPEG_4_HE_AAC_V2,
        eFDKAAC_PROFILE_MPEG_4_AAC_LD,
        eFDKAAC_PROFILE_MPEG_4_AAC_ELD,
        eFDKAAC_PROFILE_MPEG_2_LC_AAC,
        eFDKAAC_PROFILE_MPEG_2_HE_AAC,
        eFDKAAC_PROFILE_MPEG_2_HE_AAC_V2,

        eNEROAAC_PROFILE_AUTO = eINDEX_0,
        eNEROAAC_PROFILE_HE_AAC_PS,
        eNEROAAC_PROFILE_HE_AAC,
        eNEROAAC_PROFILE_LC_AAC,
    };

    AudioAdvancedConfig getDefaultConfig(const uint &a_type = eINDEX_0, const QVariant &a_value = DEFAULT_BITRATE);
    void setDefaultConfig(const AudioAdvancedConfig &advanced_config);
    void setDefaultConfig(const uint &a_type, const QVariant &a_value); /* used from class audio enc */

    AudioAdvancedConfig getConfig(void);
    void setConfig(AudioAdvancedConfig *a_pAdvancedConfig);
    void setConfig(AudioAdvancedConfig a_pAdvancedConfig);

    void reloadConfig(const QString &a_key);

public slots:
    virtual void setMode(bool a_advancedMode);
    virtual void moveValue(void);
    virtual void setValueValue(void);
    virtual bool containsValue(QObject *a_object);
    virtual void setValueVisible(const bool &a_visible);
    virtual void setValueHidden(void);
    virtual void valueChanged(double a_value);
    virtual QString processAccApple(void);
    virtual QString processAccFdk(void);
    virtual QString processAccNero(void);
    virtual QString processAlac(void);
    virtual QString processFlac(void);
    virtual QString processOpus(void);
    virtual QString processOggVorbis(void);
    virtual QString processMp3(void);
    virtual QString processAc3(void);
    virtual QString processWav(void);

private slots:
    virtual bool eventFilter(QObject *o, QEvent *e);
    virtual void resizeEvent(QResizeEvent *e);
    virtual void resizeEvent(void);
    virtual void resizeEventMinimum(void);

    void on_buttonSaveTemplate_clicked();
    void on_buttonDeleteTemplate_clicked();
    void on_buttonAccept_clicked();
    void on_buttonCancel_clicked();
    void on_comboBoxTemplate_activated(const QString &a_key);
    void on_comboBoxAudioEncoder_currentIndexChanged(int a_index);
    void on_checkBoxAdvancedOption_stateChanged(int a_state);
    void on_comboBoxAacAppleProfile_currentIndexChanged(int a_index);
    void on_comboBoxAacAppleMode_currentIndexChanged(int a_index);
    void on_horizontalSliderAacApple_valueChanged(int a_value);
    void on_comboBoxAacFdkMode_currentIndexChanged(int a_index);
    void on_horizontalSliderAacFdk_valueChanged(int a_value);
    void on_horizontalSliderAacNero_valueChanged(int value);
    void on_comboBoxAacNeroMode_currentIndexChanged(int a_index);
    void on_horizontalSliderFlac_valueChanged(int a_value);
    void on_horizontalSliderOpus_valueChanged(int a_value);
    void on_horizontalSliderOggVorbis_valueChanged(int a_value);
    void on_comboBoxMp3Mode_currentIndexChanged(int a_index);
    void on_horizontalSliderMp3_valueChanged(int a_value);
    void on_horizontalSliderAc3_valueChanged(int a_value);

private:
    Ui::AudioConfig *ui;
    bool m_advancedMode;
    QDoubleSpinBox *m_pSpinBox;
    QTimer *m_pTimerValueHidden;
    QList<QWidget *> s_value_sliders;

private:
    void setup(void);
    void setupUi(void);
    void loadConfig(void);
    void fitValue(QSlider *a_slider, const int &a_maxValue, const int &a_minValue = (int)eINDEX_0);
    QStringList getTemplateKeys(void);
};

extern const QList<QPair<AudioAdvancedConfig::ECONFIG, QString>> c_list_config_encode_audio;

#endif // AUDIO_CONFIG_H
