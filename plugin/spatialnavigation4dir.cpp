/****************************************************************************
**
** Copyright (C) 2018, 2019 Luxoft Sweden AB. All rights reserved.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the cursor management module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 3 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL3 included in the
** packaging of this file. Please review the following information to
** ensure the GNU Lesser General Public License version 3 requirements
** will be met: https://www.gnu.org/licenses/lgpl-3.0.html.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 2.0 or (at your option) the GNU General
** Public license version 3 or any later version approved by the KDE Free
** Qt Foundation. The licenses are as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL2 and LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-2.0.html and
** https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

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

    qCDebug(cursorNavigationLog) << "4-way algortihm called, no of candidates=" << candidates.count();

    if (!currentItem && candidates.size()) {
        qCDebug(cursorNavigationLog) << "the spatial chooser falling back to first child" << candidates.first();
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

    //NOTICE: candidates overlapping with current item will be ignored for now (TODO, this needs to be changed)

    qreal right_start = -M_PI_4;
    qreal right_end = M_PI_4;
    qreal left_start = M_PI-M_PI_4;
    qreal left_end = -M_PI+M_PI_4;


    if (CursorNavigationCommand::angleIsBetween(cmd.angle, right_start, right_end) ||
        CursorNavigationCommand::angleIsBetween(cmd.angle, left_start, left_end) ) {

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

    //item that is closest within the projection
    CursorNavigationAttached* inProjectionItem = nullptr;
    float inProjectionItemDistance = -1;
    //item that is closest in the general direction, but not within projection
    CursorNavigationAttached* inDirectionItem = nullptr;
    float inDirectionItemDistance = -1;

    for (auto candidate : candidates)
    {
        QQuickItem *candidateItem = candidate->item();
        if (!candidate->available() || candidate == currentItem)
            continue;

        //scene coords of the candidate
        QRectF candidateSceneRect = candidateItem->mapRectToScene(
                                    QRectF( 0, 0,
                                    candidateItem->width(), candidateItem->height() ));

        if (isInDirection(candidateSceneRect)) {
            if (isInProjection(candidateSceneRect)) {
                float dist = distanceSquared(currentItemSceneRect,candidateSceneRect);
                if (inProjectionItemDistance > dist || !inProjectionItem)
                {
                    inProjectionItemDistance = dist;
                    inProjectionItem = candidate;
                }
            } else if (!inProjectionItem) {
                float dist = distanceSquared(currentItemSceneRect,candidateSceneRect);
                if (inDirectionItemDistance > dist || !inDirectionItem)
                {
                    inDirectionItemDistance = dist;
                    inDirectionItem = candidate;
                }
            }
        }
    }

    if (inProjectionItem)
    {
        return inProjectionItem;
    }
    return inDirectionItem;
}
