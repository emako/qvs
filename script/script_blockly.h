#ifndef SCRIPT_BLOCKLY_H
#define SCRIPT_BLOCKLY_H

#include "../com/common.h"
#include "../com/config.h"
#include "blockly_scheme_handler.h"
#include "script_blockly_content.h"
#include <QWidget>
#include <QUuid>
#include <QWebEngineView>
#include <QWebEnginePage>
#include <QWebEngineProfile>
#include <QtWebChannel>

namespace Ui {
class ScriptBlockly;
}
class MainWindow;
class SyntaxHighlighter;

class ScriptBlockly : public QWidget
{
    Q_OBJECT

public:
    explicit ScriptBlockly(QWidget *parent = nullptr);
    ~ScriptBlockly();
    friend class MainWindow;
    class MainWindow *mainUi;
    QUuid m_uid_own;

protected slots:
    void keyPressEvent(QKeyEvent * e);
    void closeEvent(QCloseEvent *e);

private slots:
    void slotCodeUpdated(const QString &code);
    void slotSaveFilenameUpdated(const QString &a_filename);
    void on_buttonBrowseSource_clicked();
    void on_buttonSave_clicked();
    void on_buttonPreview_clicked();

private:
    void loadCommonConfig(void);
    void setSyntax(void);
    void clearSyntax(void);

    void release(const QUuid &a_uid);
    QString previewScriptFilename(const QUuid &a_uid);

private:
    Ui::ScriptBlockly *ui;
    QWebEngineView *m_pWebBrowser;
    QWebEnginePage *m_pWebPage;
    QWebChannel *m_pWebChannel;
    ScriptBlocklyContent *m_pWebContent;
    BlocklySchemeHandler *m_pBlocklySchemeHandler;
    QWebEngineView *m_pInspector;
    SyntaxHighlighter *m_pSyntaxHighlighter;

    QUuid m_uid_preview_script;
};

#endif // SCRIPT_BLOCKLY_H
