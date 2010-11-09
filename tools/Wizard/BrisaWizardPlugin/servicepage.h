#ifndef SERVICEPAGE_H
#define SERVICEPAGE_H

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
