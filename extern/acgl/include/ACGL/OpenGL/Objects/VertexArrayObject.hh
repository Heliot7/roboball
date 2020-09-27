////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2011, Computer Graphics Group RWTH Aachen University         //
// All rights reserved.                                                       //
////////////////////////////////////////////////////////////////////////////////

#ifndef ACGL_OPENGL_OBJECTS_VERTEXARRAYOBJECT_HH
#define ACGL_OPENGL_OBJECTS_VERTEXARRAYOBJECT_HH

/**
 * A VertexArrayObject is a predefined combination of (multiple) attributes of
 * (multiple) ArrayBuffers and optionally one ElementArrayBuffer.
 *
 * It's only present in OpenGL 3.0 onwards. For older implementations (or
 * embedded systems) see VertexBufferObject which is a softwareimplementation
 * of the same idea).
 * Alternatively, there are the GL_APPLE_vertex_array_object and
 * GL_ARB_vertex_array_object extensions for OpenGL 2.1.
 * OES_vertex_array_object for OpenGL ES (e.g. iOS 4.0+)
 *
 * A VAO will cache the enabled vertex attributes (set with glEnableVertexAttribArray)
 * and vertex attribute pointer calls (glVertexAttribPointer).
 * Binding a VAO will restore that state (saving a lot of gl calls to do that
 * manually).
 */

#include <ACGL/ACGL.hh>
#include <ACGL/OpenGL/GL.hh>
#if (ACGL_OPENGL_VERSION >= 30)

#include <ACGL/Base/Macros.hh>
#include <ACGL/OpenGL/Tools.hh>

#include <ACGL/OpenGL/Objects/ArrayBuffer.hh>
#include <ACGL/OpenGL/Objects/ElementArrayBuffer.hh>
#include <ACGL/OpenGL/Objects/ShaderProgram.hh>

#include <vector>
#include <tr1/memory>

namespace ACGL{
namespace OpenGL{

class VertexArrayObject
{
    ACGL_NOT_COPYABLE(VertexArrayObject)

    // ==================================================================================================== \/
    // ============================================================================================ STRUCTS \/
    // ==================================================================================================== \/
public:
    struct Attribute
    {
        SharedArrayBuffer arrayBuffer; // the ArrayBuffer to use
        int32_t           attributeID; // the attribute from that ArrayBuffer
        GLint             location;    // a location the in-attribute from a shader is bound to
        // more Attribute properties can be looked up in the ArrayBuffer (like the name)
    };

    // ========================================================================================================= \/
    // ============================================================================================ CONSTRUCTORS \/
    // ========================================================================================================= \/
public:
    VertexArrayObject()
    :   mObjectName(0),
        mpElementArrayBuffer(),
        mAttributes()
    {
        glGenVertexArrays(1, &mObjectName);
        if (openGLCriticalErrorOccured() ) {
            ACGL::Utils::error() << "could not generate vertex array object!" << std::endl;
        }
    }

    virtual ~VertexArrayObject(void)
    {
        // as always, OpenGL will ignore object name 0
        glDeleteVertexArrays(1, &mObjectName);
    }

    // ==================================================================================================== \/
    // ============================================================================================ GETTERS \/
    // ==================================================================================================== \/
public:
    inline GLuint operator()   (void) const { return mObjectName; }
    inline GLuint getObjectName(void) const { return mObjectName; }

    // ==================================================================================================== \/
    // ============================================================================================ METHODS \/
    // ==================================================================================================== \/
public:
    /**
     * Will check if the VAO looks ok (e.g. there is at least one ArrayBuffer and all ArrayBuffers
     * have the same number of elements).
     * A failed test will output an error but won't have other consequences.
     */
    bool isValid(void) const;

