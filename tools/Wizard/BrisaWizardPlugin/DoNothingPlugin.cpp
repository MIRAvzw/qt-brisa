#include "DoNothingPlugin.h"
#include <QtPlugin>
#include <QStringList>
#include <coreplugin/coreconstants.h>
#include <coreplugin/actionmanager/actionmanager.h>
#include <coreplugin/actionmanager/actioncontainer.h>
#include <coreplugin/actionmanager/command.h>
#include <coreplugin/icore.h>
#include <QKeySequence>
#include <QAction>
#include <QMenu>
#include <QMessageBox>
#include <QProcess>
#include <QDir>
#include <QtDebug>
#include <QMainWindow>
#include <QCoreApplication>

#include "BrisaProjectWizard.h"

DoNothingPlugin::DoNothingPlugin()
{
    // Do nothing
}
DoNothingPlugin::~DoNothingPlugin()
{
    // Do nothing
}

bool DoNothingPlugin::initialize(const QStringList& args, QString *errMsg)
{

    //DoNothingPlugin *nothing = new DoNothingPlugin();
    //BrisaProjectWizard *custom = new BrisaProjectWizard();

    Q_UNUSED(args);
    Q_UNUSED(errMsg);



    addAutoReleasedObject(new BrisaProjectWizard);

Core::ActionManager* am = Core::ICore::instance()->actionManager();
    Core::Command* cmd = am->registerAction(new QAction(this),
                                            "DoNothingPlugin.AboutDoNothing",
                                            QList<int>() << 0);
    cmd->action()->setText("About DoNothing");


    //connect(command->action(), SIGNAL(triggered()), this, SLOT(newProject()));
    connect(cmd->action(), SIGNAL(triggered(bool)), this, SLOT(about()));
    return true;
}
/*
bool DoNothingPlugin::initialize(const QStringList& args, QString *errMsg)
{
    Q_UNUSED(args);
    Q_UNUSED(errMsg);
    // Fetch the action manager
    Core::ActionManager* am = Core::ICore::instance()->actionManager();
    // Create a DoNothing menu
    Core::ActionContainer* ac
           = am->createMenu("DoNothingPlugin.DoNothingMenu");
    Core::ActionContainer* brisaProject = am->createMenu("DoNothingPlugin.BrisaProjectMenu");

    ac->menu()->setTitle("DoNothing");
    brisaProject->menu()->setTitle("Brisa Project");
    // Create a command for "About DoNothing".
    Core::Command* cmd = am->registerAction(new QAction(this),
                                            "DoNothingPlugin.AboutDoNothing",
                                            QList<int>() << 0);
    cmd->action()->setText("About DoNothing");

    Core::Command* command = am->registerAction(new QAction(this),
                                            "DoNothingPlugin.NewBrisaProject",
                                            QList<int>() << 0);
    command->action()->setText("New BRisa Project");

    // Add DoNothing menu to the menubar
    am->actionContainer(Core::Constants::M_HELP)->addMenu(ac);
    am->actionContainer(Core::Constants::M_FILE)->addAction(command);
    // Add the "About DoNothing" action to the DoNothing menu
    ac->addAction(cmd);

    // Connect the action
    connect(command->action(), SIGNAL(triggered()), this, SLOT(newProject()));
    connect(cmd->action(), SIGNAL(triggered(bool)), this, SLOT(about()));
    return true;
  }

  */
void DoNothingPlugin::newProject()
{
    QString wizard = QCoreApplication::applicationDirPath();
    wizard.chop(3); //removes the bin
    wizard += "lib/qtcreator/plugins/BRisa/classwizard";
    QProcess *myProcess = new QProcess(Core::ICore::instance()->mainWindow());
    myProcess->start(wizard);
    connect(myProcess ,SIGNAL(finished(int,QProcess::ExitStatus)),this,SLOT(on_finished()));

    //QDir::cha
    //QString dir = QDir::currentPath();
    //bool funcionou =0;
    //funcionou = QProcess::startDetached("/home/camilo/qtcreator-build-desktop/lib/qtcreator/plugins/BRisa/classwizard"); //
    //qDebug("funcionou: %d", funcionou);
}

void DoNothingPlugin::on_finished()
{

}

void DoNothingPlugin::about()
{
    QMessageBox::information(0, "About BRisa Plugin",
                              "o que tem escrito aqui");
}


void DoNothingPlugin::extensionsInitialized()
{
    // Do nothing
}

void DoNothingPlugin::shutdown()
{
    // Do nothing
}

Q_EXPORT_PLUGIN(DoNothingPlugin)
