#include "std_watcher.h"
#include "std_manager.h"
#include "ui_std_watcher.h"
#include "../mainwindow.h"

extern QMap<QUuid, StdWatcher*> g_pStdWatch;

StdWatcher::StdWatcher(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StdWatcher),
    m_isBatch(false)
{
    ui->setupUi(this);
    this->setupUi();
}

StdWatcher::~StdWatcher()
{
    delete ui;
    delete m_pContextMenu;
    delete m_pCloseTimer;
}

void StdWatcher::setCloseTime(const long a_msec)
{
    m_close_time_set = a_msec;
    initCloseTimerParm();
}

void StdWatcher::initJob(QUuid a_uid)
{
    m_uid = a_uid;
    m_cmds_index = (long)eINDEX_0;
}

void StdWatcher::startJob(QString a_cmd)
{
    m_cmd = a_cmd;
    ui->plainTextEdit->appendPlainText(m_cmd);
    m_process_job_encoder.start(m_cmd);
}

void StdWatcher::startJob(StdWatcherCmd a_cmd)
{
    m_pipe = a_cmd.pipe;
    m_cmd = a_cmd.cmd;
    ui->plainTextEdit->appendPlainText(QString("%1 | %2").arg(m_pipe).arg(m_cmd));
    m_process_job_encoder.start(m_cmd);
    if(!m_pipe.isEmpty())
    {
        m_process_job_piper.start(m_pipe);
    }
}

void StdWatcher::startJob(QList<StdWatcherCmd> a_cmds)
{
    if(!a_cmds.isEmpty())
    {
        m_cmds = a_cmds;
        m_isBatch = true;
        startJob(a_cmds.first());
        m_cmds_index++;
    }
}

void StdWatcher::abortJob()
{
    if(ui->btnPause->isChecked())
    {
        ui->btnPause->setChecked(false);
        resumeJob();
    }
    if(m_process_job_info.state() != QProcess::NotRunning)
    {
        m_process_job_info.kill();
    }
    if(m_process_job_piper.state() != QProcess::NotRunning)
    {
        m_process_job_piper.kill();
    }
    if(m_process_job_encoder.state() != QProcess::NotRunning)
    {
        m_process_job_encoder.kill();
    }
    m_process_job_info.waitForFinished(-1);
    m_process_job_piper.waitForFinished(-1);
    m_process_job_encoder.waitForFinished(-1);
}

bool StdWatcher::isRunning(void)
{
    if(m_process_job_info.state() != QProcess::NotRunning)
    {
        return true;
    }
    if(m_process_job_piper.state() != QProcess::NotRunning)
    {
        return true;
    }
    if(m_process_job_encoder.state() != QProcess::NotRunning)
    {
        return true;
    }
    return false;
}

bool StdWatcher::isStarted(void)
{
    if(m_process_job_info.state() == QProcess::Running)
    {
        return true;
    }
    if(m_process_job_piper.state() == QProcess::Running)
    {
        return true;
    }
    if(m_process_job_encoder.state() == QProcess::Running)
    {
        return true;
    }
    return false;
}

void StdWatcher::releaseJob(void)
{
    abortJob();
    releaseCloseTimer();
    StdManager::releaseStdWatch(m_uid);
}

void StdWatcher::pauseJob(void)
{
    QList<qint64> processIds = getAllProcessID();

    if(processIds.isEmpty())
    {
        ui->btnPause->setChecked(false);
        return;
    }

    for(QList<qint64>::iterator i = processIds.begin(); i != processIds.end(); ++i)
    {
        BOOL result = DebugActiveProcess((DWORD)*i);

        if(result)
        {
            viewLog(JobChef::eJOB_LOG_TYPE_JOB_STATUS, tr("Paused. PID %1.").arg(QString::number((DWORD)*i)));
        }
        else
        {
            viewLog(JobChef::eJOB_LOG_TYPE_WARN, tr("Paused failed. PID %1. Error %2.").arg(QString::number((DWORD)*i)).arg(GetLastError()));
        }
    }
}

QList<qint64> StdWatcher::getAllProcessID(void)
{
    QList<qint64> processIds;

    if(m_process_job_info.state() != QProcess::NotRunning)
    {
        processIds.append(m_process_job_info.processId());
    }
    if(m_process_job_piper.state() != QProcess::NotRunning)
    {
        processIds.append(m_process_job_piper.processId());
    }
    if(m_process_job_encoder.state() != QProcess::NotRunning)
    {
        processIds.append(m_process_job_encoder.processId());
    }
    return processIds;
}

