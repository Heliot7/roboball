////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2011, Computer Graphics Group RWTH Aachen University         //
// All rights reserved.                                                       //
////////////////////////////////////////////////////////////////////////////////

#ifndef ACGL_OPENGL_CONTROLLER_TEXTURECONTROLFILEJPG_HH
#define ACGL_OPENGL_CONTROLLER_TEXTURECONTROLFILEJPG_HH

#include <ACGL/ACGL.hh>

#include <ACGL/Resource/FileController.hh>
#include <ACGL/Base/Settings.hh>
#include <ACGL/OpenGL/Objects/Texture.hh>
#include <ACGL/OpenGL/GL.hh>

namespace ACGL{
namespace OpenGL{

class TextureControlFileJPG : public Resource::FileController<Texture>
{
    // ========================================================================================================= \/
    // ============================================================================================ CONSTRUCTORS \/
    // ========================================================================================================= \/
public:
    TextureControlFileJPG(const std::string& _filename)
    :   Resource::FileController<Texture>(_filename, Base::Settings::the()->getFullTexturePath()),
        mMinFilter(0),
        mMagFilter(0),
        mAnisotropicFilter(0.0),
        mWrapS(0),
        mWrapT(0),
        mWrapR(0)
    {}
    virtual ~TextureControlFileJPG(void) {}

    // ==================================================================================================== \/
    // ============================================================================================ METHODS \/
    // ==================================================================================================== \/
public:
    inline TextureControlFileJPG& minFilter (GLint _minFilter) { mMinFilter = _minFilter; return *this; }
    inline TextureControlFileJPG& magFilter (GLint _magFilter) { mMagFilter = _magFilter; return *this; }
    inline TextureControlFileJPG& anisotropicFilter (GLfloat _anisotropicFilter) { mAnisotropicFilter = _anisotropicFilter; return *this; }

    inline TextureControlFileJPG& wrap (GLenum _wrapS, GLenum _wrapT = 0, GLenum _wrapR = 0)
    {
        mWrapS = _wrapS;
        mWrapT = _wrapT;
        mWrapR = _wrapR;
        return *this;
    }

private:
    bool loadJPG(SharedTexture& texture);

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
    GLint mMinFilter;
    GLint mMagFilter;
    GLfloat mAnisotropicFilter;
    GLenum  mWrapS;
    GLenum  mWrapT;
    GLenum  mWrapR;
};

} // OpenGL
} // ACGL

#endif // ACGL_OPENGL_CONTROLLER_TEXTURECONTROLFILEJPG_HH
