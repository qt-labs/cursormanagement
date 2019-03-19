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

#ifndef SPATIALNAVIGATION360_H
#define SPATIALNAVIGATION360_H

#include "cursornavigationalgorithm.h"

/* algorithm for stepless 360 cursor navigation
 *
 * idea: allow user customization by providing a set of variables to use for
 * selecting a candidate. for these, the user may set tolerances and weights.
 * tolerance affects the first step of finding candidates. weights are
 * used when choosing between multiple candidates, that are fit within the tolerances
 *
 */

class SpatialNavigation360 : public CursorNavigationAlgorithm
{
public:
    SpatialNavigation360();

    virtual CursorNavigationAttached* getNextCandidate(
                            const QList<CursorNavigationAttached*> &candidates,
                            const CursorNavigationAttached *currentItem,
                            const CursorNavigationCommand& cmd);

private:

};

#endif // SPATIALNAVIGATION360_H
