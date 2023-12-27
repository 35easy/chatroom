#include "serverwoker.h"

ServerWoker::ServerWoker(QObject *parent) : QObject(parent)
{
    m_serverSocket = new QTcpSocket(this);
}
//?????????????????
bool ServerWoker::setSoketDescriptor(qintptr socketDescriptor)
{
    return m_serverSocket->setSocketDescriptor(socketDescriptor);
}

void ServerWoker::onReadyRead()
{
   QByteArray jsonData;
   QDataStream socketStream(m_serverSocket);
   socketStream.setVersion(QDataStream::Qt_5_14);

    for(;;){
        socketStream.startTransaction();
        socketStream>>jsonData;
        if(socketStream.commitTransaction()){
            emit logMessage(QString::fromUtf8(jsonData));
            sendMessage("I recieved message");
        }
        else{
            break;
        }
    }
}

void ServerWoker::sendMessage(const QString &text, const QString &type)
{
    if(m_serverSocket->state()!=QAbstractSocket::ConnectedState)
        return;

    if(!text.isEmpty()){
        //
        QDataStream serverStream(m_serverSocket);
        serverStream.setVersion(QDataStream::Qt_5_14);

        QJsonObject message;
        message["type"]=type;
        message["text"]=text;

        serverStream << QJsonDocument(message).toJson();

    }
}


