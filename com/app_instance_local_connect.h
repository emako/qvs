#ifndef APP_INSTANCE_LOCAL_CONNECT_H
#define APP_INSTANCE_LOCAL_CONNECT_H

#include <QObject>
#include <QLocalServer>
#include <QLocalSocket>

#include "common.h"

#define CMD_CHAR_TO_BYTES(_X) QString(QChar(_X)).toUtf8()
#define CMD_COMPARE(_STR, _BYTES) (QString(_STR).toUtf8() == _BYTES)
#define CMD_SHOW CMD_CHAR_TO_BYTES(0x30)

class AppInstanceLocalConnect : public QObject
{
    Q_OBJECT
public:
    explicit AppInstanceLocalConnect(const QString &a_name, QObject *parent = nullptr);
    virtual ~AppInstanceLocalConnect();
    bool isLocked();

signals:
    void commandRecived(const QString &a_cmd);

public slots:
    void newConnection(void);
    void readyRead(void);

private:
    QLocalServer *m_pServer;
    QLocalSocket *m_pClient;
};

#endif // APP_INSTANCE_LOCAL_CONNECT_H
