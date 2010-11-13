/*
 * Universidade Federal de Alagoas
 * Instituto de Computação
 * Laboratório de Computação Pervasiva
 * BRisa Project / BRisa-Qt - http://brisa.garage.maemo.org
 * Filename: intropage.h
 * Created: 11/13/2010
 * Description: Implements the page where basic info will be setted.
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

#ifndef INTROPAGE_H
#define INTROPAGE_H

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

class IntroPage : public QWizardPage
{
    Q_OBJECT

public:
    IntroPage(QWidget *parent = 0);



private:

    QPushButton *browserButton;
    QVBoxLayout *mainBox;
    QLabel *pathLabel;
    QLabel *label;
    QLineEdit *projectNameLineEdit;
    QLineEdit *deviceNameEdit;
    QLineEdit *pathLineEdit;
    QCheckBox *generateControlPointYES;
public slots:
    void changeDirectory();
    void on_deviceNameChanged();
    void on_projectNameChanged();
};

#endif // INTROPAGE_H
