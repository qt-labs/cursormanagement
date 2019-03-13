#include "inputtypes.h"
#include <QtMath>

CursorNavigationCommand::CursorNavigationCommand()
    :angle(-1), angleTolerance(-1), action(NoAction)
{}

CursorNavigationCommand::CursorNavigationCommand(qreal a, qreal tolerance)
    :angle(CursorNavigationCommand::fitAngle(a)), angleTolerance(tolerance), action(NoAction)
{}

CursorNavigationCommand::CursorNavigationCommand(Action a)
    :angle(-1), angleTolerance(-1), action(a)
{}

//test if this commands angle is between given angles. clockwise from begin to end
//bool CursorNavigationCommand::angleIsBetween(qreal begin, qreal end)
//{
//    return CursorNavigationCommand::angleIsBetween(this->angle, begin, end);
//}

bool CursorNavigationCommand::angleIsBetween(qreal angle, qreal begin, qreal end)
{
    if (begin > end)
        return angle >= begin || angle <= end;
    else
        return angle >= begin && angle <= end;
}

qreal CursorNavigationCommand::fitAngle(qreal angle)
{
    if (angle > M_PI)
        return -M_PI + std::fmod(angle ,M_PI);
    else if (angle < -M_PI)
        return M_PI + std::fmod(angle ,M_PI);
    return angle;
}
