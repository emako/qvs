#ifndef MEDIAINFO_PROBER_H
#define MEDIAINFO_PROBER_H

#include "../com/common.h"

#include <QtAV>
#include <QDebug>

using namespace QtAV;

extern "C"
{
#include "libavfilter/buffersink.h"
#include "libavfilter/buffersrc.h"
#include "libswscale/swscale.h"
#include "libavdevice/avdevice.h"
#include "libavutil/pixfmt.h"
#include "libavutil/opt.h"
#include "libavcodec/avfft.h"
#include "libavutil/imgutils.h"
}

class MediaInfoProber
{
public:
    MediaInfoProber();
    MediaInfoProber(const QString &a_filename);
    virtual ~MediaInfoProber();

    bool open(const QString &a_filename);
    bool open(void);

    AVFormatContext *get(void);

    QString inform(void);
    QString inform(bool a_complete);

    virtual void close(void);

    QString version(void);

    QString getPixfmt(const AVPixelFormat &a_pixfmt);
    int64_t getDuration();

private:
    AVFormatContext *m_pFormatCtx;
    QString m_filename;
};

#endif // MEDIAINFO_PROBER_H
