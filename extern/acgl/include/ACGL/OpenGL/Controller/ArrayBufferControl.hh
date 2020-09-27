////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2011, Computer Graphics Group RWTH Aachen University         //
// All rights reserved.                                                       //
////////////////////////////////////////////////////////////////////////////////

#ifndef ACGL_OPENGL_CONTROLLER_ARRAYBUFFERCONTROL_HH
#define ACGL_OPENGL_CONTROLLER_ARRAYBUFFERCONTROL_HH

#include <ACGL/ACGL.hh>

#include <ACGL/Resource/BasicCreateController.hh>
#include <ACGL/OpenGL/Objects/ArrayBuffer.hh>
#include <ACGL/OpenGL/GL.hh>

namespace ACGL{
namespace OpenGL{

class ArrayBufferControl : public Resource::BasicCreateController<ArrayBuffer>
{
    // ==================================================================================================== \/
    // ============================================================================================ STRUCTS \/
    // ==================================================================================================== \/
public:
    struct AttributeDefine
    {
        std::string name;
        GLenum      type;
        GLint       dimension;
        GLboolean   normalized;
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
    ArrayBufferControl(void)
    :   mUsage(GL_STATIC_DRAW),
        mMode(GL_TRIANGLES),
        mElements(0),
        mpData(NULL),
        mAttributeDefines()
    {}
    virtual ~ArrayBufferControl() {}

    // ==================================================================================================== \/
    // ============================================================================================ METHODS \/
    // ==================================================================================================== \/
public:
    inline ArrayBufferControl& usage (GLenum _usage) { mUsage = _usage; return *this; }
    inline ArrayBufferControl& mode  (GLenum _mode)  { mMode = _mode;   return *this; }

    inline ArrayBufferControl& data (const GLvoid* _pData, GLsizei _elements)
    {
        mpData = _pData;
        mElements = _elements;
        return *this;
    }

    inline ArrayBufferControl& attribute (const std::string& _name, GLenum _type, GLint _dimension, GLboolean _normalized = GL_FALSE)
    {
        AttributeDefine a = {_name, _type, _dimension, _normalized};
        mAttributeDefines.push_back(a);
        return *this;
    }

    // ===================================================================================================== \/
    // ============================================================================================ OVERRIDE \/
    // ===================================================================================================== \/
public:
    virtual SharedArrayBuffer create(void);

    // =================================================================================================== \/
    // ============================================================================================ FIELDS \/
    // =================================================================================================== \/
protected:
    GLenum  mUsage;
    GLenum  mMode;
    GLsizei mElements;
    const GLvoid* mpData;
    AttributeDefineVec mAttributeDefines;
};

} // OpenGL
} // ACGL

#endif // ACGL_OPENGL_CONTROLLER_ARRAYBUFFERCONTROL_HH
