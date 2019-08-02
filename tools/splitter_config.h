#ifndef SPLITTER_CONFIG_H
#define SPLITTER_CONFIG_H

#include <QDialog>
#include <QMenu>
#include <QMimeData>
#include <QUrl>
#include <QDropEvent>
#include <QFile>
#include <QFileInfo>
#include <QFileDialog>
#include <QCloseEvent>
#include <QDebug>
#include <QFlag>

#include "../com/common.h"
#include "../com/style_sheet.h"
#include "../mediainfo/mediainfo_loader.h"

#define SPLITTER_EXEC_FFMPEG "ffmpeg"
#define SPLITTER_EXEC_FFPROBE "ffprobe"
#define SPLITTER_EXEC_MKVMERGE "mkvmerge"

#define FRAME_SECTION "frame"
#define FRAME_I "I"
#define FRAME_P "P"
#define FRAME_B "B"

#define SPLITTER_DIVIDED_PARTS_TIP(a) qvs::toHtml(QObject::tr("  (It will be divided into %1 parts.)").arg(a), COLOR_LOGGING_STATUS, false)

namespace Ui {
class SplitterConfig;
}

class LineParser;

class SplitterParam
{
public:
    SplitterParam()
    {
		streamType = eSTREAM_TYPE_ALL;
        isMuxed = true;
        fps = 29.970;
        frameCount = eINDEX_0;
        delayMs = eINDEX_0;
        currentStartFrame = eINDEX_0;
        currentEndFrame = eINDEX_0;
        currentStartTime = QTime(eINDEX_0, eINDEX_0);
        currentEndTime = QTime(eINDEX_0, eINDEX_0);
        splittedSize = 4092;
		formatType = eFORMAT_TYPE_FFMPEG;
        isSplittedBaseTimecodes = false;
        isSplittedBaseFrames = true;
        isSplittedBaseSize = false;
        isConfigured = false;
        isKeyFrameSeekFinished = false;
    }

	enum ESTREAM_TYPE : int
	{
		eSTREAM_TYPE_ALL,
		eSTREAM_TYPE_AUDIO,
		eSTREAM_TYPE_VIDEO,
		eSTREAM_TYPE_MAX,
	};

	enum EFORMAT_TYPE : int
	{
		eFORMAT_TYPE_FFMPEG,
		eFORMAT_TYPE_MKVMERGE,
		eFORMAT_TYPE_MAX,
	};

    QString path; // splitted file path.
    QList<QPair<QString, QString>> splittedList; // Format: List<Pair<StartTimecode, EndTimecode>>.
    QList<int> keyFrameList;
    bool isKeyFrameSeekFinished;
	ESTREAM_TYPE streamType;
    bool isMuxed;
    double fps;
    int frameCount;
    int delayMs;
    int currentStartFrame;
    int currentEndFrame;
    QTime currentStartTime;
    QTime currentEndTime;
    int splittedSize;
    EFORMAT_TYPE formatType;
    bool isSplittedBaseTimecodes;
    bool isSplittedBaseFrames;
    bool isSplittedBaseSize;
    bool isConfigured;
};

class SplitterConfig : public QDialog
{
    Q_OBJECT

public:
    explicit SplitterConfig(QDialog *parent = nullptr);
    ~SplitterConfig();

    enum ESPLITTER_CONFIG_MENU
    {
        eSPLITTER_CONFIG_MENU_COPY,
        eSPLITTER_CONFIG_MENU_DELETE,
        eSPLITTER_CONFIG_MENU_CLEAR,
        eSPLITTER_CONFIG_MENU_SEPARATOR_0,
        eSPLITTER_CONFIG_MENU_MOVE_UP,
        eSPLITTER_CONFIG_MENU_MOVE_DOWN,
        eSPLITTER_CONFIG_MENU_SEPARATOR_1,
        eSPLITTER_CONFIG_MENU_IMPORT,
        eSPLITTER_CONFIG_MENU_EXPORT,
        eSPLITTER_CONFIG_MENU_MAX,
    };

	enum ESPLITTER_KEY_FRAMES_MENU
	{
		eSPLITTER_KEY_FRAMES_MENU_OPEN_MEDIA,
		eSPLITTER_KEY_FRAMES_MENU_REQUEST,
		eSPLITTER_KEY_FRAMES_MENU_SEPARATOR_0,
		eSPLITTER_KEY_FRAMES_MENU_COPY,
		eSPLITTER_KEY_FRAMES_MENU_EXPORT,
		eSPLITTER_KEY_FRAMES_MENU_MAX,
	};