void StdWatcher::resumeJob(void)
{
    QList<qint64> processIds = getAllProcessID();

    for(QList<qint64>::iterator i = processIds.begin(); i != processIds.end(); ++i)
    {
        BOOL result = DebugActiveProcessStop((DWORD)*i);

        if(result)
        {
            viewLog(JobChef::eJOB_LOG_TYPE_JOB_STATUS, tr("Resumed. PID %1.").arg(QString::number((DWORD)*i)));
        }
        else
        {
            viewLog(JobChef::eJOB_LOG_TYPE_JOB_STATUS, tr("Failed to resume. PID %1. Error %2.").arg(QString::number((DWORD)*i)).arg(GetLastError()));
        }
    }
}

void StdWatcher::copyCommand(void)
{
    QClipboard *clipboard = QApplication::clipboard();
    QString cmd;

    if(!m_pipe.isEmpty())
    {
        cmd = QString("%1 | %2").arg(m_pipe).arg(m_cmd);
    }
    else
    {
        cmd = m_cmd;
    }
    clipboard->setText(cmd);
}

void StdWatcher::setWrapped(bool a_enable)
{
    if(a_enable)
    {
        ui->plainTextEdit->setLineWrapMode(QPlainTextEdit::WidgetWidth);
    }
    else
    {
        ui->plainTextEdit->setLineWrapMode(QPlainTextEdit::NoWrap);
    }
}

void StdWatcher::setupUi(void)
{
    m_pContextMenu = new QMenu(ui->plainTextEdit);
    ui->plainTextEdit->setContextMenuPolicy(Qt::CustomContextMenu);
    QAction *at_action_copy = new QAction(QIcon(":/buttons/page_paste.png"), tr("Copy command"), ui->plainTextEdit);
    QAction *at_action_enable_line_wrapping = new QAction(QIcon(":/buttons/text_wrapping.png"), tr("Enable Line Wrap"), ui->plainTextEdit);
    at_action_enable_line_wrapping->setCheckable(true);
    m_pContextMenu->addActions(QList<QAction*>() << at_action_copy);
    m_pContextMenu->addSeparator();
    m_pContextMenu->addActions(QList<QAction*>() << at_action_enable_line_wrapping);
    connect(at_action_copy, SIGNAL(triggered()), this, SLOT(copyCommand()));
    connect(at_action_enable_line_wrapping, SIGNAL(triggered(bool)), this, SLOT(setWrapped(bool)));

    initCloseTimerParm();
    m_pCloseTimer = new QTimer(this);
    connect(m_pCloseTimer, SIGNAL(timeout()), this, SLOT(checkClose()));

    connect(&m_process_job_piper, SIGNAL(started()),this, SLOT(slotPiperProcessStarted()));
    connect(&m_process_job_piper, SIGNAL(finished(int,QProcess::ExitStatus)), this, SLOT(slotPiperProcessFinished(int, QProcess::ExitStatus)));
    connect(&m_process_job_piper, SIGNAL(readyReadStandardOutput()), this, SLOT(slotPiperProcessReadyReadStandardOutput()));
    connect(&m_process_job_piper, SIGNAL(readyReadStandardError()), this, SLOT(slotPiperProcessReadyReadStandardError()));
    connect(&m_process_job_piper, SIGNAL(error(QProcess::ProcessError)), this, SLOT(slotPiperProcessError(QProcess::ProcessError)));

    connect(&m_process_job_encoder, SIGNAL(started()),this, SLOT(slotEncoderProcessStarted()));
    connect(&m_process_job_encoder, SIGNAL(finished(int,QProcess::ExitStatus)), this, SLOT(slotEncoderProcessFinished(int, QProcess::ExitStatus)));
    connect(&m_process_job_encoder, SIGNAL(readyReadStandardOutput()), this, SLOT(slotEncoderProcessReadyReadStandardOutput()));
    connect(&m_process_job_encoder, SIGNAL(readyReadStandardError()), this, SLOT(slotEncoderProcessReadyReadStandardError()));
    connect(&m_process_job_encoder, SIGNAL(error(QProcess::ProcessError)), this, SLOT(slotEncoderProcessError(QProcess::ProcessError)));

    m_process_job_piper.setStandardOutputProcess(&m_process_job_encoder);
}

