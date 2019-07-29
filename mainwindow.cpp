#include "mainwindow.h"
#include "mediainfo/mediainfo_loader.h"
#include "mediainfo/mediainfo_dialog.h"
#include "tools/muxer.h"
#include "tools/demuxer.h"
#include "tools/audio_enc.h"
#include "tools/audio_batch_enc.h"
#include "tools/installer_dialog.h"
#include "tools/splitter.h"
#include "tools/merge.h"
#include "script/script_player.h"
#include "preview/preview_dialog.h"
#include "script/script_creator.h"
#include "com/version.h"
#include "com/style_sheet.h"
#include "ui_muxer.h"
#include "ui_demuxer.h"
#include "ui_mainwindow.h"
#include "ui_audio_enc.h"
#include "ui_audio_batch_enc.h"
#include "ui_mediainfo_dialog.h"
#include "ui_script_player.h"
#include "ui_installer_dialog.h"
#include "ui_preview_dialog.h"
#include "ui_script_creator.h"
#include "ui_splitter.h"
#include "ui_merge.h"

#include "mediainfo/mediainfo_prober.h"

extern QMap<QUuid, StdWatcher*> g_pStdWatch;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    m_job_chef(new JobChef),
    m_logging(new Logging),
    m_pJobViewMenu(nullptr),
    m_pLogViewMenu(nullptr),
    m_pSystemTray(new QSystemTrayIcon(this)),
    ui(new Ui::MainWindow),
    m_pActionGruopOnCompletion(nullptr),
    m_pActionGruopLanguage(nullptr),
    m_pMsgBoxShutdown(nullptr)
{
    ui->setupUi(this);
    this->setupUi();
}

MainWindow::~MainWindow()
{
    delete m_pJobViewMenu;
    delete m_pLogViewMenu;
    delete m_job_chef;
    delete m_pActionGruopOnCompletion;
    delete m_pActionGruopLanguage;
    delete g_pConfig;
    delete ui;
    delete m_pTaskbarButton;
    delete m_pThumbnailToolBar;
    delete m_pSystemTray;
}

void MainWindow::setupUi(void)
{
    /*Macro*/
    g_pConfig->initCommonConfig(); //Init common config before.
    m_pActionGruopOnCompletion = new QActionGroup(this);
    m_pActionGruopLanguage = new QActionGroup(this);
    m_pJobViewMenu = new QMenu(ui->jobsView);
    m_pLogViewMenu = new QMenu(ui->logView);
    m_pTaskbarButton = new QWinTaskbarButton(this);
    m_pThumbnailToolBar = new QWinThumbnailToolBar(this);

    /*Property*/
    this->setWindowTitle(tr("Qvs"));
    this->setWindowIcon(QIcon(":/icons/qvs.ico"));
    this->setAcceptDrops(true);

    /*Init*/
    m_job_chef->mainUi = this;
    ui->widgetMerge->mainUi = this;
    ui->widgetAudioEnc->mainUi = this;
    ui->widgetMuxer->mainUi = this;
    ui->widgetDemuxer->mainUi = this;
    ui->widgetMediaInfo->mainUi = this;
    m_isAborted = false;
    m_jobs_index = eINDEX_0;
    m_job_status_prev = JobChef::eJOB_STATUS_INITIAL;
    m_isStartJobImmediately = false;
    Common::getInstance()->loadCommonConfig();
    Timer::getInstance()->start(Timer::eTIMER_TYPE_MAIL_BOX, Timer::eTIMER_SLOT_CHECK_UP_MAIL, TIMER_INTERVAL_MAIL);
    m_job_chef->updatePriortyStart();
    m_pSystemTray->setIcon(this->windowIcon());
    m_pSystemTray->setToolTip(this->windowTitle());
    m_pSystemTray->show();
    m_pSystemTray->hide();
    ui->widgetAudioEnc->init();
    m_pTaskbarButton->progress()->setMinimum(eINDEX_0);
    m_pTaskbarButton->progress()->setMaximum(eINDEX_100);
    m_pTaskbarButton->progress()->show();

    /*Ui*/
    ui->progressBar->setStyleSheet(c_qss_process_bar_pink_lady);
    ui->tabWidget->setCurrentIndex(eINDEX_0);
    ui->logView->setStyleSheet(c_qss_vertical_scroll_bar_alpha_gray);
    ui->logView->setLineWrapMode(QPlainTextEdit::NoWrap);
    ui->logView->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->jobsView->setStyleSheet(c_qss_table_widget_selection_bk_focus_in);
    ui->jobsView->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->jobsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->jobsView->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->jobsView->horizontalHeader()->setStretchLastSection(true);
    ui->jobsView->horizontalHeader()->show();
    ui->jobsView->setFrameShape(QFrame::StyledPanel);
    ui->jobsView->setColumnCount(eINDEX_3);
    ui->jobsView->setHorizontalHeaderLabels(QStringList() << tr("Job") << tr("Status") << tr("Progress"));
    ui->jobsView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->jobsView->setGeometry(eINDEX_0, eINDEX_0, eINDEX_100 * eINDEX_7, eINDEX_0);
    ui->jobsView->setColumnWidth(eINDEX_1, eINDEX_100);
    ui->jobsView->setColumnWidth(eINDEX_2, eINDEX_100);

    /*Signal*/
    setAcctions();
	connect(Common::getInstance(), SIGNAL(systemShutdown()), this, SLOT(close()));
	connect(Timer::getInstance(), SIGNAL(timeout(int, int)), this, SLOT(slotTimeout(int, int)));
	connect(MailBox::getInstance(), SIGNAL(mailRecived(EMODULE, STMAILBOX*)), this, SLOT(slotMail(EMODULE, STMAILBOX*)));
    connect(m_pSystemTray, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(slotTrayActivated(QSystemTrayIcon::ActivationReason)));
    connect(this, SIGNAL(ntfStartJob()), this, SLOT(startJob()));
    connect(this, SIGNAL(ntfFailJob()), this, SLOT(failJob()));
    connect(this, SIGNAL(ntfStatusChanged(JobChef::EJOB_STATUS)), this, SLOT(statusChanged(JobChef::EJOB_STATUS)));
    connect(ui->widgetAudioBatchEnc, SIGNAL(ntfStarted()), this, SLOT(slotAudioBatchEncStarted()));

    /*After Reload*/
    if(g_pConfig->getConfig(Config::eCONFIG_FIRST_FIRST_LAUNCH).toBool())
    {
        if(g_pConfig->isShowMainWindow())
        {
            QString version = g_pConfig->getReg(REG_KEY_VS_VERSION, REG_HKEY_SOFTWARE_VS);

            if(version.isEmpty())
            {
                /* Detected VapourSynth has not been installed. */
                this->show();
                emit ui->actionInstaller->triggered();
            }
            else
            {
#ifdef QT_DEBUG
                qDebug() << "Tip: Detected VapourSynth has been installed.";
#endif
            }
            g_pConfig->setConfig(Config::eCONFIG_FIRST_FIRST_LAUNCH, false);
        }
    }
}

void MainWindow::showEvent(QShowEvent *e)
{
#ifdef Q_OS_WIN32
    m_pTaskbarButton->setWindow(this->windowHandle());
# if false
    m_pThumbnailToolBar->setWindow(this->windowHandle());
# endif
#endif

    e->accept();
}

void MainWindow::closeEvent(QCloseEvent *e)
{
    if(isStarted())
    {
        int reply = QMessageBox::question(this, MESSAGE_QUESTION, tr("Do you really want to abort the job now?"), QMessageBox::Yes | QMessageBox::No);

        if (reply == QMessageBox::No)
        {
            e->ignore();
        }
        else if(reply == QMessageBox::Yes)
        {
            abortJob();
            e->accept();
        }
    }

	Timer::getInstance()->stopAll();
	MailBox::getInstance()->releaseMailBox();
    this->releaseChildWindowsAll();
    StdManager::releaseStdWatchAll();

    g_pConfig->saveConfigAll();
}

