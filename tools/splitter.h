#ifndef SPLITTER_H
#define SPLITTER_H

#include <QWidget>
#include <QFileDialog>

class StdWatcherCmd;

#include "splitter_config.h"

#define SPLITTER_EXEC_FFMPEG "ffmpeg"
#define SPLITTER_EXEC_MKVMERGE "mkvmerge"

#define EXT_MKV "mkv"
#define EXT_MKA "mka"

namespace Ui {
class Splitter;
}
class MainWindow;

class Splitter : public QWidget
{
    Q_OBJECT

public:
    explicit Splitter(QWidget *parent = nullptr);
    ~Splitter();
    friend class MainWindow;

    void reload(const QString &a_filename, bool a_isRequestKeyFrame = true);
    QString getOutputFilename(const QString &a_path, const QString &a_ext = NULLSTR, int a_count = eINDEX_NONE);
    QString getOutputFileExt(void);
    StdWatcherCmd getSplittedCmd(QString a_input, QString a_output, QPair<QString, QString> a_paramPair);
    StdWatcherCmd getMuxedCmd(QStringList a_inputs, QString a_output);

private slots:
    void splitterParamUpdated(SplitterParam a_param);

    void on_buttonSpliteConfig_clicked();
    void on_buttonSpliteStart_clicked();
    void on_buttonSplitInput_clicked();
    void on_buttonSplitOutput_clicked();

private:
    Ui::Splitter *ui;
    SplitterParam m_param;
};

#endif // SPLITTER_H
