////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2011, Computer Graphics Group RWTH Aachen University         //
// All rights reserved.                                                       //
////////////////////////////////////////////////////////////////////////////////

#version 150

uniform vec3 uFirstColor;
uniform vec3 uSecondColor;

in vec2 vTexCoordScreen;

out vec4 fFragDataGradient;

void main (void)
{
    fFragDataGradient = mix(vec4(uFirstColor,1.0), vec4(uSecondColor,1.0), vTexCoordScreen.y);
}
