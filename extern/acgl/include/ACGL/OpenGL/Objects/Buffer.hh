////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2011, Computer Graphics Group RWTH Aachen University         //
// All rights reserved.                                                       //
////////////////////////////////////////////////////////////////////////////////

#ifndef ACGL_OPENGL_OBJECTS_BUFFER_HH
#define ACGL_OPENGL_OBJECTS_BUFFER_HH

/*
 * A generic OpenGL Buffer Object
 *
 * Mostly an OpenGL Buffer Wrapper: names of OpenGL calls are stripped of the
 * 'gl' and 'Buffer' tokens and setters got a 'set' prefix.
 *
 * Calls that give the target the buffer should get bound to have an alternative
 * call that uses the last used or set target.
 *
 * Note: Most methods will bind this buffer!
 */

#include <ACGL/ACGL.hh>

#include <ACGL/Base/Macros.hh>
#include <ACGL/OpenGL/GL.hh>
#include <ACGL/OpenGL/Tools.hh>

#include <string>
#include <vector>
#include <tr1/memory>

namespace ACGL{
namespace OpenGL{

class Buffer
{
    ACGL_NOT_COPYABLE(Buffer)

    // ========================================================================================================= \/
    // ============================================================================================ CONSTRUCTORS \/
    // ========================================================================================================= \/
public:
    Buffer(void) :   mLastTarget(GL_INVALID_VALUE), mObjectName(0)
    {
        glGenBuffers(1, &mObjectName);
    }

    virtual ~Buffer(void)
    {
        // buffer 0 will get ignored by OpenGL
        glDeleteBuffers(1, &mObjectName);
    }

    // ==================================================================================================== \/
    // ============================================================================================ GETTERS \/
    // ==================================================================================================== \/
public:
    inline GLuint operator()    (void) const { return mObjectName; }
    inline GLuint getObjectName (void) const { return mObjectName; }
    inline bool   isValid       (void) const { return glIsBuffer( mObjectName ); }

private:
    inline GLint getParameter( GLenum _parameter ) {
        bind( mLastTarget );
        GLint value;
        glGetBufferParameteriv( mLastTarget, _parameter, &value );
        return value;
    }

#if (ACGL_OPENGL_VERSION >= 32)
    inline GLint64 getParameter64( GLenum _parameter ) {
        bind( mLastTarget );
        GLint64 value;
        glGetBufferParameteri64v( mLastTarget, _parameter, &value );
        return value;
    }

    //! not side effect free! will bind this buffer to it's last target!
    //! caching of these values on RAM could be a good idea if needed very often!
    inline GLint64   getSize()        { return             getParameter64( GL_BUFFER_SIZE         ); }
    inline GLint64   getMapOffset()   { return             getParameter64( GL_BUFFER_MAP_OFFSET   ); }
    inline GLint64   getMapLength()   { return             getParameter64( GL_BUFFER_MAP_LENGTH   ); }
#else // OpenGL pre 3.2:
    inline GLint     getSize()        { return             getParameter  ( GL_BUFFER_SIZE         ); }
    inline GLint     getMapOffset()   { return             getParameter  ( GL_BUFFER_MAP_OFFSET   ); }
    inline GLint     getMapLength()   { return             getParameter  ( GL_BUFFER_MAP_LENGTH   ); }
#endif // OpenGL >= 3.2
    inline GLenum    getUsage()       { return (GLenum)    getParameter  ( GL_BUFFER_USAGE        ); }
    inline GLenum    getAccess()      { return (GLenum)    getParameter  ( GL_BUFFER_ACCESS       ); }
    inline GLint     getAccessFlags() { return (GLint)     getParameter  ( GL_BUFFER_ACCESS_FLAGS ); }
    inline GLboolean isMapped()       { return (GLboolean) getParameter  ( GL_BUFFER_MAPPED       ); }



    // ===================================================================================================== \/
    // ============================================================================================ WRAPPERS \/
    // ===================================================================================================== \/
public:
    //! Bind this buffer
    inline void bind( GLenum _target )
    {
        glBindBuffer( _target, mObjectName );
        openGLRareError();
        mLastTarget = _target;
    }

    //! Bind this buffer to its last target
    inline void bind()
    {
        glBindBuffer( mLastTarget, mObjectName );
        openGLRareError();
    }

    //! Set data for this buffer. Use only to init the buffer!
    //! Note: The function is not const, because it changes the corresponding GPU data
    inline void setData( GLenum _target, GLsizeiptr _size, const GLvoid *_pData = NULL, GLenum _usage = GL_STATIC_DRAW ) {
        bind( _target );
        glBufferData( _target, _size, _pData, _usage );
        openGLRareError();
    }

