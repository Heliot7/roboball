////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2011, Computer Graphics Group RWTH Aachen University         //
// All rights reserved.                                                       //
////////////////////////////////////////////////////////////////////////////////

#include <ACGL/OpenGL/Controller/TextureControlFileJPG.hh>

using namespace ACGL::OpenGL;

SharedTexture TextureControlFileJPG::create(void)
{
    updateFileModificationTime();

    SharedTexture texture(new Texture(GL_TEXTURE_2D));

    texture->bind();
    texture->setMinFilter(mMinFilter == 0 ? GL_LINEAR_MIPMAP_LINEAR : mMinFilter);
    texture->setMagFilter(mMagFilter == 0 ? GL_LINEAR : mMagFilter);
    if(mWrapS > 0) texture->setWrap(mWrapS, mWrapT, mWrapR);

    if(mAnisotropicFilter > 0.0)
        texture->setAnisotropicFilter(mAnisotropicFilter);

    if(loadJPG(texture))
        return texture;

    return SharedTexture();
}

bool TextureControlFileJPG::update(SharedTexture& texture)
{
    if(fileIsUpToDate())
        return false;

    if(!loadJPG(texture))
        return false;

    updateFileModificationTime();
    return true;
}
