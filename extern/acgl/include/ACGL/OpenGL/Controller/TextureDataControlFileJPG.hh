////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2011, Computer Graphics Group RWTH Aachen University         //
// All rights reserved.                                                       //
////////////////////////////////////////////////////////////////////////////////

#ifndef ACGL_OPENGL_CONTROLLER_TEXTUREDATACONTROLFILEJPG_HH
#define ACGL_OPENGL_CONTROLLER_TEXTUREDATACONTROLFILEJPG_HH

#include <ACGL/ACGL.hh>

#include <ACGL/OpenGL/Controller/TextureDataControlFile.hh>

namespace ACGL{
namespace OpenGL{

class TextureDataControlFileJPG : public TextureDataControlFile
{
    // ========================================================================================================= \/
    // ============================================================================================ CONSTRUCTORS \/
    // ========================================================================================================= \/
public:
    TextureDataControlFileJPG(const std::string& _filename)
    :   TextureDataControlFile(_filename)
    {}
    virtual ~TextureDataControlFileJPG(void) {}

    static SharedTextureDataControlFile creator(const std::string& _filename) { return SharedTextureDataControlFile(new TextureDataControlFileJPG(_filename)); }

    // ===================================================================================================== \/
    // ============================================================================================ OVERRIDE \/
    // ===================================================================================================== \/
private:
    virtual bool load(SharedTextureData& texture) const;

    // ==================================================================================================== \/
    // ============================================================================================ METHODS \/
    // ==================================================================================================== \/
public:
    static int_t getTypeID(void) { return sTypeID; }

    // =================================================================================================== \/
    // ============================================================================================ FIELDS \/
    // =================================================================================================== \/
private:
    static int_t sTypeID;
};

ACGL_SHARED_TYPEDEF(TextureDataControlFileJPG)

} // OpenGL
} // ACGL

#endif // ACGL_OPENGL_CONTROLLER_TEXTUREDATACONTROLFILEJPG_HH
