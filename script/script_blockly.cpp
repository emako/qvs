#include "script_blockly.h"
#include "syntax_highlighter.h"
#include "script_player.h"
#include "../tools/std_manager.h"
#include "../preview/preview_dialog.h"
#include "../mainwindow.h"
#include "ui_script_blockly.h"

ScriptBlockly::ScriptBlockly(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ScriptBlockly),
    m_pWebBrowser(new QWebEngineView(this)),
    m_pWebPage(new QWebEnginePage(this)),
    m_pWebChannel(new QWebChannel(this)),
    m_pWebContent(new ScriptBlocklyContent(this)),
    m_pBlocklySchemeHandler(new BlocklySchemeHandler(this)),
    m_pInspector(nullptr)
{
    ui->setupUi(this);
    ui->scriptEditor->setFont(QFont("Consolas"));
#if (QT_VERSION >= QT_VERSION_CHECK(5, 12, 0))
        ui->scriptEditor->setTabStopDistance(QFontMetrics(ui->scriptEditor->font()).width(QT_BLANK) * eINDEX_4);
#else
    ui->scriptEditor->setTabStopWidth(QFontMetrics(ui->scriptEditor->font()).width(QT_BLANK) * eINDEX_4);
#endif
    ui->scrollAreaBlockly->setWidget(m_pWebBrowser);
    m_pWebBrowser->setPage(m_pWebPage);
    m_pWebPage->load(BLOCKLY_URL);
    m_pWebPage->setWebChannel(m_pWebChannel);
    m_pWebChannel->registerObject("app", m_pWebContent);
    m_pWebContent->connect(m_pWebContent, SIGNAL(codeUpdated(const QString &)), this, SLOT(slotCodeUpdated(const QString &)));
    m_pWebContent->connect(m_pWebContent, SIGNAL(saveFilenameUpdated(const QString &)), this, SLOT(slotSaveFilenameUpdated(const QString &)));

    setSyntax();
}

ScriptBlockly::~ScriptBlockly()
{
    delete ui;
    delete m_pSyntaxHighlighter;
    delete m_pWebPage;
    delete m_pWebBrowser;
    delete m_pWebChannel;
    delete m_pWebContent;
}

void ScriptBlockly::keyPressEvent(QKeyEvent * e)
{
    if(e->key() == Qt::Key_F12)
    {
        if (m_pInspector == nullptr)
        {
            m_pInspector = new QWebEngineView();
        }
        m_pInspector->load(QUrl("http://127.0.0.1:7777"));
        m_pInspector->show();
    }
    else if(e->key() == Qt::Key_F5)
    {
        m_pInspector->reload();
    }
}

void ScriptBlockly::closeEvent(QCloseEvent *)
{
//    m_pWebPage->deleteLater();
//    m_pWebBrowser->deleteLater();
}

void ScriptBlockly::setSyntax(void)
{
    m_pSyntaxHighlighter = new SyntaxHighlighter(ui->scriptEditor->document());
}

void ScriptBlockly::clearSyntax(void)
{
    m_pSyntaxHighlighter->clear();
}

void ScriptBlockly::loadCommonConfig(void)
{
    ui->checkBoxNotAddJobOnSaved->setChecked(!g_pConfig->getConfig(Config::eCONFIG_COMMON_ADD_JOB_IMMEDIATELY).toBool());
}

void ScriptBlockly::slotCodeUpdated(const QString &a_code)
{
    ui->scriptEditor->setPlainText(a_code);
}

void ScriptBlockly::on_buttonBrowseSource_clicked()
{
    QString filename = QFileDialog::getSaveFileName(this, tr("Save Script file"), ui->lineEditSave->text(), tr("Script (*.vpy)"));

    if(!filename.isEmpty())
    {
        ui->lineEditSave->setText(QDir::toNativeSeparators(filename));
    }
}

void ScriptBlockly::slotSaveFilenameUpdated(const QString &a_filename)
{
    qDebug() << "SaveFilenameUpdated: " << a_filename;

    if (ui->lineEditSave->text().isEmpty())
    {
        ui->lineEditSave->setText(a_filename + ".vpy");
    }
}

void ScriptBlockly::on_buttonSave_clicked()
{
    if(ui->scriptEditor->toPlainText().isEmpty())
    {
        QMessageBox::warning(this, MESSAGE_WARNING, tr("Script is empty!"), QMessageBox::Ok);
        return;
    }
    if(ui->lineEditSave->text().isEmpty())
    {
        QMessageBox::warning(this, MESSAGE_WARNING, tr("Save filename is empty!"), QMessageBox::Ok);
        return;
    }
    if(qvs::isFileExist(ui->lineEditSave->text()))
    {
        int reply = QMessageBox::question(this, MESSAGE_QUESTION, tr("Output file already exists! Overwrite?"), QMessageBox::Yes | QMessageBox::Cancel);

        if(reply == QMessageBox::Cancel)
        {
            return;
        }
    }

    qvs::setFileText(ui->lineEditSave->text(), ui->scriptEditor->toPlainText());

    if(!ui->checkBoxNotAddJobOnSaved->isChecked())
    {
        this->hide();
        mainUi->execJobCreator(JobCreator::eJOB_RELOAD_DROP, QDir::toNativeSeparators(ui->lineEditSave->text()));
    }
    g_pConfig->setConfig(Config::eCONFIG_COMMON_ADD_JOB_IMMEDIATELY, !ui->checkBoxNotAddJobOnSaved->isChecked());
    this->close();
}

void ScriptBlockly::release(const QUuid &a_uid)
{
    if(g_pPreviewDialogs.contains(a_uid))
    {
        if(g_pPreviewDialogs[a_uid] != nullptr)
        {
            g_pPreviewDialogs[a_uid]->close();
        }
        g_pPreviewDialogs.remove(a_uid);
    }
    else if(g_pScriptPlayers.contains(a_uid))
    {
        if(g_pScriptPlayers[a_uid] != nullptr)
        {
            g_pScriptPlayers[a_uid]->close();
        }
        g_pScriptPlayers.remove(a_uid);
    }
    QFile(previewScriptFilename(a_uid)).remove();
}

QString ScriptBlockly::previewScriptFilename(const QUuid &a_uid)
{
    return "temp." + a_uid.toString().remove(QT_BRACKET_L).remove(QT_BRACKET_R).remove(QT_HYPHEN) + ".vpy";
}

void ScriptBlockly::on_buttonPreview_clicked()
{
    if(ui->scriptEditor->toPlainText().isEmpty())
    {
        QMessageBox::warning(this, MESSAGE_WARNING, tr("Script is empty!"), QMessageBox::Ok);
        return;
    }

    QString script_filename;

    release(m_uid_preview_script);
    m_uid_preview_script = QUuid::createUuid();
    script_filename = previewScriptFilename(m_uid_preview_script);
    qvs::setFileText(script_filename, ui->scriptEditor->toPlainText());

    ScriptPlayer *at_pScriptPlayer = new ScriptPlayer();
    at_pScriptPlayer->mainUi = mainUi;
    at_pScriptPlayer->m_uid_own = m_uid_preview_script;
    at_pScriptPlayer->show();
    at_pScriptPlayer->setReloadTitleShown(false);
    at_pScriptPlayer->slotPlayOnMounted(true);
    at_pScriptPlayer->reload(script_filename);
    g_pScriptPlayers.insert(at_pScriptPlayer->m_uid_own, at_pScriptPlayer);
}
