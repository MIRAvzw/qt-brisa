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

    Q_UNUSED(args);
    Q_UNUSED(errMsg);

    addAutoReleasedObject(new BrisaProjectWizard);
    Core::ActionManager* am = Core::ICore::instance()->actionManager();
    Core::ActionContainer* ac = am->createMenu("DoNothingPlugin.DoNothingMenu");
    ac->menu()->setTitle("BRisa");
    am->actionContainer(Core::Constants::M_HELP)->addMenu(ac);
    Core::Command* cmd = am->registerAction(new QAction(this),
                                            "DoNothingPlugin.AboutDoNothing",
                                            QList<int>() << 0);
    cmd->action()->setText(tr("About BRisa"));
    ac->addAction(cmd);
    connect(cmd->action(), SIGNAL(triggered(bool)), this, SLOT(about()));
    return true;
}


void DoNothingPlugin::about()
{
    QMessageBox::information(0, tr("About BRisa Plugin"),
                              tr("More info about Brisa in:\nhttp://brisa.garage.maemo.org/"));
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
