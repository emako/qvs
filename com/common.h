#ifndef COMMON_H
#define COMMON_H

#include <QDragEnterEvent>
#include <QDragMoveEvent>
#include <QDropEvent>
#include <QMimeData>
#include <QString>
#include <QFileInfoList>
#include <QFileInfo>
#include <QFile>
#include <QDir>
#include <QProcess>
#include <QObject>
#include <QUuid>
#include <QTableWidget>
#include <QClipboard>
#include <QTextCursor>
#include <QPlainTextEdit>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonArray>
#include <QCryptographicHash>
#include <QMessageBox>
#include <QDateTime>
#include <QResource>
#include <QApplication>
#include <QDebug>

#include <windows.h>

#include "preferences.h"

#define KB (1024)
#define MB (KB * KB)
#define GB (MB * KB)
#define MINUTE (60)
#define HOUR (MINUTE * MINUTE)
#define SECOND_TO_MILLISECOND_UNIT (1000)
#define NUL (0)
#define QT_PASS do{}while(false)

static const char QT_EMPTY[]          = "";
static const char QT_BLANK[]          = " ";
static const char QT_EXT_SPLITE[]     = ".";
static const char QT_CSV_SPLITE[]     = ",";
static const char QT_PATH_SPLITE[]    = ";";
static const char QT_COLON[]          = ":";
static const char QT_SQM[]            = "'";
static const char QT_PIPE[]           = "|";
static const char QT_HYPHEN[]         = "-";
static const char QT_PARENTHESES_L[]  = "(";
static const char QT_PARENTHESES_R[]  = ")";
static const char QT_BRACKET_L[]      = "{";
static const char QT_BRACKET_R[]      = "}";
static const char QT_BIKKURI_MARK[]   = "!";
static const char QT_NOR_PATH_SPR[]   = "/";
static const char QT_EQUAL[]          = "=";
static const char QT_DOS_PATH_SPR[]   = "\\";
static const char QT_META[]           = "\b";
static const char QT_NOR_EOL[]        = "\n";
static const char QT_OTR_EOL[]        = "\r\n";
static const char QT_MAC_EOL[]        = "\r";

class MainWindow;
class JobItem;
class Config;

enum EINDEX : int {
    eINDEX_NONE = -1,
    eINDEX_0 = 0,
    eINDEX_1 = 1,
    eINDEX_2 = 2,
    eINDEX_3 = 3,
    eINDEX_4 = 4,
    eINDEX_5 = 5,
    eINDEX_6 = 6,
    eINDEX_7 = 7,
    eINDEX_8 = 8,
    eINDEX_9 = 9,
    eINDEX_10 = 10,
    eINDEX_16 = 16,
    eINDEX_24 = 24,
    eINDEX_32 = 32,
    eINDEX_100 = 100,
    eINDEX_1000 = 1000,
    eINDEX_MAX,
};

enum EBOOL {
    eFALSE   = false,
    eTRUE    = true,
    eDISABLE = false,
    eENABLE  = true,
    eOK      = true,
    eNG      = true,
};

namespace qvs
{
    bool isFileExist(const QString &a_filename);
    QString getFileExt(const QString &a_filename);
    QString chgFileExt(const QString &a_filename, QString a_ext);
    QString delFileExt(const QString &a_filename);
    QString getFileText(const QString &a_filename);
    bool setFileText(const QString &a_filename, const QString &a_text);
    QString timeToString(double a_seconds, bool a_fullFormat = false);      /* For Time Line Slider */

    QString fromStdBasicWString(const std::basic_string<wchar_t> &a_str);
    std::basic_string<wchar_t> toStdBasicWString(const QString &a_str);

    QString fromStdBasicString(const std::basic_string<char> &a_str);
    std::basic_string<char> toStdBasicString(const QString &a_str);

    QString convertFramesToTimecode(double a_frames, double a_fps);
    double convertFramesToTime(double a_frames, double a_fps);
    QString convertSecondToTimecode(double a_timeSec);
}

class Common : public QObject
{
    Q_OBJECT
public:
    explicit Common(QObject *parent = nullptr);
    ~Common();
    class MainWindow *mainUi;
    void loadCommonConfig(void);

    enum ESHUTDOWN {
        eSHUTDOWN_NOTHING,
        eSHUTDOWN_LOG_OUT,
        eSHUTDOWN_POWER_OFF,
        eSHUTDOWN_REBOOT,
        eSHUTDOWN_SLEEP,
        eSHUTDOWN_ABORT_POWER_OFF,
        eSHUTDOWN_FORCE_POWER_OFF,
        eSHUTDOWN_MAX,
    };

    enum EURL {
        eURL_HOME_PAGE,
        eURL_GITHUB,
        eURL_OFFICIAL_X264,
        eURL_OFFICIAL_X265,
        eURL_DL_X264_1,
        eURL_DL_X264_2,
        eURL_DL_X264_3,
        eURL_DL_X265_1,
        eURL_DL_X265_2,
        eURL_DL_X265_3,
        eURL_DL_X265_4,
        eURL_DL_AVS_32,
        eURL_DL_AVS_64,
        eURL_DL_AVS_PLUS,
        eURL_DL_VS,
        eURL_DOC_X264,
        eURL_DOC_X265,
        eURL_DOC_AVS,
        eURL_DOC_VS,
        eURL_MAX,
    };