    /**
     * Set the given ElementArrayBuffer, if a NULL pointer is given, an existing EAB will get unset.
     * Will restore the previously bound VAO (DSA style)
     */
    void attachElementArrayBuffer( const SharedElementArrayBuffer& _elementArrayBuffer )
    {
        // query old VAO
        GLint oldVAO; glGetIntegerv( GL_VERTEX_ARRAY_BINDING, &oldVAO );

        mpElementArrayBuffer = _elementArrayBuffer;

        bind();
        if (mpElementArrayBuffer) { // could be set to NULL!
            mpElementArrayBuffer->bind();
        } else {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        }

        // restore old VAO
        glBindVertexArray( oldVAO ); openGLRareError();
    }

    inline void detachElementArrayBuffer() { attachElementArrayBuffer( SharedElementArrayBuffer() ); }

    /**
     * Will set the attribute _arrayBufferAttribute of ArrayBuffer _arrayBuffer to the given attribute location.
     * If that location was already used it will get overwritten.
     * The _attributeLocation has to be lower than GL_MAX_VERTEX_ATTRIBS
     */
    void attachAttribute( const SharedArrayBuffer &_arrayBuffer,
                          uint32_t _arrayBufferAttribute,
                          GLuint   _attributeLocation)
    {
        Attribute newAttribute = { _arrayBuffer, _arrayBufferAttribute, _attributeLocation };
        attachAttribute( newAttribute );
    }

    void attachAttribute( const Attribute &_attribute )
    {
        GLint maxAttributes;
        glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &maxAttributes); // TODO: clever caching
        if (mAttributes.size() >= (uint32_t) maxAttributes) {
            ACGL::Utils::error() << "can't attach attribute " << _attribute.arrayBuffer->getAttributes()[_attribute.attributeID].name
                                 << " - maximum number of attributes reached: " << maxAttributes << std::endl;
            return;
        }

        mAttributes.push_back( _attribute );

        // query old VAO
        GLint oldVAO; glGetIntegerv( GL_VERTEX_ARRAY_BINDING, &oldVAO );

        bind();
        glEnableVertexAttribArray( _attribute.location );
        _attribute.arrayBuffer->setAttributePointer( _attribute.attributeID, _attribute.location );

        // restore old VAO
        glBindVertexArray( oldVAO ); openGLRareError();
    }

    /**
     * Will detach the first found Attribute with the given attribute location.
     */
    void detachAttribute( GLint _location )
    {
        for (AttributeVec::size_type i = 0; i < mAttributes.size(); ++i)
        {
            if (mAttributes[i].location == _location) {
                // the other pointer data is still set, but that isn't relevant if the attribute itself is deactivated
                glDisableVertexArrayAttribEXT( mObjectName, mAttributes[i].location );
                mAttributes.erase( mAttributes.begin()+i );
                return;
            }
        }
        // if we got here, no Attribute of the given name exists
        ACGL::Utils::warning() << "can't detach attribute with location " << _location << " - no such Attribute" << std::endl;
    }

    /**
     * Will detach the first found Attribute with the given name.
     */
    void detachAttribute( const std::string &_name )
    {
        for (AttributeVec::size_type i = 0; i < mAttributes.size(); ++i)
        {
            if (mAttributes[i].arrayBuffer->getAttributes()[ mAttributes[i].attributeID ].name == _name) {
                // the other pointer data is still set, but that isn't relevant if the attribute itself is deactivated
                glDisableVertexArrayAttribEXT( mObjectName, mAttributes[i].location );
                mAttributes.erase( mAttributes.begin()+i );
                return;
            }
        }
        // if we got here, no Attribute of the given name exists
        ACGL::Utils::warning() << "can't detach attribute " << _name << " - no such Attribute" << std::endl;
    }

    /**
     * Return true if setAttributeMappingsByShaderProgram(_shaderProgram) would do nothing.
     * That means the VAO and ShaderProgram have already matching layouts.
     */
    bool mappingsMatchShaderProgram( const ConstSharedShaderProgram &_shaderProgram )
    {
        for (AttributeVec::size_type i = 0; i < mAttributes.size(); ++i)
        {
            std::string attributeName  = mAttributes[i].arrayBuffer->getAttributes()[ mAttributes[i].attributeID ].name;
            GLint       shaderLocation = _shaderProgram->getAttributeLocation( attributeName );

            if (mAttributes[i].location != shaderLocation) return false;
        }
        return true;
    }

