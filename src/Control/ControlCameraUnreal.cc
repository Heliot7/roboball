////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2011, Computer Graphics Group RWTH Aachen University         //
// All rights reserved.                                                       //
////////////////////////////////////////////////////////////////////////////////

#include "ControlCameraUnreal.hh"

ControlCameraUnreal::ControlCameraUnreal(
    const std::tr1::shared_ptr<ACGL::Scene::Camera>& _pCamera,
    float _walkSpeed,
    float _rotationSpeed,
    float _moveSpeed,
    float _accelerationDamper)
:   ControlCamera(_pCamera),
    mWalkSpeed(_walkSpeed),
    mRotationSpeed(_rotationSpeed),
    mMoveSpeed(_moveSpeed),
    mAccelerationDamper(_accelerationDamper)
{
    mKeys = new bool[4];
    for(ACGL::int_t i = 0; i < 4; i++)
        mKeys[i] = false;
}

ControlCameraUnreal::~ControlCameraUnreal(void)
{
    if(mKeys)
        delete[](mKeys);
}

void ControlCameraUnreal::update(float _elapsedTime)
{
    if(mKeys[0])
        mpCamera->setPosition(mpCamera->getPosition() - mpCamera->getForwardDirection() * _elapsedTime * -mWalkSpeed);
    if(mKeys[1])
        mpCamera->setPosition(mpCamera->getPosition() - mpCamera->getForwardDirection() * _elapsedTime * mWalkSpeed);
    if(mKeys[2])
        mpCamera->setPosition(mpCamera->getPosition() - mpCamera->getRightDirection() * _elapsedTime * mWalkSpeed);
    if(mKeys[3])
        mpCamera->setPosition(mpCamera->getPosition() - mpCamera->getRightDirection() * _elapsedTime * -mWalkSpeed);
}

void ControlCameraUnreal::keyPressEvent(QKeyEvent* pKeyEvent)
{
    switch(pKeyEvent->key())
    {
        // WASD movement
        case Qt::Key_W:
            mKeys[0] = true;
            break;
        case Qt::Key_S:
            mKeys[1] = true;
            break;
        case Qt::Key_A:
            mKeys[2] = true;
            break;
        case Qt::Key_D:
            mKeys[3] = true;
            break;
    }
}

void ControlCameraUnreal::keyReleaseEvent(QKeyEvent* pKeyEvent)
{
    switch(pKeyEvent->key())
    {
        // WASD movement
        case Qt::Key_W:
            mKeys[0] = false;
            break;
        case Qt::Key_S:
            mKeys[1] = false;
            break;
        case Qt::Key_A:
            mKeys[2] = false;
            break;
        case Qt::Key_D:
            mKeys[3] = false;
            break;
    }
}

void ControlCameraUnreal::mousePressEvent(QMouseEvent*)
{
}

void ControlCameraUnreal::mouseReleaseEvent(QMouseEvent*)
{
}

void ControlCameraUnreal::mouseMoveEvent(QMouseEvent* pMouseEvent, const QPoint& oRelative)
{
    float relativeX = (float)(oRelative.x());
    float relativeY = (float)(oRelative.y());
    /*
    fRelativeX *= AEFunctions::fAbs(fRelativeX);
    fRelativeY *= AEFunctions::fAbs(fRelativeY);
    fRelativeX /= 10.0f;
    fRelativeY /= 10.0f;
    */
    if(pMouseEvent->buttons() & Qt::LeftButton && pMouseEvent->buttons() & Qt::RightButton)
    {
        float dynamicMoveSpeed = mMoveSpeed * mpCamera->getPosition().y / mAccelerationDamper;
        if(dynamicMoveSpeed < mMoveSpeed)
                dynamicMoveSpeed = mMoveSpeed;

        mpCamera->setPosition(mpCamera->getPosition() + mpCamera->getRightDirection() * dynamicMoveSpeed * relativeX + glm::vec3(0.0f, -1.0f, 0.0f) * dynamicMoveSpeed * relativeY);
    }
    else if(pMouseEvent->buttons() & Qt::LeftButton)
    {
        float dynamicMoveSpeed = mMoveSpeed * mpCamera->getPosition().y / mAccelerationDamper;
        if(dynamicMoveSpeed < mMoveSpeed)
                dynamicMoveSpeed = mMoveSpeed;

        mpCamera->setYaw(mpCamera->getYaw() - relativeX * mRotationSpeed);
        glm::vec3 forwardInXZ = glm::normalize( glm::vec3(mpCamera->getForwardDirection().x, 0.0f, mpCamera->getForwardDirection().z) );
        mpCamera->setPosition(mpCamera->getPosition() - forwardInXZ * dynamicMoveSpeed * relativeY);
    }
    else if(pMouseEvent->buttons() & Qt::RightButton)
    {
        float dynamicMoveSpeed = mMoveSpeed * mpCamera->getPosition().y / mAccelerationDamper;
        if(dynamicMoveSpeed < mMoveSpeed)
                dynamicMoveSpeed = mMoveSpeed;

        mpCamera->setYaw(mpCamera->getYaw() - relativeX * mRotationSpeed);
        mpCamera->setPitch(mpCamera->getPitch() - relativeY * mRotationSpeed);
    }
}

void ControlCameraUnreal::wheelEvent(QWheelEvent*)
{
}
