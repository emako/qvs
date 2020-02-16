#include "std_watcher.h"
#include "std_manager.h"
#include "ui_std_watcher.h"
#include "../mainwindow.h"

extern QMap<QUuid, StdWatcher*> g_pStdWatch;

StdWatcher::StdWatcher(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StdWatcher),
    m_isBatch(false),
    m_dataType(eDATA_TYPE_UTF8),
	m_isSamplingStdOut(false),
	m_isSamplingStdErr(false),
    m_pContextMenu(nullptr)
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
    m_cmds_index = eINDEX_0;
}

void StdWatcher::startJob(QString a_cmd)
{
    if (m_isAborted)
    {
        return;
    }

    m_cmd = a_cmd;
    viewLog(JobChef::eJOB_LOG_TYPE_INFO, m_cmd);
    m_process_job_encoder.start(m_cmd);
}

void StdWatcher::startJob(StdWatcherCmd a_cmd)
{
    if (m_isAborted)
    {
        return;
    }

    m_pipe = a_cmd.pipe;
    m_cmd = a_cmd.cmd;

    if(m_pipe.isEmpty())
    {
        viewLog(JobChef::eJOB_LOG_TYPE_INFO, m_cmd);
    }
    else
    {
        viewLog(JobChef::eJOB_LOG_TYPE_INFO, QString("%1 | %2").arg(m_pipe).arg(m_cmd));
    }
    m_process_job_encoder.start(m_cmd);
    if(!m_pipe.isEmpty())
    {
        m_process_job_piper.start(m_pipe);
    }
}

void StdWatcher::startJob(QList<StdWatcherCmd> a_cmds)
{
    if (m_isAborted)
    {
        return;
    }

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

    m_isAborted = true;

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
    m_process_job_info.waitForFinished(eINDEX_NONE);
    m_process_job_piper.waitForFinished(eINDEX_NONE);
    m_process_job_encoder.waitForFinished(eINDEX_NONE);
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
        BOOL result = DebugActiveProcess(static_cast<DWORD>(*i));

        if(result)
        {
            viewLog(JobChef::eJOB_LOG_TYPE_JOB_STATUS, tr("Paused. PID %1.").arg(QString::number(static_cast<DWORD>(*i))));
        }
        else
        {
            viewLog(JobChef::eJOB_LOG_TYPE_WARN, tr("Paused failed. PID %1. Error %2.").arg(QString::number(static_cast<DWORD>(*i))).arg(GetLastError()));
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
        BOOL result = DebugActiveProcessStop(static_cast<DWORD>(*i));

        if(result)
        {
            viewLog(JobChef::eJOB_LOG_TYPE_JOB_STATUS, tr("Resumed. PID %1.").arg(QString::number(static_cast<DWORD>(*i))));
        }
        else
        {
            viewLog(JobChef::eJOB_LOG_TYPE_JOB_STATUS, tr("Failed to resume. PID %1. Error %2.").arg(QString::number(static_cast<DWORD>(*i))).arg(GetLastError()));
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
        ui->logView->setLineWrapMode(QPlainTextEdit::WidgetWidth);
    }
    else
    {
        ui->logView->setLineWrapMode(QPlainTextEdit::NoWrap);
    }
}

void StdWatcher::setupUi(void)
{
    m_pContextMenu = new QMenu(ui->logView);
    ui->logView->setContextMenuPolicy(Qt::CustomContextMenu);
    QAction *at_action_copy = new QAction(QIcon(":/buttons/page_paste.png"), tr("Copy command"), ui->logView);
    QAction *at_action_enable_line_wrapping = new QAction(QIcon(":/buttons/text_wrapping.png"), tr("Enable Line Wrap"), ui->logView);
    at_action_enable_line_wrapping->setCheckable(true);
    at_action_enable_line_wrapping->setChecked(true);
    m_pContextMenu->addActions(QList<QAction*>() << at_action_copy);
    m_pContextMenu->addSeparator();
    m_pContextMenu->addActions(QList<QAction*>() << at_action_enable_line_wrapping);
    connect(at_action_copy, SIGNAL(triggered()), this, SLOT(copyCommand()));
    connect(at_action_enable_line_wrapping, SIGNAL(triggered(bool)), this, SLOT(setWrapped(bool)));

    this->setAttribute(Qt::WA_DeleteOnClose, true);
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
    case JobChef::eJOB_LOG_TYPE_DEBUG:
        qDebug() << a_log;
        break;
    case JobChef::eJOB_LOG_TYPE_INFO:
        ui->logView->appendHtml(qvs::toHtml(a_log, COLOR_LOGGING_INFO, false));
        break;
    case JobChef::eJOB_LOG_TYPE_WARN:
    case JobChef::eJOB_LOG_TYPE_ERROE:
    case JobChef::eJOB_LOG_TYPE_FATAL:
        ui->logView->appendHtml(qvs::toHtml(a_log, COLOR_LOGGING_WARN, false));
        break;
    case JobChef::eJOB_LOG_TYPE_JOB_STATUS:
        ui->logView->appendHtml(qvs::toHtml(a_log, COLOR_LOGGING_STATUS, false));
        qDebug() << a_log;
        break;
    case JobChef::eJOB_LOG_TYPE_JOB_STD_ERROR:
        ui->logView->appendHtml(qvs::toHtml(a_log, COLOR_LOGGING_STD_ERROR, false));
        break;
    case JobChef::eJOB_LOG_TYPE_JOB_STD_OUTPUT:
        ui->logView->appendHtml(qvs::toHtml(a_log, COLOR_LOGGING_STD_OUTPUT, false));
        break;
    default:
        ui->logView->appendHtml(qvs::toHtml(a_log, COLOR_LOGGING_DEFAULT, false));
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
    QTextCursor cursor = ui->logView->textCursor();

    fmt.setForeground(a_color);
    cursor.setPosition(ui->logView->toPlainText().length() - a_length);
    cursor.setPosition(ui->logView->toPlainText().length(), QTextCursor::KeepAnchor);
    cursor.setCharFormat(fmt);
}

void StdWatcher::slotEncoderProcessStarted()
{
    viewLog(JobChef::eJOB_LOG_TYPE_JOB_STATUS, "Encoder Process started.");

    if(!m_process_job_encoder.isReadable())
    {
        viewLog(JobChef::eJOB_LOG_TYPE_WARN, "Encoder process is not Writable.");
        return;
    }
}

void StdWatcher::slotEncoderProcessFinished(int a_exitCode, QProcess::ExitStatus a_exitStatus)
{
    QString message = tr("Encoder Process has completed.");

    emit encoderProcessFinished();
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
        else
        {
            emit encoderProcessAllFinished();
        }
    }
    else
    {
        emit encoderProcessAllFinished();
    }

    if(ui->checkBoxExitCompleted->isChecked())
    {
        if(this->isHidden())
        {
            close();
        }
        else
        {
            m_pCloseTimer->start(m_close_time_min);
        }
    }
}

