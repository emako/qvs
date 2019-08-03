#include "app_instance_local_connect.h"

AppInstanceLocalConnect::AppInstanceLocalConnect(const QString &a_name, QObject *parent)
    : QObject(parent)
    , m_pServer(nullptr)
    , m_pClient(nullptr)
{
    if(!a_name.isEmpty())
    {
        m_pClient = new QLocalSocket(this);
        m_pClient->connectToServer(a_name);

        if (m_pClient->waitForConnected(eINDEX_100))
        {
            /* Another instance is probably already running. */
            m_pClient->write(CMD_SHOW);
            m_pClient->waitForBytesWritten();
            m_pClient->disconnectFromServer();
            m_pClient->close();
        }
        else
        {
            m_pServer = new QLocalServer(this);
            if(m_pServer->listen(a_name))
            {
                connect(m_pServer, SIGNAL(newConnection()), this, SLOT(newConnection()));
            }
            else
            {
                qWarning() << "unkonw error in m_pServer->listen";
            }
        }
    }
}

AppInstanceLocalConnect::~AppInstanceLocalConnect()
{
    if (m_pServer != nullptr)
        delete m_pServer;
    if (m_pClient != nullptr)
        delete m_pClient;
}

bool AppInstanceLocalConnect::isLocked()
{
    return (m_pServer != nullptr && m_pServer->isListening());
}

void AppInstanceLocalConnect::newConnection(void)
{
    QLocalSocket *newsocket = m_pServer->nextPendingConnection();

    connect(newsocket, SIGNAL(readyRead()), this, SLOT(readyRead()));
}

void AppInstanceLocalConnect::readyRead(void)
{
    QLocalSocket *at_pClient = static_cast<QLocalSocket *>(sender());

    if (at_pClient == nullptr)
    {
        return;
    }

    QTextStream in(at_pClient);
    emit commandRecived(in.readAll());
}

