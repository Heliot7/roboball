////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2011, Computer Graphics Group RWTH Aachen University         //
// All rights reserved.                                                       //
////////////////////////////////////////////////////////////////////////////////

#ifndef ACGL_TEMPLATE_CONTROLWORLD_HH
#define ACGL_TEMPLATE_CONTROLWORLD_HH

#include <QtGui/QMouseEvent>

#include "ControlCamera.hh"
#include "../Model/World.hh"

class ControlWorld : public ControlEvents, public ControlTime
{
public:
    ControlWorld(const std::tr1::shared_ptr<World>& _pWorld);
    virtual ~ControlWorld(void);

    void keyPressEvent     ( QKeyEvent*   pKeyEvent);
    void keyReleaseEvent   ( QKeyEvent*   pKeyEvent);
    void mousePressEvent   ( QMouseEvent* pMouseEvent);
    void mouseReleaseEvent ( QMouseEvent* pMouseEvent);
    void mouseMoveEvent    ( QMouseEvent* pMouseEvent, const QPoint& oRelative);
    void wheelEvent        ( QWheelEvent* pWheelEvent);

    void update(float _elapsedTime);

protected:
    float mAccumulatedTime;
    std::tr1::shared_ptr<World> mpWorld;
    std::tr1::shared_ptr<ControlCamera> mpControlCamera;
};

#endif // ACGL_TEMPLATE_CONTROLWORLD_HH
