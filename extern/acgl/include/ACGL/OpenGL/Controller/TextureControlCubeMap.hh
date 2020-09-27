////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2011, Computer Graphics Group RWTH Aachen University         //
// All rights reserved.                                                       //
////////////////////////////////////////////////////////////////////////////////

#ifndef ACGL_OPENGL_CONTROLLER_TEXTURECONTROLCUBEMAP_HH
#define ACGL_OPENGL_CONTROLLER_TEXTURECONTROLCUBEMAP_HH

#include <ACGL/ACGL.hh>

#include <ACGL/Resource/BasicCreateController.hh>
#include <ACGL/OpenGL/Data/TextureData.hh>
#include <ACGL/OpenGL/Objects/Texture.hh>
#include <ACGL/OpenGL/GL.hh>

namespace ACGL{
namespace OpenGL{

class TextureControlCubeMap : public Resource::BasicCreateController<Texture>
{
    // ========================================================================================================= \/
    // ============================================================================================ CONSTRUCTORS \/
    // ========================================================================================================= \/
public:
    TextureControlCubeMap(void)
    :   Resource::BasicCreateController<Texture>(),
        mPositiveX(),
        mNegativeX(),
        mPositiveY(),
        mNegativeY(),
        mPositiveZ(),
        mNegativeZ(),
        mSize(0),
        mInternalFormat(GL_RGBA),
        mFormat(GL_RGBA),
        mType(GL_UNSIGNED_BYTE),
        mMinFilter(GL_LINEAR),
        mMagFilter(GL_LINEAR),
        mAnisotropicFilter(0.0),
        mWrapS(GL_CLAMP_TO_EDGE),
        mWrapT(GL_CLAMP_TO_EDGE),
        mWrapR(GL_CLAMP_TO_EDGE)
    {}
    virtual ~TextureControlCubeMap(void) {}

    // ==================================================================================================== \/
    // ============================================================================================ METHODS \/
    // ==================================================================================================== \/
public:
    inline TextureControlCubeMap& positiveX (const SharedTextureData& _data) { mPositiveX = _data; return *this; }
    inline TextureControlCubeMap& negativeX (const SharedTextureData& _data) { mNegativeX = _data; return *this; }
    inline TextureControlCubeMap& positiveY (const SharedTextureData& _data) { mPositiveY = _data; return *this; }
    inline TextureControlCubeMap& negativeY (const SharedTextureData& _data) { mNegativeY = _data; return *this; }
    inline TextureControlCubeMap& positiveZ (const SharedTextureData& _data) { mPositiveZ = _data; return *this; }
    inline TextureControlCubeMap& negativeZ (const SharedTextureData& _data) { mNegativeZ = _data; return *this; }


    inline TextureControlCubeMap& wrap (GLenum _wrapS, GLenum _wrapT = 0, GLenum _wrapR = 0)
    {
        mWrapS = _wrapS;
        mWrapT = _wrapT;
        mWrapR = _wrapR;
        return *this;
    }

    inline TextureControlCubeMap& size              (GLsizei _size)            { mSize = _size;                           return *this; }
    inline TextureControlCubeMap& internalFormat    (GLenum _internalFormat)   { mInternalFormat = _internalFormat;       return *this; }
    inline TextureControlCubeMap& format            (GLenum _format)           { mFormat = _format;                       return *this; }
    inline TextureControlCubeMap& type              (GLenum type)              { mType = type;                            return *this; }
    inline TextureControlCubeMap& minFilter         (GLint _minFilter)         { mMinFilter = _minFilter;                 return *this; }
    inline TextureControlCubeMap& magFilter         (GLint _magFilter)         { mMagFilter = _magFilter;                 return *this; }
    inline TextureControlCubeMap& anisotropicFilter (GLint _anisotropicFilter) { mAnisotropicFilter = _anisotropicFilter; return *this; }

    // ===================================================================================================== \/
    // ============================================================================================ OVERRIDE \/
    // ===================================================================================================== \/
public:
    virtual SharedTexture create(void);

    // =================================================================================================== \/
    // ============================================================================================ FIELDS \/
    // =================================================================================================== \/
protected:
    SharedTextureData mPositiveX;
    SharedTextureData mNegativeX;
    SharedTextureData mPositiveY;
    SharedTextureData mNegativeY;
    SharedTextureData mPositiveZ;
    SharedTextureData mNegativeZ;
    GLsizei mSize;
    GLenum  mInternalFormat;
    GLenum  mFormat;
    GLenum  mType;
    GLint   mMinFilter;
    GLint   mMagFilter;
    GLfloat mAnisotropicFilter;
    GLenum  mWrapS;
    GLenum  mWrapT;
    GLenum  mWrapR;
};

} // OpenGL
} // ACGL

#endif // ACGL_OPENGL_CONTROLLER_TEXTURECONTROL_HH
