#ifndef MEDIAINFO_H
#define MEDIAINFO_H

#include <QWidget>
#include <QMenu>
#include <QProcess>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMimeData>
#include <QUrl>
#include <QFileInfo>
#include <QUuid>

#define MEDIAINFO_DIALOG_EXEC_FFPROBE "ffprobe"
#define MEDIAINFO_DIALOG_EXEC_MEDIAINFO "mediainfo"

class MainWindow;
class MediaInfoLoader;

namespace Ui {
class MediaInfoDialog;
}

class MediaInfoDialog : public QWidget
{
    Q_OBJECT

public:
    explicit MediaInfoDialog(QWidget *parent = nullptr);
    ~MediaInfoDialog();
    friend class MainWindow;
    class MainWindow *mainUi;
    void setupUi(void);
    void setChild(bool a_child);
    bool isChild(void);

    void showMediaInfo(void);
    void showMediaInfo(const QString &a_filename, bool a_is_full_info);
    void showMediaInfo(const QString &a_filename);

    QUuid m_uid_own; /* For Own (called).      */
    QUuid m_uid;     /* For StdWatcher (call). */
    bool m_fromCLI;

    enum ECONTEXT_MENU
    {
        eCONTEXT_MENU_LOAD,
        eCONTEXT_MENU_ADD_A_FORM,
        eCONTEXT_MENU_SEPARATOR_0,
        eCONTEXT_MENU_PREVIEW,
        eCONTEXT_MENU_COPY,
        eCONTEXT_MENU_SAVE,
        eCONTEXT_MENU_SEPARATOR_1,
        eCONTEXT_MENU_CALA_MD5,
        eCONTEXT_MENU_USING_FFPROBE,
        eCONTEXT_MENU_SHOW_FULL_INFO,
        eCONTEXT_MENU_ENABLE_LINE_WARP,
        eCONTEXT_MENU_MAX,
    };

    void setPath(const QString &a_filename);
    QString getPath(void);
    void append(QString a_text);
    void clear(void);

private slots:
    void reload(QString a_filename);
    void reload(void);
    void slotPreview(void);
    void selectMediafile(void);
    void addMediainfoForm(void);
    void setFFprobe(bool a_state);
    void setFull(bool a_state);
    void setWrapped(bool a_enable);
    void calcMd5(void);
    void setLanguage(MediaInfoLoader *a_pMediaInfoLoader);
    QString toPlainText(void);

    void on_editMediaInfo_customContextMenuRequested(const QPoint &a_pos);
    void on_buttonMediaInfoSave_clicked();
    void on_buttonMediaInfoCopy_clicked();
    void on_checkBoxMediaInfoFull_stateChanged(int a_state);
    void on_buttonMediaInfoPreview_clicked();

private:
    Ui::MediaInfoDialog *ui;
    QMenu *m_pContextMenu;
    QProcess m_process_sub;
    QString m_mediainfo_path;
    bool m_isFFprobe;
    bool m_child;

protected slots:
    virtual void dragEnterEvent(QDragEnterEvent *e);
    virtual void dropEvent(QDropEvent *e);
    virtual void closeEvent(QCloseEvent *e);
    /*Sub Process*/
    virtual void slotSubProcessReadyReadStandardError();
    virtual void slotSubProcessReadyReadStandardOutput();
};

#endif // MEDIAINFO_H
