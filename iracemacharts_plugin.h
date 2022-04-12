#ifndef IRACEMACHARTS_PLUGIN_H
#define IRACEMACHARTS_PLUGIN_H

#include <QQmlExtensionPlugin>

class IracemaChartsPlugin : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QQmlExtensionInterface_iid)

public:
    void registerTypes(const char *uri) override;
};

#endif // IRACEMACHARTS_PLUGIN_H
