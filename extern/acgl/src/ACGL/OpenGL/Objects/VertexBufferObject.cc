////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2011, Computer Graphics Group RWTH Aachen University         //
// All rights reserved.                                                       //
////////////////////////////////////////////////////////////////////////////////

#include <ACGL/OpenGL/Objects/VertexBufferObject.hh>

using namespace ACGL;
using namespace ACGL::OpenGL;

int_t VertexBufferObject::getAttributeIndexByName(const std::string& _name) const
{
    for(AttributeVec::size_type i = 0; i < mAttributes.size(); ++i)
        if(mAttributes[i].name == _name)
            return i;
    return -1;
}

void VertexBufferObject::validate(void) const
{
    GLenum mode      = -1;
    GLsizei elements = -1;

    if(mpElementArrayBuffer)
    {
        mode     = mpElementArrayBuffer->getMode();
        elements = mpElementArrayBuffer->getElements();
    }
    else if(mArrayBuffers.size() > 0)
    {
        mode     = mArrayBuffers[0]->getMode();
        elements = mArrayBuffers[0]->getElements();
    }
    else
    {
        Utils::error() << "VertexBufferObject validation failed: No ArrayBuffer or ElementArrayBuffer specified."<< std::endl;
        return;
    }

    for(ConstArrayBufferVec::size_type k = 0; k < mArrayBuffers.size(); k++)
    {
        if(mArrayBuffers[k]->getMode() != mode)
            Utils::error() << "VertexBufferObject validation failed: ArrayBuffer "<< k << " has different mode."<< std::endl;

        if(mArrayBuffers[k]->getElements() != elements)
            Utils::error() << "VertexBufferObject validation failed: ArrayBuffer "<< k << " has different number of elements."<< std::endl;
    }
}

void VertexBufferObject::enable(void) const
{
    if(mpElementArrayBuffer)
        mpElementArrayBuffer->bind();

    int_t currentBufferID = -1;
    for(AttributeVec::size_type i = 0; i < mAttributes.size(); ++i)
    {
        if(mAttributes[i].bufferID != currentBufferID)
        {
            currentBufferID = mAttributes[i].bufferID;
            mArrayBuffers[currentBufferID]->bind();
        }
        mArrayBuffers[currentBufferID]->setAttributePointer(mAttributes[i].attributeID, mAttributes[i].indexInShader);
        glEnableVertexAttribArray(mAttributes[i].indexInShader);
        openGLRareError();
    }
}

void VertexBufferObject::disable(void) const
{
    int_t currentBufferID = -1;
    for(AttributeVec::size_type i = 0; i < mAttributes.size(); ++i)
    {
        if(mAttributes[i].bufferID != currentBufferID)
        {
            currentBufferID = mAttributes[i].bufferID;
            mArrayBuffers[currentBufferID]->bind();
        }
        glDisableVertexAttribArray(mAttributes[i].indexInShader);
        openGLRareError();
    }
}
