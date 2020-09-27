////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2011, Computer Graphics Group RWTH Aachen University         //
// All rights reserved.                                                       //
////////////////////////////////////////////////////////////////////////////////

#ifndef ACGL_OPENGL_OBJECTS_ELEMENTBUFFERDATA_HH
#define ACGL_OPENGL_OBJECTS_ELEMENTBUFFERDATA_HH

/*
 * An ElementArrayBuffer is an index into ArrayBuffers and defines which
 * elements of that array should be drawn in which order.
 *
 * The combination of (multiple) attributes of (multiple) ArrayBuffers
 * and one (optional) ElementArrayBuffer is a VertexBufferObject or VertexArrayObject.
 *
 * Note: In some documents ElementArrayBuffer are called VertexBufferObjects, VBOs
 *       or IndexBufferObjects (IBOs). But ArrayBuffers can also be called VBOs...
 *       The original extension that introduced these two new buffer types was called
 *       ARB_vertex_buffer_object but the buffers itself are called ArrayBuffer and
 *       ElementArrayBuffer.
 */

#include <ACGL/ACGL.hh>

#include <ACGL/Base/Macros.hh>
#include <ACGL/OpenGL/GL.hh>
#include <ACGL/OpenGL/Tools.hh>

#include <tr1/memory>

namespace ACGL{
namespace OpenGL{

class ElementArrayBuffer
{
    ACGL_NOT_COPYABLE(ElementArrayBuffer)

    // ========================================================================================================= \/
    // ============================================================================================ CONSTRUCTORS \/
    // ========================================================================================================= \/
public:
    ElementArrayBuffer(
        GLenum _usage = GL_STATIC_DRAW,
        GLenum _mode  = GL_TRIANGLES,
        GLenum _type  = GL_UNSIGNED_INT)
    :   mObjectName(0),
        mUsage(_usage),
        mMode(_mode),
        mElements(0),
        mType(_type),
        mSizeOfType(getGLTypeSize(_type))
    {
        glGenBuffers(1, &mObjectName);
        if (openGLCriticalErrorOccured() ) {
            ACGL::Utils::error() << "could not generate element array buffer!" << std::endl;
        }

    }

    virtual ~ElementArrayBuffer(void)
    {
        // buffer 0 will get ignored by OpenGL
        glDeleteBuffers(1, &mObjectName);
    }
    
    // ==================================================================================================== \/
    // ============================================================================================ GETTERS \/
    // ==================================================================================================== \/
public:
    inline GLuint  operator()    (void) const { return mObjectName; }
    inline GLuint  getObjectName (void) const { return mObjectName; }
    inline GLenum  getUsage      (void) const { return mUsage;      }
    inline GLenum  getMode       (void) const { return mMode;       }
    inline GLsizei getElements   (void) const { return mElements;   }
    inline GLenum  getType       (void) const { return mType;       }
    inline GLint   getSizeOfType (void) const { return mSizeOfType; }

    // ==================================================================================================== \/
    // ============================================================================================ SETTERS \/
    // ==================================================================================================== \/
public:
    inline void setUsage (GLenum _usage) { mUsage = _usage; }
    inline void setMode  (GLenum _mode)  { mMode = _mode;   }

    inline void setType (GLenum _type)
    {
        mType = _type;
        mSizeOfType = getGLTypeSize(mType);
    }
    
    // ===================================================================================================== \/
    // ============================================================================================ WRAPPERS \/
    // ===================================================================================================== \/
public:
    //! Bind this buffer
    inline void bind(void) const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mObjectName);
    }

    void draw(GLint _first, GLsizei _count) const
    {
        glDrawElements(mMode, _count, mType, reinterpret_cast<GLvoid*>(_first));
        openGLRareError();
    }

    void draw(void) const
    {
        glDrawElements(mMode, mElements, mType, (GLvoid*)0);
        openGLRareError();
    }

    //! Set data for this buffer
    inline void setData(
        const GLvoid* _pData,
        GLsizei _elements)
    {
        mElements = _elements;
        setData( _pData );
    }

    //! Set data for this buffer
    //! Note: The function is not const, because it changes the corresponding GPU data
    inline void setData(
        const GLvoid* _pData)
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mObjectName);
        glBufferData(
            GL_ELEMENT_ARRAY_BUFFER,
            mElements * mSizeOfType,
            _pData,
            mUsage);
        openGLRareError();
    }

    // =================================================================================================== \/
    // ============================================================================================ FIELDS \/
    // =================================================================================================== \/
protected:
    GLuint  mObjectName;
    GLenum  mUsage;
    GLenum  mMode;
    GLsizei mElements;
    GLenum  mType;
    GLint   mSizeOfType;
};

ACGL_SHARED_TYPEDEF(ElementArrayBuffer)

} // OpenGL
} // ACGL

#endif // ACGL_OPENGL_OBJECTS_ELEMENTBUFFERDATA_HH
