#include "mainwindow.h"
#include "com/config.h"
#include "com/app_instance_file_guard.h"
#include "com/common.h"

int main(int argc, char *argv[])
{
    /* Application Setup */
    QApplication a(argc, argv);

    /* Application Current Path */
    QDir::setCurrent(QCoreApplication::applicationDirPath());

    /* Global Configure First */
    g_pConfig = new Config();
    g_pConfig->init(a.arguments());

    /* Splash Screen Show */
#ifdef QT_PLASH
    QSplashScreen screen(QPixmap(":/images/splashscreen.png"));
    if(g_pConfig->isStartSplashScreen())
    {
        screen.show();
    }
#endif

    /* Application Instance File Guard */
    AppInstanceFileGuard guard("qvs_running");

    if(g_pConfig->isCheckGuardLocker())
    {
        if(!guard.isLocked())
        {
            qCritical("Couldn't start the qvs.\nAnother instance is probably already running.");
            return (int)eINDEX_NONE;
        }
    }

    /* MainWindow Setup */
    MainWindow w;
    g_pConfig->setMainWindow(&w);
    g_pConfig->initEncodeConfig();  //Init encode config after create classes.

    /* Splash Screen Finish */
#ifdef QT_PLASH
    if(screen.isActiveWindow())
    {
        screen.finish(&w);
    }
#endif

    /* MainWindow Show */
    if(g_pConfig->isShowMainWindow())
    {
        w.show();
    }
    else
    {
        w.modeLaunch();
    }

    return a.exec();
}
