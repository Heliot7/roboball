////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2011, Computer Graphics Group RWTH Aachen University         //
// All rights reserved.                                                       //
////////////////////////////////////////////////////////////////////////////////

#ifndef ACGL_OPENGL_OBJECTS_SHADER_HH
#define ACGL_OPENGL_OBJECTS_SHADER_HH

/*
 * A Shader ist just one OpenGL shader like a fragment or vertex shader. To use these
 * a ShaderProgram is needed that links together multiple Shaders for the different
 * pipelinestages.
 *
 * So normally you want to work with ShaderPrograms instead of Shaders (switch Programs,
 * set uniforms etc).
 */

#include <vector>
#include <string>
#include <tr1/memory>

#include <ACGL/ACGL.hh>

#include <ACGL/Base/Macros.hh>
#include <ACGL/OpenGL/GL.hh>

namespace ACGL{
namespace OpenGL{

class Shader
{
    ACGL_NOT_COPYABLE(Shader)

    // ========================================================================================================= \/
    // ============================================================================================ CONSTRUCTORS \/
    // ========================================================================================================= \/
public:
    Shader(GLenum _type)
    :   mObjectName(0),
        mType(_type)
    {
        mObjectName = glCreateShader(mType);
    }

    virtual ~Shader(void)
    {
        // "DeleteShader will silently ignore the value zero." - GL Spec
        glDeleteShader(mObjectName);
    }
    
    // ==================================================================================================== \/
    // ============================================================================================ GETTERS \/
    // ==================================================================================================== \/
public:
    inline GLuint operator()   (void) const { return mObjectName; }
    inline GLuint getObjectName(void) const { return mObjectName; }
    inline GLenum getType      (void) const { return mType;       }

    // ==================================================================================================== \/
    // ============================================================================================ METHODS \/
    // ==================================================================================================== \/
public:
    bool setFromFile (const std::string &_filename);
    bool setSource   (const std::string &_source  );

protected:
    bool compile (const char *_pProgramText) const;

    // =================================================================================================== \/
    // ============================================================================================ FIELDS \/
    // =================================================================================================== \/
protected:
    GLuint              mObjectName;
    GLenum              mType;
};

ACGL_SHARED_TYPEDEF(Shader)

} // OpenGL
} // ACGL

#endif // ACGL_OPENGL_OBJECTS_SHADER_HH
