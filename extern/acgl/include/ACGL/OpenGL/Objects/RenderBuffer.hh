////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2011, Computer Graphics Group RWTH Aachen University         //
// All rights reserved.                                                       //
////////////////////////////////////////////////////////////////////////////////

#ifndef ACGL_OPENGL_OBJECTS_RENDERBUFFER_HH
#define ACGL_OPENGL_OBJECTS_RENDERBUFFER_HH

#include <ACGL/ACGL.hh>

#include <ACGL/Base/Macros.hh>
#include <ACGL/OpenGL/GL.hh>
#include <ACGL/OpenGL/Tools.hh>

#include <tr1/memory>

namespace ACGL{
namespace OpenGL{

class RenderBuffer
{
    ACGL_NOT_COPYABLE(RenderBuffer)

    // ========================================================================================================= \/
    // ============================================================================================ CONSTRUCTORS \/
    // ========================================================================================================= \/
public:
    RenderBuffer(
        GLenum _internalFormat)
    :   mObjectName(0),
        mInternalFormat(_internalFormat),
        mWidth(0),
        mHeight(0),
        mSamples(0)
    {
        glGenRenderbuffers(1, &mObjectName);
        if (openGLCriticalErrorOccured() ) {
            ACGL::Utils::error() << "could not generate renderbuffer!" << std::endl;
            return;
        }
    }

    virtual ~RenderBuffer(void)
    {
        // buffer 0 will get ignored by OpenGL
        glDeleteRenderbuffers(1, &mObjectName);
    }

    // ==================================================================================================== \/
    // ============================================================================================ GETTERS \/
    // ==================================================================================================== \/
public:
    inline GLuint  operator()        (void) const { return mObjectName;     }
    inline GLuint  getObjectName     (void) const { return mObjectName;     }
    inline GLenum  getInternalFormat (void) const { return mInternalFormat; }
    inline GLsizei getWidth          (void) const { return mWidth;          }
    inline GLsizei getHeight         (void) const { return mHeight;         }

    // ==================================================================================================== \/
    // ============================================================================================ METHODS \/
    // ==================================================================================================== \/
public:
    //! Get the actual number of samples
    inline int_t getSamples(void) const
    {
        glBindRenderbuffer(GL_RENDERBUFFER, mObjectName);
        GLint samples;
        glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_SAMPLES, &samples);
        return (int_t)samples;
    }

    // ===================================================================================================== \/
    // ============================================================================================ WRAPPERS \/
    // ===================================================================================================== \/
public:    
    //! Bind the renderbuffer
    inline void bind(void) const
    {
        glBindRenderbuffer(GL_RENDERBUFFER, mObjectName);
    }

    //! Set texture size and NULL data
    inline void setSize(
        GLsizei _width,
        GLsizei _height,
        GLsizei _samples = 0)
    {
        mWidth = _width;
        mHeight = _height;
        mSamples = _samples;
        glBindRenderbuffer(GL_RENDERBUFFER, mObjectName);

#if (ACGL_OPENGL_VERSION >= 30)
        glRenderbufferStorageMultisample(GL_RENDERBUFFER, mSamples, mInternalFormat, mWidth, mHeight);
#else
        glRenderbufferStorage(GL_RENDERBUFFER, mInternalFormat, mWidth, mHeight);
#endif // OpenGL >= 3.0

    }

    // =================================================================================================== \/
    // ============================================================================================ FIELDS \/
    // =================================================================================================== \/
protected:
    GLuint  mObjectName;
    GLenum  mInternalFormat;
    GLsizei mWidth;
    GLsizei mHeight;
    GLsizei mSamples;
};

ACGL_SHARED_TYPEDEF(RenderBuffer)

} // OpenGL
} // ACGL

#endif // ACGL_OPENGL_OBJECTS_RENDERBUFFER_HH
