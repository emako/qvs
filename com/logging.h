#ifndef LOGGING_H
#define LOGGING_H

#include "common.h"
#include "log4qt/propertyconfigurator.h"
#include "log4qt/logger.h"

#include <QObject>
#include <QDebug>
#include <QDir>

#define DEFAULT_LOG_PROP_FILENAME "/log4j.properties"
#define DEFAULT_LOG_PROP_PATH_RESOURCE QString(":/strings/log4j") + QString(DEFAULT_LOG_PROP_FILENAME)
#define DEFAULT_LOG_PROP_PATH_CURRENT QDir::currentPath() + QString(DEFAULT_LOG_PROP_FILENAME)
#define DEFAULT_LOG_FILENAME "logging.html" /* Must synchronize with define=DEFAULT_LOG_PROP_PATH_RESOURCE */

using namespace Log4Qt;

class Logging : public QObject
{
    Q_OBJECT
public:
    explicit Logging(QObject *parent = nullptr);

    void init(void);

    Logger &log(const QString &a_rName = QLatin1String("logger"));

    bool configure(const QString &a_configFilename);

    QString history(void);

    bool remove(void);
};

#endif // LOGGING_H
