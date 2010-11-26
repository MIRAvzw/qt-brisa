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

#include "brisaicon.h"

using namespace Brisa;

BrisaIcon::BrisaIcon(QString mimetype, QString width, QString height,
                     QString depth, QString url,
                     QObject *parent) : QObject(parent)
{
    this->mimetype = mimetype;
    this->width = width;
    this->height = height;
    this-> depth = depth;
    this->url = url;
}

void BrisaIcon::setAttribute(xmlIconTags key, QString v)
{
    switch (key) {
    case Mimetype:
        this->mimetype = v;
        break;
    case Width:
        this->width = v;
        break;
    case Height:
        this->height = v;
        break;
    case Depth:
        this->depth = v;
        break;
    case Url:
        this->url = v;
        break;
    }
}

void BrisaIcon::setIcon(QIcon icon)
{
    this->icon = icon;
}

QIcon BrisaIcon::getIcon()
{
    return this->icon;
}

void BrisaIcon::downloadIcon(QString deviceUrl)
{
    QNetworkAccessManager *manager = new QNetworkAccessManager();
    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(downloadFinished(QNetworkReply*)));

    QString iconUrl = deviceUrl + this->url;
    manager->get(QNetworkRequest(QUrl(iconUrl)));
}

void BrisaIcon::downloadFinished(QNetworkReply *reply)
{
    QByteArray imageData = reply->readAll();
    QPixmap pixmap;
    pixmap.loadFromData(imageData);
    this->setIcon(QIcon(pixmap));

    emit iconDownloadFinished();
}

void BrisaIcon::clear()
{
    this->mimetype.clear();
    this->width.clear();
    this->height.clear();
    this->depth.clear();
    this->url.clear();
    this->attribute.clear();
}

QString BrisaIcon::getAttribute(xmlIconTags key)
{
    switch (key) {
    case Mimetype:
        return this->mimetype;
        break;
    case Width:
        return this->width;
        break;
    case Height:
        return this->height;
        break;
    case Depth:
        return this->depth;
        break;
    case Url:
        return this->url;
        break;
    default:
        return "";
        break;
    }
}
