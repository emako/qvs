#include "main.h"
#include "process.h"

#undef QT_REG_TEST
#define QT_REG_TEST
#undef QT_REG_TEST

static const char MAKE_FLAG_MEDIAINFO_PATH[] = "$(MEDIAINFO_PATH)";
static const char MAKE_FLAG_QVS_HOME[]       = "$(QVS_HOME)";
static const char MAKE_FLAG_VS_VERSION[]     = "$(VS_VERSION)";
static const char PFM_INSTALLER_FILENAME[]   = "pfm-%1-vapoursynth-win";
static const char REG_INSTALLER_FILENAME[]   = "qvs-installer-%1.reg";
static const char BAT_INSTALLER_FILENAME[]   = "qvs-installer.bat";
static const char SETTINGS_FILE_NAME[]       = "/qvs.config";

static const char QT_NOR_PATH_SPR[]   = "/";
static const char QT_DOS_PATH_SPR[]   = "\\";
static const char QT_REG_PATH_SPR[]   = "\\\\";

static const char *g_pfm_version = "192";
static const char *g_vs_version  = "R54@qvs_portable";

static QString g_settings_file_path;
static QString g_pfm_filename;
static QString g_current_path;
static QString g_env_system_root;
static QString g_current_path_reg_type;
static EINSTALLER_OPTIONS g_installer_option = eINSTALLER_OPTIONS_HELP;
static QStringList cmds;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QStringList args = a.arguments();

    g_current_path = QDir::toNativeSeparators(QCoreApplication::applicationDirPath());
    g_env_system_root = QProcessEnvironment::systemEnvironment().value("SystemRoot");
    g_current_path_reg_type = toRegPath(g_current_path);
    QDir::setCurrent(g_current_path);
    getConfigFile();
    getPfmInstallerFilename();

    if(args.length() == 2)
    {
        if(args[1] == "-h" || args[1] == "--help")
        {
            printHelp();
            return 0;
        }
        else if(args[1] == "-i" || args[1] == "--install" || args[1] == "-u" || args[1] == "--uninstall")
        {
            qStdOut() << "Error: empty content." << endl;
            printHelp();
            return 1;
        }
    }
    else if(args.length() > 2)
    {
        if(args[1] == "-i" || args[1] == "--install")
        {
            g_installer_option = eINSTALLER_OPTIONS_INSTALL;
        }
        else if(args[1] == "-u" || args[1] == "--uninstall")
        {
            g_installer_option = eINSTALLER_OPTIONS_UNINSTALL;
        }
        else
        {
            qStdOut() << "Error: invalid option." << endl;
            printHelp();
            return 1;
        }
        for(int i = 0; i < args.length(); i++)
        {
            if(i == 0 || i == 1)
            {
                continue;
            }
            if(args[i] == "vs64")
            {
                toReg(eINSTALLER_CONTENTS_VS64);
            }
            else if(args[i] == "avs32")
            {
                toReg(eINSTALLER_CONTENTS_AVS32);
                toCmd(eINSTALLER_CONTENTS_AVS32);
            }
            else if(args[i] == "pfm")
            {
                toCmd(eINSTALLER_CONTENTS_PFM);
            }
            else if(args[i] == "lav")
            {
                toCmd(eINSTALLER_CONTENTS_LAV);
            }
            else if(args[i] == "media")
            {
                toReg(eINSTALLER_CONTENTS_MEDIA);
            }
            else if(args[i] == "vsedit-recovery")
            {
                toCmd(eINSTALLER_CONTENTS_VSEDIT_RECOVERY);
            }
            else if(args[i] == "vsedit-template")
            {
                toCmd(eINSTALLER_CONTENTS_VSEDIT_TEMPLATE);
            }
            else
            {
                continue;
            }
        }
        saveCmd();
        qStdOut() << "Installer start ..." << endl;

#if 0
        WinExec((LPCSTR)QString(BAT_INSTALLER_FILENAME).toLocal8Bit(), SW_SHOW);
#endif

        Process process;
        process.m_process_installer.start(BAT_INSTALLER_FILENAME);
        process.m_process_installer.waitForFinished(-1);

#ifndef QT_REG_TEST
        QFile(BAT_INSTALLER_FILENAME).remove();
#endif

        qStdOut() << "Installer completed." << endl;
    }
    else
    {
        printHelp();
        return 1;
    }
    return 0;
}

QTextStream &qStdOut(void)
{
    static QTextStream qstdout(stdout);
    return qstdout;
}

QTextStream &qErrOut(void)
{
    static QTextStream qerrout(stderr);
    return qerrout;
}

void printHelp(void)
{
    QString filename = ":/strings/qvs-installer-usage";
    QFile file;

    file.setFileName(filename);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    qStdOut() << file.readAll();
    file.close();
}

