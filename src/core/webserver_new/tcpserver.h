#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QTcpServer>

class TcpServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit TcpServer(QObject *parent = 0);

signals:
    void newConnection(int socketDescriptor);

protected:
    void incomingConnection(int handle);

};

#endif // TCPSERVER_H
