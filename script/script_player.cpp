#include "script_player.h"
#include "../preview/preview_dialog.h"
#include "../mainwindow.h"
#include "../tools/std_watcher.h"
#include "ui_script_player.h"

static const QString c_pfm_root = "C:/Volumes";
static const QString c_pfm_log  = "error.log";

extern QMap<QUuid, StdWatcher*> g_pStdWatch;

ScriptPlayer::ScriptPlayer(QWidget *parent) :
    QWidget(parent),
    m_script_path_index(NULL),
    ui(new Ui::ScriptPlayer),
    m_isPlayOnMounted(false),
    m_isPlayAvsWith32Bit(false),
    m_reloadTitleShown(true)
{
    ui->setupUi(this);
    this->setupUi();
}

ScriptPlayer::~ScriptPlayer()
{
    delete m_pContextMenu;
    delete ui;
}

void ScriptPlayer::closeEvent(QCloseEvent *e)
{
    StdManager::releaseStdWatch(m_uid_std);
    releasePreviewDialog(m_uid_preview);
    mainUi->slotChildWindowClosed(m_uid_own);
    e->accept();
}

void ScriptPlayer::releasePreviewDialog(const QUuid &a_uid)
{
    if(mainUi->m_pPreviewDialogs.contains(a_uid))
    {
        mainUi->m_pPreviewDialogs[a_uid]->close();
    }
}

void ScriptPlayer::setupUi(void)
{
    this->setAttribute(Qt::WA_DeleteOnClose, true);
    ui->editInput->setReadOnly(true);
    ui->editMountMessage->setReadOnly(true);
    ui->labelMessage->clear();

    /* ContextMenu */
    m_pContextMenu = new QMenu(ui->editMountMessage);
    QAction *at_action_explore = new QAction(QIcon(":/buttons/folder_magnify.png"), tr("Explore"), ui->editMountMessage);
    QAction *at_action_copy_clip_path = new QAction(QIcon(":/buttons/page_paste.png"), tr("Copy clip path"), ui->editMountMessage);
    QAction *at_action_play_on_mounted = new QAction(QIcon(":/buttons/clock_play.png"), tr("Play on mounted"), ui->editMountMessage);
    QAction *at_action_show_stdwatcher = new QAction(QIcon(":/buttons/application_add.png"), tr("Show StdWatcher"), ui->editMountMessage);
    at_action_play_on_mounted->setCheckable(true);
    at_action_show_stdwatcher->setCheckable(true);
    m_pContextMenu->addActions(QList<QAction*>() << at_action_explore << at_action_copy_clip_path);
    m_pContextMenu->addSeparator();
    m_pContextMenu->addActions(QList<QAction*>() << at_action_play_on_mounted << at_action_show_stdwatcher);
    connect(at_action_explore, SIGNAL(triggered()), this, SLOT(exploreVolumes()));
    connect(at_action_copy_clip_path, SIGNAL(triggered()), this, SLOT(slotCopyClipPath()));
    connect(at_action_play_on_mounted, SIGNAL(triggered(bool)), this, SLOT(slotPlayOnMounted(bool)));
    connect(at_action_show_stdwatcher, SIGNAL(triggered(bool)), this, SLOT(showStdwatcher(bool)));

    loadCommonConfig();
}

void ScriptPlayer::reload(QString a_filename)
{
    ui->editInput->setText(a_filename);
    m_filename = a_filename;
    ui->editMountMessage->clear();
    ui->comboBoxArch->setEnabled(true);

    switch(reloadTypeDetect(a_filename))
    {
    case eSCRIPT_TYPE_VS:
        ui->buttonMount->setChecked(true);
        emit ui->buttonMount->clicked(true);
        break;
    case eSCRIPT_TYPE_AVS:
        ui->buttonMount->setChecked(true);
        emit ui->buttonMount->clicked(true);
        if(m_isPlayAvsWith32Bit)
        {
            ui->comboBoxArch->setCurrentIndex(eINDEX_1);/*32bit*/
            ui->comboBoxArch->setEnabled(false);
        }
        break;
    case eSCRIPT_TYPE_NOT_SCRIPT:
        setNotScriptMessage(a_filename);
        break;
    }
}

