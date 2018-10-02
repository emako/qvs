#include "logging.h"

Logging::Logging(QObject *parent) : QObject(parent)
{
    init();
}

void Logging::init(void)
{
    remove();

    if(configure(DEFAULT_LOG_PROP_PATH_RESOURCE))
    {
        qDebug() << QString("Logging config file: \"%1\"").arg(DEFAULT_LOG_PROP_PATH_RESOURCE);
    }
    else if(configure(DEFAULT_LOG_PROP_PATH_CURRENT))
    {
        qDebug() << QString("Logging config file: \"%1\"").arg(DEFAULT_LOG_PROP_PATH_CURRENT);
    }
    else
    {
        qDebug() << "Logging config error!";
    }
}

Log4Qt::Logger &Logging::log(const QString &a_name)
{
    return *Logger::logger(a_name);
}

bool Logging::configure(const QString &a_configFilename)
{
    return PropertyConfigurator::configure(a_configFilename);
}

QString Logging::history(void)
{
    return qvs::getFileText(DEFAULT_LOG_FILENAME);
}

bool Logging::remove(void)
{
    return QFile(DEFAULT_LOG_FILENAME).remove();
}
