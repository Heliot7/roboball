////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2011, Computer Graphics Group RWTH Aachen University         //
// All rights reserved.                                                       //
////////////////////////////////////////////////////////////////////////////////

#include <ACGL/OpenGL/Controller/TextureControlFileJPG.hh>

#include <QtGui/QImage>
#include <QtOpenGL/QGLWidget>

using namespace ACGL::Base;
using namespace ACGL::OpenGL;
using namespace ACGL::Utils;

bool TextureControlFileJPG::loadJPG(SharedTexture& texture)
{
    QImage image = QImage(QString(getFullFilePath().c_str()));

    if(image.isNull())
    {
        error() << "Loading image " << getFullFilePath() << " has failed!" << std::endl;
        return false;
    }

    image = QGLWidget::convertToGLFormat(image);
    texture->bind();
    texture->setImageData2D(
            image.bits(),
            image.width(),
            image.height(),
            GL_RGBA,
            GL_RGBA,
            GL_UNSIGNED_BYTE);
    texture->generateMipmaps();
    return true;
}
