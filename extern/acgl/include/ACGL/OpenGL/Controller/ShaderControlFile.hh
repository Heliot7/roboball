////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2011, Computer Graphics Group RWTH Aachen University         //
// All rights reserved.                                                       //
////////////////////////////////////////////////////////////////////////////////

#ifndef ACGL_OPENGL_CONTROLLER_SHADERCONTROLFILE_HH
#define ACGL_OPENGL_CONTROLLER_SHADERCONTROLFILE_HH

#include <ACGL/ACGL.hh>

#include <ACGL/Resource/FileController.hh>
#include <ACGL/Base/Settings.hh>
#include <ACGL/OpenGL/Objects/Shader.hh>
#include <ACGL/OpenGL/GL.hh>

namespace ACGL{
namespace OpenGL{

class ShaderControlFile : public Resource::FileController<Shader>
{
    // ========================================================================================================= \/
    // ============================================================================================ CONSTRUCTORS \/
    // ========================================================================================================= \/
public:
    ShaderControlFile(const std::string& _filename)
    :   Resource::FileController<Shader>(_filename, Base::Settings::the()->getFullShaderPath()),
        mType(GL_INVALID_ENUM)
    {}
    virtual ~ShaderControlFile(void) {}

    // ==================================================================================================== \/
    // ============================================================================================ METHODS \/
    // ==================================================================================================== \/
public:
    inline ShaderControlFile& type (GLenum _type) { mType = _type;  return *this; }

    // ===================================================================================================== \/
    // ============================================================================================ OVERRIDE \/
    // ===================================================================================================== \/
public:
    virtual SharedShader create(void);
    virtual bool update(SharedShader& shader);

    // =================================================================================================== \/
    // ============================================================================================ FIELDS \/
    // =================================================================================================== \/
protected:
    GLenum mType;
};

} // OpenGL
} // ACGL

#endif // ACGL_OPENGL_CONTROLLER_SHADERCONTROLFILE_HH
