#ifndef CURSORNAVIGATIONALGORITHM_H
#define CURSORNAVIGATIONALGORITHM_H

#include <QList>
#include "inputtypes.h"

class ItemRegister;
class QQuickItem;

class CursorNavigationAlgorithm
{
public:
    CursorNavigationAlgorithm(ItemRegister *itemRegister);

    virtual ~CursorNavigationAlgorithm();

    virtual QQuickItem* getNextCandidate(const QList<QQuickItem*> &candidates,
                                         const QQuickItem *currentItem,
                                         const CursorNavigationCommand& cmd) = 0;

private:
    ItemRegister *m_itemRegister;

};

#endif // CURSORNAVIGATIONALGORITHM_H
