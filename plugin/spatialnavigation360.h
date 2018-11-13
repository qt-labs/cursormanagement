#ifndef SPATIALNAVIGATION360_H
#define SPATIALNAVIGATION360_H

#include "cursornavigationalgorithm.h"

/* algorithm for stepless 360 cursor navigation
 *
 * idea: allow user customization by providing a set of variables to use for
 * selecting a candidate. for these, the user may set tolerances and weights.
 * tolerance affects the first step of finding candidates. weights are
 * used when choosing between multiple candidates, that are fit within the tolerances
 *
 */

class SpatialNavigation360 : public CursorNavigationAlgorithm
{
public:
    SpatialNavigation360();

    virtual CursorNavigationAttached* getNextCandidate(
                            const QList<CursorNavigationAttached*> &candidates,
                            const CursorNavigationAttached *currentItem,
                            const CursorNavigationCommand& cmd);

private:

};

#endif // SPATIALNAVIGATION360_H
