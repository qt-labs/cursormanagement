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
        cmd = CursorNavigationCommand::Left;
        break;
    case Qt::Key_Right:
        cmd = CursorNavigationCommand::Right;
        break;
    case Qt::Key_Up:
        cmd = CursorNavigationCommand::Up;
        break;
    case Qt::Key_Down:
        cmd = CursorNavigationCommand::Down;
        break;
    case Qt::Key_Return:
    case Qt::Key_Enter:
        cmd.action = CursorNavigationCommand::Activate;
        break;
    case Qt::BackButton:
    case Qt::Key_Escape:
        cmd.action = CursorNavigationCommand::Escape;
        break;
    case Qt::Key_Tab:
        cmd.action = CursorNavigationCommand::Forward;
        break;
    case Qt::Key_Backtab:
        cmd.action = CursorNavigationCommand::Back;
        break;
    default:
        return false;
    }

    return m_cursorNavigation->inputCommand(cmd);
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
