 #ifndef SERVERWOKER_H
#define SERVERWOKER_H

#include <QObject>
#include <QTcpSocket>
#include <QDataStream>
#include <QJsonObject>
#include <QJsonDocument>
#include <QDebug>
class ServerWoker : public QObject
{
    Q_OBJECT
public:
    explicit ServerWoker(QObject *parent = nullptr);
    virtual bool setSoketDescriptor(qintptr socketDescriptor);
    QString userName();
    void setUserName(QString name);
;

signals:
    void logMessage(const QString &msg);
    void jsonReceived(ServerWoker *sender,const QJsonObject &docObj);
private:
    QDataStream *m_socketStream;
    QTcpSocket *m_serverSocket;
    QString m_userName;
public slots:
    void onReadyRead();
    void sendMessage(const QString &text,const QString &type = "message");
    void sendJson(const QJsonObject &json);
};

#endif // SERVERWOKER_H
