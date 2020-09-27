////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2011, Computer Graphics Group RWTH Aachen University         //
// All rights reserved.                                                       //
////////////////////////////////////////////////////////////////////////////////

#version 150

uniform mat3 uNormalMatrix;
uniform mat4 uModelViewMatrix;
uniform mat4 uModelViewProjectionMatrix;

in vec4 aPosition;
in vec3 aNormal;
in vec2 aTexCoord;

out vec4 vEyeVertexPosition;
out vec3 vEyeNormal;
out vec2 vTexCoord;

void main()
{
    // eye space normal:
    vEyeNormal = uNormalMatrix * aNormal;

    // eye space vertex position:
    vEyeVertexPosition = uModelViewMatrix * aPosition;

    // pass texture coordinates
    vTexCoord = aTexCoord;

    // projected vertex position used for the interpolation
    gl_Position  = uModelViewProjectionMatrix * aPosition;
}
