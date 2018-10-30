/*#ifndef ITEMREGISTER_H
#define ITEMREGISTER_H

#include <QObject>

class QQuickItem;

//keeps track of items that are cursor navigable
class ItemRegister : public QObject
{
    Q_OBJECT

public:
    ItemRegister();

    void registerItem(QQuickItem* item);
    void unregisterItem(QQuickItem* item);

    //find the items that are within the same scope as the argument item
    const QList<QQuickItem*> siblingItems(QQuickItem* item) const;

private Q_SLOTS:
    void onItemDestroyed(QObject *obj);

private:
    //find the item's first parent that is cursor navigable
    QQuickItem *findParent(QQuickItem* item);

    //for now the data structure is just a list. could be replaced with something more efficient for the final purpose
    QList<QQuickItem*> m_items;

};

#endif // ITEMREGISTER_H
*/
