#include "chatserver.h"

ChatServer::ChatServer(QWidget *parent)
//    :QTcpServer(parent)
{

}

void ChatServer::incomingConnection(qintptr handle)
{
    ServerWoker *worker = new ServerWoker(this);
    if(!worker->setSoketDescriptor(socketDescriptor())){
        worker->deleteLater();
        return;
    }

    m_clients.append(worker);
    emit logMessage("新的用户连接上了");
}

void ChatServer::stopServer()
{
    close();
}
