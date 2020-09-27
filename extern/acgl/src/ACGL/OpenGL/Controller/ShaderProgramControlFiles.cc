////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2011, Computer Graphics Group RWTH Aachen University         //
// All rights reserved.                                                       //
////////////////////////////////////////////////////////////////////////////////

#include <ACGL/OpenGL/Controller/ShaderProgramControlFiles.hh>
#include <ACGL/OpenGL/Controller/ShaderControlFile.hh>
#include <ACGL/Resource/FileManager.hh>
#include <ACGL/OpenGL/Managers.hh>
#include <ACGL/Base/Settings.hh>
#include <ACGL/Base/FileHelpers.hh>

using namespace ACGL::Base;
using namespace ACGL::OpenGL;

SharedShaderProgram ShaderProgramControlFiles::create(void)
{
    SharedShaderProgram shaderProgram(new ShaderProgram());

    std::vector<std::string>::size_type numberOfFiles = mFileName.size();

    for (std::vector<std::string>::size_type i = 0; i < numberOfFiles; ++i) {
        //mShaderType.push_back( GL_INVALID_VALUE );

        // guess shader type based on the file extension:
        if ( FileHelpers::stringEndsWith(mFileName[i], ".vsh") ) {
            mShaderType[i] = GL_VERTEX_SHADER;
#ifndef ACGL_OPENGL_ES
        // this shader types are not defined for ES
        } else if ( FileHelpers::stringEndsWith(mFileName[i], ".tcsh") ) {
            mShaderType[i] = GL_TESS_CONTROL_SHADER;
        } else if ( FileHelpers::stringEndsWith(mFileName[i], ".tesh") ) {
            mShaderType[i] = GL_TESS_EVALUATION_SHADER;
        } else if ( FileHelpers::stringEndsWith(mFileName[i], ".gsh") ) {
            mShaderType[i] = GL_GEOMETRY_SHADER;
#endif // OpenGL ES
        } else if ( FileHelpers::stringEndsWith(mFileName[i], ".fsh") ) {
            mShaderType[i] = GL_FRAGMENT_SHADER;
        }
    }

    for (std::vector<std::string>::size_type i = 0; i < numberOfFiles; ++i) {
#       ifdef ACGL_CHECK_CRITICAL_GL_ERRORS
        // check for problems:

        if ( mShaderType[i] == GL_INVALID_VALUE ) {
            Utils::error() << "file extension of file " << mFileName[i] << " not recognized - ignored" << std::endl;
        }

        if (! FileHelpers::fileExists( Settings::the()->getFullShaderPath() + mFileName[i] ) ) {
            Utils::warning() << "file " << mFileName[i] << " does not exist - ignored" << std::endl;
            mShaderType[i] = GL_INVALID_VALUE;
        }

        if ( (mShaderType[i] == GL_GEOMETRY_SHADER) && !OpenGL::doesSupportGeometryShader() ) {
            Utils::error() << "file " << mFileName[i] << " ignored, hardware does not support geometry shader" << std::endl;
            mShaderType[i] = GL_INVALID_VALUE;
        }

        if (    ((mShaderType[i] == GL_TESS_CONTROL_SHADER) || (mShaderType[i] == GL_TESS_EVALUATION_SHADER))
             && !OpenGL::doesSupportTessellationShader() ) {
            Utils::error() << "file " << mFileName[i] << " ignored, hardware does not support tessellation shader" << std::endl;
            mShaderType[i] = GL_INVALID_VALUE;
        }
#       endif // critical checks

        // attach shader
        if ( mShaderType[i] != GL_INVALID_VALUE ) {
            ConstSharedShader shader = ShaderFileManager::the()->get(ShaderControlFile( mFileName[i] ).type( mShaderType[i] ));
            if ( shader ) {
                shaderProgram->attachShader( shader );
            } else {
#           ifdef ACGL_CHECK_CRITICAL_GL_ERRORS
                Utils::error() << "could not attach shader " << mFileName[i] << std::endl;
#           endif // critical checks
            }
        }
    }

    setBindings( shaderProgram );

    if(shaderProgram->link())
        return shaderProgram;

    return SharedShaderProgram();
}

void ShaderProgramControlFiles::setBindings(SharedShaderProgram &_shaderProgram)
{
#if (ACGL_OPENGL_VERSION >= 30)
    for (std::vector<std::string>::size_type i = 0; i < mAttributeLocations.size(); ++i) {
        _shaderProgram->bindAttributeLocation(mAttributeLocations[i], i);
    }
    for (std::vector<std::string>::size_type i = 0; i < mFragmentDataLocations.size(); ++i) {
        _shaderProgram->bindFragmentDataLocation(mFragmentDataLocations[i], i);
    }
#else
    if ( (mAttributeLocations.size() > 0) && (mFragmentDataLocations.size() > 0) ) {
        Utils::error() << "can't set explicit attribute/fragdata locations on OpenGL < 3.0 " << std::endl;
    }
#endif
}

bool ShaderProgramControlFiles::update(SharedShaderProgram &_shaderProgram)
{
    bool update = false;

    for (std::vector<std::string>::size_type i = 0; i < mFileName.size(); ++i) {
        if ( mShaderType[i] != GL_INVALID_VALUE ) {
            update |= ShaderFileManager::the()->update( mFileName[i] );
        }
    }

    setBindings( _shaderProgram );

    if (update)
        return _shaderProgram->link();
    return false;
}
