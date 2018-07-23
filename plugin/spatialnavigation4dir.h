#ifndef SPATIALNAVIGATION_H
#define SPATIALNAVIGATION_H

#include "cursornavigationalgorithm.h"

class SpatialNavigation4Dir : public CursorNavigationAlgorithm
{
public:
    SpatialNavigation4Dir(ItemRegister *itemRegister);

    virtual QQuickItem* getNextCandidate(const QList<QQuickItem*> &candidates,
                                         const QQuickItem *currentItem,
                                         const CursorNavigationCommand &cmd);

};

#endif // SPATIALNAVIGATION_H
