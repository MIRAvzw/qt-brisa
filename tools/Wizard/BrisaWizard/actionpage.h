#ifndef ACTIONPAGE_H
#define ACTIONPAGE_H
#include "servicepage.h"
#include <QObject>

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
#include <QListWidget>
#include <QTableWidget>

#include <BRisa/BrisaUpnp/BrisaAction>
#include <BRisa/BrisaUpnp/brisaargument.h>
#include <BRisa/BrisaUpnp/brisaaction.h>
#include <BRisa/BrisaUpnp/brisastatevariable.h>
#include <BRisa/BrisaUpnp/BrisaService>


using BrisaUpnp::BrisaArgument;
using BrisaUpnp::BrisaStateVariable;
using BrisaUpnp::BrisaAction;
using BrisaUpnp::BrisaService;

Q_DECLARE_METATYPE(BrisaAction*)
//Q_DECLARE_METATYPE(BrisaService*)



class ActionPage : public QWizardPage
{
    Q_OBJECT

public:
    ActionPage(QWidget *parent = 0);
    int currentTableRow;
    QListWidget *actionListWidget;
    QTableWidget *argumentTableWidget;
    QLineEdit * argumentEdit;
private:
    QVBoxLayout *mainBox;
    QLabel *actionNameLabel;

//    QLabel *baseClassLabel;
    QComboBox *serviceCbox;
    QPushButton *addActionButton;
    //QPushButton *addArgumentButton;
    QPushButton *removeActionButton;
    QPushButton *editArgumentsButton;
//    QRadioButton *inRadioButton;
  //  QRadioButton *outRadioButton;
    QLineEdit *stateVariableLineEdit;
    QPushButton *repeatArgumentsButton;
    QList<BrisaService*> serviceList;
    //QRadioButton *stringType;
    //QRadioButton *floatType;
    //QRadioButton *intType;
    //QRadioButton *boolType;
    //QRadioButton *userType;
    //QRadioButton *eventsYES;
    //QRadioButton *eventsNO;
    QLineEdit *actionNameLineEdit;
    QLineEdit *userTypeNameLineEdit;
    //QListWidget *listActionWidget;
//    QLineEdit *baseClassLineEdit;
   // QCheckBox *qobjectMacroCheckBox;
    //QGroupBox *groupBox;
//    QRadioButton *qobjectCtorRadioButton;
//    QRadioButton *qwidgetCtorRadioButton;
//    QRadioButton *defaultCtorRadioButton;
//    QCheckBox *copyCtorCheckBox;
public slots:
    void on_addActionButton_clicked();
    //void on_AddArgumentButton_clicked();
    //void on_RemoveArgumentButton_clicked();
    void on_RemoveActionButton_clicked();
    void on_actionChange(QModelIndex i);
    void on_actionNameLineEdit_edited();
    void on_actionPage(int id);
    void on_selectedService(int i);
    void on_actionListWidget_DoubleClicked();
    void on_EditArgumentsButton_clicked();
    void on_repeatArgumentsButton_clicked();
};

#endif // ACTIONPAGE_H
