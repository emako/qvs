#include "mediainfo_loader.h"
#include <QDebug>

using namespace MediaInfoDLL;
using namespace std;

MediaInfoLoader::MediaInfoLoader()
{
}

MediaInfoLoader::MediaInfoLoader(const QString &a_filename)
    : m_filename(a_filename)
{
    open();
}

void MediaInfoLoader::close(void)
{
    if(m_mediainfo.IsReady())
    {
        m_mediainfo.Close();
    }
}

size_t MediaInfoLoader::open(const QString &a_filename)
{
    close();
    return m_mediainfo.Open(a_filename.toStdWString());
}

size_t MediaInfoLoader::open(void)
{
    close();
    return m_mediainfo.Open(m_filename.toStdWString());
}

QString MediaInfoLoader::get(EMEDIA_PROP a_prop, ESTREAM_TYPE a_streamType, size_t a_streamNumber)
{
    QString info;

    if(!m_mediainfo.IsReady())
    {
        return info;
    }

    switch(a_prop)
    {
    case eMEDIA_PROP_ALL_COMPLETE:
        m_mediainfo.Option(MEDIA_PROP_COMPLETE, MEDIA_PROP_TRUE);
        info = _Q(m_mediainfo.Inform());
        break;
    case eMEDIA_PROP_ALL:
        m_mediainfo.Option(MEDIA_PROP_COMPLETE, MEDIA_PROP_FALSE);
        info = _Q(m_mediainfo.Inform());
        break;
    case eMEDIA_PROP_FORMAT_CODE:
        info = _Q(m_mediainfo.Get((stream_t)a_streamType, a_streamNumber, MEDIA_PROP_FORMAT));
        break;
    case eMEDIA_PROP_FORMAT:
    do{
        QString color_space = get(eMEDIA_PROP_COLOR_SPACE, a_streamType, a_streamNumber);
        QString chroma_subsampling = get(eMEDIA_PROP_CHROMA_SUBSAMPLING, a_streamType, a_streamNumber).remove(QT_COLON);
        QString bit_depth = get(eMEDIA_PROP_BIT_DEPTH, a_streamType, a_streamNumber);
        if(color_space.isEmpty() || chroma_subsampling.isEmpty() || bit_depth.isEmpty())
        {
            QString format = get(eMEDIA_PROP_FORMAT_CODE, eSTREAM_TYPE_GENERAL, a_streamNumber);

            if(format.isEmpty())
            {
                info = QObject::tr("UNKNOWED");
            }
            else
            {
                info = format;
            }
        }
        else
        {
            info = color_space + chroma_subsampling + "P" + bit_depth;
        }
    }while(false);
        break;
    case eMEDIA_PROP_WIDTH:
        info = _Q(m_mediainfo.Get((stream_t)a_streamType, a_streamNumber, MEDIA_PROP_WIDTH));
        break;
    case eMEDIA_PROP_HEIGHT:
        info = _Q(m_mediainfo.Get((stream_t)a_streamType, a_streamNumber, MEDIA_PROP_HEIGHT));
        break;
    case eMEDIA_PROP_FRAME_RATE_MODE:
        info = _Q(m_mediainfo.Get((stream_t)a_streamType, a_streamNumber, MEDIA_PROP_FRAME_RATE_MODE));
        break;
    case eMEDIA_PROP_FRAME_RATE:
        info = _Q(m_mediainfo.Get((stream_t)a_streamType, a_streamNumber, MEDIA_PROP_FRAME_RATE));
        break;
    case eMEDIA_PROP_FRAME_RATE_NUM:
        info = _Q(m_mediainfo.Get((stream_t)a_streamType, a_streamNumber, MEDIA_PROP_FRAME_RATE_NUM));
        break;
    case eMEDIA_PROP_FRAME_RATE_DEN:
        info = _Q(m_mediainfo.Get((stream_t)a_streamType, a_streamNumber, MEDIA_PROP_FRAME_RATE_DEN));
        break;
    case eMEDIA_PROP_FRAME_COUNT:
        info = _Q(m_mediainfo.Get((stream_t)a_streamType, a_streamNumber, MEDIA_PROP_FRAME_COUNT));
        break;
    case eMEDIA_PROP_DURATION:
        info = _Q(m_mediainfo.Get((stream_t)a_streamType, a_streamNumber, MEDIA_PROP_DURATION));
        break;
    case eMEDIA_PROP_BIT_RATE:
        info = _Q(m_mediainfo.Get((stream_t)a_streamType, a_streamNumber, MEDIA_PROP_BIT_RATE));
        break;
    case eMEDIA_PROP_COLOR_SPACE:
        info = _Q(m_mediainfo.Get((stream_t)a_streamType, a_streamNumber, MEDIA_PROP_COLOR_SPACE));
        break;
    case eMEDIA_PROP_CHROMA_SUBSAMPLING:
        info = _Q(m_mediainfo.Get((stream_t)a_streamType, a_streamNumber, MEDIA_PROP_CHROMA_SUBSAMPLING));
        break;
    case eMEDIA_PROP_BIT_DEPTH:
        info = _Q(m_mediainfo.Get((stream_t)a_streamType, a_streamNumber, MEDIA_PROP_BIT_DEPTH));
        break;
    case eMEDIA_PROP_SCAN_TYPE:
        info = _Q(m_mediainfo.Get((stream_t)a_streamType, a_streamNumber, MEDIA_PROP_SCAN_TYPE));
        break;
    case eMEDIA_PROP_SCAN_ORDER:
        info = _Q(m_mediainfo.Get((stream_t)a_streamType, a_streamNumber, MEDIA_PROP_SCAN_ORDER));
        break;
    }
    return info;
}