void StdWatcher::viewLog(JobChef::EJOB_LOG_TYPE a_log_type, const QString a_log)
{
    switch(a_log_type)
    {
    case JobChef::eJOB_LOG_TYPE_WARN:
        ui->plainTextEdit->appendPlainText(a_log);
        setInsertTextColor(QColor(255, 0, 0), a_log.length());
        break;
    case JobChef::eJOB_LOG_TYPE_JOB_STATUS:
        ui->plainTextEdit->appendPlainText(a_log);
        setInsertTextColor(QColor(0, 128, 128), a_log.length());
        break;
    case JobChef::eJOB_LOG_TYPE_DEBUG:
    case JobChef::eJOB_LOG_TYPE_INFO:
    case JobChef::eJOB_LOG_TYPE_ERROE:
    case JobChef::eJOB_LOG_TYPE_FATAL:
    case JobChef::eJOB_LOG_TYPE_JOB_STD_ERROR:
    case JobChef::eJOB_LOG_TYPE_JOB_STD_OUTPUT:
    case JobChef::eJOB_LOG_TYPE_JOB_STD_PROGRESS:
    case JobChef::eJOB_LOG_TYPE_JOB_STD_DETAILS:
    default:
        ui->plainTextEdit->appendPlainText(a_log);
        break;
    }
}

void StdWatcher::setInsertTextColor(QColor a_color, int a_length)
{
    if(a_length == eINDEX_0)
    {
        return;
    }

    QTextCharFormat fmt;
    QTextCursor cursor = ui->plainTextEdit->textCursor();

    fmt.setForeground(a_color);
    cursor.setPosition(ui->plainTextEdit->toPlainText().length() - a_length);
    cursor.setPosition(ui->plainTextEdit->toPlainText().length(), QTextCursor::KeepAnchor);
    cursor.setCharFormat(fmt);
}

void StdWatcher::slotEncoderProcessStarted()
{
    viewLog(JobChef::eJOB_LOG_TYPE_JOB_STATUS, "Encoder Process started.");

    if(!m_process_job_encoder.isReadable())
    {
        viewLog(JobChef::eJOB_LOG_TYPE_WARN, "Encoder process is not Writable.");
        //abortJob();
        return;
    }
}

void StdWatcher::slotEncoderProcessFinished(int a_exitCode, QProcess::ExitStatus a_exitStatus)
{
    QString message = tr("Encoder Process has completed.");

    if(a_exitStatus == QProcess::CrashExit)
    {
        message = tr("Encoder Process has crashed.");
    }

    viewLog(JobChef::eJOB_LOG_TYPE_JOB_STATUS, QString("%1 Exit code: %2").arg(message).arg(a_exitCode));

    if(m_isBatch)
    {
        if(m_cmds_index < m_cmds.length())
        {
            startJob(m_cmds.at(m_cmds_index));
            m_cmds_index++;
            return;
        }
    }

    if(ui->checkBoxExitCompleted->isChecked())
    {
        m_pCloseTimer->start(m_close_time_min);
    }
}

void StdWatcher::slotEncoderProcessReadyReadStandardError()
{
    QByteArray standardError = m_process_job_encoder.readAllStandardError();
    QString standardErrorText = QString::fromUtf8(standardError);
    standardErrorText = standardErrorText.trimmed();
    if(!standardErrorText.isEmpty())
    {
        viewLog(JobChef::eJOB_LOG_TYPE_JOB_STD_ERROR, standardErrorText);
    }
}

void StdWatcher::slotEncoderProcessReadyReadStandardOutput()
{
    QByteArray standardOutput = m_process_job_encoder.readAllStandardOutput();
    QString standardOutputText = QString::fromUtf8(standardOutput);
    standardOutputText = standardOutputText.trimmed();
    if(!standardOutputText.isEmpty())
    {
        viewLog(JobChef::eJOB_LOG_TYPE_JOB_STD_OUTPUT, standardOutputText);
    }
}

void StdWatcher::slotEncoderProcessError(QProcess::ProcessError a_error)
{
    switch(a_error)
    {
    case QProcess::FailedToStart:
        viewLog(JobChef::eJOB_LOG_TYPE_WARN, "Encoder Process has failed to start.");
        break;
    case QProcess::Crashed:
        viewLog(JobChef::eJOB_LOG_TYPE_WARN, "Encoder Process has crashed.");
        break;
    case QProcess::Timedout:
        viewLog(JobChef::eJOB_LOG_TYPE_WARN, "Encoder Process timeout.");
        break;
    case QProcess::ReadError:
        viewLog(JobChef::eJOB_LOG_TYPE_WARN, "Encoder Process read error occured.");
        break;
    case QProcess::WriteError:
        viewLog(JobChef::eJOB_LOG_TYPE_WARN, "Encoder Process write error occured.");
        break;
    case QProcess::UnknownError:
    default:
        viewLog(JobChef::eJOB_LOG_TYPE_WARN, "Encoder Process unknown error occured.");
        break;
    }
}

