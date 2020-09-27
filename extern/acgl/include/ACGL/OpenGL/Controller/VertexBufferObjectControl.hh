////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2011, Computer Graphics Group RWTH Aachen University         //
// All rights reserved.                                                       //
////////////////////////////////////////////////////////////////////////////////

#ifndef ACGL_OPENGL_CONTROLLER_VERTEXBUFFEROBJECTCONTROL_HH
#define ACGL_OPENGL_CONTROLLER_VERTEXBUFFEROBJECTCONTROL_HH

#include <ACGL/ACGL.hh>

#include <ACGL/Resource/BasicCreateController.hh>
#include <ACGL/OpenGL/Objects/VertexBufferObject.hh>
#include <ACGL/OpenGL/Objects/ShaderProgram.hh>
#include <ACGL/OpenGL/GL.hh>

namespace ACGL{
namespace OpenGL{

class VertexBufferObjectControl : public Resource::BasicCreateController<VertexBufferObject>
{
    // ==================================================================================================== \/
    // ============================================================================================ STRUCTS \/
    // ==================================================================================================== \/
public:
    struct AttributeDefine
    {
        std::string name;
        int_t bufferID;
        std::string attributeName;
    };

    // ===================================================================================================== \/
    // ============================================================================================ TYPEDEFS \/
    // ===================================================================================================== \/
public:
    typedef std::vector< AttributeDefine > AttributeDefineVec;

    // ========================================================================================================= \/
    // ============================================================================================ CONSTRUCTORS \/
    // ========================================================================================================= \/
public:
    VertexBufferObjectControl(void)
    :   Resource::BasicCreateController<VertexBufferObject>(),
        mpElementArrayBuffer(),
        mArrayBuffers(),
        mAttributeDefines(),
        mpShaderProgram()
    {}
    virtual ~VertexBufferObjectControl() {}

    // ==================================================================================================== \/
    // ============================================================================================ METHODS \/
    // ==================================================================================================== \/
public:
    inline VertexBufferObjectControl& index (const ConstSharedElementArrayBuffer& _elementArrayBuffer) { mpElementArrayBuffer = _elementArrayBuffer; return *this; }
    inline VertexBufferObjectControl& data  (const ConstSharedArrayBuffer& _arrayBuffer)               { mArrayBuffers.push_back(_arrayBuffer);      return *this; }
    inline VertexBufferObjectControl& shaderProgram (const ConstSharedShaderProgram& _shaderProgram)   { mpShaderProgram = _shaderProgram;           return *this; }

    inline VertexBufferObjectControl& attribute (const std::string& _name, const std::string& _nameInArray)
    {
        AttributeDefine a = {_name, (int_t)mArrayBuffers.size()-1, _nameInArray};
        mAttributeDefines.push_back(a);
        return *this;
    }

    inline VertexBufferObjectControl& attribute (const std::string& _name, int_t _bufferID, const std::string& _nameInArray)
    {
        AttributeDefine a = {_name, _bufferID, _nameInArray};
        mAttributeDefines.push_back(a);
        return *this;
    }

    // ===================================================================================================== \/
    // ============================================================================================ OVERRIDE \/
    // ===================================================================================================== \/
public:
    virtual SharedVertexBufferObject create(void);

    // =================================================================================================== \/
    // ============================================================================================ FIELDS \/
    // =================================================================================================== \/
protected:
    ConstSharedElementArrayBuffer           mpElementArrayBuffer;
    VertexBufferObject::ConstArrayBufferVec mArrayBuffers;
    AttributeDefineVec                      mAttributeDefines;
    ConstSharedShaderProgram                mpShaderProgram;
};

} // OpenGL
} // ACGL

#endif // ACGL_OPENGL_CONTROLLER_VERTEXBUFFEROBJECTCONTROL_HH
