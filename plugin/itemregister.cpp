#include "itemregister.h"
#include <QQuickItem>

ItemRegister::ItemRegister()
{

}

void ItemRegister::registerItem(QQuickItem* item)
{
    if (!item)
        return;

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

const QList<QQuickItem*> ItemRegister::items() const
{
    return m_items;
}

void ItemRegister::onItemDestroyed(QObject *obj)
{
    QQuickItem *item=static_cast<QQuickItem*>(obj);
    m_items.removeOne(item);
}