void StdWatcher::slotPiperProcessStarted()
{
    viewLog(JobChef::eJOB_LOG_TYPE_JOB_STATUS, "Piper Process started.");

    if(!m_process_job_piper.isReadable())
    {
        viewLog(JobChef::eJOB_LOG_TYPE_WARN, "Piper process is not Writable.");
        //abortJob();
        return;
    }
}

void StdWatcher::slotPiperProcessFinished(int a_exitCode, QProcess::ExitStatus a_exitStatus)
{
    QString message = tr("Piper Process has completed.");

    if(a_exitStatus == QProcess::CrashExit)
    {
        message = tr("Piper Process has crashed.");
    }

    viewLog(JobChef::eJOB_LOG_TYPE_JOB_STATUS, QString("%1 Exit code: %2").arg(message).arg(a_exitCode));
}

void StdWatcher::slotPiperProcessReadyReadStandardError()
{
    QByteArray standardError = m_process_job_piper.readAllStandardError();
    QString standardErrorText = QString::fromUtf8(standardError);
    standardErrorText = standardErrorText.trimmed();
    if(!standardErrorText.isEmpty())
    {
        viewLog(JobChef::eJOB_LOG_TYPE_JOB_STD_ERROR, standardErrorText);
    }
}

void StdWatcher::slotPiperProcessReadyReadStandardOutput()
{
    QByteArray standardOutput = m_process_job_piper.readAllStandardOutput();
    QString standardOutputText = QString::fromUtf8(standardOutput);
    standardOutputText = standardOutputText.trimmed();
    if(!standardOutputText.isEmpty())
    {
        viewLog(JobChef::eJOB_LOG_TYPE_JOB_STD_OUTPUT, standardOutputText);
    }
}

void StdWatcher::slotPiperProcessError(QProcess::ProcessError a_error)
{
    switch(a_error)
    {
    case QProcess::FailedToStart:
        viewLog(JobChef::eJOB_LOG_TYPE_WARN, "Piper Process has failed to start.");
        break;
    case QProcess::Crashed:
        viewLog(JobChef::eJOB_LOG_TYPE_WARN, "Piper Process has crashed.");
        break;
    case QProcess::Timedout:
        viewLog(JobChef::eJOB_LOG_TYPE_WARN, "Piper Process timeout.");
        break;
    case QProcess::ReadError:
        viewLog(JobChef::eJOB_LOG_TYPE_WARN, "Piper Process read error occured.");
        break;
    case QProcess::WriteError:
        viewLog(JobChef::eJOB_LOG_TYPE_WARN, "Piper Process write error occured.");
        break;
    case QProcess::UnknownError:
    default:
        viewLog(JobChef::eJOB_LOG_TYPE_WARN, "Piper Process unknown error occured.");
        break;
    }
}

void StdWatcher::on_btnClose_clicked()
{
    releaseJob();
}

void StdWatcher::on_btnPause_clicked(bool a_checked)
{
    if(a_checked)
    {
        pauseJob();
    }
    else
    {
        resumeJob();
    }
}

void StdWatcher::initCloseTimerParm(void)
{
    long var_close_time_unit;
    if(m_close_time_set == (long)eINDEX_NONE)
    {
        /* Close time not be set. */
        var_close_time_unit = c_close_time;
    }
    else
    {
        var_close_time_unit = m_close_time_set;
    }
    m_close_time_min = c_close_time_unit;
    m_close_time = m_close_time_max = var_close_time_unit * c_close_time_unit;
}

void StdWatcher::checkClose(void)
{
    m_close_time -= m_close_time_min;
    if(m_close_time < m_close_time_min)
    {
        m_pCloseTimer->stop();
        emit ui->btnClose->clicked();
    }
    else
    {
        this->setWindowTitle(tr("StdWatcher - closed in %1s").arg(m_close_time / c_close_time_unit));
    }
}

void StdWatcher::on_checkBoxExitCompleted_stateChanged(int a_state)
{
    if((bool)a_state)
    {
        QT_PASS;
    }
    else
    {
        if(m_pCloseTimer->isActive())
        {
            m_pCloseTimer->stop();
            initCloseTimerParm();
            this->setWindowTitle(QString("StdWatcher"));
        }
    }
}

void StdWatcher::releaseCloseTimer()
{
    if(m_pCloseTimer->isActive())
    {
        m_pCloseTimer->stop();
    }
}

void StdWatcher::on_plainTextEdit_customContextMenuRequested(const QPoint &)
{
    m_pContextMenu->exec(QCursor::pos());
}

void StdWatcher::closeEvent(QCloseEvent *e)
{
    abortJob();
    e->accept();
}
