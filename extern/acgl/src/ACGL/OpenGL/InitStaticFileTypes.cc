////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2011, Computer Graphics Group RWTH Aachen University         //
// All rights reserved.                                                       //
////////////////////////////////////////////////////////////////////////////////

#include <ACGL/OpenGL/InitStaticFileTypes.hh>

#include <ACGL/OpenGL/Controller/TextureDataControlFileJPG.hh>
#include <ACGL/OpenGL/Controller/TextureDataControlFilePNG.hh>

using namespace ACGL::OpenGL;

void ACGL::OpenGL::initStaticFileTypes(void)
{
    ACGL::Utils::debug() << "TextureDataControlFileJPG type ID: " << TextureDataControlFileJPG::getTypeID() << std::endl;
    ACGL::Utils::debug() << "TextureDataControlFilePNG type ID: " << TextureDataControlFilePNG::getTypeID() << std::endl;
}

