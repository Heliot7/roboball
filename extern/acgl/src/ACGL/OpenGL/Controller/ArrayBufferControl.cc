////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2011, Computer Graphics Group RWTH Aachen University         //
// All rights reserved.                                                       //
////////////////////////////////////////////////////////////////////////////////

#include <ACGL/OpenGL/Controller/ArrayBufferControl.hh>

using namespace ACGL::OpenGL;

SharedArrayBuffer ArrayBufferControl::create(void)
{
    SharedArrayBuffer arrayBuffer(new ArrayBuffer(
        mUsage,
        mMode));
    for(AttributeDefineVec::size_type i = 0; i < mAttributeDefines.size(); i++)
    {
        arrayBuffer->attachAttribute(
            mAttributeDefines[i].name,
            mAttributeDefines[i].type,
            mAttributeDefines[i].dimension,
            mAttributeDefines[i].normalized);
    }
    if(mpData != NULL)
    {
        arrayBuffer->bind();
        arrayBuffer->setData(mpData, mElements);
        //glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
    return arrayBuffer;
}
