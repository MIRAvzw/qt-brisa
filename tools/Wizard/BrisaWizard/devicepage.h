#ifndef DEVICEPAGE_H
#define DEVICEPAGE_H

#include <QObject>
#include <QWizard>
#include <QDir>
#include <QLabel>
#include <QCheckBox>
#include <QGroupBox>
#include <QLineEdit>
//#include <QRadioButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
//#include <QListWidget>
//#include <QTableWidget>
#include <QFileDialog>
#include <QComboBox>
#include <QSpacerItem>
//#include <QListWidgetItem>
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