void ScriptPlayer::setNotScriptMessage(const QString &a_filename)
{
    ui->editMountMessage->setText(tr("Input: \"%1\"").arg(a_filename));
    ui->editMountMessage->append(tr("Detect: Not a script file."));
}

ScriptPlayer::ESCRIPT_TYPE ScriptPlayer::reloadTypeDetect(QString a_filename)
{
    QString ext = qvs::getFileExt(a_filename).toLower();
    ESCRIPT_TYPE type = eSCRIPT_TYPE_NOT_SCRIPT;

    if(ext == "vpy") /* Can't load *.py */
    {
        type = eSCRIPT_TYPE_VS;
    }
    else if(ext == "avs" || ext == "avsi")
    {
        type = eSCRIPT_TYPE_AVS;
    }
    m_script_type = type;

    return m_script_type;
}

void ScriptPlayer::dragEnterEvent(QDragEnterEvent* e)
{
    if(e->mimeData()->hasText())
    {
        e->acceptProposedAction();
    }
}

void ScriptPlayer::dropEvent(QDropEvent* e)
{
    const QMimeData* mime = e->mimeData();

    if(mime->hasUrls())
    {
        foreach(QUrl url, e->mimeData()->urls())
        {
            QFileInfo file(url.toLocalFile());
            QString filename = file.canonicalFilePath();
            filename = QDir::toNativeSeparators(filename);
            if(!QFileInfo(filename).isFile())
            {
                continue;
            }
            reload(filename);
        }
    }
    e->acceptProposedAction();
}

void ScriptPlayer::on_buttonMount_clicked(bool a_checked)
{
    if(reloadTypeDetect(m_filename) == eSCRIPT_TYPE_NOT_SCRIPT)
    {
        setNotScriptMessage(m_filename);
        ui->buttonMount->setChecked(false);
        return;
    }

    QString arch;
    QString cmd;

    if(a_checked)
    {
        switch(ui->comboBoxArch->currentIndex())
        {
        case eINDEX_0:
        default:
            arch = "x64";
            break;
        case eINDEX_1:
            arch = "x86";
            break;
        }

        if((m_script_type == eSCRIPT_TYPE_AVS) && (m_isPlayAvsWith32Bit == true))
        {
            arch = "x86";
        }

        cmd = QString("%1 -d \"%2\"").arg(qvs::findFirstFilePath(QString("%1_%2").arg(SCRIPT_PLAYER_EXEC_AVFS).arg(arch))).arg(m_filename);

        StdManager::releaseStdWatch(m_uid_std);
        m_uid_std = StdManager::createStdWatch();
        g_pStdWatch[m_uid_std]->mainUi = mainUi;
        g_pStdWatch[m_uid_std]->hide();
        g_pStdWatch[m_uid_std]->initJob(m_uid_std);
        g_pStdWatch[m_uid_std]->setCloseTime(static_cast<long>(eINDEX_0));
        g_pStdWatch[m_uid_std]->startJob(cmd);
        setErrorLog();
    }
    else
    {
        if(g_pStdWatch.contains(m_uid_std))
        {
            g_pStdWatch[m_uid_std]->abortJob();
            StdManager::releaseStdWatch(m_uid_std);
            ui->editMountMessage->setText(tr("Message: Avfs had been closed."));
        }
    }
}

void ScriptPlayer::setErrorLog(void)
{
    STMAILBOX mail_box = mainUi->m_pMailBox->createMailBoxDefault();
    mail_box.uid = m_uid_own;
    mail_box.type = eINDEX_0;
    mail_box.content = getErrorLogFilename();
    mail_box.is_cyclic = true; /* Run until detected errorlog file or stdwatcher was closed. */
    mainUi->m_pMailBox->slotCreateMailBox(MailBox::eMODULE_SCRIPT_PLAYER, mail_box);
}

