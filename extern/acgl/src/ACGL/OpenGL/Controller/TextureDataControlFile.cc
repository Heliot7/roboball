////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2011, Computer Graphics Group RWTH Aachen University         //
// All rights reserved.                                                       //
////////////////////////////////////////////////////////////////////////////////

#include <ACGL/OpenGL/Controller/TextureDataControlFile.hh>

using namespace ACGL::OpenGL;

SharedTextureData TextureDataControlFile::create(void)
{
    updateFileModificationTime();

    SharedTextureData texture(new TextureData());

    if(load(texture))
        return texture;

    return SharedTextureData();
}

bool TextureDataControlFile::update(SharedTextureData& _texture)
{
    if(fileIsUpToDate())
        return false;

    if(!load(_texture))
        return false;

    updateFileModificationTime();
    return true;
}
