////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2011, Computer Graphics Group RWTH Aachen University         //
// All rights reserved.                                                       //
////////////////////////////////////////////////////////////////////////////////

#include <ACGL/OpenGL/Controller/VertexBufferObjectControl.hh>

using namespace ACGL::OpenGL;

SharedVertexBufferObject VertexBufferObjectControl::create(void)
{
    /*
    GLenum mode = GL_TRIANGLES;
    GLsizei elements = 0;
    if(mpElementArrayBuffer)
    {
        mode = mpElementArrayBuffer->getMode();
        elements = mpElementArrayBuffer->getElements();
    }
    else if(mArrayBuffers.size() > 0 && mArrayBuffers[0])
    {
        mode = mArrayBuffers[0]->getMode();
        elements = mArrayBuffers[0]->getElements();
    }
    */

    SharedVertexBufferObject vertexBuffer(new VertexBufferObject());

    vertexBuffer->setElementArrayBuffer(mpElementArrayBuffer);

    for(VertexBufferObject::ConstArrayBufferVec::size_type i = 0; i < mArrayBuffers.size(); i++)
    {
        vertexBuffer->attachArrayBuffer(mArrayBuffers[i]);
    }

    for(AttributeDefineVec::size_type i = 0; i < mAttributeDefines.size(); i++)
    {
#if (ACGL_OPENGL_VERSION >= 30)
        if(mpShaderProgram)
        {
            vertexBuffer->attachAttribute(
                mAttributeDefines[i].name,
                mAttributeDefines[i].bufferID,
                mAttributeDefines[i].attributeName,
                mpShaderProgram->getAttributeLocation(mAttributeDefines[i].attributeName));
        }
        else
#endif
        {
            vertexBuffer->attachAttribute(
                mAttributeDefines[i].name,
                mAttributeDefines[i].bufferID,
                mAttributeDefines[i].attributeName,
                i);
        }
    }

    return vertexBuffer;
}
