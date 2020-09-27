////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2011, Computer Graphics Group RWTH Aachen University         //
// All rights reserved.                                                       //
////////////////////////////////////////////////////////////////////////////////

#ifndef ACGL_SCENE_CAMERA_HH
#define ACGL_SCENE_CAMERA_HH

/*
 * A generic camera class.
 */

#include <ACGL/ACGL.hh>
#include <ACGL/Math/Math.hh>

namespace ACGL{
namespace Scene{

class Camera
{
public:
    Camera(void)
    :   mRight    (),
        mUp       (),
        mForward  (),
        mWidth    (800),
        mHeight   (600),
        mFOV      (75.0f),
        mNear     (0.1f),
        mFar      (10000.0f),
        mPitch    (0.0f),
        mYaw      (0.0f),
        mRoll     (0.0f),
        mPosition (3.0f, 2.0f, 3.0f),
        mTarget   (0.0f, 0.0f, 0.0f)
    {
        updateLocalCoordinateSystemByTarget();
        updateOrientationByLocalCoordinateSystem();
    }
    Camera(
        int_t _width,
        int_t _height,
        float _fov,
        float _near,
        float _far,
        const glm::vec3& _position,
        const glm::vec3& _target)
    :   mRight    (),
        mUp       (),
        mForward  (),
        mWidth    (_width),
        mHeight   (_height),
        mFOV      (_fov),
        mNear     (_near),
        mFar      (_far),
        mPitch    (0.0f),
        mYaw      (0.0f),
        mRoll     (0.0f),
        mPosition (_position),
        mTarget   (_target)
    {
        updateLocalCoordinateSystemByTarget();
        updateOrientationByLocalCoordinateSystem();
    }
    Camera(const Camera& other)
    :   mRight    (other.mRight),
        mUp       (other.mUp),
        mForward  (other.mForward),
        mWidth    (other.mWidth),
        mHeight   (other.mHeight),
        mFOV      (other.mFOV),
        mNear     (other.mNear),
        mFar      (other.mFar),
        mPitch    (other.mPitch),
        mYaw      (other.mYaw),
        mRoll     (other.mRoll),
        mPosition (other.mPosition),
        mTarget   (other.mTarget)
    {
    }
    ~Camera(void) {}

    inline       float      getAspectRatio      (void) const { return (float)mWidth / (float)mHeight; }
    inline const glm::vec3& getUpDirection      (void) const { return mUp;                            }
    inline const glm::vec3& getRightDirection   (void) const { return mRight;                         }
    inline const glm::vec3& getForwardDirection (void) const { return mForward;                       }
    inline       int_t      getWidth            (void) const { return mWidth;                         }
    inline       int_t      getHeight           (void) const { return mHeight;                        }
    inline       float      getFOV              (void) const { return mFOV;                           }
    inline       float      getNear             (void) const { return mNear;                          }
    inline       float      getFar              (void) const { return mFar;                           }
    inline       float      getPitch            (void) const { return mPitch;                         }
    inline       float      getYaw              (void) const { return mYaw;                           }
    inline       float      getRoll             (void) const { return mRoll;                          }
    inline const glm::vec3& getPosition         (void) const { return mPosition;                      }
    inline const glm::vec3& getTarget           (void) const { return mTarget;                        }
    
    inline void setWidth  (int_t _width)  { mWidth  = _width;  }
    inline void setHeight (int_t _height) { mHeight = _height; }
    inline void setFOV    (float _fov)    { mFOV    = _fov;    }
    inline void setNear   (float _near)   { mNear   = _near;   }
    inline void setFar    (float _far)    { mFar    = _far;    }


    inline void setPosition(const glm::vec3& _position, bool _moveTarget = true)
    {
        if(_moveTarget)
            mTarget += _position - mPosition;

        mPosition = _position;

        if(!_moveTarget)
            updateLocalCoordinateSystemByTarget(mUp);
    }
    inline void setPosition(const glm::vec3& _position, const glm::vec3& _up, bool _moveTarget = true)
    {
        if(_moveTarget)
            mTarget += _position - mPosition;

        mPosition = _position;
        updateLocalCoordinateSystemByTarget(_up);
    }

    inline void setTarget(const glm::vec3& _target, bool _movePosition = true)
    {
        if(_movePosition)
            mPosition += _target - mTarget;

        mTarget = _target;

        if(!_movePosition)
            updateLocalCoordinateSystemByTarget(mUp);
    }

    inline void setPitch(float _pitch)
    {
        mPitch = _pitch;
        updateLocalCoordinateSystemByOrientation();
        mTarget = mPosition + glm::length(mTarget - mPosition) * mForward;
    }

    inline void setYaw(float _yaw)
    {
        mYaw = _yaw;
        updateLocalCoordinateSystemByOrientation();
        mTarget = mPosition + glm::length(mTarget - mPosition) * mForward;
    }

    inline void setRoll(float _roll)
    {
        mRoll = _roll;
    }
    
    inline void setPitchAroundTarget(float pitch)
    { 
        mPitch = pitch;
        updateLocalCoordinateSystemByOrientation();
        mPosition = mTarget - glm::length(mTarget - mPosition) * mForward;
    }
    inline void setYawAroundTarget(float yaw)
    { 
        mYaw = yaw;
        updateLocalCoordinateSystemByOrientation(); 
        mPosition = mTarget - glm::length(mTarget - mPosition) * mForward;
    }

    inline void setOrientation(float _pitch, float _yaw, float _roll)
    {
        mPitch = _pitch;
        mYaw   = _yaw;
        mRoll  = _roll;
        updateLocalCoordinateSystemByOrientation();
    }

    
    glm::mat4 getProjectionMatrix() const;
    glm::mat4 getViewMatrix() const;
    glm::mat4 getInverseViewMatrix() const;

private:
    void updateLocalCoordinateSystemByTarget(const glm::vec3& _up = glm::vec3(0.0f, 1.0f, 0.0f));
    void updateLocalCoordinateSystemByOrientation(void);
    void updateOrientationByLocalCoordinateSystem(void);

    glm::vec3 mRight;
    glm::vec3 mUp;
    glm::vec3 mForward;
    int_t     mWidth;
    int_t     mHeight;
    float     mFOV;
    float     mNear;
    float     mFar;
    float     mPitch;
    float     mYaw;
    float     mRoll;
    glm::vec3 mPosition;
    glm::vec3 mTarget;
};

} // Scene
} // ACGL

#endif // ACGL_SCENE_CAMERA_HH