    enum EFFPROBE_FORMAT
    {
        eFFPROBE_FORMAT_SECTION,                        // eg. 'frame' in csv format / 'frames' in json format
        eFFPROBE_FORMAT_MEDIA_TYPE,                     // eg. 'video' or 'audio'
        eFFPROBE_FORMAT_STREAM_INDEX,
        eFFPROBE_FORMAT_KEY_FRAME,                      // eg. 1 or 0
        eFFPROBE_FORMAT_PKT_PTS,
        eFFPROBE_FORMAT_PKT_PTS_TIME,
        eFFPROBE_FORMAT_PKT_DTS,
        eFFPROBE_FORMAT_PKT_DTS_TIME,
        eFFPROBE_FORMAT_BEST_EFFORT_TIMESTAMP,
        eFFPROBE_FORMAT_BEST_EFFORT_TIMESTAMP_TIME,
        eFFPROBE_FORMAT_PKT_DURATION,
        eFFPROBE_FORMAT_PKT_DURATION_TIME,
        eFFPROBE_FORMAT_PKT_POS,
        eFFPROBE_FORMAT_PKT_SIZE,
        eFFPROBE_FORMAT_WIDTH,
        eFFPROBE_FORMAT_HEIGHT,
        eFFPROBE_FORMAT_PIX_FMT,                        // eg. 'yuv420p'
        eFFPROBE_FORMAT_SAMPLE_ASPECT_RATIO,            // eg. '1:1'
        eFFPROBE_FORMAT_PICT_TYPE,                      // eg. 'I' or 'P' or 'B'
        eFFPROBE_FORMAT_CODED_PICTURE_NUMBER,
        eFFPROBE_FORMAT_DISPLAY_PICTURE_NUMBER,
        eFFPROBE_FORMAT_INTERLACED_FRAME,               // eg. 0
        eFFPROBE_FORMAT_TOP_FIELD_FIRST,                // eg. 0
        eFFPROBE_FORMAT_REPEAT_PICT,
        eFFPROBE_FORMAT_CHROMA_LOCATION,
        eFFPROBE_FORMAT_MAX,
    };

    enum EFFPROBE_KEY_FRAME_FORMAT
    {
		eFFPROBE_KEY_FRAME_FORMAT_SECTION,              // eg. 'frame' in csv format / 'frames' in json format
		eFFPROBE_KEY_FRAME_FORMAT_KEY_FRAME,            // eg. 1 or 0
		eFFPROBE_KEY_FRAME_FORMAT_PICT_TYPE,            // eg. 'I' or 'P' or 'B'
		eFFPROBE_KEY_FRAME_FORMAT_MAX,
	};

    void reload(const QString &a_filename, bool a_isRequestKeyFrame = true);
    void reload(const SplitterParam &a_param);
	void release(void);
	bool openMediaFile();
	void saveSplitterParam(void);
    QString getImportFilePath(void);
    QString getExportFilePath(void);
	QString getKeyFramesSaveFilePath(void);

    QString createArray(QList<QPair<QString, QString>> a_list);
    QList<QPair<QString, QString>> parseArray(QString a_listStr);
	QString getKeyFramesString(void);

    SplitterParam m_param;

signals:
    void splitterParamUpdated(SplitterParam a_param);

private slots:
	void closeEvent(QCloseEvent *e);
    void dragEnterEvent(QDragEnterEvent* e);
    void dropEvent(QDropEvent* e);
    void keyFrameLogRecived(QString a_log);
    void keyFrameProcessFinished();

    void addItem(void);
    void panelChecked(bool a_checked = false);
    void contextMenuConfigListTriggered(void);
	void contextMenuKeyFrameListTriggered(void);
    void configListContextMenuRequested(const QPoint &a_pos);
	void keyFrameListContextMenuRequested(const QPoint &a_pos);
    void addConfigListIcon();

    void on_buttonAccept_clicked();
    void on_buttonCancel_clicked();
    void on_spinBoxFileSize_valueChanged(int a_value);
    void on_buttonKeyFrames_clicked();
    void on_comboBoxFormat_activated(int a_index);

private:
    Ui::SplitterConfig *ui;
    LineParser *m_pLineParser;
	QUuid m_uidKeyFrame;
    QMenu *m_pContextMenuConfigList;
	QMenu *m_pContextMenuKeyFrameList;
	int m_currentFrameNumber;
};

#endif // SPLITTER_CONFIG_H
