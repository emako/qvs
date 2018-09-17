#ifndef MERGE_H
#define MERGE_H

#include <QWidget>

#define MERGE_EXT_MP4 "mp4"
#define MERGE_EXT_MKV "mkv"
#define MERGE_EXT_FLV "flv"
#define MERGE_EXT_TS "ts"
#define MERGE_EXT_MOV "mov"
#define MERGE_EXT_AVI "avi"

#define toStdStringData(a) QString(a).toStdString().data()

namespace Ui {
class Merge;
}

class MainWindow;
class StdWatcherCmd;

class QMenu;

class Merge : public QWidget
{
    Q_OBJECT

public:
    explicit Merge(QWidget *parent = 0);
    ~Merge();
    friend class MainWindow;
    class MainWindow *mainUi;

    enum EMERGE_MODE {
        eMERGE_MODE_CONTAINER,
        eMERGE_MODE_COMBINE,
        eMERGE_MODE_COPY,
        eMERGE_MODE_CAT,
        eMERGE_MODE_CUSTOM,
        eMERGE_MODE_MAX,
    };

    enum EMERGE_TYPE {
        eMERGE_TYPE_MULTIPLE_LINES,
        eMERGE_TYPE_SINGLE_LINE,
        eMERGE_TYPE_MAX,
    };

    enum EMERGE_STACKED_WIDGET_MODE {
        eMERGE_STACKED_WIDGET_MODE_CONTAINER,
        eMERGE_STACKED_WIDGET_MODE_CUSTOM,
        eMERGE_STACKED_WIDGET_MODE_MAX,
    };

    enum EMERGE_CONTAINER_AUDIO_CODEC {
        eMERGE_CONTAINER_AUDIO_CODEC_COPY,
        eMERGE_CONTAINER_AUDIO_CODEC_AAC,
        eMERGE_CONTAINER_AUDIO_CODEC_MAX,
    };

    enum ECONTEXT_MENU {
        eCONTEXT_MENU_LOAD_FROM_FILES,
        eCONTEXT_MENU_LOAD_FROM_FILE_TEXT,
        eCONTEXT_MENU_LOAD_FROM_CLIPBOARD,
        eCONTEXT_MENU_SEPARATOR_0,
        eCONTEXT_MENU_DELETE,
        eCONTEXT_MENU_CLEAR,
        eCONTEXT_MENU_SEPARATOR_1,
        eCONTEXT_MENU_MOVE_UP,
        eCONTEXT_MENU_MOVE_DOWN,
        eCONTEXT_MENU_MAX,
    };

    void reload(const QString &a_filename);
    void reload(const QStringList &a_filenames);
    QList<StdWatcherCmd> createCommand(void);
    QList<StdWatcherCmd> createCommand(EMERGE_TYPE type, QStringList a_inputs, QString a_output, QString a_cmd, QString a_param);

public slots:
    void load(void);
    void listCtrl(void);

private slots:
    void on_buttonDebug_clicked();
    void on_buttonStart_clicked();
    void on_comboBoxMode_currentIndexChanged(int a_index);
    void on_comboBoxCustomType_currentIndexChanged(int a_index);
    void on_listWidget_customContextMenuRequested(const QPoint &a_pos);

private:
    Ui::Merge *ui;
    QMenu *m_pContextMenu;
    void setup(void);
};

#endif // MERGE_H
