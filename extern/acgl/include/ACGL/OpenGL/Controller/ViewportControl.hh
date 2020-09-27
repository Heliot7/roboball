////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2011, Computer Graphics Group RWTH Aachen University         //
// All rights reserved.                                                       //
////////////////////////////////////////////////////////////////////////////////

#ifndef ACGL_OPENGL_CONTROLLER_VIEWPORTCONTROL_HH
#define ACGL_OPENGL_CONTROLLER_VIEWPORTCONTROL_HH

#include <ACGL/ACGL.hh>

#include <ACGL/Resource/BasicCreateController.hh>
#include <ACGL/OpenGL/GL.hh>

namespace ACGL{
namespace OpenGL{

class ViewportControl : public Resource::BasicCreateController<Viewport>
{
    // ========================================================================================================= \/
    // ============================================================================================ CONSTRUCTORS \/
    // ========================================================================================================= \/
public:
    ViewportControl()
    :   mOffsetX(0),
        mOffsetY(0),
        mWidth(0),
        mHeight(0)
    {}
    virtual ~ViewportControl(void) {}

    // ==================================================================================================== \/
    // ============================================================================================ GETTERS \/
    // ==================================================================================================== \/
public:
    inline ViewportControl& offset (GLint _offsetX, GLint _offsetY)
    {
        mOffsetX = _offsetX;
        mOffsetY = _offsetY;
        return *this;
    }

    inline ViewportControl& size (GLsizei _width, GLsizei _height)
    {
        mOffsetX = _width;
        mOffsetY = _height;
        return *this;
    }

    // ===================================================================================================== \/
    // ============================================================================================ OVERRIDE \/
    // ===================================================================================================== \/
public:
    virtual SharedViewport create(void)
    {
        SharedViewport viewport(new Viewport(mOffsetX, mOffsetY, mWidth, mHeight));
        return viewport;
    }

    // =================================================================================================== \/
    // ============================================================================================ FIELDS \/
    // =================================================================================================== \/
protected:
    GLint   mOffsetX;
    GLint   mOffsetY;
    GLsizei mWidth;
    GLsizei mHeight;
};

} // OpenGL
} // ACGL

#endif // ACGL_OPENGL_CONTROLLER_TEXTURECONTROL_HH
