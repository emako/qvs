#include "mediainfo_loader.h"
#include <QDebug>

extern QList<QPair<QString, QList<QPair<MediaInfoDLL::String, QPair<QString, bool>>>>> g_mediainfo_lists;

MediaInfoLoader::MediaInfoLoader()
{
}

MediaInfoLoader::MediaInfoLoader(const QString &a_filename)
    : m_filename(a_filename)
{
    open();
}

QString MediaInfoLoader::option(const String &a_option, const String &a_value)
{
    return fromStd(m_mediainfo.Option(a_option, a_value));
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

QString MediaInfoLoader::inform(EFORMAT a_format)
{
    QString inform;

    if(a_format == eFORMAT_INI)
    {
        for(size_t i = (size_t)eINDEX_0; i < (size_t)g_mediainfo_lists.length(); i++)
        {
            QList<QPair<MediaInfoDLL::String, QPair<QString, bool>>> context = g_mediainfo_lists.at((int)i).second;
            size_t streamCount = count(static_cast<stream_t>(i));

            for(size_t k = (size_t)0; k < streamCount; k++)
            {
                QString group = QString("[%1%2]").arg(g_mediainfo_lists.at((int)i).first).arg(streamCount >= (size_t)eINDEX_2 ? QString::number(k + (size_t)eINDEX_1) : QT_EMPTY);;

                inform += group + QT_NOR_EOL;
                for(int j = (size_t)eINDEX_0; j < (size_t)context.length(); j++)
                {
                    QString key = context.at(j).second.first;
                    QString value = get(context.at(j).first, static_cast<stream_t>(i), k);

                    if(!value.isEmpty() && context.at(j).first != MI_OPTION_INFORM)
                    {
                        QString info = QString("%1=%2").arg(key).arg(value);
                        inform += info + QT_NOR_EOL;
#ifdef QT_DEBUG
                        qDebug() << group << info;
#endif
                    }
                }
            }
        }
    }
    else if(a_format == eFORMAT_JSON)
    {
        QJsonObject infoArray;

        for(size_t i = (size_t)eINDEX_0; i < (size_t)g_mediainfo_lists.length(); i++)
        {
            QList<QPair<MediaInfoDLL::String, QPair<QString, bool>>> context = g_mediainfo_lists.at((int)i).second;
            size_t streamCount = count(static_cast<stream_t>(i));
            QJsonObject info;

            for(size_t k = (size_t)0; k < streamCount; k++)
            {
                QString group = QString("%1%2").arg(g_mediainfo_lists.at((int)i).first).arg(streamCount >= (size_t)eINDEX_2 ? QString::number(k + (size_t)eINDEX_1) : QT_EMPTY);;

                for(int j = (size_t)eINDEX_0; j < (size_t)context.length(); j++)
                {
                    QString key = context.at(j).second.first;
                    QString value = get(context.at(j).first, static_cast<stream_t>(i), k);

                    if(!value.isEmpty() && context.at(j).first != MI_OPTION_INFORM)
                    {
                        info.insert(key, value);
#ifdef QT_DEBUG
                        qDebug() << group << info;
#endif
                    }
                }
                infoArray.insert(group, info);
            }
        }
        inform = qvs::getStringFromJson(infoArray);
#ifdef QT_DEBUG
        qvs::setFileText(".json", inform);
#endif
    }
    else if(a_format == eFORMAT_XML)
    {

    }

    return inform;
}

QString MediaInfoLoader::get(EMEDIA_PROP a_prop, ESTREAM_TYPE a_streamType, size_t a_streamNumber)
{
    String info; /* Type define from MediaInfoDLL Header file. */
    String option;

    if(!m_mediainfo.IsReady())
    {
        return QT_EMPTY;
    }

    switch(a_prop)
    {
    case eMEDIA_PROP_ALL_COMPLETE:
        option = m_mediainfo.Option(MI_OPTION_COMPLETE, MI_VALUE_TRUE);
        info = m_mediainfo.Inform();
        break;
    case eMEDIA_PROP_ALL:
        option = m_mediainfo.Option(MI_OPTION_COMPLETE, MI_VALUE_FALSE);
        info = m_mediainfo.Inform();
        break;
    case eMEDIA_PROP_FORMAT_CODE:
        info = m_mediainfo.Get((stream_t)a_streamType, a_streamNumber, MEDIA_PROP_FORMAT);
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
                info = toStd(QObject::tr("Unknowed"));
            }
            else
            {
                info = toStd(format);
            }
        }
        else
        {
            info = toStd(color_space + chroma_subsampling + "P" + bit_depth);
        }
    }while(false);
        break;
    case eMEDIA_PROP_WIDTH:
        info = m_mediainfo.Get((stream_t)a_streamType, a_streamNumber, MEDIA_PROP_WIDTH);
        break;
    case eMEDIA_PROP_HEIGHT:
        info = m_mediainfo.Get((stream_t)a_streamType, a_streamNumber, MEDIA_PROP_HEIGHT);
        break;
    case eMEDIA_PROP_FRAME_RATE_MODE:
        info = m_mediainfo.Get((stream_t)a_streamType, a_streamNumber, MEDIA_PROP_FRAME_RATE_MODE);
        break;
    case eMEDIA_PROP_FRAME_RATE:
        info = m_mediainfo.Get((stream_t)a_streamType, a_streamNumber, MEDIA_PROP_FRAME_RATE);
        break;
    case eMEDIA_PROP_FRAME_RATE_NUM:
        info = m_mediainfo.Get((stream_t)a_streamType, a_streamNumber, MEDIA_PROP_FRAME_RATE_NUM);
        break;
    case eMEDIA_PROP_FRAME_RATE_DEN:
        info = m_mediainfo.Get((stream_t)a_streamType, a_streamNumber, MEDIA_PROP_FRAME_RATE_DEN);
        break;
    case eMEDIA_PROP_FRAME_COUNT:
        info = m_mediainfo.Get((stream_t)a_streamType, a_streamNumber, MEDIA_PROP_FRAME_COUNT);
        break;
    case eMEDIA_PROP_DURATION:
        info = m_mediainfo.Get((stream_t)a_streamType, a_streamNumber, MEDIA_PROP_DURATION);
        break;
    case eMEDIA_PROP_BIT_RATE:
        info = m_mediainfo.Get((stream_t)a_streamType, a_streamNumber, MEDIA_PROP_BIT_RATE);
        break;
    case eMEDIA_PROP_COLOR_SPACE:
        info = m_mediainfo.Get((stream_t)a_streamType, a_streamNumber, MEDIA_PROP_COLOR_SPACE);
        break;
    case eMEDIA_PROP_CHROMA_SUBSAMPLING:
        info = m_mediainfo.Get((stream_t)a_streamType, a_streamNumber, MEDIA_PROP_CHROMA_SUBSAMPLING);
        break;
    case eMEDIA_PROP_BIT_DEPTH:
        info = m_mediainfo.Get((stream_t)a_streamType, a_streamNumber, MEDIA_PROP_BIT_DEPTH);
        break;
    case eMEDIA_PROP_SCAN_TYPE:
        info = m_mediainfo.Get((stream_t)a_streamType, a_streamNumber, MEDIA_PROP_SCAN_TYPE);
        break;
    case eMEDIA_PROP_SCAN_ORDER:
        info = m_mediainfo.Get((stream_t)a_streamType, a_streamNumber, MEDIA_PROP_SCAN_ORDER);
        break;
    }
    return fromStd(info);
}

QString MediaInfoLoader::get(const String &a_param, stream_t a_streamType, size_t a_streamNumber, info_t a_infoKind, info_t a_SearchKind)
{
    return fromStd(m_mediainfo.Get(a_streamType, a_streamNumber, a_param, a_infoKind, a_SearchKind));
}

QString MediaInfoLoader::get(size_t a_param, stream_t a_streamType, size_t a_streamNumber, info_t a_infoKind)
{
    return fromStd(m_mediainfo.Get(a_streamType, a_streamNumber, a_param, a_infoKind));
}

size_t MediaInfoLoader::count(stream_t a_streamType, size_t a_streamNumber)
{
    return m_mediainfo.Count_Get(a_streamType, a_streamNumber);
}

void MediaInfoLoader::close(void)
{
    if(m_mediainfo.IsReady())
    {
        m_mediainfo.Close();
    }
}

QString MediaInfoLoader::ver(void)
{
    return option(MI_OPTION_INFO_VERSION);
}
