#ifndef STD_MANAGER_H
#define STD_MANAGER_H

#include "std_watcher.h"
#include <QUuid>

namespace StdManager
{
    QUuid createStdWatch(void);
    StdWatcher* callStdWatch(QUuid a_uid);
    void releaseStdWatch(QUuid a_uid);
    void releaseStdWatchAll(void);
}

#endif // STD_MANAGER_H
