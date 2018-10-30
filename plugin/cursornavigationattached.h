#ifndef CURSORNAVIGATIONATTACHED_H
#define CURSORNAVIGATIONATTACHED_H

//#include <qqml.h>
#include <QObject>
#include <QList>

class CursorNavigation;
class QQuickItem;
class QQuickWindow;

class CursorNavigationAttached : public QObject
{
    Q_OBJECT
    //is available for cursor navigation
    Q_PROPERTY(bool acceptsCursor READ acceptsCursor WRITE setAcceptsCursor NOTIFY acceptsCursorChanged)
    //indicates if item is currently selected, indicated also by activeFocus property
    Q_PROPERTY(bool hasCursor READ hasCursor NOTIFY hasCursorChanged)
    //indicates if one of children is currently selected
    Q_PROPERTY(bool childHasCursor READ hasCursor NOTIFY hasCursorChanged)
    //traps cursor. a trapped cursor can not be traversed outside of the item that traps it until the escape input is given
    Q_PROPERTY(bool trapsCursor READ trapsCursor WRITE setTrapsCursor NOTIFY trapsCursorChanged)


public:
    CursorNavigationAttached(QQuickItem *parent);
    ~CursorNavigationAttached();

    bool acceptsCursor() const;
    void setAcceptsCursor(bool acceptsCursor);

    bool hasCursor() const;

    bool trapsCursor() const;
    void setTrapsCursor(bool trapsCursor);

    QQuickItem *item() const;

signals:
    void acceptsCursorChanged(bool acceptsCursor);
    void hasCursorChanged(bool hasCursor);
    void trapsCursorChanged(bool trapsCursor);

private slots:
    void onWindowChanged(QQuickWindow *window);

private:
    void setHasCursor(bool hasCursor);
    QList<CursorNavigationAttached*> &siblings();

    CursorNavigation *m_cursorNavigation;
    CursorNavigationAttached *m_parentNavigable;
    QList<CursorNavigationAttached*> m_children;

    bool m_acceptsCursor;
    bool m_hasCursor;
    bool m_trapsCursor;

    friend class CursorNavigation;
};

#endif // CURSORNAVIGATIONATTACHED_H
