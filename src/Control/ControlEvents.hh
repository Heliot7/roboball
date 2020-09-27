////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2011, Computer Graphics Group RWTH Aachen University         //
// All rights reserved.                                                       //
////////////////////////////////////////////////////////////////////////////////

#ifndef ACGL_TEMPLATE_CONTROLEVENTS_HH
#define ACGL_TEMPLATE_CONTROLEVENTS_HH

#include <QtGui/QMouseEvent>
#include <QtGui/QKeyEvent>
#include <QtGui/QWheelEvent>
#include <QtCore/QPoint>

class ControlEvents
{
public:
    ControlEvents(void){}
    virtual ~ControlEvents(void) {}

    virtual void keyPressEvent     (QKeyEvent*) {}
    virtual void keyReleaseEvent   (QKeyEvent*) {}
    virtual void mousePressEvent   (QMouseEvent*) {}
    virtual void mouseReleaseEvent (QMouseEvent*) {}
    virtual void mouseMoveEvent    (QMouseEvent*, const QPoint&) {}
    virtual void wheelEvent        (QWheelEvent*) {}
};

#endif // ACGL_TEMPLATE_CONTROLEVENTS_HH
