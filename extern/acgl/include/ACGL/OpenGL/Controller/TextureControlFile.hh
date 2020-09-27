////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2011, Computer Graphics Group RWTH Aachen University         //
// All rights reserved.                                                       //
////////////////////////////////////////////////////////////////////////////////

#ifndef ACGL_OPENGL_CONTROLLER_TEXTURECONTROLFILE_HH
#define ACGL_OPENGL_CONTROLLER_TEXTURECONTROLFILE_HH

#include <ACGL/ACGL.hh>

#include <ACGL/Resource/FileController.hh>
#include <ACGL/OpenGL/Controller/TextureDataControlFile.hh>
#include <ACGL/OpenGL/Objects/Texture.hh>

namespace ACGL{
namespace OpenGL{

class TextureControlFile : public Resource::FileController<Texture>
{
    // ========================================================================================================= \/
    // ============================================================================================ CONSTRUCTORS \/
    // ========================================================================================================= \/
public:
    TextureControlFile(const std::string& _filename);
    TextureControlFile(const char* _filename);

    template<typename CONTROLLER>
    TextureControlFile(const CONTROLLER& _fileController)
    :   Resource::FileController<Texture>(_fileController.getFilename(), Base::Settings::the()->getFullTexturePath()),
        mDataController(new CONTROLLER(_fileController)),
        mMinFilter(0),
        mMagFilter(0),
        mAnisotropicFilter(0.0),
        mWrapS(0),
        mWrapT(0),
        mWrapR(0)
    {}
    virtual ~TextureControlFile(void) {}

    // ==================================================================================================== \/
    // ============================================================================================ METHODS \/
    // ==================================================================================================== \/
public:
    inline TextureControlFile& minFilter (GLint _minFilter) { mMinFilter = _minFilter; return *this; }
    inline TextureControlFile& magFilter (GLint _magFilter) { mMagFilter = _magFilter; return *this; }
    inline TextureControlFile& anisotropicFilter (GLfloat _anisotropicFilter) { mAnisotropicFilter = _anisotropicFilter; return *this; }

    inline TextureControlFile& wrap (GLenum _wrapS, GLenum _wrapT = 0, GLenum _wrapR = 0)
    {
        mWrapS = _wrapS;
        mWrapT = _wrapT;
        mWrapR = _wrapR;
        return *this;
    }

private:
    bool load(SharedTexture& texture);

    // ===================================================================================================== \/
    // ============================================================================================ OVERRIDE \/
    // ===================================================================================================== \/
public:
    virtual SharedTexture create(void);
    virtual bool update(SharedTexture& texture);

    // =================================================================================================== \/
    // ============================================================================================ FIELDS \/
    // =================================================================================================== \/
protected:
    SharedTextureDataControlFile mDataController;
    GLint mMinFilter;
    GLint mMagFilter;
    GLfloat mAnisotropicFilter;
    GLenum  mWrapS;
    GLenum  mWrapT;
    GLenum  mWrapR;
};

} // OpenGL
} // ACGL

#endif // ACGL_OPENGL_CONTROLLER_TEXTURECONTROLFILE_HH
