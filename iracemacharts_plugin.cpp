#include "iracemacharts_plugin.h"

#include "iracemacharts.h"

#include <qqml.h>

void IracemaChartsPlugin::registerTypes(const char *uri)
{
    // @uri IracemaCharts
    qmlRegisterType<IracemaCharts>(uri, 1, 0, "IracemaCharts");
}
