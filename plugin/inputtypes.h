#ifndef INPUTTYPES_H
#define INPUTTYPES_H

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

#endif // INPUTTYPES_H
