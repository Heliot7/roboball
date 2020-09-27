////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2011, Computer Graphics Group RWTH Aachen University         //
// All rights reserved.                                                       //
////////////////////////////////////////////////////////////////////////////////

#ifndef ACGL_OPENGL_OBJECTS_TEXTURE_HH
#define ACGL_OPENGL_OBJECTS_TEXTURE_HH

/*
 * A Texture wrapps the OpenGL texture. To fill these with data from image files a
 * matching TextureControllerFile* is needed.
 */

#include <ACGL/ACGL.hh>

#include <ACGL/Base/Macros.hh>
#include <ACGL/OpenGL/GL.hh>
#include <ACGL/OpenGL/Tools.hh>
#include <ACGL/Math/Math.hh>

#include <vector>
#include <tr1/memory>

namespace ACGL{
namespace OpenGL{

class Texture
{
    ACGL_NOT_COPYABLE(Texture)

    // ========================================================================================================= \/
    // ============================================================================================ CONSTRUCTORS \/
    // ========================================================================================================= \/
public:
    //!
    /*!
        Default texture parameters taken from: http://www.opengl.org/sdk/docs/man/xhtml/glTexParameter.xml
     */
    Texture(GLenum _target)
    :   mObjectName(0),
        mTarget(_target),
        mWidth(0),
        mHeight(0),
        mDepth(0),
        mInternalFormat(GL_RGBA),
        mFormat(GL_RGBA),
        mType(GL_UNSIGNED_BYTE),
        mMinFilter(GL_NEAREST_MIPMAP_LINEAR),
        mMagFilter(GL_LINEAR),
        mWrapS(GL_REPEAT),
        mWrapT(GL_REPEAT),
        mWrapR(GL_REPEAT)
    {
        glGenTextures(1, &mObjectName);
        if (openGLCriticalErrorOccured() ) {
            ACGL::Utils::error() << "could not generate texture!" << std::endl;
        }
    }

    virtual ~Texture(void)
    {
        // object name 0 will get ignored by OpenGL
        glDeleteTextures(1, &mObjectName);
    }

    // ==================================================================================================== \/
    // ============================================================================================ GETTERS \/
    // ==================================================================================================== \/
public:
    inline GLuint  operator()        (void) const { return mObjectName;     }
    inline GLuint  getObjectName     (void) const { return mObjectName;     }
    inline GLenum  getTarget         (void) const { return mTarget;         }
    inline GLsizei getWidth          (void) const { return mWidth;          }
    inline GLsizei getHeight         (void) const { return mHeight;         }
    inline GLsizei getDepth          (void) const { return mDepth;          }
    inline GLenum  getInternalFormat (void) const { return mInternalFormat; }
    inline GLenum  getFormat         (void) const { return mFormat;         }
    inline GLenum  getType           (void) const { return mType;           }
    inline GLint   getMinFilter      (void) const { return mMinFilter;      }
    inline GLint   getMagFilter      (void) const { return mMagFilter;      }
    inline GLenum  getWrapS          (void) const { return mWrapS;          }
    inline GLenum  getWrapT          (void) const { return mWrapT;          }
    inline GLenum  getWrapR          (void) const { return mWrapR;          }

    // ===================================================================================================== \/
    // ============================================================================================ WRAPPERS \/
    // ===================================================================================================== \/
public:
    //! Activate texture unit and bind this texture.
    inline void bind(GLenum _textureUnit) const
    {
        glActiveTexture(GL_TEXTURE0 + _textureUnit);
        glBindTexture(mTarget, mObjectName);
        openGLRareError();
    }
    
    //! Bind this texture.
    inline void bind(void) const
    {
        glBindTexture(mTarget, mObjectName);
        openGLRareError();
    }

    //! Note: The function is not const, because it changes the corresponding GPU data
    inline void setMinFilter(GLint _value)
    {
        mMinFilter = _value;
        glBindTexture(mTarget, mObjectName);
        glTexParameteri(mTarget, GL_TEXTURE_MIN_FILTER, mMinFilter);
        openGLRareError();
    }

    //! Note: The function is not const, because it changes the corresponding GPU data
    inline void setMagFilter(GLint _value)
    {
        mMagFilter = _value;
        glBindTexture(mTarget, mObjectName);
        glTexParameteri(mTarget, GL_TEXTURE_MAG_FILTER, mMagFilter);
        openGLRareError();
    }

    //! Note: The function is not const, because it changes the corresponding GPU data
    inline void setWrap(GLenum _wrapS, GLenum _wrapT = 0, GLenum _wrapR = 0)
    {
        glBindTexture(mTarget, mObjectName);

        mWrapS = _wrapS;
        glTexParameteri(mTarget, GL_TEXTURE_WRAP_S, mWrapS);

        if(_wrapT != 0)
        {
            mWrapT = _wrapT;
            glTexParameteri(mTarget, GL_TEXTURE_WRAP_T, mWrapT);
        }

        if(_wrapR != 0)
        {
            mWrapR = _wrapR;
            glTexParameteri(mTarget, GL_TEXTURE_WRAP_R, mWrapR);
        }

        openGLRareError();
    }