void MainWindow::setAcctions(void)
{
    /* JobViewMenu */
    QAction *at_action_preview = new QAction(QIcon(":/buttons/film.png"), tr("Preview"), ui->jobsView);
    QAction *at_action_explore = new QAction(QIcon(":/buttons/folder_magnify.png"), tr("Explore Job"), ui->jobsView);
    QAction *at_action_delete = new QAction(QIcon(":/buttons/trash.png"), tr("Delete Job"), ui->jobsView);
    QAction *at_action_eidt = new QAction(QIcon(":/buttons/sheduled_task.png"), tr("Edit Job"), ui->jobsView);
    QAction *at_action_view = new QAction(QIcon(":/buttons/date_task.png"), tr("View Job"), ui->jobsView);
    QAction *at_action_reset = new QAction(QIcon(":/buttons/restart.png"), tr("Reset Job"), ui->jobsView);
    QAction *at_action_move_up = new QAction(QIcon(":/buttons/arrow_up.png"), tr("Move Up"), ui->jobsView);
    QAction *at_action_move_down = new QAction(QIcon(":/buttons/arrow_down.png"), tr("Move Dwon"), ui->jobsView);
    m_pJobViewMenu->addActions(QList<QAction*>() << at_action_preview);
    m_pJobViewMenu->addSeparator();
    m_pJobViewMenu->addActions(QList<QAction*>() << at_action_explore << at_action_delete << at_action_eidt << at_action_view << at_action_reset);
    m_pJobViewMenu->addSeparator();
    m_pJobViewMenu->addActions(QList<QAction*>() << at_action_move_up << at_action_move_down);
    connect(at_action_preview, SIGNAL(triggered()), this, SLOT(slotPreview()));
    connect(at_action_explore, SIGNAL(triggered()), this, SLOT(exploreJob()));
    connect(at_action_delete, SIGNAL(triggered()), this, SLOT(delJob()));
    connect(at_action_eidt, SIGNAL(triggered()), this, SLOT(editJob()));
    connect(at_action_view, SIGNAL(triggered()), this, SLOT(viewJobCmd()));
    connect(at_action_reset, SIGNAL(triggered()), this, SLOT(resetJob()));
    connect(at_action_move_up, SIGNAL(triggered()), this, SLOT(moveUpJob()));
    connect(at_action_move_down, SIGNAL(triggered()), this, SLOT(moveDownJob()));

    /* LogViewMenu */
    QAction *at_action_log_copy = new QAction(QIcon(":/buttons/page_paste.png"), tr("Copy to Clipboard"), ui->logView);
    QAction *at_action_log_save = new QAction(QIcon(":/buttons/disk.png"), tr("Save to File..."), ui->logView);
    QAction *at_action_log_clear = new QAction(QIcon(":/buttons/erase.png"), tr("Clear log"), ui->logView);
    QAction *at_action_log_enable_line_wrapping = new QAction(QIcon(":/buttons/text_wrapping.png"), tr("Enable Line Wrap"), ui->logView);
    at_action_log_enable_line_wrapping->setCheckable(true);
    m_pLogViewMenu->addActions(QList<QAction*>() << at_action_log_copy << at_action_log_save << at_action_log_clear);
    m_pLogViewMenu->addSeparator();
    m_pLogViewMenu->addAction(at_action_log_enable_line_wrapping);
    connect(at_action_log_copy, SIGNAL(triggered()), this, SLOT(logCopy()));
    connect(at_action_log_clear, SIGNAL(triggered()), this, SLOT(logClear()));
    connect(at_action_log_save, SIGNAL(triggered()), this, SLOT(logSave()));
    connect(at_action_log_enable_line_wrapping, SIGNAL(triggered(bool)), this, SLOT(logSetWrapped(bool)));

    /* AppMenu */
    connect(ui->actionOpen, SIGNAL(triggered()), this, SLOT(selectOpenfile()));
    connect(ui->actionAddJob, SIGNAL(triggered()), this, SLOT(on_buttonAddJob_clicked()));
    connect(ui->actionCommand_Line, SIGNAL(triggered()), this, SLOT(openCommandLine()));
    connect(ui->actionPython, SIGNAL(triggered()), this, SLOT(openPython()));
    connect(ui->actionPreferences, SIGNAL(triggered()), this, SLOT(showPreferences()));
    connect(ui->actionInstaller, SIGNAL(triggered()), this, SLOT(showInstaller()));

    /* JobMenu */
    connect(ui->actionJob_Start, SIGNAL(triggered()), this, SLOT(on_buttonStartJob_clicked()));
    connect(ui->actionJob_Pause, SIGNAL(triggered(bool)), this, SLOT(on_buttonPauseJob_clicked(bool)));
    connect(ui->actionJob_Abort, SIGNAL(triggered()), this, SLOT(on_buttonAbortJob_clicked()));
    connect(ui->actionJob_Explore, SIGNAL(triggered()), this, SLOT(exploreJob()));
    connect(ui->actionJob_Delete, SIGNAL(triggered()), this, SLOT(delJob()));
    connect(ui->actionJob_Edit, SIGNAL(triggered()), this, SLOT(editJob()));
    connect(ui->actionJob_View, SIGNAL(triggered()), this, SLOT(viewJobCmd()));
    connect(ui->actionJob_Reset, SIGNAL(triggered()), this, SLOT(resetJob()));
    connect(ui->actionJob_MoveUp, SIGNAL(triggered()), this, SLOT(moveUpJob()));
    connect(ui->actionJob_MoveDown, SIGNAL(triggered()), this, SLOT(moveDownJob()));

    /* CleanUpMenu */
    connect(ui->actionCleanupFinished, SIGNAL(triggered()), this, SLOT(cleanUpFinished()));
    connect(ui->actionCleanupAll, SIGNAL(triggered()), this, SLOT(cleanUpAll()));
    connect(ui->actionCleanLoggingFile, SIGNAL(triggered()), this, SLOT(cleanLoggingFile()));

    /* OnCompletionMenu */
    m_pActionGruopOnCompletion->addAction(ui->actionPostOp_PowerDown);
    m_pActionGruopOnCompletion->addAction(ui->actionPostOp_Hibernate);
    m_pActionGruopOnCompletion->addAction(ui->actionPostOp_DoNothing);

    /* LanguageMenu */
    m_pActionGruopLanguage->addAction(ui->actionLanguageEnglish);
    m_pActionGruopLanguage->addAction(ui->actionLanguageChinese);
    m_pActionGruopLanguage->addAction(ui->actionLanguageJapanese);
    setLanguage(static_cast<Config::ELANGUAGE>(g_pConfig->getConfig(Config::eCONFIG_FIRST_LANGUAGE).toInt()));
    for(int i = eINDEX_0; i < m_pActionGruopLanguage->actions().length(); i++)
    {
        connect(m_pActionGruopLanguage->actions().at(i), SIGNAL(triggered()), this, SLOT(languageChanged()));
    }

    /* View */
    connect(ui->actionMinimize, SIGNAL(triggered()), this, SLOT(slotMinimize()));
    connect(ui->actionJobsLog, SIGNAL(triggered()), this, SLOT(slotViewJobsLog()));

    /* Tools */
    connect(ui->actionPreviewDialog, SIGNAL(triggered()), this, SLOT(openPreviewDialog()));
    connect(ui->actionScriptCreator, SIGNAL(triggered()), this, SLOT(openScriptCreator()));
    connect(ui->actionScriptPlayer, SIGNAL(triggered()), this, SLOT(openScriptPlayer()));
    connect(ui->actionVSedit, SIGNAL(triggered()), this, SLOT(openTools()));
    connect(ui->actionD2VWitch, SIGNAL(triggered()), this, SLOT(openTools()));
    connect(ui->actionWobbly, SIGNAL(triggered()), this, SLOT(openTools()));
    connect(ui->actionWibbly, SIGNAL(triggered()), this, SLOT(openTools()));

    /* Help */
    connect(ui->actionCheckForUpdates, SIGNAL(triggered()), this, SLOT(slotOpenUrl()));
    connect(ui->actionWebX264, SIGNAL(triggered()), this, SLOT(slotOpenUrl()));
    connect(ui->actionWebX265, SIGNAL(triggered()), this, SLOT(slotOpenUrl()));
    connect(ui->actionWebX264VideoLAN, SIGNAL(triggered()), this, SLOT(slotOpenUrl()));
    connect(ui->actionWebX264Komisar, SIGNAL(triggered()), this, SLOT(slotOpenUrl()));
    connect(ui->actionWebX264FreeCodecs, SIGNAL(triggered()), this, SLOT(slotOpenUrl()));
    connect(ui->actionWebX265Fllear, SIGNAL(triggered()), this, SLOT(slotOpenUrl()));
    connect(ui->actionWebX265LigH, SIGNAL(triggered()), this, SLOT(slotOpenUrl()));
    connect(ui->actionWebX265Snowfag, SIGNAL(triggered()), this, SLOT(slotOpenUrl()));
    connect(ui->actionWebX265FreeCodecs, SIGNAL(triggered()), this, SLOT(slotOpenUrl()));
    connect(ui->actionWebAvisynth32, SIGNAL(triggered()), this, SLOT(slotOpenUrl()));
    connect(ui->actionWebAvisynth64, SIGNAL(triggered()), this, SLOT(slotOpenUrl()));
    connect(ui->actionWebAvisynthPlus, SIGNAL(triggered()), this, SLOT(slotOpenUrl()));
    connect(ui->actionWebVapourSynth, SIGNAL(triggered()), this, SLOT(slotOpenUrl()));
    connect(ui->actionWebLAVFilter, SIGNAL(triggered()), this, SLOT(slotOpenUrl()));
    connect(ui->actionWebNVEncC, SIGNAL(triggered()), this, SLOT(slotOpenUrl()));
    connect(ui->actionWebQSVEncC, SIGNAL(triggered()), this, SLOT(slotOpenUrl()));
    connect(ui->actionWebVCEEncC, SIGNAL(triggered()), this, SLOT(slotOpenUrl()));
    connect(ui->actionOnlineDocX264, SIGNAL(triggered()), this, SLOT(slotOpenUrl()));
    connect(ui->actionOnlineDocX265, SIGNAL(triggered()), this, SLOT(slotOpenUrl()));
    connect(ui->actionWebAvsWiki, SIGNAL(triggered()), this, SLOT(slotOpenUrl()));
    connect(ui->actionWebVapourSynthDocs, SIGNAL(triggered()), this, SLOT(slotOpenUrl()));
    connect(ui->actionAbout, SIGNAL(triggered()), this, SLOT(slotAbout()));
    connect(ui->actionAboutQt, SIGNAL(triggered()), this, SLOT(slotAboutQt()));

    /* ThumbnailTool */
    QWinThumbnailToolButton *thumbnailToolStartJob = new QWinThumbnailToolButton(m_pThumbnailToolBar);
    QWinThumbnailToolButton *thumbnailToolAbortJob = new QWinThumbnailToolButton(m_pThumbnailToolBar);
    thumbnailToolStartJob->setToolTip(tr("Start Job"));
    thumbnailToolStartJob->setIcon(QIcon(":/buttons/start_green.png"));
    thumbnailToolAbortJob->setToolTip(tr("Abort Job"));
    thumbnailToolAbortJob->setIcon(QIcon(":/buttons/stop_red.png"));
    m_pThumbnailToolBar->addButton(thumbnailToolStartJob);
    m_pThumbnailToolBar->addButton(thumbnailToolAbortJob);
    connect(thumbnailToolStartJob, SIGNAL(clicked()), this, SLOT(on_buttonStartJob_clicked()));
    connect(thumbnailToolAbortJob, SIGNAL(clicked()), this, SLOT(on_buttonAbortJob_clicked()));
}

