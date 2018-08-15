#ifndef MAIL_BOX_H
#define MAIL_BOX_H

#include <QObject>
#include <QVariant>
#include <QUuid>

class MainWindow;
class MailBox;

struct STMAILBOX;
enum EINDEX;

class MailBox
{
public:
    MailBox();
    ~MailBox();
    class MainWindow *mainUi;

    enum EMODULE {
        eMODULE_MAINWINDOW,
        eMODULE_STD_WATCHER,
        eMODULE_SCRIPT_PLAYER,
        eMODULE_JOB_CHEF,
        eMODULE_TIMER,
        eMODULE_COMMON,
        eMODULE_MAX,
    };

    enum EMAIL_TIMING {
        eMAIL_TIMING_DEFAULT,
        eMAIL_TIMING_PROCESS_STARTED,
        eMAIL_TIMING_PROCESS_ERROR,
        eMAIL_TIMING_PROCESS_FINISHED,
        eMAIL_TIMING_MAX,
    };

    STMAILBOX createMailBoxDefault(void);

public slots:
    void slotCreateMailBox(EMODULE a_module, STMAILBOX a_mail_box);
    void slotCheckUpMailBox(void);
    void slotDeleteMailBox(EMODULE a_module);
    void slotInterruptMailBox(bool a_state = true);
    void releaseMailBox(void);

private:
    bool is_interrupted;
};

struct STMAILBOX
{
    MailBox::EMAIL_TIMING timing;
    EINDEX type;
    QUuid uid;
    QVariant content;
    QVariant content_sub;
    bool is_cyclic;
};

#endif // MAIL_BOX_H
