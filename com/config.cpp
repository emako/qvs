#include "config.h"
#include "common.h"
#include "../mainwindow.h"
#include "../job/job_chef.h"
#include "../job/job_view_cmd.h"
#include "../tools/installer_dialog.h"

const char SETTINGS_PY_FILE_NAME[]        = "./Lib/site-packages/qvs.conf";
const char SETTINGS_FILE_NAME[]           = "/qvs.config";
const char COMMON_GROUP[]                 = "common";
const char ENCODING_PRESETS_GROUP[]       = "encoding_presets";
const char ENCODING_AUDIO_PRESETS_GROUP[] = "encoding_audio_presets";
const char INSTALLER_GROUP[]              = "installer";
const char PYTHON_GROUP[]                 = "python";

const char *c_config_common_key[Config::eCONFIG_COMMON_MAX] = {
    "not_auto_next_job",                /*eCONFIG_COMMON_NOT_AUTO_NEXT_JOB*/
    "prefer_avs_32bit",                 /*eCONFIG_COMMON_PREFER_AVS_32BIT*/
    "style_factory",                    /*eCONFIG_COMMON_STYLE_FACTORY*/
    "encoder_precess_priority",         /*eCONFIG_COMMON_ENCODER_PRECESS_PRIORITY*/
    "start_job_immediately",            /*eCONFIG_COMMON_START_JOB_IMMEDIATELY*/
    "add_job_immediately",              /*eCONFIG_COMMON_ADD_JOB_IMMEDIATELY*/
    "script_player_player",             /*eCONFIG_COMMON_SCRIPT_PLAYER_PLAYER*/
    "preview_custom_fps",               /*eCONFIG_COMMON_PREVIEW_FPS_LIMIT_CUSTOM*/
    "preview_zoom_mode",                /*eCONFIG_COMMON_PREVIEW_ZOOM_MODE*/
    "preview_scale_mode",               /*eCONFIG_COMMON_PREVIEW_SCALE_MODE*/
    "preview_timeline_display_mode",    /*eCONFIG_COMMON_PREVIEW_TIMELINE_DISPLAY_MODE*/
    "preview_last_snapshot_ext",        /*eCONFIG_COMMON_PREVIEW_LAST_SNAPSHOT_EXT*/
    "encoding_audio_current_presets",   /*eCONFIG_COMMON_ENCODING_AUDIO_CURRENT_PRESETS*/
};

const char *c_config_first_key[Config::eCONFIG_FIRST_MAX] = {
    QT_EMPTY,                           /*eCONFIG_FIRST_GUARD_LOCKER*/
    "splash_screen",                    /*eCONFIG_FIRST_SPLASH_SCREEN*/
    QT_EMPTY,                           /*eCONFIG_FIRST_CLI_FILENAME*/
    "first_launch",                     /*eCONFIG_FIRST_FIRST_LAUNCH*/
    "language",                         /*eCONFIG_FIRST_LANGUAGE*/
};

const char *c_config_installer_key[Config::eCONFIG_INSTALLER_MAX] = {
    "pfm_installed",                    /*eCONFIG_INSTALLER_PFM*/
    "vs64_installed",                   /*eCONFIG_INSTALLER_VS64*/
    "avs32_installed",                  /*eCONFIG_INSTALLER_AVS32*/
    "lav_installed",                    /*eCONFIG_INSTALLER_LAV*/
    "media_installed",                  /*eCONFIG_INSTALLER_MEDIA*/
};

const char *c_config_python_key[Config::eCONFIG_PYTHON_MAX] = {
    "d2v",                              /*eCONFIG_PYTHON_D2V*/
    "dg",                               /*eCONFIG_PYTHON_DG*/
    "dgnv",                             /*eCONFIG_PYTHON_DGNV*/
    "dgim",                             /*eCONFIG_PYTHON_DGIM*/
};

