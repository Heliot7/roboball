////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2011, Computer Graphics Group RWTH Aachen University         //
// All rights reserved.                                                       //
////////////////////////////////////////////////////////////////////////////////

#ifndef ACGL_OPENGL_OBJECTS_VERTEXBUFFEROBJECT_HH
#define ACGL_OPENGL_OBJECTS_VERTEXBUFFEROBJECT_HH

/*
 * A VertexBufferObject combines the two tightly related buffers from the
 * ARB_vertex_buffer_object extension.
 *
 * M Attributes from N ArrayBuffer and one (optional) ElementArrayBuffer form
 * one VertexBufferObject.
 */

#include <ACGL/ACGL.hh>

#include <ACGL/Base/Macros.hh>
#include <ACGL/OpenGL/GL.hh>
#include <ACGL/OpenGL/Objects/ArrayBuffer.hh>
#include <ACGL/OpenGL/Objects/ElementArrayBuffer.hh>

#include <vector>
#include <tr1/memory>

namespace ACGL{
namespace OpenGL{

class VertexBufferObject
{
    ACGL_NOT_COPYABLE(VertexBufferObject)

    // ==================================================================================================== \/
    // ============================================================================================ STRUCTS \/
    // ==================================================================================================== \/
public:
    struct Attribute
    {
        std::string name;
        int_t bufferID;
        int_t attributeID;
        GLint indexInShader;
    };

    // ===================================================================================================== \/
    // ============================================================================================ TYPEDEFS \/
    // ===================================================================================================== \/
public:
    typedef std::vector< ConstSharedArrayBuffer > ConstArrayBufferVec;
    typedef std::vector< Attribute > AttributeVec;

    // ========================================================================================================= \/
    // ============================================================================================ CONSTRUCTORS \/
    // ========================================================================================================= \/
public:
    VertexBufferObject(void)
    :   mpElementArrayBuffer(),
        mArrayBuffers(),
        mAttributes()
    {}

    virtual ~VertexBufferObject(void) {};
    
    // ==================================================================================================== \/
    // ============================================================================================ GETTERS \/
    // ==================================================================================================== \/
public:
    inline const ConstSharedElementArrayBuffer& getElementArrayBuffer (void) const { return mpElementArrayBuffer; }
    inline const ConstArrayBufferVec&           getArrayBuffers       (void) const { return mArrayBuffers;        }
    inline const AttributeVec&                  getAttributes         (void) const { return mAttributes;          }

    // ==================================================================================================== \/
    // ============================================================================================ METHODS \/
    // ==================================================================================================== \/
public:
    int_t getAttributeIndexByName(const std::string& _name) const;

    inline void setAttributePointer(AttributeVec::size_type _indexInArray, GLuint _indexInShader) const
    {
        mArrayBuffers[mAttributes[_indexInArray].bufferID]->setAttributePointer(
                mAttributes[_indexInArray].attributeID,
                _indexInShader);
    }

    void validate (void) const;

    inline void setElementArrayBuffer(const ConstSharedElementArrayBuffer& _elementArrayBuffer)
    {
        mpElementArrayBuffer = _elementArrayBuffer;
    }

    inline void attachArrayBuffer(const ConstSharedArrayBuffer& _arrayBuffer)
    {
        mArrayBuffers.push_back(_arrayBuffer);
    }

    inline void removeArrayBuffers(void)
    {
        mArrayBuffers.clear();
    }

    inline void attachAttribute(
        const std::string& _name,
        int_t _bufferID,
        const std::string& _attributeName,
        GLint _indexInShader)
    {
        Attribute attribute = {
            _name,
            _bufferID,
            mArrayBuffers[_bufferID]->getAttributeIndexByName(_attributeName),
            _indexInShader};
        mAttributes.push_back(attribute);
    }

    inline void removeAttributes(void)
    {
        mAttributes.clear();
    }

    // ===================================================================================================== \/
    // ============================================================================================ WRAPPERS \/
    // ===================================================================================================== \/
public:
    void enable  (void) const;
    void disable (void) const;


    inline void render (void)  const
    {
        enable();
        draw();
        disable();
    }

    void drawElements(void) const
    {
        mpElementArrayBuffer->draw();
    }

    void drawArrays(void) const
    {
        //If no ElementArrayBuffer is specified we use the convention that
        //the first ArrayBuffers determines the mode and the number of elements.
        mArrayBuffers[0]->draw();
    }

    void draw(void) const
    {
        if(mpElementArrayBuffer)
            drawElements();
        else
            drawArrays();
        openGLRareError();
    }

    // =================================================================================================== \/
    // ============================================================================================ FIELDS \/
    // =================================================================================================== \/
protected:
    ConstSharedElementArrayBuffer mpElementArrayBuffer;
    ConstArrayBufferVec           mArrayBuffers;
    AttributeVec                  mAttributes;
};

ACGL_SHARED_TYPEDEF(VertexBufferObject)

} // OpenGL
} // ACGL
#endif // ACGL_OPENGL_OBJECTS_VERTEXBUFFEROBJECT_HH
