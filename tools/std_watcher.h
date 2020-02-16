#ifndef STD_WATCHER_H
#define STD_WATCHER_H

#include <QWidget>
#include <QTimer>
#include "../job/job_chef.h"

#define StdWatcherMoudleName QObject::tr("StdWatcher")

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
    explicit StdWatcher(QWidget *parent = nullptr);
    ~StdWatcher();
    class MainWindow *mainUi;

    enum EHANDLER_TYPE
    {
        eHANDLER_TYPE_STARTED,
        eHANDLER_TYPE_ERROR,
        eHANDLER_TYPE_FINISHED,
        eHANDLER_TYPE_MAX,
    };

    enum EDATA_TYPE
    {
        eDATA_TYPE_UTF8,
        eDATA_TYPE_LOCAL,
        eDATA_TYPE_LATIN1,
    };

    enum ESTD_TYPE
    {
        eSTD_TYPE_OUT,
        eSTD_TYPE_ERROR,
    };

    void initJob(QUuid a_uid);
    void startJob(QString a_cmd);
    void startJob(StdWatcherCmd a_cmd);
    void startJob(QList<StdWatcherCmd> a_cmds);
    void abortJob();
    void releaseJob(void);
    void resumeJob(void);
    void pauseJob(void);

    bool isRunning(void);
    bool isStarted(void);

    void viewLog(JobChef::EJOB_LOG_TYPE a_log_type, const QString a_log);

	QList<qint64> getAllProcessID(void);
    void setCloseTime(const long a_msec);

    void setDataType(EDATA_TYPE a_dataType);

	void setStdSampling(bool a_stdOut, bool a_stdErr);
	bool isStdOutSampling(void);
	bool isStdErrSampling(void);
	void samplingLog(ESTD_TYPE a_stdType, QString a_log);
	QString getSamplingLog(ESTD_TYPE a_stdType);

    QProcess m_process_job_info;
    QProcess m_process_job_piper;
    QProcess m_process_job_encoder;

signals:
    void stdOutRecived(QString a_log);
    void stdErrRecived(QString a_log);
    void encoderProcessFinished();
    void encoderProcessAllFinished();

private:
    Ui::StdWatcher *ui;
    void setupUi(void);
    void releaseCloseTimer(void);
    void initCloseTimerParm(void);
    void setInsertTextColor(QColor a_color, int a_length);
    inline QString fromStandard(const QByteArray &a_data) const;

    bool m_isAborted = false;

    QUuid m_uid;
    QString m_cmd;
    QString m_pipe;
    QList<StdWatcherCmd> m_cmds;
    long m_cmds_index;
    bool m_isBatch;
    EDATA_TYPE m_dataType;

	bool m_isSamplingStdOut;
	bool m_isSamplingStdErr;

	QString m_stdOutBuffer;
	QString m_stdErrBuffer;

    QTimer *m_pCloseTimer;
    QMenu *m_pContextMenu;
    long m_close_time;
    long m_close_time_min;
    long m_close_time_max;
    long m_close_time_set = eINDEX_NONE;
    const long c_close_time = eINDEX_10 + eINDEX_1; // 10s

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
