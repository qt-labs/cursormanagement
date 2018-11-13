#include "spatialnavigation4dir.h"
#include "cursornavigationattached.h"
#include <QQuickItem>
#include <QDebug>
#include <algorithm>
#include <functional>
#include <QtMath>

//we only compare distances to eachother so no need to calculate expensive
//square roots. centerpoint comparison is just enough for now too
float distanceSquared(const QRectF& item1, const QRectF& item2)
{
    QPointF p1=item1.center();
    QPointF p2=item2.center();
    float dx=p1.x()-p2.x();
    float dy=p1.y()-p2.y();
    return dx*dx+dy*dy;
}

SpatialNavigation4Dir::SpatialNavigation4Dir()
{

}

CursorNavigationAttached* SpatialNavigation4Dir::getNextCandidate(
                            const QList<CursorNavigationAttached*> &candidates,
                            const CursorNavigationAttached *currentItem,
                            const CursorNavigationCommand &cmd)
{
    if (candidates.isEmpty())
        return nullptr;

    qDebug() << "spatial chooser called, no of candidates=" << candidates.count();

    if (!currentItem && candidates.size()) {
        qDebug() << "the spatial chooser falling back to first child" << candidates.first();
        return candidates.first();
    }

    //picking the next item according to the current items location and the command:
    //-check direction
    //-choose candidates in that general direction currentItem our current item (up, down, left or right)
    //-currentItem those pick ones inside of current items projection
    //  -currentItem those within the projection pick the closest one
    //-if no hits within the projection, then take the closest with distance just in the general direction
    //this algorithm uses the scene coordinates of the items

    std::function<bool(const QRectF&)> isInDirection;
    std::function<bool(const QRectF&)> isInProjection;

    //scene coords of the current item
    const QRectF currentItemSceneRect = currentItem->item()->mapRectToScene(QRectF( 0, 0,
                                          currentItem->item()->width(), currentItem->item()->height() ));

    //NOTICE: overlapping candidates will be ignored for now (TODO, this needs to be changed)

    qreal right_start = -M_PI_4;
    qreal right_end = M_PI_4;
    qreal left_start = M_PI-M_PI_4;
    qreal left_end = -M_PI+M_PI_4;


    if (CursorNavigationCommand::angleIsBetween(cmd.angle, right_start, right_end) ||
        CursorNavigationCommand::angleIsBetween(cmd.angle, left_start, left_end) ) {
    //if (cmd == CursorNavigationCommand::Right || cmd == CursorNavigationCommand::Left) {

        isInProjection = [&currentItemSceneRect](const QRectF &itemRect) {
            return !( currentItemSceneRect.y() > itemRect.y()+itemRect.height() ||
                      currentItemSceneRect.y()+currentItemSceneRect.height() < itemRect.y() );
        };
        if (CursorNavigationCommand::angleIsBetween(cmd.angle, right_start, right_end)) {
        //if (cmd == Command_Right) {
            isInDirection = [&currentItemSceneRect](const QRectF &itemRect) {
                return currentItemSceneRect.x()+currentItemSceneRect.width() <= itemRect.x();
            };
        } else {
            isInDirection = [&currentItemSceneRect](const QRectF &itemRect) {
                return currentItemSceneRect.x() >= itemRect.x()+itemRect.width();
            };
        }

    } else if (CursorNavigationCommand::angleIsBetween(cmd.angle, left_end, right_start) ||
               CursorNavigationCommand::angleIsBetween(cmd.angle, right_end, left_start)) {
    //} else if (cmd == Command_Up || cmd == Command_Down) {
        isInProjection = [&currentItemSceneRect](const QRectF &itemRect) {
            return !( currentItemSceneRect.x() > itemRect.x()+itemRect.width() ||
                      currentItemSceneRect.x()+currentItemSceneRect.width() < itemRect.x() );
        };
        if (CursorNavigationCommand::angleIsBetween(cmd.angle, right_end, left_start)) {
        //if (cmd == Command_Down) {
            isInDirection = [&currentItemSceneRect](const QRectF &itemRect) {
                return currentItemSceneRect.y()+currentItemSceneRect.height() <= itemRect.y();
            };
        } else {
            isInDirection = [currentItemSceneRect](const QRectF &itemRect) {
                return currentItemSceneRect.y() >= itemRect.y()+itemRect.height();
            };
        }
    } else {
        return nullptr;
    }

    std::pair<CursorNavigationAttached*,int> closest(nullptr,0);

    //qDebug() << "current: x=" << currentItemSceneRect.x() << " y=" << currentItemSceneRect.y();

    for (auto candidate : candidates)
    {
        QQuickItem *candidateItem = candidate->item();
        if (!candidateItem->isVisible() || !candidateItem->isEnabled()) {
            //qDebug() << "skipping a invisible/disabled item";
            continue;
        }

        //scene coords of the candidate
        QRectF candidateSceneRect = candidateItem->mapRectToScene(
                                    QRect( 0, 0,
                                    candidateItem->width(), candidateItem->height() ));

        //qDebug() << "x=" << candidateSceneRect.x() << " y=" << candidateSceneRect.y();

        if (isInDirection(candidateSceneRect) && isInProjection(candidateSceneRect))
        {
            //qDebug() << "  is in direction and projection...";
            int dist = distanceSquared(currentItemSceneRect,candidateSceneRect);
            if (closest.second > dist || !closest.first)
            {
                closest.second = dist;
                closest.first = candidate;
            }
        }
    }

    if (closest.first)
    {
        qDebug() << "chosen one: " << closest.first->item()->mapRectToScene(
                        QRect( 0, 0,
                        closest.first->item()->width(), closest.first->item()->height() ));
    }

    if (!closest.first) {
        //qDebug() << Q_FUNC_INFO << " looking for a candidate in the general direction...";

        for (auto candidate : candidates)
        {
            QQuickItem *candidateItem = candidate->item();
            if (!candidateItem->isVisible() || !candidateItem->isEnabled()) {
                //qDebug() << "skipping a invisible/disabled item";
                continue;
            }

            //scene coords of the candidate
            QRectF candidateSceneRect = candidateItem->mapRectToScene(
                                        QRect( 0, 0,
                                        candidateItem->width(), candidateItem->height() ));

            if (isInDirection(candidateSceneRect))
            {
                int dist = distanceSquared(currentItemSceneRect,candidateSceneRect);
                if (closest.second > dist || !closest.first)
                {
                    closest.second = dist;
                    closest.first = candidate;
                }
            }
        }
    }

    qDebug() << Q_FUNC_INFO << " selected candidate:" << closest.first;

    return closest.first;

}