bool ScriptPlayer::slotMail(STMAILBOX* a_mail_box)
{
    QVariant content = a_mail_box->content;

    switch(a_mail_box->type)
    {
    case eINDEX_0: // Tpye 0: Read error log file
        if(qvs::isFileExist(content.toString())) /* Errorlog filename. */
        {
            if(g_pStdWatch.contains(m_uid_std))
            {
                QString text = qvs::getFileText(content.toString());
                ui->editMountMessage->setText(text);
                if(m_isPlayOnMounted)
                {
                    emit ui->buttonPlay->click();
                }
                return true;
            }
        }
        break;
    default:
        break;
    }
    return false;
}

QString ScriptPlayer::getErrorLogFilename(void)
{
    QString script_filename = ui->editInput->text();
    QString error_log_filename = QString("%1/%2/%3").arg(c_pfm_root).arg(QFileInfo(getScriptRightMountedPath(script_filename)).fileName()).arg(c_pfm_log);

    m_script_path_index = NULL;
    if(qvs::isFileExist(error_log_filename))
    {
        /* Welding detected */
        for(int i = eINDEX_1; true; i++)
        {
            error_log_filename = QString("%1/%2-%3/%4").arg(c_pfm_root).arg(QFileInfo(getScriptRightMountedPath(script_filename)).fileName()).arg(i).arg(c_pfm_log);

            if(!qvs::isFileExist(error_log_filename))
            {
                m_script_path_index = static_cast<uint>(i);
                break;
            }
            else
            {
                error_log_filename.clear();
            }
        }
    }
    return error_log_filename;
}

QString ScriptPlayer::getScriptFilename(void)
{
    return QString("%1/%2/%3").arg(c_pfm_root).arg(QFileInfo(getScriptRightMountedPath(ui->editInput->text())).fileName()).arg(QFileInfo(m_filename).fileName());
}

QString ScriptPlayer::getScriptRightMountedPath(const QString &a_filename) const
{
    QString filename = a_filename;

    filename.remove(QT_BRACKET_L).remove(QT_BRACKET_R).remove(QT_BIKKURI_MARK);
    if(m_script_path_index != NULL)
    {
        filename = QString("%1-%2").arg(filename).arg(m_script_path_index);
    }
    return filename;
}

QString ScriptPlayer::getOutputFilename(void)
{
    /* Avi -> Wav -> Error */
    QString script_filename = QFileInfo(ui->editInput->text()).fileName();
    QString script_path = QDir::toNativeSeparators(QString("%1/%2/").arg(c_pfm_root).arg(getScriptRightMountedPath(script_filename)));
    QString play_filename = script_path + QFileInfo(qvs::chgFileExt(script_filename, "avi")).fileName();
    QString filename;

    qDebug() << play_filename;

    if(!qvs::isFileExist(play_filename))
    {
        play_filename = script_path + QFileInfo(qvs::chgFileExt(script_filename, "wav")).fileName();
    }
    if(!qvs::isFileExist(play_filename))
    {
        return filename;
    }
    filename = play_filename;
    return filename;
}

void ScriptPlayer::setReloadTitleShown(bool a_shown)
{
    m_reloadTitleShown = a_shown;
}