void MainWindow::slotOpenUrl(void)
{
    const QMap<QObject *, QString> c_url_map =
    {
        { nullptr,                      "https://github.com/emako/qvs" },
        { ui->actionCheckForUpdates,    "https://github.com/emako/qvs/releases" },
        { ui->actionWebX264,            "http://www.videolan.org/developers/x264.html" },
        { ui->actionWebX265,            "http://www.videolan.org/developers/x265.html" },
        { ui->actionWebX264VideoLAN,    "http://download.videolan.org/pub/x264/binaries" },
        { ui->actionWebX264Komisar,     "http://komisar.gin.by" },
        { ui->actionWebX264FreeCodecs,  "http://www.free-codecs.com/x264_video_codec_download.htm" },
        { ui->actionWebX265Fllear,      "http://x265.ru/en/builds" },
        { ui->actionWebX265LigH,        "https://www.mediafire.com/?6lfp2jlygogwa" },
        { ui->actionWebX265Snowfag,     "http://builds.x265.eu" },
        { ui->actionWebX265FreeCodecs,  "http://www.free-codecs.com/x265_hevc_encoder_download.htm" },
        { ui->actionWebAvisynth32,      "https://sourceforge.net/projects/avisynth2/files/AviSynth%202.6" },
        { ui->actionWebAvisynth64,      "http://forum.doom9.org/showthread.php?t=152800" },
        { ui->actionWebAvisynthPlus,    "http://www.avs-plus.net" },
        { ui->actionWebVapourSynth,     "http://www.vapoursynth.com" },
        { ui->actionWebLAVFilter,       "https://github.com/Nevcairiel/LAVFilters/releases" },
        { ui->actionWebNVEncC,          "https://github.com/rigaya/NVEnc/releases" },
        { ui->actionWebQSVEncC,         "https://github.com/rigaya/QSVEnc/releases" },
        { ui->actionWebVCEEncC,         "https://github.com/rigaya/VCEEnc/releases" },
        { ui->actionOnlineDocX264,      "http://en.wikibooks.org/wiki/MeGUI/x264_Settings" },
        { ui->actionOnlineDocX265,      "http://x265.readthedocs.org/en/default" },
        { ui->actionWebAvsWiki,         "http://avisynth.nl/index.php/Main_Page#Usage" },
        { ui->actionWebVapourSynthDocs, "http://www.vapoursynth.com/doc" },
    };

    if(c_url_map.contains(sender()))
    {
		Common::getInstance()->openUrl(c_url_map[sender()]);
    }
}

void MainWindow::cleanUpAll(void)
{
    int row = ui->jobsView->rowCount();

    for(int i = eINDEX_0; i < row; i++)
    {
        ui->jobsView->removeRow(eINDEX_0);
        m_jobs.removeAt(eINDEX_0);
    }
}

void MainWindow::cleanLoggingFile(void)
{
    if(m_job_chef->isStarted())
    {
        QMessageBox::warning(this, MESSAGE_WARNING, tr("Can't clean while the job running."));
    }
    else
    {
        m_logging->restart();
    }
}

int MainWindow::getFirstJobStatusIndex(JobChef::EJOB_STATUS a_status)
{
    int i = eINDEX_NONE;
    bool has = false;

    for(i = eINDEX_0; i < ui->jobsView->rowCount(); i++)
    {
        if(ui->jobsView->item(i, eINDEX_1)->text() == getJobStatusText(a_status))
        {
            has = true;
            break;
        }
    }

    if(!has)
    {
        return eINDEX_NONE;
    }
    return i;
}

void MainWindow::cleanUpStatusAll(JobChef::EJOB_STATUS a_status)
{
    while(true)
    {
        int index = getFirstJobStatusIndex(a_status);

        if(index == eINDEX_NONE)
        {
            break;
        }
        ui->jobsView->removeRow(index);
        m_jobs.removeAt(index);
    }
}

void MainWindow::cleanUpFinished(void)
{
    cleanUpStatusAll(JobChef::eJOB_STATUS_COMPLETED);
}

void MainWindow::selectOpenfile(void)
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Open Media/Script file"), QString(), tr("Media/Script (*.*)"));

    if(!filename.isEmpty())
    {
        execJobCreator(JobCreator::eJOB_RELOAD_DROP, filename);
    }
}

void MainWindow::logCopy(void)
{
    QClipboard *clipboard = QApplication::clipboard();

    clipboard->setText(ui->logView->toPlainText());
}

void MainWindow::logClear(void)
{
    ui->logView->clear();
}

void MainWindow::logSave(void)
{
    QString filename = QFileDialog::getSaveFileName(this, tr("Edit Filename"), NULLSTR, "Log File (*.log)");

    if(filename.isEmpty())
    {
        return;
    }

    QFile file(filename);
    QTextStream out(&file);

    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qDebug() << "Open log failed.";
        return;
    }
    out << ui->logView->toPlainText();
    file.close();
}

void MainWindow::logSetWrapped(bool a_enable)
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

void MainWindow::viewJobCmd(void)
{
    int row = ui->jobsView->currentRow();

    if(row >= eINDEX_0)
    {
        JobItem job_item = m_jobs.at(row);

        JobViewCmd job_view_cmd;
        job_view_cmd.mainUi = this;
        job_view_cmd.reload(job_item);
        job_view_cmd.exec();
    }
}

void MainWindow::slotPreview(void)
{
    int row = ui->jobsView->currentRow();
    QString source_path;
    JobItem job_item;

    if(row >= eINDEX_0)
    {
        job_item = m_jobs.at(row);
        source_path = job_item.job_config[JobCreator::eJOB_CONFIG_INPUT].toString();
    }
    if(source_path.isEmpty())
    {
        return;
    }

    ScriptPlayer *at_pScriptPlayer = new ScriptPlayer();

    at_pScriptPlayer->mainUi = this;
    at_pScriptPlayer->m_uid_own = QUuid::createUuid();

    if(at_pScriptPlayer->reloadTypeDetect(source_path) == ScriptPlayer::eSCRIPT_TYPE_NOT_SCRIPT)
    {
        at_pScriptPlayer->hide();
        QProcess::startDetached(QString("cmd /c %1").arg(source_path));
        delete at_pScriptPlayer;
        at_pScriptPlayer = nullptr;
    }
    else
    {
        at_pScriptPlayer->show();
        at_pScriptPlayer->slotPlayOnMounted(true);
        at_pScriptPlayer->setPlayAvisynthWith32Bit(false);
        at_pScriptPlayer->ui->comboBoxArch->setCurrentIndex(job_item.job_config[JobCreator::eJOB_CONFIG_ARCH].toInt());
        at_pScriptPlayer->reload(source_path);
        m_pScriptPlayers.insert(at_pScriptPlayer->m_uid_own, at_pScriptPlayer);
    }
}

void MainWindow::exploreJob(void)
{
    int row = ui->jobsView->currentRow();

    if(row >= eINDEX_0)
    {
        QFileInfo file(m_jobs.at(row).job_config[JobCreator::eJOB_CONFIG_OUTPUT].toString());
        QDesktopServices::openUrl(QUrl::fromLocalFile(QString("file:///%1").arg(file.absolutePath())));
    }
}

void MainWindow::editJob(void)
{
    int row = ui->jobsView->currentRow();

    if(row >= eINDEX_0)
    {
        execJobCreator(JobCreator::eJOB_RELOAD_EDIT);
    }
}

void MainWindow::resetJob(void)
{
    int row = ui->jobsView->currentRow();

    if(row >= eINDEX_0)
    {
        QTableWidgetItem *item;
        item = ui->jobsView->item(row, eINDEX_1);
        if( (item->text() == getJobStatusText(JobChef::eJOB_STATUS_ABORTED))
         || (item->text() == getJobStatusText(JobChef::eJOB_STATUS_FAILED))
         || (item->text() == getJobStatusText(JobChef::eJOB_STATUS_COMPLETED)) )
        {
            item->setText(getJobStatusText(JobChef::eJOB_STATUS_READY));

            item = ui->jobsView->item(row, eINDEX_0);
            item->setIcon(getJobStatusIcon(JobChef::eJOB_STATUS_READY));

            item = ui->jobsView->item(row, eINDEX_2);
            item->setText(QString::number(false) + QString("%"));
        }
    }
}

void MainWindow::moveUpJob(void)
{
    if(!isPaused())
    {
        int row = ui->jobsView->currentRow();

        qvs::moveRowUi(ui->jobsView, row, row - eINDEX_1);
        qvs::moveRow(&m_jobs, row, row - eINDEX_1);
    }
    else
    {
        QMessageBox::warning(this, MESSAGE_WARNING, tr("Can't move the job on pausing mode."));
    }
}

void MainWindow::moveDownJob(void)
{
    if(!isPaused())
    {
        int row = ui->jobsView->currentRow();

        qvs::moveRowUi(ui->jobsView, row, row + eINDEX_2);
        qvs::moveRow(&m_jobs, row, row + eINDEX_1);
    }
    else
    {
        QMessageBox::warning(this, MESSAGE_WARNING, tr("Can't move the job on pausing mode."));
    }
}

void MainWindow::delJob(void)
{
    int row = ui->jobsView->currentRow();

    if(row >= eINDEX_0)
    {
        ui->jobsView->removeRow(row);
        m_jobs.removeAt(row);
    }
}