    /**
     * Query the attribute locations based on the attribute names in the ArrayBuffers and the ShaderProgram
     * If they match, use the location reported from the ShaderProgram.
     */
    void setAttributeMappingsByShaderProgram( const ConstSharedShaderProgram &_shaderProgram )
    {
        bool fullUpdateNeeded = false;

        for (AttributeVec::size_type i = 0; i < mAttributes.size(); ++i)
        {
            std::string attributeName  = mAttributes[i].arrayBuffer->getAttributes()[ mAttributes[i].attributeID ].name;
            GLint       shaderLocation = _shaderProgram->getAttributeLocation( attributeName );

            if (shaderLocation == -1) {
                ACGL::Utils::error() << "can't update VAO mappings, attribute " << attributeName << " does not exist in shader" << std::endl;
                continue; // try to match as much as possible
            }

            if (mAttributes[i].location != shaderLocation) {
                mAttributes[i].location  = shaderLocation;
                fullUpdateNeeded = true;
            }
        }

        // why the full update? setting the new location right when a change is detected will get problamatic
        // if two attributes exchange there position...
        if (fullUpdateNeeded) {
            // query old VAO
            GLint oldVAO; glGetIntegerv( GL_VERTEX_ARRAY_BINDING, &oldVAO );

            bind();
            GLint maxAttributes;
            glGetIntegerv( GL_MAX_VERTEX_ATTRIBS, &maxAttributes );

            // disable all attributes
            for (GLint i = 0; i < maxAttributes; ++i) glDisableVertexAttribArray( i );
            // set all attributes:

            for (uint32_t i = 0; i < mAttributes.size(); ++i) {
                glEnableVertexAttribArray( mAttributes[i].location );
                mAttributes[i].arrayBuffer->setAttributePointer( mAttributes[i].attributeID, mAttributes[i].location );
            }

            // restore old VAO
            glBindVertexArray( oldVAO ); openGLRareError();
        }
    }

    // ===================================================================================================== \/
    // ============================================================================================ WRAPPERS \/
    // ===================================================================================================== \/
public:
    //! Bind this VAO
    inline void bind(void) const
    {
        glBindVertexArray( mObjectName );
    }

    inline void enable  (void) const { bind(); }
    inline void disable (void) const { glBindVertexArray(0); }

    //! Nothing has to be prepared for a render call
    //! Note: the previously bound VAO will not get restored, instead VAO 0 will get bound
    inline void render (void)  const
    {
        enable();
        draw();
        disable();
    }

    //! Will select the matching draw call. Remember to enable first!
    void draw(void) const
    {
        if(mpElementArrayBuffer)
            drawElements();
        else
            drawArrays();

        openGLRareError();
    }

    //! Can be called directly instead of draw() iff the caller knows this is the correct call!
    inline void drawElements(void) const
    {
        mpElementArrayBuffer->draw();
    }

    //! Can be called directly instead of draw() iff the caller knows this is the correct call!
    inline void drawArrays(void) const
    {
        mAttributes[0].arrayBuffer->draw();
    }

    // ===================================================================================================== \/
    // ============================================================================================ TYPEDEFS \/
    // ===================================================================================================== \/
protected:
    typedef std::vector< Attribute > AttributeVec;

    // =================================================================================================== \/
    // ============================================================================================ FIELDS \/
    // =================================================================================================== \/
protected:
    GLuint                   mObjectName;          // OpenGL object name
    SharedElementArrayBuffer mpElementArrayBuffer; // optional EAB
    AttributeVec             mAttributes;          // vertex attributes
};

ACGL_SHARED_TYPEDEF(VertexArrayObject)

} // OpenGL
} // ACGL

#endif // OpenGL 3.0

#endif // ACGL_OPENGL_OBJECTS_VERTEXARRAYOBJECT_HH
