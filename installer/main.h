#ifndef MAIN_H
#define MAIN_H

#include <QCoreApplication>
#include <QTextStream>
#include <QDebug>
#include <QResource>
#include <QByteArray>
#include <QFile>
#include <QDir>
#include <QSettings>
#include <QProcess>
#include <QStandardPaths>

#include <windows.h>

enum EINSTALLER_OPTIONS {
    eINSTALLER_OPTIONS_HELP,
    eINSTALLER_OPTIONS_INSTALL,
    eINSTALLER_OPTIONS_UNINSTALL,
    eINSTALLER_OPTIONS_MAX,
};

enum EINSTALLER_CONTENTS {
    eINSTALLER_CONTENTS_PFM,                /* Cmd */
    eINSTALLER_CONTENTS_VS64,               /* Reg */
    eINSTALLER_CONTENTS_AVS32,              /* Reg */
    eINSTALLER_CONTENTS_LAV,                /* Cmd */
    eINSTALLER_CONTENTS_MEDIA,              /* Reg */
    eINSTALLER_CONTENTS_VSEDIT_RECOVERY,    /* Cmd */
    eINSTALLER_CONTENTS_VSEDIT_TEMPLATE,    /* Cmd */
    eINSTALLER_CONTENTS_MAX,
};

bool saveCmd(void);
bool toCmd(EINSTALLER_CONTENTS a_content);
bool toReg(EINSTALLER_CONTENTS a_content);
QString getWinRegOption(void);
QString getRegText(EINSTALLER_CONTENTS a_content);
QString replaceRegText(QString a_text);
QString toRegPath(QString a_text);
void getPfmInstallerFilename(void);
bool getPortableMode(void);
void getConfigFile(void);

QTextStream& qStdOut(void);
QTextStream& qErrOut(void);
void printHelp(void);


#endif // MAIN_H