void MainWindow::saveJob(JobItem a_job_item, JobCreator::EJOB_RELOAD a_job_reload)
{
    switch(a_job_reload)
    {
    case JobCreator::eJOB_RELOAD_NEW:
    case JobCreator::eJOB_RELOAD_DROP:
    default:
        m_jobs.append(a_job_item);
        break;
    case JobCreator::eJOB_RELOAD_EDIT:
        do {
            int row = ui->jobsView->currentRow();
            m_jobs.removeAt(row);
            m_jobs.insert(row, a_job_item);
        } while(false);
        break;
    }

    /* Debug Print */
#ifdef QT_DEBUG
    for(QMap<JobCreator::EJOB_CONFIG, QVariant>::const_iterator i = a_job_item.job_config.constBegin(); i != a_job_item.job_config.constEnd(); ++i)
    {
        qDebug() << i.key() << ":" << i.value();
    }
    for(int i = 0; i < a_job_item.job_cmds.length(); i++)
    {
        qDebug() << "Job:" << a_job_item.job_name << "UID:" << a_job_item.job_cmds.at(i).uid << "," << "Exec:" << a_job_item.job_cmds.at(i).type << "," << "Command:" << a_job_item.job_cmds.at(i).cmd;
    }
#endif
}

bool MainWindow::isStarted(void)
{
    return m_job_chef->isStarted();
}

bool MainWindow::isPaused(void)
{
    return ui->buttonPauseJob->isChecked();
}

bool MainWindow::isAborted(void)
{
    return m_isAborted;
}

void MainWindow::viewLog(JobChef::EJOB_LOG_TYPE a_log_type, const QString &a_log)
{
    QString html;

    switch(a_log_type)
    {
    case JobChef::eJOB_LOG_TYPE_DEBUG:
        qDebug() << a_log;
        break;
    case JobChef::eJOB_LOG_TYPE_INFO:
        html = qvs::toHtml(a_log, COLOR_LOGGING_INFO, true);
        ui->logView->appendHtml(html);
        break;
    case JobChef::eJOB_LOG_TYPE_WARN:
    case JobChef::eJOB_LOG_TYPE_ERROE:
    case JobChef::eJOB_LOG_TYPE_FATAL:
        html = qvs::toHtml(a_log, COLOR_LOGGING_WARN, true);
        ui->logView->appendHtml(html);
        m_pTaskbarButton->progress()->stop();
        m_pTaskbarButton->progress()->setValue(eINDEX_0);
        break;
    case JobChef::eJOB_LOG_TYPE_JOB_STATUS:
        html = qvs::toHtml(a_log, COLOR_LOGGING_STATUS, true);
        ui->logView->appendHtml(html);
        break;
    case JobChef::eJOB_LOG_TYPE_JOB_STD_ERROR:
        html = qvs::toHtml(a_log, COLOR_LOGGING_STD_ERROR, true);
        ui->logView->appendHtml(html);
        break;
    case JobChef::eJOB_LOG_TYPE_JOB_STD_OUTPUT:
        html = qvs::toHtml(a_log, COLOR_LOGGING_STD_OUTPUT, true);
        ui->logView->appendHtml(html);
        break;
    case JobChef::eJOB_LOG_TYPE_JOB_STD_PROGRESS:
        ui->progressBar->setMaximum(eINDEX_100);
        if( (m_jobs_index <= ui->jobsView->rowCount())
         && (ui->jobsView->columnCount() >= eINDEX_3) )
        {
            delete ui->jobsView->item(m_jobs_index - eINDEX_1, eINDEX_2);
            ui->jobsView->setItem(m_jobs_index - eINDEX_1, eINDEX_2, new QTableWidgetItem(QString("%1%").arg(a_log)));
        }
        ui->progressBar->setValue(static_cast<int>(a_log.toDouble()));
        m_pTaskbarButton->progress()->resume();
        if(static_cast<int>(a_log.toDouble()) == eINDEX_100)
        {
            m_pTaskbarButton->progress()->setValue(static_cast<int>(eINDEX_0));
        }
        else
        {
            m_pTaskbarButton->progress()->setValue(static_cast<int>(a_log.toDouble()));
        }
        break;
    case JobChef::eJOB_LOG_TYPE_JOB_STD_DETAILS:
        setDetailLog(a_log);
        break;
    default:
        break;
    }

    if(html.isEmpty())
    {
        html = qvs::toHtml(a_log, COLOR_LOGGING_DEFAULT, true);
    }

    if(a_log_type != JobChef::eJOB_LOG_TYPE_JOB_STD_PROGRESS)
    {
        logging(html);
    }
}

void MainWindow::setDetailLog(const QString &a_log)
{
    QString log = a_log;

    if(a_log.indexOf(QString(QT_MAC_EOL)) >= eINDEX_0)
    {
        log = a_log.left(a_log.indexOf(QString(QT_MAC_EOL)));
    }
    ui->editDetails->setText(log);
}

void MainWindow::setInsertTextColor(QColor a_color, int a_length)
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

void MainWindow::on_buttonAddJob_clicked(void)
{
    execJobCreator(JobCreator::eJOB_RELOAD_NEW);
}

void MainWindow::on_buttonStartJob_clicked(void)
{
    reqJobStart();
}

void MainWindow::reqJobStart(void)
{
    if(!isEmptyJobs() && !isStarted())
    {
        initJob();
        emit ntfStartJob();
    }
}

void MainWindow::setStartJobImmediately(bool a_set)
{
    m_isStartJobImmediately = a_set;
}

void MainWindow::initJob(void)
{
    ui->logView->clear();
    viewLog(JobChef::eJOB_LOG_TYPE_DEBUG, tr("o=o=o=o=o=o=o=o=o=o=o=o=o=o=o=o=o=o=o=o=o=o=o=o=o=o"));
    setDetailLog(tr("Job Initialising ..."));
    m_jobs_index = eINDEX_0;
    m_isAborted = false;
    ui->progressBar->setMaximum(eINDEX_0);
    ui->progressBar->setMinimum(eINDEX_0);
    m_pTaskbarButton->progress()->resume();
    m_pTaskbarButton->progress()->setValue(eINDEX_0);
    m_job_chef->loadCommonConfig();
    emit ntfStatusChanged(JobChef::eJOB_STATUS_STARTING);
}

bool MainWindow::isSkipJob(void)
{
    if(m_jobs_index < ui->jobsView->rowCount())
    {
        if(ui->jobsView->item(m_jobs_index, eINDEX_1)->text() != getJobStatusText(JobChef::eJOB_STATUS_READY))
        {
            return true;
        }
    }
    return false;
}

bool MainWindow::isEmptyJobs(void)
{
    bool is_empty_jobs = true;

    for(int at_jobs_index = eINDEX_0; at_jobs_index < ui->jobsView->rowCount(); at_jobs_index++)
    {
        if(ui->jobsView->item(at_jobs_index, eINDEX_1)->text() == getJobStatusText(JobChef::eJOB_STATUS_READY))
        {
            is_empty_jobs = false;
        }
    }
    return is_empty_jobs;
}

void MainWindow::startJob(void)
{
    bool is_started = false;

    while(isSkipJob())
    {
        m_jobs_index++;
    }
    if(m_jobs_index < m_jobs.length())
    {
        m_job_chef->initJob(m_jobs.at(m_jobs_index).job_cmds);
        is_started = true;
    }
    m_jobs_index++;

    if(is_started)
    {
        QString log = tr("Job Started at %1.").arg(qvs::currentDateTime());

        viewLog(JobChef::eJOB_LOG_TYPE_JOB_STATUS, log);
        setDetailLog(log);
        m_job_chef->startJob();
    }
    else
    {
        allCompleted();
    }
}

void MainWindow::appendItems(QStringList a_contents)
{
    int row = ui->jobsView->rowCount();

    ui->jobsView->setRowCount(row + eINDEX_1);
    for(int i = eINDEX_0; i < a_contents.length(); i++)
    {
        if(i == eINDEX_0)
        {
            addItem(row, i, a_contents.at(i), QIcon(":/buttons/hourglass.png"));
        }
        else
        {
            addItem(row, i, a_contents.at(i));
        }
    }
}

void MainWindow::addItem(int a_row, int a_col, QString a_content)
{
    QTableWidgetItem *item = new QTableWidgetItem(a_content);
    ui->jobsView->setItem(a_row, a_col, item);
}

void MainWindow::addItem(int a_row, int a_col, QString a_content, QIcon a_icon)
{
    QTableWidgetItem *item = new QTableWidgetItem(a_icon, a_content);
    ui->jobsView->setItem(a_row, a_col, item);
}

void MainWindow::resizeEvent(QResizeEvent*)
{
    /*Resize JobsView Header Width*/
    int at_header_def_width = eINDEX_10 * eINDEX_10;
    int at_diff_width = eINDEX_2;
    ui->jobsView->setColumnWidth(eINDEX_0, ui->jobsView->geometry().width() - eINDEX_2 * at_header_def_width - at_diff_width);
}

void MainWindow::dragEnterEvent(QDragEnterEvent* e)
{
    if(e->mimeData()->hasText())
    {
		switch (ui->tabWidget->currentIndex())
		{
		case eTAB_MAIN:/*Main*/
			break;
		default:
			break;
		}
        e->acceptProposedAction();
    }
}

