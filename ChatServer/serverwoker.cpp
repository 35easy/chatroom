#include "serverwoker.h"

ServerWoker::ServerWoker(QObject *parent) : QObject(parent)
{
    m_serverSocket = new QTcpSocket(this);
    connect(m_serverSocket,&QTcpSocket::readyRead,this,&ServerWoker::onReadyRead);

}

bool ServerWoker::setSoketDescriptor(qintptr socketDescriptor)
{
    return m_serverSocket->setSocketDescriptor(socketDescriptor);
}

QString ServerWoker::userName()
{
    return m_userName;
}

void ServerWoker::setUserName(QString name)
{
    m_userName=name;
}

void ServerWoker::onReadyRead()
{
   qDebug()<<"receive!";
   QByteArray jsonData;
   QDataStream socketStream(m_serverSocket);
   socketStream.setVersion(QDataStream::Qt_5_14);

    for(;;){
        socketStream.startTransaction();
        socketStream>>jsonData;
        if(socketStream.commitTransaction()){
            emit logMessage(QString::fromUtf8(jsonData));
            sendMessage("I recieved message");

//            格式化
            QJsonParseError parseError;
            const QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData,&parseError);
            if(parseError.error == QJsonParseError::NoError){
                if(jsonDoc.isObject()){
                    emit logMessage(QJsonDocument(jsonDoc).toJson(QJsonDocument::Compact));
                    emit jsonReceived(this,jsonDoc.object());

                }
            }
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

void ServerWoker::sendJson(const QJsonObject &json)
{
    const QByteArray jsonData = QJsonDocument(json).toJson(QJsonDocument::Compact);
    emit logMessage(QLatin1String("Sending to ")+userName()+QLatin1String(" - ")+
                    QString::fromUtf8(jsonData));
    QDataStream socketStream(m_serverSocket);
    socketStream.setVersion(QDataStream::Qt_5_7);
    socketStream<<jsonData;
}


