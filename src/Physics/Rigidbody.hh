#ifndef RIGIDBODY_HH
#define RIGIDBODY_HH

#include <ACGL/OpenGL/Objects.hh>
#include <ACGL/OpenGL/GL.hh>
#include <ACGL/OpenGL/Tools.hh>
#include <ACGL/OpenGL/Managers.hh>
#include <ACGL/Scene/MatrixStack.hh>
#include <ACGL/Math/Math.hh>

#include "Object.hh"

using namespace ACGL::Math;
using namespace ACGL::Utils;
using namespace ACGL::OpenGL;
using namespace ACGL::Resource;
using namespace ACGL::Scene;
using namespace std;

struct Collision
{
    Collision() { isWall = false; isCollision = false;}
    bool isCollision;
    bool isWall;
    vec3 point;
    vec3 normal;
};

class RigidBody
{
public:
    RigidBody(vec3 initPos, float mass, char* aPathBody, float aElasticity = 1.0f);

    void nextStep(double timeStep, float gravity, float damping, vec3 inputForce = vec3(), vec3 inputTorque = vec3());
    void undoNextStep();
    void undoPositions();
    void undoVelocities();
    void updateVelocities();
    void updatePositions(float timeStep);

    // Getters
    vec3 getPos() { return _pos; }
    vec3 getPos0() { return _pos0; }
    float getPosX() { return _pos.x; }
    float getPosY() { return _pos.y; }
    float getPosZ() { return _pos.z; }
    vec3 getCenterMass() { return _centerMass; }
    vec3 getVel() { return _vel; }
    vec3 getVel0() { return _vel0; }
    float getMass() { return _mass; }
    vec3 getAngle() { return _angle; }
    vec3 getAngle0() { return _angle0; }
    float getAngleX() { return _angle.x; }
    float getAngleY() { return _angle.y; }
    float getAngleZ() { return _angle.z; }
    vec3 getAngVel() { return _angVel; }
    vec3 getAngVel0() { return _angVel0; }
    vec3 getInertia() { return _inertia; }
    vector<vec3>* getImpulseV() { return &impulseV; }
    vector<vec3>* getImpulseW() { return &impulseW; }
    bool isImpulse() { return (impulseV.size() > 0); }
    float getElasticity() { return _elasticity; }
    Object* getObj() { return objBody; }
    ACGL::OpenGL::ConstSharedRenderObject getRender() { return renderObj; }

    // Setters
    void setPos(vec3 pos) { _pos = pos; }
    void setPos0(vec3 pos0) { _pos0 = pos0; }
    void updatePos(vec3 newPos) { _pos += newPos; }
    void updatePosX(float x) { _pos.x += x; }
    void updatePosY(float y) { _pos.y += y; }
    void updatePosZ(float z) { _pos.z += z; }
    void setPosX(float posX) { _pos.x = posX; }
    void setPosY(float posY) { _pos.y = posY; }
    void setPosZ(float  posZ) { _pos.z = posZ; }
    void setCenterMass(vec3 center) { _centerMass = center; }
    void setVel(vec3 vel) { _vel = vel; }
    void updateVel(vec3 vel) { _vel += vel; }
    void setVel0(vec3 vel0) { _vel0 = vel0; }
    void updateVel0(vec3 vel0) { _vel0 += vel0; }
    void setMass(float mass) { _mass = mass; }
    void setAngle(vec3 angle) { _angle = angle; }
    void updateAngle(vec3 angle) { _angle += angle; }
    void setAngle0(vec3 angle0) { _angle0 = angle0; }
    void setAngleX(float angleX) { _angle.x = angleX; }
    void updateAngleX(float rotate) { _angle.x += rotate; }
    void setAngleY(float angleY) { _angle.y = angleY; }
    void updateAngleY(float rotate) { _angle.y += rotate; }
    void setAngleZ(float angleZ) { _angle.z = angleZ; }
    void updateAngleZ(float rotate) { _angle.z += rotate; }
    void setAngVel(vec3 angVel) { _angVel = angVel; }
    void setAngVel0(vec3 angVel0) { _angVel0 = angVel0; }
    void setInertia(vec3 inertia) { _inertia = inertia; }
    void addImpulseV(vec3 im) { impulseV.push_back(im); }
    void addImpulseW(vec3 im) { impulseW.push_back(im); }
    void resetImpulses() { impulseV.clear(); impulseW.clear(); }
    void setElasticity(float e) { _elasticity = e; }
    void setObj(Object* obj) { objBody = obj; }
    void setRender(ACGL::OpenGL::ConstSharedRenderObject render) { renderObj = render; }


