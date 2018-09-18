#ifndef JOB_CREATOR_HELP_H
#define JOB_CREATOR_HELP_H

#include <QDialog>
#include <QProcess>
#include <QDebug>

class JobCreator;
class MainWindow;

namespace Ui {
class JobCreatorHelp;
}

class JobCreatorHelp : public QDialog
{
    Q_OBJECT

public:
    explicit JobCreatorHelp(QDialog *parent = nullptr);
    ~JobCreatorHelp();
    class JobCreator *mainUi;

    enum EJOB_ENCODER {
        eJOB_ENCODER_AVC,
        eJOB_ENCODER_HEVC,
        eJOB_ENCODER_NVENCC,
        eJOB_ENCODER_QSVENCC,
        eJOB_ENCODER_VCEENCC,
        eJOB_ENCODER_MAX,
    };

    enum EJOB_PIPER {
        eJOB_PIPER_VSPIPE,
        eJOB_PIPER_AVS4X26X,
        eJOB_PIPER_DIRECT,
        eJOB_PIPER_MAX,
    };

    void showHelp(EJOB_ENCODER a_encoder);
    void showHelp(EJOB_PIPER a_piper);

private:
    Ui::JobCreatorHelp *ui;
    QProcess m_process;

protected:
    void setupUi(void);
    void startJob(QString &a_cmd);

protected slots:
    virtual void slotProcessStarted();
    virtual void slotProcessReadyReadStandardError();
    virtual void slotProcessReadyReadStandardOutput();
    virtual void slotProcessFinished(int a_exitCode, QProcess::ExitStatus a_exitStatus);
    virtual void slotProcessError(QProcess::ProcessError a_error);

private slots:
    void on_buttonClose_clicked();
};

#endif // JOB_CREATOR_HELP_H