void ScriptPlayer::on_buttonPlay_clicked()
{
    if(!ui->buttonMount->isChecked())
    {
        QMessageBox::information(this, MESSAGE_INFORMATION, tr("No script mounted."), QMessageBox::Ok);
        return;
    }

    QString filename = getOutputFilename();

    if(filename.isEmpty())
    {
        QMessageBox::warning(this, MESSAGE_FAILED, tr("Source file is empty!"), QMessageBox::Ok);
        return;
    }

    releasePreviewDialog(m_uid_preview);

    switch(static_cast<ESCRIPT_PLAYER_PLAYER>(ui->comboBoxPlayer->currentIndex()))
    {
    case eSCRIPT_PLAYER_PLAYER_SYSTEM:
    default:
        QProcess::startDetached(QString("cmd /c \"%1\"").arg(filename));
        break;
    case eSCRIPT_PLAYER_PLAYER_PREVIEW:
        do{
            PreviewDialog *at_pPreviewDialog = new PreviewDialog();

            at_pPreviewDialog->mainUi = mainUi;
            m_uid_preview = QUuid::createUuid();
            at_pPreviewDialog->m_uid = m_uid_preview;
            at_pPreviewDialog->show();
            at_pPreviewDialog->m_reloadTitleShown = m_reloadTitleShown;
            at_pPreviewDialog->reload(filename.toStdString());
            mainUi->m_pPreviewDialogs.insert(at_pPreviewDialog->m_uid, at_pPreviewDialog);
        }while(false);
        break;
    case eSCRIPT_PLAYER_PLAYER_VIRTUAL_DUB64:
        QProcess::startDetached(QString("%1 \"%2\"").arg(qvs::findFirstFilePath(SCRIPT_PLAYER_EXEC_VIRTUALDUB64)).arg(filename));
        break;
    }
}

void ScriptPlayer::on_editMountMessage_customContextMenuRequested(const QPoint &)
{
    m_pContextMenu->exec(QCursor::pos());
}

void ScriptPlayer::exploreVolumes(void)
{
    if(m_filename.isEmpty())
    {
        return;
    }
    QFileInfo file(QDir::toNativeSeparators(getScriptFilename()));
    QDesktopServices::openUrl(QUrl::fromLocalFile(QString("file:///%1").arg(file.absolutePath())));
}

void ScriptPlayer::slotCopyClipPath(void)
{
    if(m_filename.isEmpty())
    {
        return;
    }

    QClipboard *clipboard = QApplication::clipboard();
    clipboard->setText(m_filename);
}

void ScriptPlayer::slotPlayOnMounted(bool a_isPlay)
{
    m_isPlayOnMounted = a_isPlay;
    m_pContextMenu->actions().at(eCONTEXT_MENU_PLAY_ON_MOUNTED)->setChecked(a_isPlay);
}

void ScriptPlayer::showStdwatcher(bool a_isShow)
{
    if(g_pStdWatch.contains(m_uid_std))
    {
        g_pStdWatch[m_uid_std]->setHidden(!a_isShow);
    }
    else
    {
        m_pContextMenu->actions().at(eCONTEXT_MENU_SHOW_STD_WATCHER)->setChecked(false);
        QMessageBox::information(this, MESSAGE_INFORMATION, tr("No Standard Watcher opened!"), QMessageBox::Ok);
    }
}

void ScriptPlayer::on_buttonInput_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Open Script file"), NULLSTR, tr("Script file (*.vpy *.avs *.avsi)"));

    if(!filename.isEmpty())
    {
        filename = QDir::toNativeSeparators(filename);
        reload(filename);
    }
}

void ScriptPlayer::loadCommonConfig(void)
{
    m_isPlayAvsWith32Bit = g_pConfig->getConfig(Config::eCONFIG_COMMON_PREFER_AVS_32BIT).toBool();
    ui->comboBoxPlayer->setCurrentIndex(g_pConfig->getConfig(Config::eCONFIG_COMMON_SCRIPT_PLAYER_PLAYER).toInt());

    if(m_isPlayAvsWith32Bit)
    {
        ui->labelMessage->setText(tr("Avisynth Script 32bit forced."));
    }
}

void ScriptPlayer::setPlayAvisynthWith32Bit(bool a_is32Bit)
{
    m_isPlayAvsWith32Bit = a_is32Bit;
}

void ScriptPlayer::on_comboBoxPlayer_currentIndexChanged(int a_index)
{
    g_pConfig->setConfig(Config::eCONFIG_COMMON_SCRIPT_PLAYER_PLAYER, a_index);
}
