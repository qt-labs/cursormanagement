#ifndef INPUTTYPES_H
#define INPUTTYPES_H

#include <QtGlobal>

//TODO: make these into classes w accessors

enum Action
{
    NoAction,
    Forward,    //tab
    Back,       //ctrl-tab
    Activate,   //enter/click on item
    Escape      //leave scope
};

//generic of way of describing the input that cursor management can handle
struct CursorNavigationCommand
{
    CursorNavigationCommand();

    CursorNavigationCommand(qreal angle, qreal tolerance);

    CursorNavigationCommand(Action a);

    //bool angleIsBetween(qreal begin, qreal end);

    qreal angle;          //-pi to pi
    qreal angleTolerance;  //0 to pi
    Action action;

    static const CursorNavigationCommand Up;
    static const CursorNavigationCommand Down;
    static const CursorNavigationCommand Left;
    static const CursorNavigationCommand Right;

    //test if given angle is between given sector. sector defined clockwise from begin to end
    static bool angleIsBetween(qreal angle, qreal begin, qreal end);

    //fit the given angle to be between -pi and pi
    static qreal fitAngle(qreal angle);

};

/*feedback datatype returned for commands, describing command results
 *this could be used for example to indicate that a end of a list has been reached,
 *that might produce force feedback on certain inut devices
 */
enum CommandResult
{
    Succesful = 0,
    AreaBoundsReached,
    ListEndReached
};

//describing which boundary was met
enum Boundary {
    Undefined = 0,
    Top = 1,
    Bottom = 2,
    Right = 4,
    Left = 8
};

class CursorNavigationFeedback
{
//    Q_GADGET
//    Q_PROPERTY(CommandResult READ commandResult NOTIFY commandResultChanged )
//    Q_PROPERTY(Boundary READ boundary NOTIFY boundaryChanged )

    //feedback cases;
    //-cmd succesfull
    //-end of list reached (or just the end of whatever selection area maybe)
    //-fell back to the previous scope
};


#endif // INPUTTYPES_H
