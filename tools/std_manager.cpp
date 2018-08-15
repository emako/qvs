#include "std_manager.h"

QMap<QUuid, StdWatcher*> g_pStdWatch;
QUuid g_now_uid;

QUuid StdManager::createStdWatch(void)
{
    g_now_uid = QUuid::createUuid();
    g_pStdWatch.insert(g_now_uid, new StdWatcher());
    return g_now_uid;
}

StdWatcher *StdManager::callStdWatch(QUuid a_uid)
{
    return g_pStdWatch[a_uid];
}

void StdManager::releaseStdWatch(QUuid a_uid)
{
    if(g_pStdWatch.contains(a_uid))
    {
        g_pStdWatch[a_uid]->close();
        g_pStdWatch.remove(a_uid);
    }
}

void StdManager::releaseStdWatchAll(void)
{
    for(QMap<QUuid, StdWatcher*>::const_iterator i = g_pStdWatch.constBegin(); i != g_pStdWatch.constEnd(); ++i)
    {
        if(g_pStdWatch[i.key()]->isRunning())
        {
            if(QMessageBox::question(NULL, QObject::tr("Question"), QObject::tr("StdWatcher is running!\nDo you really want to abort the job now?"), QMessageBox::Yes | QMessageBox::Cancel) == QMessageBox::Yes)
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
