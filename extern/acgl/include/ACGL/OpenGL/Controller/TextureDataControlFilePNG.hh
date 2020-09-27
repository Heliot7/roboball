////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2011, Computer Graphics Group RWTH Aachen University         //
// All rights reserved.                                                       //
////////////////////////////////////////////////////////////////////////////////

#ifndef ACGL_OPENGL_CONTROLLER_TEXTUREDATACONTROLFILEPNG_HH
#define ACGL_OPENGL_CONTROLLER_TEXTUREDATACONTROLFILEPNG_HH

#include <ACGL/ACGL.hh>

#include <ACGL/OpenGL/Controller/TextureDataControlFile.hh>

namespace ACGL{
namespace OpenGL{

class TextureDataControlFilePNG : public TextureDataControlFile
{
    // ========================================================================================================= \/
    // ============================================================================================ CONSTRUCTORS \/
    // ========================================================================================================= \/
public:
    TextureDataControlFilePNG(const std::string& _filename)
    :   TextureDataControlFile(_filename)
    {}
    virtual ~TextureDataControlFilePNG(void) {}

    static SharedTextureDataControlFile creator(const std::string& _filename) { return SharedTextureDataControlFile(new TextureDataControlFilePNG(_filename)); }

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

ACGL_SHARED_TYPEDEF(TextureDataControlFilePNG)

} // OpenGL
} // ACGL

#endif // ACGL_OPENGL_CONTROLLER_TEXTUREDATACONTROLFILEPNG_HH
