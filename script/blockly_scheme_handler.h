#ifndef BLOCKLY_SCHEME_HANDLER_H
#define BLOCKLY_SCHEME_HANDLER_H

#include <QObject>
#include <QDebug>
#include <QDir>
#include <QByteArray>
#include <QBuffer>
#include <QUrl>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QWebEngineUrlRequestJob>
#include <QWebEngineUrlSchemeHandler>
#include <QWebEngineUrlScheme>
#include <QWebEngineProfile>

#define BLOCKLY_SCHEME_NAME "blockly"
#define BLOCKLY_HOST "localhost"
#define BLOCKLY_PORT 10087
#define BLOCKLY_HOSTANDPORT QString(BLOCKLY_HOST) + ":" + QString::number(BLOCKLY_PORT)
#define BLOCKLY_URL_STR QString(BLOCKLY_SCHEME_NAME) + ":///"
#define BLOCKLY_URL QUrl(BLOCKLY_URL_STR)
#define BLOCKLY_HOMEPAGE "/qvs/index.html"
#define BLOCKLY_ARCHIVE "tools/ScriptBlockly/script_blockly.blockly"
#define BLOCKLY_EXTRACT "tools/ScriptBlockly"

#define BLOCKLY_REPLY false

class BlocklySchemeHandler : public QWebEngineUrlSchemeHandler
{
    Q_OBJECT
public:
    BlocklySchemeHandler(QObject *parent = nullptr);
    ~BlocklySchemeHandler() override;
    void requestStarted(QWebEngineUrlRequestJob *a_requestJob) override;

public slots:

private:
    void setupBlocklyResources();
    void registerUrlScheme();
    QByteArray *getDataByteArray(const QString &a_url);
    QString getMineType(const QString &a_ext);

private:
    QMap<QString, QByteArray *> mMap;
};

#endif // BLOCKLY_SCHEME_HANDLER_H
