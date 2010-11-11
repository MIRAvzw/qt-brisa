#ifndef BrisaProjectWizard_H
#define BrisaProjectWizard_H
#include <extensionsystem/iplugin.h>
#include <coreplugin/icore.h>
#include <coreplugin/basefilewizard.h>
#include <QStringList>


class BrisaProjectWizard : public Core::IWizard
{
public:
    BrisaProjectWizard() {}
    ~BrisaProjectWizard() { qDebug("hell2"); }
    Core::IWizard::WizardKind kind() const;
    QIcon icon() const;
    QString description() const;
    QString name() const;
    QString category() const;
    QString trCategory() const;
    QStringList runWizard(const QString &path, QWidget *parent);

    bool initialize(const QStringList& args, QString *errMsg);

    QString displayName() const;
    QString id() const;
    QString displayCategory() const;
    Q_OBJECT
public slots:
    void on_finished();
    static void setProjectPaths(QStringList paths);

};

#endif // DONOTHINGPLUGIN_H
