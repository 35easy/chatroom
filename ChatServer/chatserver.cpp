#include "chatserver.h"

ChatServer::ChatServer(QObject *parent):
    QTcpServer(parent)
{

}

void ChatServer::broadcast(const QJsonObject message, ServerWoker *exclude)
{
    for(ServerWoker *worker :m_clients){
        worker->sendJson(message);
    }
}

void ChatServer::incomingConnection(qintptr socketDescriptor)
{
    ServerWoker *worker = new ServerWoker(this);


    if(!worker->setSoketDescriptor(socketDescriptor)){
        worker->deleteLater();
        return;
    }

    connect(worker,&ServerWoker::logMessage,this,&ChatServer::logMessage);
    connect(worker,&ServerWoker::jsonReceived,this,&ChatServer::jsonReceived);

    m_clients.append(worker);
    emit logMessage("新的用户连接上了");
}

void ChatServer::stopServer()
{
    close();
}

void ChatServer::jsonReceived(ServerWoker *sender, const QJsonObject &docObj)
{
    const QJsonValue typeVal = docObj.value("type");
    if(typeVal.isNull()||!typeVal.isString())
        return;
    if(typeVal.toString().compare("message", Qt::CaseInsensitive) == 0){
        const QJsonValue textVal = docObj.value("text");
        if(textVal.isNull()||!textVal.isString())
            return;
        const QString text = textVal.toString().trimmed();
        if(text.isEmpty())
            return;
        QJsonObject message;
        message["type"]="message";
        message["text"]=text;
        message["sender"]=sender->userName();
        broadcast(message,sender);


    }else if(typeVal.toString().compare("login",Qt::CaseInsensitive)==0){
        const QJsonValue usernameVal=docObj.value("text");
        if(usernameVal.isNull()||!usernameVal.isString())
            return;

        sender->setUserName(usernameVal.toString());
        QJsonObject connectedMessage;
        connectedMessage["type"]="newuser";
        connectedMessage["text"]=usernameVal.toString();
        broadcast(connectedMessage,sender);
    }
}
