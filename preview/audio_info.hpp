#ifndef AUDIO_INFO_HPP
#define AUDIO_INFO_HPP

#include <QObject>
#include <QMap>
#include <QList>
#include <QImage>

class AudioInfo
{
public:
    AudioInfo()
    {
        clear();
    }

    virtual ~AudioInfo()
    {
    }

    virtual void clear(void)
    {
        m_infoMap.clear();
        m_infoImages.clear();
    }

    QMap<QString, QString> m_infoMap;
    QList<QImage> m_infoImages;
};

#endif // AUDIO_INFO_HPP
