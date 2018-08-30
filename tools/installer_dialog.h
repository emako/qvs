#ifndef INSTALLER_DIALOG_H
#define INSTALLER_DIALOG_H

#include "../com/config.h"

#include <QDialog>
#include <QDebug>

#undef QVS_PORTABLE
#define QVS_PORTABLE

class MainWindow;

namespace Ui {
class InstallerDialog;
}

class InstallerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit InstallerDialog(QWidget *parent = 0);
    ~InstallerDialog();
    class MainWindow *mainUi;
    friend class MainWindow;

    enum EINSTALLER_CONTENTS {
        eINSTALLER_CONTENTS_PFM,                /* Cmd */
        eINSTALLER_CONTENTS_VS64,               /* Reg */
        eINSTALLER_CONTENTS_AVS32,              /* Reg */
        eINSTALLER_CONTENTS_LAV,                /* Cmd */
        eINSTALLER_CONTENTS_MEDIA,              /* Reg */
        eINSTALLER_CONTENTS_VSEDIT_RECOVERY,    /* Cmd */
        eINSTALLER_CONTENTS_VSEDIT_TEMPLATE,    /* Cmd */
        eINSTALLER_CONTENTS_ALL,                /* Reg */
        eINSTALLER_CONTENTS_MAX,
    };

    bool convertCheckStateToBool(const Qt::CheckState &a_checkState);
    Qt::CheckState convertBoolToCheckState(const bool &a_isChecked);

private slots:
    /*Piper Process*/
    virtual void slotInstallerProcessStarted();
    virtual void slotInstallerProcessReadyReadStandardOutput();
    virtual void slotInstallerProcessReadyReadStandardError();
    virtual void slotInstallerProcessFinished(int a_exitCode, QProcess::ExitStatus a_exitStatus);
    virtual void slotInstallerProcessError(QProcess::ProcessError a_error);

    void on_checkBoxUninstall_stateChanged(int arg1);
    void on_buttonSecletAll_clicked();
    void on_buttonSelectNone_clicked();
    void on_buttonDefault_clicked();
    void on_buttonInstall_clicked();


private:
    Ui::InstallerDialog *ui;
    QMap<Config::ECONFIG_INSTALLER, Qt::CheckState> m_checkstate;
    QProcess m_process_installer;

    void setup(void);
    void loadInstallerConfig(void);
    bool saveCmd(QString a_exec, QStringList a_args);
};

#endif // INSTALLER_DIALOG_H
