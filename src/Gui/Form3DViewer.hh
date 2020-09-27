////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2011, Computer Graphics Group RWTH Aachen University         //
// All rights reserved.                                                       //
////////////////////////////////////////////////////////////////////////////////

#ifndef ACGL_TEMPLATE_FORM3DVIEWER_HH
#define ACGL_TEMPLATE_FORM3DVIEWER_HH

#include "../Model/World.hh"
#include "../View/ViewWorld.hh"
#include "../Control/ControlWorld.hh"

#include <QtOpenGL/QGLWidget>
#include <QtCore/QTime>

class MainWindow;

class Form3DViewer : public QGLWidget
{
    Q_OBJECT

public:
    Form3DViewer(
        QWidget *_pParent,
        QGLFormat _openGLFormat);
    virtual ~Form3DViewer(void);

signals:
    void signalUpdateFPS(double _fps);

protected:
    void initializeGL(void);
    void paintGL(void);
    void resizeGL(int iWidth, int iHeight);

    void keyPressEvent     ( QKeyEvent*   pKeyEvent);
    void keyReleaseEvent   ( QKeyEvent*   pKeyEvent);
    void mousePressEvent   ( QMouseEvent* pMouseEvent);
    void mouseReleaseEvent ( QMouseEvent* pMouseEvent);
    void mouseMoveEvent    ( QMouseEvent* pMouseEvent);
    void wheelEvent        ( QWheelEvent* pWheelEvent);

protected:

    std::tr1::shared_ptr<World> mpWorld;
    std::tr1::shared_ptr<ViewWorld> mpViewWorld;
    std::tr1::shared_ptr<ControlWorld> mpControlWorld;

    QPoint mInitMousePosition;
    QCursor mArrowCursor;
    QCursor mBlankCursor;

    QTime mRenderLoopTimer; // measures the time of one frame, used for camera movement
    QTime mFPSTimer;        // used for FPS calculation
};


#endif // ACGL_TEMPLATE_FORM3DVIEWER_HH