void StdWatcher::slotEncoderProcessReadyReadStandardError()
{
    QByteArray standardError = m_process_job_encoder.readAllStandardError();
    QString standardErrorText = fromStandard(standardError);
    standardErrorText = standardErrorText.trimmed();
    if(!standardErrorText.isEmpty())
    {
        viewLog(JobChef::eJOB_LOG_TYPE_JOB_STD_ERROR, standardErrorText);
		samplingLog(eSTD_TYPE_ERROR, standardErrorText);
    }
}

void StdWatcher::slotEncoderProcessReadyReadStandardOutput()
{
    QByteArray standardOutput = m_process_job_encoder.readAllStandardOutput();
    QString standardOutputText = fromStandard(standardOutput);
    standardOutputText = standardOutputText.trimmed();
    if(!standardOutputText.isEmpty())
    {
        viewLog(JobChef::eJOB_LOG_TYPE_JOB_STD_OUTPUT, standardOutputText);
		samplingLog(eSTD_TYPE_OUT, standardOutputText);
    }
}

void StdWatcher::slotEncoderProcessError(QProcess::ProcessError a_error)
{
    switch(a_error)
    {
    case QProcess::FailedToStart:
        viewLog(JobChef::eJOB_LOG_TYPE_WARN, tr("Encoder Process has failed to start."));
        break;
    case QProcess::Crashed:
        viewLog(JobChef::eJOB_LOG_TYPE_WARN, tr("Encoder Process has crashed."));
        break;
    case QProcess::Timedout:
        viewLog(JobChef::eJOB_LOG_TYPE_WARN, tr("Encoder Process timeout."));
        break;
    case QProcess::ReadError:
        viewLog(JobChef::eJOB_LOG_TYPE_WARN, tr("Encoder Process read error occured."));
        break;
    case QProcess::WriteError:
        viewLog(JobChef::eJOB_LOG_TYPE_WARN, tr("Encoder Process write error occured."));
        break;
    case QProcess::UnknownError:
        viewLog(JobChef::eJOB_LOG_TYPE_WARN, tr("Encoder Process unknown error occured."));
        break;
    }
}