Config::Config(QObject *parent) :
    QObject(parent),
    m_launchMode(eLAUNCH_MODE_NORMAL),
    m_isInitConfigInstaller(false)
{
    this->getConfigFile();
}

void Config::init(QStringList a_args)
{
    initArgs(a_args);
    initFirstConfig();
}

void Config::initArgs(QStringList a_args)
{
    m_args = a_args;
    setLaunchMode();
}

void Config::initFirstConfigDefault(void)
{
    m_config_first_default << QVariant((m_launchMode == eLAUNCH_MODE_NORMAL) ? true : false); /*eCONFIG_FIRST_GUARD_LOCKER*/
    m_config_first_default << QVariant(false); /*eCONFIG_FIRST_SPLASH_SCREEN*/
    m_config_first_default << QVariant(QT_EMPTY); /*eCONFIG_FIRST_CLI_FILENAME: Can't insert config after init arguments.*/
    m_config_first_default << QVariant(true); /*eCONFIG_FIRST_FIRST_LAUNCH*/
    m_config_first_default << QVariant(eLANGUAGE_EN); /*eCONFIG_FIRST_LANGUAGE*/
}

void Config::initFirstConfig(void)
{
    initFirstConfigDefault();
    m_config_first.insert(eCONFIG_FIRST_GUARD_LOCKER, m_config_first_default.at(eCONFIG_FIRST_GUARD_LOCKER).toBool());
    m_config_first.insert(eCONFIG_FIRST_SPLASH_SCREEN, ( (m_launchMode == eLAUNCH_MODE_NORMAL) && value(c_config_first_key[eCONFIG_FIRST_SPLASH_SCREEN], m_config_first_default.at(eCONFIG_FIRST_SPLASH_SCREEN)).toBool() ));
    m_config_first.insert(eCONFIG_FIRST_FIRST_LAUNCH, value(c_config_first_key[eCONFIG_FIRST_FIRST_LAUNCH], m_config_first_default.at(eCONFIG_FIRST_FIRST_LAUNCH)).toBool() );
    m_config_first.insert(eCONFIG_FIRST_LANGUAGE, value(c_config_first_key[eCONFIG_FIRST_LANGUAGE], m_config_first_default.at(eCONFIG_FIRST_LANGUAGE)).toInt() );

    qDebug() << QString("[%1]").arg(COMMON_GROUP);
    for(QMap<ECONFIG_FIRST, QVariant>::iterator i = m_config_first.begin(); i != m_config_first.end(); i++)
    {
        qDebug() << QString("%1:%2=").arg(i.key()).arg(QString(c_config_first_key[i.key()]).isEmpty() ? "empty_key" : c_config_first_key[i.key()]) << i.value();
    }
}

void Config::initCommonConfigDefault(void)
{
    m_config_common_default << QVariant(false); /* eCONFIG_COMMON_NOT_AUTO_NEXT_JOB */
    m_config_common_default << QVariant(false); /* eCONFIG_COMMON_PREFER_AVS_32BIT */
    m_config_common_default << QVariant(eINDEX_NONE); /* eCONFIG_COMMON_STYLE_FACTORY */
    m_config_common_default << QVariant(JobChef::ePROCESS_PRIORITY_NORMAL_INDEX); /* eCONFIG_COMMON_ENCODER_PRECESS_PRIORITY */
    m_config_common_default << QVariant(false); /* eCONFIG_COMMON_START_JOB_IMMEDIATELY */
    m_config_common_default << QVariant(false); /* eCONFIG_COMMON_ADD_JOB_IMMEDIATELY */
    m_config_common_default << QVariant(eINDEX_0); /*eCONFIG_COMMON_SCRIPT_PLAYER_PLAYER*/
    m_config_common_default << QVariant(eINDEX_24); /*eCONFIG_COMMON_PREVIEW_FPS_LIMIT_CUSTOM*/
    m_config_common_default << QVariant(eINDEX_2); /*eCONFIG_COMMON_PREVIEW_ZOOM_MODE*/
    m_config_common_default << QVariant(eINDEX_1); /*eCONFIG_COMMON_PREVIEW_SCALE_MODE*/
    m_config_common_default << QVariant(eINDEX_1); /*eCONFIG_COMMON_PREVIEW_TIMELINE_DISPLAY_MODE*/
    m_config_common_default << QVariant(NULLSTR); /*eCONFIG_COMMON_PREVIEW_LAST_SNAPSHOT_EXT*/
    m_config_common_default << QVariant(NULLSTR); /*eCONFIG_COMMON_ENCODING_AUDIO_CURRENT_PRESETS*/
}

