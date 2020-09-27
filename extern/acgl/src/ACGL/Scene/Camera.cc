////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2011, Computer Graphics Group RWTH Aachen University         //
// All rights reserved.                                                       //
////////////////////////////////////////////////////////////////////////////////

#include <ACGL/Scene/Camera.hh>

using namespace ACGL::Scene;

glm::mat4 Camera::getProjectionMatrix(void) const
{
    // returns a projection matrix as gluPerspective would do
    return glm::perspective( mFOV, getAspectRatio(), mNear, mFar );
}

glm::mat4 Camera::getViewMatrix(void) const
{
    glm::mat4 mView;
    mView[0][0] =  mRight.x;
    mView[0][1] =  mUp.x;
    mView[0][2] = -mForward.x;
    mView[1][0] =  mRight.y;
    mView[1][1] =  mUp.y;
    mView[1][2] = -mForward.y;
    mView[2][0] =  mRight.z;
    mView[2][1] =  mUp.z;
    mView[2][2] = -mForward.z;
    mView[3][0] = -(mRight.x   * mPosition.x + mRight.y   * mPosition.y + mRight.z   * mPosition.z);
    mView[3][1] = -(mUp.x      * mPosition.x + mUp.y      * mPosition.y + mUp.z      * mPosition.z);
    mView[3][2] =  (mForward.x * mPosition.x + mForward.y * mPosition.y + mForward.z * mPosition.z);

    return mView;
}

glm::mat4 Camera::getInverseViewMatrix(void) const
{
    glm::mat4 mView;
    mView[0][0] =  mRight.x;
    mView[0][1] =  mRight.y;
    mView[0][2] =  mRight.z;
    mView[1][0] =  mUp.x;
    mView[1][1] =  mUp.y;
    mView[1][2] =  mUp.z;
    mView[2][0] = -mForward.x;
    mView[2][1] = -mForward.y;
    mView[2][2] = -mForward.z;
    mView[3][0] =  mPosition.x;
    mView[3][1] =  mPosition.y;
    mView[3][2] =  mPosition.z;
    return mView;
}

void Camera::updateLocalCoordinateSystemByTarget(const glm::vec3& _up)
{
    mForward = glm::normalize( mTarget - mPosition );
    mRight   = glm::normalize( glm::cross( mForward, _up) );
    mUp      = glm::normalize( glm::cross( mRight,   mForward) );

    updateOrientationByLocalCoordinateSystem();
}


void Camera::updateLocalCoordinateSystemByOrientation(void)
{
    //Calculate the full rotation in the right order:
    //rot => 1. mYaw (y) -> 2. mPitch (x) -> 3. mRoll (z)
    glm::mat3 rx = Math::Functions::rotationMatrixX(mPitch);
    glm::mat3 ry = Math::Functions::rotationMatrixY(mYaw);
    glm::mat3 rz = Math::Functions::rotationMatrixZ(mRoll);

    glm::mat3 rotation = ry * rx * rz;
    
    mRight   = rotation * glm::vec3(1.0f, 0.0f,  0.0f);
    mUp      = rotation * glm::vec3(0.0f, 1.0f,  0.0f);
    mForward = rotation * glm::vec3(0.0f, 0.0f, -1.0f);
}

void Camera::updateOrientationByLocalCoordinateSystem(void)
{
    if (mUp.x > 1.0f - Math::Constants::EPSILON_FLOAT)
    {
        mYaw = Math::Functions::atan2Deg(mForward.x, -mForward.z);
        mPitch = 90.0f;
        mRoll  =  0.0f;
        return;
    }
    if (mUp.x < Math::Constants::EPSILON_FLOAT - 1.0f)
    {
        mYaw = Math::Functions::atan2Deg(mForward.x, -mForward.z);
        mPitch = -90.0f;
        mRoll  =   0.0f;
        return;
    }

    mYaw   = Math::Functions::atan2Deg(-mRight.z,   mRight.x);
    mPitch = Math::Functions::atan2Deg( mForward.y, mUp.y);
    mRoll  = Math::Functions::asinDeg(  mRight.y);
}
