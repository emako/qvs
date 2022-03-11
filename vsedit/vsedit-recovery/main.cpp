#include "vseditrecovery.h"
#include <QCoreApplication>
#include <QApplication>
#include <QFile>
#include <QFileInfo>
#include <QStandardPaths>
#include <QSettings>

QString m_settingsFilePath;
const char SETTINGS_FILE_NAME[] = "/vsedit.config";

void setFactoryReset();
bool getPortableMode();
bool setPortableMode(bool a_portableMod);

void setFactoryReset()
{
    QString applicationDir = QCoreApplication::applicationDirPath();
    bool portableMode = getPortableMode();
    if(portableMode){
        m_settingsFilePath = applicationDir + SETTINGS_FILE_NAME;
    }
    else{
        m_settingsFilePath = QStandardPaths::writableLocation(QStandardPaths::GenericConfigLocation) + SETTINGS_FILE_NAME;
    }
    QFile::remove(m_settingsFilePath);
}

bool getPortableMode()
{
    QString applicationDir = QCoreApplication::applicationDirPath();
    QString settingsFilePath = applicationDir + SETTINGS_FILE_NAME;
    QFileInfo settingsFileInfo(settingsFilePath);
    bool portableMode = (settingsFileInfo.exists() && settingsFileInfo.isWritable());
    return portableMode;
}

bool setPortableMode(bool a_portableMod)
{
    bool currentModePortable = getPortableMode();
    if(a_portableMod == currentModePortable)
        return true;
    QString applicationDir = QCoreApplication::applicationDirPath();
    QString genericConfigDir = QStandardPaths::writableLocation(
        QStandardPaths::GenericConfigLocation);
    QString newSettingsFilePath;
    if(a_portableMod)
        newSettingsFilePath = applicationDir + SETTINGS_FILE_NAME;
    else
        newSettingsFilePath = genericConfigDir + SETTINGS_FILE_NAME;
    // When copying portable settings to common folder - another settings
    // file may already exist there. Need to delete it first.
    if(QFile::exists(newSettingsFilePath)){
        bool settingsFileDeleted = QFile::remove(newSettingsFilePath);
        if(!settingsFileDeleted)
            return false;
    }
    bool settingsFileCopied = QFile::copy(m_settingsFilePath, newSettingsFilePath);
    QString oldSettingsFilePath = m_settingsFilePath;
    m_settingsFilePath = newSettingsFilePath;
    if(a_portableMod){
        return settingsFileCopied;
    }
    else if(settingsFileCopied){
        bool portableSettingsFileDeleted = QFile::remove(oldSettingsFilePath);
        return portableSettingsFileDeleted;
    }
    return false;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    setFactoryReset();
    VseditRecovery w;
    if(argc >= 2)
    {
        if(QString(argv[1]) == "-q")
            w.setIsShowMessage(false);
    }
    w.hide();
    return a.exec();
}
