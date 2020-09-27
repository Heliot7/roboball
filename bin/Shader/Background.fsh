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

in vec4 vEyeVertexPosition;
in vec3 vEyeNormal;
in vec2 vTexCoord;

out vec4 fFragDataColor;

void main()
{
    // instead of Phong: just take color from texture
    vec4 baseColor = texture(uSamplerBaseColor, vTexCoord).rgba;
    //if(baseColor.r < 0.75 && baseColor.g < 0.75 && baseColor.b < 0.75)
    //    fFragDataColor = vec4(baseColor,0.0);
    //else if(baseColor.r < 0.50 && baseColor.g < 0.50 && baseColor.b < 0.50)
    //    fFragDataColor = vec4(baseColor,0.10);
    //else if(baseColor.r < 0.40 && baseColor.g < 0.40 && baseColor.b < 0.40)
    //    fFragDataColor = vec4(baseColor,0.15);
    //else if(baseColor.r < 0.25 && baseColor.g < 0.25 && baseColor.b < 0.25)
    //    fFragDataColor = vec4(baseColor,0.25);
    //else
    //    fFragDataColor = vec4(baseColor,0.75);
    if(baseColor.a == 0.0)
	fFragDataColor = baseColor;
    else
        fFragDataColor = vec4(baseColor.rgb,0.5);
}
