#include "CustomProjectWizard.h"
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
#include <QProcess>
#include <QDir>
#include <QFile>
#include <QtDebug>
#include <QMainWindow>
#include <QCoreApplication>

#include <QMessageBox>
#include <QApplication>
#include <QIcon>
#include <iplugin.h>
#include <coreplugin/editormanager/editormanager.h>
//#include <coreplugin/editormanager/editorview.h>
//#include "mimedatabase.h"
#include <QProcess>



#include <projectexplorer/project.h>
#include <projectexplorer/pluginfilefactory.h>
#include <projectexplorer/iprojectmanager.h>
#include <projectexplorer/projectexplorer.h>



//#include "DoNothingPlugin.h"


Core::IWizard::WizardKind CustomProjectWizard::kind() const
{
    return IWizard::ProjectWizard;
}


QIcon CustomProjectWizard::icon() const
{
    return qApp->windowIcon();
}

QString CustomProjectWizard::description() const
{
    return "A BRisa project";
}
QString CustomProjectWizard::name() const
{
    return "BRisa project";
}
QString CustomProjectWizard::category() const
{
    return "Upnp Project";
}
QString CustomProjectWizard::trCategory() const
{
    return tr("UPnP Project");
}
QString CustomProjectWizard::displayName() const
{
    return "BRisa UPnP";
}
QString CustomProjectWizard::id() const
{
    return "BRisa Project";
}

QString CustomProjectWizard::displayCategory() const
{
    return "Upnp Project";
}

QStringList CustomProjectWizard::runWizard(const QString &path, QWidget *parent)
{
    Q_UNUSED(path);
    Q_UNUSED(parent);
    QMessageBox::information(parent, "Custom Wizard Dialog", "Hi there!");



        QString wizard = QCoreApplication::applicationDirPath();
        wizard.chop(3); //removes the bin
        wizard += "lib/qtcreator/plugins/BRisa/classwizard";
        QProcess *myProcess = new QProcess(Core::ICore::instance()->mainWindow());
        myProcess->start(wizard);
        connect(myProcess ,SIGNAL(finished(int,QProcess::ExitStatus)),this,SLOT(on_finished()));


        return QStringList();
        //QDir::cha
        //QString dir = QDir::currentPath();
        //bool funcionou =0;
        //funcionou = QProcess::startDetached("/home/camilo/qtcreator-build-desktop/lib/qtcreator/plugins/BRisa/classwizard"); //
        //qDebug("funcionou: %d", funcionou);
    }

    void CustomProjectWizard::on_finished()
    {
        QString dir = QCoreApplication::applicationDirPath();
        dir.chop(3);
        QDir::setCurrent(dir + "lib/qtcreator/plugins/BRisa/");
        qDebug() << QDir::currentPath();
        QFile file("info.path");  //FIXME
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QMessageBox::warning( 0, "An erro ocurred",
                                      "Could not read the info.path");
        }else{

            //QByteArray line = file.readAll();
            QByteArray line = file.readLine();
            QString deviceFilePath = QString(line);

            line = file.readLine();
            QString controlPointFilePath = QString(line);

            deviceFilePath.chop(1);
            //controlPointFilePath.chop(1);


//        Core::ActionManager* am = Core::ICore::instance()->actionManager();
//        QAction *abrir =  am->command(Core::Constants::OPEN)->action();

            //Core::Internal::EditorView *view = new Core::Internal::EditorView();

            //ProjectExplorer::IProjectManager *ip = ProjectExplorer::IProjectManager();
            //ip = ProjectExplorer::ProjectExplorerPlugin::instance()->openProject(path);
            qDebug() << deviceFilePath;
            qDebug() << controlPointFilePath;
            ProjectExplorer::ProjectExplorerPlugin::instance()->openProject(deviceFilePath);
            ProjectExplorer::ProjectExplorerPlugin::instance()->openProject(controlPointFilePath);
        //Core::EditorManager *em = Core::EditorManager::instance();
        //em->openEditor(path);


    }
        //abrir->AboutQtRole
    //agora tenho que abrir o projeto...
    }


//    Core::ActionManager *am =  Core::ICore::instance()->actionManager();
  //      am->command(Core::Constants::OPEN)->action()->trigger();


    //Core::EditorManager *em = Core::EditorManager::instance();
    //Core::Internal::EditorView *view =  ;
    //em->openEditor("/home/camilo/BrisaWizard/DoNothing/DoNothing.pro",);
//}


//bool CustomProjectWizard::initialize(const QStringList& args, QString *errMsg)
//{
//    DoNothingPlugin *nothing = new DoNothingPlugin();
//    //CustomProjectWizard *custom = new CustomProjectWizard();
//    Q_UNUSED(args);
//    Q_UNUSED(errMsg);
//    nothing->addAutoReleasedObject(new CustomProjectWizard);
//    return true;
//}


/*
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
    Core::ActionManager* am = Core::ICore::instance()->actionManager();
    QAction *abrir =  am->command(Core::Constants::OPEN)->action();
    abrir->AboutQtRole
//agora tenho que abrir o projeto...
}

void DoNothingPlugin::about()
{
    QMessageBox::information(0, "About BRisa Plugin",
                              "More information about this plugin in http://brisa.garage.maemo.org/");
}


void DoNothingPlugin::extensionsInitialized()
{
    // Do nothing
}

void DoNothingPlugin::shutdown()
{
    // Do nothing
}

*/
//Q_EXPORT_PLUGIN(CustomProjectWizard)
