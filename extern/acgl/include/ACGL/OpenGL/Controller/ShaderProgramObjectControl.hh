////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2011, Computer Graphics Group RWTH Aachen University         //
// All rights reserved.                                                       //
////////////////////////////////////////////////////////////////////////////////

#ifndef ACGL_OPENGL_CONTROLLER_SHADERPROGRAMOBJECTCONTROL_HH
#define ACGL_OPENGL_CONTROLLER_SHADERPROGRAMOBJECTCONTROL_HH

#include <ACGL/ACGL.hh>

#include <ACGL/Resource/FileController.hh>
#include <ACGL/OpenGL/Objects/ShaderProgramObject.hh>
#include <ACGL/OpenGL/GL.hh>

#include <vector>

namespace ACGL{
namespace OpenGL{

class ShaderProgramObjectControl : public Resource::BasicCreateController<ShaderProgramObject>
{
    // ==================================================================================================== \/
    // ============================================================================================ STRUCTS \/
    // ==================================================================================================== \/
public:
    struct UniformAttachmentDefine
    {
        std::string name;
        ConstSharedUniform uniform;
    };

    struct UniformTextureAttachmentDefine
    {
        std::string name;
        ConstSharedUniformTexture uniformTexture;
    };

    // ===================================================================================================== \/
    // ============================================================================================ TYPEDEFS \/
    // ===================================================================================================== \/
public:
    typedef std::vector< UniformAttachmentDefine >        UniformAttachmentDefineVec;
    typedef std::vector< UniformTextureAttachmentDefine > UniformTextureAttachmentDefineVec;

    // ========================================================================================================= \/
    // ============================================================================================ CONSTRUCTORS \/
    // ========================================================================================================= \/
public:
    ShaderProgramObjectControl(const ConstSharedShaderProgram& _shaderProgram)
    :   Resource::BasicCreateController<ShaderProgramObject>(),
        mShaderProgram(_shaderProgram),
        mUniformAttachmentDefines(),
        mUniformTextureAttachmentDefines()
    {}
    virtual ~ShaderProgramObjectControl(void) {}

    // ==================================================================================================== \/
    // ============================================================================================ METHODS \/
    // ==================================================================================================== \/
public:
    inline ShaderProgramObjectControl& shaderProgram (const ConstSharedShaderProgram& _shaderProgram) { mShaderProgram = _shaderProgram; return *this; }

    inline ShaderProgramObjectControl& uniform (const std::string& _name, const ConstSharedUniform& _uniform)
    {
        UniformAttachmentDefine u = {_name, _uniform};
        mUniformAttachmentDefines.push_back(u);
        return *this;
    }

    inline ShaderProgramObjectControl& uniformTexture (const std::string& _name, const ConstSharedUniformTexture& _uniformTexture)
    {
        UniformTextureAttachmentDefine u = {_name, _uniformTexture};
        mUniformTextureAttachmentDefines.push_back(u);
        return *this;
    }

    // ===================================================================================================== \/
    // ============================================================================================ OVERRIDE \/
    // ===================================================================================================== \/
public:
    virtual SharedShaderProgramObject create(void);

    // =================================================================================================== \/
    // ============================================================================================ FIELDS \/
    // =================================================================================================== \/
protected:
    ConstSharedShaderProgram          mShaderProgram;
    UniformAttachmentDefineVec        mUniformAttachmentDefines;
    UniformTextureAttachmentDefineVec mUniformTextureAttachmentDefines;
};

} // OpenGL
} // ACGL

#endif // ACGL_OPENGL_CONTROLLER_SHADERPROGRAMOBJECTCONTROL_HH
