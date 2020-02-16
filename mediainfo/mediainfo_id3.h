#ifndef MEDIAINFO_ID3_H
#define MEDIAINFO_ID3_H

#include <QMap>
#include <QImage>

#include "../com/common.h"

extern "C"
{
#include "libavdevice/avdevice.h"
}

class MediaInfoID3
{
public:
    MediaInfoID3();
    ~MediaInfoID3();

    bool open(const QString &a_fileName);
    void close();

    AVFormatContext *m_pFormatCtx;
    QMap<QString, QString> m_infoMap;
    QList<QImage> m_infoImages;
};

#endif // MEDIAINFO_ID3_H
