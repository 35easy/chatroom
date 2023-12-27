#ifndef SERVERWOKER_H
#define SERVERWOKER_H

#include <QObject>

class ServerWoker : public QObject
{
    Q_OBJECT
public:
    explicit ServerWoker(QObject *parent = nullptr);

signals:

};

#endif // SERVERWOKER_H
