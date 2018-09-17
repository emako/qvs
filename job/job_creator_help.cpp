#include "job_creator_help.h"
#include "ui_job_creator_help.h"
#include "job_creator.h"
#include "mainwindow.h"

JobCreatorHelp::JobCreatorHelp(QDialog *parent) :
    QDialog(parent),
    ui(new Ui::JobCreatorHelp)
{
    ui->setupUi(this);
    this->setupUi();
}

JobCreatorHelp::~JobCreatorHelp()
{
    delete ui;
}

void JobCreatorHelp::setupUi(void)
{
    ui->plainTextEdit->setLineWrapMode(QPlainTextEdit::NoWrap);
    connect(&m_process, SIGNAL(started()),this, SLOT(slotProcessStarted()));
    connect(&m_process, SIGNAL(finished(int, QProcess::ExitStatus)),this, SLOT(slotProcessFinished(int, QProcess::ExitStatus)));
    connect(&m_process, SIGNAL(error(QProcess::ProcessError)),this, SLOT(slotProcessError(QProcess::ProcessError)));
    connect(&m_process, SIGNAL(readyReadStandardError()), this, SLOT(slotProcessReadyReadStandardError()));
    connect(&m_process, SIGNAL(readyReadStandardOutput()), this, SLOT(slotProcessReadyReadStandardOutput()));
}

void JobCreatorHelp::showHelp(EJOB_ENCODER a_encoder)
{
    QString cmd;
    switch(a_encoder)
    {
    case eJOB_ENCODER_AVC:
    default:
        cmd = "x264_x64";
        break;
    case eJOB_ENCODER_HEVC:
        cmd = "x265_x64";
        break;
    case eJOB_ENCODER_NVENCC:
        cmd = "NVEncC64";
        break;
    case eJOB_ENCODER_QSVENCC:
        cmd = "QSVEncC64";
        break;
    case eJOB_ENCODER_VCEENCC:
        cmd = "VCEEncC64";
        break;
    }
    cmd = qvs::findFirstFilePath(cmd);
    if(cmd.indexOf(QT_PIPE) >= 0)
    {
        /* One process can't support pipe. */
        cmd = "cmd /c " + cmd;
    }
    if(!cmd.isEmpty())
    {
        if((a_encoder == eJOB_ENCODER_AVC) || (a_encoder == eJOB_ENCODER_HEVC))
        {
            cmd += " --fullhelp";
        }
    }
    ui->plainTextEdit->clear();
    startJob(cmd);
}

void JobCreatorHelp::showHelp(EJOB_PIPER a_piper)
{
    QString cmd;
    switch(a_piper)
    {
    case eJOB_PIPER_VSPIPE:
    default:
        cmd = "VSPipe";
        break;
    case eJOB_PIPER_AVS4X26X:
        cmd = "avs4x26x64";
        break;
    case eJOB_PIPER_DIRECT:
        cmd = "";
        break;
    }

    cmd = qvs::findFirstFilePath(cmd);
    ui->plainTextEdit->clear();
    startJob(cmd);
}

void JobCreatorHelp::startJob(QString &a_cmd)
{
#ifdef QT_DEBUG
    qDebug()<<a_cmd;
#endif

    ui->plainTextEdit->appendPlainText(a_cmd);
    m_process.start(a_cmd);
}

void JobCreatorHelp::slotProcessStarted()
{
    if(!m_process.isWritable())
    {
#ifdef QT_DEBUG
        qDebug()<<"Can not write to encoder.";
#endif
        return;
    }
}

void JobCreatorHelp::slotProcessReadyReadStandardError()
{
    QByteArray standardError = m_process.readAllStandardError();
    QString standardErrorText = QString::fromUtf8(standardError);
    standardErrorText = standardErrorText.trimmed();
    if(!standardErrorText.isEmpty())
    {
#ifdef QT_DEBUG
       qDebug()<<standardErrorText;
#endif
       ui->plainTextEdit->appendPlainText(standardErrorText);
    }
}

void JobCreatorHelp::slotProcessReadyReadStandardOutput()
{
    QByteArray standardOutput = m_process.readAllStandardOutput();
    QString standardOutputText = QString::fromUtf8(standardOutput);
    standardOutputText = standardOutputText.trimmed();
    if(!standardOutputText.isEmpty())
    {
#ifdef QT_DEBUG
       qDebug()<<standardOutputText;
#endif
       ui->plainTextEdit->appendPlainText(standardOutputText);
    }
}

void JobCreatorHelp::slotProcessError(QProcess::ProcessError a_error)
{
    switch(a_error)
    {
    case QProcess::FailedToStart:
#ifdef QT_DEBUG
        qDebug()<<"Process has failed to start.";
#endif
        break;
    case QProcess::Crashed:
#ifdef QT_DEBUG
        qDebug()<<"Process has crashed.";
#endif
        break;
    default:
        break;
    }
}

void JobCreatorHelp::slotProcessFinished(int a_exitCode, QProcess::ExitStatus a_exitStatus)
{
    QString message = "Process has completed.";

    if(a_exitStatus == QProcess::CrashExit)
    {
        message = "Process has crashed.";
    }
    if((a_exitCode != 0) && (a_exitCode != 1))
    {
        qDebug()<<QString("%1 Exit code: %2").arg(message).arg(a_exitCode);
    }
    ui->plainTextEdit->moveCursor(QTextCursor::Start);
}
