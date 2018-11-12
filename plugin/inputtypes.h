#ifndef INPUTTYPES_H
#define INPUTTYPES_H

//TODO: make these into classes w accessors

//generic of way of describing the input that cursor management can handle
struct CursorNavigationCommand
{
    enum Action
    {
        NoAction,
        Forward,    //tab
        Back,       //ctrl-tab
        Activate,   //enter/click on item
        Escape      //leave scope
    };

    CursorNavigationCommand();

    CursorNavigationCommand(float magnitude, int angle);

    CursorNavigationCommand(Action a);

    //test if this commands angle is between given angles. clockwise from begin to end
    bool angleIsBetween(int begin, int end) const;

    float magnitude;    //0.0 to 1.0
    int angle;          //0 to 359
    Action action;

    static const CursorNavigationCommand Up;
    static const CursorNavigationCommand Down;
    static const CursorNavigationCommand Left;
    static const CursorNavigationCommand Right;

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
//    Q_PROPERTY(CommandResult READ commandResult NOTIFY commandResultChanged )

    //feedback cases;
    //-cmd succesfull
    //-end of list reached (or just the end of whatever selection area maybe)
    //-fell back to the previous scope
};


#endif // INPUTTYPES_H
