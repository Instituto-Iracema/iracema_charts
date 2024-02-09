#ifndef IRACEMACHARTS_PLUGIN_H
#define IRACEMACHARTS_PLUGIN_H

#include <QQmlExtensionPlugin>


/**
 * \class IracemaChartsPlugin
 * \brief The IracemaChartsPlugin class is a plugin for QML.
 * 
 * \startuml
 * skinparam classAttributeIconSize 0
 * class IracemaChartsPlugin {
 *  +registerTypes()
 * }
 * IracemaChartsPlugin <|-- QQmlExtensionPlugin
 * \enduml
*/
class IracemaChartsPlugin : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QQmlExtensionInterface_iid)

public:
    /***
     * \fn registerTypes
     * \brief Register the types for QML.
     * \param uri The URI for the plugin.
     * \details This function is called by the QML engine when the plugin is loaded.
     * \n Calls qmlRegisterType
    */
    virtual void registerTypes(const char *uri) override;
};

#endif // IRACEMACHARTS_PLUGIN_H
