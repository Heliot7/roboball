////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2011, Computer Graphics Group RWTH Aachen University         //
// All rights reserved.                                                       //
////////////////////////////////////////////////////////////////////////////////

#ifndef ACGL_TEMPLATE_WORLD_HH
#define ACGL_TEMPLATE_WORLD_HH

#include <ACGL/Scene/Camera.hh>
#include <ACGL/Scene/CoordinateSystem.hh>
#include <ACGL/OpenGL/Objects.hh>

#include <vector>

enum State {Play, Config, Finish, Goal};

class World
{
public:
    World(int _heightArrayDimension);
    virtual ~World(void);

    void initArrayBufferGrid(void);

    const std::tr1::shared_ptr<ACGL::Scene::CoordinateSystem>& getCoordinateSystem(void) const { return mpCoordinateSystem; }
    const std::tr1::shared_ptr<ACGL::Scene::Camera>& getCamera(void) const { return mpCamera; }

    int   getHeightArrayDimension(void) const { return mHeightArrayDimension; }
    float getHeightAt(int _x, int _y) const { return mpHeightArray[_x][_y]; }

    void setHeightAt(int _x, int _y, float _value) { mpHeightArray[_x][_y] = _value; }

    float INIT_CAM_X;
    float INIT_CAM_Y;
    float INIT_CAM_Z;
    float INIT_PITCH;

private:
    std::tr1::shared_ptr<ACGL::Scene::CoordinateSystem> mpCoordinateSystem;
    std::tr1::shared_ptr<ACGL::Scene::Camera> mpCamera;
    int mHeightArrayDimension;
    std::vector< std::vector<float> > mpHeightArray;
};

#endif // ACGL_TEMPLATE_WORLD_HH
