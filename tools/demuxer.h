#ifndef DEMUXER_H
#define DEMUXER_H

#include <QWidget>
#include <QProcess>
#include "std_watcher.h"
#include "std_manager.h"
#include "../job/job_chef.h"

class Demuxer;
class MainWindow;
class JobChef;

namespace Ui {
class Demuxer;
}

class DemuxerItem
{
public:
    DemuxerItem()
    {
        this->clear();
    }

    enum EMEDIA_TYPE {
        eMEDIA_TYPE_UNSPECIFIED,
        eMEDIA_TYPE_VIDEO,
        eMEDIA_TYPE_AUDIO,
        eMEDIA_TYPE_SUBTITLE,
        eMEDIA_TYPE_CHAPTER,
        eMEDIA_TYPE_ATTACHMENT,
        eMEDIA_TYPE_TAG,
        eMEDIA_TYPE_OTHER,
        eMEDIA_TYPE_DISABLE,        /* Can't demux with this type. */
        eRELOAD_TYPE_MAX,
    };

    void clear(void)
    {
        text.clear();
        track_num = eINDEX_NONE;
        type = eMEDIA_TYPE_UNSPECIFIED;
        type_track_num = eINDEX_NONE;
        delay.clear();
        track_info.clear();
        ext.clear();
        output.clear();
    }

    int track_num;        /* Default track number  */
    EMEDIA_TYPE type;     /* Track type            */
    int type_track_num;   /* Type track number     */
    QString text;         /* Item track text       */
    QString delay;        /* Delay Millisecond     */
    QString track_info;   /* Track info            */
    QString ext;          /* Output ext            */
    QString output;       /* Force output filename */
};

class Demuxer : public QWidget
{
    Q_OBJECT

public:
    explicit Demuxer(QWidget *parent = 0);
    ~Demuxer();
    friend class MainWindow;
    class MainWindow *mainUi;

    enum ERELOAD_TYPE {
        eRELOAD_TYPE_FFMPEG,
        eRELOAD_TYPE_EAC3TO,
        eRELOAD_TYPE_MKVEXTRACT,
        eRELOAD_TYPE_TSDEMUXER,
        eRELOAD_TYPE_CAPTION2ASS,
        eRELOAD_TYPE_MAX,
    };

    void reload(ERELOAD_TYPE a_reload_type, QString a_filename);
    void reloadInfo(ERELOAD_TYPE a_reload_type);
    void setOutput(ERELOAD_TYPE a_reload_type, QString a_filename);
    void insertInfo(void);
    void abortJob(void);
    void viewLog(JobChef::EJOB_LOG_TYPE a_log_type, QString a_log);
    QProcess m_process_job_encoder;
    QString m_track_raw;
    QMap<int, QString> m_track_map;
    QList<DemuxerItem> m_items;

private:
    Ui::Demuxer *ui;
    void setupUi(void);
    void reloadParamUi(ERELOAD_TYPE a_reload_type);
    QString getEac3toDelayMillisecond(QString a_track_info = QString());
    QString getEac3toExt(QString a_track_info = QString());
    QString getMkvextractAttachmentOutput(QString a_track_info);
    QString getMkvextractSubtitlesExt(QString a_track_info);
    QString getOutput(QString a_input, DemuxerItem a_item);
    bool isItemModule(void);

private slots:
    /*Encoder Process*/
    virtual void slotEncoderProcessStarted();
    virtual void slotEncoderProcessReadyReadStandardError();
    virtual void slotEncoderProcessReadyReadStandardOutput();
    virtual void slotEncoderProcessFinished(int a_exitCode, QProcess::ExitStatus a_exitStatus);
    virtual void slotEncoderProcessError(QProcess::ProcessError a_error);
    /*Loading Process*/
    virtual void slotStartLoading(void);
    virtual void slotStopLoading(void);

    void on_comboBoxDemuxerFormat_currentIndexChanged(int a_index);
    void on_buttonDemuxerStart_clicked();
    void on_listWidgetTrack_currentRowChanged(int a_row);
    void on_comboBoxDemuxerParam_currentIndexChanged(int a_index);
    void on_buttonDemuxerVideoInput_clicked();
    void on_buttonDemuxerOutput_clicked();
};

#endif // DEMUXER_H
