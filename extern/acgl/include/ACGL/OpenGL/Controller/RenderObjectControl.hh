////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2011, Computer Graphics Group RWTH Aachen University         //
// All rights reserved.                                                       //
////////////////////////////////////////////////////////////////////////////////

#ifndef ACGL_OPENGL_CONTROLLER_RENDEROBJECTCONTROL_HH
#define ACGL_OPENGL_CONTROLLER_RENDEROBJECTCONTROL_HH

#include <ACGL/ACGL.hh>
#include <ACGL/OpenGL/GL.hh>
#if (ACGL_OPENGL_VERSION >= 30)

#include <ACGL/Resource/BasicCreateController.hh>
#include <ACGL/OpenGL/Objects/RenderObject.hh>

namespace ACGL{
namespace OpenGL{

class RenderObjectControl : public Resource::BasicCreateController<RenderObject>
{
    // ========================================================================================================= \/
    // ============================================================================================ CONSTRUCTORS \/
    // ========================================================================================================= \/
public:
    RenderObjectControl(
        const ConstSharedVertexBufferObject& _vertexBufferObject,
        const ConstSharedShaderProgramObject& _shaderProgramObject)
    :   mpVertexBufferObject(_vertexBufferObject),
        mpShaderProgramObject(_shaderProgramObject),
        mpFrameBufferObject()
    {}

    RenderObjectControl(
        const ConstSharedVertexBufferObject& _vertexBufferObject,
        const ConstSharedShaderProgramObject& _shaderProgramObject,
        const ConstSharedFrameBufferObject& _frameBufferObject)
    :   mpVertexBufferObject(_vertexBufferObject),
        mpShaderProgramObject(_shaderProgramObject),
        mpFrameBufferObject(_frameBufferObject)
    {}
    virtual ~RenderObjectControl(void) {}

    // ==================================================================================================== \/
    // ============================================================================================ GETTERS \/
    // ==================================================================================================== \/
public:
    inline RenderObjectControl& vertexBufferObject  (const ConstSharedVertexBufferObject&  _vertexBufferObject)  { mpVertexBufferObject  = _vertexBufferObject;  return *this; }
    inline RenderObjectControl& shaderProgramObject (const ConstSharedShaderProgramObject& _shaderProgramObject) { mpShaderProgramObject = _shaderProgramObject; return *this; }
    inline RenderObjectControl& frameBufferObject   (const ConstSharedFrameBufferObject&   _frameBufferObject)   { mpFrameBufferObject   = _frameBufferObject;   return *this; }

    // ===================================================================================================== \/
    // ============================================================================================ OVERRIDE \/
    // ===================================================================================================== \/
public:
    virtual SharedRenderObject create(void)
    {
        SharedRenderObject renderObject(new RenderObject(mpVertexBufferObject, mpShaderProgramObject, mpFrameBufferObject));
        return renderObject;
    }

    // =================================================================================================== \/
    // ============================================================================================ FIELDS \/
    // =================================================================================================== \/
protected:
    ConstSharedVertexBufferObject  mpVertexBufferObject;
    ConstSharedShaderProgramObject mpShaderProgramObject;
    ConstSharedFrameBufferObject   mpFrameBufferObject;
};

} // OpenGL
} // ACGL

#endif // GL >= 3.0

#endif // ACGL_OPENGL_CONTROLLER_TEXTURECONTROL_HH
