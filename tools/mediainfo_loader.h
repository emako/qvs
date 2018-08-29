#ifndef MEDIAINFO_LOADER_H
#define MEDIAINFO_LOADER_H

#include "mediaInfo_dll.h"
#include "../com/common.h"

#define _Q(a) qvs::fromStdBasicWString(a)

#define MEDIA_PROP_COMPLETE L"Complete"
#define MEDIA_PROP_FORMAT L"Format"
#define MEDIA_PROP_WIDTH L"Width"
#define MEDIA_PROP_HEIGHT L"Height"
#define MEDIA_PROP_FRAME_RATE_MODE L"FrameRateMode"
#define MEDIA_PROP_FRAME_RATE L"FrameRate"
#define MEDIA_PROP_FRAME_RATE_NUM L"FrameRate_Num"
#define MEDIA_PROP_FRAME_RATE_DEN L"FrameRate_Den"
#define MEDIA_PROP_FRAME_COUNT L"FrameCount"
#define MEDIA_PROP_DURATION L"Duration"
#define MEDIA_PROP_BIT_RATE L"BitRate"
#define MEDIA_PROP_COLOR_SPACE L"ColorSpace"
#define MEDIA_PROP_CHROMA_SUBSAMPLING L"ChromaSubsampling"
#define MEDIA_PROP_BIT_DEPTH L"BitDepth"
#define MEDIA_PROP_SCAN_TYPE L"ScanType"
#define MEDIA_PROP_SCAN_ORDER L"ScanOrder"

#define MEDIA_PROP_TRUE L"1"
#define MEDIA_PROP_FALSE L"0"

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
    virtual void close(void);

private:
    MediaInfoDLL::MediaInfo m_mediainfo;
    QString m_filename;
};

#endif // MEDIAINFO_LOADER_H
