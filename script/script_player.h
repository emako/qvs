#ifndef SCRIPT_PLAYER_H
#define SCRIPT_PLAYER_H

#include <QWidget>
#include "../tools/std_manager.h"

class MainWindow;
struct STMAILBOX;

namespace Ui {
class ScriptPlayer;
}

class ScriptPlayer : public QWidget
{
    Q_OBJECT

public:
    explicit ScriptPlayer(QWidget *parent = 0);
    ~ScriptPlayer();
    friend class MainWindow;
    class MainWindow *mainUi;
    void loadCommonConfig(void);
    void setPlayAvisynthWith32Bit(bool a_is32Bit);
    QUuid m_uid_own;     /* For Own (called).      */
    QUuid m_uid_preview; /* For Preview (call).    */
    QUuid m_uid_std;     /* For StdWatcher (call). */

    enum ESCRIPT_TYPE {
        eSCRIPT_TYPE_VS,
        eSCRIPT_TYPE_AVS,
        eSCRIPT_TYPE_NOT_SCRIPT,
    };

    enum ECONTEXT_MENU {
        eCONTEXT_MENU_EXPLORE,
        eCONTEXT_MENU_COPY_CLIP_PATH,
        eCONTEXT_MENU_SEPARATOR_0,
        eCONTEXT_MENU_PLAY_ON_MOUNTED,
        eCONTEXT_MENU_SHOW_STD_WATCHER,
        eCONTEXT_MENU_MAX,
    };

    enum ESCRIPT_PLAYER_PLAYER {
        eSCRIPT_PLAYER_PLAYER_SYSTEM,
        eSCRIPT_PLAYER_PLAYER_PREVIEW,
        eSCRIPT_PLAYER_PLAYER_VIRTUAL_DUB64,
        eSCRIPT_PLAYER_PLAYER_MAX,
    };

    void setupUi(void);
    void reload(QString a_filename);
    ESCRIPT_TYPE reloadTypeDetect(QString a_filename);
    void setNotScriptMessage(const QString &a_filename);
    void setErrorLog(void);
    QString getErrorLogFilename(void);
    QString getScriptFilename(void);
    QString getOutputFilename(void);
    void setReloadTitleShown(bool a_shown);

    QMenu *m_pContextMenu;
    QString m_filename;
    ESCRIPT_TYPE m_script_type;

public slots:
    bool slotMail(STMAILBOX* a_mail_box);
    void exploreVolumes(void);
    void slotCopyClipPath(void);
    void slotPlayOnMounted(bool a_isPlay);
    void showStdwatcher(bool a_isShow);
    void releasePreviewDialog(const QUuid &a_uid);

private slots:
    void on_buttonMount_clicked(bool a_checked);
    void on_buttonPlay_clicked();
    void on_editMountMessage_customContextMenuRequested(const QPoint &a_pos);
    void on_buttonInput_clicked();
    void on_comboBoxPlayer_currentIndexChanged(int a_index);

protected slots:
    void dragEnterEvent(QDragEnterEvent* e);
    void dropEvent(QDropEvent* e);
    void closeEvent(QCloseEvent *e);

private:
    Ui::ScriptPlayer *ui;
    bool m_isPlayOnMounted;
    bool m_isPlayAvsWith32Bit;
    bool m_reloadTitleShown;
};

#endif // SCRIPT_PLAYER_H
