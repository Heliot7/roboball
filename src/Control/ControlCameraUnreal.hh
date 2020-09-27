////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2011, Computer Graphics Group RWTH Aachen University         //
// All rights reserved.                                                       //
////////////////////////////////////////////////////////////////////////////////

#ifndef ACGL_TEMPLATE_CONTROLCAMERAUNREAL_HH
#define ACGL_TEMPLATE_CONTROLCAMERAUNREAL_HH

#include "ControlCamera.hh"

class ControlCameraUnreal : public ControlCamera
{
public:
    ControlCameraUnreal(
        const std::tr1::shared_ptr<ACGL::Scene::Camera>& _pCamera,
        float _walkSpeed = 10.0f,
        float _rotationSpeed = 0.5f,
        float _moveSpeed = 0.05f,
        float _accelerationDamper = 100.0f);
    virtual ~ControlCameraUnreal(void);

    void setWalkSpeed          (float _walkSpeed)          { mWalkSpeed = _walkSpeed;                   }
    void setRotationSpeed      (float _rotationSpeed)      { mRotationSpeed = _rotationSpeed;           }
    void setMoveSpeed          (float _moveSpeed)          { mMoveSpeed = _moveSpeed;                   }
    void setAccelerationDamper (float _accelerationDamper) { mAccelerationDamper = _accelerationDamper; }

    float getWalkSpeed          (void) const { return mWalkSpeed;          }
    float getRotationSpeed      (void) const { return mRotationSpeed;      }
    float getMoveSpeed          (void) const { return mMoveSpeed;          }
    float getAccelerationDamper (void) const { return mAccelerationDamper; }

    void keyPressEvent     ( QKeyEvent*   pKeyEvent);
    void keyReleaseEvent   ( QKeyEvent*   pKeyEvent);
    void mousePressEvent   ( QMouseEvent* pMouseEvent);
    void mouseReleaseEvent ( QMouseEvent* pMouseEvent);
    void mouseMoveEvent    ( QMouseEvent* pMouseEvent, const QPoint& oRelative);
    void wheelEvent        ( QWheelEvent* pWheelEvent);

    void update(float _elapsedTime);

private:
    bool* mKeys;

    float mWalkSpeed;
    float mRotationSpeed;
    float mMoveSpeed;
    float mAccelerationDamper;
};

#endif // ACGL_TEMPLATE_CONTROLCAMERAUNREAL_HH
