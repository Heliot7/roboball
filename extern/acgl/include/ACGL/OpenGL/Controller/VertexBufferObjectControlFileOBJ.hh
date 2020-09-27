////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2011, Computer Graphics Group RWTH Aachen University         //
// All rights reserved.                                                       //
////////////////////////////////////////////////////////////////////////////////

#ifndef ACGL_OPENGL_CONTROLLER_VERTEXBUFFEROBJECTCONTROLFILEOBJ_HH
#define ACGL_OPENGL_CONTROLLER_VERTEXBUFFEROBJECTCONTROLFILEOBJ_HH

#include <ACGL/ACGL.hh>

#include <ACGL/Resource/FileController.hh>
#include <ACGL/Base/Settings.hh>
#include <ACGL/OpenGL/Objects/VertexBufferObject.hh>
#include <ACGL/OpenGL/Objects/ShaderProgram.hh>
#include <ACGL/OpenGL/GL.hh>

namespace ACGL{
namespace OpenGL{

class VertexBufferObjectControlFileOBJ : public Resource::FileController<VertexBufferObject>
{
    // ========================================================================================================= \/
    // ============================================================================================ CONSTRUCTORS \/
    // ========================================================================================================= \/
public:
    VertexBufferObjectControlFileOBJ(const std::string& _filename)
    :   Resource::FileController<VertexBufferObject>(_filename, Base::Settings::the()->getFullGeometryPath()),
        mpShaderProgram(),
        mElementArrayBuffer(),
        mArrayBuffer()
    {}
    virtual ~VertexBufferObjectControlFileOBJ() {}

    // ==================================================================================================== \/
    // ============================================================================================ METHODS \/
    // ==================================================================================================== \/
public:
    inline VertexBufferObjectControlFileOBJ& shaderProgram (const ConstSharedShaderProgram& _shaderProgram) { mpShaderProgram = _shaderProgram; return *this; }

private:
    bool loadOBJ(SharedVertexBufferObject& _vertexBuffer);

    // ===================================================================================================== \/
    // ============================================================================================ OVERRIDE \/
    // ===================================================================================================== \/
public:
    virtual SharedVertexBufferObject create(void);
    virtual bool update(SharedVertexBufferObject& _vertexBuffer);

    // =================================================================================================== \/
    // ============================================================================================ FIELDS \/
    // =================================================================================================== \/
protected:
    ConstSharedShaderProgram mpShaderProgram;
    SharedElementArrayBuffer mElementArrayBuffer;
    SharedArrayBuffer        mArrayBuffer;
};

} // OpenGL
} // ACGL

#endif // ACGL_OPENGL_CONTROLLER_VERTEXBUFFEROBJECTCONTROLFILEOBJ_HH
