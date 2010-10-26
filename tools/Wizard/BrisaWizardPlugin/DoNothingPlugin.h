#ifndef DONOTHINGPLUGIN_H
#define DONOTHINGPLUGIN_H
#include <extensionsystem/iplugin.h>
class DoNothingPlugin : public ExtensionSystem::IPlugin
{
        Q_OBJECT
public:
    DoNothingPlugin();
    ~DoNothingPlugin();
    void extensionsInitialized();
    bool initialize(const QStringList & arguments, QString * errorString);
    void shutdown();

public slots:
    void about();
    void newProject();
    void on_finished();
};
#endif // DONOTHINGPLUGIN_H

