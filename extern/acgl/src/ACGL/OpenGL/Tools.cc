////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2011, Computer Graphics Group RWTH Aachen University         //
// All rights reserved.                                                       //
////////////////////////////////////////////////////////////////////////////////

#include <ACGL/ACGL.hh>
#include <ACGL/OpenGL/Tools.hh>

namespace ACGL{
namespace OpenGL{

//
// This is a "private" function that should not be called from outside of this file.
//
// glGetIntegerv(GL_MAJOR_VERSION... and glGetIntegerv(GL_MINOR_VERSION... are great, but
// require OpenGL 3.0 and are not supported on ES :-( so the VERSION string has to get parsed...
//
// OpenGL spec:
// The VERSION ... strings are laid out as follows:
// <version number><space><vendor-specific information>
//
// OpenGL ES spec:
// The VERSION string is laid out as follows:
// "OpenGL ES N.M vendor-specific information"
//
// both specs:
// The version number is either of the form major_number.minor_number or
// major_number.minor_number.release_number, where the numbers all have one or more digits.
//
uint32_t privateGetOpenGLVersion( int _type )
{
    static uint32_t OGLminor   = 0;
    static uint32_t OGLmajor   = 0;
    static uint32_t OGLversion = 0;

    if (OGLversion == 0) {
        // calculate the version numbers once:
        // NOTE: similar to GLEW we assume here, that the minor and major numbers
        //       only have one digit. We also ignore release numbers. This will fail e.g. for OpenGL 10.0
        const GLubyte* versionString;
        versionString = glGetString(GL_VERSION);
        if (openGLRareErrorOccured()) {
            ACGL::Utils::error() << "could not query OpenGL version!" << std::endl;
            return false;
        }

        int positionOfFirstDot = 0;
        while ((versionString[positionOfFirstDot] != '\0') && (versionString[positionOfFirstDot] != '.')) ++positionOfFirstDot;

        OGLmajor = versionString[positionOfFirstDot-1] - '0';
        OGLminor = versionString[positionOfFirstDot+1] - '0';

        if (OGLmajor > 9) OGLmajor = 0;
        if (OGLminor > 9) OGLminor = 0;

        OGLversion = OGLmajor*10 + OGLminor;
    }
    switch (_type) {
        case 0: return OGLminor;
        case 1: return OGLmajor;
        default: return OGLversion;
    };
}

uint32_t getOpenGLMinorVersionNumber()
{
    return privateGetOpenGLVersion( 0 );
}

uint32_t getOpenGLMajorVersionNumber()
{
    return privateGetOpenGLVersion( 1 );
}

uint32_t getOpenGLVersionNumber()
{
    return privateGetOpenGLVersion( 2 );
}

bool doesSupportGeometryShader()
{
#ifdef ACGL_OPENGL_ES
    return false;
#else
#   if defined(ACGL_USE_GLEW)
        return (GLEW_EXT_geometry_shader4 || GLEW_ARB_geometry_shader4 || (getOpenGLVersionNumber() >= 32));
#   else
        return (getOpenGLVersionNumber() >= 32);
#   endif
#endif
}

bool doesSupportTessellationShader()
{
#ifdef ACGL_OPENGL_ES
    return false;
#else
#   if defined(ACGL_USE_GLEW)
        return ( GLEW_ARB_tessellation_shader || (getOpenGLVersionNumber() >= 40));
#   else
        return (getOpenGLVersionNumber() >= 40);
#   endif
#endif
}

const GLubyte* acglErrorString( GLenum _errorCode )
{
#ifndef ACGL_USE_GLEW
    // no gluErrorString on iOS
    // this should only get used on OpenGL ES plattforms or if compiled without GLEW, so error strings from the compatibility profile
    // are ignored. Only 3.2+ Core and ES 2.0+ errors belong here:
    if      (_errorCode == GL_INVALID_ENUM)                  { return (GLubyte*) "GL_INVALID_ENUM"; }
    else if (_errorCode == GL_INVALID_VALUE)                 { return (GLubyte*) "GL_INVALID_VALUE"; }
    else if (_errorCode == GL_INVALID_OPERATION)             { return (GLubyte*) "GL_INVALID_OPERATION"; }
    else if (_errorCode == GL_INVALID_FRAMEBUFFER_OPERATION) { return (GLubyte*) "GL_INVALID_FRAMEBUFFER_OPERATION"; }
    else if (_errorCode == GL_OUT_OF_MEMORY)                 { return (GLubyte*) "GL_OUT_OF_MEMORY"; }
    else if (_errorCode == GL_NO_ERROR)                      { return (GLubyte*) "GL_NO_ERROR"; }
    else {
        return (GLubyte*) "unknown error";
    }
#else
    return gluErrorString( _errorCode );
#endif
}



GLenum openGLError_( const char *_fileName, const unsigned long _lineNumber )
{
    GLenum currentError = glGetError();
    GLenum lastError    = currentError;

    // OpenGL does not forbit the implementation to stack up more than one error code
    // so we have to check those in a loop:
    while ( currentError != GL_NO_ERROR ) {
        ACGL::Utils::error() << "GL error in file " << _fileName << ":" << _lineNumber << " - " << acglErrorString( currentError ) << std::endl;
        lastError    = currentError;
        currentError = glGetError();
    }

    return lastError; // returns the last real error (in case there was at least one!)
}


} // OpenGL
} // ACGL

