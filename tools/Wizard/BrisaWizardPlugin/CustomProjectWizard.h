#ifndef CustomProjectWizard_H
#define CustomProjectWizard_H
#include <extensionsystem/iplugin.h>
#include <coreplugin/icore.h>
#include <coreplugin/basefilewizard.h>
#include <QStringList>

//#include <coreplugin/dialogs/iwizard.h>
//class DoNothingPlugin : public ExtensionSystem::IPlugin
//{
//        Q_OBJECT
//public:
//    DoNothingPlugin();
//    ~DoNothingPlugin();
//    void extensionsInitialized();
//    bool initialize(const QStringList & arguments, QString * errorString);
//    void shutdown();

//public slots:
////    void about();
////    void newProject();
//    void on_finished();
//};

class CustomProjectWizard : public Core::IWizard
{
public:
    CustomProjectWizard() {}
    ~CustomProjectWizard() { }
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
//    void about();
//    void newProject();
    void on_finished();
    static void setProjectPaths(QStringList paths);

};

#endif // DONOTHINGPLUGIN_H
