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
    }
    return false;
}

bool InputAdapter::handleKeyEvent(QKeyEvent *event)
{
    switch (event->key())
    {
    case Qt::Key_Left:
        m_cursorNavigation->m_rootItem->moveLeft();
        break;
    case Qt::Key_Right:
        m_cursorNavigation->m_rootItem->moveRight();
        break;
    case Qt::Key_Up:
        m_cursorNavigation->m_rootItem->moveUp();
        break;
    case Qt::Key_Down:
        m_cursorNavigation->m_rootItem->moveDown();
        break;
    case Qt::Key_Return:
    case Qt::Key_Enter:
        m_cursorNavigation->m_rootItem->activate();
        break;
    case Qt::BackButton:
    case Qt::Key_Escape:
        m_cursorNavigation->m_rootItem->escape();
        break;
    case Qt::Key_Tab:
        m_cursorNavigation->m_rootItem->moveForward();
        break;
    case Qt::Key_Backtab:
        m_cursorNavigation->m_rootItem->moveBack();
        break;
    default:
        return false;
    }

    return true;
}
