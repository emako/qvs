#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QApplication>
#include <QStandardItemModel>
#include <QTableWidgetItem>
#include <QScrollBar>
#include <QDesktopServices>
#include <QJsonDocument>
#include <QSystemTrayIcon>

#include "job/job_creator.h"
#include "job/job_cmdlist.h"
#include "job/job_chef.h"
#include "job/job_item.h"
#include "job/job_view_cmd.h"
//#include "preview/ffpreview_dialog.h"
#include "com/common.h"
#include "com/logging.h"
#include "com/timer.h"
#include "com/mail_box.h"
#include "com/config.h"

#undef QT_PLASH
#ifndef QT_DEBUG
#define QT_PLASH
#endif

class AudioEnc;
class Muxer;
class Demuxer;
class ScriptPlayer;
class MediaInfoDialog;
class InstallerDialog;
class PreviewDialog;
class ScriptCreator;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    friend class Timer;
    friend class AudioEnc;
    friend class Muxer;
    friend class Demuxer;
    friend class MediaInfo;
    friend class AudioConfig;
    friend class ScriptPlayer;
    friend class InstallerDialog;
    friend class PreviewDialog;
    friend class ScriptCreator;
    friend class StdWatcher;

    enum ETAB {
        eTAB_MAIN,
        eTAB_AUDIO,
        eTAB_MUXER,
        eTAB_EXTRA,
        eTAB_MEDIAINFO,
        eTAB_MAX,
    };

    void modeLaunch(void);
    void loadFonts(void);
    void setLanguage(Config::ELANGUAGE a_language);
    Config::ELANGUAGE language(void);
    void execJobCreator(JobCreator::EJOB_RELOAD a_job_reload, QString a_filename = QT_EMPTY);
    void acceptedJobCreator(JobCreator::EJOB_RELOAD a_job_reload);
    void saveJob(JobItem a_job_item, JobCreator::EJOB_RELOAD a_job_reload);
    void viewLog(JobChef::EJOB_LOG_TYPE a_log_type, const QString &a_log);
    void setDetailLog(const QString &a_log);
    bool isStarted(void);
    bool isPaused(void);
    bool isAborted(void);
    void reqJobStart(void);
    void setStartJobImmediately(bool a_set);
    void logging(const QString &a_log);

    QList<JobItem> m_jobs;
    int m_jobs_index;
    JobChef *m_job_chef;
    Common *m_com;
    Logging *m_logging;
    Timer *m_timer;
    MailBox *m_pMailBox;
    QMap<QUuid, ScriptPlayer *> m_pScriptPlayers;
    QMap<QUuid, MediaInfoDialog *> m_pMediaInfoDialogs;
    QMap<QUuid, PreviewDialog *> m_pPreviewDialogs;
    QMap<QUuid, ScriptCreator *> m_pScriptCreators;
    QMenu *m_pJobViewMenu;
    QMenu *m_pLogViewMenu;
    QSystemTrayIcon *m_pSystemTray;
    QMap<QUuid, QWidget *> m_pMinimizeWidgets;

    JobChef::EJOB_STATUS m_job_status_prev;

signals:
    void ntfStartJob(void);
    void ntfFailJob(void);
    void ntfStatusChanged(JobChef::EJOB_STATUS a_job_status);
    void ntfTimeout(Timer::ETIMER_SLOT a_timer);

public slots:
    void slotChildWindowClosed(QUuid a_uid);
    bool slotMail(STMAILBOX* a_mail_box);

private slots:
    bool isEmptyJobs(void);
    bool isSkipJob(void);
    void timeout(Timer::ETIMER_SLOT a_timer);

    void initJob(void);
    void startJob(void);
    void failJob(void);
    void pauseJob(void);
    void resumeJob(void);
    void abortJob(void);
    void exploreJob(void);
    void editJob(void);
    void viewJobCmd(void);
    void resetJob(void);
    void delJob(void);
    void moveUpJob(void);
    void moveDownJob(void);
    void slotPreview(void);
    void allCompleted(void);

    void showPreferences(void);
    void showInstaller(void);
    void statusChanged(JobChef::EJOB_STATUS a_job_status);
    bool slotChildWindowClosedRemove(QUuid a_uid);

    void logCopy(void);
    void logClear(void);
    void logSave(void);
    void logSetWrapped(bool a_enable);

    void languageChanged(void);

    void openCommandLine(void);
    void openPython(void);
    void openPreviewDialog(void);
    void openScriptCreator(void);
    void openScriptPlayer(void);
    void openTools(void);
    void selectOpenfile(void);

    void slotMinimize(void);
    void slotTrayActivated(QSystemTrayIcon::ActivationReason a_reason);
    void slotViewJobsLog(void);

    void cleanUpAll(void);
    void cleanUpFinished(void);
    void cleanLoggingFile(void);
    int getFirstJobStatusIndex(JobChef::EJOB_STATUS a_status);
    void cleanUpStatusAll(JobChef::EJOB_STATUS a_status);
    void slotOpenUrl(void);
    void slotAbout(void);
    void slotAboutQt(void);

    void on_buttonAddJob_clicked(void);
    void on_buttonStartJob_clicked(void);
    void on_jobsView_itemDoubleClicked(QTableWidgetItem *a_item);
    void on_buttonPauseJob_clicked(bool a_checked);
    void on_buttonAbortJob_clicked(void);
    void on_jobsView_customContextMenuRequested(const QPoint &a_pos);
    void on_logView_customContextMenuRequested(const QPoint &a_pos);

    void on_buttonAudioBatchAdd_clicked();
    void on_buttonAudioBatchDelete_clicked();
    void on_buttonAudioBatchClear_clicked();
    void on_buttonAudioBatchStart_clicked();

private:
    Ui::MainWindow *ui;
    bool m_isAborted;
    QActionGroup *m_pActionGruopOnCompletion;
    QActionGroup *m_pActionGruopLanguage;

    void showShutdownMessage(Common::ESHUTDOWN a_shutdown);
    QString getShutdownTitle(Common::ESHUTDOWN a_shutdown);
    void setShutCountMessage(void);
    QMessageBox *m_pMsgBoxShutdown;
    unsigned int m_count4shutdown;

    bool m_isStartJobImmediately;

    void setupUi(void);
    void setAcctions(void);

    QString getJobStatusText(JobChef::EJOB_STATUS a_job_status);
    QIcon getJobStatusIcon(JobChef::EJOB_STATUS a_job_status);
    void appendItems(QStringList a_contents);
    void addItem(int a_row, int a_col, QString a_content);
    void addItem(int a_row, int a_col, QString a_content, QIcon a_icon);
    void releaseChildWindowsAll(void);
    void setInsertTextColor(QColor a_color, int a_length);

protected:
    virtual bool eventFilter(QObject *o, QEvent *e);
    virtual void dragEnterEvent(QDragEnterEvent *e);
    virtual void dropEvent(QDropEvent *e);
    virtual void dragMoveEvent(QDragMoveEvent *e);
    virtual void resizeEvent(QResizeEvent* e);
    virtual void closeEvent(QCloseEvent *e);
};

#endif // MAINWINDOW_H
