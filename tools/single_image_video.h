#ifndef SINGLE_IMAGE_VIDEO_H
#define SINGLE_IMAGE_VIDEO_H

#include "../com/config.h"

#include <QWidget>
#include <QInputDialog>

#define SIGNLE_IMAGE_VIDEO_EXEC_FFMPEG "ffmpeg"
#define OUTPUT_EXT_MP4 "mp4"
#define OUTPUT_EXT_JPG "jpg"

class MainWindow;

namespace Ui {
class SingleImageVideo;
}

class SingleImageVideo : public QWidget
{
    Q_OBJECT

public:
    explicit SingleImageVideo(QWidget *parent = nullptr);
    ~SingleImageVideo();

    friend class MainWindow;

    void setup();

    void reload(const QString &a_imageFilename, const QString &a_audioFilename);
    QString getOutputFilename(const QString &a_path);

private slots:
    bool eventFilter(QObject *o, QEvent *e);
    void showInOutDialog();
    void previewImage();
    void previewImageFromAudioFile();

    void on_buttonImageVideoStart_clicked();
    void on_editAudioInput_customContextMenuRequested(const QPoint &);

private:
    Ui::SingleImageVideo *ui;
    QMenu *m_pAudioContextMenu;
};

#endif // SINGLE_IMAGE_VIDEO_H
