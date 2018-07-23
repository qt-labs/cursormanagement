#ifndef INPUTADAPTER_H
#define INPUTADAPTER_H

#include <QObject>
#include "inputtypes.h"

class CursorNavigation;
class QQuickWindow;
class QKeyEvent;
class QMouseEvent;
class QWheelEvent;

/* filter various input events and translate them for the cursor navigation.
 * it is possible to interpret mouse events as joystick/swipe events
 * Set instance of this class as an input filter to the window or component that
 * is being tracked.
 * Events are passed forward to the CursorNavigation class, which should accept
 * the event or reject it. When rejected, event is passed on.
 */

class InputAdapter : public QObject
{
    Q_OBJECT
public:
    InputAdapter(QObject *target, CursorNavigation *cursorNavigation);

protected:
    bool eventFilter(QObject *object, QEvent *event) override;

private:
    bool handleKeyEvent(QKeyEvent *ev);
    bool handleMouseEvent(QMouseEvent *ev);
    bool handleWheelEvent(QWheelEvent *ev);

    QObject *const m_target;
    CursorNavigation *m_cursorNavigation;

};

#endif // INPUTADAPTER_H
