#ifndef AUDIO_ENC_H
#define AUDIO_ENC_H

#include <QWidget>

class MainWindow;
class StdWatcherCmd;

namespace Ui {
class AudioEnc;
}

class AudioEnc : public QWidget
{
    Q_OBJECT

public:
    explicit AudioEnc(QWidget *parent = 0);
    ~AudioEnc();
    friend class MainWindow;
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

    void reload(QString a_filename);
    void reload(void);
    QString getAudioOutputPath(EENCODE_TYPE a_type, QString a_filename);
    QString getAudioOutputExt(EENCODE_TYPE a_type);
    StdWatcherCmd getEncodeCmd(QString a_input, QString a_output, QString a_bitrate);
    QString getPiperFilename(void);

private slots:
    void on_buttonAudioStart_clicked();
    void on_comboBoxAudioEncoder_activated(int a_index);
    void on_buttonAudioInput_clicked();
    void on_buttonAudioOutput_clicked();

private:
    Ui::AudioEnc *ui;
    void setupUi(void);
};

#endif // AUDIO_ENC_H
