////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2011, Computer Graphics Group RWTH Aachen University         //
// All rights reserved.                                                       //
////////////////////////////////////////////////////////////////////////////////

#ifndef ACGL_OPENGL_CONTROLLER_ELEMENTARRAYBUFFERCONTROL_HH
#define ACGL_OPENGL_CONTROLLER_ELEMENTARRAYBUFFERCONTROL_HH

#include <ACGL/ACGL.hh>

#include <ACGL/Resource/BasicCreateController.hh>
#include <ACGL/OpenGL/Objects/ElementArrayBuffer.hh>
#include <ACGL/OpenGL/GL.hh>

namespace ACGL{
namespace OpenGL{

class ElementArrayBufferControl : public Resource::BasicCreateController<ElementArrayBuffer>
{
    // ========================================================================================================= \/
    // ============================================================================================ CONSTRUCTORS \/
    // ========================================================================================================= \/
public:
    ElementArrayBufferControl(void)
    :   mUsage(GL_STATIC_DRAW),
        mMode(GL_TRIANGLES),
        mType(GL_UNSIGNED_INT),
        mElements(0),
        mpData(NULL)
    {}
    virtual ~ElementArrayBufferControl() {}

    // ==================================================================================================== \/
    // ============================================================================================ METHODS \/
    // ==================================================================================================== \/
public:
    inline ElementArrayBufferControl& usage (GLenum _usage) { mUsage = _usage; return *this; }
    inline ElementArrayBufferControl& mode  (GLenum _mode)  { mMode = _mode;   return *this; }
    inline ElementArrayBufferControl& type  (GLenum _type)  { mType = _type;   return *this; }

    inline ElementArrayBufferControl& data (const GLvoid* _pData, GLsizei _elements)
    {
        mpData = _pData;
        mElements = _elements;
        return *this;
    }

    // ===================================================================================================== \/
    // ============================================================================================ OVERRIDE \/
    // ===================================================================================================== \/
public:
    virtual SharedElementArrayBuffer create(void)
    {
        SharedElementArrayBuffer elementArrayBuffer(new ElementArrayBuffer(
            mUsage,
            mMode,
            mType));
        if(mpData != NULL)
        {
            elementArrayBuffer->bind();
            elementArrayBuffer->setData(mpData, mElements);
            //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        }
        return elementArrayBuffer;
    }

    // =================================================================================================== \/
    // ============================================================================================ FIELDS \/
    // =================================================================================================== \/
protected:
    GLenum  mUsage;
    GLenum  mMode;
    GLenum  mType;
    GLsizei mElements;
    const GLvoid* mpData;
};

} // OpenGL
} // ACGL

#endif // ACGL_OPENGL_CONTROLLER_ELEMENTARRAYBUFFERCONTROL_HH
