#ifndef COMMON_H
#define COMMON_H

#include "preferences.h"

#include <Windows.h>
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
#include <QListWidget>
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
#include <QTextCodec>
#include <QtMath>

#ifdef max
# undef max /* Undefind max from windows header,
             * because it will raise the compiling failed. */
#endif

#define APPINSTANCE "qvs_running"
#define NULLSTR QString()
#define NULLSTRS QStringList()

#define KB (1024)
#define MB (KB * KB)
#define GB (MB * KB)

#define MINUTE (60)
#define HOUR (MINUTE * MINUTE)

#define SECOND_TO_MILLISECOND_UNIT (1000)
#define SECOND_TO_MILLISECOND_UNIT_F static_cast<double>(SECOND_TO_MILLISECOND_UNIT)

#define TIME_FORMAT "HH:mm:ss.zzz"

#define NUL 0
#define ARI 1

#define QT_PASS do{}while(false)
#define PASS QT_PASS

#if (QT_VERSION >= QT_VERSION_CHECK(5, 0, QT_VERSION_PATCH))
#define QT_VERSION_TOO_LOW NUL
#else
#define QT_VERSION_TOO_LOW ARI
#endif

#define COLOR_WHITE_HEX     #FFFFFF //RGB(255, 255, 255)
#define COLOR_SILVER_HEX    #C0C0C0	//RGB(192, 192, 192)
#define COLOR_GRAY_HEX      #808080	//RGB(128, 128, 128)
#define COLOR_BLACK_HEX     #000000	//RGB(0, 0, 0)
#define COLOR_RED_HEX       #FF0000	//RGB(255, 0, 0)
#define COLOR_MAROON_HEX	#800000	//RGB(128, 0, 0)
#define COLOR_YELLOW_HEX	#FFFF00	//RGB(255, 255, 0)
#define COLOR_OLIVE_HEX     #808000	//RGB(128, 128, 0)
#define COLOR_LIME_HEX      #00FF00	//RGB(0, 255, 0)
#define COLOR_GREEN_HEX     #008000	//RGB(0, 128, 0)
#define COLOR_AQUA_HEX      #00FFFF	//RGB(0, 255, 255)
#define COLOR_TEAL_HEX      #008080	//RGB(0, 128, 128)
#define COLOR_BLUE_HEX      #0000FF	//RGB(0, 0, 255)
#define COLOR_NAVY_HEX	    #000080	//RGB(0, 0, 128)
#define COLOR_FUCHSIA_HEX	#FF00FF	//RGB(255, 0, 255)
#define COLOR_PURPLE_HEX	#800080	//RGB(128, 0, 128)

#define COLOR_LOGGING_DEFAULT QColor(0, 0, 0)
#define COLOR_LOGGING_INFO QColor(0, 0, 128)
#define COLOR_LOGGING_WARN QColor(255, 0, 0)
#define COLOR_LOGGING_STATUS QColor(0, 128, 128)
#define COLOR_LOGGING_STD_ERROR QColor(135, 45, 90)
#define COLOR_LOGGING_STD_OUTPUT QColor(128, 0, 128)

#define MESSAGE_ERROR QObject::tr("Error")
#define MESSAGE_FATAL QObject::tr("Fatal")
#define MESSAGE_FAILED QObject::tr("Failed")
#define MESSAGE_REJECTION QObject::tr("Rejection")
#define MESSAGE_QUESTION QObject::tr("Question")
#define MESSAGE_WARNING QObject::tr("Warning")
#define MESSAGE_INFORMATION QObject::tr("Information")
#define MESSAGE_ARE_YOU_BAKA QObject::tr("Are you BAKA?")
#define MESSAGE_DONE QObject::tr("Done")

#define FONT_SIZE_DEFAULT 9
#define FONT_DEFAULT QFont(QObject::tr("Consolas"), FONT_SIZE_DEFAULT)
#define FONT_DEFAULT_BAK QFont(QObject::tr("Yu Gothic UI"), FONT_SIZE_DEFAULT)

#define CR QT_MAC_EOL
#define LF QT_NOR_EOL
#define EOL QT_OTR_EOL

#define SET_FONT_BOLD(WIDGET,BOLD) do { QFont _font = WIDGET->font(); _font.setBold(BOLD); WIDGET->setFont(_font); } while(0)
#define SET_TEXT_COLOR(WIDGET,COLOR) do { QPalette _palette = WIDGET->palette(); _palette.setColor(QPalette::WindowText, (COLOR)); _palette.setColor(QPalette::Text, (COLOR)); WIDGET->setPalette(_palette); } while(0)

