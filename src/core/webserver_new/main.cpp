/*
  Copyright (C) 2010 Vinícius dos Santos Oliveira

  This program is free software; you can redistribute it and/or
  modify it under the terms of the GNU General Public License
  version 2 as published by the Free Software Foundation.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
*/

#include <QtCore/QCoreApplication>
#include "webserver.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    WebServer *server = new WebServer(QHostAddress::LocalHost, 8080);
    server->publishFile("/index", WebResource("index.html", "text/plain; charset=UTF-8"));
    server->publishFile("/index.pdf", WebResource("vai.gif", "image/png"));
    server->start();

    return a.exec();
}