void Config::initCommonConfig(void)
{
    initCommonConfigDefault();
    for(int i = eINDEX_0; i < eCONFIG_COMMON_MAX; i++)
    {
        m_config_common.insert(static_cast<ECONFIG_COMMON>(i), value(c_config_common_key[static_cast<ECONFIG_COMMON>(i)], m_config_common_default.at(static_cast<ECONFIG_COMMON>(i))));
    }
    for(QMap<ECONFIG_COMMON, QVariant>::iterator i = m_config_common.begin(); i != m_config_common.end(); i++)
    {
        qDebug() << QString("%1:%2=").arg(i.key()).arg(c_config_common_key[i.key()]) << i.value();
    }
}

void Config::initEncodeConfig(void)
{
    QStringList keys = groupKeys(ENCODING_PRESETS_GROUP);
    for(QString key : keys)
    {
        QString jsonStr = valueInGroup(ENCODING_PRESETS_GROUP, key, QT_EMPTY).toString();
        QJsonObject json = qvs::getJsonFromString(jsonStr);
        QMap<JobCreator::EJOB_CONFIG, QVariant> config = jsonToConfig(json);

        m_config_encode_templates.insert(key, config);
    }

    qDebug() << QString("[%1]").arg(ENCODING_PRESETS_GROUP);
    for(QString key : keys)
    {
        qDebug() << QString("%1=").arg(key) << valueInGroup(ENCODING_PRESETS_GROUP, key, QT_EMPTY).toString();
    }
#ifdef QT_DEBUG
    for(QMap<QString, QMap<JobCreator::EJOB_CONFIG, QVariant>>::iterator i = m_config_encode_templates.begin(); i != m_config_encode_templates.end(); i++)
    {
        for(QMap<JobCreator::EJOB_CONFIG, QVariant>::iterator j = i.value().begin(); j != i.value().end(); j++)
        {
            qDebug() << QString("%1=").arg(i.key()) << j.value();
        }
    }
#endif
}

void Config::initEncodeAudioConfig(void)
{
    QStringList keys = groupKeys(ENCODING_AUDIO_PRESETS_GROUP);
    for(QString key : keys)
    {
        QString jsonStr = valueInGroup(ENCODING_AUDIO_PRESETS_GROUP, key, QT_EMPTY).toString();
        QJsonObject json = qvs::getJsonFromString(jsonStr);
        AudioAdvancedConfig config = jsonToAudioConfig(json);

        m_config_audio_encode_templates.insert(key, config);
    }

#ifndef QT_DEBUG
    qDebug() << QString("[%1]").arg(ENCODING_AUDIO_PRESETS_GROUP);
    for(QString key : keys)
    {
        qDebug() << QString("%1=").arg(key) << valueInGroup(ENCODING_AUDIO_PRESETS_GROUP, key, QT_EMPTY).toString();
    }
    for(QMap<QString, AudioAdvancedConfig>::iterator i = m_config_audio_encode_templates.begin(); i != m_config_audio_encode_templates.end(); i++)
    {
        qDebug() << QString("%1=").arg(i.key()) << i.value().toString();
    }
#endif
}

