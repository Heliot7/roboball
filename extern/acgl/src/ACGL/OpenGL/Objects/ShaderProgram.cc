////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2011, Computer Graphics Group RWTH Aachen University         //
// All rights reserved.                                                       //
////////////////////////////////////////////////////////////////////////////////

#include <ACGL/OpenGL/Objects/ShaderProgram.hh>
#include <ACGL/OpenGL/Tools.hh>

using namespace ACGL::OpenGL;
using namespace ACGL::Base;
using namespace ACGL::Utils;

bool ShaderProgram::link(void) const
{
    glLinkProgram(mObjectName);

#ifdef ACGL_CHECK_CRITICAL_GL_ERRORS
    if ( openGLRareErrorOccured() )
    {
        // it's uncommon that glLinkProgram creates errors,
        // linking errors create no gl errors but a GL_LINK_STATUS of GL_FALSE
        return false;
    }

    // check for program link errors:
    GLint programError;
    glGetProgramiv(mObjectName, GL_LINK_STATUS, &programError);

    if (programError != GL_TRUE)
    {
        // yes, errors :-(
        error() << "Program could not get linked:" << std::endl;
    }

    GLsizei length = 0;
    glGetProgramiv(mObjectName, GL_INFO_LOG_LENGTH, &length);
    if (length > 1)
    {
        // error log or warnings:
        GLchar* pInfo = new char[length + 1];
        glGetProgramInfoLog(mObjectName,  length, &length, pInfo);
        openGLRareError();
        warning() << "Linker log: " << std::string(pInfo) << std::endl;
        delete[] pInfo;
        return (programError == GL_TRUE); // if the log contains only warnings we return true
    }
#endif
    return true;
}
