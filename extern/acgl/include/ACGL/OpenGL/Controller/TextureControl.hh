////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2011, Computer Graphics Group RWTH Aachen University         //
// All rights reserved.                                                       //
////////////////////////////////////////////////////////////////////////////////

#ifndef ACGL_OPENGL_CONTROLLER_TEXTURECONTROL_HH
#define ACGL_OPENGL_CONTROLLER_TEXTURECONTROL_HH

#include <ACGL/ACGL.hh>

#include <ACGL/Resource/BasicCreateController.hh>
#include <ACGL/OpenGL/Objects/Texture.hh>
#include <ACGL/OpenGL/GL.hh>

namespace ACGL{
namespace OpenGL{

class TextureControl : public Resource::BasicCreateController<Texture>
{
    // ========================================================================================================= \/
    // ============================================================================================ CONSTRUCTORS \/
    // ========================================================================================================= \/
public:
    TextureControl(void)
    :   Resource::BasicCreateController<Texture>(),
        mWidth(0),
        mHeight(0),
        mDepth(0),
        mInternalFormat(GL_RGBA),
        mTarget(GL_TEXTURE_2D),
        mFormat(GL_RGBA),
        mType(GL_UNSIGNED_BYTE),
        mMinFilter(0),
        mMagFilter(0),
        mAnisotropicFilter(0.0),
        mWrapS(0),
        mWrapT(0),
        mWrapR(0)
    {}
    virtual ~TextureControl(void) {}

    // ==================================================================================================== \/
    // ============================================================================================ METHODS \/
    // ==================================================================================================== \/
public:
    inline TextureControl& size (GLsizei _width, GLsizei _height = 0, GLsizei _depth = 0)
    {
        mWidth = _width;
        mHeight = _height;
        mDepth = _depth;
        return *this;
    }

    inline TextureControl& wrap (GLenum _wrapS, GLenum _wrapT = 0, GLenum _wrapR = 0)
    {
        mWrapS = _wrapS;
        mWrapT = _wrapT;
        mWrapR = _wrapR;
        return *this;
    }

    inline TextureControl& internalFormat    (GLenum _internalFormat)   { mInternalFormat = _internalFormat;       return *this; }
    inline TextureControl& target            (GLenum _target)           { mTarget = _target;                       return *this; }
    inline TextureControl& format            (GLenum _format)           { mFormat = _format;                       return *this; }
    inline TextureControl& type              (GLenum type)              { mType = type;                            return *this; }
    inline TextureControl& minFilter         (GLint _minFilter)         { mMinFilter = _minFilter;                 return *this; }
    inline TextureControl& magFilter         (GLint _magFilter)         { mMagFilter = _magFilter;                 return *this; }
    inline TextureControl& anisotropicFilter (GLint _anisotropicFilter) { mAnisotropicFilter = _anisotropicFilter; return *this; }

    // ===================================================================================================== \/
    // ============================================================================================ OVERRIDE \/
    // ===================================================================================================== \/
public:
    virtual SharedTexture create(void)
    {
        SharedTexture texture(new Texture(mTarget));
        texture->bind();
        if(mMinFilter > 0)           texture->setMinFilter(mMinFilter);
        if(mMagFilter > 0)           texture->setMagFilter(mMagFilter);
        if(mWrapS > 0)               texture->setWrap(mWrapS, mWrapT, mWrapR);
        if(mAnisotropicFilter > 0.0) texture->setAnisotropicFilter(mAnisotropicFilter);
        texture->setImageData(
            NULL,
            mWidth,
            mHeight,
            mDepth,
            mInternalFormat,
            mFormat,
            mType);
        return texture;
    }

    // =================================================================================================== \/
    // ============================================================================================ FIELDS \/
    // =================================================================================================== \/
protected:
    GLsizei mWidth;
    GLsizei mHeight;
    GLsizei mDepth;
    GLenum  mInternalFormat;
    GLenum  mTarget;
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
