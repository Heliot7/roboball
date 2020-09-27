////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2011, Computer Graphics Group RWTH Aachen University         //
// All rights reserved.                                                       //
////////////////////////////////////////////////////////////////////////////////

#include <ACGL/OpenGL/Controller/TextureControlCubeMap.hh>

using namespace ACGL::Utils;
using namespace ACGL::OpenGL;

SharedTexture TextureControlCubeMap::create(void)
{
    SharedTexture texture(new Texture(GL_TEXTURE_CUBE_MAP));
    texture->bind();
    texture->setMinFilter(mMinFilter);
    texture->setMagFilter(mMagFilter);
    texture->setWrap(mWrapS, mWrapT, mWrapR);

    if(mAnisotropicFilter > 0.0) texture->setAnisotropicFilter(mAnisotropicFilter);

    texture->setCubeMapFormat(
        mSize,
        mInternalFormat,
        mFormat,
        mType);

    if(mPositiveX)
    {
        if(mPositiveX->getWidth() != mSize || mPositiveX->getHeight() != mSize)
        {
            error() << "Size of positive x does not match the definition in the cube map!" << std::endl;
            texture->setImageDataCubeMapPositiveX();
        }
        else
        {
            texture->setImageDataCubeMapPositiveX(mPositiveX->getFormat(), mPositiveX->getType(), mPositiveX->getData());
        }
    }

    if(mNegativeX)
    {
        if(mNegativeX->getWidth() != mSize || mNegativeX->getHeight() != mSize)
        {
            error() << "Size of negative x does not match the definition in the cube map!" << std::endl;
            texture->setImageDataCubeMapNegativeX();
        }
        else
        {
            texture->setImageDataCubeMapNegativeX(mNegativeX->getFormat(), mNegativeX->getType(), mNegativeX->getData());
        }
    }

    if(mPositiveY)
    {
        if(mPositiveY->getWidth() != mSize || mPositiveY->getHeight() != mSize)
        {
            error() << "Size of positive y does not match the definition in the cube map!" << std::endl;
            texture->setImageDataCubeMapPositiveY();
        }
        else
        {
            texture->setImageDataCubeMapPositiveY(mPositiveY->getFormat(), mPositiveY->getType(), mPositiveY->getData());
        }
    }

    if(mNegativeY)
    {
        if(mNegativeY->getWidth() != mSize || mNegativeY->getHeight() != mSize)
        {
            error() << "Size of negative y does not match the definition in the cube map!" << std::endl;
            texture->setImageDataCubeMapNegativeY();
        }
        else
        {
            texture->setImageDataCubeMapNegativeY(mNegativeY->getFormat(), mNegativeY->getType(), mNegativeY->getData());
        }
    }

    if(mPositiveZ)
    {
        if(mPositiveZ->getWidth() != mSize || mPositiveZ->getHeight() != mSize)
        {
            error() << "Size of positive z does not match the definition in the cube map!" << std::endl;
            texture->setImageDataCubeMapPositiveZ();
        }
        else
        {
            texture->setImageDataCubeMapPositiveZ(mPositiveZ->getFormat(), mPositiveZ->getType(), mPositiveZ->getData());
        }
    }

    if(mNegativeZ)
    {
        if(mNegativeZ->getWidth() != mSize || mNegativeZ->getHeight() != mSize)
        {
            error() << "Size of negative z does not match the definition in the cube map!" << std::endl;
            texture->setImageDataCubeMapNegativeZ();
        }
        else
        {
            texture->setImageDataCubeMapNegativeZ(mNegativeZ->getFormat(), mNegativeZ->getType(), mNegativeZ->getData());
        }
    }
    return texture;
}

