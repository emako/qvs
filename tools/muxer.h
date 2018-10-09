#ifndef MUXER_H
#define MUXER_H

#include <QWidget>
#include "std_watcher.h"
#include "std_manager.h"

#define MUXER_EXEC_MP4BOX "mp4box"
#define MUXER_EXEC_LSMASH_MUXER "muxer"
#define MUXER_EXEC_FFMPEG "ffmpeg"
#define MUXER_EXEC_MKVMERGE "mkvmerge"

class MainWindow;

namespace Ui {
class Muxer;
}

class Muxer : public QWidget
{
    Q_OBJECT

public:
    explicit Muxer(QWidget *parent = nullptr);
    ~Muxer();
    friend class MainWindow;
    class MainWindow *mainUi;

    enum ERELOAD_TYPE {
        eRELOAD_TYPE_VIDEO,
        eRELOAD_TYPE_AUDIO,
        eRELOAD_TYPE_MAX,
    };
    enum EOUTPUT_TYPE {
        eOUTPUT_TYPE_MP4BOX,
        eOUTPUT_TYPE_LSMASH,
        eOUTPUT_TYPE_MKVMERGE,
        eOUTPUT_TYPE_FFMPEG,
        eOUTPUT_TYPE_MAX,
    };

    void reload(ERELOAD_TYPE a_reload_type, QString a_filename);
    void reload(EOUTPUT_TYPE a_reload_type);
    QString getOutputFilename(const QString a_basename);
    QString getOutputFileExt(EOUTPUT_TYPE a_output_type);

private slots:
    void on_buttonMuxerStart_clicked();
    void on_comboBoxMuxerFormat_activated(int a_index);
    void on_comboBoxMuxerFormat_currentIndexChanged(int a_index);
    void on_buttonMuxerVideoInput_clicked();
    void on_buttonMuxerAudioInput_clicked();
    void on_buttonMuxerOutput_clicked();

private:
    Ui::Muxer *ui;
    void setup(void);
};

#endif // MUXER_H
