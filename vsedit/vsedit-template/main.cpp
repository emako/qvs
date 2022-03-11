#include <QCoreApplication>
#include <QFile>
#include <QFileInfo>
#include <QStandardPaths>
#include <QSettings>
#include <QResource>

#ifdef QT_DEBUG
#include <QDebug>
#endif

QString m_settingsFilePath;
const char SETTINGS_FILE_NAME[] = "/vsedit.config";

QString readTemplete(void);
void setTemplete(void);
bool getPortableMode(void);
bool setPortableMode(bool a_portableMod);

QString readTemplete(void)
{
    QString text;
    QFile file("template.vpy");

    if(file.exists() && file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QByteArray all = file.readAll();
        text = all;
        file.close();
    }
    else
    {
#ifdef QT_DEBUG
        QResource res(":/template/template.vpy");
        QByteArray resData((const char *)res.data(), res.size());
        text = QString::fromUtf8(resData);
#endif
    }
    if(text.isEmpty())
    {
        text = "import vapoursynth as vs\nimport havsfunc as haf\nimport mvsfunc as mvf\nimport qvs\n\ncore = vs.get_core()\nsrc = qvs.LWLSource(None)\nsrc.set_output()";
    }
#ifdef QT_DEBUG
    qDebug() << "template:" << text;
#endif
    return text;
}

void setTemplete(void)
{
    QString applicationDir = QCoreApplication::applicationDirPath();
    bool portableMode = getPortableMode();
    if(portableMode){
        m_settingsFilePath = applicationDir + SETTINGS_FILE_NAME;
    }
    else{
        m_settingsFilePath = QStandardPaths::writableLocation(QStandardPaths::GenericConfigLocation) + SETTINGS_FILE_NAME;
    }

    QSettings setting(m_settingsFilePath, QSettings::IniFormat);
    setting.beginGroup("common");
    setting.setValue("new_script_template", readTemplete());
    setting.endGroup();
}

bool getPortableMode(void)
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
    QCoreApplication a(argc, argv);
    setTemplete();
    return a.exit();
}
