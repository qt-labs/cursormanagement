#ifndef CURSORNAVIGATIONALGORITHM_H
#define CURSORNAVIGATIONALGORITHM_H

#include <QList>
#include "inputtypes.h"

class CursorNavigationAttached;

class CursorNavigationAlgorithm
{
public:
    CursorNavigationAlgorithm();

    virtual ~CursorNavigationAlgorithm();

    virtual CursorNavigationAttached* getNextCandidate(
                            const QList<CursorNavigationAttached*> &candidates,
                            const CursorNavigationAttached *currentItem,
                            const CursorNavigationCommand& cmd) = 0;

};

#endif // CURSORNAVIGATIONALGORITHM_H
