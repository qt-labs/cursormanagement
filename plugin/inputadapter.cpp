#include "inputadapter.h"
#include "cursornavigation.h"
#include <QEvent>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QWheelEvent>

InputAdapter::InputAdapter(QObject *target, CursorNavigation *cursorNavigation)
    : QObject(cursorNavigation)
    ,m_target(target)
    ,m_cursorNavigation(cursorNavigation)
{
    if (m_target)
        m_target->installEventFilter(this);
}

bool InputAdapter::eventFilter(QObject *object, QEvent *event)
{
    if (object != m_target)
        return false;
    if (event->type() == QEvent::KeyPress) {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        return handleKeyEvent(keyEvent);
    } else if (event->type() == QEvent::Wheel) {
        QWheelEvent *wheelEvent = static_cast<QWheelEvent *>(event);
        return handleWheelEvent(wheelEvent);
    } else if (event->type() == QEvent::MouseMove) {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
        return handleMouseEvent(mouseEvent);
    }
    return false;
}

bool InputAdapter::handleKeyEvent(QKeyEvent *event)
{
    CursorNavigationCommand cmd;
    //detect arrow keys, tabs, enter and esc
    switch (event->key())
    {
    case Qt::Key_Left:
        m_cursorNavigation->move(180, 0, true);
        break;
    case Qt::Key_Right:
        m_cursorNavigation->move(0, 0, true);
        break;
    case Qt::Key_Up:
        m_cursorNavigation->move(270, 0, true);
        break;
    case Qt::Key_Down:
        m_cursorNavigation->move(90, 0, true);
        break;
    case Qt::Key_Return:
    case Qt::Key_Enter:
        m_cursorNavigation->action(Activate);
        break;
    case Qt::BackButton:
    case Qt::Key_Escape:
        m_cursorNavigation->action(Escape);
        break;
    case Qt::Key_Tab:
        m_cursorNavigation->action(Forward);
        break;
    case Qt::Key_Backtab:
        m_cursorNavigation->action(Back);
        break;
    default:
        return false;
    }

    return true;
}

bool InputAdapter::handleMouseEvent(QMouseEvent *event)
{
    //interpret mouse movement as omnnidirectional joystick movements for testing purposes
    return false;
}

bool InputAdapter::handleWheelEvent(QWheelEvent *event)
{
    //turn wheel events into tabs
    return false;
}
