#ifndef PREVIEW_DIALOG_H
#define PREVIEW_DIALOG_H

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

class VideoInfo
{
public:
    VideoInfo() {
        clear();
    }

    virtual ~VideoInfo() {
    }

    enum ScanType {
        Progressive,
        Interlaced,
    };

    enum ScanOrder {
        TFF,
        BFF,
    };

    virtual void clear(void)
    {
        frameCount    = eINDEX_0;
        frameWidth    = eINDEX_0;
        frameHeight   = eINDEX_0;
        fpsCV         = static_cast<double>(eINDEX_0);
        fps           = static_cast<double>(eINDEX_0);
        fpsNum        = eINDEX_0;
        fpsDen        = eINDEX_0;
        depth         = eINDEX_NONE;
        isVFR         = false;
        scanType      = Progressive;
        scanOrder     = TFF;
    }

    QString getStatus(void)
    {
        calcFps();
        return QObject::tr("Frames: %1 | Time: %2 | Size: %3x%4 | FPS: %5 (%6/%7) | Format: %8").arg(frameCount).arg(time).arg(frameWidth).arg(frameHeight).arg(fps).arg(fpsNum).arg(fpsDen).arg(format);
    }

    void printStatus(void)
    {
        qDebug() << QString("Pos=%1ms,Frames=%2/%3,FPS=%4,Size=%5x%6").arg(posMsec).arg(posFrames).arg(frameCount).arg(fps).arg(frameWidth).arg(frameHeight);
    }

    int getGreatestCommonDivisor(int a, int b)
    {
        int c;

        c = (a > b) ? b : a;
        while(a % c != 0 || b % c != 0)
        {
            c--;
        }
        return c;
    }

    void calcFps(void)
    {
        int gcd;

        if( (fpsNum == 0) && (fpsDen == 0) && (static_cast<int>(fps) != 0) )
        {
            fpsNum = static_cast<int>(fps * eINDEX_1000);
            fpsDen = eINDEX_1000;
            gcd = getGreatestCommonDivisor(fpsNum, fpsDen);
            if(gcd != 0)
            {
                fpsNum /= gcd;
                fpsDen /= gcd;
            }
        }
    }

    bool checkVFR(const QString & a_frameRateMode)
    {
        bool isVFR = false;

        if(a_frameRateMode == "Constant")
        {
            isVFR = false;
        }
        else if(a_frameRateMode == "Variable")
        {
            isVFR = true;
        }
        return isVFR;
    }

    ScanType checkScanType(const QString & a_scanType)
    {
        ScanType scanType = Progressive;

        if(a_scanType == "Progressive")
        {
            scanType = Progressive;
        }
        else if(a_scanType == "Interlaced")
        {
            scanType = Interlaced;
        }
        return scanType;
    }

    ScanOrder checkScanOrder(const QString & a_scanOrder)
    {
        ScanOrder scanOrder = TFF;

        if(a_scanOrder == "TFF")
        {
            scanOrder = TFF;
        }
        else if(a_scanOrder == "BFF")
        {
            scanOrder = BFF;
        }
        return scanOrder;
    }

    /* Variant Info */
    double posMsec;
    int posFrames;
    double AviRatio;

    /* Fixed Info */
    int frameCount;
    int frameWidth;
    int frameHeight;
    double fpsCV;
    double fps;
    int fpsNum;
    int fpsDen;
    QString format;
    int depth;
    QString time;
    bool isVFR;
    ScanType scanType;
    ScanOrder scanOrder;
};

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
