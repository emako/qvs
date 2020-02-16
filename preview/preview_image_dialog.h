#ifndef PREVIEW_IMAGE_DIALOG_H
#define PREVIEW_IMAGE_DIALOG_H

#include <QMainWindow>
#include <QObject>
#include <QLabel>
#include <QDebug>
#include <QImageWriter>
#include <QStandardPaths>
#include <QFileDialog>

#include "preview_area.h"
#include "audio_info.hpp"
#include "../com/common.h"

namespace Ui {
class PreviewImageDialog;
}

class MainWindow;
class MediaInfoID3;

class PreviewImageDialog : public QMainWindow
{
    Q_OBJECT

public:
    explicit PreviewImageDialog(QWidget *parent = nullptr);
    ~PreviewImageDialog();
    int exec();
    friend class MainWindow;

    bool reloadFromImageFile(const QString& a_filename);
    bool reloadFromAudioFile(const QString& a_filename);
    bool reload(QImage a_iamge);
    bool reload(QList<QImage> a_iamges);
    void setPreviewPixmap(const QImage &a_image);
    void setPreviewPixmap(void);

    inline QImage getFrameImage();
    QList<QImage> m_frameImages;
    int m_frameImageIndex;
    QPixmap m_framePixmap;

private:
    Ui::PreviewImageDialog *ui;
    QEventLoop *m_pEventLoop;
    QMenu *m_pContextMenu;
    QLabel *m_statusBarLabel;

    void setup(void);
    QRect getPreviewRect(void);

    AudioInfo getAudioInfo(const QString& a_filename);

    void updateTitle(const QString& a_filename);
    void updateStatus(void);
    QString getStatus(void);

private Q_SLOTS:
    void showEvent(QShowEvent *e);
    void closeEvent(QCloseEvent *e);
    void resizeEvent(QResizeEvent *a_pEvent);
    void previewContextMenuRequested(const QPoint &);

    void slotJumpPagePrev(void);
    void slotJumpPageNext(void);
    void slotFrameToClipboard(void);
};

#endif // PREVIEW_IMAGE_DIALOG_H
