////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2011, Computer Graphics Group RWTH Aachen University         //
// All rights reserved.                                                       //
////////////////////////////////////////////////////////////////////////////////

#include <ACGL/OpenGL/Controller/TextureControlFile.hh>
#include <ACGL/OpenGL/Controller/TextureDataControlFileFactory.hh>

using namespace ACGL::OpenGL;

TextureControlFile::TextureControlFile(const std::string& _filename)
:   Resource::FileController<Texture>(_filename, Base::Settings::the()->getFullTexturePath()),
    mDataController(TextureDataControlFileFactory::the()->create(_filename)),
    mMinFilter(0),
    mMagFilter(0),
    mAnisotropicFilter(0.0),
    mWrapS(0),
    mWrapT(0),
    mWrapR(0)
{
    if(!mDataController)
        ACGL::Utils::error() << "No valid texture controller to load the image. Perhaps there is no loader for that file extension: " << _filename << std::endl;
}

TextureControlFile::TextureControlFile(const char* _filename)
:   Resource::FileController<Texture>(std::string(_filename), Base::Settings::the()->getFullTexturePath()),
    mDataController(TextureDataControlFileFactory::the()->create(std::string(_filename))),
    mMinFilter(0),
    mMagFilter(0),
    mAnisotropicFilter(0.0),
    mWrapS(0),
    mWrapT(0),
    mWrapR(0)
{
    if(!mDataController)
        ACGL::Utils::error() << "No valid texture controller to load the image. Perhaps there is no loader for that file extension: " << _filename << std::endl;
}

bool TextureControlFile::load(SharedTexture& texture)
{
    if(!mDataController)
        return false;

    SharedTextureData tempData = mDataController->create();

    if(!tempData)
        return false;

    texture->bind();
    texture->setImageData2D(
            tempData->getData(),
            tempData->getWidth(),
            tempData->getHeight(),
            tempData->getFormat(),
            tempData->getFormat(),
            tempData->getType());
    texture->generateMipmaps();
    return true;
}

SharedTexture TextureControlFile::create(void)
{
    updateFileModificationTime();

    SharedTexture texture(new Texture(GL_TEXTURE_2D));

    texture->bind();
    texture->setMinFilter(mMinFilter == 0 ? GL_LINEAR_MIPMAP_LINEAR : mMinFilter);
    texture->setMagFilter(mMagFilter == 0 ? GL_LINEAR : mMagFilter);
    if(mWrapS > 0) texture->setWrap(mWrapS, mWrapT, mWrapR);

    if(mAnisotropicFilter > 0.0)
        texture->setAnisotropicFilter(mAnisotropicFilter);

    if(!load(texture))
        return SharedTexture();
    return texture;
}

bool TextureControlFile::update(SharedTexture& texture)
{
    if(fileIsUpToDate())
        return false;

    if(!load(texture))
        return false;

    updateFileModificationTime();
    return true;
}
