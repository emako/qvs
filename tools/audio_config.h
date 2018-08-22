#ifndef AUDIO_CONFIG_H
#define AUDIO_CONFIG_H

#include "../com/common.h"

#include <QDialog>
#include <QDebug>

class MainWindow;
class AudioEnc;

namespace Ui {
class AudioConfig;
}

class AudioAdvancedConfig
{
public:
    AudioAdvancedConfig()
    {
    }

    QString config_name;
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

public slots:
    virtual void setMode(bool a_advancedMode);
    virtual void reloadFlac(void);

private slots:
    virtual void contextMenuEvent(QContextMenuEvent *e);
    virtual bool eventFilter(QObject *o, QEvent *e);
    virtual void resizeEvent(QResizeEvent *e);
    virtual void resizeEvent(void);
    virtual void resizeEventMinimum(void);

    void on_buttonAccept_clicked();
    void on_buttonCancel_clicked();
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
    void setup(void);
};

#endif // AUDIO_CONFIG_H