void Config::initInstallerConfig(void)
{
    if(m_isInitConfigInstaller)
    {
        return;
    }
    m_config_installer.insert(eCONFIG_INSTALLER_PFM, valueInGroup(INSTALLER_GROUP, c_config_installer_key[eCONFIG_INSTALLER_PFM], false));
    m_config_installer.insert(eCONFIG_INSTALLER_VS64, valueInGroup(INSTALLER_GROUP, c_config_installer_key[eCONFIG_INSTALLER_VS64], false));
    m_config_installer.insert(eCONFIG_INSTALLER_AVS32, valueInGroup(INSTALLER_GROUP, c_config_installer_key[eCONFIG_INSTALLER_AVS32], false));
    m_config_installer.insert(eCONFIG_INSTALLER_LAV, valueInGroup(INSTALLER_GROUP, c_config_installer_key[eCONFIG_INSTALLER_LAV], false));
    m_config_installer.insert(eCONFIG_INSTALLER_MEDIA, valueInGroup(INSTALLER_GROUP, c_config_installer_key[eCONFIG_INSTALLER_MEDIA], false));
    m_isInitConfigInstaller = true;

    qDebug() << QString("[%1]").arg(INSTALLER_GROUP);
    for(QMap<ECONFIG_INSTALLER, QVariant>::iterator i = m_config_installer.begin(); i != m_config_installer.end(); i++)
    {
        qDebug() << QString("%1:%2=").arg(i.key()).arg(c_config_installer_key[i.key()]) << i.value();
    }
}

void Config::saveConfigAll(void)
{
    QString key;
    QVariant value;

    for(QMap<ECONFIG_FIRST, QVariant>::iterator i = m_config_first.begin(); i != m_config_first.end(); i++)
    {
        key = c_config_first_key[i.key()];
        value = i.value();
        if(key.isEmpty())
        {
            continue;
        }
        setValue(key, value);
    }
    for(QMap<ECONFIG_COMMON, QVariant>::iterator i = m_config_common.begin(); i != m_config_common.end(); i++)
    {
        key = c_config_common_key[i.key()];
        value = i.value();
        if(key.isEmpty())
        {
            continue;
        }
        setValue(key, value);
    }
    for(QMap<QString, QMap<JobCreator::EJOB_CONFIG, QVariant>>::iterator i = m_config_encode_templates.begin(); i != m_config_encode_templates.end(); i++)
    {
        key = i.key();
        value = qvs::getStringFromJson(configToJson(i.value())).simplified();
        setValueInGroup(ENCODING_PRESETS_GROUP, key, value);
    }
    for(QMap<QString, AudioAdvancedConfig>::iterator i = m_config_audio_encode_templates.begin(); i != m_config_audio_encode_templates.end(); i++)
    {
        key = i.key();
        value = qvs::getStringFromJson(audioConfigToJson(i.value())).simplified();
        setValueInGroup(ENCODING_AUDIO_PRESETS_GROUP, key, value);
    }
    for(QMap<ECONFIG_INSTALLER, QVariant>::iterator i = m_config_installer.begin(); i != m_config_installer.end(); i++)
    {
        key = c_config_installer_key[i.key()];
        value = i.value();
        if(key.isEmpty())
        {
            continue;
        }
        setValueInGroup(INSTALLER_GROUP, key, value);
    }
}

QJsonObject Config::configToJson(QMap<JobCreator::EJOB_CONFIG, QVariant> a_config)
{
    QJsonObject json;
    QMap<JobCreator::EJOB_CONFIG, bool> skip_config; /* Config value will be skiped on true. */

    skip_config.insert(JobCreator::eJOB_CONFIG_INPUT, true);     /* Skip input */
    skip_config.insert(JobCreator::eJOB_CONFIG_OUTPUT, true);    /* Skip output */
    skip_config.insert(JobCreator::eJOB_CONFIG_PASS_NUM, true);  /* Skip pass num */

    for(QMap<JobCreator::EJOB_CONFIG, QVariant>::iterator i = a_config.begin(); i != a_config.end(); i++)
    {
        QString key = c_config_key[i.key()];
        QJsonValue value = QJsonValue::fromVariant(i.value());

        if(skip_config.contains(i.key()) || key.isEmpty())
        {
            continue;
        }
        json.insert(key, value);
    }
    return json;
}