    void initRender(SharedUniformMatrix3f mpUniformNormalMatrix, SharedUniformMatrix4f mpUniformModelViewMatrix,
                    SharedUniformMatrix4f mpUniformModelViewProjectionMatrix, SharedTexture pTextureScreenSizeColor,
                    SharedTexture pTextureScreenSizeDepth, char* shader, char* pathTex, vec4 vPositionLight, vec3 vAttenuationLight);

    void initRender(SharedUniformMatrix3f mpUniformNormalMatrix, SharedUniformMatrix4f mpUniformModelViewMatrix,
                    SharedUniformMatrix4f mpUniformModelViewProjectionMatrix, SharedTexture pTextureScreenSizeColor,
                    SharedTexture pTextureScreenSizeDepth, char* shader, char* pathTex, char* pathTexNormal, vec4 vPositionLight, vec3 vAttenuationLight);

    // Returns true if BB collide (Both bodies have a sphere bounding box)
    Collision isCollisionSpheres(RigidBody* sphere);
    // Returns true if BB collide (Both bodies have a AABB)
    Collision isCollisionAABoxes(RigidBody* cube);
    // Returns true if BB collide (Both BB's might rotate)
    Collision isCollisionRotBoxes(RigidBody* cube);
    // Check collision between a box and a sphere BB's
    Collision isCollisionBoxSphere(RigidBody* sphere);

    // Returns true if point 'p' collides with the object described by the collision tree
    Collision isCollisionTree(vec3 p);
    Collision isCollisionTreeRecursive(BoxTree* bbTree, vec3 p);
    // Check collision between a tree-based BB and a Sphere (robot and ball)
    Collision isCollisionSphereInTree(RigidBody* sphere);
    // Check collision between a tree-based BB and a Sphere (robot and ball)
    Collision isCollisionTreeInSphere(RigidBody* sphere);
    // Check collision between a tree-based BB and a common BB (robot vs flat kick)
    Collision isCollisionTreeInBB(RigidBody* sphere);
    // Check collision between two tree-based BBs (both robots)
    Collision isCollisionTreeTree(RigidBody* treeBB);
    // Check collisions between objects and walls
    Collision isCollisionSphereWall(RigidBody* wall);
    Collision isCollisionBoxWall(RigidBody* wall);
    Collision isCollisionTreeWall(RigidBody* wall);

