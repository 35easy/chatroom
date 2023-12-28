#ifndef CHATSERVER_H
#define CHATSERVER_H

#include <QObject>
#include <QTcpServer>
#include <serverwoker.h>
#include <QJsonValue>
class ChatServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit ChatServer(QObject *parent = nullptr);
    void broadcast(const QJsonObject message,ServerWoker *exclude);
protected:
    void incomingConnection(qintptr handle) override;

signals:
    void logMessage(const QString &msg);


public slots:
    void stopServer();
    void jsonReceived(ServerWoker *sender,const QJsonObject &docObj);


private:
    QVector<ServerWoker*>m_clients;

};

#endif // CHATSERVER_H
