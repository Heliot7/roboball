////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2011, Computer Graphics Group RWTH Aachen University         //
// All rights reserved.                                                       //
////////////////////////////////////////////////////////////////////////////////

#include "Gui/MainWindow.hh"

#include <QtGui/QApplication>
#include <cstdlib>
#include <string>
#include <iostream>
#include <QGLWidget>

using namespace std;

int main(int argc, char *argv[])
{
    QGL::setPreferredPaintEngine(QPaintEngine::OpenGL);
    QApplication app(argc, argv);

    // Using our own customized cursos
    // app.setOverrideCursor(QCursor(QPixmap(":/cursor/cursor.gif"),0,0));

    // this will be our QT MainWindow:
    MainWindow window(NULL);
    window.showFullScreen();
    window.setWindowFlags(Qt::WindowStaysOnTopHint);
    app.setActiveWindow(&window);
    window.show();

    return app.exec();
}

