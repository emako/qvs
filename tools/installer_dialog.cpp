#include "installer_dialog.h"
#include "ui_installer_dialog.h"

const char BAT_INSTALLER_FILENAME[] = "qvs-installer-auto.bat";

const char *c_content_to_arg[InstallerDialog::eINSTALLER_CONTENTS_MAX] =
{
    "pfm",                /* eINSTALLER_CONTENTS_PFM */
    "vs64",               /* eINSTALLER_CONTENTS_VS64 */
    "avs32",              /* eINSTALLER_CONTENTS_AVS32 */
    "media",              /* eINSTALLER_CONTENTS_MEDIA */
    "vsedit-recovery",    /* eINSTALLER_CONTENTS_VSEDIT_RECOVERY */
    "vsedit-template",    /* eINSTALLER_CONTENTS_VSEDIT_TEMPLATE */
    "all",                /* eINSTALLER_CONTENTS_ALL */
};

InstallerDialog::InstallerDialog(QDialog *parent) :
    QDialog(parent),
    ui(new Ui::InstallerDialog)
{
    ui->setupUi(this);
    this->setup();
}

InstallerDialog::~InstallerDialog()
{
    delete ui;
}

void InstallerDialog::setup(void)
{
    g_pConfig->initInstallerConfig();
    this->loadInstallerConfig();
    this->setWindowFlags(Qt::Dialog | Qt::WindowCloseButtonHint);
    ui->treeWidgetModule->setHeaderHidden(false);

#ifndef QVS_PORTABLE
    int index = eINDEX_0;
    QTreeWidgetItemIterator i(ui->treeWidgetModule);

    while(*i)
    {
        if(index != (int)eINSTALLER_CONTENTS_MEDIA)
        {
            (*i)->setDisabled(true);
            (*i)->setCheckState(0, Qt::Unchecked);
            (*i)->setHidden(true);
        }
        i++;
        index++;
    }
#endif

    connect(&m_process_installer, SIGNAL(started()),this, SLOT(slotInstallerProcessStarted()));
    connect(&m_process_installer, SIGNAL(finished(int,QProcess::ExitStatus)), this, SLOT(slotInstallerProcessFinished(int, QProcess::ExitStatus)));
    connect(&m_process_installer, SIGNAL(readyReadStandardOutput()), this, SLOT(slotInstallerProcessReadyReadStandardOutput()));
    connect(&m_process_installer, SIGNAL(readyReadStandardError()), this, SLOT(slotInstallerProcessReadyReadStandardError()));
    connect(&m_process_installer, SIGNAL(error(QProcess::ProcessError)), this, SLOT(slotInstallerProcessError(QProcess::ProcessError)));
}

void InstallerDialog::loadInstallerConfig(void)
{
    m_checkstate.insert(Config::eCONFIG_INSTALLER_PFM, convertBoolToCheckState(g_pConfig->m_config_installer[Config::eCONFIG_INSTALLER_PFM].toBool()));
    m_checkstate.insert(Config::eCONFIG_INSTALLER_VS64, convertBoolToCheckState(g_pConfig->m_config_installer[Config::eCONFIG_INSTALLER_VS64].toBool()));
    m_checkstate.insert(Config::eCONFIG_INSTALLER_AVS32, convertBoolToCheckState(g_pConfig->m_config_installer[Config::eCONFIG_INSTALLER_AVS32].toBool()));
    m_checkstate.insert(Config::eCONFIG_INSTALLER_LAV, convertBoolToCheckState(g_pConfig->m_config_installer[Config::eCONFIG_INSTALLER_LAV].toBool()));
    m_checkstate.insert(Config::eCONFIG_INSTALLER_MEDIA, convertBoolToCheckState(g_pConfig->m_config_installer[Config::eCONFIG_INSTALLER_MEDIA].toBool()));

    int index = eINDEX_0;
    QTreeWidgetItemIterator i(ui->treeWidgetModule);
    while(*i)
    {
        if(!(*i)->isDisabled())
        {
            if(!ui->checkBoxUninstall->isChecked())
            {
                (*i)->setCheckState(0, convertBoolToCheckState(!convertCheckStateToBool(m_checkstate[static_cast<Config::ECONFIG_INSTALLER>(index)])));
            }
            else
            {
                (*i)->setCheckState(0, static_cast<Qt::CheckState>(m_checkstate[static_cast<Config::ECONFIG_INSTALLER>(index)]));
            }
        }
        i++;
        index++;
    }
}

bool InstallerDialog::convertCheckStateToBool(const Qt::CheckState &a_checkState)
{
    bool isChecked = false;

    if(a_checkState != Qt::Unchecked)
    {
        isChecked = true;
    }
    return isChecked;
}

Qt::CheckState InstallerDialog::convertBoolToCheckState(const bool &a_isChecked)
{
    Qt::CheckState checkState = Qt::Unchecked;

    if(a_isChecked)
    {
        checkState = Qt::Checked;
    }
    return checkState;
}

void InstallerDialog::on_checkBoxUninstall_stateChanged(int a_state)
{
    if(a_state)
    {
        ui->buttonInstall->setText(tr("Uninstall"));
    }
    else
    {
        ui->buttonInstall->setText(tr("Install"));
    }
    loadInstallerConfig();
}

