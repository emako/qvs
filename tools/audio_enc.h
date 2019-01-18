#ifndef AUDIO_ENC_H
#define AUDIO_ENC_H

#include <QWidget>
#include <QValidator>
#include <QRegExpValidator>

#include "std_watcher.h"

#define AUDIO_CONFIG_EXEC_PIPER "ffmpeg"
#define AUDIO_CONFIG_EXEC_PIPER_32 "ffmpeg32"
#define AUDIO_CONFIG_EXEC_AAC_APPLE "qaac"
#define AUDIO_CONFIG_EXEC_AAC_FDK "fdkaac"
#define AUDIO_CONFIG_EXEC_AAC_NERO "neroAacEnc"
#define AUDIO_CONFIG_EXEC_FLAC "flac"
#define AUDIO_CONFIG_EXEC_ALAC "refalac"
#define AUDIO_CONFIG_EXEC_OPUS "opusenc"
#define AUDIO_CONFIG_EXEC_OGG_VORBIS "oggenc2"
#define AUDIO_CONFIG_EXEC_MP3 "lame"
#define AUDIO_CONFIG_EXEC_AC3 AUDIO_CONFIG_EXEC_PIPER
#define AUDIO_CONFIG_EXEC_AC3_32 AUDIO_CONFIG_EXEC_PIPER_32
#define AUDIO_CONFIG_EXEC_WAV AUDIO_CONFIG_EXEC_PIPER
#define AUDIO_CONFIG_EXEC_WAV_32 AUDIO_CONFIG_EXEC_PIPER_32

class MainWindow;
class AudioConfig;
class AudioAdvancedConfig;
class StdWatcherCmd;
class StdWatcher;

namespace Ui {
class AudioEnc;
}

class AudioEnc : public QWidget
{
    Q_OBJECT

public:
    explicit AudioEnc(QWidget *parent = nullptr);
    ~AudioEnc();
    friend class MainWindow;
    friend class AudioConfig;
    class MainWindow *mainUi;

    enum EENCODE_TYPE {
        eENCODE_TYPE_AAC_APPLE,
        eENCODE_TYPE_AAC_FDK,
        eENCODE_TYPE_AAC_NERO,
        eENCODE_TYPE_ALAC,
        eENCODE_TYPE_FLAC,
        eENCODE_TYPE_OPUS,
        eENCODE_TYPE_OGG_VORBIS,
        eENCODE_TYPE_MP3,
        eENCODE_TYPE_AC3,
        eENCODE_TYPE_WAV,
        eENCODER_MAX,
    };

    void init(void);
    void reload(QString a_filename);
    void reload(void);
    QString getAudioOutputPath(EENCODE_TYPE a_type, QString a_filename);
    QString getAudioOutputExt(EENCODE_TYPE a_type);
    StdWatcherCmd getEncodeCmd(QString a_input, QString a_output, QString a_bitrate);
    StdWatcher::EDATA_TYPE getDataType(void);
    QString getPiperFilename(void);

public slots:
    void setMode(const bool &a_advancedMode);
    void setConfig(const AudioAdvancedConfig &a_advancedConfig);

private slots:
    void on_buttonAudioStart_clicked();
    void on_comboBoxAudioEncoder_activated(int a_index);
    void on_comboBoxAudioEncoder_currentIndexChanged(int a_index);
    void on_comboBoxAudioBitrate_currentTextChanged(const QString &a_text);
    void on_buttonAudioInput_clicked();
    void on_buttonAudioOutput_clicked();
    void on_buttonAudioConfig_clicked();

private:
    Ui::AudioEnc *ui;
    AudioAdvancedConfig *m_pAdvancedConfig;
    QValidator *m_validatorBitrate;
    void setup(void);
    void setDefaultConfig(void);
    void saveCurrentAdvancedConfig(void);
};

#endif // AUDIO_ENC_H
