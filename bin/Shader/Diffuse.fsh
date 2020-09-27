////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2011, Computer Graphics Group RWTH Aachen University         //
// All rights reserved.                                                       //
////////////////////////////////////////////////////////////////////////////////

#version 150

// lighting:
uniform vec3 uAmbientLight;
uniform vec3 uLightColor;
uniform vec3 uEyeLightPosition;

// material:
uniform sampler2D uSamplerBaseColor;
uniform float     uDiffuseMaterialFactor;
uniform float     uSpecularMaterialFactor;
uniform float     uShininessMaterialFactor;

varying float diffuse;

in vec4 vEyeVertexPosition;
in vec3 vEyeNormal;
in vec2 vTexCoord;

out vec4 fFragDataColor;

void main()
{
    // Diffuse lighting
    vec3 baseColor = texture(uSamplerBaseColor, vTexCoord).rgb;
    fFragDataColor = vec4(baseColor*diffuse, 1.0);
}
