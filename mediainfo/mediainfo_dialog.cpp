#include "mediainfo_dialog.h"
#include "mediainfo_loader.h"
#include "mainwindow.h"
#include "com/common.h"
#include "../script/script_player.h"
#include "ui_mediainfo_dialog.h"

MediaInfoDialog::MediaInfoDialog(QWidget *parent) :
    QWidget(parent),
    m_fromCLI(false),
    ui(new Ui::MediaInfoDialog),
    m_pContextMenu(nullptr),
    m_isFFprobe(false),
    m_child(false)
{
    ui->setupUi(this);
    this->setupUi();
}

MediaInfoDialog::~MediaInfoDialog()
{
    delete m_pContextMenu;
    delete ui;
}

void MediaInfoDialog::setupUi(void)
{
    this->setAcceptDrops(true);
    this->setAttribute(Qt::WA_DeleteOnClose, true);
    ui->editMediaInfo->setAcceptDrops(false);
    ui->editMediaInfo->setContextMenuPolicy(Qt::CustomContextMenu);

    /* MediaInfoMenu */
    m_pContextMenu = new QMenu(ui->editMediaInfo);
    QAction *at_action_load = new QAction(QIcon(":/buttons/folder_add.png"), tr("Open..."), ui->editMediaInfo);
    QAction *at_action_preview = new QAction(QIcon(":/buttons/film.png"), tr("Preview"), ui->editMediaInfo);
    QAction *at_action_copy = new QAction(QIcon(":/buttons/page_paste.png"), tr("Copy to Clipboard"), ui->editMediaInfo);
    QAction *at_action_save = new QAction(QIcon(":/buttons/disk.png"), tr("Save to the Same Here"), ui->editMediaInfo);
    QAction *at_action_add_media_form = new QAction(QIcon(":/buttons/application_add.png"), tr("Add a Form"), ui->editMediaInfo);
    QAction *at_action_calc_md5 = new QAction(QIcon(":/buttons/tag_blue.png"), tr("Calculate MD5"), ui->editMediaInfo);
    QAction *at_action_using_ffprobe = new QAction(QIcon(":/buttons/ffmpeg.png"), tr("From FFprobe"), ui->editMediaInfo);
    QAction *at_action_show_full_info = new QAction(QIcon(":/buttons/text_wrapping.png"), tr("Show Full Info"), ui->editMediaInfo);
    QAction *at_action_enable_line_wrapping = new QAction(QIcon(":/buttons/text_wrapping.png"), tr("Enable Line Wrap"), ui->editMediaInfo);
    at_action_using_ffprobe->setCheckable(true);
    at_action_show_full_info->setCheckable(true);
    at_action_enable_line_wrapping->setCheckable(true);
    at_action_enable_line_wrapping->setChecked(true);
    m_pContextMenu->addActions(QList<QAction*>() << at_action_load << at_action_add_media_form);
    m_pContextMenu->addSeparator();
    m_pContextMenu->addActions(QList<QAction*>() << at_action_preview << at_action_copy << at_action_save);
    m_pContextMenu->addSeparator();
    m_pContextMenu->addActions(QList<QAction*>() << at_action_calc_md5 << at_action_using_ffprobe << at_action_show_full_info << at_action_enable_line_wrapping);
    connect(at_action_load, SIGNAL(triggered()), this, SLOT(selectMediafile()));
    connect(at_action_add_media_form, SIGNAL(triggered()), this, SLOT(addMediainfoForm()));
    connect(at_action_preview, SIGNAL(triggered()), this, SLOT(slotPreview()));
    connect(at_action_copy, SIGNAL(triggered()), this, SLOT(on_buttonMediaInfoCopy_clicked()));
    connect(at_action_save, SIGNAL(triggered()), this, SLOT(on_buttonMediaInfoSave_clicked()));
    connect(at_action_using_ffprobe, SIGNAL(triggered(bool)), this, SLOT(setFFprobe(bool)));
    connect(at_action_show_full_info, SIGNAL(triggered(bool)), this, SLOT(setFull(bool)));
    connect(at_action_enable_line_wrapping, SIGNAL(triggered(bool)), this, SLOT(setWrapped(bool)));
    connect(at_action_calc_md5, SIGNAL(triggered()), this, SLOT(calcMd5()));

    /*Signal*/
    connect(&m_process_sub, SIGNAL(readyReadStandardError()), this, SLOT(slotSubProcessReadyReadStandardError()));
    connect(&m_process_sub, SIGNAL(readyReadStandardOutput()), this, SLOT(slotSubProcessReadyReadStandardOutput()));
}

void MediaInfoDialog::setChild(bool a_child)
{
    m_child = a_child;
    ui->editMediaInfo->setAcceptDrops(true);
    this->setAcceptDrops(true);
}

bool MediaInfoDialog::isChild(void)
{
    return m_child;
}