void MainWindow::dropEvent(QDropEvent* e)
{
    const QMimeData* mime = e->mimeData();

    qDebug() << "Dropped Position:" << e->pos();
    if(mime->hasUrls())
    {
        foreach(QUrl url, e->mimeData()->urls())
        {
            QFileInfo file(url.toLocalFile());
            QString filename = QDir::toNativeSeparators(file.canonicalFilePath());
            QPoint pos;
            QRect ret;

            if(!QFileInfo(filename).isFile())
            {
                continue;
            }
            switch(ui->tabWidget->currentIndex())
            {
            case eTAB_MAIN:/*Main*/
                execJobCreator(JobCreator::eJOB_RELOAD_DROP, filename);
                break;
            case eTAB_AUDIO: /*Audio*/
                /* Audio Input */
                pos = QPoint(ui->widgetAudioEnc->ui->editAudioInput->pos()
                           + ui->widgetAudioEnc->ui->groupBoxAudio->pos()
                           + ui->tabWidget->pos()
                           + ui->centralWidget->pos()
                           + ui->widgetAudioEnc->pos()
                           + QPoint(ui->menubar->pos().x(), ui->menubar->height()));
                ret = QRect(pos, ui->widgetAudioEnc->ui->editAudioInput->size());
                qDebug() << "Audio Input:" << ret;
                if(ret.contains(e->pos()))
                {
                    ui->widgetAudioEnc->reload(filename);
                    break;
                }
                /* Audio Batch Input */
                pos = QPoint(ui->tabWidget->pos()
                           + ui->widgetAudioBatchEnc->ui->groupBoxAudioBatch->pos()
                           + ui->centralWidget->pos()
                           + ui->widgetAudioBatchEnc->ui->listViewAudioBatch->pos()
                           + QPoint(ui->menubar->pos().x(), ui->menubar->height()));
                ret = QRect(pos, ui->widgetAudioBatchEnc->ui->listViewAudioBatch->size());
                qDebug() << "Audio Batch Input:" << ret;
                if(ret.contains(e->pos()))
                {
                    QListWidgetItem *item = new QListWidgetItem(filename);
                    ui->widgetAudioBatchEnc->ui->listViewAudioBatch->addItem(item);
                    break;
                }
                break;
            case eTAB_MUXER: /*Muxer*/
                /* Muxer */
                /* Video Input */
                pos = QPoint(ui->widgetMuxer->ui->editMuxerVideoInput->pos()
                           + ui->widgetMuxer->ui->groupBoxMuxer->pos()
                           + ui->tabWidget->pos()
                           + ui->centralWidget->pos()
                           + ui->widgetMuxer->pos()
                           + QPoint(ui->menubar->pos().x(), ui->menubar->height()));
                ret = QRect(pos, ui->widgetMuxer->ui->editMuxerVideoInput->size());
                qDebug() << "Video Input:" << ret;
                if(ret.contains(e->pos()))
                {
                    ui->widgetMuxer->reload(Muxer::eRELOAD_TYPE_VIDEO, filename);
                    break;
                }

                /* Audio Input */
                pos = QPoint(ui->widgetMuxer->ui->editMuxerAudioInput->pos()
                           + ui->widgetMuxer->ui->groupBoxMuxer->pos()
                           + ui->tabWidget->pos()
                           + ui->centralWidget->pos()
                           + ui->widgetMuxer->pos()
                           + QPoint(ui->menubar->pos().x(), ui->menubar->height()));
                ret = QRect(pos, ui->widgetMuxer->ui->editMuxerAudioInput->size());
                qDebug() << "Audio Input:" << ret;
                if(ret.contains(e->pos()))
                {
                    ui->widgetMuxer->reload(Muxer::eRELOAD_TYPE_AUDIO, filename);
                    break;
                }
                /* Demuxer */
                pos = QPoint(ui->widgetDemuxer->ui->editDemuxerVideoInput->pos()
                           + ui->widgetDemuxer->ui->groupBoxDemuxer->pos()
                           + ui->tabWidget->pos()
                           + ui->centralWidget->pos()
                           + ui->widgetDemuxer->pos()
                           + QPoint(ui->menubar->pos().x(), ui->menubar->height()));
                ret = QRect(pos, ui->widgetDemuxer->ui->editDemuxerVideoInput->size());
                qDebug() << "Demuxer:" << ret;
                if(ret.contains(e->pos()))
                {
                    ui->widgetDemuxer->reload(static_cast<Demuxer::ERELOAD_TYPE>(ui->widgetDemuxer->ui->comboBoxDemuxerFormat->currentIndex()), filename);
                    break;
                }
                break;
            case eTAB_MEDIAINFO: /*MediaInfo*/
                ui->widgetMediaInfo->m_mediainfo_path = filename;
                ui->widgetMediaInfo->showMediaInfo(filename);
                break;
            case eTAB_EXTRA: /*Extra*/
                /*Extra*/
                /*Splitter*/
                pos = QPoint(ui->widgetSplitter->ui->editSplitMediaInput->pos()
                           + ui->widgetSplitter->ui->groupBoxSplitter->pos()
                           + ui->tabWidget->pos()
                           + ui->centralWidget->pos()
                           + ui->widgetSplitter->pos()
                           + QPoint(ui->menubar->pos().x(), ui->menubar->height()));
                ret = QRect(pos, ui->widgetSplitter->ui->editSplitMediaInput->size());
                qDebug() << "Splitter:" << ret;
                if(ret.contains(e->pos()))
                {
                    ui->widgetSplitter->reload(filename);
                    break;
                }
                /*Merge*/
                pos = QPoint(ui->widgetMerge->ui->listWidget->pos()
                           + ui->widgetMerge->ui->groupBoxMerge->pos()
                           + ui->tabWidget->pos()
                           + ui->centralWidget->pos()
                           + ui->widgetMerge->pos()
                           + QPoint(ui->menubar->pos().x(), ui->menubar->height()));
                ret = QRect(pos, ui->widgetMerge->ui->listWidget->size());
                qDebug() << "Merge:" << ret;
                if(ret.contains(e->pos()))
                {
                    ui->widgetMerge->reload(filename);
                    break;
                }
                break;
            default:
                break;
            }
        }
    }
    e->acceptProposedAction();
}

void MainWindow::dragMoveEvent(QDragMoveEvent *e)
{
    int menubar_height_diff = ui->menubar->height();
    QRect tabRectIndex0(QPoint(ui->tabWidget->tabBar()->tabRect(eINDEX_0).x(), ui->tabWidget->y() + ui->tabWidget->tabBar()->tabRect(eINDEX_0).y() + menubar_height_diff), ui->tabWidget->tabBar()->tabRect(eINDEX_0).size());
    QRect tabRectIndex1(QPoint(ui->tabWidget->tabBar()->tabRect(eINDEX_1).x(), ui->tabWidget->y() + ui->tabWidget->tabBar()->tabRect(eINDEX_1).y() + menubar_height_diff), ui->tabWidget->tabBar()->tabRect(eINDEX_1).size());
    QRect tabRectIndex2(QPoint(ui->tabWidget->tabBar()->tabRect(eINDEX_2).x(), ui->tabWidget->y() + ui->tabWidget->tabBar()->tabRect(eINDEX_2).y() + menubar_height_diff), ui->tabWidget->tabBar()->tabRect(eINDEX_2).size());
    QRect tabRectIndex3(QPoint(ui->tabWidget->tabBar()->tabRect(eINDEX_3).x(), ui->tabWidget->y() + ui->tabWidget->tabBar()->tabRect(eINDEX_3).y() + menubar_height_diff), ui->tabWidget->tabBar()->tabRect(eINDEX_3).size());
    QRect tabRectIndex4(QPoint(ui->tabWidget->tabBar()->tabRect(eINDEX_4).x(), ui->tabWidget->y() + ui->tabWidget->tabBar()->tabRect(eINDEX_4).y() + menubar_height_diff), ui->tabWidget->tabBar()->tabRect(eINDEX_4).size());
    QRect tabRectIndex5(QPoint(ui->tabWidget->tabBar()->tabRect(eINDEX_5).x(), ui->tabWidget->y() + ui->tabWidget->tabBar()->tabRect(eINDEX_5).y() + menubar_height_diff), ui->tabWidget->tabBar()->tabRect(eINDEX_5).size());
    if(tabRectIndex0.contains(e->pos()))
    {
        ui->tabWidget->setCurrentIndex(eINDEX_0);
    }
    else if(tabRectIndex1.contains(e->pos()))
    {
        ui->tabWidget->setCurrentIndex(eINDEX_1);
    }
    else if(tabRectIndex2.contains(e->pos()))
    {
        ui->tabWidget->setCurrentIndex(eINDEX_2);
    }
    else if(tabRectIndex3.contains(e->pos()))
    {
        ui->tabWidget->setCurrentIndex(eINDEX_3);
    }
    else if(tabRectIndex4.contains(e->pos()))
    {
        ui->tabWidget->setCurrentIndex(eINDEX_4);
    }
    else if(tabRectIndex5.contains(e->pos()))
    {
        ui->tabWidget->setCurrentIndex(eINDEX_5);
    }
}

void MainWindow::on_jobsView_itemDoubleClicked(QTableWidgetItem *)
{
    execJobCreator(JobCreator::eJOB_RELOAD_EDIT);
}

void MainWindow::execJobCreator(JobCreator::EJOB_RELOAD a_job_reload, QString a_filename)
{
    JobCreator job_creator;

    job_creator.mainUi = this;
    job_creator.reload(a_job_reload);

    switch(a_job_reload)
    {
    case JobCreator::eJOB_RELOAD_NEW:
    default:
        /*Add Job Item*/
        job_creator.reloadConfig(QMap<JobCreator::EJOB_CONFIG, QVariant>());
        break;
    case JobCreator::eJOB_RELOAD_DROP:
        /*Dropped and Add Job Item*/
        job_creator.reloadConfig(QMap<JobCreator::EJOB_CONFIG, QVariant>());
        job_creator.reloadSource(a_filename);
        break;
    case JobCreator::eJOB_RELOAD_EDIT:
        /*Edit Job Item*/
        job_creator.reloadConfig(m_jobs.at(ui->jobsView->currentRow()).job_config);
        break;
    }

    switch(job_creator.exec())
    {
    case QDialog::Accepted:
        acceptedJobCreator(a_job_reload);
        break;
    case QDialog::Rejected:
    default:
        break;
    }

    if(m_isStartJobImmediately)
    {
        reqJobStart();
    }
    setStartJobImmediately(false);
}

