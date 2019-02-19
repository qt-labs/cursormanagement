#ifndef REDIRECT_H
#define REDIRECT_H

#include <QObject>

class QQuickItem;

class Redirect : public QObject
{
    Q_OBJECT

    Q_PROPERTY(qreal start READ start WRITE setStart)
    Q_PROPERTY(qreal end READ end WRITE setEnd)
    Q_PROPERTY(QQuickItem *target READ target WRITE setTarget)
public:
    Redirect(QObject *parent = nullptr);
    virtual ~Redirect();

    qreal start() const;
    qreal end() const;
    QQuickItem *target() const;

    void setStart(qreal start);
    void setEnd(qreal end);
    void setTarget(QQuickItem *target);

    bool angleIsIncluded(qreal angle);

private slots:
    void onTargetDestroyed();

private:
    qreal m_start;
    qreal m_end;
    //fitted angles in radians
    qreal m_startR;
    qreal m_endR;
    QQuickItem *m_target;
};

#endif // REDIRECT_H