QMap<JobCreator::EJOB_CONFIG, QVariant> Config::jsonToConfig(QJsonObject a_json)
{
    QMap<JobCreator::EJOB_CONFIG, QVariant> config;
    QMap<JobCreator::EJOB_CONFIG, bool> skip_config; /* Config value will be skiped on true. */

    skip_config.insert(JobCreator::eJOB_CONFIG_INPUT, true);     /* Skip input */
    skip_config.insert(JobCreator::eJOB_CONFIG_OUTPUT, true);    /* Skip output */
    skip_config.insert(JobCreator::eJOB_CONFIG_PASS_NUM, true);  /* Skip pass num */

    for(int i = eINDEX_0; i < JobCreator::eJOB_CONFIG_MAX; i++)
    {
        JobCreator::EJOB_CONFIG key = static_cast<JobCreator::EJOB_CONFIG>(i);
        QVariant value = a_json[c_config_key[i]].toVariant();

        if(skip_config.contains(key) || value.isNull())
        {
            continue;
        }
        config.insert(key, value);
    }
    return config;
}

QJsonObject Config::audioConfigToJson(AudioAdvancedConfig a_config)
{
    QJsonObject json;

    for(int i = eINDEX_0; i < c_list_config_encode_audio.length(); i++)
    {
        QString key = c_list_config_encode_audio.at(i).second;
        QJsonValue value;

        if(key.isEmpty())
        {
            continue;
        }
        if(key == c_list_config_encode_audio[AudioAdvancedConfig::eCONFIG_ADVANCED].second)
        {
            value = QJsonValue::fromVariant(a_config.isEnable());
        }
        else if(key == c_list_config_encode_audio[AudioAdvancedConfig::eCONFIG_TYPE].second)
        {
            value = QJsonValue::fromVariant(a_config.type);
        }
        else if(key == c_list_config_encode_audio[AudioAdvancedConfig::eCONFIG_MODE].second)
        {
            value = QJsonValue::fromVariant(a_config.mode);
        }
        else if(key == c_list_config_encode_audio[AudioAdvancedConfig::eCONFIG_PROFILE].second)
        {
            value = QJsonValue::fromVariant(a_config.profile);
        }
        else if(key == c_list_config_encode_audio[AudioAdvancedConfig::eCONFIG_VALUE].second)
        {
            value = QJsonValue::fromVariant(a_config.value);
        }
        else if(key == c_list_config_encode_audio[AudioAdvancedConfig::eCONFIG_VALUE2].second)
        {
            value = QJsonValue::fromVariant(a_config.value2);
        }
        json.insert(key, value);
    }
    return json;
}


AudioAdvancedConfig Config::jsonToAudioConfig(QJsonObject a_json)
{
    AudioAdvancedConfig config;

    for(int i = eINDEX_0; i < c_list_config_encode_audio.length(); i++)
    {
        AudioAdvancedConfig::ECONFIG key = c_list_config_encode_audio.at(i).first;
        QVariant value = a_json[c_list_config_encode_audio.at(i).second].toVariant();

        switch(key)
        {
        case AudioAdvancedConfig::eCONFIG_ADVANCED:
            config.setEnable(static_cast<uint>(value.toBool()));
            break;
        case AudioAdvancedConfig::eCONFIG_TYPE:
            config.type = static_cast<uint>(value.toInt());
            break;
        case AudioAdvancedConfig::eCONFIG_MODE:
            config.mode = static_cast<uint>(value.toInt());
            break;
        case AudioAdvancedConfig::eCONFIG_PROFILE:
            config.profile = static_cast<uint>(value.toInt());
            break;
        case AudioAdvancedConfig::eCONFIG_VALUE:
            config.value = value;
            break;
        case AudioAdvancedConfig::eCONFIG_VALUE2:
            config.value2 = value;
            break;
        default:
            break;
        }
    }
    return config;
}

