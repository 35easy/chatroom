#ifndef CHATSERVER_H
#define CHATSERVER_H

#include <QObject>
#include <QTcpServer>
#include <serverwoker.h>
class ChatServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit ChatServer(QWidget *parent = nullptr);

protected:
    void incomingConnection(qintptr handle) override;

signals:
    void logMessage(const QString &msg);

public slots:
    void stopServer();

private:
    QVector<ServerWoker*>m_clients;

};

#endif // CHATSERVER_H