void MainWindow::acceptedJobCreator(JobCreator::EJOB_RELOAD a_job_reload)
{
    switch(a_job_reload)
    {
    case JobCreator::eJOB_RELOAD_NEW:
    case JobCreator::eJOB_RELOAD_DROP:
    default:
        appendItems(QStringList() << m_jobs.at(m_jobs.length() - eINDEX_1).job_name
                                  << getJobStatusText(JobChef::eJOB_STATUS_READY)
                                  << QString("0%"));
        break;
    case JobCreator::eJOB_RELOAD_EDIT:
        do {
            QTableWidgetItem *at_item;
            int row = ui->jobsView->currentRow();
            at_item = ui->jobsView->item(row, eINDEX_0);
            at_item->setText(m_jobs.at(m_jobs.length() - eINDEX_1).job_name);
        } while(false);
        break;
    }
}

bool MainWindow::eventFilter(QObject *o, QEvent *e)
{
    if(o == ui->jobsView)
    {
        if (e->type() == QEvent::FocusIn)
        {
            ui->jobsView->setStyleSheet(c_qss_table_widget_selection_bk_focus_in);
        }
        else if(e->type() == QEvent::FocusOut)
        {
            ui->jobsView->setStyleSheet(c_qss_table_widget_selection_bk_focus_out);
        }
    }
    return false;
}

void MainWindow::statusChanged(JobChef::EJOB_STATUS a_job_status)
{
    qDebug() << QString("JobStatus(%1/%2):").arg(m_jobs_index).arg(ui->jobsView->rowCount()) << getJobStatusText(m_job_status_prev) << "->" << getJobStatusText(a_job_status);

    if((m_jobs_index <= ui->jobsView->rowCount()) && (m_jobs_index >= eINDEX_1))
    {
        delete ui->jobsView->item(m_jobs_index - eINDEX_1, eINDEX_1);
        ui->jobsView->setItem(m_jobs_index - eINDEX_1, eINDEX_1, new QTableWidgetItem(getJobStatusText(a_job_status)));

        delete ui->jobsView->item(m_jobs_index - eINDEX_1, eINDEX_0);
        ui->jobsView->setItem(m_jobs_index - eINDEX_1, eINDEX_0, new QTableWidgetItem(getJobStatusIcon(a_job_status), m_jobs.at(m_jobs_index - eINDEX_1).job_name));
    }

    switch(a_job_status)
    {
    case JobChef::eJOB_STATUS_INITIAL:
    default:
        break;
    case JobChef::eJOB_STATUS_READY:
        m_pTaskbarButton->progress()->resume();
        break;
    case JobChef::eJOB_STATUS_WAITING:
        m_pTaskbarButton->progress()->resume();
        break;
    case JobChef::eJOB_STATUS_STARTING:
        m_pTaskbarButton->progress()->resume();
        break;
    case JobChef::eJOB_STATUS_RUNNING:
        m_pTaskbarButton->progress()->resume();
        break;
    case JobChef::eJOB_STATUS_PAUSING:
        m_pTaskbarButton->progress()->pause();
        break;
    case JobChef::eJOB_STATUS_PAUSED:
        ui->editDetails->setText(tr("Paused by user!"));
        m_pTaskbarButton->progress()->pause();
        break;
    case JobChef::eJOB_STATUS_ABORTING:
        m_pTaskbarButton->progress()->resume();
        m_isAborted = true;
        break;
    case JobChef::eJOB_STATUS_ABORTED:
        ui->editDetails->setText(tr("Aborted by user!"));
        m_pTaskbarButton->progress()->resume();
        m_isAborted = true;
        break;
    case JobChef::eJOB_STATUS_FAILED:
        ui->progressBar->setMaximum(eINDEX_100); /* Fixed progress bar failed on not processing encoder. */
        m_pTaskbarButton->progress()->stop();
        m_pTaskbarButton->progress()->setValue(static_cast<int>(eINDEX_0));
        viewLog(JobChef::eJOB_LOG_TYPE_DEBUG, tr("Process Failed!"));
        break;
    case JobChef::eJOB_STATUS_COMPLETED:
        viewLog(JobChef::eJOB_LOG_TYPE_JOB_STD_PROGRESS, QString::number(eINDEX_10 * eINDEX_10));
        ui->editDetails->setText(tr("Job Completed!"));
        m_pTaskbarButton->progress()->resume();
        m_pTaskbarButton->progress()->setValue(static_cast<int>(eINDEX_0));
        break;
    }
    m_job_status_prev = a_job_status;
}

QString MainWindow::getJobStatusText(JobChef::EJOB_STATUS a_job_status)
{
    static const QStringList s_job_status =
    {
        QObject::tr("Initial"),     /* eJOB_STATUS_INITIAL */
        QObject::tr("Ready"),       /* eJOB_STATUS_READY */
        QObject::tr("Starting"),    /* eJOB_STATUS_STARTING */
        QObject::tr("Running..."),  /* eJOB_STATUS_RUNNING */
        QObject::tr("Pausing"),     /* eJOB_STATUS_PAUSING */
        QObject::tr("Paused"),      /* eJOB_STATUS_PAUSED */
        QObject::tr("Resuming"),    /* eJOB_STATUS_RESUMING */
        QObject::tr("Aborting"),    /* eJOB_STATUS_ABORTING */
        QObject::tr("Aborted"),     /* eJOB_STATUS_ABORTED */
        QObject::tr("Failed"),      /* eJOB_STATUS_FAILED */
        QObject::tr("Waiting"),     /* eJOB_STATUS_WAITING */
        QObject::tr("Completed"),   /* eJOB_STATUS_COMPLETED */
    };

    return s_job_status[a_job_status];
}

QIcon MainWindow::getJobStatusIcon(JobChef::EJOB_STATUS a_job_status)
{
    QIcon icon;

    switch(a_job_status)
    {
    case JobChef::eJOB_STATUS_INITIAL:
    case JobChef::eJOB_STATUS_READY:
        icon = QIcon(":/buttons/hourglass.png");
        break;
    case JobChef::eJOB_STATUS_STARTING:
        icon = QIcon(":/buttons/lightning.png");
        break;
    case JobChef::eJOB_STATUS_RUNNING:
        icon = QIcon(":/buttons/play.png");
        break;
    case JobChef::eJOB_STATUS_PAUSING:
        icon = QIcon(":/buttons/clock_pause.png");
        break;
    case JobChef::eJOB_STATUS_PAUSED:
        icon = QIcon(":/buttons/pause_green.png");
        break;
    case JobChef::eJOB_STATUS_RESUMING:
        icon = QIcon(":/buttons/clock_play.png");
        break;
    case JobChef::eJOB_STATUS_ABORTING:
        icon = QIcon(":/buttons/clock_stop.png");
        break;
    case JobChef::eJOB_STATUS_ABORTED:
        icon = QIcon(":/buttons/error.png");
        break;
    case JobChef::eJOB_STATUS_FAILED:
        icon = QIcon(":/buttons/exclamation.png");
        break;
    case JobChef::eJOB_STATUS_WAITING:
        icon = QIcon(":/buttons/clock.png");
        break;
    case JobChef::eJOB_STATUS_COMPLETED:
        icon = QIcon(":/buttons/accept.png");
        break;
    }
    return icon;
}

void MainWindow::pauseJob(void)
{
    QList<qint64> processIds = m_job_chef->getAllProcessID();

    for(QList<qint64>::iterator i = processIds.begin(); i != processIds.end(); ++i)
    {
        BOOL result = DebugActiveProcess(static_cast<DWORD>(*i));

        if(result)
        {
            emit ntfStatusChanged(JobChef::eJOB_STATUS_PAUSING);
            viewLog(JobChef::eJOB_LOG_TYPE_JOB_STATUS, tr("Paused. PID %1.").arg(QString::number(static_cast<DWORD>(*i))));
        }
        else
        {
            viewLog(JobChef::eJOB_LOG_TYPE_ERROE, tr("Paused failed. PID %1. Error %2.").arg(QString::number(static_cast<DWORD>(*i))).arg(GetLastError()));
        }
    }

    if(m_job_status_prev != JobChef::eJOB_STATUS_FAILED)
    {
        emit ntfStatusChanged(JobChef::eJOB_STATUS_PAUSED);
    }
}

void MainWindow::resumeJob(void)
{
    QList<qint64> processIds = m_job_chef->getAllProcessID();

    for(QList<qint64>::iterator i = processIds.begin(); i != processIds.end(); ++i)
    {
        BOOL result = DebugActiveProcessStop(static_cast<DWORD>(*i));

        if(result)
        {
            emit ntfStatusChanged(JobChef::eJOB_STATUS_RESUMING);
            viewLog(JobChef::eJOB_LOG_TYPE_JOB_STATUS, tr("Resumed. PID %1.").arg(QString::number(static_cast<DWORD>(*i))));
        }
        else
        {
            emit ntfStatusChanged(JobChef::eJOB_STATUS_FAILED);
            viewLog(JobChef::eJOB_LOG_TYPE_JOB_STATUS, tr("Failed to resume. PID %1. Error %2.").arg(QString::number(static_cast<DWORD>(*i))).arg(GetLastError()));
        }
    }
    if(m_job_status_prev != JobChef::eJOB_STATUS_FAILED)
    {
        emit ntfStatusChanged(JobChef::eJOB_STATUS_RUNNING);
    }
}

void MainWindow::on_buttonPauseJob_clicked(bool a_checked)
{
    if(!isStarted())
    {
        ui->buttonPauseJob->setChecked(false);
        ui->actionJob_Pause->setChecked(false);
        return;
    }

    if(a_checked)
    {
        ui->buttonPauseJob->setChecked(true);
        ui->actionJob_Pause->setChecked(true);
        pauseJob();
    }
    else
    {
        ui->buttonPauseJob->setChecked(false);
        ui->actionJob_Pause->setChecked(false);
        resumeJob();
    }
}

