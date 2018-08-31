#ifndef MEDIAINFO_LOADER_H
#define MEDIAINFO_LOADER_H

#include "mediainfo_define.h"
#include "../com/common.h"

using namespace MediaInfoDLL;

#define __TR(__x) QObject::tr(__x)
#if defined(UNICODE) || defined(_UNICODE)
    #define toStd(__x) qvs::toStdBasicWString(__x)
    #define fromStd(__x) qvs::fromStdBasicWString(__x)
#else
    #define toStd(__x) qvs::toStdBasicString(__x)
    #define fromStd(__x) qvs::fromStdBasicString(__x)
#endif

#define MEDIA_PROP_COMPLETE __T("Complete")
#define MEDIA_PROP_FORMAT __T("Format")
#define MEDIA_PROP_WIDTH __T("Width")
#define MEDIA_PROP_HEIGHT __T("Height")
#define MEDIA_PROP_FRAME_RATE_MODE __T("FrameRateMode")
#define MEDIA_PROP_FRAME_RATE __T("FrameRate")
#define MEDIA_PROP_FRAME_RATE_NUM __T("FrameRate_Num")
#define MEDIA_PROP_FRAME_RATE_DEN __T("FrameRate_Den")
#define MEDIA_PROP_FRAME_COUNT __T("FrameCount")
#define MEDIA_PROP_DURATION __T("Duration")
#define MEDIA_PROP_BIT_RATE __T("BitRate")
#define MEDIA_PROP_COLOR_SPACE __T("ColorSpace")
#define MEDIA_PROP_CHROMA_SUBSAMPLING __T("ChromaSubsampling")
#define MEDIA_PROP_BIT_DEPTH __T("BitDepth")
#define MEDIA_PROP_SCAN_TYPE __T("ScanType")
#define MEDIA_PROP_SCAN_ORDER __T("ScanOrder")
#define MEDIA_PROP_TRUE __T("1")
#define MEDIA_PROP_FALSE __T("0")
#define MEDIA_UNKNOWED_FORMAT __TR("UNKNOWED")

namespace MediaInfoDLL {
class MediaInfo;
}

class MediaInfoLoader
{
public:
    MediaInfoLoader();
    MediaInfoLoader(const QString &a_filename);

    enum EMEDIA_PROP {
        eMEDIA_PROP_ALL,
        eMEDIA_PROP_ALL_COMPLETE,
        eMEDIA_PROP_FORMAT_CODE,
        eMEDIA_PROP_FORMAT,
        eMEDIA_PROP_WIDTH,
        eMEDIA_PROP_HEIGHT,
        eMEDIA_PROP_FRAME_RATE_MODE,
        eMEDIA_PROP_FRAME_RATE,
        eMEDIA_PROP_FRAME_RATE_NUM,
        eMEDIA_PROP_FRAME_RATE_DEN,
        eMEDIA_PROP_FRAME_COUNT,
        eMEDIA_PROP_DURATION,
        eMEDIA_PROP_BIT_RATE,
        eMEDIA_PROP_COLOR_SPACE,
        eMEDIA_PROP_CHROMA_SUBSAMPLING,
        eMEDIA_PROP_BIT_DEPTH,
        eMEDIA_PROP_SCAN_TYPE,
        eMEDIA_PROP_SCAN_ORDER,
        eMEDIA_PROP_MAX,
    };

    enum ESTREAM_TYPE {
        eSTREAM_TYPE_GENERAL,         /* StreamKind = General */
        eSTREAM_TYPE_VIDEO,           /* StreamKind = Video   */
        eSTREAM_TYPE_AUDIO,           /* StreamKind = Audio   */
        eSTREAM_TYPE_TEXT,            /* StreamKind = Text    */
        eSTREAM_TYPE_OTHER,           /* StreamKind = Other   */
        eSTREAM_TYPE_IMAGE,           /* StreamKind = Image   */
        eSTREAM_TYPE_MENU,            /* StreamKind = Menu    */
        eSTREAM_TYPE_MAX,
    };

    size_t open(const QString &a_filename);
    size_t open(void);
    QString get(EMEDIA_PROP a_prop = eMEDIA_PROP_ALL, ESTREAM_TYPE a_streamType = eSTREAM_TYPE_VIDEO, size_t a_streamNumber = (size_t)eINDEX_0);
    QString get(String a_prop, stream_t a_streamType = Stream_Video, size_t a_streamNumber = (size_t)eINDEX_0);
    virtual void close(void);

private:
    MediaInfoDLL::MediaInfo m_mediainfo;
    QString m_filename;
};

#endif // MEDIAINFO_LOADER_H
