#include "tcpserver.h"

TcpServer::TcpServer(QObject *parent) :
    QTcpServer(parent)
{
}

void TcpServer::incomingConnection(int handle)
{
    emit newConnection(handle);
}
