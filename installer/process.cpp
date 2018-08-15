#include "process.h"
#include "main.h"

Process::Process(QObject *parent) : QObject(parent)
{
    connect(&m_process_installer, SIGNAL(started()),this, SLOT(slotInstallerProcessStarted()));
    connect(&m_process_installer, SIGNAL(finished(int,QProcess::ExitStatus)), this, SLOT(slotInstallerProcessFinished(int, QProcess::ExitStatus)));
    connect(&m_process_installer, SIGNAL(readyReadStandardOutput()), this, SLOT(slotInstallerProcessReadyReadStandardOutput()));
    connect(&m_process_installer, SIGNAL(readyReadStandardError()), this, SLOT(slotInstallerProcessReadyReadStandardError()));
    connect(&m_process_installer, SIGNAL(error(QProcess::ProcessError)), this, SLOT(slotInstallerProcessError(QProcess::ProcessError)));
}

Process::~Process()
{
}

void Process::slotInstallerProcessStarted()
{
    qStdOut() << "Installer Process started." << endl;

    if(!m_process_installer.isReadable())
    {
        qErrOut() << "Installer process is not Writable." << endl;
        return;
    }
}

void Process::slotInstallerProcessFinished(int a_exitCode, QProcess::ExitStatus a_exitStatus)
{
    QString message = tr("Installer Process has completed.");

    if(a_exitStatus == QProcess::CrashExit)
    {
        message = tr("Installer Process has crashed.");
    }

    qStdOut() << QString("%1 Exit code: %2").arg(message).arg(a_exitCode) << endl;
}

void Process::slotInstallerProcessReadyReadStandardError()
{
    QByteArray standardError = m_process_installer.readAllStandardError();
    QString standardErrorText = QString::fromUtf8(standardError);
    standardErrorText = standardErrorText.trimmed();
    if(!standardErrorText.isEmpty())
    {
        qErrOut() << standardErrorText << endl;
    }
}

void Process::slotInstallerProcessReadyReadStandardOutput()
{
    QByteArray standardOutput = m_process_installer.readAllStandardOutput();
    QString standardOutputText = QString::fromUtf8(standardOutput);
    standardOutputText = standardOutputText.trimmed();
    if(!standardOutputText.isEmpty())
    {
        qStdOut() << standardOutputText << endl;
    }
}

void Process::slotInstallerProcessError(QProcess::ProcessError a_error)
{
    switch(a_error)
    {
    case QProcess::FailedToStart:
        qErrOut() << "Encoder Process has failed to start." << endl;
        break;
    case QProcess::Crashed:
        qErrOut() << "Installer Process has crashed." << endl;
        break;
    case QProcess::Timedout:
        qErrOut() << "Installer Process timeout." << endl;
        break;
    case QProcess::ReadError:
        qErrOut() << "Installer Process read error occured." << endl;
        break;
    case QProcess::WriteError:
        qErrOut() << "Installer Process write error occured." << endl;
        break;
    case QProcess::UnknownError:
    default:
        qErrOut() << "Installer Process unknown error occured." << endl;
        break;
    }
}
