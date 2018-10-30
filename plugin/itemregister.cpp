/*#include "itemregister.h"
#include "cursornavigation.h"
#include <QQuickItem>

ItemRegister::ItemRegister()
{

}

void ItemRegister::registerItem(QQuickItem* item)
{
    if (!item)
        return;

    //find first cursor navigable parent
    QQuickItem *parentItem = item->parentItem();
    CursorNavigationAttached *parentCNA;
    while (parentItem) {
        if ((parentCNA=CursorNavigation::cursorNavigationAttachment(parentItem)))
            break;
        parentItem = parentItem->parentItem();
    }

    if (parentCNA)
        parentCNA->m_children.append();

    m_items.append(item);
    connect(item, &QQuickItem::destroyed, this, &ItemRegister::onItemDestroyed);
}

void ItemRegister::unregisterItem(QQuickItem* item)
{
    if (!item)
        return;

    disconnect(item, &QQuickItem::destroyed, this, &ItemRegister::onItemDestroyed);
    m_items.removeOne(item);
}

const QList<QQuickItem*> ItemRegister::siblingItems(QQuickItem *item) const
{
    //find the items that are within the same scope as the argument item
    return m_items;
}

void ItemRegister::onItemDestroyed(QObject *obj)
{
    QQuickItem *item=static_cast<QQuickItem*>(obj);
    m_items.removeOne(item);
}
*/
