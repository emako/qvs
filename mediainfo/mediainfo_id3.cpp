#include "mediainfo_id3.h"

MediaInfoID3::MediaInfoID3()
    : m_pFormatCtx(nullptr)
{
}

MediaInfoID3::~MediaInfoID3()
{
    close();
}

void MediaInfoID3::close()
{
    if (m_pFormatCtx != nullptr)
    {
        avformat_close_input(&m_pFormatCtx);
        avformat_free_context(m_pFormatCtx);
        m_pFormatCtx = nullptr;
    }
}

bool MediaInfoID3::open(const QString &a_fileName)
{
    AVDictionaryEntry *tags = nullptr;

    m_pFormatCtx = avformat_alloc_context();

    int result = avformat_open_input(&m_pFormatCtx, a_fileName.toLocal8Bit().data(), nullptr, nullptr);

    if (result != 0 || m_pFormatCtx == nullptr)
    {
        qWarning() << "MediaInfoID3::open -> avformat_open_input failed!";
        close();
        return false;
    }

    if (avformat_find_stream_info(m_pFormatCtx, nullptr) < 0)
    {
        qWarning() << "MediaInfoID3::open -> avformat_find_stream_info failed!";
        close();
        return false;
    }

    m_infoMap.clear();
    while ((tags = av_dict_get(m_pFormatCtx->metadata, QT_EMPTY, tags, AV_DICT_IGNORE_SUFFIX)))
    {
        QString keyString = tags->key;
        QString valueString = QString::fromUtf8(tags->value);

        m_infoMap.insert(keyString, valueString);
    }

    m_infoImages.clear();
    for (uint i = 0; i < m_pFormatCtx->nb_streams; ++i)
    {
        if (m_pFormatCtx->streams[i]->disposition & AV_DISPOSITION_ATTACHED_PIC)
        {
            AVPacket pkt = m_pFormatCtx->streams[i]->attached_pic;
            QImage image = QImage::fromData(static_cast<uchar *>(pkt.data), pkt.size);

            m_infoImages.append(image);
        }
    }

    close();

    return true;
}
