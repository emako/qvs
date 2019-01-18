#ifndef VIDEO_INFO_HPP
#define VIDEO_INFO_HPP

#include "../com/common.h"

class VideoInfo
{
public:
    VideoInfo()
    {
        clear();
    }

    virtual ~VideoInfo()
    {
    }

    enum ScanType
    {
        Progressive,
        Interlaced,
    };

    enum ScanOrder
    {
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
    double fpsFF;
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

#endif // VIDEO_INFO_HPP
