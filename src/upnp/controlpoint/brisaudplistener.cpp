/*
 * Universidade Federal de Campina Grande
 * Centro de Engenharia Elétrica e Informática
 * Laboratório de Sistemas Embarcados e Computação Pervasiva
 * BRisa Project / BRisa-Qt - http://brisa.garage.maemo.org
 * Filename: brisaudplistener.cpp
 * Created:
 * Description: This File implements the BrisaUdpListener class.
 * Authors: Danilo Araujo de Freitas <dsurviver@gmail.com> @since 2010
 *
 *
 * Copyright (C) <2009> <Embbeded Systems and Pervasive Computing Laboratory>
 *
 * BRisa-Qt is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation, either version 3 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 */


#include "brisaudplistener.h"

#ifdef Q_OS_UNIX
#include <arpa/inet.h>
#include <netinet/in.h>
#else
#include <winsock2.h>
#include <ws2tcpip.h>
#endif
#include <cstring>
#define MAX_LEN  1024   /* maximum receive string size */

using namespace Brisa;

BrisaUdpListener::BrisaUdpListener(QString address, quint32 port,
                                   QString objectName, QObject *parent) :
        QUdpSocket(parent)
{
    this->port = port;
    this->objectName = objectName;
    this->address = address;
}

BrisaUdpListener::~BrisaUdpListener()
{
}

void BrisaUdpListener::start()
{

#ifdef Q_WS_X11
    if (!this->bind(QHostAddress(this->address), this->port, QUdpSocket::ShareAddress |
                    QUdpSocket::ReuseAddressHint)) {
            qWarning() << this->objectName << ": failure to bind interface.";
    }
#endif

    int fd;
    fd = this->socketDescriptor();
    struct ip_mreq mreq;
    memset(&mreq, 0, sizeof(ip_mreq));
    mreq.imr_multiaddr.s_addr = inet_addr(this->address.toUtf8());
    bool boolean = true;

    QString ip = getValidIP();
    if (ip == LOCAL_HOST)
    {
        mreq.imr_interface.s_addr = inet_addr(ip.toUtf8());
    }
    else
    {
        mreq.imr_interface.s_addr = htons(INADDR_ANY);
    }
#ifndef Q_WS_X11
    qWarning() << "windows procedure is running...";
       WSADATA wsaData;              /* Windows socket DLL structure */
       struct sockaddr_in mc_addr;   /* socket address structure */

           /* Load Winsock 2.0 DLL */
       if (WSAStartup(MAKEWORD(2, 0), &wsaData) != 0) {
             fprintf(stderr, "WSAStartup() failed");
             exit(1);
       }

       /* create socket to join multicast group on */
       if ((fd = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0) {
         qWarning() << "socket() failed";
         exit(1);
       }

       /* set reuse port to on to allow multiple binds per host */
       if ((setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, (char*)&boolean,
            sizeof(boolean))) < 0) {
         qWarning() << "setsockopt() failed";
             exit(1);
       }

       /* construct a multicast address structure */
       memset(&mc_addr, 0, sizeof(mc_addr));
       mc_addr.sin_family      = AF_INET;
       mc_addr.sin_addr.s_addr = htonl(INADDR_ANY);
       mc_addr.sin_port        = htons(this->port);

       /* bind to multicast address to socket */
       if ((::bind(fd, (struct sockaddr *) &mc_addr,
            sizeof(mc_addr))) < 0) {
         qWarning() << "bind() failed";
         exit(1);
       }

         /* construct an IGMP join request structure */
       mreq.imr_multiaddr.s_addr = inet_addr(address.toAscii());
       mreq.imr_interface.s_addr = htonl(INADDR_ANY);


       /* send an ADD MEMBERSHIP message via setsockopt */
       if ((setsockopt(fd, IPPROTO_IP, IP_ADD_MEMBERSHIP,
            (char*) &mreq, sizeof(mreq))) < 0) {
           qWarning() << this->objectName << ": could not join MULTICAST group.";

         exit(1);
       }
       this->setSocketDescriptor(fd,QUdpSocket::BoundState,QUdpSocket::ReadOnly);
#endif


#ifdef Q_WS_X11
    if (setsockopt(fd, IPPROTO_IP, IP_ADD_MEMBERSHIP,
                   &mreq, sizeof(mreq)) < 0 ||
        setsockopt(fd, IPPROTO_IP, IP_MULTICAST_LOOP,
                   &boolean, sizeof (boolean)) < 0)
    {
          qWarning() << this->objectName << ": could not join MULTICAST group.";
    }
#endif
}






