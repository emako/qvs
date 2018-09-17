#ifndef STD_WATCHER_H
#define STD_WATCHER_H

#include <QWidget>
#include <QTimer>
#include "../job/job_chef.h"

class JobChef;
class MainWindow;

namespace Ui {
class StdWatcher;
}

class StdWatcherCmd
{
public:
    QString cmd;
    QString pipe;
};

class StdWatcher : public QWidget
{
    Q_OBJECT

public:
    explicit StdWatcher(QWidget *parent = 0);
    ~StdWatcher();
    class MainWindow *mainUi;

    enum EHANDLER_TYPE {
        eHANDLER_TYPE_STARTED,
        eHANDLER_TYPE_ERROR,
        eHANDLER_TYPE_FINISHED,
        eHANDLER_TYPE_MAX,
    };

    void initJob(QUuid a_uid);
    void startJob(QString a_cmd);
    void startJob(StdWatcherCmd a_cmd);
    void startJob(QList<StdWatcherCmd> a_cmds);
    void abortJob();
    QList<qint64> getAllProcessID(void);
    void releaseJob(void);
    void resumeJob(void);
    void pauseJob(void);
    bool isRunning(void);
    bool isStarted(void);
    void viewLog(JobChef::EJOB_LOG_TYPE a_log_type, const QString a_log);
    void setCloseTime(const long a_msec);

    QProcess m_process_job_info;
    QProcess m_process_job_piper;
    QProcess m_process_job_encoder;

private:
    Ui::StdWatcher *ui;
    void setupUi(void);
    void releaseCloseTimer(void);
    void initCloseTimerParm(void);
    void setInsertTextColor(QColor a_color, int a_length);
    QUuid m_uid;
    QString m_cmd;
    QString m_pipe;
    QList<StdWatcherCmd> m_cmds;
    long m_cmds_index;
    bool m_isBatch;

    QTimer *m_pCloseTimer;
    QMenu *m_pContextMenu;
    long m_close_time;
    long m_close_time_min;
    long m_close_time_max;
    long m_close_time_set = (long)eINDEX_NONE;
    const long c_close_time = (long)(eINDEX_3 * eINDEX_10) + eINDEX_1;
    const long c_close_time_unit = (long)(eINDEX_10 * eINDEX_10 * eINDEX_10);

private slots:
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
    /*Close Timer*/
    virtual void checkClose(void);
    virtual void closeEvent(QCloseEvent *e);
    /*Context Menu*/
    void copyCommand(void);
    void setWrapped(bool a_enable);

    void on_btnClose_clicked();
    void on_btnPause_clicked(bool a_checked);
    void on_checkBoxExitCompleted_stateChanged(int a_state);
    void on_logView_customContextMenuRequested(const QPoint &a_pos);
};

#endif // STD_WATCHER_H
