#ifndef CONFIG_H
#define CONFIG_H

#include "../job/job_creator.h"
#include "../tools/audio_config.h"

#include <QObject>
#include <QSettings>
#include <QFileInfo>
#include <QCoreApplication>
#include <QStandardPaths>
#include <QSplashScreen>
#include <QDebug>

#define ENV_PYTHON_HOME               "PYTHONHOME"
#define ENV_PATH                      "PATH"

#define REG_HKEY_SOFTWARE_VS          "HKEY_LOCAL_MACHINE\\SOFTWARE\\VapourSynth"
#define REG_HKEY_SOFTWARE_AVS         "HKEY_LOCAL_MACHINE\\SOFTWARE\\Avisynth"
#define REG_HKEY_SOFTWARE_VS2         "HKEY_LOCAL_MACHINE\\SOFTWARE\\WOW6432Node\\VapourSynth"

#define REG_KEY_VS_VERSION            "Version"
#define REG_KEY_VS_PATH               "Path"
#define REG_KEY_VS_PYTHON_PATH        "PythonPath"
#define REG_KEY_VS_CORE_PLUGINS       "CorePlugins"
#define REG_KEY_VS_PLUGINS            "Plugins"
#define REG_KEY_VS_VAPOURSYNTH_DLL    "VapourSynthDLL"
#define REG_KEY_VS_VSSCRIPT_DLL       "VSScriptDLL"
#define REG_KEY_AVS_INIT_DIR          "initialplugindir"
#define REG_KEY_AVS_PLUGIN_DIR        "plugindir2_5"

extern const char *c_config_key[JobCreator::eJOB_CONFIG_MAX];

class MainWindow;
class JobCreator;
class Config;

extern Config *g_pConfig;

class Config : public QObject
{
    Q_OBJECT
public:
    explicit Config(QObject *parent = nullptr);
    class MainWindow *mainUi;
    void setMainWindow(MainWindow *a_pMainUi);

    enum ECONFIG_TYPE {
        eCONFIG_TYPE_FIRST,
        eCONFIG_TYPE_COMMON,
        eCONFIG_TYPE_ENCODE,
        eCONFIG_TYPE_ENCODE_AUDIO,
        eCONFIG_TYPE_MAX,
    };

    enum ECONFIG_COMMON {
        eCONFIG_COMMON_NOT_AUTO_NEXT_JOB,
        eCONFIG_COMMON_PREFER_AVS_32BIT,
        eCONFIG_COMMON_STYLE_FACTORY,
        eCONFIG_COMMON_ENCODER_PRECESS_PRIORITY,
        eCONFIG_COMMON_START_JOB_IMMEDIATELY,
        eCONFIG_COMMON_SCRIPT_PLAYER_PLAYER,
        eCONFIG_COMMON_PREVIEW_FPS_LIMIT_CUSTOM,
        eCONFIG_COMMON_PREVIEW_ZOOM_MODE,
        eCONFIG_COMMON_PREVIEW_SCALE_MODE,
        eCONFIG_COMMON_PREVIEW_TIMELINE_DISPLAY_MODE,
        eCONFIG_COMMON_PREVIEW_LAST_SNAPSHOT_EXT,
        eCONFIG_COMMON_MAX,
    };

    enum ECONFIG_FIRST {
        eCONFIG_FIRST_GUARD_LOCKER,
        eCONFIG_FIRST_SPLASH_SCREEN,
        eCONFIG_FIRST_CLI_FILENAME,
        eCONFIG_FIRST_FIRST_LAUNCH,
        eCONFIG_FIRST_MAX,
    };

    enum ECONFIG_INSTALLER {
        eCONFIG_INSTALLER_PFM,
        eCONFIG_INSTALLER_VS64,
        eCONFIG_INSTALLER_AVS32,
        eCONFIG_INSTALLER_LAV,
        eCONFIG_INSTALLER_MEDIA,
        eCONFIG_INSTALLER_MAX,
    };

    enum ELAUNCH_MODE {
        eLAUNCH_MODE_NORMAL,
        eLAUNCH_MODE_NORMAL_ADD_JOB,
        eLAUNCH_MODE_MEDIAINFO,
        eLAUNCH_MODE_COPY_PATH_DOS,
        eLAUNCH_MODE_COPY_PATH_UNIX,
        eLAUNCH_MODE_COPY_PATH_PYTHON,
        eLAUNCH_MODE_SHOW_HELP,
        eLAUNCH_MODE_EXIT,
        eLAUNCH_MODE_MAX,
    };

