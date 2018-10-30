#ifndef SPATIALNAVIGATION_H
#define SPATIALNAVIGATION_H

#include "cursornavigationalgorithm.h"

class SpatialNavigation4Dir : public CursorNavigationAlgorithm
{
public:
    SpatialNavigation4Dir();

    virtual CursorNavigationAttached* getNextCandidate(
                            const QList<CursorNavigationAttached*> &candidates,
                            const CursorNavigationAttached *currentItem,
                            const CursorNavigationCommand &cmd);

};

#endif // SPATIALNAVIGATION_H
