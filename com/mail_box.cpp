#include "mail_box.h"

QMap<EMODULE, STMAILBOX*> g_pMailBox;  /* Map<Receiver, MailBox*> */

MailBox::MailBox(QObject *parent) :
	QObject(parent),
    is_interrupted(false)
{
}

MailBox::~MailBox()
{
}

STMAILBOX MailBox::createMailBoxDefault(void)
{
    STMAILBOX mail_box;

    mail_box.timing      = eMAIL_TIMING_DEFAULT;
    mail_box.uid         = QUuid();
    mail_box.type        = eINDEX_NONE;
    mail_box.content     = QVariant();
    mail_box.content_sub = QVariant();
    mail_box.is_cyclic   = false;
    return mail_box;
}

void MailBox::slotCreateMailBox(EMODULE a_module, STMAILBOX a_mail_box)
{
    STMAILBOX *mail_box = new STMAILBOX();

    mail_box->timing      = a_mail_box.timing;
    mail_box->uid         = a_mail_box.uid;
    mail_box->type        = a_mail_box.type;
    mail_box->content     = a_mail_box.content;
    mail_box->content_sub = a_mail_box.content_sub;
    mail_box->is_cyclic   = a_mail_box.is_cyclic;
    g_pMailBox.insert(a_module, mail_box);
}

void MailBox::slotCheckUpMailBox(void)
{
    if(is_interrupted)
    {
        return;
    }

    for(QMap<EMODULE, STMAILBOX*>::iterator i = g_pMailBox.begin(); i != g_pMailBox.end(); NULL)
    {
        STMAILBOX *mail_box = g_pMailBox[i.key()];
        bool is_erase = emit mailRecived(i.key(), mail_box);

        if((!mail_box->is_cyclic) || is_erase)
        {
            g_pMailBox.erase(i++);
        }
        else
        {
            i++;
        }
    }
}

void MailBox::slotDeleteMailBox(EMODULE a_module)
{
    slotInterruptMailBox(true); /* Interrupt: Disable ergodic. */

    if(g_pMailBox.contains(a_module))
    {
        if(g_pMailBox[a_module] != nullptr)
            delete g_pMailBox[a_module];
        g_pMailBox[a_module] = nullptr;
        g_pMailBox.remove(a_module);
    }

    slotInterruptMailBox(false); /* Interrupt: Enable ergodic. */
}

void MailBox::slotInterruptMailBox(bool a_state)
{
    is_interrupted = a_state;
}

void MailBox::releaseMailBox(void)
{
    for(QMap<EMODULE, STMAILBOX*>::const_iterator i = g_pMailBox.constBegin(); i != g_pMailBox.constEnd(); ++i)
    {
        if(g_pMailBox[i.key()] != nullptr)
            delete g_pMailBox[i.key()];
        g_pMailBox[i.key()] = nullptr;
    }
    g_pMailBox.clear();
}