void Config::setLaunchMode(void)
{
    qDebug() << "Arguments:" <<m_args;

    if(m_args.length() == eINDEX_1)
    {
        m_launchMode = eLAUNCH_MODE_NORMAL;
    }
    else if(m_args.length() == eINDEX_2)
    {
        if(m_args[eINDEX_1] == "-h" || m_args[eINDEX_1] == "--help")
        {
            m_launchMode = eLAUNCH_MODE_SHOW_HELP;
        }
        else if(qvs::isFile(m_args[eINDEX_1]))
        {
            m_launchMode = eLAUNCH_MODE_NORMAL_ADD_JOB;
            setConfig(eCONFIG_FIRST_CLI_FILENAME, m_args[eINDEX_1]);
        }
        else
        {
            m_launchMode = eLAUNCH_MODE_SHOW_HELP;
        }
    }
    else if(m_args.length() == eINDEX_3)
    {
        if(qvs::isFile(m_args[eINDEX_1]))
        {
            if(m_args[eINDEX_2] == "-cp" || m_args[eINDEX_2] == "--copypath")
            {
                m_launchMode = eLAUNCH_MODE_COPY_PATH_DOS;
            }
            else if(m_args[eINDEX_2] == "-cup" || m_args[eINDEX_2] == "--copyunixpath")
            {
                m_launchMode = eLAUNCH_MODE_COPY_PATH_UNIX;
            }
            else if(m_args[eINDEX_2] == "-cpp" || m_args[eINDEX_2] == "--copypypath")
            {
                m_launchMode = eLAUNCH_MODE_COPY_PATH_PYTHON;
            }
            else if(m_args[eINDEX_2] == "-info" || m_args[eINDEX_2] == "--mediainfo")
            {
                m_launchMode = eLAUNCH_MODE_MEDIAINFO;
            }
            else
            {
                m_launchMode = eLAUNCH_MODE_EXIT;
            }
            setConfig(eCONFIG_FIRST_CLI_FILENAME, m_args[eINDEX_1]);
        }
        else
        {
            m_launchMode = eLAUNCH_MODE_SHOW_HELP;
        }
    }
    else
    {
        m_launchMode = eLAUNCH_MODE_NORMAL;
    }
}

Config::ELAUNCH_MODE Config::getLaunchMode(void)
{
    return m_launchMode;
}

void Config::setMainWindow(MainWindow *a_pMainUi)
{
    mainUi = a_pMainUi;
}

bool Config::deleteConfigFile(void)
{
    return QFile::remove(m_settingsFilePath);
}

void Config::getConfigFile(void)
{
    QString applicationDir = QCoreApplication::applicationDirPath();

    if(getPortableMode())
    {
        m_settingsFilePath = applicationDir + SETTINGS_FILE_NAME;
    }
    else
    {
        m_settingsFilePath = QStandardPaths::writableLocation(QStandardPaths::GenericConfigLocation) + SETTINGS_FILE_NAME;
    }
    m_settingsFilePath = QDir::toNativeSeparators(m_settingsFilePath);

    qDebug() << "Config file:" << m_settingsFilePath;
}

bool Config::getPortableMode(void)
{
    QString applicationDir = QCoreApplication::applicationDirPath();
    QString settingsFilePath = applicationDir + SETTINGS_FILE_NAME;
    QFileInfo settingsFileInfo(settingsFilePath);
    bool portableMode = (settingsFileInfo.exists() && settingsFileInfo.isWritable());
    return portableMode;
}

