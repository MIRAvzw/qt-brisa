/*
 * Universidade Federal de Campina Grande
 * Centro de Engenharia Elétrica e Informática
 * Laboratório de Sistemas Embarcados e Computação Pervasiva
 * BRisa Project / BRisa-Qt - http://brisa.garage.maemo.org
 * Filename: brisaicon.cpp
 * Created:
 * Description: This file implements the BrisaIcon class.
 * Authors: Name <email> @since 2009
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

#ifndef _BRISAICON_H
#define _BRISAICON_H

#include <QObject>
#include <QString>
#include <QIcon>
#include <QNetworkAccessManager>
#include <QUrl>
#include <QNetworkReply>
#include <QDebug>

#include "brisaglobal.h"

namespace Brisa {

class BRISA_UPNP_EXPORT BrisaIcon: public QObject {
Q_OBJECT
public:
    BrisaIcon(QString mimetype = "", QString width = "", QString height = "",
            QString depth = "", QString url = "", QObject *parent = 0);

    typedef enum {
        Mimetype, Width, Height, Depth, Url
    } xmlIconTags;

    void setAttribute(xmlIconTags key, QString v);
    void setIcon(QIcon icon);
    QIcon getIcon();
    void clear();
    QString getAttribute(xmlIconTags key);
    void downloadIcon(QString deviceUrl);

signals:
    void iconDownloadFinished();

public slots:
    void downloadFinished(QNetworkReply*);


private:
    QString mimetype;
    QString width;
    QString height;
    QString depth;
    QString url;
    QString attribute;
    QIcon icon;
};

}

#endif /* BRISAICON_H_ */
