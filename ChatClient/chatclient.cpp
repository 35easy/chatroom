#include "chatclient.h"

ChatClient::ChatClient(QObject *parent) : QObject(parent)
{
    m_clientSocket = new QTcpSocket(this);
    connect(m_clientSocket,&QTcpSocket::connected,this,&ChatClient::connected);
    connect(m_clientSocket,&QTcpSocket::readyRead,this,&ChatClient::onReadyRead);

}

void ChatClient::onReadyRead()
{
    QByteArray jsonData;
    QDataStream socketStream(m_clientSocket); // 创建一个 QDataStream 对象，用于从 m_clientSocket 读取数据。
    socketStream.setVersion(QDataStream::Qt_5_14);

     for(;;){ // 无限循环，用于持续读取数据。
         socketStream.startTransaction();// 在数据流上开始一个事务。
         socketStream>>jsonData;// 从套接字读取 JSON 数据到 QByteArray。
         if(socketStream.commitTransaction()){//该函数用来确认事务是否成功
//             emit messageReceived(QString::fromUtf8(jsonData));// 发射一个信号，带有以 UTF-8 格式接收到的消息。

 //          格式化
             QJsonParseError parseError;
             const QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData,&parseError);
             if(parseError.error == QJsonParseError::NoError){
                 if(jsonDoc.isObject()){
//                     emit logMessage(QJsonDocument(jsonDoc).toJson(QJsonDocument::Compact));
                     emit jsonReceived(jsonDoc.object());

                 }
             }

         }
         else{
             break;
         }
     }
}

void ChatClient::sendMessage(const QString &text, const QString &type)
{
    if(m_clientSocket->state()!=QAbstractSocket::ConnectedState)
        return;

    if(!text.isEmpty()){
        //
        QDataStream serverStream(m_clientSocket);
        serverStream.setVersion(QDataStream::Qt_5_14);
        QJsonObject message;
        message["type"]=type;
        message["text"]=text;  
        serverStream << QJsonDocument(message).toJson();
        qDebug()<<"sendMessage!";
    }
}

void ChatClient::connectToServer(const QHostAddress &address, quint16 port)
{
    m_clientSocket->connectToHost(address,port);
}

void ChatClient::disconnectFromHost()
{
    m_clientSocket->disconnectFromHost();
}
