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




#include <QApplication>
#include <QTranslator>
#include <QLocale>
#include <QLibraryInfo>

#include "brisawizard.h"


//#include "DoNothingPlugin.h"

static QStringList projectPaths;


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



        QString wizard = QCoreApplication::applicationDirPath();
        wizard.chop(3); //removes the bin
        wizard += "lib/qtcreator/plugins/BRisa/classwizard";

        Q_INIT_RESOURCE(brisawizard);

        QString translatorFileName = QLatin1String("qt_");
        translatorFileName += QLocale::system().name();
        QTranslator *translator = new QTranslator(QCoreApplication::instance());
        if (translator->load(translatorFileName, QLibraryInfo::location(QLibraryInfo::TranslationsPath)))
            QCoreApplication::instance()->installTranslator(translator);
        BrisaWizard *b = new BrisaWizard(parent);
        b->show();
        connect(b,SIGNAL(finished(int)),this, SLOT(on_finished()));
        return QStringList();

    }

    void CustomProjectWizard::on_finished()
    {
            qDebug() << "ON FINISHED:";
            qDebug() << projectPaths.at(0);
            qDebug() << projectPaths.at(1);
            ProjectExplorer::ProjectExplorerPlugin::instance()->openProject(projectPaths.at(0));
            if(projectPaths.at(1) != "")
                ProjectExplorer::ProjectExplorerPlugin::instance()->openProject(projectPaths.at(1));
    }

    void CustomProjectWizard::setProjectPaths(QStringList paths){
        qDebug() << "at customProjectWizard ";
        qDebug() << paths.at(0);
        qDebug() << paths.at(1);
        foreach(QString path, paths)
            projectPaths.append(path);
    }