void MainWindow::abortJob(void)
{
    if(isPaused())
    {
        ui->buttonPauseJob->setChecked(false);
        ui->actionJob_Pause->setChecked(false);
        resumeJob();
    }
    m_job_chef->abortJobs();
}

void MainWindow::failJob(void)
{
    /* Notified from job chef. */
    emit ntfStatusChanged(JobChef::eJOB_STATUS_FAILED);
}

void MainWindow::on_buttonAbortJob_clicked(void)
{
    if(!isStarted())
    {
        return;
    }

    int reply = QMessageBox::question(this, MESSAGE_QUESTION, tr("Do you really want to abort the job now?"), QMessageBox::Yes | QMessageBox::Cancel);

    if(reply == QMessageBox::Yes)
    {
        m_isAborted = true;
        abortJob();
    }
}

void MainWindow::on_jobsView_customContextMenuRequested(const QPoint &)
{
    m_pJobViewMenu->exec(QCursor::pos());
}

void MainWindow::on_logView_customContextMenuRequested(const QPoint &)
{
    m_pLogViewMenu->exec(QCursor::pos());
}

void MainWindow::openCommandLine(void)
{
    WinExec("cmd", SW_SHOW);
}

void MainWindow::openPython(void)
{
    WinExec("python", SW_SHOW);
}

void MainWindow::openPreviewDialog(void)
{
#if true
    PreviewDialog *at_pPreviewDialog = new PreviewDialog();
    at_pPreviewDialog->mainUi = this;
    at_pPreviewDialog->m_uid = QUuid::createUuid();
    at_pPreviewDialog->show();
    m_pPreviewDialogs.insert(at_pPreviewDialog->m_uid, at_pPreviewDialog);
#else
    FFPreviewDialog *at_pPreviewDialog = new FFPreviewDialog();
    at_pPreviewDialog->mainUi = this;
    at_pPreviewDialog->m_uid = QUuid::createUuid();
    at_pPreviewDialog->show();
    //m_pPreviewDialogs.insert(at_pPreviewDialog->m_uid, at_pPreviewDialog);
#endif
}

void MainWindow::openScriptCreator(void)
{
    ScriptCreator *at_pScriptCreator = new ScriptCreator();

    at_pScriptCreator->mainUi = this;
    at_pScriptCreator->m_uid_own = QUuid::createUuid();
    at_pScriptCreator->show();
    m_pScriptCreators.insert(at_pScriptCreator->m_uid_own, at_pScriptCreator);
}

void MainWindow::openScriptPlayer(void)
{
    ScriptPlayer *at_pScriptPlayer = new ScriptPlayer();

    at_pScriptPlayer->mainUi = this;
    at_pScriptPlayer->m_uid_own = QUuid::createUuid();
    at_pScriptPlayer->show();
    m_pScriptPlayers.insert(at_pScriptPlayer->m_uid_own, at_pScriptPlayer);
}

void MainWindow::openTools(void)
{
    const QMap<QObject *, QString> c_toolsCmdMap =
    {
        { ui->actionVSedit,   "vsedit" },
        { ui->actionD2VWitch, "d2vwitch" },
        { ui->actionWobbly,   "wobbly" },
        { ui->actionWibbly,   "wibbly" },
    };

    if(c_toolsCmdMap.contains(sender()))
    {
        QProcess::startDetached(c_toolsCmdMap[sender()]);
    }
}

void MainWindow::releaseChildWindowsAll(void)
{
    for(QMap<QUuid, ScriptPlayer *>::iterator i = m_pScriptPlayers.begin(); i != m_pScriptPlayers.end(); ++i)
    {
        if(m_pScriptPlayers[i.key()] != nullptr)
        {
            m_pScriptPlayers[i.key()]->close();
        }
    }
    m_pScriptPlayers.clear();

    for(QMap<QUuid, MediaInfoDialog *>::iterator i = m_pMediaInfoDialogs.begin(); i != m_pMediaInfoDialogs.end(); ++i)
    {
        if(m_pMediaInfoDialogs[i.key()] != nullptr)
        {
            m_pMediaInfoDialogs[i.key()]->close();
        }
    }
    m_pMediaInfoDialogs.clear();

    for(QMap<QUuid, PreviewDialog *>::iterator i = m_pPreviewDialogs.begin(); i != m_pPreviewDialogs.end(); ++i)
    {
        if(m_pPreviewDialogs[i.key()] != nullptr)
        {
            m_pPreviewDialogs[i.key()]->close();
        }
    }
    m_pPreviewDialogs.clear();

    for(QMap<QUuid, ScriptCreator *>::iterator i = m_pScriptCreators.begin(); i != m_pScriptCreators.end(); ++i)
    {
        if(m_pScriptCreators[i.key()] != nullptr)
        {
            m_pScriptCreators[i.key()]->close();
        }
    }
    m_pScriptCreators.clear();
}

void MainWindow::slotAudioBatchEncStarted(void)
{
    QList<StdWatcherCmd> cmds;
    QUuid uid = StdManager::createStdWatch();

    for(int i = eINDEX_0; i < ui->widgetAudioBatchEnc->ui->listViewAudioBatch->count(); i++)
    {
        QString input = ui->widgetAudioBatchEnc->ui->listViewAudioBatch->item(i)->text();
        QString output = ui->widgetAudioEnc->getAudioOutputPath(static_cast<AudioEnc::EENCODE_TYPE>(ui->widgetAudioEnc->ui->comboBoxAudioEncoder->currentIndex()), input);
        QString bitrate = ui->widgetAudioEnc->ui->comboBoxAudioBitrate->currentText();
        StdWatcherCmd cmd = ui->widgetAudioEnc->getEncodeCmd(input, output, bitrate);
        cmds << cmd;
    }
    g_pStdWatch[uid]->show();
    g_pStdWatch[uid]->initJob(uid);
    g_pStdWatch[uid]->startJob(cmds);
}

void MainWindow::allCompleted(void)
{
	Common::getInstance()->m_shutdown = Common::eSHUTDOWN_NOTHING;

    if(ui->actionPostOp_PowerDown->isChecked())
    {
		Common::getInstance()->m_shutdown = Common::eSHUTDOWN_POWER_OFF;
    }
    else if(ui->actionPostOp_Hibernate->isChecked())
    {
		Common::getInstance()->m_shutdown = Common::eSHUTDOWN_SLEEP;
    }
    else if(ui->actionPostOp_DoNothing->isChecked())
    {
		Common::getInstance()->m_shutdown = Common::eSHUTDOWN_NOTHING;
    }
    showShutdownMessage(Common::getInstance()->m_shutdown);
}

QString MainWindow::getShutdownTitle(Common::ESHUTDOWN a_shutdown)
{
    QString msg;

    switch(a_shutdown)
    {
    case Common::eSHUTDOWN_LOG_OUT:
        msg = tr("Log out");
        break;
    case Common::eSHUTDOWN_POWER_OFF:
    default:
        msg = tr("Shutdowm");
        break;
    case Common::eSHUTDOWN_REBOOT:
        msg = tr("Restart");
        break;
    case Common::eSHUTDOWN_SLEEP:
        msg = tr("Sleep");
        break;
    case Common::eSHUTDOWN_ABORT_POWER_OFF:
        msg = tr("Shutdown Aborted");
        break;
    case Common::eSHUTDOWN_FORCE_POWER_OFF:
        msg = tr("Shutdown Forced");
        break;
    }
    return msg;
}

void MainWindow::showShutdownMessage(Common::ESHUTDOWN a_shutdown)
{
    if(a_shutdown == Common::eSHUTDOWN_NOTHING)
    {
        return;
    }

    QString msg = getShutdownTitle(a_shutdown);

    m_count4shutdown = eINDEX_3 * eINDEX_10;
    m_pMsgBoxShutdown = new QMessageBox(QMessageBox::Information, msg, tr("%1 in %2s!").arg(msg).arg(m_count4shutdown), QMessageBox::Cancel);
	Timer::getInstance()->start(Timer::eTIMER_TYPE_CYCLIC, Timer::eTIMER_SLOT_SYSTEM_SHUTDOWN, static_cast<int>(eINDEX_10 * eINDEX_10 * eINDEX_10));

    if(m_pMsgBoxShutdown->exec() == QMessageBox::Cancel)
    {
		Timer::getInstance()->stop(Timer::eTIMER_TYPE_CYCLIC);
    }
    delete m_pMsgBoxShutdown;
    m_pMsgBoxShutdown = nullptr;
}

void MainWindow::setShutCountMessage(void)
{
    QString msg = getShutdownTitle(Common::getInstance()->m_shutdown);

    m_count4shutdown--;
    m_pMsgBoxShutdown->setText(tr("%1 in %2s!").arg(msg).arg(m_count4shutdown));

#ifdef QT_DEBUG
    qDebug() << QString("%1 in %2s!").arg(msg).arg(m_count4shutdown);
#endif

    if(m_count4shutdown <= eINDEX_0)
    {
		Timer::getInstance()->stop(Timer::eTIMER_TYPE_CYCLIC);
        m_pMsgBoxShutdown->close();
		Common::getInstance()->systemShutdown(Common::getInstance()->m_shutdown);

        delete m_pMsgBoxShutdown;
        m_pMsgBoxShutdown = nullptr;
    }
}

void MainWindow::slotAbout(void)
{
    QMessageBox::about(this, tr("About"), qvs::fromResource(":/strings/about").arg(QVS_VERSION));
}

void MainWindow::slotAboutQt(void)
{
    QMessageBox::aboutQt(this);
}

void MainWindow::showPreferences(void)
{
    Preferences at_pref;
    at_pref.mainUi = this;
    at_pref.exec();
}

void MainWindow::showInstaller(void)
{
    InstallerDialog at_installer_dialog;
    at_installer_dialog.mainUi = this;
    at_installer_dialog.exec();
}

