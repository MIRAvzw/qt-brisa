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
#include <QIcon>
#include <QPixmap>
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

QMessageBox * aboutBox = new QMessageBox();
/*QMessageBox::NoIcon,
                                         tr("About BRisa Plugin"),
                                         tr("BRisa is a project focused on the development of UPnP technologies. <br><br> It provides two projects: the python-brisa and qt-brisa, while a third project is under development: a java version. BRisa Python and Qt implement the UPnP specification 1.1 and shares the same framework API to building UPnP devices, services and control points. This means that developers are able to implement application in one of these programming language reading only a common programming API. In this way, developers only needs to learn just one API and implement UPnP applications in the programming languages BRisa project provides, this prevents, among other problems, have to learn other UPnP stack/API in case it is necessary to migrate codes from one programming language to other.<br><br> BRisa project is released in <a href= 'http://www.opensource.org/licenses/mit-license.php'> MIT License </a>(Python version) and in <a href='http://www.opensource.org/licenses/lgpl-license.php'> LGPL License </a> (Qt version). <br><br> <a href='http://brisa.garage.maemo.org/'>BRisa Project</a>"),
                                         QMessageBox::Ok);
aboutBox->setIconPixmap(QPixmap(":/images/bigBrisaIcon.png"));
*/
aboutBox->setText(tr("BRisa is a project focused on the development of UPnP technologies. <br><br> It provides two projects: the python-brisa and qt-brisa, while a third project is under development: a java version. BRisa Python and Qt implement the UPnP specification 1.1 and shares the same framework API to building UPnP devices, services and control points. This means that developers are able to implement application in one of these programming language reading only a common programming API. In this way, developers only needs to learn just one API and implement UPnP applications in the programming languages BRisa project provides, this prevents, among other problems, have to learn other UPnP stack/API in case it is necessary to migrate codes from one programming language to other.<br><br> BRisa project is released in <a href= 'http://www.opensource.org/licenses/mit-license.php'> MIT License </a>(Python version) and in <a href='http://www.opensource.org/licenses/lgpl-license.php'> LGPL License </a> (Qt version). <br><br> <a href='http://brisa.garage.maemo.org/'>BRisa Project</a>"));
aboutBox->setWindowTitle(tr("About BRisa Plugin"));
aboutBox->setIconPixmap(QPixmap(":/images/bigBrisaIcon.png"));
aboutBox->show();

//QMessageBox::about(0, tr("About BRisa Plugin"), tr("BRisa is a project focused on the development of UPnP technologies. <br><br> It provides two projects: the python-brisa and qt-brisa, while a third project is under development: a java version. BRisa Python and Qt implement the UPnP specification 1.1 and shares the same framework API to building UPnP devices, services and control points. This means that developers are able to implement application in one of these programming language reading only a common programming API. In this way, developers only needs to learn just one API and implement UPnP applications in the programming languages BRisa project provides, this prevents, among other problems, have to learn other UPnP stack/API in case it is necessary to migrate codes from one programming language to other.<br><br> BRisa project is released in <a href= 'http://www.opensource.org/licenses/mit-license.php'> MIT License </a>(Python version) and in <a href='http://www.opensource.org/licenses/lgpl-license.php'> LGPL License </a> (Qt version). <br><br> <a href='http://brisa.garage.maemo.org/'>BRisa Project</a>"));
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
