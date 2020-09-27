////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2011, Computer Graphics Group RWTH Aachen University         //
// All rights reserved.                                                       //
////////////////////////////////////////////////////////////////////////////////

#include <ACGL/OpenGL/Objects/VertexArrayObject.hh>
#if (ACGL_OPENGL_VERSION >= 30)

using namespace ACGL;
using namespace ACGL::OpenGL;

bool VertexArrayObject::isValid(void) const
{
    GLenum  mode;
    GLsizei elements = 0;

    if (mAttributes.size() > 0)
    {
        mode     = mAttributes[0].arrayBuffer->getMode();
        elements = mAttributes[0].arrayBuffer->getElements();
    } else {
        Utils::error() << "VertexArrayObject has no attributes attached" << std::endl;
        return false;
    }
    if (mpElementArrayBuffer)
    {
        mode     = mpElementArrayBuffer->getMode();
        elements = mpElementArrayBuffer->getElements();
    }

    for (AttributeVec::size_type i = 0; i < mAttributes.size(); ++i)
    {
        if (mAttributes[0].arrayBuffer->getMode() != mode) {
            Utils::error() << "VertexArrayObject validation failed: Attribute "<< i << " has different mode."<< std::endl;
            return false;
        }

        if (mAttributes[0].arrayBuffer->getElements() != elements) {
            Utils::error() << "VertexArrayObject validation failed: Attribute "<< i << " has different number of elements."<< std::endl;
            return false;
        }
    }

    return true;
}

#endif // (ACGL_OPENGL_VERSION >= 30)
