#ifndef MAIL_BOX_H
#define MAIL_BOX_H

#include "common.h"
#include <QObject>
#include <QVariant>
#include <QUuid>
#include <QMap>

#define MODULE_MAINWINDOW    EMODULE::eMODULE_MAINWINDOW
#define MODULE_STD_WATCHER   EMODULE::eMODULE_STD_WATCHER
#define MODULE_SCRIPT_PLAYER EMODULE::eMODULE_SCRIPT_PLAYER
#define MODULE_JOB_CHEF      EMODULE::eMODULE_JOB_CHEF

class MailBox;
struct STMAILBOX;

enum class EMODULE
{
	eMODULE_MAINWINDOW,
	eMODULE_STD_WATCHER,
	eMODULE_SCRIPT_PLAYER,
	eMODULE_JOB_CHEF,
	eMODULE_MAX,
};

class MailBox : public QObject
{
	Q_OBJECT

public:
	explicit MailBox(QObject *parent = nullptr);
    ~MailBox();

	static class MailBox *getInstance(void)
	{
		static MailBox s_mailBox;
		return &s_mailBox;
	}

    enum EMAIL_TIMING {
        eMAIL_TIMING_DEFAULT,
        eMAIL_TIMING_PROCESS_STARTED,
        eMAIL_TIMING_PROCESS_ERROR,
        eMAIL_TIMING_PROCESS_FINISHED,
        eMAIL_TIMING_MAX,
    };

    STMAILBOX createMailBoxDefault(void);

signals:
	bool mailRecived(EMODULE, STMAILBOX *);

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

extern QMap<EMODULE, STMAILBOX*> g_pMailBox;

#endif // MAIL_BOX_H
