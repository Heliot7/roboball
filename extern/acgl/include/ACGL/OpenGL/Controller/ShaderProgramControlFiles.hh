////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2011, Computer Graphics Group RWTH Aachen University         //
// All rights reserved.                                                       //
////////////////////////////////////////////////////////////////////////////////

#ifndef ACGL_OPENGL_CONTROLLER_SHADERPROGRAMCONTROLFILES_HH
#define ACGL_OPENGL_CONTROLLER_SHADERPROGRAMCONTROLFILES_HH

/*
 * Used to create a ShaderProgram from a given set of file names:
 * e.g.:
 *      SharedShaderProgram prog = ShaderProgramControlFiles("file.vsh").andFile("foobar.fsh").create();
 *
 * The shadertype will be guessed by the extensions.
 */

#include <ACGL/ACGL.hh>

#include <ACGL/Resource/FileController.hh>
#include <ACGL/OpenGL/Objects/ShaderProgram.hh>
#include <ACGL/OpenGL/GL.hh>

#include <vector>

namespace ACGL{
namespace OpenGL{

class ShaderProgramControlFiles : public Resource::FileController<ShaderProgram>
{
    // ========================================================================================================= \/
    // ============================================================================================ CONSTRUCTORS \/
    // ========================================================================================================= \/
public:
    //! the filename will also be the name of the resource
    ShaderProgramControlFiles(const std::string& _fileName)
    :   Resource::FileController<ShaderProgram>(_fileName),
        mShaderType(),
        mAttributeLocations(),
        mFragmentDataLocations()
    {
        // only add the first name if it is a valid file name
        if ( _fileName.find( "." ) != std::string::npos )
            andFile( _fileName );
    }
    virtual ~ShaderProgramControlFiles(void) {}

    // ==================================================================================================== \/
    // ============================================================================================ METHODS \/
    // ==================================================================================================== \/
public:
    inline ShaderProgramControlFiles& andFile              (const std::string &_fileName)         { mFileName.push_back( _fileName ); mShaderType.push_back( GL_INVALID_VALUE ); return *this; }
    inline ShaderProgramControlFiles& attributeLocation    (const std::string &_attributeName)    { mAttributeLocations.push_back(_attributeName);       return *this; }
    inline ShaderProgramControlFiles& fragmentDataLocation (const std::string &_fragmentDataName) { mFragmentDataLocations.push_back(_fragmentDataName); return *this; }

    // ===================================================================================================== \/
    // ============================================================================================ OVERRIDE \/
    // ===================================================================================================== \/
public:
    virtual SharedShaderProgram create(void);
    virtual bool update(SharedShaderProgram &_shaderProgram);

    // =================================================================================================== \/
    // ============================================================================================ FIELDS \/
    // =================================================================================================== \/
protected:
    std::vector<GLenum>      mShaderType;
    std::vector<std::string> mFileName;
    std::vector<std::string> mAttributeLocations;
    std::vector<std::string> mFragmentDataLocations;

private:
    // set attribute & fragdata locations prior to shader program linking
    void setBindings(SharedShaderProgram &_shaderProgram);
};

} // OpenGL
} // ACGL

#endif // ACGL_OPENGL_CONTROLLER_SHADERPROGRAMCONTROLFILES_HH
