////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2011, Computer Graphics Group RWTH Aachen University         //
// All rights reserved.                                                       //
////////////////////////////////////////////////////////////////////////////////

#ifndef ACGL_TEMPLATE_CONTROLCAMERA_HH
#define ACGL_TEMPLATE_CONTROLCAMERA_HH

#include "ControlEvents.hh"
#include "ControlTime.hh"

#include <ACGL/Scene/Camera.hh>

#include <QtGui/QMouseEvent>

class ControlCamera : public ControlEvents, public ControlTime
{
public:
    ControlCamera(const std::tr1::shared_ptr<ACGL::Scene::Camera>& _pCamera)
    :   ControlEvents(),
        ControlTime(),
        mpCamera(_pCamera)
    {}
    virtual ~ControlCamera(void) {}

protected:
    std::tr1::shared_ptr<ACGL::Scene::Camera> mpCamera;
};

#endif // ACGL_TEMPLATE_CONTROLCAMERA_HH