bool getPortableMode(void)
{
    QString applicationDir = QCoreApplication::applicationDirPath();
    QString settingsFilePath = applicationDir + SETTINGS_FILE_NAME;
    QFileInfo settingsFileInfo(settingsFilePath);
    bool portableMode = (settingsFileInfo.exists() && settingsFileInfo.isWritable());
    return portableMode;
}

void getConfigFile(void)
{
    QString applicationDir = QCoreApplication::applicationDirPath();

    if(getPortableMode())
    {
        g_settings_file_path = applicationDir + SETTINGS_FILE_NAME;
    }
    else
    {
        g_settings_file_path = QStandardPaths::writableLocation(QStandardPaths::GenericConfigLocation) + SETTINGS_FILE_NAME;
    }
    g_settings_file_path = QDir::toNativeSeparators(g_settings_file_path);
}

void getPfmInstallerFilename(void)
{
    QSettings settings(g_settings_file_path, QSettings::IniFormat);
    QString at_pfm_version;

    settings.beginGroup("installer");
    at_pfm_version = settings.value("pfm_version", QString(g_pfm_version)).toString();
    g_pfm_filename = QString(PFM_INSTALLER_FILENAME).arg(at_pfm_version);
}

QString toRegPath(QString a_text)
{
    a_text = a_text.replace(QT_DOS_PATH_SPR, QT_REG_PATH_SPR);
    return a_text;
}

QString replaceRegText(QString a_text)
{
    a_text = a_text.replace(MAKE_FLAG_MEDIAINFO_PATH, g_current_path_reg_type + toRegPath(QDir::toNativeSeparators("/qvs")));
    a_text = a_text.replace(MAKE_FLAG_QVS_HOME, g_current_path_reg_type);
    a_text = a_text.replace(MAKE_FLAG_VS_VERSION, g_vs_version);
    return a_text;
}

QString getRegText(EINSTALLER_CONTENTS a_content)
{
    QString filename;
    QFile file;
    QString text;

    if(g_installer_option == eINSTALLER_OPTIONS_INSTALL)
    {
        switch(a_content){
        case eINSTALLER_CONTENTS_VS64:  { filename = ":/strings/qvs-installer-vs64-reg";  break; }
        case eINSTALLER_CONTENTS_AVS32: { filename = ":/strings/qvs-installer-avs32-reg"; break; }
        case eINSTALLER_CONTENTS_MEDIA: { filename = ":/strings/qvs-installer-media-reg"; break; }
        default:                        {                                                 break; }
        }
    }
    else if(g_installer_option == eINSTALLER_OPTIONS_UNINSTALL)
    {
        switch(a_content){
        case eINSTALLER_CONTENTS_VS64:  { filename = ":/strings/qvs-installer-vs64-u-reg";  break; }
        case eINSTALLER_CONTENTS_AVS32: { filename = ":/strings/qvs-installer-avs32-u-reg"; break; }
        case eINSTALLER_CONTENTS_MEDIA: { filename = ":/strings/qvs-installer-media-u-reg"; break; }
        default:                        {                                                   break; }
        }
    }
    file.setFileName(filename);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    text = replaceRegText(QString(file.readAll()));
    file.close();
    return text;
}

QString getWinRegOption(void)
{
    QString option;
    if(g_installer_option == eINSTALLER_OPTIONS_INSTALL)
    {
        option = "/s";
    }
    else if(g_installer_option == eINSTALLER_OPTIONS_UNINSTALL)
    {
        option = "/s /u";
    }
    return option;
}

bool toReg(EINSTALLER_CONTENTS a_content)
{
    QString filename = QString(REG_INSTALLER_FILENAME).arg(a_content);
    QFile file(filename);
    QTextStream out(&file);

    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qErrOut() << "Open failed." << endl;
        return false;
    }
    out << getRegText(a_content);
    file.close();

    cmds << QString("regedit %1 \"%2\"").arg(getWinRegOption()).arg(g_current_path + QDir::separator() + QString(REG_INSTALLER_FILENAME).arg(a_content));

#ifndef QT_REG_TEST
    cmds << QString("del %1").arg(filename);
#endif

    return true;
}

