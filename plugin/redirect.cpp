#include "redirect.h"
#include <QQuickItem>
#include <QtMath>
#include "inputtypes.h"

Redirect::Redirect(QObject *parent)
:QObject(parent)
,m_start(-1)
,m_end(-1)
,m_target(nullptr)
{
}

Redirect::~Redirect()
{
}

qreal Redirect::start() const
{
    return m_start;
}

qreal Redirect::end() const
{
    return m_end;
}

QQuickItem *Redirect::target() const
{
    return m_target;
}

void Redirect::setStart(qreal start)
{
    m_start = start;
    m_startR = CursorNavigationCommand::fitAngle(qDegreesToRadians(start));
}

void Redirect::setEnd(qreal end)
{
    m_end = end;
    m_endR = CursorNavigationCommand::fitAngle(qDegreesToRadians(end));
}

void Redirect::setTarget(QQuickItem *target)
{
    if (m_target) {
        disconnect(m_target, &QObject::destroyed, this, &Redirect::onTargetDestroyed);
    }
    m_target = target;
    if (m_target) {
        connect(m_target, &QObject::destroyed, this, &Redirect::onTargetDestroyed);
    }
}

bool Redirect::angleIsIncluded(qreal angle)
{
    if (m_startR > m_endR)
        return angle >= m_startR || angle <= m_endR;
    else
        return angle >= m_startR && angle <= m_endR;
}

void Redirect::onTargetDestroyed()
{
    m_target = nullptr;
}

