#ifndef STD_MANAGER_H
#define STD_MANAGER_H

#include "std_watcher.h"
#include <QUuid>

class StdManager
{
public:
    static QUuid createStdWatch(void);
    static StdWatcher* callStdWatch(QUuid a_uid);
    static void releaseStdWatch(QUuid a_uid);
    static void releaseStdWatchAll(void);
};

#endif // STD_MANAGER_H
