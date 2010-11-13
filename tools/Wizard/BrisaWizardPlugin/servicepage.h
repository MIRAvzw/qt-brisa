/*
 * Universidade Federal de Alagoas
 * Instituto de Computação
 * Laboratório de Computação Pervasiva
 * BRisa Project / BRisa-Qt - http://brisa.garage.maemo.org
 * Filename: servicepage.h
 * Created: 11/13/2010
 * Description: Implements the page where the BRisa service will setted.
 * Authors: Willian Victor Silva <willian.victors@gmail.com> 2010
 *          Camilo Costa Campos <zeromaisum@gmail.com> 2010
 *
 *
 * Copyright (C) <2010> <Pervasive Computing Laboratory @ Federal
 * University of Alagoas>
 *
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

#ifndef SERVICEPAGE_H
#define SERVICEPAGE_H

#include <QObject>
#include <QWizard>
#include <QDir>
#include <QLabel>
#include <QCheckBox>
#include <QGroupBox>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QFileDialog>
#include <QComboBox>
#include <QSpacerItem>
#include <QPushButton>
#include <QListWidget>
#include <BRisa/BrisaUpnp/BrisaService>


using BrisaUpnp::BrisaService;

Q_DECLARE_METATYPE(BrisaService*)



class ServicePage : public QWizardPage
{
    Q_OBJECT

public:
    ServicePage(QWidget *parent = 0);
private:
    QLabel *serviceLabel;
    QLineEdit *serviceEdit;
    QPushButton *addServiceButton;
    QHBoxLayout *hBox;
    QVBoxLayout *mainBox;
    QListWidget *serviceListWidget;
    QLineEdit *serviceTypeLineEdit;
    QLineEdit *serviceIDLineEdit;
    QLineEdit *serviceXMLPathLineEdit;
    QLineEdit *serviceControlLineEdit;
    QLineEdit *eventSubLineEdit;
    QPushButton *removeServiceButton;
public:
    static QList<BrisaService*> getServiceList();
    static QStringList getServiceNameList();

public slots:

    void on_addServiceButton_clicked();
    void on_servicePage(int);
    void on_serviceEditing_finished();
    void on_removeButton_clicked();
};

#endif // SERVICEPAGE_H
