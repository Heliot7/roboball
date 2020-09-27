////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2011, Computer Graphics Group RWTH Aachen University         //
// All rights reserved.                                                       //
////////////////////////////////////////////////////////////////////////////////

#version 150

in vec4 aPosition;

out vec2 vTexCoordScreen;

void main()
{
    gl_Position     = aPosition;
    vTexCoordScreen = aPosition.xy * 0.5 + 0.5;
}