static const char QT_EMPTY[]            = "";
static const char QT_BLANK[]            = " ";
static const char QT_EXT_SPLITE[]       = ".";
static const char QT_CSV_SPLITE[]       = ",";
static const char QT_PATH_SPLITE[]      = ";";
static const char QT_COLON[]            = ":";
static const char QT_SQM[]              = "'";
static const char QT_PIPE[]             = "|";
static const char QT_HYPHEN[]           = "-";
static const char QT_PARENTHESES_L[]    = "(";
static const char QT_PARENTHESES_R[]    = ")";
static const char QT_BRACKET_L[]        = "{";
static const char QT_BRACKET_R[]        = "}";
static const char QT_BIKKURI_MARK[]     = "!";
static const char QT_NOR_PATH_SPR[]     = "/";
static const char QT_EQUAL[]            = "=";
static const char QT_ASTERISK[]			= "*";
static const char QT_QUE_MARK[]			= "?";
static const char QT_LESS_THAN[]		= "<";
static const char QT_GREATER_THAN[]		= ">";
static const char QT_TAB[]				= "\t";
static const char QT_DOS_PATH_SPR[]     = "\\";
static const char QT_DOUBLE_QUOT_MARK[] = "\"";
static const char QT_META[]             = "\b";
static const char QT_NOR_EOL[]          = "\n";
static const char QT_OTR_EOL[]          = "\r\n";
static const char QT_MAC_EOL[]          = "\r";

class MainWindow;
class JobItem;
class Config;

enum EINDEX : int
{
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
    eINDEX_12 = 12,
    eINDEX_16 = 16,
    eINDEX_24 = 24,
    eINDEX_30 = 30,
    eINDEX_32 = 32,
    eINDEX_100 = 100,
    eINDEX_1000 = 1000,
    eINDEX_MAX,
};

enum EBOOL
{
    eFALSE   = false,
    eTRUE    = true,
    eDISABLE = false,
    eENABLE  = true,
    eOK      = true,
    eNG      = true,
};

namespace qvs
{
    void loadFonts(void);

    bool isFileExist(const QString &a_filename);
    bool isFile(const QString &a_filename);

    QFileInfoList getFileList(QString a_path);
    QString findFirstFilePath(QString a_filename, QString a_path = QDir::currentPath());

    QString getFileExt(const QString &a_filename);
    QString chgFileExt(const QString &a_filename, QString a_ext);
    QString delFileExt(const QString &a_filename);

    QString getFileText(const QString &a_filename, const QString &a_codec = NULLSTR);
    bool setFileText(const QString &a_filename, const QString &a_text);

    QByteArray getResource(const QString &a_filename);
    QString fromResource(const QString &a_filename);

    QString fromDouble(double a_number, int a_prec = eINDEX_3);

    QString fromSecondTime(double a_seconds, bool a_fullFormat = false);
    QString fromTime(double a_seconds);
    double toTime(QString a_secondsStr);

    QString currentTime(void);
    QString currentDateTime(void);

    QString fromStdBasicWString(const std::basic_string<wchar_t> &a_str);
    std::basic_string<wchar_t> toStdBasicWString(const QString &a_str);

    QString fromStdBasicString(const std::basic_string<char> &a_str);
    std::basic_string<char> toStdBasicString(const QString &a_str);

    QString fromHtml(const QString &a_str);
    QString toHtml(const QString &a_str, QColor a_color = QColor(Qt::black), bool logging = false);
    QString toHtmlText(const QString &a_str);

    QString toNormalEol(const QString &a_str);
	QString toFilename(const QString &a_str);
	QString toFilename2(const QString &a_filename);

    QString convertFramesToTimecode(double a_frames, double a_fps);
    double convertFramesToTime(double a_frames, double a_fps);
    QString convertSecondToTimecode(double a_timeSec);

    QJsonObject getJsonFromString(const QString a_string);
    QString getStringFromJson(const QJsonObject& a_json);

    QString toStringFirstUpper(QString a_str);

    QStringList getUrlFromText(const QString &a_text);

    template <class T>
    void moveRow(QList<T> *a_list, int a_from, int a_to);
    void moveRow(QList<JobItem> *a_list, int a_from, int a_to);
    void moveRow(QList<QPair<QString, QString>> *a_list, int a_from, int a_to);
    void moveRowUi(QTableWidget *a_pTable, int a_from, int a_to);
    void moveRowUi(QListWidget *a_pList, int a_from, int a_to);
}

class Common : public QObject
{
    Q_OBJECT
public:
    explicit Common(QObject *parent = nullptr);
    ~Common();

    static Common* getInstance(void)
    {
        static Common s_instance;
        return &s_instance;
    }

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

    QList<DWORD> getProcessID(QString a_filename);
    QList<DWORD> getProcessID(QStringList a_filename_list);
    BOOL setPriortyClass(DWORD a_pid, DWORD a_priorityClass);

    QString beautifyText(QString a_text, QString a_color = "red");
    int hadNumber(QString a_text);

    QString getHashMd5(QString a_filename);
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

signals:
	void systemShutdown(void);

public slots:
    virtual void openUrl(QString a_url);

protected slots:
    virtual void slotProcessReadyReadStandardError();
    virtual void slotProcessReadyReadStandardOutput();

};

#endif // COMMON_H
