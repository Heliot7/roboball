////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2011, Computer Graphics Group RWTH Aachen University         //
// All rights reserved.                                                       //
////////////////////////////////////////////////////////////////////////////////

#ifndef ACGL_OPENGL_OBJECTS_ARRAYBUFFER_HH
#define ACGL_OPENGL_OBJECTS_ARRAYBUFFER_HH

/*
 * An ArrayBuffer holds an array of per-vertex data. In its simplest form an
 * array of one attribute, for example the vertex position or texture-coordinate.
 * An ArrayBuffer however can also hold multiple attributes in an interleaved
 * way.
 *
 * An ArrayBuffer can be drawn directly or indexed in combination with an
 * ElementArrayBuffer.
 *
 * The combination of (multiple) attributes of (multiple) ArrayBuffers
 * and one (optional) ElementArrayBuffer is a VertexBufferObject or VertexArrayObject.
 *
 * Note: In some documents ArrayBuffers (and sometimes ElementArrayBuffers) are
 *       called VertexBufferObjects, VBOs. The original extension that introduced
 *       these two new buffer types was called ARB_vertex_buffer_object but the buffers
 *       itself are called ArrayBuffer and ElementArrayBuffer.
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

class ArrayBuffer
{
    ACGL_NOT_COPYABLE(ArrayBuffer)

    // ==================================================================================================== \/
    // ============================================================================================ STRUCTS \/
    // ==================================================================================================== \/
public:
    //! Each attribute has a dimension (#components, e.g. normal with x/y/z => 3) and an offset in the stride (in bytes)
    struct Attribute
    {
        std::string name;
        GLenum      type;
        GLint       dimension;
        GLint       offset;
        GLboolean   normalized;
    };

    // ===================================================================================================== \/
    // ============================================================================================ TYPEDEFS \/
    // ===================================================================================================== \/
public:
    typedef std::vector< Attribute > AttributeVec;

    // ========================================================================================================= \/
    // ============================================================================================ CONSTRUCTORS \/
    // ========================================================================================================= \/
public:
    ArrayBuffer(
        GLenum _usage = GL_STATIC_DRAW,
        GLenum _mode = GL_TRIANGLES)
    :   mObjectName(0),
        mUsage(_usage),
        mMode(_mode),
        mElements(0),
        mStride(0),
        mAttributes()
    {
        glGenBuffers(1, &mObjectName);
        if (openGLCriticalErrorOccured() ) {
            ACGL::Utils::error() << "could not generate array buffer!" << std::endl;
        }
    }

    virtual ~ArrayBuffer(void)
    {
        // buffer 0 will get ignored by OpenGL
        glDeleteBuffers(1, &mObjectName);
    }

    // ==================================================================================================== \/
    // ============================================================================================ GETTERS \/
    // ==================================================================================================== \/
public:
    inline       GLuint        operator()    (void) const { return mObjectName; }
    inline       GLuint        getObjectName (void) const { return mObjectName; }
    inline       GLenum        getUsage      (void) const { return mUsage;      }
    inline       GLenum        getMode       (void) const { return mMode;       }
    inline       GLsizei       getElements   (void) const { return mElements;   }
    inline       GLsizei       getStride     (void) const { return mStride;     }
    inline const AttributeVec& getAttributes (void) const { return mAttributes; }

    // ==================================================================================================== \/
    // ============================================================================================ METHODS \/
    // ==================================================================================================== \/
public:
    int_t getAttributeIndexByName(const std::string& _nameInArray) const;

    inline void attachAttribute(
        const std::string& _name,
        GLenum _type,
        GLint _dimension,
        GLboolean _normalized = GL_FALSE)
    {
        Attribute attribute = {
            _name,
            _type,
            _dimension,
            mStride,
            _normalized};
        mStride += getGLTypeSize(_type) * _dimension;
        mAttributes.push_back(attribute);
    }

    inline void removeAttributes(void)
    {
        mStride = 0;
        mAttributes.clear();
    }

    // ===================================================================================================== \/
    // ============================================================================================ WRAPPERS \/
    // ===================================================================================================== \/
public:
    void render(void) const;

    void draw(void) const
    {
        glDrawArrays(mMode, 0, mElements);
        openGLRareError();
    }

    void draw(GLint _first, GLsizei _count) const
    {
        glDrawArrays(mMode, _first, _count);
        openGLRareError();
    }

    //! Bind this buffer
    inline void bind(void) const
    {
        glBindBuffer(GL_ARRAY_BUFFER, mObjectName);
        openGLRareError();
    }

    inline void setAttributePointer(AttributeVec::size_type _indexInArray, GLuint _indexInShader) const
    {
        glVertexAttribPointer(
            _indexInShader,
            mAttributes[_indexInArray].dimension,
            mAttributes[_indexInArray].type,
            mAttributes[_indexInArray].normalized,
            mStride,
            reinterpret_cast<GLvoid*>(mAttributes[_indexInArray].offset));
        openGLRareError();
    }

    inline bool setAttributePointer(const std::string& _nameInArray, GLuint _indexInShader) const
    {
        int_t index = getAttributeIndexByName(_nameInArray);
        if(index == -1)
            return false;

        setAttributePointer(index, _indexInShader);
        return true;
    }    

    //! Set data for this buffer and change its size, usage and mode
    inline void setData(
        const GLvoid* _pData,
        GLsizei       _elements,
        GLenum        _usage,
        GLenum        _mode)
    {
        mUsage = _usage;
        mMode  = _mode;
        setData( _pData, _elements );
    }

    //! Set data for this buffer and change its size
    inline void setData(
        const GLvoid* _pData,
        GLsizei       _elements)
    {
        mElements = _elements;
        setData( _pData );
    }

    //! Set data for this buffer
    //! Note: The function is not const, because it changes the corresponding GPU data
    inline void setData(const GLvoid* _pData)
    {
        glBindBuffer(GL_ARRAY_BUFFER, mObjectName);
        glBufferData(
            GL_ARRAY_BUFFER,
            mStride * mElements,
            _pData,
            mUsage);
    }

    // =================================================================================================== \/
    // ============================================================================================ FIELDS \/
    // =================================================================================================== \/
protected:
    GLuint       mObjectName;
    GLenum       mUsage;
    GLenum       mMode;
    GLsizei      mElements;
    GLsizei      mStride;
    AttributeVec mAttributes;
};

ACGL_SHARED_TYPEDEF(ArrayBuffer)

} // OpenGL
} // ACGL

#endif // ACGL_OPENGL_OBJECTS_ARRAYBUFFER_HH
