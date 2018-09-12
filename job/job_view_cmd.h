#ifndef JOB_VIEW_CMD_H
#define JOB_VIEW_CMD_H

#include "job_item.h"
#include <QDialog>

class MainWindow;

namespace Ui {
class JobViewCmd;
}

class JobViewCmd : public QDialog
{
    Q_OBJECT

public:
    explicit JobViewCmd(QDialog *parent = 0);
    ~JobViewCmd();
    void reload(JobItem a_job_item);

    QString createCommand(bool a_is_detail = false);
    void showCommand(bool a_is_detail);
    int lookupJobEncoder(QList<JobCmdList> a_cmds, QUuid a_uid);
    QString getConfigName(JobCreator::EJOB_CONFIG a_job_config);

    class MainWindow *mainUi;

private slots:
    void on_checkBoxShowDetail_stateChanged(int a_state);
    void on_buttonSave_clicked();
    void on_buttonCopy_clicked();
    void on_buttonClose_clicked();

private:
    Ui::JobViewCmd *ui;
    JobItem m_job_item;
};

#endif // JOB_VIEW_CMD_H
