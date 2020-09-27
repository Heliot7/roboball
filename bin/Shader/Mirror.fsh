////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2011, Computer Graphics Group RWTH Aachen University         //
// All rights reserved.                                                       //
////////////////////////////////////////////////////////////////////////////////

#version 150

// lighting:
uniform vec3 uEyeLightPosition;
uniform vec3 uAmbientLight;
uniform vec3 uDiffuseLight;
uniform vec3 uSpecularLight;
uniform vec3 uSceneColor;

// material:
uniform sampler2D uSamplerBaseColor;
uniform vec3      uAmbientMaterial;
uniform vec3      uDiffuseMaterial;
uniform vec3      uSpecularMaterial;
uniform float     uShininessMaterial;

in vec4  vEyeVertexPosition;
in vec3  vEyeNormal;
in vec2  vTexCoord;
in vec3  vLightDir;
in vec3  vCameraVector;
in float vAttenuation;

out vec4 fFragDataColor;

void main()
{
    // Phong lighing
    vec3 finalColor = vec3((uSceneColor.rgb*uAmbientMaterial.rgb) 
				+ (uAmbientLight.rgb*uAmbientMaterial.rgb)*vAttenuation);
    vec3 N = normalize(vEyeNormal);
    vec3 L = normalize(vLightDir);
    float lambertTerm = dot(N,L);
    if(lambertTerm > 0.0)
    {
    	finalColor += uDiffuseLight*uDiffuseMaterial*lambertTerm*vAttenuation;
	vec3 E = normalize(vCameraVector.xzy);
	vec3 R = reflect(-L,N);
	float specular = pow( max(dot(R,E), 0.0), uShininessMaterial);
	finalColor += uSpecularLight*uSpecularMaterial*specular*vAttenuation;
    }

    // Diffuse lighting
    vec3 baseColor = texture(uSamplerBaseColor, vTexCoord).rgb;
    fFragDataColor = vec4(baseColor*finalColor, 0.25);
}