void MediaInfoDialog::setPath(const QString &a_filename)
{
    m_mediainfo_path = a_filename;
}

QString MediaInfoDialog::getPath(void)
{
    return m_mediainfo_path;
}

void MediaInfoDialog::append(QString a_text)
{
    ui->editMediaInfo->append(a_text);
}

void MediaInfoDialog::clear(void)
{
    ui->editMediaInfo->clear();
}

void MediaInfoDialog::reload(QString a_filename)
{
    if(!a_filename.isEmpty())
    {
        showMediaInfo(a_filename, ui->checkBoxMediaInfoFull->isChecked());
        m_mediainfo_path = a_filename;
    }
}

void MediaInfoDialog::reload(void)
{
    if(!m_mediainfo_path.isEmpty())
    {
        showMediaInfo(m_mediainfo_path, ui->checkBoxMediaInfoFull->isChecked());
    }
}

void MediaInfoDialog::showMediaInfo(void)
{
    showMediaInfo(m_mediainfo_path, ui->checkBoxMediaInfoFull->isChecked());
}

void MediaInfoDialog::showMediaInfo(const QString &a_filename)
{
    showMediaInfo(a_filename, ui->checkBoxMediaInfoFull->isChecked());
}

void MediaInfoDialog::showMediaInfo(const QString &a_filename, bool a_is_full_info)
{
    if(a_filename.isEmpty())
    {
        return;
    }

    if(m_fromCLI)
    {
        QString cmd;

        if(m_isFFprobe)
        {
            cmd = QString("%1 -show_streams -show_chapters -of json %3 \"%2\"").arg(qvs::findFirstFilePath(MEDIAINFO_DIALOG_EXEC_FFPROBE)).arg(a_filename).arg(QString("-show_format ") + QString((a_is_full_info) ? "-show_data" : QT_EMPTY));
        }
        else
        {
            cmd = QString("%1 \"%2\"").arg(qvs::findFirstFilePath(MEDIAINFO_DIALOG_EXEC_MEDIAINFO)).arg(a_filename) + ((a_is_full_info) ? " -f" : "");
        }

        ui->editMediaInfo->clear();
        if(m_process_sub.state() != QProcess::NotRunning)
        {
            m_process_sub.kill();
            m_process_sub.waitForFinished();
        }
        m_process_sub.start(cmd);
    }
    else
    {
        MediaInfoLoader mediainfoLoder(a_filename);

        setLanguage(&mediainfoLoder);
        ui->editMediaInfo->setText(mediainfoLoder.inform(a_is_full_info));
        mediainfoLoder.close();
    }
}

void MediaInfoDialog::on_editMediaInfo_customContextMenuRequested(const QPoint &)
{
    m_pContextMenu->exec(QCursor::pos());
}

void MediaInfoDialog::on_buttonMediaInfoSave_clicked()
{
    QString text = this->toPlainText();
    QString filename = QString("%1.txt").arg(m_mediainfo_path);

    if( text.isEmpty() || m_mediainfo_path.isEmpty() )
    {
        return;
    }

    if(qvs::setFileText(filename, text))
    {
        qDebug() << QMessageBox::warning(this,tr("test"), tr("msg"), tr("Yesd"), tr("No"), tr("Cancel"));
        QMessageBox::information(this, tr("Information"), tr("Saved successfully.\nLocation is \"%1\".").arg(filename), QMessageBox::NoButton);
    }
    else
    {
        QMessageBox::critical(this, tr("Failed"), tr("Save is failed."), QMessageBox::Discard);
    }
}

void MediaInfoDialog::on_buttonMediaInfoCopy_clicked()
{
    QClipboard *clipboard = QApplication::clipboard();
    QString text = this->toPlainText();

    clipboard->setText(text);
}

void MediaInfoDialog::setWrapped(bool a_enable)
{
    if(a_enable)
    {
        ui->editMediaInfo->setLineWrapMode(QTextEdit::WidgetWidth);
    }
    else
    {
        ui->editMediaInfo->setLineWrapMode(QTextEdit::NoWrap);
    }
}

void MediaInfoDialog::calcMd5(void)
{
    if(!m_mediainfo_path.isEmpty())
    {
        if(!isChild())
        {
            mainUi->m_timer->start(Timer::ETIMER_TYPE_ONE_SHOT, Timer::ETIMER_SLOT_CALC_MD5);
        }
        else
        {
            QString md5 = mainUi->m_com->getHashMd5(getPath());

            clear();
            append(tr("Filename: ") + QFileInfo(getPath()).fileName());
            append(tr("MD5: ") + md5);
        }
    }
}

void MediaInfoDialog::setFull(bool a_state)
{
    ui->checkBoxMediaInfoFull->setChecked(a_state);
}

