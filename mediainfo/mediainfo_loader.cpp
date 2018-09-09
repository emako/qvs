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

QString MediaInfoLoader::traversal(EFORMAT a_format)
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
    }
    return inform;
}

QString MediaInfoLoader::inform(bool a_complete, EFORMAT a_format)
{
    String value = MI_VALUE_FALSE;

    if(a_complete)
    {
        value = MI_VALUE_TRUE;
    }
    if(option(MI_OPTION_COMPLETE_GET, value) != value)
    {
        option(MI_OPTION_COMPLETE, value);
    }
    format(a_format);
    return inform();
}

QString MediaInfoLoader::inform(bool a_complete)
{
    String value = MI_VALUE_FALSE;

    if(a_complete)
    {
        value = MI_VALUE_TRUE;
    }
    if(option(MI_OPTION_COMPLETE_GET, value) != value)
    {
        option(MI_OPTION_COMPLETE, value);
    }
    return inform();
}

QString MediaInfoLoader::inform(void)
{
    return fromStd(m_mediainfo.Inform());
}

QString MediaInfoLoader::get(EMEDIA_PROP a_prop, ESTREAM_TYPE a_streamType, size_t a_streamNumber)
{
    String info; /* Type define from MediaInfoDLL Header file. */

    if(!m_mediainfo.IsReady())
    {
        return QT_EMPTY;
    }

    switch(a_prop)
    {
    case eMEDIA_PROP_ALL_COMPLETE:
        option(MI_OPTION_COMPLETE, MI_VALUE_TRUE);
        info = m_mediainfo.Inform();
        break;
    case eMEDIA_PROP_ALL:
        option(MI_OPTION_COMPLETE, MI_VALUE_FALSE);
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

QString MediaInfoLoader::version(void)
{
    return option(MI_OPTION_INFO_VERSION);
}

QString MediaInfoLoader::language(const QString &a_language)
{
    QResource resource(QString(":/strings/mediainfo/language/%1.csv").arg(a_language));
    QByteArray data((const char *)resource.data(), resource.size());
    QString language_list = QString::fromUtf8(data);

    if(a_language == MEDIA_LANGUAGE_DEFAULT)
    {
        if(option(MI_OPTION_INFORM_GET) != MI_VALUE_TREE)
        {
            option(MI_OPTION_INFORM, MI_VALUE_TREE);
        }
    }
    else
    {
        if(option(MI_OPTION_INFORM_GET) != MI_VALUE_HTML)
        {
            option(MI_OPTION_INFORM, MI_VALUE_HTML);
        }
    }
    return option(MI_OPTION_LANGUAGE, toStd(language_list));
}

QString MediaInfoLoader::format(const QString &a_format)
{
    if(option(MI_OPTION_INFORM_GET) != a_format)
    {
        return option(MI_OPTION_INFORM, toStd(a_format));
    }
    return QT_EMPTY;
}

QString MediaInfoLoader::format(EFORMAT a_format)
{
    QString info;

    switch(a_format)
    {
    case eFORMAT_TREE:
    default:
        info = format(fromStd(MI_VALUE_TREE));
        break;
    case eFORMAT_CSV:
        info = format(fromStd(MI_VALUE_CSV));
        break;
    case eFORMAT_HTML:
        info = format(fromStd(MI_VALUE_HTML));
        break;
    case eFORMAT_XML:
        info = format(fromStd(MI_VALUE_XML));
        break;
    case eFORMAT_MAXML:
        info = format(fromStd(MI_VALUE_MAXML));
        break;
    case eFORMAT_JSON:
        info = format(fromStd(MI_VALUE_JSON));
        break;
    case eFORMAT_EBUCORE_1_8_PS:
        info = format(fromStd(MI_VALUE_EBUCORE_1_8_PS));
        break;
    case eFORMAT_EBUCORE_1_8_SP:
        info = format(fromStd(MI_VALUE_EBUCORE_1_8_SP));
        break;
    case eFORMAT_EBUCORE_1_8_PS_JSON:
        info = format(fromStd(MI_VALUE_EBUCORE_1_8_PS_JSON));
        break;
    case eFORMAT_EBUCORE_1_8_SP_JSON:
        info = format(fromStd(MI_VALUE_EBUCORE_1_8_SP_JSON));
        break;
    case eFORMAT_EBUCORE_1_6:
        info = format(fromStd(MI_VALUE_EBUCORE_1_6));
        break;
    case eFORMAT_FIMS_1_3:
        info = format(fromStd(MI_VALUE_FIMS_1_3));
        break;
    case eFORMAT_MPEG_7:
        info = format(fromStd(MI_VALUE_MPEG_7));
        break;
    case eFORMAT_PBCORE_2_1:
        info = format(fromStd(MI_VALUE_PBCORE_2_1));
        break;
    case eFORMAT_PBCORE_2_0:
        info = format(fromStd(MI_VALUE_PBCORE_2_0));
        break;
    case eFORMAT_PBCORE_1_2:
        info = format(fromStd(MI_VALUE_PBCORE_1_2));
        break;
    case eFORMAT_NISO_Z39_87:
        info = format(fromStd(MI_VALUE_NISO_Z39_87));
        break;
    }
    return info;
}
