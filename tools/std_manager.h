#ifndef STD_MANAGER_H
#define STD_MANAGER_H

#include "std_watcher.h"
#include <QUuid>

class ScriptPlayer;
class MediaInfoDialog;
class PreviewDialog;
class ScriptCreator;
class ScriptBlockly;

extern QMap<QUuid, StdWatcher*> g_pStdWatch;
extern QMap<QUuid, ScriptPlayer *> g_pScriptPlayers;
extern QMap<QUuid, MediaInfoDialog *> g_pMediaInfoDialogs;
extern QMap<QUuid, PreviewDialog *> g_pPreviewDialogs;
extern QMap<QUuid, ScriptCreator *> g_pScriptCreators;
extern QMap<QUuid, ScriptBlockly *> g_pScriptBlocklys;
extern QMap<QUuid, QWidget *> g_pMinimizeWidgets;

namespace StdManager
{
    QUuid createStdWatch(void);
    StdWatcher* callStdWatch(QUuid a_uid);
    void releaseStdWatch(QUuid a_uid);
    void releaseStdWatchAll(void);
}

#endif // STD_MANAGER_H
