////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2011, Computer Graphics Group RWTH Aachen University         //
// All rights reserved.                                                       //
////////////////////////////////////////////////////////////////////////////////

#include <ACGL/OpenGL/Objects/RenderObject.hh>
#if (ACGL_OPENGL_VERSION >= 30)

#include <ACGL/OpenGL/Tools.hh>
#include <ACGL/Base/StringOperations.hh>

#include <iostream>
#include <fstream>

using namespace ACGL::Base;
using namespace ACGL::Utils;
using namespace ACGL::OpenGL;

void RenderObject::updateMappings (void)
{
    for(VertexBufferObject::AttributeVec::size_type i = 0; i < mpVertexBufferObject->getAttributes().size(); ++i)
    {
        AttributeMapping mapping = {(int_t)i, (int_t)mpShaderProgramObject->getShaderProgram()->getAttributeLocation(mpVertexBufferObject->getAttributes()[i].name)};
        bool inserted = false;
        for (AttributeMappingVec::iterator it = mAttributeMappings.begin(); it < mAttributeMappings.end() && !inserted; it++)
        {
            if(mpVertexBufferObject->getAttributes()[(*it).attributeID].bufferID > mpVertexBufferObject->getAttributes()[mapping.attributeID].bufferID)
            {
                mAttributeMappings.insert(it, mapping);
                inserted = true;
            }
        }

        if(!inserted)
            mAttributeMappings.push_back(mapping);
    }

    if(mpFrameBufferObject)
    {
        mpDrawBuffers = new GLuint[mpFrameBufferObject->getColorAttachments().size()];
        for(FrameBufferObject::AttachmentVec::size_type i = 0; i < mpFrameBufferObject->getColorAttachments().size(); ++i)
            mpDrawBuffers[i] =  GL_COLOR_ATTACHMENT0 + mpShaderProgramObject->getShaderProgram()->getFragmentDataLocation(mpFrameBufferObject->getColorAttachments()[i].name);
    }

}

void RenderObject::bindFrameBufferObject (void) const
{
    if(mpFrameBufferObject)
    {
        mpFrameBufferObject->bind();
        glDrawBuffers(mpFrameBufferObject->getColorAttachments().size(), mpDrawBuffers);
        openGLRareError();
    }
    else
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        openGLRareError();
    }
}

void RenderObject::useShaderProgramObject (void) const
{
    mpShaderProgramObject->use();
}

void RenderObject::enableVertexBufferObject (void) const
{
    if(mpVertexBufferObject->getElementArrayBuffer())
        mpVertexBufferObject->getElementArrayBuffer()->bind();

    int currentArrayBufferID = -1;

    for(AttributeMappingVec::size_type i = 0; i < mAttributeMappings.size(); i++)
    {
        if(mAttributeMappings[i].attributeLocation != -1)
        {
            if(mpVertexBufferObject->getAttributes()[mAttributeMappings[i].attributeID].bufferID != currentArrayBufferID)
            {
                mpVertexBufferObject->getArrayBuffers()[mpVertexBufferObject->getAttributes()[mAttributeMappings[i].attributeID].bufferID]->bind();
                currentArrayBufferID = mpVertexBufferObject->getAttributes()[mAttributeMappings[i].attributeID].bufferID;
            }
            mpVertexBufferObject->setAttributePointer(mAttributeMappings[i].attributeID, mAttributeMappings[i].attributeLocation);
            glEnableVertexAttribArray(mAttributeMappings[i].attributeLocation);
            openGLRareError();
        }
    }
}

void RenderObject::disableVertexBufferObject (void) const
{
    int currentArrayBufferID = -1;
    for(AttributeMappingVec::size_type i = 0; i < mAttributeMappings.size(); i++)
    {
        if(mAttributeMappings[i].attributeLocation != -1)
        {
            if(mpVertexBufferObject->getAttributes()[mAttributeMappings[i].attributeID].bufferID != currentArrayBufferID)
            {
                mpVertexBufferObject->getArrayBuffers()[mpVertexBufferObject->getAttributes()[mAttributeMappings[i].attributeID].bufferID]->bind();
                currentArrayBufferID = mpVertexBufferObject->getAttributes()[mAttributeMappings[i].attributeID].bufferID;
            }
            glDisableVertexAttribArray(mAttributeMappings[i].attributeLocation);
            openGLRareError();
        }
    }
}

#endif
