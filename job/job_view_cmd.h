#ifndef JOB_VIEW_CMD_H
#define JOB_VIEW_CMD_H

#include "job_item.h"
#include <QDialog>

class MainWindow;
class StdWatcherCmd;

namespace Ui {
class JobViewCmd;
}

class JobViewCmd : public QDialog
{
    Q_OBJECT

public:
    explicit JobViewCmd(QDialog *parent = nullptr);
    ~JobViewCmd();

    enum ERELOAD_MODE
    {
        eRELOAD_MODE_NONE,
        eRELOAD_MODE_JOB_ITEM,
        eRELOAD_MODE_STD_WATCHER_CMD_LIST,
        eRELOAD_MODE_MAX,
    };

    void setup(void);

    void reload(JobItem a_job_item);
    void reload(QList<StdWatcherCmd> a_job_item);
    void reload(QStringList a_job_item);
    void reload(QString a_html);

    QString createCommand(bool a_is_detail = false);
    void showCommand(bool a_is_detail);
    int lookupJobEncoder(QList<JobCmdList> a_cmds, QUuid a_uid);
    QString getConfigName(JobCreator::EJOB_CONFIG a_job_config);

private slots:
    void setWrapped(bool a_enable);

    void on_checkBoxShowDetail_stateChanged(int a_state);
    void on_buttonSave_clicked();
    void on_buttonCopy_clicked();
    void on_buttonClose_clicked();
    void on_plainTextEdit_customContextMenuRequested(const QPoint &a_pos);

private:
    Ui::JobViewCmd *ui;
    JobItem m_job_item;
    ERELOAD_MODE m_mode;
    QMenu *m_pViewMenu;
};

extern const char *c_config_key[JobCreator::eJOB_CONFIG_MAX];
extern const char *c_config_type[JobCmdList::eJOB_CMD_TYPE_MAX];

#endif // JOB_VIEW_CMD_H
