#ifndef PREVIEW_DIALOG_H
#define PREVIEW_DIALOG_H

#include "video_info.hpp"
#include "../com/common.h"
#include "../mediainfo/mediainfo_loader.h"

#include <QMainWindow>
#include <opencv2/opencv.hpp>

#include <QLabel>
#include <QTimer>
#include <QDebug>
#include <QImageWriter>

using namespace cv;

namespace Ui {
class PreviewDialog;
}

class VideoInfo;
class MainWindow;

class PreviewDialog : public QMainWindow
{
    Q_OBJECT

public:
    explicit PreviewDialog(QWidget *parent = nullptr);
    ~PreviewDialog();
    friend class MainWindow;
    class MainWindow *mainUi;
    QUuid m_uid;

    bool reload(const std::string &a_filename);

    inline void setPreviewPixmap(void);
    void setUpZoomPanel(void);
    void setUpTimeLinePanel(void);
    bool requestShowFrame(int a_frameNumber);

    enum ZoomMode {
        NoZoom,
        FixedRatio,
        FitToFrame,
    };

    enum PlayFPSLimitMode{
        FromVideo,
        NoLimit,
        Custom,
    };

    std::string m_filename;
    VideoInfo m_videoInfo;
    MediaInfoLoader m_mediainfoLoader;
    double m_secondsBetweenFrames;
    VideoCapture m_videoCapture;
    Mat m_mat;
    QPixmap m_framePixmap;
    QTimer *m_pPlayTimer;
    int m_frameShown;
    bool m_playing;
    int m_bigFrameStep;
    bool m_reloadTitleShown;

private:
    Ui::PreviewDialog *ui;
    QLabel *m_statusBarLabel;
    void setup(void);

    inline QImage convertMatToImage(const Mat& a_mat);
    inline QPixmap convertMatToPixmap(const Mat& a_mat);
    inline bool setMat(const Mat& a_mat);

    void getVideoInfo(void);
    inline void printVideoInfo(void);

private slots:
    void closeEvent(QCloseEvent *e);
    void wheelEvent(QWheelEvent *e);
    void dragEnterEvent(QDragEnterEvent* e);
    void dropEvent(QDropEvent* e);
    bool eventFilter(QObject *o, QEvent *e);
    void resizeEvent(QResizeEvent *a_pEvent);
    void keyPressEvent(QKeyEvent * a_pEvent);

    void slotPlay(bool a_checked);
    void slotPlayNext(void);
    void slotShowZoomPanel(bool a_checked);
    void slotZoomRatioChanged(double);
    void slotShowFrame(int a_frameNumber);
    void slotZoomModeChanged(int a_index);
    void slotScaleModeChanged(int a_index);
    void slotFrameToClipboard(void);
    void slotSaveSnapshot(void);
    void slotSetPlayFPSLimit(void);
    void slotTimeLineModeChanged(int a_index);
};

#endif // PREVIEW_DIALOG_H
