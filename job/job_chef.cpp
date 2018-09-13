#include "job_chef.h"
#include "mainwindow.h"

static const int PROCESS_EXIT_CODE_AUTO_SKIP = 'A'+'u'+'t'+'o'+'S'+'k'+'i'+'p';
static const DWORD c_priortyIndexToPriorty[JobChef::ePROCESS_PRIORITY_INDEX_MAX] = {
    JobChef::ePROCESS_PRIORITY_IIDLE,
    JobChef::ePROCESS_PRIORITY_BELOW_NORMAL,
    JobChef::ePROCESS_PRIORITY_NORMAL,
    JobChef::ePROCESS_PRIORITY_ABOVE_NORMAL,
    JobChef::ePROCESS_PRIORITY_HIGH,
    JobChef::ePROCESS_PRIORITY_REALTIME,
};

JobChef::JobChef(QObject *parent) :
    QObject(parent),
    m_prev_priority(ePROCESS_PRIORITY_NORMAL),
    m_priority(ePROCESS_PRIORITY_NORMAL)
{
    this->setup();
}

void JobChef::setup(void)
{
    m_job_cmd_list_count = (int)eINDEX_0;

    connect(&m_process_job_info, SIGNAL(started()),this, SLOT(slotInfoProcessStarted()));
    connect(&m_process_job_info, SIGNAL(finished(int,QProcess::ExitStatus)), this, SLOT(slotInfoProcessFinished(int, QProcess::ExitStatus)));
    connect(&m_process_job_info, SIGNAL(readyReadStandardOutput()), this, SLOT(slotInfoProcessReadyReadStandardOutput()));
    connect(&m_process_job_info, SIGNAL(readyReadStandardError()), this, SLOT(slotInfoProcessReadyReadStandardError()));
    connect(&m_process_job_info, SIGNAL(error(QProcess::ProcessError)), this, SLOT(slotInfoProcessError(QProcess::ProcessError)));

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

void JobChef::loadCommonConfig(void)
{
    setNotAutoNextJob(g_pConfig->getConfig(Config::eCONFIG_COMMON_NOT_AUTO_NEXT_JOB).toBool());
    setPriorty((EPROCESS_PRIORITY_INDEX)g_pConfig->getConfig(Config::eCONFIG_COMMON_ENCODER_PRECESS_PRIORITY).toInt());
}

void JobChef::initJob(QList<JobCmdList> a_cmds)
{
    m_cmds = a_cmds;
    m_process_catch_vs_frames = false;
    m_process_vs_frames = QString::number((int)eINDEX_0);
    m_job_cmd_list_count = (int)eINDEX_0;

    m_cmds_flag = QList<bool>();
    for(int i = (int)eINDEX_0; i < a_cmds.length(); i++)
    {
        m_cmds_flag.append(false);
    }

#ifdef QT_DEBUG
    mainUi->viewLog(eJOB_LOG_TYPE_INFO, ">-----------------------------------<");
    mainUi->viewLog(eJOB_LOG_TYPE_DEBUG, "Job Init Complete");
#endif
}

void JobChef::startJob(void)
{
#ifdef QT_DEBUG
    mainUi->viewLog(eJOB_LOG_TYPE_DEBUG, "Job Started Count: " + QString::number(m_job_cmd_list_count));
    mainUi->viewLog(eJOB_LOG_TYPE_DEBUG, "Job Skip Flag: " + QString::number(m_cmds_flag.at(m_job_cmd_list_count)));
#endif

    int i = m_job_cmd_list_count;

    if(m_cmds_flag.at(i) == true)
    {
        emit m_process_job_encoder.finished(PROCESS_EXIT_CODE_AUTO_SKIP, QProcess::NormalExit);
        return;
    }

    if(i != (int)eINDEX_0)
    {
        m_process_catch_vs_frames = false;
    }

    if(m_cmds.at(i).type == JobCmdList::eJOB_CMD_TYPE_INFO)
    {
        mainUi->viewLog(eJOB_LOG_TYPE_INFO, tr("Info Process: %1").arg(m_cmds.at(i).cmd));

        m_process_catch_vs_frames = true;
        m_process_job_info.start(m_cmds.at(i).cmd);
        setFlag(i);
    }
    else if(m_cmds.at(i).type == JobCmdList::eJOB_CMD_TYPE_PIPER)
    {
        int encoder_cmd_list_count = lookupJobEncoder(m_cmds, m_cmds.at(i).uid);
        if(encoder_cmd_list_count >= (int)eINDEX_0)
        {
            QString cmd = QString(m_cmds.at(encoder_cmd_list_count).cmd).arg(m_process_vs_frames);

            mainUi->viewLog(eJOB_LOG_TYPE_INFO, tr("Piper Process: %1").arg(m_cmds.at(i).cmd));
            mainUi->viewLog(eJOB_LOG_TYPE_INFO, tr("Encoder Process: %1").arg(cmd));

            m_process_job_encoder.start(cmd);
            m_process_job_piper.start(m_cmds.at(i).cmd);

            setFlag(i);
            setFlag(encoder_cmd_list_count);
        }
    }
    else
    {
        mainUi->viewLog(eJOB_LOG_TYPE_INFO, tr("Encoder Process: %1").arg(m_cmds.at(i).cmd));
        m_process_job_encoder.start(m_cmds.at(i).cmd);
        setFlag(i);
    }
}

bool JobChef::isStarted(void)
{
    if(m_process_job_encoder.state() != QProcess::NotRunning)
        return true;
    if(m_process_job_piper.state() != QProcess::NotRunning)
        return true;
    if(m_process_job_info.state() != QProcess::NotRunning)
        return true;
    return false;
}

void JobChef::abortJobs(void)
{
    emit mainUi->ntfStatusChanged(JobChef::eJOB_STATUS_ABORTING);
    m_process_job_encoder.kill();
    m_process_job_piper.kill();
    m_process_job_info.kill();
    m_process_job_encoder.waitForFinished(-1);
    m_process_job_piper.waitForFinished(-1);
    m_process_job_info.waitForFinished(-1);
    emit mainUi->ntfStatusChanged(JobChef::eJOB_STATUS_ABORTED);
}

void JobChef::setFlag(int a_index)
{
    QList<bool> at_cmds_flag;

    for(int i = (int)eINDEX_0; i < m_cmds_flag.length(); i++)
    {
        if(i == a_index)
        {
            at_cmds_flag.append(true);
        }
        else
        {
            at_cmds_flag.append(m_cmds_flag.at(i));
        }
    }
    m_cmds_flag = at_cmds_flag;
}

int JobChef::lookupJobEncoder(QList<JobCmdList> a_cmds, QUuid a_uid)
{
    int job_cmd_list_count = (int)eINDEX_NONE;

    for(int i = m_job_cmd_list_count; i < a_cmds.length(); i++)
    {
        if(m_cmds_flag.at(i) == false)
        {
            if(a_cmds.at(i).uid == a_uid)
            {
                if(a_cmds.at(i).type == JobCmdList::eJOB_CMD_TYPE_ENCODER)
                {
                    job_cmd_list_count = i;
                    break;
                }
            }
        }
    }
    return job_cmd_list_count;
}

void JobChef::slotPiperProcessReadyReadStandardOutput()
{
    QByteArray standardOutput = m_process_job_piper.readAllStandardOutput();
    QString standardOutputText = QString::fromUtf8(standardOutput);
    standardOutputText = standardOutputText.trimmed();
    if(!standardOutputText.isEmpty())
    {
        mainUi->viewLog(eJOB_LOG_TYPE_JOB_STD_OUTPUT, standardOutputText);
    }
}

void JobChef::slotInfoProcessReadyReadStandardOutput()
{
    QByteArray standardOutput = m_process_job_info.readAllStandardOutput();
    QString standardOutputText = QString::fromUtf8(standardOutput);
    standardOutputText = standardOutputText.trimmed();
    if(!standardOutputText.isEmpty())
    {
        mainUi->viewLog(eJOB_LOG_TYPE_JOB_STD_OUTPUT, standardOutputText);
        if(m_process_catch_vs_frames)
        {
            m_process_vs_frames = catchVspipeFrames(standardOutputText);
            mainUi->viewLog(eJOB_LOG_TYPE_DEBUG, "Info Process: Catch Frames "+m_process_vs_frames);
        }
    }
}

void JobChef::slotEncoderProcessReadyReadStandardOutput()
{
    QByteArray standardOutput = m_process_job_encoder.readAllStandardOutput();
    QString standardOutputText = QString::fromUtf8(standardOutput);
    standardOutputText = standardOutputText.trimmed();
    if(!standardOutputText.isEmpty())
    {
        mainUi->viewLog(eJOB_LOG_TYPE_JOB_STD_OUTPUT, standardOutputText);
    }
}

void JobChef::slotEncoderProcessReadyReadStandardError()
{
    QByteArray standardError = m_process_job_encoder.readAllStandardError();
    QString standardErrorText = QString::fromUtf8(standardError);
    standardErrorText = standardErrorText.trimmed();
    if(!standardErrorText.isEmpty())
    {
        if(!updateProgress(standardErrorText))
        {
            mainUi->viewLog(eJOB_LOG_TYPE_JOB_STD_ERROR, standardErrorText);
        }
    }
}

void JobChef::slotPiperProcessReadyReadStandardError()
{
    QByteArray standardError = m_process_job_piper.readAllStandardError();
    QString standardErrorText = QString::fromUtf8(standardError);
    standardErrorText = standardErrorText.trimmed();
    if(!standardErrorText.isEmpty())
    {
        mainUi->viewLog(eJOB_LOG_TYPE_JOB_STD_ERROR, standardErrorText);
    }
}

void JobChef::slotInfoProcessReadyReadStandardError()
{
    QByteArray standardError = m_process_job_info.readAllStandardError();
    QString standardErrorText = QString::fromUtf8(standardError);
    standardErrorText = standardErrorText.trimmed();
    if(!standardErrorText.isEmpty())
    {
        mainUi->viewLog(eJOB_LOG_TYPE_JOB_STD_ERROR, standardErrorText);
    }
}

QString JobChef::catchVspipeFrames(QString a_std)
{
    /* Catch frames from vspipe. */
    QString frames = QString::number((int)eINDEX_0);
    QStringList stds = a_std.split(QT_NOR_EOL);

    if(stds.length() >= (int)eINDEX_3)
    {
        QString frames_text = stds.at((int)eINDEX_2);
        int frames_blank_index = frames_text.indexOf(QT_BLANK);
        frames = frames_text.right(frames_text.length() - frames_blank_index).simplified();
    }
    return frames;
}

void JobChef::slotInfoProcessFinished(int a_exitCode, QProcess::ExitStatus a_exitStatus)
{
    QString message = tr("Info Process has completed.");

    emit mainUi->ntfStatusChanged(JobChef::eJOB_STATUS_READY);
    if(a_exitStatus == QProcess::CrashExit)
    {
        message = tr("Info Process has crashed.");
    }

    mainUi->viewLog(eJOB_LOG_TYPE_JOB_STATUS, QString("%1 Exit code: %2").arg(message).arg(a_exitCode));

    if(mainUi->isAborted())
    {
        return;
    }
    if(!isAllProcessCompleted())
    {
        m_job_cmd_list_count++;
        startJob();
    }
    else
    {
        emit mainUi->ntfStartJob();
    }
}

void JobChef::slotPiperProcessFinished(int a_exitCode, QProcess::ExitStatus a_exitStatus)
{
    QString message = tr("Piper Process has completed.");

    if(a_exitStatus == QProcess::CrashExit)
    {
        message = tr("Piper Process has crashed.");
    }

    mainUi->viewLog(eJOB_LOG_TYPE_JOB_STATUS, QString("%1 Exit code: %2").arg(message).arg(a_exitCode));
}


void JobChef::slotEncoderProcessFinished(int a_exitCode, QProcess::ExitStatus a_exitStatus)
{
    QString message = tr("Encoder Process has completed.");

    emit mainUi->ntfStatusChanged(JobChef::eJOB_STATUS_COMPLETED);
    if(a_exitStatus == QProcess::CrashExit)
    {
        message = tr("Encoder Process has crashed.");
    }

    if(a_exitCode == PROCESS_EXIT_CODE_AUTO_SKIP)
    {
        mainUi->viewLog(eJOB_LOG_TYPE_JOB_STATUS, "Auto Skip Process.");
    }
    else
    {
        mainUi->viewLog(eJOB_LOG_TYPE_JOB_STATUS, QString("%1 Exit code: %2").arg(message).arg(a_exitCode));
    }

    if(mainUi->isAborted())
    {
        return;
    }
    if(!isAllProcessCompleted())
    {
        m_job_cmd_list_count++;
        startJob();
    }
    else if(!isNotAutoNextJob())
    {
        mainUi->viewLog(eJOB_LOG_TYPE_JOB_STATUS, "Job Completed!");
        mainUi->viewLog(eJOB_LOG_TYPE_JOB_STATUS, QT_EMPTY);
        emit mainUi->ntfStartJob();
    }
}

bool JobChef::isAllProcessCompleted(void)
{
    bool is_completed = true;

    if(m_job_cmd_list_count < m_cmds.length() - (int)eINDEX_1)
    {
        is_completed = false;
    }
    return is_completed;
}

void JobChef::slotEncoderProcessStarted()
{
    mainUi->viewLog(eJOB_LOG_TYPE_JOB_STATUS, tr("Encoder Process started."));
    emit mainUi->ntfStatusChanged(JobChef::eJOB_STATUS_RUNNING);
    m_prev_priority = ePROCESS_PRIORITY_NORMAL;

    if(!m_process_job_encoder.isReadable())
    {
        mainUi->viewLog(eJOB_LOG_TYPE_WARN, tr("Encoder process is not Writable."));
        //abortJob();
        return;
    }
}

void JobChef::slotInfoProcessStarted()
{
    mainUi->viewLog(eJOB_LOG_TYPE_JOB_STATUS, tr("Info Process started."));
    emit mainUi->ntfStatusChanged(JobChef::eJOB_STATUS_RUNNING);
    m_prev_priority = ePROCESS_PRIORITY_NORMAL;

    if(!m_process_job_info.isReadable())
    {
        mainUi->viewLog(eJOB_LOG_TYPE_WARN, tr("Info process is not Readable."));
        //abortJob();
        return;
    }
}

void JobChef::slotPiperProcessStarted()
{
    mainUi->viewLog(eJOB_LOG_TYPE_JOB_STATUS, tr("Piper Process started."));
    m_prev_priority = ePROCESS_PRIORITY_NORMAL;

    if(!m_process_job_piper.isWritable())
    {
        mainUi->viewLog(eJOB_LOG_TYPE_WARN, tr("Piper process is not Writable."));
        //abortJob();
        return;
    }
}

void JobChef::slotPiperProcessError(QProcess::ProcessError a_error)
{
    emit mainUi->ntfStatusChanged(JobChef::eJOB_STATUS_FAILED);
    switch(a_error)
    {
    case QProcess::FailedToStart:
        mainUi->viewLog(eJOB_LOG_TYPE_DEBUG, tr("Piper Process has failed to start."));
        break;
    case QProcess::Crashed:
        mainUi->viewLog(eJOB_LOG_TYPE_DEBUG, tr("Piper Process has crashed."));
        break;
    case QProcess::Timedout:
        mainUi->viewLog(eJOB_LOG_TYPE_DEBUG, tr("Piper Process timeout."));
        break;
    case QProcess::ReadError:
        mainUi->viewLog(eJOB_LOG_TYPE_DEBUG, tr("Piper Process read error occured."));
        break;
    case QProcess::WriteError:
        mainUi->viewLog(eJOB_LOG_TYPE_DEBUG, tr("Piper Process write error occured."));
        break;
    case QProcess::UnknownError:
    default:
        mainUi->viewLog(eJOB_LOG_TYPE_DEBUG, tr("Piper Process unknown error occured."));
        break;
    }
}

void JobChef::slotEncoderProcessError(QProcess::ProcessError a_error)
{
    emit mainUi->ntfStatusChanged(JobChef::eJOB_STATUS_FAILED);
    switch(a_error)
    {
    case QProcess::FailedToStart:
        mainUi->viewLog(eJOB_LOG_TYPE_DEBUG, tr("Encoder Process has failed to start."));
        break;
    case QProcess::Crashed:
        mainUi->viewLog(eJOB_LOG_TYPE_DEBUG, tr("Encoder Process has crashed."));
        break;
    case QProcess::Timedout:
        mainUi->viewLog(eJOB_LOG_TYPE_DEBUG, tr("Encoder Process timeout."));
        break;
    case QProcess::ReadError:
        mainUi->viewLog(eJOB_LOG_TYPE_DEBUG, tr("Encoder Process read error occured."));
        break;
    case QProcess::WriteError:
        mainUi->viewLog(eJOB_LOG_TYPE_DEBUG, tr("Encoder Process write error occured."));
        break;
    case QProcess::UnknownError:
    default:
        mainUi->viewLog(eJOB_LOG_TYPE_DEBUG, tr("Encoder Process unknown error occured."));
        break;
    }
}

void JobChef::slotInfoProcessError(QProcess::ProcessError a_error)
{
    emit mainUi->ntfStatusChanged(JobChef::eJOB_STATUS_FAILED);
    switch(a_error)
    {
    case QProcess::FailedToStart:
        mainUi->viewLog(eJOB_LOG_TYPE_DEBUG, tr("Info Process has failed to start."));
        break;
    case QProcess::Crashed:
        mainUi->viewLog(eJOB_LOG_TYPE_DEBUG, tr("Info Process has crashed."));
        break;
    case QProcess::Timedout:
        mainUi->viewLog(eJOB_LOG_TYPE_DEBUG, tr("Info Process timeout."));
        break;
    case QProcess::ReadError:
        mainUi->viewLog(eJOB_LOG_TYPE_DEBUG, tr("Info Process read error occured."));
        break;
    case QProcess::WriteError:
        mainUi->viewLog(eJOB_LOG_TYPE_DEBUG, tr("Info Process write error occured."));
        break;
    case QProcess::UnknownError:
    default:
        mainUi->viewLog(eJOB_LOG_TYPE_DEBUG, tr("Info Process unknown error occured."));
        break;
    }
}

bool JobChef::updateProgress(QString a_text)
{
    bool is_match = false;
    QRegularExpression rex("^\\[(\\d+\\.?\\d?)%\\].*");
    QRegularExpressionMatch rex_match = rex.match(a_text);

    if(rex_match.hasMatch())
    {
        QStringList rex_match_texts = rex_match.capturedTexts();
        if(rex_match_texts.length() == (int)eINDEX_2)
        {
            is_match = true;
            mainUi->viewLog(eJOB_LOG_TYPE_JOB_STD_PROGRESS, rex_match_texts.at(rex_match_texts.length() - (int)eINDEX_1));
            mainUi->viewLog(eJOB_LOG_TYPE_JOB_STD_DETAILS, rex_match_texts.at((int)eINDEX_0));
        }
    }

    return is_match;
}

QList<qint64> JobChef::getAllProcessID(void)
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

void JobChef::setNotAutoNextJob(bool a_isNotAutoNextJob)
{
    m_isNotAutoNextJob = a_isNotAutoNextJob;
}

bool JobChef::isNotAutoNextJob(void)
{
    return m_isNotAutoNextJob;
}

void JobChef::setPriorty(EPROCESS_PRIORITY a_priority)
{
    m_priority = a_priority;
}

void JobChef::setPriorty(EPROCESS_PRIORITY_INDEX a_priority)
{
    m_priority = (EPROCESS_PRIORITY)c_priortyIndexToPriorty[a_priority];
}

JobChef::EPROCESS_PRIORITY JobChef::getPriorty(void)
{
    return m_priority;
}

bool JobChef::updatePriorty(void)
{
    setPriorty((EPROCESS_PRIORITY_INDEX)g_pConfig->getConfig(Config::eCONFIG_COMMON_ENCODER_PRECESS_PRIORITY).toInt());

    if(m_prev_priority != m_priority)
    {
        QList<qint64> processIds = getAllProcessID();

        for(QList<qint64>::iterator i = processIds.begin(); i != processIds.end(); ++i)
        {
            if((bool)mainUi->m_com->setPriortyClass((DWORD)*i, (DWORD)m_priority))
            {
                mainUi->viewLog(eJOB_LOG_TYPE_JOB_STATUS,  tr("Priority updated. PID %1.").arg(QString::number((DWORD)*i)));
            }
        }
        m_prev_priority = m_priority;
    }
    return false;
}

void JobChef::updatePriortyStart(void)
{
    STMAILBOX mail_box = mainUi->m_pMailBox->createMailBoxDefault();
    mail_box.is_cyclic = true;
    mainUi->m_pMailBox->slotCreateMailBox(MailBox::eMODULE_JOB_CHEF, mail_box);
}