QVariant Config::valueInGroup(const QString & a_group, const QString & a_key, const QVariant & a_defaultValue) const
{
    QSettings settings(m_settingsFilePath, QSettings::IniFormat);
    settings.beginGroup(a_group);
    return settings.value(a_key, a_defaultValue);
}

bool Config::setValueInGroup(const QString & a_group, const QString & a_key, const QVariant & a_value)
{
    QSettings settings(m_settingsFilePath, QSettings::IniFormat);
    settings.beginGroup(a_group);
    settings.setValue(a_key, a_value);
    settings.sync();
    bool success = (QSettings::NoError == settings.status());
    return success;
}

bool Config::deleteValueInGroup(const QString & a_group, const QString & a_key)
{
    QSettings settings(m_settingsFilePath, QSettings::IniFormat);
    settings.beginGroup(a_group);
    settings.remove(a_key);
    settings.sync();
    bool success = (QSettings::NoError == settings.status());
    return success;
}

QVariant Config::value(const QString & a_key, const QVariant & a_defaultValue) const
{
    return valueInGroup(COMMON_GROUP, a_key, a_defaultValue);
}

bool Config::setValue(const QString & a_key, const QVariant & a_value)
{
    return setValueInGroup(COMMON_GROUP, a_key, a_value);
}

bool Config::isStartSplashScreen(void)
{
    return m_config_first[eCONFIG_FIRST_SPLASH_SCREEN].toBool();
}

bool Config::isCheckGuardLocker(void)
{
    return m_config_first[eCONFIG_FIRST_GUARD_LOCKER].toBool();
}

bool Config::isShowMainWindow(void)
{
    return isCheckGuardLocker();
}

void Config::setConfigEncodeTemplate(QString a_key, QMap<JobCreator::EJOB_CONFIG, QVariant> a_config)
{
    removeConfigEncodeTemplate(a_key);
    m_config_encode_templates.insert(a_key, a_config);
}

QMap<JobCreator::EJOB_CONFIG, QVariant> Config::getConfigEncodeTemplate(QString a_key)
{
    QMap<JobCreator::EJOB_CONFIG, QVariant> config;

    if(m_config_encode_templates.contains(a_key))
    {
        config = m_config_encode_templates[a_key];
    }
    return config;
}

void Config::removeConfigEncodeTemplate(QString a_key)
{
    if(m_config_encode_templates.contains(a_key))
    {
        m_config_encode_templates.remove(a_key);
        deleteValueInGroup(ENCODING_PRESETS_GROUP, a_key);
    }
}

bool Config::containsConfigEncodeTemplate(QString a_key)
{
    return m_config_encode_templates.contains(a_key);
}

void Config::setConfigAudioEncodeTemplate(QString a_key, AudioAdvancedConfig a_config)
{
    removeConfigAudioEncodeTemplate(a_key);
    m_config_audio_encode_templates.insert(a_key, a_config);
}

AudioAdvancedConfig Config::getConfigAudioEncodeTemplate(QString a_key)
{
    AudioAdvancedConfig config;

    if(m_config_audio_encode_templates.contains(a_key))
    {
        config = m_config_audio_encode_templates[a_key];
    }
    return config;
}

void Config::removeConfigAudioEncodeTemplate(QString a_key)
{
    if(m_config_audio_encode_templates.contains(a_key))
    {
        m_config_audio_encode_templates.remove(a_key);
        deleteValueInGroup(ENCODING_AUDIO_PRESETS_GROUP, a_key);
    }
}

bool Config::containsConfigAudioEncodeTemplate(QString a_key)
{
    return m_config_audio_encode_templates.contains(a_key);
}

QVariant Config::getConfig(ECONFIG_FIRST a_key)
{
    return m_config_first[a_key];
}

QVariant Config::getConfig(ECONFIG_COMMON a_key)
{
    return m_config_common[a_key];
}

QVariant Config::getConfig(ECONFIG_INSTALLER a_key)
{
    return m_config_installer[a_key];
}

