#include "std_manager.h"

QMap<QUuid, StdWatcher*> g_pStdWatch;

QUuid StdManager::createStdWatch(void)
{
    QUuid uid = QUuid::createUuid();
    g_pStdWatch.insert(uid, new StdWatcher());
    return uid;
}

StdWatcher *StdManager::callStdWatch(QUuid a_uid)
{
    return g_pStdWatch[a_uid];
}

void StdManager::releaseStdWatch(QUuid a_uid)
{
    /* Not recommended for be called in slot func of close event. */

    if(g_pStdWatch.contains(a_uid))
    {
        if(g_pStdWatch[a_uid] != nullptr)
        {
            g_pStdWatch[a_uid]->close();
        }
        g_pStdWatch[a_uid] = nullptr;
        g_pStdWatch.remove(a_uid);
    }
}

void StdManager::releaseStdWatchAll(void)
{
    QMap<QUuid, StdWatcher*> at_pStdWatchClone = g_pStdWatch;

    for(QMap<QUuid, StdWatcher*>::iterator i = at_pStdWatchClone.begin(); i != at_pStdWatchClone.end(); i++)
    {
        if (at_pStdWatchClone[i.key()] == nullptr)
        {
            continue;
        }

        if(at_pStdWatchClone[i.key()]->isRunning())
        {
            if(QMessageBox::question(at_pStdWatchClone[i.key()], MESSAGE_QUESTION, QObject::tr("StdWatcher is running!\nDo you really want to abort the job now?"), QMessageBox::Yes | QMessageBox::Cancel) == QMessageBox::Yes)
            {
                /* Abort on y. */
                at_pStdWatchClone[i.key()]->abortJob();
            }
            else
            {
                /* Skip on n. */
                continue;
            }
        }

        at_pStdWatchClone[i.key()]->close();
    }
}
