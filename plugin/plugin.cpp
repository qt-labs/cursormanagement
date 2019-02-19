#include "plugin.h"
#include "cursornavigation.h"
#include "redirect.h"
#include "qqml.h"

CursorNavigationPlugin::CursorNavigationPlugin()
{
}

void CursorNavigationPlugin::registerTypes(const char *uri)
{
    qmlRegisterUncreatableType<CursorNavigation>(uri, 1, 0, "CursorNavigation",
        QStringLiteral("CursorNavigation is not creatable, use the attached properties."));
    qmlRegisterType<Redirect>(uri, 1, 0, "Redirect");
}
