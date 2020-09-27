////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2011, Computer Graphics Group RWTH Aachen University         //
// All rights reserved.                                                       //
////////////////////////////////////////////////////////////////////////////////

#version 150

uniform sampler2DRect uSampleImage;

out vec4 fFragDataColor;

void main(void)
{
    fFragDataColor = texture(uSampleImage, gl_FragCoord.xy);
}
