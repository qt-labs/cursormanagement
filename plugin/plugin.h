#ifndef PLUGIN_H
#define PLUGIN_H

#include <QQmlExtensionPlugin>

class CursorNavigationPlugin : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QQmlExtensionInterface_iid)

public:
    CursorNavigationPlugin();
    void registerTypes(const char *uri);
};

#endif // PLUGIN_H
