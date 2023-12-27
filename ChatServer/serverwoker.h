#ifndef SERVERWOKER_H
#define SERVERWOKER_H

#include <QObject>
#include <QTcpSocket>
#include <QDataStream>
#include <QJsonObject>
#include <QJsonDocument>
class ServerWoker : public QObject
{
    Q_OBJECT
public:
    explicit ServerWoker(QObject *parent = nullptr);
    virtual bool setSoketDescriptor(qintptr socketDescriptor);
private:
    QTcpSocket *m_serverSocket;

signals:
    void logMessage(const QString &msg);

public slots:
    void onReadyRead();
    void sendMessage(const QString &text,const QString &type = "message");
};

#endif // SERVERWOKER_H
