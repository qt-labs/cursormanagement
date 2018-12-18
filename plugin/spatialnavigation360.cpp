#include "spatialnavigation360.h"
#include <QQuickItem>
#include "cursornavigationattached.h"
#include <algorithm>
#include <QtMath>

SpatialNavigation360::SpatialNavigation360()
{

}

//test if point is contained in at least one of the given quadrants
bool isPointIncluded(const std::vector<bool> &q, const QPointF &p, const QPointF &o)
{
    return (q[0] && (p.x() > o.x()) && (p.y() > o.y())) ||
           (q[1] && (p.x() < o.x()) && (p.y() > o.y())) ||
           (q[2] && (p.x() < o.x()) && (p.y() < o.y())) ||
           (q[3] && (p.x() > o.x()) && (p.y() < o.y()));
}

//test if rect is contained in at least one of the given quadrants
bool isRectIncluded(const std::vector<bool> &q, const QRectF &rect, const QPointF &origin)
{
    return  !rect.contains(origin) &&
            (isPointIncluded(q, rect.topLeft(), origin) ||
            isPointIncluded(q, rect.bottomRight(), origin));
}

//test if angle is between start and end angles
bool angleIsBetween(qreal angle, qreal begin, qreal end)
{
    if (begin > end)
        return angle >= begin || angle <= end;
    else
        return angle >= begin && angle <= end;
}

//test if 2 sectors overlap
bool sectorsOverlap(qreal begin1, qreal end1,
                    qreal begin2, qreal end2)
{
    return angleIsBetween(begin1, begin2, end2) ||
           angleIsBetween(end1, begin2, end2) ||
           angleIsBetween(begin2, begin1, end1) ||
           angleIsBetween(end2, begin1, end1);
}

qreal pointDistance(const QPointF& p1, const QPointF& p2)
{
    qreal dx=p1.x()-p2.x();
    qreal dy=p1.y()-p2.y();
    return qSqrt(qPow(dx,2)+qPow(dy,2));
}

//minimum distance between 2 rects, calculated from their edges
qreal rectDistance(const QRectF& rect1, const QRectF& rect2)
{
    bool left   = rect2.bottomRight().x() < rect1.topLeft().x();
    bool right  = rect2.topLeft().x() > rect1.bottomRight().x();
    bool bottom = rect2.topLeft().y() > rect1.bottomRight().y();
    bool top    = rect2.bottomRight().y() < rect1.topLeft().y();

    if (top && left)
        return pointDistance(rect1.topLeft(), rect2.bottomRight());
    else if (left && bottom)
        return pointDistance(rect1.bottomLeft(), rect2.topRight());
    else if (bottom && right)
        return pointDistance(rect1.bottomRight(), rect2.topLeft());
    else if (right && top)
        return pointDistance(rect1.topRight(), rect2.bottomRight());
    else if (left)
        return rect1.x() - rect2.bottomRight().x();
    else if (right)
        return rect2.x() - rect1.bottomRight().x();
    else if (bottom)
        return rect2.y() - rect1.bottomRight().y();
    else if (top)
        return rect1.y() - rect2.bottomRight().y();//y2 - y1b
    else //rectangles overlap
        return 0;
}

//get the widest arc that is less than 180 degrees, that this item covers, clockwise around the origin
std::pair<qreal, qreal> getSector(const QRectF &rect, const QPointF &origin)
{
    std::pair<qreal, qreal> angles;
    angles = std::minmax({std::atan2(rect.topLeft().y()-origin.y(), rect.topLeft().x()-origin.x()),
                          std::atan2(rect.topRight().y()-origin.y(), rect.topRight().x()-origin.x()),
                          std::atan2(rect.bottomRight().y()-origin.y(), rect.bottomRight().x()-origin.x()),
                          std::atan2(rect.bottomLeft().y()-origin.y(), rect.bottomLeft().x()-origin.x())
                         });

    //if delta larger than 180, invert min and max
    if (angles.second-angles.first > M_PI) {
        qreal temp = angles.first;
        angles.first = angles.second;
        angles.second = temp;
    }

    return angles;
}

CursorNavigationAttached* SpatialNavigation360::getNextCandidate(
                        const QList<CursorNavigationAttached*> &candidates,
                        const CursorNavigationAttached *currentItem,
                        const CursorNavigationCommand& cmd)
{
    /* -angle should be between -180 and 180 in relation to the x axis, clockwise around the origin
     * -depending on the input angle, find min and max x and y values which items must have
     * -calculate angles for items points that are within the limits. from those angles, pick min and max (widest sector the item covers)
     * -items that overlap the current item center, should be ignored
     * -items that are within seaqrch beams angle limits, are stored along the angle ranges they have
     * -if there are more than 1 stored items, we select the item that cuts the exact selection vector.
     *  if no item overlaps the center, pick the one closest to the current item
     * -remember to use current item's coord system as the reference!!!
     */

    //qWarning() << "##### navigation360: start, angle = " << cmd.angle << " tolerance = " << cmd.angleTolerance;

    if (candidates.isEmpty())
        return nullptr;

    if (!currentItem && candidates.size()) {
        return candidates.first();
    }

    //booleans for quadrants
    std::vector<bool> quadrants(4);

    //define selector beam sector
    qreal angle1, angle2;

    angle1 = CursorNavigationCommand::fitAngle(cmd.angle - cmd.angleTolerance);
    angle2 = CursorNavigationCommand::fitAngle(cmd.angle + cmd.angleTolerance);

    quadrants[0] = sectorsOverlap(angle1, angle2, 0, M_PI_2);
    quadrants[1] = sectorsOverlap(angle1, angle2, M_PI_2, M_PI);
    quadrants[2] = sectorsOverlap(angle1, angle2, -M_PI, -M_PI_2);
    quadrants[3] = sectorsOverlap(angle1, angle2, -M_PI_2, 0);

    const QRectF currentItemSceneRect = currentItem->item()->mapRectToScene(
                QRectF( 0, 0, currentItem->item()->width(), currentItem->item()->height() ));

    const QPointF origin = currentItemSceneRect.center();

    //item that overlaps the center of the selector beam
    CursorNavigationAttached* directHitItem = nullptr;
    qreal directHitDistance = -1;
    //item that overlaps selector beam, but does not overlap with the center
    CursorNavigationAttached* withinToleranceItem = nullptr;
    qreal withinToleranceDistance = -1;


    for (auto iter: candidates)
    {
        if (!iter->available() || iter == currentItem)
            continue;

        const QRectF itemSceneRect = iter->item()->mapRectToScene(
                    QRectF( 0, 0, iter->item()->width(), iter->item()->height() ));

        if (isRectIncluded(quadrants, itemSceneRect, origin)) {

            std::pair<qreal,qreal> sector = getSector(itemSceneRect, origin);

            if (angleIsBetween(cmd.angle, sector.first, sector.second)) {
                qreal dist = rectDistance(itemSceneRect, currentItemSceneRect);
                if (!directHitItem || dist < directHitDistance) {
                    directHitDistance = dist;
                    directHitItem = iter;
                }
            } else if (!directHitItem && sectorsOverlap(angle1, angle2, sector.first, sector.second)) {
                qreal dist = rectDistance(itemSceneRect, currentItemSceneRect);
                if (!withinToleranceItem || dist < withinToleranceDistance) {
                    withinToleranceDistance = dist;
                    withinToleranceItem = iter;
                }
            }
        }
    }

    //qWarning() << "##### end, directHit = " <<
      //            directHitItem << "  withinTolerances = " << withinToleranceItem;

    if (directHitItem)
        return directHitItem;

    return withinToleranceItem;

}