    const char *c_shotdown2arg[eSHUTDOWN_MAX] = {QT_EMPTY, "-l", "-s", "-r", "-h", "-a", "-f"};
    const char *c_urls[Common::eURL_MAX] = {
        "https://github.com/emako/qvs/releases",                            /* eURL_HOME_PAGE */
        "https://github.com/emako/qvs/releases",                            /* eURL_GITHUB */
        "http://www.videolan.org/developers/x264.html",                     /* eURL_OFFICIAL_X264 */
        "http://www.videolan.org/developers/x265.html",                     /* eURL_OFFICIAL_X265 */
        "http://download.videolan.org/pub/x264/binaries",                   /* eURL_DL_X264_1 */
        "http://komisar.gin.by/",                                           /* eURL_DL_X264_2 */
        "http://www.free-codecs.com/x264_video_codec_download.htm",         /* eURL_DL_X264_3 */
        "http://x265.ru/en/builds/",                                        /* eURL_DL_X265_1 */
        "https://www.mediafire.com/?6lfp2jlygogwa",                         /* eURL_DL_X265_2 */
        "http://builds.x265.eu",                                            /* eURL_DL_X265_3 */
        "http://www.free-codecs.com/x265_hevc_encoder_download.htm",        /* eURL_DL_X265_4 */
        "https://sourceforge.net/projects/avisynth2/files/AviSynth%202.6",  /* eURL_DL_AVS_32 */
        "http://forum.doom9.org/showthread.php?t=152800",                   /* eURL_DL_AVS_64 */
        "http://www.avs-plus.net",                                          /* eURL_DL_AVS_PLUS */
        "http://www.vapoursynth.com",                                       /* eURL_DL_VS */
        "http://en.wikibooks.org/wiki/MeGUI/x264_Settings",                 /* eURL_DOC_X264 */
        "http://x265.readthedocs.org/en/default",                           /* eURL_DOC_X265 */
        "http://avisynth.nl/index.php/Main_Page#Usage",                     /* eURL_DOC_AVS */
        "http://www.vapoursynth.com/doc",                                   /* eURL_DOC_VS */
    };

    QFileInfoList getFileList(QString a_path);
    QString findFirstFilePath(QString a_filename, QString a_path = QDir::currentPath());
    static bool isFile(QString a_filename);

    QList<DWORD> getProcessID(QString a_filename);
    QList<DWORD> getProcessID(QStringList a_filename_list);
    BOOL setPriortyClass(DWORD a_pid, DWORD a_priorityClass);

    void moveRow(QList<class JobItem> *a_list, int a_from, int a_to);
    void moveRow(QTableWidget *a_pTable, int a_from, int a_to);

    QString beautifyText(QString a_text, QString a_color = "red");
    int hadNumber(QString a_text);

    QJsonObject getJsonFromString(const QString a_string);
    QString getStringFromJson(const QJsonObject& a_json);

    QString getHashMd5(QString a_filename);
    QString toUpperFirstStr(QString a_str);
    void copyPath(void);

    QString getAudioFileDelayValueString(QString a_filename);
    int getAudioFileDelayValue(QString a_filename);

    ESHUTDOWN m_shutdown;
    void systemShutdown(ESHUTDOWN a_shotdown);
    void systemInfoPrint(void);

    bool isVaildIndex(int a_length, int a_index);
    int getStringListIndex(QStringList a_list, QString a_string);

    QProcess m_process;
    QString m_process_out;

public slots:
    virtual void openUrl(QString a_url);
    virtual void openUrl(EURL a_url);
    virtual void openUrlCheckForUpdates(void);
    virtual void openUrlWebX264(void);
    virtual void openUrlWebX265(void);
    virtual void openUrlWebX264VideoLAN(void);
    virtual void openUrlWebX264Komisar(void);
    virtual void openUrlWebX264FreeCodecs(void);
    virtual void openUrlWebX265Fllear(void);
    virtual void openUrlWebX265LigH(void);
    virtual void openUrlWebX265Snowfag(void);
    virtual void openUrlWebX265FreeCodecs(void);
    virtual void openUrlWebAvisynth32(void);
    virtual void openUrlWebAvisynth64(void);
    virtual void openUrlWebAvisynthPlus(void);
    virtual void openUrlWebVapourSynth(void);
    virtual void openUrlOnlineDocX264(void);
    virtual void openUrlOnlineDocX265(void);
    virtual void openUrlWebAvsWiki(void);
    virtual void openUrlWebVapourSynthDocs(void);

protected slots:
    virtual void slotProcessReadyReadStandardError();
    virtual void slotProcessReadyReadStandardOutput();

};

#endif // COMMON_H