    //! _sampleCount = 1.0 to deactivate anisotrop filtering, maximum is often 16. If a value is too high it will get clamped to the maximum
    void setAnisotropicFilter( GLfloat _sampleCount )
    {
#ifdef ACGL_USE_GLEW
        if (GLEW_EXT_texture_filter_anisotropic) {
            GLfloat maxAnisotropicSamples;
            glGetFloatv( GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &maxAnisotropicSamples );
            _sampleCount = std::max( 1.0f, _sampleCount );
            _sampleCount = std::min( maxAnisotropicSamples, _sampleCount );
            glBindTexture(mTarget, mObjectName);
            glTexParameterf( mTarget, GL_TEXTURE_MAX_ANISOTROPY_EXT, _sampleCount);
            openGLRareError();
        } else
#endif
        {
            // anisotropic filtering will just increase the image quality, so this is just
            // a warning and no error
            ACGL::Utils::warning() << "Anisotropic filtering is not supported, ignored" << std::endl;
        }
    }

    //! Set texture data for 1D, 2D or 3D textures
    inline void setImageData(const GLvoid* _pData = NULL)
    {
        if(mWidth > 0 && mHeight > 0 && mDepth > 0)
        {
            //3D
        }
        else if(mWidth > 0 && mHeight > 0)
        {
            setImageData2D(_pData);
        }
        else if(mWidth > 0)
        {
            //1D
        }
    }
    //! Set texture data for 1D, 2D or 3D textures
    inline void setImageData(
        const GLvoid* _pData,
        GLsizei _width,
        GLsizei _height,
        GLsizei _depth)
    {
        mWidth = _width;
        mHeight = _height;
        mDepth = _depth;
        if(mWidth > 0 && mHeight > 0 && mDepth > 0)
        {
            //3D
        }
        else if(mWidth > 0 && mHeight > 0)
        {
            setImageData2D(_pData);
        }
        else if(mWidth > 0)
        {
            //1D
        }
    }

    //! Set texture data for 1D, 2D or 3D textures
    inline void setImageData(
        const GLvoid* _pData,
        GLsizei _width,
        GLsizei _height,
        GLsizei _depth,
        GLenum _internalFormat,
        GLenum _format,
        GLenum _type)
    {
        mWidth = _width;
        mHeight = _height;
        mDepth = _depth;
        mInternalFormat = _internalFormat;
        mFormat = _format;
        mType = _type;
        if(mWidth > 0 && mHeight > 0 && mDepth > 0)
        {
            //3D
        }
        else if(mWidth > 0 && mHeight > 0)
        {
            setImageData2D(_pData);
        }
        else if(mWidth > 0)
        {
            //1D
        }
    }

    //! Set texture data
    inline void setImageData2D(
        const GLvoid* _pData,
        GLsizei _width,
        GLsizei _height,
        GLenum  _internalFormat,
        GLenum  _format,
        GLenum  _type)
    {
        mInternalFormat = _internalFormat;
        mFormat         = _format;
        mType           = _type;
        setImageData2D( _pData, _width, _height );
    }

    //! Set texture data
    inline void setImageData2D(
        const GLvoid* _pData,
        GLsizei _width,
        GLsizei _height)
    {
        mWidth  = _width;
        mHeight = _height;
        setImageData2D( _pData );
    }

    //! Set texture data using the specified target for uploading the data
    inline void setImageData2D(const GLvoid* _pData = NULL)
    {
        setImageData2D(mTarget, mFormat, mType, _pData);
    }

    //! Set format for the cube maps that are uploaded
    inline void setCubeMapFormat(
        GLsizei _size,
        GLenum _internalFormat)
    {
        mWidth = _size;
        mHeight = _size;
        mDepth = 0;
        mInternalFormat = _internalFormat;
    }

    //! Set format for the cube maps that are uploaded including a default format and type
    inline void setCubeMapFormat(
        GLsizei _size,
        GLenum _internalFormat,
        GLenum _format,
        GLenum _type)
    {
        mWidth = _size;
        mHeight = _size;
        mDepth = 0;
        mInternalFormat = _internalFormat;
        mFormat = _format;
        mType = _type;
    }

