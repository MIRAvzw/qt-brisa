/****************************************************************************
**
** Copyright (C) 2009 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial Usage
** Licensees holding valid Qt Commercial licenses may use this file in
** accordance with the Qt Commercial License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Nokia.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights.  These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
** If you have questions regarding the use of this file, please contact
** Nokia at qt-info@nokia.com.
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef CLASSWIZARD_H
#define CLASSWIZARD_H
#include "intropage.h"
#include "devicepage.h"
#include "servicepage.h"
#include "actionpage.h"
#include <QWizard>
#include <QMap>
#include <QMetaType>
#include <QDir>
#include <BRisa/BrisaUpnp/BrisaAction>
#include <BRisa/BrisaUpnp/brisaargument.h>
#include <BRisa/BrisaUpnp/brisaaction.h>
#include <BRisa/BrisaUpnp/brisastatevariable.h>
#include <BRisa/BrisaUpnp/BrisaService>
//#include "BrisaProjectWizard.h"

using BrisaUpnp::BrisaArgument;
using BrisaUpnp::BrisaStateVariable;
using BrisaUpnp::BrisaAction;
using BrisaUpnp::BrisaService;

//struct QMetaTypeId< BrisaService * >;

//typedef QMultiMap<QString,QString> Argument;
//Q_DECLARE_METATYPE(BrisaArgument*)
//Q_DECLARE_METATYPE(BrisaService*)

class QCheckBox;
class QGroupBox;
class QLabel;
class QLineEdit;
class QRadioButton;
class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QListWidget;
class QTableWidget;
class QFileDialog;
class QComboBox;
class QSpacerItem;
class QListWidgetItem;


class BrisaWizard : public QWizard
{
    Q_OBJECT

public:
    BrisaWizard(QWidget *parent = 0);
    ~BrisaWizard();
    void accept();
//    void reject();
    void generateServiceXml();//TODO
    void generatePro();//TODO
    void generateService();//TODO
    void generateDevice();//TODO
    static bool wasAcceptedWizard();
private:
    QList<BrisaService*> serviceList;
    IntroPage* introPage;
    DevicePage *devicePage;
    ServicePage *servicePage;
    ActionPage *actionPage;
    //IntroPage *introPage;
public slots:
  //  void on_pagechanged(int id);
signals:
    //void thirdPage_arrives();
};

#endif
