////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2011, Computer Graphics Group RWTH Aachen University         //
// All rights reserved.                                                       //
////////////////////////////////////////////////////////////////////////////////

#ifndef ACGL_OPENGL_TOOLS_HH
#define ACGL_OPENGL_TOOLS_HH

/*
 * Some OpenGL related helper functions.
 * All the error checking functions are in here.
 */

#include <ACGL/ACGL.hh>
#include <ACGL/OpenGL/GL.hh>

namespace ACGL{
namespace OpenGL{

inline GLint getGLTypeSize ( GLenum _type )
{
    switch(_type)
    {
        case GL_BYTE:           return sizeof(GLubyte);
        case GL_UNSIGNED_BYTE:  return sizeof(GLbyte);
        case GL_SHORT:          return sizeof(GLshort);
        case GL_UNSIGNED_SHORT: return sizeof(GLushort);
        case GL_INT:            return sizeof(GLint);
        case GL_UNSIGNED_INT:   return sizeof(GLuint);
        case GL_FLOAT:          return sizeof(GLfloat);
        case GL_DOUBLE:         return sizeof(GLdouble);
    }
    return 0;
}

uint32_t getOpenGLMinorVersionNumber();
uint32_t getOpenGLMajorVersionNumber();

// returns the combined version number as 10*major + minor for easy comparing
uint32_t getOpenGLVersionNumber();

bool doesSupportGeometryShader();
bool doesSupportTessellationShader();

// for every OpenGL error enum this will return a human readable version of it
// similar to gluErrorString, but that function is not available on all plattforms
// (read: iOS)
const GLubyte* acglErrorString( GLenum _errorCode );

/*
 * This function can be used outside of the ACGL framework to check always(!) for
 * OpenGL errors. It will print the errors and return the error code of the last one.
 * Each OpenGL command can only throw one error, errors can only stack up if this
 * function or glGetError was not called often enough (and some OpenGL implementations
 * will forget old errors if new ones occur).
 */
#define openGLError() openGLError_( __FILE__, __LINE__ )

/*
 * This function is used internally in ACGL - but not directly. It gets called from all
 * other rare/common/critical error checks. The __FILE__ __LINE macros have to be used in
 * those to get the correct values from the caller file, if we would use the macro
 * above we could get the file/line from this file, which isn't helping.
 */
GLenum openGLError_( const char *_fileName, const unsigned long _lineNumber );

/*
 * Inside of ACGL we distinguish between rare, common and critical errors. Each kind can be
 * switched off which turns the function into nothing after compiler optimization. If an
 * error check is turned off it will always behave as if there was no error, even if there
 * is one...
 *
 * Per default a debug build enables critical and common errors, a release build only critical
 * ones.
 *
 * We have two functions for each kind:
 * openGL____Error()        will print error messages and return the last error (or GL_NO_ERROR)
 * openGL____ErrorOccured() will print error messages and retrun true if there was an error
 *
 * The definition of rare/common/critical is a bit fuzzy:
 *
 * critical: Errors which can occur even in a bug-free app, like out-of-memory errors.
 *           These checks are rare, stuff like glCreate calls get checked here.
 *           Tests for critical errors should not impact the performance of the app measurably.
 *
 * common:   
 *           Errors which are quite common while developing. Misuse of the library etc.
 *           Setting uniforms which don't exist or shader compile errors are candidates for
 *           common errors. Places where OpenGL resources are calles by a string etc.
 *
 * rare:     Errors which are so uncommon that we don't even check those ina normal debug build.
 *           Switching these on can impact performance as there can be alot of them. If theres a
 *           OpenGL error somewhere in the code, switch these checks on to find the correct spot.
 *
 * OpenGL error checks that are more complicated than just a glGetError call will be wrapped in the
 * same defines, this can be used in application code as well.
 *
 */

inline GLenum openGLErrorDummy()        { return GL_NO_ERROR; }
inline bool   openGLErrorOccuredDummy() { return false; }

#ifdef ACGL_CHECK_CRITICAL_GL_ERRORS
# define openGLCriticalError()         ACGL::OpenGL::openGLError_( __FILE__, __LINE__ )
# define openGLCriticalErrorOccured() (ACGL::OpenGL::openGLError_( __FILE__, __LINE__ ) != GL_NO_ERROR)
#else
# define openGLCriticalError()         ACGL::OpenGL::openGLErrorDummy()
# define openGLCriticalErrorOccured()  ACGL::OpenGL::openGLErrorOccuredDummy()
#endif

#ifdef ACGL_CHECK_COMMON_GL_ERRORS
# define openGLCommonError()         ACGL::OpenGL::openGLError_( __FILE__, __LINE__ )
# define openGLCommonErrorOccured() (ACGL::OpenGL::openGLError_( __FILE__, __LINE__ ) != GL_NO_ERROR)
#else
# define openGLCommonError()         ACGL::OpenGL::openGLErrorDummy()
# define openGLCommonErrorOccured()  ACGL::OpenGL::openGLErrorOccuredDummy()
#endif

#ifdef ACGL_CHECK_RARE_GL_ERRORS
# define openGLRareError()         ACGL::OpenGL::openGLError_( __FILE__, __LINE__ )
# define openGLRareErrorOccured() (ACGL::OpenGL::openGLError_( __FILE__, __LINE__ ) != GL_NO_ERROR)
#else
# define openGLRareError()         ACGL::OpenGL::openGLErrorDummy()
# define openGLRareErrorOccured()  ACGL::OpenGL::openGLErrorOccuredDummy()
#endif

} // OpenGL
} // ACGL

#endif // ACGL_OPENGL_TOOLS_HH

