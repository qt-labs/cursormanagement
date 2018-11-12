#include "inputtypes.h"

const CursorNavigationCommand CursorNavigationCommand::Up(1.0, 270.0);
const CursorNavigationCommand CursorNavigationCommand::Down(1.0, 90.0);
const CursorNavigationCommand CursorNavigationCommand::Left(1.0, 180.0);
const CursorNavigationCommand CursorNavigationCommand::Right(1.0, 0.0);

CursorNavigationCommand::CursorNavigationCommand()
    :magnitude(-1), angle(-1), action(NoAction)
{}

CursorNavigationCommand::CursorNavigationCommand(float magnitude, int angle)
    :magnitude(magnitude), angle(angle), action(NoAction)
{}

CursorNavigationCommand::CursorNavigationCommand(Action a)
    :magnitude(-1), angle(-1), action(a)
{}

//test if this commands angle is between given angles. clockwise from begin to end
bool CursorNavigationCommand::angleIsBetween(int begin, int end) const
{
    if (begin > end)
        return angle >= begin || angle <= end;
    else
        return angle >= begin && angle <= end;
}
