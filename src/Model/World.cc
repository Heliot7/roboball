////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2011, Computer Graphics Group RWTH Aachen University         //
// All rights reserved.                                                       //
////////////////////////////////////////////////////////////////////////////////

#include "World.hh"

#include <ACGL/OpenGL/Controller.hh>

World::World(int _heightArrayDimension)
:   mpCoordinateSystem(new ACGL::Scene::CoordinateSystem(100,5)),
    mpCamera(new ACGL::Scene::Camera()),
    mHeightArrayDimension(_heightArrayDimension),
    mpHeightArray()
{
    mpHeightArray.resize(mHeightArrayDimension);
    for (int i = 0; i < mHeightArrayDimension; ++i)
      mpHeightArray[i].resize(mHeightArrayDimension);
}

World::~World(void)
{}
