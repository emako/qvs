/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionExit;
    QAction *actionAbout;
    QAction *actionWebMulder;
    QAction *actionWebX264;
    QAction *actionWebX264Komisar;
    QAction *actionWebX264VideoLAN;
    QAction *actionOnlineDocX264;
    QAction *actionWebBluRay;
    QAction *actionCreateJob;
    QAction *actionJob_Start;
    QAction *actionJob_Abort;
    QAction *actionJob_Pause;
    QAction *actionPreferences;
    QAction *actionJob_Delete;
    QAction *actionJob_Explore;
    QAction *actionWebAvisynth32;
    QAction *actionWebAvisynth64;
    QAction *actionWebSecret;
    QAction *actionWebAvsWiki;
    QAction *actionJob_Reset;
    QAction *actionWebSupport;
    QAction *actionOpen;
    QAction *actionDownload_Avisynth;
    QAction *actionUtz;
    QAction *actionWebVapourSynth;
    QAction *actionWebVapourSynthDocs;
    QAction *actionCheckForUpdates;
    QAction *actionWebAvisynthPlus;
    QAction *actionWebX265;
    QAction *actionDownload_x265_Binaries;
    QAction *actionWebX265Fllear;
    QAction *actionWebX265FreeCodecs;
    QAction *actionWebX265Snowfag;
    QAction *actionWebX265LigH;
    QAction *actionWebX264FreeCodecs;
    QAction *actionJob_MoveUp;
    QAction *actionJob_MoveDown;
    QAction *actionOnlineDocX265;
    QAction *actionRemove_Jobs;
    QAction *actionCleanupFinished;
    QAction *actionCleanupAll;
    QAction *actionDo_Nothing;
    QAction *actionPostOp_PowerDown;
    QAction *actionPostOp_Hibernate;
    QAction *actionPostOp_DoNothing;
    QAction *actionJob_Edit;
    QAction *actionJob_View;
    QAction *actionCommand_Line;
    QAction *actionPython;
    QAction *actionScriptPlayer;
    QAction *actionVSedit;
    QAction *actionInstaller;
    QAction *actionPreviewDialog;
    QAction *actionScriptCreator;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_3;
    QTabWidget *tabWidget;
    QWidget *tab_main;
    QVBoxLayout *verticalLayout;
    QSplitter *splitter;
    QTableWidget *jobsView;
    QGroupBox *groupBoxJobDetails;
    QVBoxLayout *verticalLayout_2;
    QProgressBar *progressBar;
    QSpacerItem *verticalSpacer;
    QTextEdit *logView;
    QLineEdit *editDetails;
    QFrame *frame;
    QHBoxLayout *horizontalLayout;
    QPushButton *buttonAddJob;
    QSpacerItem *horizontalSpacer;
    QPushButton *buttonStartJob;
    QPushButton *buttonPauseJob;
    QPushButton *buttonAbortJob;
    QWidget *tab_audio;
    QVBoxLayout *verticalLayout_7;
    QStackedWidget *stackedWidgetAudioEnc;
    QWidget *page_AudioEnc;
    QGroupBox *groupBoxAudioBatch;
    QHBoxLayout *horizontalLayout_3;
    QHBoxLayout *horizontalLayout_2;
    QListWidget *listViewAudioBatch;
    QVBoxLayout *verticalLayout_6;
    QPushButton *buttonAudioBatchAdd;
    QPushButton *buttonAudioBatchDelete;
    QPushButton *buttonAudioBatchClear;
    QSpacerItem *verticalSpacer_3;
    QPushButton *buttonAudioBatchStart;
    QWidget *tab_muxer;
    QVBoxLayout *verticalLayout_10;
    QStackedWidget *stackedWidgetMuxer;
    QWidget *page_Muxer;
    QStackedWidget *stackedWidgetDemuxer;
    QWidget *page_Demuxer;
    QWidget *tab_mediainfo;
    QVBoxLayout *verticalLayout_4;
    QStackedWidget *stackedWidgetMediaInfo;
    QWidget *page_MediaInfo;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuRemove_Jobs;
    QMenu *menuRemove_PostOperation;
    QMenu *menuHelp;
    QMenu *menuDownloadX264;
    QMenu *menuDownloadAvisynth;
    QMenu *menuDownloadX265;
    QMenu *menuJob;
    QMenu *menuTools;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(720, 640);
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/buttons/door_in.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionExit->setIcon(icon);
        actionAbout = new QAction(MainWindow);
        actionAbout->setObjectName(QStringLiteral("actionAbout"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/buttons/information.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionAbout->setIcon(icon1);
        actionWebMulder = new QAction(MainWindow);
        actionWebMulder->setObjectName(QStringLiteral("actionWebMulder"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/buttons/world_link.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionWebMulder->setIcon(icon2);
        actionWebX264 = new QAction(MainWindow);
        actionWebX264->setObjectName(QStringLiteral("actionWebX264"));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/buttons/x264.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionWebX264->setIcon(icon3);
        actionWebX264Komisar = new QAction(MainWindow);
        actionWebX264Komisar->setObjectName(QStringLiteral("actionWebX264Komisar"));
        actionWebX264Komisar->setIcon(icon2);
        actionWebX264VideoLAN = new QAction(MainWindow);
        actionWebX264VideoLAN->setObjectName(QStringLiteral("actionWebX264VideoLAN"));
        actionWebX264VideoLAN->setIcon(icon2);
        actionOnlineDocX264 = new QAction(MainWindow);
        actionOnlineDocX264->setObjectName(QStringLiteral("actionOnlineDocX264"));
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/buttons/book_open.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionOnlineDocX264->setIcon(icon4);
        actionWebBluRay = new QAction(MainWindow);
        actionWebBluRay->setObjectName(QStringLiteral("actionWebBluRay"));
        actionWebBluRay->setIcon(icon4);
        actionCreateJob = new QAction(MainWindow);
        actionCreateJob->setObjectName(QStringLiteral("actionCreateJob"));
        QIcon icon5;
        icon5.addFile(QStringLiteral(":/buttons/add.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionCreateJob->setIcon(icon5);
        actionJob_Start = new QAction(MainWindow);
        actionJob_Start->setObjectName(QStringLiteral("actionJob_Start"));
        actionJob_Start->setEnabled(true);
        QIcon icon6;
        icon6.addFile(QStringLiteral(":/buttons/play.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionJob_Start->setIcon(icon6);
        actionJob_Abort = new QAction(MainWindow);
        actionJob_Abort->setObjectName(QStringLiteral("actionJob_Abort"));
        actionJob_Abort->setEnabled(true);
        QIcon icon7;
        icon7.addFile(QStringLiteral(":/buttons/cross.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionJob_Abort->setIcon(icon7);
        actionJob_Pause = new QAction(MainWindow);
        actionJob_Pause->setObjectName(QStringLiteral("actionJob_Pause"));
        actionJob_Pause->setCheckable(true);
        actionJob_Pause->setEnabled(true);
        QIcon icon8;
        icon8.addFile(QStringLiteral(":/buttons/pause_green.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionJob_Pause->setIcon(icon8);
        actionPreferences = new QAction(MainWindow);
        actionPreferences->setObjectName(QStringLiteral("actionPreferences"));
        QIcon icon9;
        icon9.addFile(QStringLiteral(":/buttons/wrench.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionPreferences->setIcon(icon9);
        actionJob_Delete = new QAction(MainWindow);
        actionJob_Delete->setObjectName(QStringLiteral("actionJob_Delete"));
        actionJob_Delete->setEnabled(true);
        QIcon icon10;
        icon10.addFile(QStringLiteral(":/buttons/trash.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionJob_Delete->setIcon(icon10);
        actionJob_Explore = new QAction(MainWindow);
        actionJob_Explore->setObjectName(QStringLiteral("actionJob_Explore"));
        actionJob_Explore->setEnabled(true);
        QIcon icon11;
        icon11.addFile(QStringLiteral(":/buttons/folder_magnify.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionJob_Explore->setIcon(icon11);
        actionWebAvisynth32 = new QAction(MainWindow);
        actionWebAvisynth32->setObjectName(QStringLiteral("actionWebAvisynth32"));
        actionWebAvisynth32->setIcon(icon2);
        actionWebAvisynth64 = new QAction(MainWindow);
        actionWebAvisynth64->setObjectName(QStringLiteral("actionWebAvisynth64"));
        actionWebAvisynth64->setIcon(icon2);
        actionWebSecret = new QAction(MainWindow);
        actionWebSecret->setObjectName(QStringLiteral("actionWebSecret"));
        actionWebSecret->setIcon(icon4);
        actionWebAvsWiki = new QAction(MainWindow);
        actionWebAvsWiki->setObjectName(QStringLiteral("actionWebAvsWiki"));
        actionWebAvsWiki->setIcon(icon4);
        actionJob_Reset = new QAction(MainWindow);
        actionJob_Reset->setObjectName(QStringLiteral("actionJob_Reset"));
        actionJob_Reset->setEnabled(true);
        QIcon icon12;
        icon12.addFile(QStringLiteral(":/buttons/restart.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionJob_Reset->setIcon(icon12);
        actionWebSupport = new QAction(MainWindow);
        actionWebSupport->setObjectName(QStringLiteral("actionWebSupport"));
        QIcon icon13;
        icon13.addFile(QStringLiteral(":/buttons/group.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionWebSupport->setIcon(icon13);
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName(QStringLiteral("actionOpen"));
        QIcon icon14;
        icon14.addFile(QStringLiteral(":/buttons/folder_add.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionOpen->setIcon(icon14);
        actionDownload_Avisynth = new QAction(MainWindow);
        actionDownload_Avisynth->setObjectName(QStringLiteral("actionDownload_Avisynth"));
        actionUtz = new QAction(MainWindow);
        actionUtz->setObjectName(QStringLiteral("actionUtz"));
        actionWebVapourSynth = new QAction(MainWindow);
        actionWebVapourSynth->setObjectName(QStringLiteral("actionWebVapourSynth"));
        QIcon icon15;
        icon15.addFile(QStringLiteral(":/buttons/drive_web.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionWebVapourSynth->setIcon(icon15);
        actionWebVapourSynthDocs = new QAction(MainWindow);
        actionWebVapourSynthDocs->setObjectName(QStringLiteral("actionWebVapourSynthDocs"));
        actionWebVapourSynthDocs->setIcon(icon4);
        actionCheckForUpdates = new QAction(MainWindow);
        actionCheckForUpdates->setObjectName(QStringLiteral("actionCheckForUpdates"));
        QIcon icon16;
        icon16.addFile(QStringLiteral(":/buttons/github.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionCheckForUpdates->setIcon(icon16);
        actionWebAvisynthPlus = new QAction(MainWindow);
        actionWebAvisynthPlus->setObjectName(QStringLiteral("actionWebAvisynthPlus"));
        actionWebAvisynthPlus->setIcon(icon2);
        actionWebX265 = new QAction(MainWindow);
        actionWebX265->setObjectName(QStringLiteral("actionWebX265"));
        QIcon icon17;
        icon17.addFile(QStringLiteral(":/buttons/x265.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionWebX265->setIcon(icon17);
        actionDownload_x265_Binaries = new QAction(MainWindow);
        actionDownload_x265_Binaries->setObjectName(QStringLiteral("actionDownload_x265_Binaries"));
        actionWebX265Fllear = new QAction(MainWindow);
        actionWebX265Fllear->setObjectName(QStringLiteral("actionWebX265Fllear"));
        actionWebX265Fllear->setIcon(icon2);
        actionWebX265FreeCodecs = new QAction(MainWindow);
        actionWebX265FreeCodecs->setObjectName(QStringLiteral("actionWebX265FreeCodecs"));
        actionWebX265FreeCodecs->setIcon(icon2);
        actionWebX265Snowfag = new QAction(MainWindow);
        actionWebX265Snowfag->setObjectName(QStringLiteral("actionWebX265Snowfag"));
        actionWebX265Snowfag->setIcon(icon2);
        actionWebX265LigH = new QAction(MainWindow);
        actionWebX265LigH->setObjectName(QStringLiteral("actionWebX265LigH"));
        actionWebX265LigH->setIcon(icon2);
        actionWebX264FreeCodecs = new QAction(MainWindow);
        actionWebX264FreeCodecs->setObjectName(QStringLiteral("actionWebX264FreeCodecs"));
        actionWebX264FreeCodecs->setIcon(icon2);
        actionJob_MoveUp = new QAction(MainWindow);
        actionJob_MoveUp->setObjectName(QStringLiteral("actionJob_MoveUp"));
        actionJob_MoveUp->setEnabled(true);
        QIcon icon18;
        icon18.addFile(QStringLiteral(":/buttons/arrow_up.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionJob_MoveUp->setIcon(icon18);
        actionJob_MoveDown = new QAction(MainWindow);
        actionJob_MoveDown->setObjectName(QStringLiteral("actionJob_MoveDown"));
        actionJob_MoveDown->setEnabled(true);
        QIcon icon19;
        icon19.addFile(QStringLiteral(":/buttons/arrow_down.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionJob_MoveDown->setIcon(icon19);
        actionOnlineDocX265 = new QAction(MainWindow);
        actionOnlineDocX265->setObjectName(QStringLiteral("actionOnlineDocX265"));
        actionOnlineDocX265->setIcon(icon4);
        actionRemove_Jobs = new QAction(MainWindow);
        actionRemove_Jobs->setObjectName(QStringLiteral("actionRemove_Jobs"));
        actionCleanupFinished = new QAction(MainWindow);
        actionCleanupFinished->setObjectName(QStringLiteral("actionCleanupFinished"));
        actionCleanupFinished->setIcon(icon10);
        actionCleanupAll = new QAction(MainWindow);
        actionCleanupAll->setObjectName(QStringLiteral("actionCleanupAll"));
        actionCleanupAll->setIcon(icon10);
        actionDo_Nothing = new QAction(MainWindow);
        actionDo_Nothing->setObjectName(QStringLiteral("actionDo_Nothing"));
        QIcon icon20;
        icon20.addFile(QStringLiteral(":/buttons/cup.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionDo_Nothing->setIcon(icon20);
        actionPostOp_PowerDown = new QAction(MainWindow);
        actionPostOp_PowerDown->setObjectName(QStringLiteral("actionPostOp_PowerDown"));
        actionPostOp_PowerDown->setCheckable(true);
        QIcon icon21;
        icon21.addFile(QStringLiteral(":/buttons/power_off.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionPostOp_PowerDown->setIcon(icon21);
        actionPostOp_Hibernate = new QAction(MainWindow);
        actionPostOp_Hibernate->setObjectName(QStringLiteral("actionPostOp_Hibernate"));
        actionPostOp_Hibernate->setCheckable(true);
        QIcon icon22;
        icon22.addFile(QStringLiteral(":/buttons/snow_flake.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionPostOp_Hibernate->setIcon(icon22);
        actionPostOp_DoNothing = new QAction(MainWindow);
        actionPostOp_DoNothing->setObjectName(QStringLiteral("actionPostOp_DoNothing"));
        actionPostOp_DoNothing->setCheckable(true);
        actionPostOp_DoNothing->setChecked(true);
        QIcon icon23;
        icon23.addFile(QStringLiteral(":/buttons/cross_grey.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionPostOp_DoNothing->setIcon(icon23);
        actionJob_Edit = new QAction(MainWindow);
        actionJob_Edit->setObjectName(QStringLiteral("actionJob_Edit"));
        QIcon icon24;
        icon24.addFile(QStringLiteral(":/buttons/sheduled_task.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionJob_Edit->setIcon(icon24);
        actionJob_View = new QAction(MainWindow);
        actionJob_View->setObjectName(QStringLiteral("actionJob_View"));
        QIcon icon25;
        icon25.addFile(QStringLiteral(":/buttons/date_task.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionJob_View->setIcon(icon25);
        actionCommand_Line = new QAction(MainWindow);
        actionCommand_Line->setObjectName(QStringLiteral("actionCommand_Line"));
        QIcon icon26;
        icon26.addFile(QStringLiteral(":/buttons/application_xp_terminal.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionCommand_Line->setIcon(icon26);
        actionPython = new QAction(MainWindow);
        actionPython->setObjectName(QStringLiteral("actionPython"));
        QIcon icon27;
        icon27.addFile(QStringLiteral(":/buttons/python.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionPython->setIcon(icon27);
        actionScriptPlayer = new QAction(MainWindow);
        actionScriptPlayer->setObjectName(QStringLiteral("actionScriptPlayer"));
        QIcon icon28;
        icon28.addFile(QStringLiteral(":/buttons/slideshow_next.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionScriptPlayer->setIcon(icon28);
        actionVSedit = new QAction(MainWindow);
        actionVSedit->setObjectName(QStringLiteral("actionVSedit"));
        QIcon icon29;
        icon29.addFile(QStringLiteral(":/buttons/vsedit.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionVSedit->setIcon(icon29);
        actionInstaller = new QAction(MainWindow);
        actionInstaller->setObjectName(QStringLiteral("actionInstaller"));
        QIcon icon30;
        icon30.addFile(QStringLiteral(":/buttons/package.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionInstaller->setIcon(icon30);
        actionPreviewDialog = new QAction(MainWindow);
        actionPreviewDialog->setObjectName(QStringLiteral("actionPreviewDialog"));
        QIcon icon31;
        icon31.addFile(QStringLiteral(":/buttons/film.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionPreviewDialog->setIcon(icon31);
        actionScriptCreator = new QAction(MainWindow);
        actionScriptCreator->setObjectName(QStringLiteral("actionScriptCreator"));
        QIcon icon32;
        icon32.addFile(QStringLiteral(":/buttons/document_editing.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionScriptCreator->setIcon(icon32);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout_3 = new QVBoxLayout(centralWidget);
        verticalLayout_3->setSpacing(0);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tab_main = new QWidget();
        tab_main->setObjectName(QStringLiteral("tab_main"));
        verticalLayout = new QVBoxLayout(tab_main);
        verticalLayout->setSpacing(2);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(2, 2, 2, 2);
        splitter = new QSplitter(tab_main);
        splitter->setObjectName(QStringLiteral("splitter"));
        splitter->setOrientation(Qt::Vertical);
        splitter->setOpaqueResize(false);
        splitter->setHandleWidth(8);
        splitter->setChildrenCollapsible(false);
        jobsView = new QTableWidget(splitter);
        jobsView->setObjectName(QStringLiteral("jobsView"));
        jobsView->setFocusPolicy(Qt::StrongFocus);
        jobsView->setContextMenuPolicy(Qt::ActionsContextMenu);
        jobsView->setAlternatingRowColors(false);
        jobsView->setSelectionMode(QAbstractItemView::SingleSelection);
        jobsView->setSelectionBehavior(QAbstractItemView::SelectRows);
        jobsView->setWordWrap(false);
        jobsView->setCornerButtonEnabled(false);
        splitter->addWidget(jobsView);
        jobsView->horizontalHeader()->setVisible(false);
        jobsView->horizontalHeader()->setHighlightSections(false);
        jobsView->verticalHeader()->setVisible(false);
        groupBoxJobDetails = new QGroupBox(splitter);
        groupBoxJobDetails->setObjectName(QStringLiteral("groupBoxJobDetails"));
        verticalLayout_2 = new QVBoxLayout(groupBoxJobDetails);
        verticalLayout_2->setSpacing(2);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        progressBar = new QProgressBar(groupBoxJobDetails);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        QFont font;
        font.setFamily(QStringLiteral("Consolas"));
        progressBar->setFont(font);
        progressBar->setMouseTracking(false);
        progressBar->setFocusPolicy(Qt::StrongFocus);
        progressBar->setStyleSheet(QLatin1String("QProgressBar {\n"
"	border: 1px solid grey;\n"
"	border-radius: 0px;\n"
"	background-color: #FFFFFF;\n"
"}\n"
"QProgressBar::chunk {\n"
"	background-color: #FDCFE6;\n"
"	width: 20px;\n"
"}"));
        progressBar->setValue(0);
        progressBar->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(progressBar);

        verticalSpacer = new QSpacerItem(20, 3, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_2->addItem(verticalSpacer);

        logView = new QTextEdit(groupBoxJobDetails);
        logView->setObjectName(QStringLiteral("logView"));
        logView->setFont(font);
        logView->setContextMenuPolicy(Qt::ActionsContextMenu);
        logView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        logView->setReadOnly(true);

        verticalLayout_2->addWidget(logView);

        editDetails = new QLineEdit(groupBoxJobDetails);
        editDetails->setObjectName(QStringLiteral("editDetails"));
        QFont font1;
        font1.setFamily(QStringLiteral("Consolas"));
        font1.setBold(false);
        font1.setWeight(50);
        editDetails->setFont(font1);
        editDetails->setReadOnly(true);

        verticalLayout_2->addWidget(editDetails);

        splitter->addWidget(groupBoxJobDetails);

        verticalLayout->addWidget(splitter);

        frame = new QFrame(tab_main);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setFrameShape(QFrame::HLine);
        frame->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(frame);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        buttonAddJob = new QPushButton(tab_main);
        buttonAddJob->setObjectName(QStringLiteral("buttonAddJob"));
        buttonAddJob->setMinimumSize(QSize(128, 0));
        buttonAddJob->setIcon(icon5);

        horizontalLayout->addWidget(buttonAddJob);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        buttonStartJob = new QPushButton(tab_main);
        buttonStartJob->setObjectName(QStringLiteral("buttonStartJob"));
        buttonStartJob->setEnabled(true);
        buttonStartJob->setMinimumSize(QSize(104, 0));
        buttonStartJob->setIcon(icon6);

        horizontalLayout->addWidget(buttonStartJob);

        buttonPauseJob = new QPushButton(tab_main);
        buttonPauseJob->setObjectName(QStringLiteral("buttonPauseJob"));
        buttonPauseJob->setEnabled(true);
        buttonPauseJob->setMinimumSize(QSize(104, 0));
        buttonPauseJob->setIcon(icon8);
        buttonPauseJob->setCheckable(true);

        horizontalLayout->addWidget(buttonPauseJob);

        buttonAbortJob = new QPushButton(tab_main);
        buttonAbortJob->setObjectName(QStringLiteral("buttonAbortJob"));
        buttonAbortJob->setEnabled(true);
        buttonAbortJob->setMinimumSize(QSize(104, 0));
        buttonAbortJob->setIcon(icon7);

        horizontalLayout->addWidget(buttonAbortJob);


        verticalLayout->addLayout(horizontalLayout);

        tabWidget->addTab(tab_main, QString());
        tab_audio = new QWidget();
        tab_audio->setObjectName(QStringLiteral("tab_audio"));
        verticalLayout_7 = new QVBoxLayout(tab_audio);
        verticalLayout_7->setObjectName(QStringLiteral("verticalLayout_7"));
        verticalLayout_7->setContentsMargins(2, 2, 2, 2);
        stackedWidgetAudioEnc = new QStackedWidget(tab_audio);
        stackedWidgetAudioEnc->setObjectName(QStringLiteral("stackedWidgetAudioEnc"));
        page_AudioEnc = new QWidget();
        page_AudioEnc->setObjectName(QStringLiteral("page_AudioEnc"));
        stackedWidgetAudioEnc->addWidget(page_AudioEnc);

        verticalLayout_7->addWidget(stackedWidgetAudioEnc);

        groupBoxAudioBatch = new QGroupBox(tab_audio);
        groupBoxAudioBatch->setObjectName(QStringLiteral("groupBoxAudioBatch"));
        horizontalLayout_3 = new QHBoxLayout(groupBoxAudioBatch);
        horizontalLayout_3->setSpacing(5);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(5, 5, 5, 5);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(3);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        listViewAudioBatch = new QListWidget(groupBoxAudioBatch);
        listViewAudioBatch->setObjectName(QStringLiteral("listViewAudioBatch"));

        horizontalLayout_2->addWidget(listViewAudioBatch);

        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        buttonAudioBatchAdd = new QPushButton(groupBoxAudioBatch);
        buttonAudioBatchAdd->setObjectName(QStringLiteral("buttonAudioBatchAdd"));
        buttonAudioBatchAdd->setEnabled(true);
        buttonAudioBatchAdd->setMinimumSize(QSize(104, 0));
        buttonAudioBatchAdd->setLayoutDirection(Qt::LeftToRight);
        buttonAudioBatchAdd->setAutoFillBackground(false);
        buttonAudioBatchAdd->setIcon(icon5);
        buttonAudioBatchAdd->setCheckable(false);
        buttonAudioBatchAdd->setChecked(false);

        verticalLayout_6->addWidget(buttonAudioBatchAdd);

        buttonAudioBatchDelete = new QPushButton(groupBoxAudioBatch);
        buttonAudioBatchDelete->setObjectName(QStringLiteral("buttonAudioBatchDelete"));
        buttonAudioBatchDelete->setEnabled(true);
        buttonAudioBatchDelete->setMinimumSize(QSize(104, 0));
        QIcon icon33;
        icon33.addFile(QStringLiteral(":/buttons/delete.png"), QSize(), QIcon::Normal, QIcon::Off);
        buttonAudioBatchDelete->setIcon(icon33);

        verticalLayout_6->addWidget(buttonAudioBatchDelete);

        buttonAudioBatchClear = new QPushButton(groupBoxAudioBatch);
        buttonAudioBatchClear->setObjectName(QStringLiteral("buttonAudioBatchClear"));
        buttonAudioBatchClear->setEnabled(true);
        buttonAudioBatchClear->setMinimumSize(QSize(104, 0));
        buttonAudioBatchClear->setIcon(icon7);

        verticalLayout_6->addWidget(buttonAudioBatchClear);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_6->addItem(verticalSpacer_3);

        buttonAudioBatchStart = new QPushButton(groupBoxAudioBatch);
        buttonAudioBatchStart->setObjectName(QStringLiteral("buttonAudioBatchStart"));
        buttonAudioBatchStart->setEnabled(true);
        buttonAudioBatchStart->setMinimumSize(QSize(104, 0));
        buttonAudioBatchStart->setIcon(icon6);

        verticalLayout_6->addWidget(buttonAudioBatchStart);


        horizontalLayout_2->addLayout(verticalLayout_6);


        horizontalLayout_3->addLayout(horizontalLayout_2);


        verticalLayout_7->addWidget(groupBoxAudioBatch);

        tabWidget->addTab(tab_audio, QString());
        tab_muxer = new QWidget();
        tab_muxer->setObjectName(QStringLiteral("tab_muxer"));
        verticalLayout_10 = new QVBoxLayout(tab_muxer);
        verticalLayout_10->setSpacing(7);
        verticalLayout_10->setObjectName(QStringLiteral("verticalLayout_10"));
        verticalLayout_10->setContentsMargins(2, 2, 2, 2);
        stackedWidgetMuxer = new QStackedWidget(tab_muxer);
        stackedWidgetMuxer->setObjectName(QStringLiteral("stackedWidgetMuxer"));
        page_Muxer = new QWidget();
        page_Muxer->setObjectName(QStringLiteral("page_Muxer"));
        stackedWidgetMuxer->addWidget(page_Muxer);

        verticalLayout_10->addWidget(stackedWidgetMuxer);

        stackedWidgetDemuxer = new QStackedWidget(tab_muxer);
        stackedWidgetDemuxer->setObjectName(QStringLiteral("stackedWidgetDemuxer"));
        page_Demuxer = new QWidget();
        page_Demuxer->setObjectName(QStringLiteral("page_Demuxer"));
        stackedWidgetDemuxer->addWidget(page_Demuxer);

        verticalLayout_10->addWidget(stackedWidgetDemuxer);

        tabWidget->addTab(tab_muxer, QString());
        tab_mediainfo = new QWidget();
        tab_mediainfo->setObjectName(QStringLiteral("tab_mediainfo"));
        verticalLayout_4 = new QVBoxLayout(tab_mediainfo);
        verticalLayout_4->setSpacing(0);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        stackedWidgetMediaInfo = new QStackedWidget(tab_mediainfo);
        stackedWidgetMediaInfo->setObjectName(QStringLiteral("stackedWidgetMediaInfo"));
        page_MediaInfo = new QWidget();
        page_MediaInfo->setObjectName(QStringLiteral("page_MediaInfo"));
        stackedWidgetMediaInfo->addWidget(page_MediaInfo);

        verticalLayout_4->addWidget(stackedWidgetMediaInfo);

        tabWidget->addTab(tab_mediainfo, QString());

        verticalLayout_3->addWidget(tabWidget);

        MainWindow->setCentralWidget(centralWidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 720, 26));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuRemove_Jobs = new QMenu(menuFile);
        menuRemove_Jobs->setObjectName(QStringLiteral("menuRemove_Jobs"));
        QIcon icon34;
        icon34.addFile(QStringLiteral(":/buttons/clean.png"), QSize(), QIcon::Normal, QIcon::Off);
        menuRemove_Jobs->setIcon(icon34);
        menuRemove_PostOperation = new QMenu(menuFile);
        menuRemove_PostOperation->setObjectName(QStringLiteral("menuRemove_PostOperation"));
        QIcon icon35;
        icon35.addFile(QStringLiteral(":/buttons/flag.png"), QSize(), QIcon::Normal, QIcon::Off);
        menuRemove_PostOperation->setIcon(icon35);
        menuHelp = new QMenu(menubar);
        menuHelp->setObjectName(QStringLiteral("menuHelp"));
        menuDownloadX264 = new QMenu(menuHelp);
        menuDownloadX264->setObjectName(QStringLiteral("menuDownloadX264"));
        menuDownloadX264->setIcon(icon15);
        menuDownloadAvisynth = new QMenu(menuHelp);
        menuDownloadAvisynth->setObjectName(QStringLiteral("menuDownloadAvisynth"));
        menuDownloadAvisynth->setIcon(icon15);
        menuDownloadX265 = new QMenu(menuHelp);
        menuDownloadX265->setObjectName(QStringLiteral("menuDownloadX265"));
        menuDownloadX265->setIcon(icon15);
        menuJob = new QMenu(menubar);
        menuJob->setObjectName(QStringLiteral("menuJob"));
        menuTools = new QMenu(menubar);
        menuTools->setObjectName(QStringLiteral("menuTools"));
        MainWindow->setMenuBar(menubar);
        QWidget::setTabOrder(buttonStartJob, tabWidget);
        QWidget::setTabOrder(tabWidget, buttonAbortJob);
        QWidget::setTabOrder(buttonAbortJob, jobsView);
        QWidget::setTabOrder(jobsView, logView);
        QWidget::setTabOrder(logView, editDetails);
        QWidget::setTabOrder(editDetails, buttonAddJob);
        QWidget::setTabOrder(buttonAddJob, progressBar);
        QWidget::setTabOrder(progressBar, buttonPauseJob);
        QWidget::setTabOrder(buttonPauseJob, listViewAudioBatch);
        QWidget::setTabOrder(listViewAudioBatch, buttonAudioBatchAdd);
        QWidget::setTabOrder(buttonAudioBatchAdd, buttonAudioBatchDelete);
        QWidget::setTabOrder(buttonAudioBatchDelete, buttonAudioBatchClear);
        QWidget::setTabOrder(buttonAudioBatchClear, buttonAudioBatchStart);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuJob->menuAction());
        menubar->addAction(menuTools->menuAction());
        menubar->addAction(menuHelp->menuAction());
        menuFile->addAction(actionOpen);
        menuFile->addAction(actionCreateJob);
        menuFile->addSeparator();
        menuFile->addAction(menuRemove_Jobs->menuAction());
        menuFile->addAction(menuRemove_PostOperation->menuAction());
        menuFile->addSeparator();
        menuFile->addAction(actionCommand_Line);
        menuFile->addAction(actionPython);
        menuFile->addSeparator();
        menuFile->addAction(actionInstaller);
        menuFile->addAction(actionPreferences);
        menuFile->addSeparator();
        menuFile->addAction(actionExit);
        menuRemove_Jobs->addAction(actionCleanupFinished);
        menuRemove_Jobs->addAction(actionCleanupAll);
        menuRemove_PostOperation->addSeparator();
        menuRemove_PostOperation->addAction(actionPostOp_PowerDown);
        menuRemove_PostOperation->addAction(actionPostOp_Hibernate);
        menuRemove_PostOperation->addSeparator();
        menuRemove_PostOperation->addAction(actionPostOp_DoNothing);
        menuHelp->addAction(actionCheckForUpdates);
        menuHelp->addSeparator();
        menuHelp->addAction(actionWebX264);
        menuHelp->addAction(actionWebX265);
        menuHelp->addSeparator();
        menuHelp->addAction(menuDownloadX264->menuAction());
        menuHelp->addAction(menuDownloadX265->menuAction());
        menuHelp->addAction(menuDownloadAvisynth->menuAction());
        menuHelp->addAction(actionWebVapourSynth);
        menuHelp->addSeparator();
        menuHelp->addAction(actionOnlineDocX264);
        menuHelp->addAction(actionOnlineDocX265);
        menuHelp->addAction(actionWebAvsWiki);
        menuHelp->addAction(actionWebVapourSynthDocs);
        menuHelp->addSeparator();
        menuHelp->addAction(actionAbout);
        menuDownloadX264->addAction(actionWebX264VideoLAN);
        menuDownloadX264->addAction(actionWebX264Komisar);
        menuDownloadX264->addSeparator();
        menuDownloadX264->addAction(actionWebX264FreeCodecs);
        menuDownloadAvisynth->addAction(actionWebAvisynth32);
        menuDownloadAvisynth->addAction(actionWebAvisynth64);
        menuDownloadAvisynth->addSeparator();
        menuDownloadAvisynth->addAction(actionWebAvisynthPlus);
        menuDownloadX265->addAction(actionWebX265Fllear);
        menuDownloadX265->addAction(actionWebX265LigH);
        menuDownloadX265->addAction(actionWebX265Snowfag);
        menuDownloadX265->addSeparator();
        menuDownloadX265->addAction(actionWebX265FreeCodecs);
        menuJob->addAction(actionJob_Start);
        menuJob->addAction(actionJob_Pause);
        menuJob->addAction(actionJob_Abort);
        menuJob->addSeparator();
        menuJob->addAction(actionJob_Explore);
        menuJob->addAction(actionJob_Delete);
        menuJob->addAction(actionJob_Edit);
        menuJob->addAction(actionJob_View);
        menuJob->addAction(actionJob_Reset);
        menuJob->addSeparator();
        menuJob->addAction(actionJob_MoveUp);
        menuJob->addAction(actionJob_MoveDown);
        menuTools->addAction(actionScriptCreator);
        menuTools->addAction(actionScriptPlayer);
        menuTools->addAction(actionPreviewDialog);
        menuTools->addSeparator();
        menuTools->addAction(actionVSedit);

        retranslateUi(MainWindow);
        QObject::connect(actionExit, SIGNAL(triggered()), MainWindow, SLOT(close()));
        QObject::connect(actionCreateJob, SIGNAL(triggered()), buttonAddJob, SLOT(click()));
        QObject::connect(actionJob_Start, SIGNAL(triggered()), buttonStartJob, SLOT(click()));
        QObject::connect(actionJob_Abort, SIGNAL(triggered()), buttonAbortJob, SLOT(click()));

        tabWidget->setCurrentIndex(0);
        stackedWidgetAudioEnc->setCurrentIndex(0);
        stackedWidgetMuxer->setCurrentIndex(0);
        stackedWidgetDemuxer->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Qvs", nullptr));
        actionExit->setText(QApplication::translate("MainWindow", "Exit", nullptr));
        actionAbout->setText(QApplication::translate("MainWindow", "About...", nullptr));
        actionWebMulder->setText(QApplication::translate("MainWindow", "MuldeR's Web-Site", nullptr));
        actionWebX264->setText(QApplication::translate("MainWindow", "Official x264 Web-Site", nullptr));
        actionWebX264Komisar->setText(QApplication::translate("MainWindow", "x264 builds for Windows by Komisar", nullptr));
        actionWebX264VideoLAN->setText(QApplication::translate("MainWindow", "x264 builds for Windows by VideoLAN", nullptr));
        actionOnlineDocX264->setText(QApplication::translate("MainWindow", "x264 Online Documentation", nullptr));
        actionWebBluRay->setText(QApplication::translate("MainWindow", "BluRay Authoring Guide", nullptr));
        actionCreateJob->setText(QApplication::translate("MainWindow", "Create New Job", nullptr));
        actionJob_Start->setText(QApplication::translate("MainWindow", "Start Job", nullptr));
        actionJob_Abort->setText(QApplication::translate("MainWindow", "Abort Job", nullptr));
        actionJob_Pause->setText(QApplication::translate("MainWindow", "Pause Job", nullptr));
        actionPreferences->setText(QApplication::translate("MainWindow", "Preferences", nullptr));
        actionJob_Delete->setText(QApplication::translate("MainWindow", "Delete Job", nullptr));
        actionJob_Explore->setText(QApplication::translate("MainWindow", "Explore Job", nullptr));
        actionWebAvisynth32->setText(QApplication::translate("MainWindow", "32-Bit Avisynth (Stable)", nullptr));
        actionWebAvisynth64->setText(QApplication::translate("MainWindow", "64-Bit Avisynth (Deprecated)", nullptr));
        actionWebSecret->setText(QApplication::translate("MainWindow", "Secret Recipe - Confidential", nullptr));
        actionWebAvsWiki->setText(QApplication::translate("MainWindow", "Avisynth Usage Wiki", nullptr));
        actionJob_Reset->setText(QApplication::translate("MainWindow", "Reset Job", nullptr));
        actionWebSupport->setText(QApplication::translate("MainWindow", "Help and Support", nullptr));
        actionOpen->setText(QApplication::translate("MainWindow", "Open...", nullptr));
        actionDownload_Avisynth->setText(QApplication::translate("MainWindow", "Download Avisynth", nullptr));
        actionUtz->setText(QApplication::translate("MainWindow", "utz", nullptr));
        actionWebVapourSynth->setText(QApplication::translate("MainWindow", "Download VapourSynth", nullptr));
        actionWebVapourSynthDocs->setText(QApplication::translate("MainWindow", "VapourSynth Manual", nullptr));
        actionCheckForUpdates->setText(QApplication::translate("MainWindow", "Check for new Updates", nullptr));
        actionWebAvisynthPlus->setText(QApplication::translate("MainWindow", "Avisynth+ (32- and 64-Bit)", nullptr));
        actionWebX265->setText(QApplication::translate("MainWindow", "Official x265 Web-Site", nullptr));
        actionDownload_x265_Binaries->setText(QApplication::translate("MainWindow", "Download x265 Binaries", nullptr));
        actionWebX265Fllear->setText(QApplication::translate("MainWindow", "x265 builds for Windows by Fllear", nullptr));
        actionWebX265FreeCodecs->setText(QApplication::translate("MainWindow", "Codecs.com Mirror (x265)", nullptr));
        actionWebX265Snowfag->setText(QApplication::translate("MainWindow", "x265 builds for Windows by Snowfag", nullptr));
        actionWebX265LigH->setText(QApplication::translate("MainWindow", "x265 builds for Windows by LigH", nullptr));
        actionWebX264FreeCodecs->setText(QApplication::translate("MainWindow", "Codecs.com Mirror (x264)", nullptr));
        actionJob_MoveUp->setText(QApplication::translate("MainWindow", "Move Up", nullptr));
        actionJob_MoveDown->setText(QApplication::translate("MainWindow", "Move Down", nullptr));
        actionOnlineDocX265->setText(QApplication::translate("MainWindow", "x265 Online Documentation", nullptr));
        actionRemove_Jobs->setText(QApplication::translate("MainWindow", "Remove Jobs", nullptr));
        actionCleanupFinished->setText(QApplication::translate("MainWindow", "Remove Completed Jobs", nullptr));
        actionCleanupAll->setText(QApplication::translate("MainWindow", "Remove All Jobs", nullptr));
        actionDo_Nothing->setText(QApplication::translate("MainWindow", "Do Nothing", nullptr));
        actionPostOp_PowerDown->setText(QApplication::translate("MainWindow", "Shutdown Computer", nullptr));
        actionPostOp_Hibernate->setText(QApplication::translate("MainWindow", "Hibernate Computer", nullptr));
        actionPostOp_DoNothing->setText(QApplication::translate("MainWindow", "Do Nothing", nullptr));
        actionJob_Edit->setText(QApplication::translate("MainWindow", "Edit Job", nullptr));
        actionJob_View->setText(QApplication::translate("MainWindow", "View Job", nullptr));
        actionCommand_Line->setText(QApplication::translate("MainWindow", "Terminal CLI", nullptr));
        actionPython->setText(QApplication::translate("MainWindow", "Python CLI", nullptr));
        actionScriptPlayer->setText(QApplication::translate("MainWindow", "Script Player", nullptr));
        actionVSedit->setText(QApplication::translate("MainWindow", "VapourSynth Editor", nullptr));
        actionInstaller->setText(QApplication::translate("MainWindow", "Installer", nullptr));
        actionPreviewDialog->setText(QApplication::translate("MainWindow", "Preview Dialog", nullptr));
        actionScriptCreator->setText(QApplication::translate("MainWindow", "Script Creator", nullptr));
        groupBoxJobDetails->setTitle(QApplication::translate("MainWindow", " Job Details ", nullptr));
        progressBar->setFormat(QApplication::translate("MainWindow", "%v%", nullptr));
        buttonAddJob->setText(QApplication::translate("MainWindow", "Add New Job", nullptr));
        buttonStartJob->setText(QApplication::translate("MainWindow", "Start Job", nullptr));
        buttonPauseJob->setText(QApplication::translate("MainWindow", "Pause Job", nullptr));
        buttonAbortJob->setText(QApplication::translate("MainWindow", "Abort Job", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_main), QApplication::translate("MainWindow", "Main", nullptr));
        groupBoxAudioBatch->setTitle(QApplication::translate("MainWindow", "AudioBatch", nullptr));
        buttonAudioBatchAdd->setText(QApplication::translate("MainWindow", " Add ", nullptr));
        buttonAudioBatchDelete->setText(QApplication::translate("MainWindow", " Del ", nullptr));
        buttonAudioBatchClear->setText(QApplication::translate("MainWindow", "Clear", nullptr));
        buttonAudioBatchStart->setText(QApplication::translate("MainWindow", "Start", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_audio), QApplication::translate("MainWindow", "Audio", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_muxer), QApplication::translate("MainWindow", "Muxer", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_mediainfo), QApplication::translate("MainWindow", "MediaInfo", nullptr));
        menuFile->setTitle(QApplication::translate("MainWindow", "Application", nullptr));
        menuRemove_Jobs->setTitle(QApplication::translate("MainWindow", "Clean-Up", nullptr));
        menuRemove_PostOperation->setTitle(QApplication::translate("MainWindow", "On Completion", nullptr));
        menuHelp->setTitle(QApplication::translate("MainWindow", "Help", nullptr));
        menuDownloadX264->setTitle(QApplication::translate("MainWindow", "Download x264 Binaries", nullptr));
        menuDownloadAvisynth->setTitle(QApplication::translate("MainWindow", "Download Avisynth", nullptr));
        menuDownloadX265->setTitle(QApplication::translate("MainWindow", "Download x265 Binaries", nullptr));
        menuJob->setTitle(QApplication::translate("MainWindow", "Job", nullptr));
        menuTools->setTitle(QApplication::translate("MainWindow", "Tools", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
