#ifndef PREVIEW_DIALOG_H
#define PREVIEW_DIALOG_H

#define USING_OPENCV  0 // openCV's ffmpeg API is too slower.
#define USING_PAINTER 0 // painter can not set the scaled mode.

#if USING_OPENCV
#include <opencv2/opencv.hpp>
using namespace cv;
#else
#include <QtAV>
#include <QtAV/PreviewRenderer.h>
using namespace QtAV;
class StatisticsView;
#endif

#include <QMainWindow>
#include <QObject>
#include <QLabel>
#include <QTimer>
#include <QDebug>
#include <QImageWriter>
#include <QMetaType>
#include <QMutex>

#include "statistics_view.h"
#include "preview_area.h"
#include "video_info.hpp"
#include "../com/common.h"
#include "../mediainfo/mediainfo_loader.h"
#include "../mediainfo/mediainfo_prober.h"

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
    void setPreviewPixmap(const QImage &a_image);
    void setPreviewPixmap(void);
    void drawPreviewImage(const QImage &a_image);
    void drawPreviewImage();
    void setUpZoomPanel(void);
    void setUpTimeLinePanel(void);
    bool requestShowFrame(int a_frameNumber);

    enum ZoomMode 
	{
        NoZoom,
        FixedRatio,
        FitToFrame,
    };

    enum PlayFPSLimitMode
	{
        FromVideo,
        NoLimit,
        Custom,
    };

    std::string m_filename;
    VideoInfo m_videoInfo;
    MediaInfoLoader m_mediainfoLoader;
    MediaInfoProber *m_mediainfoProber;

    double m_secondsBetweenFrames;

#if USING_OPENCV
    VideoCapture m_videoCapture;
    Mat m_mat;
#else
	AVPlayer *m_pPlayer;
    PreviewRenderer *m_pVideoOutput;
#endif

	StatisticsView *m_pStatisticsView;

    bool m_isLocked;
    QPixmap m_framePixmap;
    QImage m_frameImage;
    QTimer *m_pPlayTimer;

    int m_frameShown;
    bool m_playing;
    int m_bigFrameStep;
    bool m_reloadTitleShown;

private:
    Ui::PreviewDialog *ui;
    QMenu *m_pContextMenu;
    QLabel *m_statusBarLabel;
    bool isInitialing; // true: avplayer was firstly played.
#if USING_PAINTER
    QPainter *m_pPreviewPainter;
#endif
    void setup(void);

#if USING_OPENCV
    inline QImage convertMatToImage(const Mat& a_mat);
    inline QPixmap convertMatToPixmap(const Mat& a_mat);
    inline bool setMat(const Mat& a_mat);
#endif

    void getVideoInfo(void);
    inline void printVideoInfo(void);

    QRect getVideoOutputRect(void);

public Q_SLOTS:
    void slotShowVideoInfo(void);

private Q_SLOTS:
    void closeEvent(QCloseEvent *e);
    void wheelEvent(QWheelEvent *e);
    void dragEnterEvent(QDragEnterEvent* e);
    void dropEvent(QDropEvent* e);
    bool eventFilter(QObject *o, QEvent *e);
    void resizeEvent(QResizeEvent *a_pEvent);
    void keyPressEvent(QKeyEvent * a_pEvent);
    void previewContextMenuRequested(const QPoint &);
    void stateChanged(AVPlayer::State a_state);
	void updatePreview(const QImage &a_image);
    void updateSoundButtonIcon(void);

    void slotPlay(bool a_checked);
    void slotPlayNext(void);
    void slotShowZoomPanel(bool a_checked);
    void slotZoomRatioChanged(double);
	void slotSeek(double a_secs);
    void slotPositionChanged(qint64 a_pos);
    void slotShowFrame(int a_frameNumber);
    void slotZoomModeChanged(int a_index);
    void slotScaleModeChanged(int a_index);
    void slotFrameToClipboard(void);
    void slotSaveSnapshot(void);
    void slotSetPlayFPSLimit(void);
    void slotTimeLineModeChanged(int a_index);
    void slotSoundMuted(bool a_checked);
    void slotOpenMediaFile(void);
    void slotSetExternalAudio(void);
    void on_sliderSound_valueChanged(int a_value);
};

#endif // PREVIEW_DIALOG_H