    //! Set data for this buffer at the last used target. Use only to init the buffer!
    inline void setData( GLsizeiptr _size, const GLvoid *_pData = NULL, GLenum _usage = GL_STATIC_DRAW ) {
        setData( mLastTarget, _size, _pData, _usage );
    }

    //! Use this to modify the buffer
    inline void setSubData( GLenum _target, GLintptr _offset,
                            GLsizeiptr _size, const GLvoid *_pData ) {
        bind( _target );
        glBufferSubData( _target, _offset, _size, _pData );
        openGLRareError();
    }

    //! Use this to modify the buffer
    inline void setSubData( GLintptr _offset, GLsizeiptr _size, const GLvoid *_pData ) {
        setSubData( mLastTarget, _offset, _size, _pData );
    }


#if (ACGL_OPENGL_VERSION >= 30)
    /** Map a part of the buffer to client memory
     * _offset & _length are values in bytes relative to the buffer
     * _access must contain one (or both) of:
     *      GL_MAP_READ_BIT and GL_MAP_WRITE_BIT
     *  and optionally:
     *      GL_MAP_INVALIDATE_RANGE_BIT GL_MAP_INVALIDATE_BUFFER_BIT
     *      GL_MAP_FLUSH_EXPLICIT_BIT GL_MAP_UNSYNCHRONIZED_BIT
     */
    GLvoid *mapRange( GLenum _target, GLintptr _offset, GLsizeiptr _length, GLbitfield _access ) {
        bind( _target );
        GLvoid *ret = glMapBufferRange( _target, _offset, _length, _access );
        openGLRareError();
        return ret;
    }

    inline GLvoid *mapRange( GLintptr _offset, GLsizeiptr _length, GLbitfield _access ) {
        return mapRange( mLastTarget, _offset, _length, _access );
    }

    /**
     * Spec:
     * If a buffer is mapped with the GL_MAP_FLUSH_EXPLICIT_BIT flag, modifications
     * to the mapped range may be indicated by calling this.
     * _offset and _length indicate a modified subrange of the mapping, in byte. The specified
     * subrange to flush is relative to the start of the currently mapped range of buffer.
     * This can be called multiple times to indicate distinct subranges
     * of the mapping which require flushing.
     */
    void flushMappedRange( GLenum _target, GLsizeiptr _offset, GLsizeiptr _length ) {
        bind( _target );
        glFlushMappedBufferRange( _target, _offset, _length );
        openGLRareError();
    }

    inline void flushMappedRange( GLintptr _offset, GLsizeiptr _length ) {
        flushMappedRange( mLastTarget, _offset, _length );
    }

    // TODO: bindBufferRange
    // TODO: bindBufferBase
#endif // OpenGL >= 3.0

    //! Maps the whole buffer, if using GL 3+, better use mapRange!
    //! _access is GL_READ_ONLY GL_WRITE_ONLY or GL_READ_WRITE
    GLvoid *map( GLenum _target, GLenum _access ) {
        bind( _target );
        GLvoid *ret = glMapBuffer( _target, _access );
        openGLRareError();
        return ret;
    }
    inline GLvoid *map( GLenum _access ) {
        return map( mLastTarget, _access );
    }

    GLboolean unmap( GLenum _target ) {
        bind( _target );
        GLboolean ret = glUnmapBuffer( _target );
        openGLRareError();
        return ret;
    }

    inline GLboolean unmap() {
        return unmap( mLastTarget );
    }

    // TODO: CopyBufferSubData

    /**
     * _target must be one of:
        GL_ARRAY_BUFFER
        GL_ATOMIC_COUNTER_BUFFER
        GL_COPY_READ_BUFFER
        GL_COPY_WRITE_BUFFER
        GL_DRAW_INDIRECT_BUFFER
        GL_ELEMENT_ARRAY_BUFFER
        GL_PIXEL_PACK_BUFFER
        GL_PIXEL_UNPACK_BUFFER
        GL_TEXTURE_BUFFER
        GL_TRANSFORM_FEEDBACK_BUFFER
        GL_UNIFORM_BUFFER
     * Can be changed at any time. Will get changed if a _target gets specified at any call.
     */
    inline void setTarget( GLenum _target ) { mLastTarget = _target; }

    // =================================================================================================== \/
    // ============================================================================================ FIELDS \/
    // =================================================================================================== \/
protected:
    GLenum       mLastTarget;
    GLuint       mObjectName;
};

ACGL_SHARED_TYPEDEF(ArrayBuffer)

} // OpenGL
} // ACGL

#endif // ACGL_OPENGL_OBJECTS_BUFFER_HH
