#include "mediainfo_prober.h"
#include "mediainfo_pixfmt.hpp"

#define FF_COMPONENT(name, NAME) #name, LIB##NAME##_VERSION_INT, name##_version(), name##_configuration(), name##_license()

MediaInfoProber::MediaInfoProber()
    : m_pFormatCtx(nullptr)
{
}

MediaInfoProber::MediaInfoProber(const QString &a_filename)
    : m_pFormatCtx(nullptr)
    , m_filename(a_filename)
{
    open();
}

MediaInfoProber::~MediaInfoProber()
{
    close();
}

bool MediaInfoProber::open(const QString &a_filename)
{
    close();

    m_pFormatCtx = avformat_alloc_context();

    if (avformat_open_input(&m_pFormatCtx, a_filename.toLocal8Bit().data(), nullptr, nullptr) != eINDEX_0)
    {
        qWarning() << "Open file failed.";
        return false;
    }

    if (avformat_find_stream_info(m_pFormatCtx, nullptr) < eINDEX_0)
    {
        qWarning() << "Could't find stream infomation.";
        close();
        return false;
    }
    return true;
}

bool MediaInfoProber::open(void)
{
    close();
    return open(m_filename);
}

QString MediaInfoProber::inform(void)
{
    // TODO
	return "";
}

AVFormatContext *MediaInfoProber::get(void)
{
    return m_pFormatCtx;
}

void MediaInfoProber::close(void)
{
    if (m_pFormatCtx != nullptr)
    {
        avformat_close_input(&m_pFormatCtx);
        avformat_free_context(m_pFormatCtx);
        m_pFormatCtx = nullptr;
    }
}

QString MediaInfoProber::version(void)
{
    struct depend_component
	{
		const char* lib;
		unsigned build_version;
		unsigned rt_version;
		const char *config;
		const char *license;
    };
	
	static const depend_component components[] =
	{
		{ FF_COMPONENT(avutil, AVUTIL)     },
		{ FF_COMPONENT(avcodec, AVCODEC)   },
		{ FF_COMPONENT(avformat, AVFORMAT) },
		{ FF_COMPONENT(avfilter, AVFILTER) },
		{ nullptr, 0, 0, nullptr, nullptr  },
	};
	
	QString ver;

	ver.sprintf("%u.%u.%u"
		, QTAV_VERSION_MAJOR(components[2].rt_version)
		, QTAV_VERSION_MINOR(components[2].rt_version)
		, QTAV_VERSION_PATCH(components[2].rt_version)
	);

	return ver;
}

QString MediaInfoProber::getPixfmt(const AVPixelFormat &a_pixfmt)
{
	return MediaInfoPixfmt::getPixelFormat(a_pixfmt);
}

int64_t MediaInfoProber::getDuration()
{
    return m_pFormatCtx->duration / static_cast<int64_t>(AV_TIME_BASE);
}
