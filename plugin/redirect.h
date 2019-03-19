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
