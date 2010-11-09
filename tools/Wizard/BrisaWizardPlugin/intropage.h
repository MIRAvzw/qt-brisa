#ifndef INTROPAGE_H
#define INTROPAGE_H

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