bool toCmd(EINSTALLER_CONTENTS a_content)
{
    switch (a_content)
    {
    case eINSTALLER_CONTENTS_PFM:
    {
        QString option;
        if(g_installer_option == eINSTALLER_OPTIONS_INSTALL)
        {
            option = "install";
        }
        else if(g_installer_option == eINSTALLER_OPTIONS_UNINSTALL)
        {
            option = "uninstall";
        }
        cmds << QString("\"%1\" %2").arg(g_current_path + QDir::separator() + "tools" + QDir::separator() + QString(g_pfm_filename)).arg(option);
        break;
    }
    case eINSTALLER_CONTENTS_AVS32:
    {
        QString src_path = g_current_path + QDir::separator() + "avisynth32" + QDir::separator() + "coreplugins" + QDir::separator();
        QString tar_path = g_env_system_root + QDir::separator() + "SysWOW64" + QDir::separator();
        if(g_installer_option == eINSTALLER_OPTIONS_INSTALL)
        {
            cmds << QString("copy \"%1\" \"%2\"").arg(src_path + "avisynth.dll").arg(tar_path);
            cmds << QString("copy \"%1\" \"%2\"").arg(src_path + "devil.dll").arg(tar_path);
            cmds << QString("copy \"%1\" \"%2\"").arg(src_path + "msvcp60.dll").arg(tar_path);
#ifdef LWL_AV_EXTERN
            cmds << QString("copy \"%1\" \"%2\"").arg(src_path + "avcodec-57.dll").arg(tar_path);
            cmds << QString("copy \"%1\" \"%2\"").arg(src_path + "avformat-57.dll").arg(tar_path);
            cmds << QString("copy \"%1\" \"%2\"").arg(src_path + "avresample-3.dll").arg(tar_path);
            cmds << QString("copy \"%1\" \"%2\"").arg(src_path + "avutil-55.dll").arg(tar_path);
            cmds << QString("copy \"%1\" \"%2\"").arg(src_path + "swscale-4.dll").arg(tar_path);
#endif
        }
        else if(g_installer_option == eINSTALLER_OPTIONS_UNINSTALL)
        {
            cmds << QString("del \"%1\"").arg(tar_path + "avisynth.dll");
            cmds << QString("del \"%1\"").arg(tar_path + "devil.dll");
#ifdef LWL_AV_EXTERN
            cmds << QString("del \"%1\"").arg(tar_path + "avcodec-57.dll");
            cmds << QString("del \"%1\"").arg(tar_path + "avformat-57.dll");
            cmds << QString("del \"%1\"").arg(tar_path + "avresample-3.dll");
            cmds << QString("del \"%1\"").arg(tar_path + "avutil-55.dll");
            cmds << QString("del \"%1\"").arg(tar_path + "swscale-4.dll");
#endif
        }
        break;
    }
    case eINSTALLER_CONTENTS_LAV:
    {
        QString cmd = QString("regsvr32 %1 ").arg(getWinRegOption());
        cmds << cmd + "\"" + g_current_path + QDir::separator() + "tools" + QDir::separator() + "LAVFilters" + QDir::separator() + "x64" + QDir::separator() + QString("LAVAudio.ax") + "\"";
        cmds << cmd + "\"" + g_current_path + QDir::separator() + "tools" + QDir::separator() + "LAVFilters" + QDir::separator() + "x64" + QDir::separator() + QString("LAVSplitter.ax") + "\"";
        cmds << cmd + "\"" + g_current_path + QDir::separator() + "tools" + QDir::separator() + "LAVFilters" + QDir::separator() + "x64" + QDir::separator() + QString("LAVVideo.ax") + "\"";
        cmds << cmd + "\"" + g_current_path + QDir::separator() + "tools" + QDir::separator() + "LAVFilters" + QDir::separator() + "x86" + QDir::separator() + QString("LAVAudio.ax") + "\"";
        cmds << cmd + "\"" + g_current_path + QDir::separator() + "tools" + QDir::separator() + "LAVFilters" + QDir::separator() + "x86" + QDir::separator() + QString("LAVSplitter.ax") + "\"";
        cmds << cmd + "\"" + g_current_path + QDir::separator() + "tools" + QDir::separator() + "LAVFilters" + QDir::separator() + "x86" + QDir::separator() + QString("LAVVideo.ax") + "\"";
        break;
    }
    case eINSTALLER_CONTENTS_VSEDIT_RECOVERY:
        if(g_installer_option == eINSTALLER_OPTIONS_INSTALL)
        {
            cmds << "\"" + g_current_path + QDir::separator() + "vsedit-recovery\" -q";
        }
        break;
    case eINSTALLER_CONTENTS_VSEDIT_TEMPLATE:
        if(g_installer_option == eINSTALLER_OPTIONS_INSTALL)
        {
            cmds << "\"" + g_current_path + QDir::separator() + "vsedit-template\"";
        }
        break;
    default:
        break;
    }
    return true;
}

bool saveCmd(void)
{
    QFile file(BAT_INSTALLER_FILENAME);
    QTextStream out(&file);

    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qErrOut() << "Open failed." << endl;
        return false;
    }
    out << cmds.join("\n");
    file.close();
    return true;
}

