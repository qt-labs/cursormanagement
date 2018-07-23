#ifndef CURSORNAVIGATIONATTACHED_H
#define CURSORNAVIGATIONATTACHED_H

//#include <qqml.h>
#include <QObject>

class CursorNavigation;
class QQuickItem;
class QQuickWindow;

class CursorNavigationAttached : public QObject
{
    Q_OBJECT
    //is available for cursor navigation
    Q_PROPERTY(bool acceptsCursor READ acceptsCursor WRITE setAcceptsCursor NOTIFY acceptsCursorChanged)
    //is available for cursor navigation
    Q_PROPERTY(bool hasCursor READ hasCursor NOTIFY hasCursorChanged)
    //traps cursor. a trapped cursor can not be traversed outside of the item that traps it
    Q_PROPERTY(bool trapsCursor READ trapsCursor WRITE setTrapsCursor NOTIFY trapsCursorChanged)
    //proxy cursor to other items
    //Q_PROPERTY(QQmlListProperty<QQuickItem> preferredCursorTargets READ preferredCursorTargetsQML)

public:
    CursorNavigationAttached(QQuickItem *parent);

    bool acceptsCursor() const;
    void setAcceptsCursor(bool acceptsCursor);

    bool hasCursor() const;

    bool trapsCursor() const;
    void setTrapsCursor(bool trapsCursor);

signals:
    void acceptsCursorChanged(bool acceptsCursor);
    void hasCursorChanged(bool hasCursor);
    void trapsCursorChanged(bool trapsCursor);

private slots:
    void onWindowChanged(QQuickWindow *window);

private:
    QQuickItem *item() const;
    void setHasCursor(bool hasCursor);

    CursorNavigation *m_cursorNavigation;
    bool m_acceptsCursor;
    bool m_hasCursor;
    bool m_trapsCursor;

    friend class CursorNavigation;
};

#endif // CURSORNAVIGATIONATTACHED_H