void MainWindow::modeLaunch(void)
{
    switch(g_pConfig->getLaunchMode())
    {
    case Config::eLAUNCH_MODE_NORMAL:
        break;
    case Config::eLAUNCH_MODE_NORMAL_ADD_JOB:
        this->show();
        execJobCreator(JobCreator::eJOB_RELOAD_DROP, g_pConfig->getConfig(Config::eCONFIG_FIRST_CLI_FILENAME).toString());
        break;
    case Config::eLAUNCH_MODE_MEDIAINFO:
        this->show();
        ui->tabWidget->setCurrentIndex(eTAB_MEDIAINFO);
        ui->widgetMediaInfo->setPath(g_pConfig->getConfig(Config::eCONFIG_FIRST_CLI_FILENAME).toString());
        ui->widgetMediaInfo->reload();
        break;
    case Config::eLAUNCH_MODE_COPY_PATH_DOS:
    case Config::eLAUNCH_MODE_COPY_PATH_UNIX:
    case Config::eLAUNCH_MODE_COPY_PATH_PYTHON:
		Common::getInstance()->copyPath();
        break;
    case Config::eLAUNCH_MODE_SHOW_HELP:
        QMessageBox::about(this, tr("Qvs Help Dialog"), qvs::fromResource(":/strings/cli-usage"));
		Timer::getInstance()->start(Timer::eTIMER_TYPE_ONE_SHOT, Timer::eTIMER_SLOT_PROGURM_QUIT, eINDEX_10);
        break;
    case Config::eLAUNCH_MODE_EXIT:
		Timer::getInstance()->start(Timer::eTIMER_TYPE_ONE_SHOT, Timer::eTIMER_SLOT_PROGURM_QUIT, eINDEX_10);
        break;
    default:
        break;
    }
}

void MainWindow::setLanguage(Config::ELANGUAGE a_language)
{
    if((a_language >= Config::eLANGUAGE_MAX) || (a_language <= static_cast<Config::ELANGUAGE>(eINDEX_NONE)))
    {
        a_language = Config::eLANGUAGE_EN;
    }
    if(a_language >= m_pActionGruopLanguage->actions().length())
    {
        return;
    }
    m_pActionGruopLanguage->actions().at(a_language)->setChecked(true);
}

Config::ELANGUAGE MainWindow::language(void)
{
    Config::ELANGUAGE language = static_cast<Config::ELANGUAGE>(eINDEX_0);

    for(int i = eINDEX_0; i < m_pActionGruopLanguage->actions().length(); i++)
    {
        if(m_pActionGruopLanguage->actions().at(i)->isChecked())
        {
            language = static_cast<Config::ELANGUAGE>(i);
            break;
        }
    }
    return language;
}

void MainWindow::languageChanged(void)
{
    g_pConfig->setConfig(Config::eCONFIG_FIRST_LANGUAGE, language());
}

void MainWindow::slotMinimize(void)
{
    m_pMinimizeWidgets.clear();

    for(QMap<QUuid, ScriptPlayer *>::iterator i = m_pScriptPlayers.begin(); i != m_pScriptPlayers.end(); ++i)
    {
        if(m_pScriptPlayers[i.key()] != nullptr && m_pScriptPlayers[i.key()]->isVisible())
        {
            m_pMinimizeWidgets.insert(i.key(), m_pScriptPlayers[i.key()]);
        }
    }

    for(QMap<QUuid, MediaInfoDialog *>::iterator i = m_pMediaInfoDialogs.begin(); i != m_pMediaInfoDialogs.end(); ++i)
    {
        if(m_pMediaInfoDialogs[i.key()] != nullptr && m_pMediaInfoDialogs[i.key()]->isVisible())
        {
            m_pMinimizeWidgets.insert(i.key(), m_pMediaInfoDialogs[i.key()]);
        }
    }

    for(QMap<QUuid, PreviewDialog *>::iterator i = m_pPreviewDialogs.begin(); i != m_pPreviewDialogs.end(); ++i)
    {
        if(m_pPreviewDialogs[i.key()] != nullptr && m_pPreviewDialogs[i.key()]->isVisible())
        {
            m_pMinimizeWidgets.insert(i.key(), m_pPreviewDialogs[i.key()]);
        }
    }

    for(QMap<QUuid, ScriptCreator *>::iterator i = m_pScriptCreators.begin(); i != m_pScriptCreators.end(); ++i)
    {
        if(m_pScriptCreators[i.key()] != nullptr && m_pScriptCreators[i.key()]->isVisible())
        {
            m_pMinimizeWidgets.insert(i.key(), m_pScriptCreators[i.key()]);
        }
    }

    for(QMap<QUuid, StdWatcher*>::iterator i = g_pStdWatch.begin(); i != g_pStdWatch.end(); i++)
    {
        if(g_pStdWatch[i.key()] != nullptr && g_pStdWatch[i.key()]->isVisible())
        {
            m_pMinimizeWidgets.insert(i.key(), g_pStdWatch[i.key()]);
        }
    }

    if(this->isVisible())
    {
        m_pMinimizeWidgets.insert(QUuid::createUuid(), this);
    }

    for(QMap<QUuid, QWidget *>::iterator i = m_pMinimizeWidgets.begin(); i != m_pMinimizeWidgets.end(); i++)
    {
        m_pMinimizeWidgets[i.key()]->hide();
    }
    m_pSystemTray->show();
    QApplication::setQuitOnLastWindowClosed(false);
}

void MainWindow::slotTrayActivated(QSystemTrayIcon::ActivationReason a_reason)
{
    Q_UNUSED(a_reason)

    if(m_pSystemTray->isVisible())
    {
        for(QMap<QUuid, QWidget *>::iterator i = m_pMinimizeWidgets.begin(); i != m_pMinimizeWidgets.end(); i++)
        {
            m_pMinimizeWidgets[i.key()]->show();
        }
    }
    m_pSystemTray->hide();
    m_pMinimizeWidgets.clear();
    QApplication::setQuitOnLastWindowClosed(true);
}

void MainWindow::slotTimeout(int a_timerType, int a_timerSlot)
{
	Timer::ETIMER_TYPE timerType = static_cast<Timer::ETIMER_TYPE>(a_timerType);
	Timer::ETIMER_SLOT timerSlot = static_cast<Timer::ETIMER_SLOT>(a_timerSlot);

	if (timerType == Timer::eTIMER_TYPE_ONE_SHOT)
	{
		switch (timerSlot)
		{
        case Timer::eTIMER_SLOT_CALC_MD5:
            ui->widgetMediaInfo->clear();
            ui->widgetMediaInfo->append(tr("Filename: ") + QFileInfo(ui->widgetMediaInfo->getPath()).fileName());
            ui->widgetMediaInfo->append(tr("MD5: ") + Common::getInstance()->getHashMd5(ui->widgetMediaInfo->getPath()));
			break;
		case Timer::eTIMER_SLOT_PROGURM_QUIT:
			this->close();
			break;
		default:
			break;
		}
	}
	else if (timerType == Timer::eTIMER_TYPE_CYCLIC)
	{
		switch (timerSlot)
		{
		case Timer::eTIMER_SLOT_SYSTEM_SHUTDOWN:
			setShutCountMessage();
			break;
		default:
			break;
		}
	}
}

bool MainWindow::slotMail(EMODULE a_module, STMAILBOX* a_mail_box)
{
	bool ret = false;

	switch (a_module)
	{
	case MODULE_MAINWINDOW:
		switch (a_mail_box->type)
		{
		case eINDEX_0: // Tpye 0: Called and to remove Widgets after closed.
			ret = slotChildWindowClosedRemove(a_mail_box->uid);
			break;
		default:
			break;
		};
		break;
	case MODULE_SCRIPT_PLAYER:
		ret = m_pScriptPlayers[a_mail_box->uid]->slotMail(a_mail_box);
		break;
	case MODULE_JOB_CHEF:
		ret = m_job_chef->updatePriorty();
		break;
	default:
		break;
	}
    return ret;
}

void MainWindow::slotChildWindowClosed(QUuid a_uid)
{
    STMAILBOX *mail_box = new STMAILBOX();

    mail_box->type = eINDEX_0;
    mail_box->uid = a_uid;
    g_pMailBox.insert(MODULE_MAINWINDOW, mail_box);
}

bool MainWindow::slotChildWindowClosedRemove(QUuid a_uid)
{
    bool ret = false;

    if(m_pMinimizeWidgets.contains(a_uid))
    {
        m_pMinimizeWidgets.remove(a_uid);
        ret = true;
    }
    if(g_pStdWatch.contains(a_uid))
    {
        g_pStdWatch.remove(a_uid);
        ret = true;
    }
    if(m_pScriptPlayers.contains(a_uid))
    {
        m_pScriptPlayers.remove(a_uid);
        ret = true;
    }
    if(m_pMediaInfoDialogs.contains(a_uid))
    {
        m_pMediaInfoDialogs.remove(a_uid);
        ret = true;
    }
    if(m_pPreviewDialogs.contains(a_uid))
    {
        m_pPreviewDialogs.remove(a_uid);
        ret = true;
    }
    if(m_pScriptCreators.contains(a_uid))
    {
        m_pScriptCreators.remove(a_uid);
        ret = true;
    }
    return ret;
}

void MainWindow::logging(const QString &a_log)
{
    m_logging->log().info(a_log);
}

void MainWindow::slotViewJobsLog(void)
{
    JobViewCmd job_view_cmd;

    job_view_cmd.mainUi = this;

    if(QFile(m_logging->loggingPath()).size() > 10 * MB)
    {
        if(QMessageBox::question(this, MESSAGE_QUESTION, tr("Log file size larger than 10MB.\nReading will take some time.\nContinue?"), QMessageBox::Ok|QMessageBox::No) == QMessageBox::No)
        {
            return;
        }
    }
    job_view_cmd.reload(m_logging->history());
    job_view_cmd.exec();
}
