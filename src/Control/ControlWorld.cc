////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2011, Computer Graphics Group RWTH Aachen University         //
// All rights reserved.                                                       //
////////////////////////////////////////////////////////////////////////////////

#include "ControlWorld.hh"
#include "ControlCameraUnreal.hh"

#include <ACGL/Math/Math.hh>

ControlWorld::ControlWorld(const std::tr1::shared_ptr<World>& _pWorld)
:   ControlEvents(),
    ControlTime(),
    mAccumulatedTime(0.0f),
    mpWorld(_pWorld),
    mpControlCamera(new ControlCameraUnreal(mpWorld->getCamera()))
{}

ControlWorld::~ControlWorld(void)
{}

void ControlWorld::keyPressEvent(QKeyEvent* pKeyEvent)
{
    mpControlCamera->keyPressEvent(pKeyEvent);
}

void ControlWorld::keyReleaseEvent(QKeyEvent* pKeyEvent)
{
    mpControlCamera->keyReleaseEvent(pKeyEvent);
}

void ControlWorld::mousePressEvent(QMouseEvent* pMouseEvent)
{
    mpControlCamera->mousePressEvent(pMouseEvent);
}

void ControlWorld::mouseReleaseEvent(QMouseEvent* pMouseEvent)
{
    mpControlCamera->mouseReleaseEvent(pMouseEvent);
}

void ControlWorld::mouseMoveEvent(QMouseEvent* pMouseEvent, const QPoint& oRelative)
{
    mpControlCamera->mouseMoveEvent(pMouseEvent, oRelative);
}

void ControlWorld::wheelEvent(QWheelEvent* pWheelEvent)
{
    mpControlCamera->wheelEvent(pWheelEvent);
}

void ControlWorld::update(float _elapsedTime)
{
    mpControlCamera->update(_elapsedTime);
    mpWorld->getCoordinateSystem()->adjust<0,2,1>(mpWorld->getCamera()->getPosition(), mpWorld->getCamera()->getForwardDirection());

    mAccumulatedTime += _elapsedTime;
    for(int i = 0; i < mpWorld->getHeightArrayDimension(); ++i)
        for(int j = 0; j < mpWorld->getHeightArrayDimension(); ++j)
            mpWorld->setHeightAt(i, j,
                ACGL::Math::Functions::sinDeg(float(i)/float(mpWorld->getHeightArrayDimension())*360.0f + 100.0f * mAccumulatedTime) *
                ACGL::Math::Functions::cosDeg(float(j)/float(mpWorld->getHeightArrayDimension())*360.0f + 200.0f * mAccumulatedTime));
}
