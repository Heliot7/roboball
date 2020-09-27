////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2011, Computer Graphics Group RWTH Aachen University         //
// All rights reserved.                                                       //
////////////////////////////////////////////////////////////////////////////////

#include <ACGL/OpenGL/Objects/Shader.hh>
#include <ACGL/OpenGL/Tools.hh>
#include <ACGL/Base/StringOperations.hh>

#include <iostream>
#include <fstream>

using namespace ACGL::Base;
using namespace ACGL::Utils;
using namespace ACGL::OpenGL;

bool Shader::setFromFile(const std::string& _filename)
{
    std::string line = "";
    std::string fileContent = "";
    
    std::ifstream fileStream(_filename.c_str(), std::ifstream::in);
    
    if(fileStream.is_open())
    {
        while (fileStream.good())
        {
            std::getline(fileStream,line);
            fileContent += line + "\n";
        }
        fileStream.close();
    }
    else
    {
        error() << "Failed to open file: " << _filename << std::endl;
        return false;
    }
    
    return setSource(fileContent);
}

bool Shader::setSource(const std::string& _source)
{
    return compile(_source.c_str());
}

bool Shader::compile(const char* _pProgramText) const
{
    glShaderSource(mObjectName, 1, &_pProgramText, NULL); // can't create OpenGL errors
    glCompileShader(mObjectName);
    
#ifdef ACGL_CHECK_CRITICAL_GL_ERRORS
    // problems with the shader creation are always a bad thing...
    // from here on only error checks are performed:
    //
    if ( openGLRareErrorOccured() )
    {
        error() << "glCompileShader failed, that can only mean, that the object name used is not a valid shader object!" << std::endl;
        return false;
    }

    // check for shader compile errors:
    GLint shaderError;
    glGetShaderiv(mObjectName, GL_COMPILE_STATUS, &shaderError);
    if(shaderError != GL_TRUE)
    {
        // yes, errors
        error() << "Shader compile error: " << std::endl;
    }

    // a log gets always printed (could be warnings)
    GLsizei length = 0;
    glGetShaderiv(mObjectName, GL_INFO_LOG_LENGTH, &length);
    if(length > 1)
    {
        // a compile log can get produced even if there were no errors, but warnings!
        GLchar* pInfo = new char[length + 1];
        glGetShaderInfoLog(mObjectName,  length, &length, pInfo);
        error() << "Compile log: " << std::string(pInfo) << std::endl;
        delete[] pInfo;
    }
    openGLRareError(); // glGetShader- calls normaly shoudn't create errors
    return (shaderError == GL_TRUE); // return true if we encountered no errors
#else
    return true; // if no error checking was done we assume it went ok
#endif
}
