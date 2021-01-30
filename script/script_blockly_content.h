#ifndef SCRIPT_BLOCKLY_CONTENT_H
#define SCRIPT_BLOCKLY_CONTENT_H

#include <QObject>
#include <QDebug>
#include <QWidget>
#include <QMessageBox>
#include <QFileDialog>
#include <QUrl>

#include "../com/common.h"
#include "blockly_scheme_handler.h"

class ScriptBlocklyContent : public QObject
{
    Q_OBJECT

public:
    ScriptBlocklyContent(QObject *parent = nullptr) : QObject(parent)
    {
    }

signals:
    void dataChanged(const QString &a_jsonData);
    void codeUpdated(const QString &a_code);
    void saveFilenameUpdated(const QString &a_filename);

public slots:
    void debug(const QString &a_message)
    {
        qDebug() << "blockly debug: " << a_message;
    }

    void updateCode(const QString &a_code)
    {
        emit codeUpdated(a_code);
    }

    void getOpenFileName(const QString &a_message)
    {
        QJsonObject jsonRequested = qvs::getJsonFromString(a_message);
        QJsonObject jsonRespond;

        QString caption = QString();
        QString filter = QString();
        QString type = QString();

        if (jsonRequested.contains("caption"))
        {
            caption = jsonRequested["caption"].toString();
        }
        if (jsonRequested.contains("filter"))
        {
            filter = jsonRequested["filter"].toString();
        }
        if (jsonRequested.contains("type"))
        {
            type = jsonRequested["type"].toString();
        }

        jsonRespond["cmd"] = "getOpenFileName";
        jsonRespond["filename"] = QFileDialog::getOpenFileName(nullptr, caption, QString(), filter);
        emit dataChanged(qvs::getStringFromJson(jsonRespond).trimmed().replace("\n", ""));

        if (type == "libavsmashsource"
         || type == "lwlibavsource"
         || type == "ffmpegsource"
         || type == "dgsourcenv"
         || type == "dgsource"
         || type == "d2vsource"
         || type == "directshowsource"
         || type == "imagesource"
         || type == "import")
        {
            emit saveFilenameUpdated(jsonRespond["filename"].toString());
        }
    }

    void openUrl(const QString &a_url)
    {
        if (a_url.startsWith("file:///"))
        {
            QString url = a_url;
            QString homePageRoot = QFileInfo(QDir::currentPath() + "/" + BLOCKLY_EXTRACT + BLOCKLY_HOMEPAGE).path();
            url.replace("file:///", QString("file:///%1/").arg(homePageRoot));

            Common::getInstance()->openUrl(url);
            return;
        }
        Common::getInstance()->openUrl(a_url);
    }
};

#endif // SCRIPT_BLOCKLY_CONTENT_H