    // Impulses from collisions
    static void addImpulses(Collision collision, RigidBody* bPoint, RigidBody* bPlane)
    {
        // Elastic component
        float e = 1.0f;
        // Friction
        //vec3 u = vec3(0.1,0.1,0.1);
        //vec3 tangent = cross(cross(collision.normal, (bPoint->getVel0() - bPlane->getVel0())), collision.normal);
        //tangent = tangent / sqrt(tangent.x*tangent.x + tangent.y*tangent.y + tangent.z*tangent.z + 0.00001f);

        vec3 j;
        vec3 R1 = collision.point - (RigidBody::rotateYaxis(bPoint->getObj()->boundingBox().centreBox(),bPoint->getAngleY())+bPoint->getPos());
        vec3 crossP1 = cross(R1,collision.normal);
        vec3 R2 = collision.point - (RigidBody::rotateYaxis(RigidBody::rotateZaxis(bPlane->getObj()->boundingBox().centreBox()-vec3(1.0f,1.0f,0.0f),bPlane->getAngleZ())+vec3(1.0f,1.0f,0.0f),bPlane->getAngleY())+bPlane->getPos());
        vec3 crossP2 = cross(R2,collision.normal);

        if(collision.isWall)
        {
            e = std::min(bPoint->getElasticity(),bPlane->getElasticity());
            j = ( -(1.0f + e)*bPoint->getVel0()*collision.normal )
                    / ( (1.0f/bPoint->getMass()) + crossP1*crossP1/bPoint->getInertia() );
        }
        else
        {
            bPoint->updatePos(0.25f*collision.normal);
            bPlane->updatePos(-0.25f*collision.normal);

            vec3 jTop, jBottom;
            jTop = -(1.0f + e)*(bPoint->getVel0() - bPlane->getVel0())*collision.normal;
            jBottom = (1.0f/bPoint->getMass()) + (1.0f/bPlane->getMass())
                      + collision.normal*(cross(crossP1/bPoint->getInertia(),R1) + collision.normal*cross(crossP2/bPlane->getInertia(),R2));
            j = jTop / jBottom;
            
            vec3 imV2 = bPlane->getVel() - (j*collision.normal /*+ (u*j*tangent)*/) / bPlane->getMass();
            if(abs(imV2.x) > 0.1 || abs(imV2.y) > 0.1 || abs(imV2.z) > 0.1)
                bPlane->addImpulseV(imV2);
            else
                bPlane->addImpulseV(vec3());
            vec3 imW2 = bPlane->getAngVel() - (cross(R2,(j*collision.normal /*+ (u*j*tangent)*/))/bPlane->getInertia());
            bPlane->addImpulseW(imW2);
        }

        vec3 imV1 = bPoint->getVel() + (j*collision.normal /*+ (u*j*tangent)*/) / bPoint->getMass();
        if(abs(imV1.x) > 0.1 || abs(imV1.y) > 0.1 || abs(imV1.z) > 0.1)
            bPoint->addImpulseV(imV1);
        else
            bPoint->addImpulseV(vec3());
        vec3 imW1 = bPoint->getAngVel() + (cross(R1,(j*collision.normal /*+ (u*j*tangent)*/))/bPoint->getInertia());
        bPoint->addImpulseW(imW1);
    }

    static vec3 rotateYaxis(vec3 p, float angle)
    {
        vec3 out;
        out.x = p.x*cos(-angle*3.1416/180.0) - p.z*sin(-angle*3.1416/180.0);
        out.y = p.y;
        out.z = p.x*sin(-angle*3.1416/180.0) + p.z*cos(-angle*3.1416/180.0);
        return out;
    }

    static vec3 rotateZaxis(vec3 p, float angle)
    {
        vec3 out;
        out.x = p.x*cos(angle*3.1416/180.0) - p.y*sin(angle*3.1416/180.0);
        out.y = p.x*sin(angle*3.1416/180.0) + p.y*cos(angle*3.1416/180.0);
        out.z = p.z;
        return out;
    }

    static float angleYvectors(vec3 v1, vec3 v2)
    {
        v1 = v1 != vec3() ? normalize(v1) : vec3();
        v2 = v2 != vec3() ? normalize(v2) : vec3();
        float dotP = v1.x*v2.x + v1.y*v2.y + v1.z*v2.z;
        float angle = acos(dotP)*180.0f/3.1416f;
        vec3 crossP = cross(v1,v2);
        return crossP.y > 0.0f ? angle : -angle;
    }

    static float norm(vec3 v)
    {
         return sqrt(v.x*v.x+v.y*v.y+v.z*v.z);
    }

private:

    /* Attributes for physical based movements */

    // - Body World coordinate position
    vec3 _pos, _pos0;

    // - Position center of mass
    vec3 _centerMass;
    // - Velocity center of mass
    vec3 _vel, _vel0;
    // - Mass of the body
    float _mass;

    // - Angle of rotation
    vec3 _angle, _angle0;
    // - Angular velocity
    vec3 _angVel, _angVel0;
    // - Moment of inertia (mass of rotational physics)
    vec3 _inertia;

    // - list of current impulses
    vector<vec3> impulseV;
    vector<vec3> impulseW;

    // - elasticity to collisions
    float _elasticity;

    // Mesh
    Object* objBody;
    char* pathBody;
    // Render object for drawing
    ACGL::OpenGL::ConstSharedRenderObject renderObj;
};

#endif // RIGIDBODY_HH


