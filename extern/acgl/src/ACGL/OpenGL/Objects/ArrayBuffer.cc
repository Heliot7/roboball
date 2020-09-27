////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2011, Computer Graphics Group RWTH Aachen University         //
// All rights reserved.                                                       //
////////////////////////////////////////////////////////////////////////////////

#include <ACGL/OpenGL/Objects/ArrayBuffer.hh>

using namespace ACGL;
using namespace ACGL::OpenGL;

int_t ArrayBuffer::getAttributeIndexByName(const std::string& _nameInArray) const
{
    for(AttributeVec::size_type i = 0; i < mAttributes.size(); ++i)
        if(mAttributes[i].name == _nameInArray)
            return i;
    return -1;
}

void ArrayBuffer::render(void) const
{
    glBindBuffer(GL_ARRAY_BUFFER, mObjectName);
    for(AttributeVec::size_type i = 0; i < mAttributes.size(); ++i)
    {
        setAttributePointer(i, i);
        glEnableVertexAttribArray(i);
        openGLRareError();
    }
    draw();
    for(AttributeVec::size_type i = 0; i < mAttributes.size(); ++i)
    {
        glDisableVertexAttribArray(i);
        openGLRareError();
    }
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
