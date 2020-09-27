////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2011, Computer Graphics Group RWTH Aachen University         //
// All rights reserved.                                                       //
////////////////////////////////////////////////////////////////////////////////

#ifndef ACGL_OPENGL_OBJECTS_RENDEROBJECT_HH
#define ACGL_OPENGL_OBJECTS_RENDEROBJECT_HH

/*
 * A RenderObject combines a FrameBuffer to draw to, a ShaderProgramObject
 * to draw with and a VertexBufferObject to name what to draw.
 *
 * Instead of setting those objects individually and hoping that they match
 * a RenderObject can take care of that.
 *
 *
 *
 * The RenderObject build around automatic mapping of VBOs to Shader-Attribute-Names
 * to Shader-Outputs to Texture-Names.
 * The needed calls (and GLSL in/out type shader-inputs/outputs) are not supported
 * on GL prior to 3.0, so RenderObject is not available on older GL implementations.
 * A similar class however could get implemented for GL 2.1 and GLES 2.0...
 */

#include <ACGL/ACGL.hh>
#include <ACGL/OpenGL/GL.hh>
#if (ACGL_OPENGL_VERSION >= 30)

#include <vector>
#include <string>
#include <tr1/memory>
#include <iostream>

#include <ACGL/Base/Macros.hh>

#include <ACGL/OpenGL/Objects/VertexBufferObject.hh>
#include <ACGL/OpenGL/Objects/FrameBufferObject.hh>
#include <ACGL/OpenGL/Objects/ShaderProgramObject.hh>
#include <ACGL/OpenGL/Objects/Viewport.hh>

namespace ACGL{
namespace OpenGL{

class RenderObject
{
    ACGL_NOT_COPYABLE(RenderObject)
    // ==================================================================================================== \/
    // ============================================================================================ STRUCTS \/
    // ==================================================================================================== \/
private:
    struct AttributeMapping
    {
        //! The attributeID stores the attribute index within the vbo.
        int_t attributeID;
        //! The attributeLocation comes from the shader
        int_t attributeLocation;
    };

    // ===================================================================================================== \/
    // ============================================================================================ TYPEDEFS \/
    // ===================================================================================================== \/
private:
    typedef std::vector< AttributeMapping > AttributeMappingVec;

    // ========================================================================================================= \/
    // ============================================================================================ CONSTRUCTORS \/
    // ========================================================================================================= \/
public:
    RenderObject(ConstSharedVertexBufferObject _vertexBufferObject,
          ConstSharedShaderProgramObject _shaderProgram,
          ConstSharedFrameBufferObject _frameBufferObject)
    :   mpVertexBufferObject(_vertexBufferObject),
        mpShaderProgramObject(_shaderProgram),
        mpFrameBufferObject(_frameBufferObject),
        mAttributeMappings(),
        mpDrawBuffers(NULL)
    {
        updateMappings();
    }

    RenderObject(ConstSharedVertexBufferObject _vertexBufferObject,
          ConstSharedShaderProgramObject _shaderProgram)
    :   mpVertexBufferObject(_vertexBufferObject),
        mpShaderProgramObject(_shaderProgram),
        mpFrameBufferObject(),
        mAttributeMappings(),
        mpDrawBuffers(NULL)
    {
        updateMappings();
    }

    virtual ~RenderObject(void)
    {
        delete[](mpDrawBuffers);
    }

    // ==================================================================================================== \/
    // ============================================================================================ GETTERS \/
    // ==================================================================================================== \/
public:
    inline ConstSharedVertexBufferObject  getVertexBufferObject  (void) const { return mpVertexBufferObject;  }
    inline ConstSharedFrameBufferObject   getFrameBufferObject   (void) const { return mpFrameBufferObject;   }
    inline ConstSharedShaderProgramObject getShaderProgramObject (void) const { return mpShaderProgramObject; }

    // ==================================================================================================== \/
    // ============================================================================================ METHODS \/
    // ==================================================================================================== \/
public:
    void updateMappings (void);

    void bindFrameBufferObject     (void) const;
    void useShaderProgramObject    (void) const;
    void enableVertexBufferObject  (void) const;
    void disableVertexBufferObject (void) const;

    inline void enable(void) const
    {
        bindFrameBufferObject();
        useShaderProgramObject();
        enableVertexBufferObject();
    }

    inline void disable(void) const
    {
        disableVertexBufferObject();
    }

    inline void draw(void) const
    {
        mpVertexBufferObject->draw();
    }

    inline void render(void) const
    {
        enable();
        draw();
        disable();
    }

    inline void validate (void) const
    {
        mpFrameBufferObject->validate();
        mpVertexBufferObject->validate();
    }

    // =================================================================================================== \/
    // ============================================================================================ FIELDS \/
    // =================================================================================================== \/
protected:
    ConstSharedVertexBufferObject  mpVertexBufferObject;
    ConstSharedShaderProgramObject mpShaderProgramObject;
    ConstSharedFrameBufferObject   mpFrameBufferObject;

    AttributeMappingVec            mAttributeMappings;
    GLuint*                        mpDrawBuffers;
};

ACGL_SHARED_TYPEDEF(RenderObject)

} // OpenGL
} // ACGL

#endif

#endif // ACGL_OPENGL_OBJECTS_RENDEROBJECT_HH
