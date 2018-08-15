#ifndef PROCESS_H
#define PROCESS_H

#include <QCoreApplication>
#include <QObject>
#include <QProcess>
#include <QDebug>

class Process : public QObject
{
    Q_OBJECT
public:
    explicit Process(QObject *parent = nullptr);
    ~Process();
    QProcess m_process_installer;

private slots:
    /*Piper Process*/
    virtual void slotInstallerProcessStarted();
    virtual void slotInstallerProcessReadyReadStandardOutput();
    virtual void slotInstallerProcessReadyReadStandardError();
    virtual void slotInstallerProcessFinished(int a_exitCode, QProcess::ExitStatus a_exitStatus);
    virtual void slotInstallerProcessError(QProcess::ProcessError a_error);
};

#endif // PROCESS_H
