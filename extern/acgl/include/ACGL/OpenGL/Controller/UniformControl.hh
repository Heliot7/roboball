////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2011, Computer Graphics Group RWTH Aachen University         //
// All rights reserved.                                                       //
////////////////////////////////////////////////////////////////////////////////

#ifndef ACGL_OPENGL_CONTROLLER_UNIFORMCONTROL_HH
#define ACGL_OPENGL_CONTROLLER_UNIFORMCONTROL_HH

#include <ACGL/ACGL.hh>

#include <ACGL/Resource/BasicCreateController.hh>
#include <ACGL/OpenGL/Objects/Uniform.hh>
#include <ACGL/OpenGL/GL.hh>

namespace ACGL{
namespace OpenGL{

template<class UNIFORM>
class UniformControl : public Resource::BasicCreateController<UNIFORM>
{
    // ========================================================================================================= \/
    // ============================================================================================ CONSTRUCTORS \/
    // ========================================================================================================= \/
public:
    UniformControl(void)
    :   mValue()
    {}
    UniformControl(const typename UNIFORM::DATA_TYPE& _value)
    :   mValue(_value)
    {}
    virtual ~UniformControl() {}

    // ==================================================================================================== \/
    // ============================================================================================ METHODS \/
    // ==================================================================================================== \/
public:
    inline UniformControl& value (const typename UNIFORM::DATA_TYPE& _value) { mValue = _value; return *this; }

    // ===================================================================================================== \/
    // ============================================================================================ OVERRIDE \/
    // ===================================================================================================== \/
public:
    virtual std::tr1::shared_ptr<UNIFORM> create(void)
    {
        std::tr1::shared_ptr<UNIFORM> uniform(new UNIFORM());
        uniform->setValue(mValue);
        return uniform;
    }

    // =================================================================================================== \/
    // ============================================================================================ FIELDS \/
    // =================================================================================================== \/
protected:
    typename UNIFORM::DATA_TYPE mValue;
};

typedef UniformControl<Uniform1i> Uniform1iControl;
typedef UniformControl<Uniform1f> Uniform1fControl;
typedef UniformControl<Uniform2f> Uniform2fControl;
typedef UniformControl<Uniform3f> Uniform3fControl;
typedef UniformControl<Uniform4f> Uniform4fControl;
typedef UniformControl<UniformMatrix2f> UniformMatrix2fControl;
typedef UniformControl<UniformMatrix3f> UniformMatrix3fControl;
typedef UniformControl<UniformMatrix4f> UniformMatrix4fControl;
typedef UniformControl<UniformTexture> UniformTextureControl;

} // OpenGL
} // ACGL

#endif // ACGL_OPENGL_CONTROLLER_ARRAYBUFFERCONTROL_HH
