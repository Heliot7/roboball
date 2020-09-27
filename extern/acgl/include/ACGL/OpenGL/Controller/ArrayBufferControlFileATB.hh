////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2011, Computer Graphics Group RWTH Aachen University         //
// All rights reserved.                                                       //
////////////////////////////////////////////////////////////////////////////////

#ifndef ACGL_OPENGL_CONTROLLER_ARRAYBUFFERCONTROLFILEATB_HH
#define ACGL_OPENGL_CONTROLLER_ARRAYBUFFERCONTROLFILEATB_HH

#include <ACGL/ACGL.hh>

#include <ACGL/Resource/FileController.hh>
#include <ACGL/Base/Settings.hh>
#include <ACGL/OpenGL/Objects/ArrayBuffer.hh>
#include <ACGL/OpenGL/Objects/ShaderProgram.hh>
#include <ACGL/OpenGL/GL.hh>

namespace ACGL{
namespace OpenGL{

class ArrayBufferControlFileATB : public Resource::FileController<ArrayBuffer>
{
    // ========================================================================================================= \/
    // ============================================================================================ CONSTRUCTORS \/
    // ========================================================================================================= \/
public:
    ArrayBufferControlFileATB(const std::string& _filename)
    :   Resource::FileController<ArrayBuffer>(_filename, Base::Settings::the()->getFullGeometryPath()),
        mpShaderProgram()
    {}
    virtual ~ArrayBufferControlFileATB() {}

    // ==================================================================================================== \/
    // ============================================================================================ METHODS \/
    // ==================================================================================================== \/
public:
    inline ArrayBufferControlFileATB& shaderProgram (const ConstSharedShaderProgram& _shaderProgram) { mpShaderProgram = _shaderProgram; return *this; }

private:
    bool loadATB(SharedArrayBuffer& _arrayBuffer);

    // ===================================================================================================== \/
    // ============================================================================================ OVERRIDE \/
    // ===================================================================================================== \/
public:
    virtual SharedArrayBuffer create(void);
    virtual bool update(SharedArrayBuffer& _arrayBuffer);

    // =================================================================================================== \/
    // ============================================================================================ FIELDS \/
    // =================================================================================================== \/
protected:
    ConstSharedShaderProgram mpShaderProgram;
};

} // OpenGL
} // ACGL

#endif // ACGL_OPENGL_CONTROLLER_ARRAYBUFFERCONTROLFILEATB_HH
