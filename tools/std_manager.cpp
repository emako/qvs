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
        g_pStdWatch[a_uid]->close();
        g_pStdWatch[a_uid] = nullptr;
        g_pStdWatch.remove(a_uid);
    }
}

void StdManager::releaseStdWatchAll(void)
{
    for(QMap<QUuid, StdWatcher*>::const_iterator i = g_pStdWatch.constBegin(); i != g_pStdWatch.constEnd(); ++i)
    {
        if(g_pStdWatch[i.key()]->isRunning())
        {
            if(QMessageBox::question(nullptr, MESSAGE_QUESTION, QObject::tr("StdWatcher is running!\nDo you really want to abort the job now?"), QMessageBox::Yes | QMessageBox::Cancel) == QMessageBox::Yes)
            {
                /* Abort on y. */
                g_pStdWatch[i.key()]->abortJob();
            }
            else
            {
                /* Skip on n. */
                continue;
            }
        }
        g_pStdWatch[i.key()]->close();
    }
}
