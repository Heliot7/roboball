////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2011, Computer Graphics Group RWTH Aachen University         //
// All rights reserved.                                                       //
////////////////////////////////////////////////////////////////////////////////

#version 150

uniform mat3 uNormalMatrix;
uniform mat4 uModelViewMatrix;
uniform mat4 uModelViewProjectionMatrix;
uniform vec3 uEyeLightPosition;
uniform vec2 uTextureFit;
uniform vec3 uAttenuationLight;

in vec4 aPosition;
in vec3 aNormal;
in vec2 aTexCoord;

out vec4  vEyeVertexPosition;
out vec3  vEyeNormal;
out vec2  vTexCoord;
out vec3  vLightDir;
out vec3  vCameraVector;
out float vAttenuation;

void main()
{
    // Eye space normal:
    vEyeNormal = uNormalMatrix * aNormal;
    // Eye space vertex position:
    vEyeVertexPosition = uModelViewMatrix * aPosition;

    // Calculate vertex light directionswa
    vLightDir = vec3(vec3(0.0,15.0,15.0).xyz - aPosition.xyz);
    // Calculate Camera vector with pixel
    vCameraVector = -vEyeVertexPosition.xyz;

    // Attenuation
    float d = length(vLightDir);
    vAttenuation = 1.0 / (0.2 + uAttenuationLight.y*d + 0.002*d*d);

    // Pass texture coordinates
    vTexCoord.s = aTexCoord.s*uTextureFit.s;
    vTexCoord.t = aTexCoord.t*uTextureFit.t;

    // Projected vertex position used for the interpolation
    gl_Position  = uModelViewProjectionMatrix * aPosition;
}