void StdWatcher::slotPiperProcessStarted()
{
    viewLog(JobChef::eJOB_LOG_TYPE_JOB_STATUS, tr("Piper Process started."));

    if(!m_process_job_piper.isReadable())
    {
        viewLog(JobChef::eJOB_LOG_TYPE_WARN, tr("Piper process is not Writable."));
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

    viewLog(JobChef::eJOB_LOG_TYPE_JOB_STATUS, tr("%1 Exit code: %2").arg(message).arg(a_exitCode));
}

void StdWatcher::slotPiperProcessReadyReadStandardError()
{
    QByteArray standardError = m_process_job_piper.readAllStandardError();
    QString standardErrorText = fromStandard(standardError);
    standardErrorText = standardErrorText.trimmed();
    if(!standardErrorText.isEmpty())
    {
        viewLog(JobChef::eJOB_LOG_TYPE_JOB_STD_ERROR, standardErrorText);
    }
}

void StdWatcher::slotPiperProcessReadyReadStandardOutput()
{
    QByteArray standardOutput = m_process_job_piper.readAllStandardOutput();
    QString standardOutputText = fromStandard(standardOutput);
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
        viewLog(JobChef::eJOB_LOG_TYPE_WARN, tr("Piper Process has failed to start."));
        break;
    case QProcess::Crashed:
        viewLog(JobChef::eJOB_LOG_TYPE_WARN, tr("Piper Process has crashed."));
        break;
    case QProcess::Timedout:
        viewLog(JobChef::eJOB_LOG_TYPE_WARN, tr("Piper Process timeout."));
        break;
    case QProcess::ReadError:
        viewLog(JobChef::eJOB_LOG_TYPE_WARN, tr("Piper Process read error occured."));
        break;
    case QProcess::WriteError:
        viewLog(JobChef::eJOB_LOG_TYPE_WARN, tr("Piper Process write error occured."));
        break;
    case QProcess::UnknownError:
        viewLog(JobChef::eJOB_LOG_TYPE_WARN, tr("Piper Process unknown error occured."));
        break;
    }
}

void StdWatcher::on_btnClose_clicked()
{
    close();
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
    if(m_close_time_set == static_cast<long>(eINDEX_NONE))
    {
        /* Close time not be set. */
        var_close_time_unit = c_close_time;
    }
    else
    {
        var_close_time_unit = m_close_time_set;
    }
    m_close_time_min = SECOND_TO_MILLISECOND_UNIT;
    m_close_time = m_close_time_max = var_close_time_unit * SECOND_TO_MILLISECOND_UNIT;
}

void StdWatcher::checkClose(void)
{
    m_close_time -= m_close_time_min;
    if( (m_close_time < m_close_time_min) || this->isHidden() )
    {
        this->setWindowTitle(StdWatcherMoudleName);
        close();
    }
    else
    {
        this->setWindowTitle(tr("%1 - closed in %2s").arg(StdWatcherMoudleName).arg(m_close_time / SECOND_TO_MILLISECOND_UNIT));
    }
}

void StdWatcher::on_checkBoxExitCompleted_stateChanged(int a_state)
{
    if(static_cast<bool>(a_state))
    {
        PASS;
    }
    else
    {
        if(m_pCloseTimer->isActive())
        {
            m_pCloseTimer->stop();
            initCloseTimerParm();
            this->setWindowTitle(StdWatcherMoudleName);
        }
    }
}

void StdWatcher::releaseJob(void)
{
    abortJob();
    releaseCloseTimer();
    StdManager::releaseStdWatch(m_uid); /* Notify -> Close Event, because this will be closed. */
    mainUi->slotChildWindowClosed(m_uid);
}

void StdWatcher::releaseCloseTimer()
{
    if(m_pCloseTimer->isActive())
    {
        m_pCloseTimer->stop();
    }
}

void StdWatcher::closeEvent(QCloseEvent *e)
{
    releaseJob();
    e->accept();
}

void StdWatcher::on_logView_customContextMenuRequested(const QPoint &)
{
    m_pContextMenu->exec(QCursor::pos());
}

inline QString StdWatcher::fromStandard(const QByteArray &a_data) const
{
    QString data;

    switch(m_dataType)
    {
    case eDATA_TYPE_UTF8:
        data = QString::fromUtf8(a_data);
        break;
    case eDATA_TYPE_LOCAL:
        data = QString::fromLocal8Bit(a_data);
        break;
    case eDATA_TYPE_LATIN1:
        data = QString::fromLatin1(a_data);
        break;
    }
    return data;
}

void StdWatcher::setDataType(EDATA_TYPE a_dataType)
{
    m_dataType = a_dataType;
}

void StdWatcher::setStdSampling(bool a_stdOut, bool a_stdErr)
{
	m_isSamplingStdOut = a_stdOut;
	m_isSamplingStdErr = a_stdErr;
}

bool StdWatcher::isStdOutSampling(void)
{
	return m_isSamplingStdOut;
}

bool StdWatcher::isStdErrSampling(void)
{
	return m_isSamplingStdErr;
}

void StdWatcher::samplingLog(ESTD_TYPE a_stdType, QString a_log)
{
	switch (a_stdType)
	{
	case eSTD_TYPE_OUT:
		if (m_isSamplingStdOut)
		{
			m_stdOutBuffer += a_log;
		}
		emit stdOutRecived(a_log);
		break;
	case eSTD_TYPE_ERROR:
		if (m_isSamplingStdErr)
		{
			m_stdErrBuffer += a_log;
        }
		emit stdErrRecived(a_log);
        break;
	}
}

QString StdWatcher::getSamplingLog(ESTD_TYPE a_stdType)
{
	if (a_stdType == eSTD_TYPE_OUT)
	{
		return m_stdOutBuffer;
	}
	else if(a_stdType == eSTD_TYPE_ERROR)
	{
		return m_stdErrBuffer;
	}
	return NULLSTR;
}
