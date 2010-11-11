#include "BrisaProjectWizard.h"
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



static QStringList projectPaths;


Core::IWizard::WizardKind BrisaProjectWizard::kind() const
{
    return IWizard::ProjectWizard;
}


QIcon BrisaProjectWizard::icon() const
{
    return QIcon(":/images/brisa.png");
}

QString BrisaProjectWizard::description() const
{
    return "A BRisa project";
}
QString BrisaProjectWizard::name() const
{
    return "BRisa project";
}
QString BrisaProjectWizard::category() const
{
    return "Upnp Project";
}
QString BrisaProjectWizard::trCategory() const
{
    return tr("UPnP Project");
}
QString BrisaProjectWizard::displayName() const
{
    return "BRisa UPnP";
}
QString BrisaProjectWizard::id() const
{
    return "BRisa Project";
}

QString BrisaProjectWizard::displayCategory() const
{
    return "Upnp Project";
}

QStringList BrisaProjectWizard::runWizard(const QString &path, QWidget *parent)
{
    Q_UNUSED(path);
    Q_UNUSED(parent);


    Q_INIT_RESOURCE(brisawizard);

    QString translatorFileName = QLatin1String("qt_");
    translatorFileName += QLocale::system().name();
    QTranslator *translator = new QTranslator(QCoreApplication::instance());
    if (translator->load(translatorFileName, QLibraryInfo::location(QLibraryInfo::TranslationsPath)))
        QCoreApplication::instance()->installTranslator(translator);

    BrisaWizard *b = new BrisaWizard(parent);
    b->show();
    connect(b,SIGNAL(finished(int)),this, SLOT(on_finished()));
    connect(b, SIGNAL(finished(int)), b, SLOT(deleteLater()));
    return QStringList();

}

void BrisaProjectWizard::on_finished()
{
    qDebug() << "ON FINISHED:";
    //qDebug() << projectPaths.at(0);
    //qDebug() << projectPaths.at(1);
    if(BrisaWizard::wasAcceptedWizard()){
        ProjectExplorer::ProjectExplorerPlugin::instance()->openProject(projectPaths.at(0));
        qDebug() << projectPaths.length();
        if(projectPaths.length() > 1)
            ProjectExplorer::ProjectExplorerPlugin::instance()->openProject(projectPaths.at(1));


    }
}

void BrisaProjectWizard::setProjectPaths(QStringList paths){
    qDebug() << "at BrisaProjectWizard ";
    //qDebug() << paths.at(0);
    //qDebug() << paths.at(1);
    foreach(QString path, paths)
        projectPaths.append(path);
}