    //! Set texture data for cube maps using the default format and type
    /// @{
    inline void setImageDataCubeMapPositiveX(const GLvoid* _pData = NULL) { setImageData2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, mFormat, mType, _pData); }
    inline void setImageDataCubeMapNegativeX(const GLvoid* _pData = NULL) { setImageData2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, mFormat, mType, _pData); }
    inline void setImageDataCubeMapPositiveY(const GLvoid* _pData = NULL) { setImageData2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, mFormat, mType, _pData); }
    inline void setImageDataCubeMapNegativeY(const GLvoid* _pData = NULL) { setImageData2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, mFormat, mType, _pData); }
    inline void setImageDataCubeMapPositiveZ(const GLvoid* _pData = NULL) { setImageData2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, mFormat, mType, _pData); }
    inline void setImageDataCubeMapNegativeZ(const GLvoid* _pData = NULL) { setImageData2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, mFormat, mType, _pData); }
    /// @}

    //! Set texture data for cube maps using a specific upload format and type per face
    /// @{
    inline void setImageDataCubeMapPositiveX(GLenum _format, GLenum _type, const GLvoid* _pData = NULL) { setImageData2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, _format, _type, _pData); }
    inline void setImageDataCubeMapNegativeX(GLenum _format, GLenum _type, const GLvoid* _pData = NULL) { setImageData2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, _format, _type, _pData); }
    inline void setImageDataCubeMapPositiveY(GLenum _format, GLenum _type, const GLvoid* _pData = NULL) { setImageData2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, _format, _type, _pData); }
    inline void setImageDataCubeMapNegativeY(GLenum _format, GLenum _type, const GLvoid* _pData = NULL) { setImageData2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, _format, _type, _pData); }
    inline void setImageDataCubeMapPositiveZ(GLenum _format, GLenum _type, const GLvoid* _pData = NULL) { setImageData2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, _format, _type, _pData); }
    inline void setImageDataCubeMapNegativeZ(GLenum _format, GLenum _type, const GLvoid* _pData = NULL) { setImageData2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, _format, _type, _pData); }
    /// @}

    //! Set texture data for some mipmap level.
    /*!
        If you upload a texture for a higher mipmap level, the function will automatically determine
        its size calculating (w,h)/2^level where w and h are the width and height of the base texture.
        Note: The function is not const, because it changes the corresponding GPU data
     */
    inline void setImageDataMipMap2D(
        const GLvoid* _pData,
        GLint         _mipmapLevel,
        GLsizei       _width = 0,
        GLsizei       _height = 0)
    {
        glBindTexture(mTarget, mObjectName);
        glTexImage2D(
            mTarget,
            _mipmapLevel,
            mInternalFormat,
            _width > 0 ? _width : mWidth  / GLsizei(Math::Functions::pow(2.0f, float(_mipmapLevel))),
            _height > 0 ? _height : mHeight / GLsizei(Math::Functions::pow(2.0f, float(_mipmapLevel))),
            0,//no border
            mFormat,
            mType,
            _pData);
    }

    //! Set data for specific area within the 2D texture
    //! Note: The function is not const, because it changes the corresponding GPU data
    inline void setSubImageData2D(
            const GLvoid* _pData,
            GLint _x,
            GLint _y,
            GLsizei _width,
            GLsizei _height)
    {
        glBindTexture(mTarget, mObjectName);
        glTexSubImage2D(
            mTarget,
            0,
            _x,
            _y,
            _width,
            _height,
            mFormat,
            mType,
            _pData);
    }

    //! Set data for specific area within the 3D texture
    //! Note: The function is not const, because it changes the corresponding GPU data
    inline void setSubImageData3D(
            const GLvoid* _pData,
            GLint _x,
            GLint _y,
            GLint _z,
            GLsizei _width,
            GLsizei _height,
            GLsizei _depth)
    {
        glBindTexture(mTarget, mObjectName);
        glTexSubImage3D(
            mTarget,
            0,
            _x,
            _y,
            _z,
            _width,
            _height,
            _depth,
            mFormat,
            mType,
            _pData);
    }
    
    //! Generate mipmaps from the current base texture (i.e. the texture from level 0)
    //! Note: The function is not const, because it changes the corresponding GPU data
    void generateMipmaps(void)
    {
        glBindTexture(mTarget, mObjectName);
#if (!defined ACGL_OPENGL_PROFILE_CORE)
        // on some ATI systems texturing has to be enabled to generate MipMaps
        // this is not needed by the spec an deprecated on core profiles (generates
        // an error on MacOS X Lion)
        glEnable(mTarget);
        openGLRareError();
#endif
#ifdef ACGL_OPENGL_VERSION_21
        // OpenGL 2 way to generate MipMaps
        glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
#else
        glGenerateMipmap(mTarget);
#endif
        openGLRareError();
    } 

private:
    //! Set texture data
    inline void setImageData2D(GLenum _uploadTarget, GLenum _uploadFormat, GLenum _uploadType, const GLvoid* _pData = NULL)
    {
        glBindTexture(mTarget, mObjectName);
        glTexImage2D(
            _uploadTarget,
            0,
            mInternalFormat,
            mWidth,
            mHeight,
            0,//no border
            _uploadFormat,
            _uploadType,
            _pData);
        if (openGLCriticalErrorOccured() ) {
            ACGL::Utils::error() << "could not generate texture!" << std::endl;
        }
    }

    // =================================================================================================== \/
    // ============================================================================================ FIELDS \/
    // =================================================================================================== \/
private:
    GLuint  mObjectName;
    GLenum  mTarget;
    GLsizei mWidth;
    GLsizei mHeight;
    GLsizei mDepth;
    GLenum  mInternalFormat;
    GLenum  mFormat;
    GLenum  mType;
    GLint   mMinFilter;
    GLint   mMagFilter;
    GLenum  mWrapS;
    GLenum  mWrapT;
    GLenum  mWrapR;
};

ACGL_SHARED_TYPEDEF(Texture)


} // OpenGL
} // ACGL

#endif // ACGL_OPENGL_OBJECTS_TEXTURE_HH
