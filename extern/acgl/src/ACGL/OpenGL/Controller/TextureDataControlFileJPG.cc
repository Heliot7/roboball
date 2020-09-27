////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2011, Computer Graphics Group RWTH Aachen University         //
// All rights reserved.                                                       //
////////////////////////////////////////////////////////////////////////////////

#include <ACGL/OpenGL/Controller/TextureDataControlFileJPG.hh>
#include <ACGL/OpenGL/Controller/TextureDataControlFileFactory.hh>

#include <QtGui/QImage>
#include <QtOpenGL/QGLWidget>

using namespace ACGL;
using namespace ACGL::OpenGL;

bool TextureDataControlFileJPG::load(SharedTextureData& texture) const
{
    QImage image = QImage(QString(getFullFilePath().c_str()));

    if(image.isNull())
    {
        ACGL::Utils::error() << "Loading image " << getFullFilePath() << " has failed!" << std::endl;
        return false;
    }

    image = QGLWidget::convertToGLFormat(image);
    GLubyte *pImageData = new GLubyte[image.byteCount()];
    memcpy(pImageData, image.bits(), image.byteCount());
    texture->setData(pImageData);
    texture->setWidth(image.width());
    texture->setHeight(image.height());
    return true;
}

int_t TextureDataControlFileJPG::sTypeID = TextureDataControlFileFactory::the()->registerType("jpg", &TextureDataControlFileJPG::creator);
