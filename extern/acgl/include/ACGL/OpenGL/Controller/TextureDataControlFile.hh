////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2011, Computer Graphics Group RWTH Aachen University         //
// All rights reserved.                                                       //
////////////////////////////////////////////////////////////////////////////////

#ifndef ACGL_OPENGL_CONTROLLER_TEXTUREDATACONTROLFILE_HH
#define ACGL_OPENGL_CONTROLLER_TEXTUREDATACONTROLFILE_HH

#include <ACGL/ACGL.hh>

#include <ACGL/Resource/FileController.hh>
#include <ACGL/Base/Settings.hh>
#include <ACGL/OpenGL/Data/TextureData.hh>

namespace ACGL{
namespace OpenGL{

class TextureDataControlFile : public Resource::FileController<TextureData>
{
    // ========================================================================================================= \/
    // ============================================================================================ CONSTRUCTORS \/
    // ========================================================================================================= \/
public:
    TextureDataControlFile(const std::string& _filename)
    :   Resource::FileController<TextureData>(_filename, Base::Settings::the()->getFullTexturePath())
    {}
    virtual ~TextureDataControlFile(void) {}

    // ====================================================================================================== \/
    // ============================================================================================ INTERFACE \/
    // ====================================================================================================== \/
private:
    virtual bool load(SharedTextureData& texture) const = 0;

    // ====================================================================================================== \/
    // ============================================================================================= OVERRIDE \/
    // ====================================================================================================== \/
public:
    virtual SharedTextureData create(void);
    virtual bool update(SharedTextureData& _texture);
};

ACGL_SHARED_TYPEDEF(TextureDataControlFile)

} // OpenGL
} // ACGL

#endif // ACGL_OPENGL_CONTROLLER_TEXTUREDATACONTROLFILE_HH
