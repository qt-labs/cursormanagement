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
    //item to select when
    Q_PROPERTY(QQuickItem *escapeTarget READ escapeTarget WRITE setEscapeTarget NOTIFY escapeTargetChanged)


public:
    CursorNavigationAttached(QQuickItem *parent);
    ~CursorNavigationAttached();

    bool acceptsCursor() const;
    bool hasCursor() const;
    bool trapsCursor() const;
    QQuickItem *escapeTarget() const;

    QQuickItem *item() const;

public slots:
    void setAcceptsCursor(bool acceptsCursor);
    void setTrapsCursor(bool trapsCursor);
    void setEscapeTarget(QQuickItem * escapeTarget);

    void move(int angle, float magnitude);
    void moveUp();
    void moveDown();
    void moveRight();
    void moveLeft();
    void activate();
    void forward();
    void back();
    void escape();


signals:
    void acceptsCursorChanged(bool acceptsCursor);
    void hasCursorChanged(bool hasCursor);
    void trapsCursorChanged(bool trapsCursor);

    void escapeTargetChanged(QQuickItem * escapeTarget);

private slots:
    void onWindowChanged(QQuickWindow *window);

private:
    void setHasCursor(bool hasCursor);
    //QList<CursorNavigationAttached*> &siblings();

    CursorNavigation *m_cursorNavigation;
    CursorNavigationAttached *m_parentNavigable;
    QList<CursorNavigationAttached*> m_children;

    bool m_acceptsCursor;
    bool m_hasCursor;
    bool m_trapsCursor;

    friend class CursorNavigation;
    QQuickItem * m_escapeTarget;
};

#endif // CURSORNAVIGATIONATTACHED_H
