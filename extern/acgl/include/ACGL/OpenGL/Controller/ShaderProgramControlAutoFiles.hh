////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2011, Computer Graphics Group RWTH Aachen University         //
// All rights reserved.                                                       //
////////////////////////////////////////////////////////////////////////////////

#ifndef ACGL_OPENGL_CONTROLLER_SHADERPROGRAMCONTROLAUTOFILES_HH
#define ACGL_OPENGL_CONTROLLER_SHADERPROGRAMCONTROLAUTOFILES_HH

#include <ACGL/ACGL.hh>

#include <ACGL/Resource/FileController.hh>
#include <ACGL/OpenGL/Objects/ShaderProgram.hh>
#include <ACGL/OpenGL/GL.hh>

#include <vector>

namespace ACGL{
namespace OpenGL{

class ShaderProgramControlAutoFiles : public Resource::FileController<ShaderProgram>
{
    // ========================================================================================================= \/
    // ============================================================================================ CONSTRUCTORS \/
    // ========================================================================================================= \/
public:
    ShaderProgramControlAutoFiles(const std::string& _filename)
    :   Resource::FileController<ShaderProgram>(_filename),
        mAttributeLocations(),
        mFragmentDataLocations()
    {}
    virtual ~ShaderProgramControlAutoFiles(void) {}

    // ==================================================================================================== \/
    // ============================================================================================ METHODS \/
    // ==================================================================================================== \/
public:
    inline ShaderProgramControlAutoFiles& attributeLocation    (const std::string& _attributeName)    { mAttributeLocations.push_back(_attributeName);       return *this; }
    inline ShaderProgramControlAutoFiles& fragmentDataLocation (const std::string& _fragmentDataName) { mFragmentDataLocations.push_back(_fragmentDataName); return *this; }

    // ===================================================================================================== \/
    // ============================================================================================ OVERRIDE \/
    // ===================================================================================================== \/
public:
    virtual SharedShaderProgram create(void);
    virtual bool update(SharedShaderProgram& shaderProgram);

    // =================================================================================================== \/
    // ============================================================================================ FIELDS \/
    // =================================================================================================== \/
protected:
    std::vector<std::string> mAttributeLocations;
    std::vector<std::string> mFragmentDataLocations;
};

} // OpenGL
} // ACGL

#endif // ACGL_OPENGL_CONTROLLER_SHADERPROGRAMCONTROLAUTOFILES_HH