    enum ECONFIG_PYTHON {
        eCONFIG_PYTHON_D2V,
        eCONFIG_PYTHON_DG,
        eCONFIG_PYTHON_DGNV,
        eCONFIG_PYTHON_DGIM,
        eCONFIG_PYTHON_MAX,
    };

    QMap<ECONFIG_FIRST, QVariant> m_config_first;
    QMap<ECONFIG_COMMON, QVariant> m_config_common;
    QMap<ECONFIG_INSTALLER, QVariant> m_config_installer;
    QMap<QString, QMap<JobCreator::EJOB_CONFIG, QVariant>> m_config_encode_templates;
    QMap<QString, AudioAdvancedConfig> m_config_audio_encode_templates;

    QVariant getConfig(ECONFIG_FIRST a_key);
    void setConfig(ECONFIG_FIRST a_key, QVariant a_value);
    QVariant getConfig(ECONFIG_COMMON a_key);
    void setConfig(ECONFIG_COMMON a_key, QVariant a_value);
    QVariant getConfig(ECONFIG_INSTALLER a_key);
    void setConfig(ECONFIG_INSTALLER a_key, QVariant a_value);

    void init(QStringList a_args);
    void initArgs(QStringList a_args);
    void initFirstConfig(void);
    void initFirstConfigDefault(void);
    void initCommonConfig(void);
    void initCommonConfigDefault(void);
    void initEncodeConfig(void);
    void initEncodeAudioConfig(void);
    void initInstallerConfig(void);

    void saveConfigAll(void);
    QJsonObject configToJson(QMap<JobCreator::EJOB_CONFIG, QVariant> a_config);
    QMap<JobCreator::EJOB_CONFIG, QVariant> jsonToConfig(QJsonObject a_json);

    QJsonObject audioConfigToJson(AudioAdvancedConfig a_config);
    AudioAdvancedConfig jsonToAudioConfig(QJsonObject a_json);

    void setLaunchMode(void);
    ELAUNCH_MODE getLaunchMode(void);

    bool isStartSplashScreen(void);
    bool isCheckGuardLocker(void);
    bool isShowMainWindow(void);

    void setConfigEncodeTemplate(QString a_key, QMap<JobCreator::EJOB_CONFIG, QVariant> a_config);
    QMap<JobCreator::EJOB_CONFIG, QVariant> getConfigEncodeTemplate(QString a_key);
    void removeConfigEncodeTemplate(QString a_key);
    bool containsConfigEncodeTemplate(QString a_key);

    void setConfigAudioEncodeTemplate(QString a_key, AudioAdvancedConfig a_config);
    AudioAdvancedConfig getConfigAudioEncodeTemplate(QString a_key);
    void removeConfigAudioEncodeTemplate(QString a_key);
    bool containsConfigAudioEncodeTemplate(QString a_key);

    bool deleteConfigFile(void);

    QVariant valueInGroup(const QString & a_group, const QString & a_key, const QVariant & a_defaultValue) const;
    bool setValueInGroup(const QString & a_group, const QString & a_key, const QVariant & a_value);
    bool deleteValueInGroup(const QString & a_group, const QString & a_key);
    QVariant value(const QString & a_key, const QVariant & a_defaultValue) const;
    bool setValue(const QString & a_key, const QVariant & a_value);
    QStringList groupKeys(const QString & a_group);

    void reset(ECONFIG_TYPE a_config_type);
    QVariant pyValue(const QString & a_key, const QVariant & a_defaultValue) const;
    bool pySetValue(const QString & a_key, const QVariant & a_value);

    QString getEnv(QString value);
    QString getReg(QString key, QString hkey);

private:
    QString m_settingsFilePath;
    ELAUNCH_MODE m_launchMode;
    QStringList m_args;
    QList<QVariant> m_config_first_default;
    QList<QVariant> m_config_common_default;
    bool m_isInitConfigInstaller;

    void getConfigFile(void);
    bool getPortableMode(void);

public slots:
};

#endif // CONFIG_H
