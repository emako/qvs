#ifndef MEDIAINFO_LOADER_H
#define MEDIAINFO_LOADER_H

#include "mediainfo_define.h"
#include "mediainfo_list.h"
#include "../com/common.h"

using namespace MediaInfoDLL;

#if defined(UNICODE) || defined(_UNICODE)
    #define toStd(__x) qvs::toStdBasicWString(__x)
    #define fromStd(__x) qvs::fromStdBasicWString(__x)
#else
    #define toStd(__x) qvs::toStdBasicString(__x)
    #define fromStd(__x) qvs::fromStdBasicString(__x)
#endif

#define MEDIA_PROP_FORMAT MI_VIDEO_FORMAT
#define MEDIA_PROP_WIDTH MI_VIDEO_WIDTH
#define MEDIA_PROP_HEIGHT MI_VIDEO_HEIGHT
#define MEDIA_PROP_FRAME_RATE_MODE MI_VIDEO_FRAMERATE_MODE
#define MEDIA_PROP_FRAME_RATE MI_VIDEO_FRAMERATE
#define MEDIA_PROP_FRAME_RATE_NUM MI_VIDEO_FRAMERATE_NUM
#define MEDIA_PROP_FRAME_RATE_DEN MI_VIDEO_FRAMERATE_DEN
#define MEDIA_PROP_FRAME_COUNT MI_VIDEO_FRAMECOUNT
#define MEDIA_PROP_DURATION MI_VIDEO_DURATION
#define MEDIA_PROP_BIT_RATE MI_VIDEO_BITRATE
#define MEDIA_PROP_COLOR_SPACE MI_VIDEO_COLORSPACE
#define MEDIA_PROP_CHROMA_SUBSAMPLING MI_VIDEO_CHROMASUBSAMPLING
#define MEDIA_PROP_BIT_DEPTH MI_VIDEO_BITDEPTH
#define MEDIA_PROP_SCAN_TYPE MI_VIDEO_SCANTYPE
#define MEDIA_PROP_SCAN_ORDER MI_VIDEO_SCANORDER

#define MEDIA_LANGUAGE_DEFAULT QObject::tr("en")

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

    enum EFORMAT {
        eFORMAT_TREE,
        eFORMAT_INI = eFORMAT_TREE,   /* for traversal */
        eFORMAT_TEXT = eFORMAT_TREE,
        eFORMAT_CSV,
        eFORMAT_HTML,
        eFORMAT_XML,
        eFORMAT_MAXML,
        eFORMAT_JSON,
        eFORMAT_EBUCORE_1_8_PS,
        eFORMAT_EBUCORE_1_8_SP,
        eFORMAT_EBUCORE_1_8_PS_JSON,
        eFORMAT_EBUCORE_1_8_SP_JSON,
        eFORMAT_EBUCORE_1_6,
        eFORMAT_FIMS_1_3,
        eFORMAT_MPEG_7,
        eFORMAT_PBCORE_2_1,
        eFORMAT_PBCORE_2_0,
        eFORMAT_PBCORE_1_2,
        eFORMAT_NISO_Z39_87,
    };

    QString option(const String &a_option, const String &a_value = MI_VALUE_EMPTY);

    size_t open(const QString &a_filename);
    size_t open(void);

    QString traversal(EFORMAT a_format);

    QString inform(void);
    QString inform(bool a_complete);
    QString inform(bool a_complete, EFORMAT a_format);

    QString get(EMEDIA_PROP a_prop = eMEDIA_PROP_ALL, ESTREAM_TYPE a_streamType = eSTREAM_TYPE_VIDEO, size_t a_streamNumber = (size_t)eINDEX_0);
    QString get(const String & a_param, stream_t a_streamType = Stream_Video, size_t a_streamNumber = (size_t)eINDEX_0, info_t a_infoKind = Info_Text, info_t a_SearchKind = Info_Name);
    QString get(size_t a_param, stream_t a_streamType = Stream_Video, size_t a_streamNumber = (size_t)eINDEX_0, info_t a_infoKind = Info_Text);

    size_t count(stream_t a_streamType = Stream_Video, size_t a_streamNumber = (size_t)eINDEX_NONE);

    virtual void close(void);

    QString version(void);
    QString language(const QString &a_language = MEDIA_LANGUAGE_DEFAULT);

    QString format(const QString &a_format);
    QString format(EFORMAT a_format);

private:
    MediaInfoDLL::MediaInfo m_mediainfo;
    QString m_filename;
};

#endif // MEDIAINFO_LOADER_H
