#ifndef JOB_CHEF_H
#define JOB_CHEF_H

#include <QObject>
#include "com/common.h"
#include "job_creator.h"

class MainWindow;

class JobChef : public QObject
{
    Q_OBJECT
public:
    explicit JobChef(QObject *parent = nullptr);
    friend class MainWindow;
    class MainWindow *mainUi;

    enum EJOB_STATUS {
        eJOB_STATUS_INITIAL,
        eJOB_STATUS_READY,
        eJOB_STATUS_STARTING,
        eJOB_STATUS_RUNNING,
        eJOB_STATUS_PAUSING,
        eJOB_STATUS_PAUSED,
        eJOB_STATUS_RESUMING,
        eJOB_STATUS_ABORTING,
        eJOB_STATUS_ABORTED,
        eJOB_STATUS_FAILED,
        eJOB_STATUS_WAITING,
        eJOB_STATUS_COMPLETED,
    };

    enum EPROCESS_PRIORITY {
        ePROCESS_PRIORITY_IIDLE          =   IDLE_PRIORITY_CLASS,
        ePROCESS_PRIORITY_BELOW_NORMAL   =   BELOW_NORMAL_PRIORITY_CLASS,
        ePROCESS_PRIORITY_NORMAL         =   NORMAL_PRIORITY_CLASS,
        ePROCESS_PRIORITY_ABOVE_NORMAL   =   ABOVE_NORMAL_PRIORITY_CLASS,
        ePROCESS_PRIORITY_HIGH           =   HIGH_PRIORITY_CLASS,
        ePROCESS_PRIORITY_REALTIME       =   REALTIME_PRIORITY_CLASS,
    };

    enum EPROCESS_PRIORITY_INDEX {
        ePROCESS_PRIORITY_IIDLE_INDEX,
        ePROCESS_PRIORITY_BELOW_NORMAL_INDEX,
        ePROCESS_PRIORITY_NORMAL_INDEX,
        ePROCESS_PRIORITY_ABOVE_NORMAL_INDEX,
        ePROCESS_PRIORITY_HIGH_INDEX,
        ePROCESS_PRIORITY_REALTIME_INDEX,
        ePROCESS_PRIORITY_INDEX_MAX,
    };

    enum EJOB_LOG_TYPE {
        eJOB_LOG_TYPE_DEBUG,
        eJOB_LOG_TYPE_INFO,
        eJOB_LOG_TYPE_WARN,
        eJOB_LOG_TYPE_ERROE,
        eJOB_LOG_TYPE_FATAL,
        eJOB_LOG_TYPE_JOB_STATUS,
        eJOB_LOG_TYPE_JOB_STD_ERROR,
        eJOB_LOG_TYPE_JOB_STD_OUTPUT,
        eJOB_LOG_TYPE_JOB_STD_PROGRESS,
        eJOB_LOG_TYPE_JOB_STD_DETAILS,
        eJOB_LOG_TYPE_MAX,
    };

    bool updatePriorty(void);
    void updatePriortyStart(void);
    void setPriorty(EPROCESS_PRIORITY a_priority = ePROCESS_PRIORITY_NORMAL);
    void setPriorty(EPROCESS_PRIORITY_INDEX a_priority = ePROCESS_PRIORITY_ABOVE_NORMAL_INDEX);
    EPROCESS_PRIORITY getPriorty(void);
    EPROCESS_PRIORITY m_prev_priority;
    EPROCESS_PRIORITY m_priority;

    void setup(void);
    void loadCommonConfig(void);
    void initJob(QList<JobCmdList> a_cmds);
    void startJob(void);
    void abortJobs(void);
    bool isStarted(void);

    bool updateProgress(QString a_text);
    QList<qint64> getAllProcessID(void);
    int lookupJobEncoder(QList<JobCmdList> a_cmds, QUuid a_uid);
    QString catchVspipeFrames(QString a_std);

    void setFlag(int a_index);
    bool isAllProcessCompleted(void);

    void setNotAutoNextJob(bool a_isNotAutoNextJob);
    bool isNotAutoNextJob(void);
    bool m_isNotAutoNextJob;

    QProcess m_process_job_piper;
    QProcess m_process_job_encoder;
    QProcess m_process_job_info;

    bool m_process_catch_vs_frames;
    int m_job_cmd_list_count;

    QString m_process_vs_frames;

    QList<JobCmdList> m_cmds;
    QList<bool> m_cmds_flag;

signals:

public slots:
    /*Info Process*/
    virtual void slotInfoProcessStarted();
    virtual void slotInfoProcessReadyReadStandardError();
    virtual void slotInfoProcessReadyReadStandardOutput();
    virtual void slotInfoProcessFinished(int a_exitCode, QProcess::ExitStatus a_exitStatus);
    virtual void slotInfoProcessError(QProcess::ProcessError a_error);
    /*Piper Process*/
    virtual void slotPiperProcessStarted();
    virtual void slotPiperProcessReadyReadStandardOutput();
    virtual void slotPiperProcessReadyReadStandardError();
    virtual void slotPiperProcessFinished(int a_exitCode, QProcess::ExitStatus a_exitStatus);
    virtual void slotPiperProcessError(QProcess::ProcessError a_error);
    /*Encoder Process*/
    virtual void slotEncoderProcessStarted();
    virtual void slotEncoderProcessReadyReadStandardError();
    virtual void slotEncoderProcessReadyReadStandardOutput();
    virtual void slotEncoderProcessFinished(int a_exitCode, QProcess::ExitStatus a_exitStatus);
    virtual void slotEncoderProcessError(QProcess::ProcessError a_error);

private:
};

#endif // JOB_CHEF_H