void Config::setConfig(ECONFIG_FIRST a_key, QVariant a_value)
{
    if(m_config_first.contains(a_key))
    {
        m_config_first.remove(a_key);
    }
    m_config_first.insert(a_key, a_value);
}

void Config::setConfig(ECONFIG_COMMON a_key, QVariant a_value)
{
    if(m_config_common.contains(a_key))
    {
        m_config_common.remove(a_key);
    }
    m_config_common.insert(a_key, a_value);
}

void Config::setConfig(ECONFIG_INSTALLER a_key, QVariant a_value)
{
    if(m_config_installer.contains(a_key))
    {
        m_config_installer.remove(a_key);
    }
    m_config_installer.insert(a_key, a_value);
}

QStringList Config::groupKeys(const QString & a_group)
{
    QSettings settings(m_settingsFilePath, QSettings::IniFormat);
    settings.beginGroup(a_group);
    return settings.childKeys();
}

void Config::reset(ECONFIG_TYPE a_config_type)
{
    switch(a_config_type)
    {
    case eCONFIG_TYPE_FIRST:
        for(int i = eINDEX_0; i < m_config_first_default.length(); i++)
        {
            if(static_cast<ECONFIG_FIRST>(i) == eCONFIG_FIRST_FIRST_LAUNCH)
            {
                /*Not reset first launch flag.*/
                continue;
            }
            setConfig(static_cast<ECONFIG_FIRST>(i), m_config_first_default.at(i));
        }
        break;
    case eCONFIG_TYPE_COMMON:
        for(int i = eINDEX_0; i < m_config_common_default.length(); i++)
        {
            setConfig(static_cast<ECONFIG_COMMON>(i), m_config_common_default.at(i));
        }
        Common::getInstance()->loadCommonConfig();
        break;
    case eCONFIG_TYPE_ENCODE:
        do{
            QStringList list = groupKeys(ENCODING_PRESETS_GROUP);
            for(int i = eINDEX_0; i < list.length(); i++)
            {
                deleteValueInGroup(ENCODING_PRESETS_GROUP, list.at(i));
            }
            m_config_encode_templates.clear();
        }while(false);
        break;
    case eCONFIG_TYPE_ENCODE_AUDIO:
        do{
            QStringList list = groupKeys(ENCODING_AUDIO_PRESETS_GROUP);
            for(int i = eINDEX_0; i < list.length(); i++)
            {
                deleteValueInGroup(ENCODING_AUDIO_PRESETS_GROUP, list.at(i));
            }
            m_config_encode_templates.clear();
        }while(false);
        break;
    case eCONFIG_TYPE_MAX:
        for(int i = eINDEX_0; i < eCONFIG_TYPE_MAX; i++)
        {
            reset(static_cast<ECONFIG_TYPE>(i));
        }
        break;
    }
}

QVariant Config::pyValue(const QString & a_key, const QVariant & a_defaultValue) const
{
    QSettings settings(SETTINGS_PY_FILE_NAME, QSettings::IniFormat);
    settings.beginGroup(PYTHON_GROUP);
    return settings.value(a_key, a_defaultValue);
}

bool Config::pySetValue(const QString & a_key, const QVariant & a_value)
{
    QSettings settings(SETTINGS_PY_FILE_NAME, QSettings::IniFormat);
    settings.beginGroup(PYTHON_GROUP);
    settings.setValue(a_key, a_value);
    settings.sync();
    bool success = (QSettings::NoError == settings.status());
    return success;
}

QString Config::getEnv(QString value)
{
    for(QString env : QProcess::systemEnvironment())
    {
        if(env.startsWith(QString(value) + QString(QT_EQUAL)))
        {
            return env.mid(QString(value).length() + eINDEX_1);
        }
    }
    return QT_EMPTY;
}

QString Config::getReg(QString key, QString hkey)
{
    QSettings settings(hkey, QSettings::NativeFormat);
    return settings.value(key).toString();
}
