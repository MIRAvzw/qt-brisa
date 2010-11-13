/*
 * Universidade Federal de Alagoas
 * Instituto de Computação
 * Laboratório de Computação Pervasiva
 * BRisa Project / BRisa-Qt - http://brisa.garage.maemo.org
 * Filename: devicepage.h
 * Created: 11/13/2010
 * Description: Implements the page where the device info will be setted.
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

#ifndef DEVICEPAGE_H
#define DEVICEPAGE_H

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


class DevicePage : public QWizardPage
{
    Q_OBJECT

public:
    DevicePage(QWidget *parent = 0);
private:
    //IntroPage *introPage;

    QGridLayout *gridBox;
    QLabel *deviceTypeLabel, *friendlyNameLabel, *manufacturerLabel, *manufacturerUrlLabel, *modelDesciptionLabel, *modelNameLabel, *modelNumberLabel;
    QLineEdit *deviceTypeLine, *friendlyNameLine, *manufacturerLine, *manufacturerUrlLine, *modelDesciptionLine, *modelNameLine, *modelNumberLine;
    QLabel *modelUrlLabel, *deviceSerialLabel;
    QLineEdit * modelUrlLine, *deviceSerialLine;
public slots:
    void on_devicePage(int);
};

#endif // DEVICEPAGE_H
