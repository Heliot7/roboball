////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2011, Computer Graphics Group RWTH Aachen University         //
// All rights reserved.                                                       //
////////////////////////////////////////////////////////////////////////////////

#ifndef ACGL_OPENGL_CONTROLLER_RENDERBUFFERCONTROL_HH
#define ACGL_OPENGL_CONTROLLER_RENDERBUFFERCONTROL_HH

#include <ACGL/ACGL.hh>

#include <ACGL/Resource/BasicCreateController.hh>
#include <ACGL/OpenGL/Objects/RenderBuffer.hh>
#include <ACGL/OpenGL/GL.hh>

namespace ACGL{
namespace OpenGL{

class RenderBufferControl : public Resource::BasicCreateController<RenderBuffer>
{
    // ========================================================================================================= \/
    // ============================================================================================ CONSTRUCTORS \/
    // ========================================================================================================= \/
public:
    RenderBufferControl(void)
    :   mWidth(0),
        mHeight(0),
        mSamples(0),
        mInternalFormat()
    {}
    virtual ~RenderBufferControl() {}

    // ==================================================================================================== \/
    // ============================================================================================ METHODS \/
    // ==================================================================================================== \/
public:
    inline RenderBufferControl& size           (GLsizei _width, GLsizei _height)                   { mWidth = _width; mHeight = _height; return *this; }
    inline RenderBufferControl& size           (GLsizei _width, GLsizei _height, GLsizei _samples) { mWidth = _width; mHeight = _height; mSamples = _samples; return *this; }
    inline RenderBufferControl& samples        (GLsizei _samples)                                  { mSamples = _samples; return *this; }
    inline RenderBufferControl& internalFormat (GLenum _internalFormat)                            { mInternalFormat = _internalFormat;  return *this; }

    // ===================================================================================================== \/
    // ============================================================================================ OVERRIDE \/
    // ===================================================================================================== \/
public:
    virtual SharedRenderBuffer create(void)
    {
        SharedRenderBuffer renderBuffer(new RenderBuffer(mInternalFormat));
        renderBuffer->setSize(mWidth, mHeight, mSamples);
        return renderBuffer;
    }

    // =================================================================================================== \/
    // ============================================================================================ FIELDS \/
    // =================================================================================================== \/
protected:
    GLsizei mWidth;
    GLsizei mHeight;
    GLsizei mSamples;
    GLenum  mInternalFormat;
};

} // OpenGL
} // ACGL

#endif // ACGL_OPENGL_CONTROLLER_RENDERBUFFERCONTROL_HH