void InstallerDialog::on_buttonSecletAll_clicked()
{
    QTreeWidgetItemIterator i(ui->treeWidgetModule);
    while(*i)
    {
        if(!(*i)->isDisabled())
        {
            (*i)->setCheckState(0, Qt::Checked);
        }
        i++;
    }
}

void InstallerDialog::on_buttonSelectNone_clicked()
{
    QTreeWidgetItemIterator i(ui->treeWidgetModule);
    while(*i)
    {
        if(!(*i)->isDisabled())
        {
            (*i)->setCheckState(0, Qt::Unchecked);
        }
        i++;
    }
}

void InstallerDialog::on_buttonDefault_clicked()
{
    loadInstallerConfig();
}

void InstallerDialog::on_buttonInstall_clicked()
{
    QStringList arg;
    int index = eINDEX_0;
    QTreeWidgetItemIterator i(ui->treeWidgetModule);
    bool isChecked;

    if(!ui->checkBoxUninstall->isChecked())
    {
        /* Install */
        arg << "-i";

        while(*i)
        {
            isChecked = convertCheckStateToBool((*i)->checkState(0));
            if(isChecked)
            {
                arg << c_content_to_arg[index];
                g_pConfig->setConfig(static_cast<Config::ECONFIG_INSTALLER>(index), true);
            }
            i++;
            index++;
        }
    }
    else
    {
        /* Uninstall */
        arg << "-u";

        while(*i)
        {
            isChecked = convertCheckStateToBool((*i)->checkState(0));
            if(isChecked)
            {
                arg << c_content_to_arg[index];
                g_pConfig->setConfig(static_cast<Config::ECONFIG_INSTALLER>(index), false);
            }
            i++;
            index++;
        }
    }

    if(arg.length() <= eINDEX_1)
    {
        QMessageBox::information(this, MESSAGE_WARNING, tr("Please select the module!"), QMessageBox::Ok);
        return;
    }

#ifdef QVS_BRANCH_VS_RECOVERY
    arg << c_content_to_arg[static_cast<int>(eINSTALLER_CONTENTS_VSEDIT_RECOVERY)];
    arg << c_content_to_arg[static_cast<int>(eINSTALLER_CONTENTS_VSEDIT_TEMPLATE)];
#endif

    saveCmd("qvs-installer", arg);
    m_process_installer.start(BAT_INSTALLER_FILENAME);
    ui->checkBoxUninstall->setEnabled(false);
    ui->buttonInstall->setEnabled(false);
    ui->buttonCancel->setEnabled(false);
}

bool InstallerDialog::saveCmd(QString a_exec, QStringList a_args)
{
    QFile file(BAT_INSTALLER_FILENAME);
    QTextStream out(&file);

    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qDebug() << "Open failed.";
        return false;
    }
    out << a_exec << QT_BLANK << a_args.join(QT_BLANK);
    file.close();
    return true;
}

void InstallerDialog::slotInstallerProcessStarted()
{
    qDebug() << "Installer Process started.";

    if(!m_process_installer.isReadable())
    {
        qDebug() << "Installer process is not Writable.";
        return;
    }
}

void InstallerDialog::slotInstallerProcessFinished(int a_exitCode, QProcess::ExitStatus a_exitStatus)
{
    QString message = tr("Installer Process has completed.");

    if(a_exitStatus == QProcess::CrashExit)
    {
        message = tr("Installer Process has crashed.");
    }
    qDebug() << QString("%1 Exit code: %2").arg(message).arg(a_exitCode);

    QFile(BAT_INSTALLER_FILENAME).remove();

    int apply = QMessageBox::information(this, MESSAGE_DONE, message, QMessageBox::Ok, QMessageBox::Cancel);
    if(apply == QMessageBox::Ok)
    {
        this->close();
    }
    ui->checkBoxUninstall->setEnabled(true);
    ui->buttonInstall->setEnabled(true);
    ui->buttonCancel->setEnabled(true);
}

void InstallerDialog::slotInstallerProcessReadyReadStandardError()
{
    QByteArray standardError = m_process_installer.readAllStandardError();
    QString standardErrorText = QString::fromUtf8(standardError);
    standardErrorText = standardErrorText.trimmed();
    if(!standardErrorText.isEmpty())
    {
        qDebug() << standardErrorText;
    }
}

void InstallerDialog::slotInstallerProcessReadyReadStandardOutput()
{
    QByteArray standardOutput = m_process_installer.readAllStandardOutput();
    QString standardOutputText = QString::fromUtf8(standardOutput);
    standardOutputText = standardOutputText.trimmed();
    if(!standardOutputText.isEmpty())
    {
        qDebug() << standardOutputText;
    }
}

void InstallerDialog::slotInstallerProcessError(QProcess::ProcessError a_error)
{
    switch(a_error)
    {
    case QProcess::FailedToStart:
        qDebug() << "Encoder Process has failed to start.";
        QMessageBox::information(this, MESSAGE_FAILED, tr("Installer has failed to start.\nPlease run Qvs as admin!"));
        break;
    case QProcess::Crashed:
        qDebug() << "Installer Process has crashed.";
        break;
    case QProcess::Timedout:
        qDebug() << "Installer Process timeout.";
        break;
    case QProcess::ReadError:
        qDebug() << "Installer Process read error occured.";
        break;
    case QProcess::WriteError:
        qDebug() << "Installer Process write error occured.";
        break;
    case QProcess::UnknownError:
        qDebug() << "Installer Process unknown error occured.";
        break;
    }
}