void MediaInfoDialog::on_checkBoxMediaInfoFull_stateChanged(int a_state)
{
    showMediaInfo(m_mediainfo_path, static_cast<bool>(a_state));
    m_pContextMenu->actions().at(eCONTEXT_MENU_SHOW_FULL_INFO)->setChecked(static_cast<bool>(a_state));
}

void MediaInfoDialog::setFFprobe(bool a_state)
{
    m_isFFprobe = a_state;
    m_fromCLI = a_state;
    reload();
}

void MediaInfoDialog::slotSubProcessReadyReadStandardError()
{
    QByteArray standardError = m_process_sub.readAllStandardError();
    QString standardErrorText = QString::fromUtf8(standardError);
    standardErrorText = standardErrorText.trimmed();
    if(!standardErrorText.isEmpty())
    {
       ui->editMediaInfo->append(standardErrorText);
       ui->editMediaInfo->moveCursor(QTextCursor::Start);
    }
}

void MediaInfoDialog::slotSubProcessReadyReadStandardOutput()
{
    QByteArray standardOutput = m_process_sub.readAllStandardOutput();
    QString standardOutputText = QString::fromUtf8(standardOutput);
    standardOutputText = standardOutputText.trimmed();
    if(!standardOutputText.isEmpty())
    {
        ui->editMediaInfo->append(standardOutputText);
        ui->editMediaInfo->moveCursor(QTextCursor::Start);
    }
}

void MediaInfoDialog::selectMediafile(void)
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Open Mediafile"), NULLSTR, tr("Media (*.*)"));

    if(!filename.isEmpty())
    {
        reload(filename);
    }
}

void MediaInfoDialog::addMediainfoForm(void)
{
    MediaInfoDialog *new_form = new MediaInfoDialog();
    new_form->mainUi = mainUi;
    new_form->setChild(true);
    new_form->m_uid_own = QUuid::createUuid();
    new_form->resize(this->width(), this->height());
    new_form->show();
    mainUi->m_pMediaInfoDialogs.insert(new_form->m_uid_own, new_form);
}

void MediaInfoDialog::slotPreview(void)
{
    if(m_mediainfo_path.isEmpty())
    {
        return;
    }

    ScriptPlayer *at_pScriptPlayer = new ScriptPlayer();

    at_pScriptPlayer->mainUi = mainUi;
    at_pScriptPlayer->m_uid_own = QUuid::createUuid();

    if(at_pScriptPlayer->reloadTypeDetect(m_mediainfo_path) == ScriptPlayer::eSCRIPT_TYPE_NOT_SCRIPT)
    {
        at_pScriptPlayer->hide();
        QProcess::startDetached(QString("cmd /c %1").arg(m_mediainfo_path));
        delete at_pScriptPlayer;
        at_pScriptPlayer = nullptr;
    }
    else
    {
        at_pScriptPlayer->show();
        at_pScriptPlayer->slotPlayOnMounted(true);
        at_pScriptPlayer->reload(m_mediainfo_path);
        mainUi->m_pScriptPlayers.insert(at_pScriptPlayer->m_uid_own, at_pScriptPlayer);
    }
}

void MediaInfoDialog::on_buttonMediaInfoPreview_clicked()
{
    slotPreview();
}

void MediaInfoDialog::dragEnterEvent(QDragEnterEvent* e)
{
    if(e->mimeData()->hasText())
    {
        e->acceptProposedAction();
    }
}

void MediaInfoDialog::dropEvent(QDropEvent* e)
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
            showMediaInfo(filename, ui->checkBoxMediaInfoFull->isChecked());
            m_mediainfo_path = filename;
        }
    }
    e->acceptProposedAction();
}

void MediaInfoDialog::closeEvent(QCloseEvent *e)
{
    StdManager::releaseStdWatch(m_uid);
    mainUi->slotChildWindowClosed(m_uid_own);
    e->accept();
}

void MediaInfoDialog::setLanguage(MediaInfoLoader *a_pMediaInfoLoader)
{
    switch(mainUi->language())
    {
    case Config::eLANGUAGE_EN:
    default:
        a_pMediaInfoLoader->language();
        break;
    case Config::eLANGUAGE_ZH:
        a_pMediaInfoLoader->language("zh-CN");
        break;
    case Config::eLANGUAGE_JA:
        a_pMediaInfoLoader->language("ja");
        break;
    }
}

QString MediaInfoDialog::toPlainText(void)
{
    QString text = ui->editMediaInfo->toPlainText();

    if(mainUi->language() != Config::eLANGUAGE_EN)
    {
        /* Clear HTML format. */
        text.replace(QString(QT_NOR_EOL) + QString(QT_NOR_EOL), QString(QT_NOR_EOL));
        text.replace(QString(QT_COLON) + QString(QT_NOR_EOL), QString(QT_COLON) + QString(QT_BLANK));
    }
    return text;
}
