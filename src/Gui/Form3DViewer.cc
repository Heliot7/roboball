////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2011, Computer Graphics Group RWTH Aachen University         //
// All rights reserved.                                                       //
////////////////////////////////////////////////////////////////////////////////

#include "Form3DViewer.hh"
#include "../View/Renderer.hh"

#if defined(__APPLE__)
#include "../LionOpenGL.hh"
#endif

#include <ACGL/OpenGL/Managers.hh>
#include <ACGL/OpenGL/Tools.hh>

#include <QString>

using namespace ACGL::OpenGL;

Form3DViewer::Form3DViewer(
    QWidget *_pParent,
    QGLFormat _openGLFormat)
#if (defined(__APPLE__) && defined(ACGL_OPENGL_PROFILE_CORE))
:   QGLWidget( new LionOpenGL32( _openGLFormat ) ),
#else
:   QGLWidget(_openGLFormat, _pParent),
#endif
    mpWorld(new World(25)),
    mpViewWorld(new Renderer(mpWorld, this)),
    mpControlWorld(new ControlWorld(mpWorld)),
    mInitMousePosition(),
    mArrowCursor(),
    mBlankCursor(),
    mRenderLoopTimer(),
    mFPSTimer()
{
    setMinimumSize(800,600);
    mArrowCursor.setShape(Qt::ArrowCursor);
    mBlankCursor.setShape(Qt::BlankCursor);

    setFocusPolicy(Qt::StrongFocus);
    activateWindow();
}

Form3DViewer::~Form3DViewer(void)
{}

/*
 * This will set everything graphics related up before the renderloop gets called the first time.
 */
void Form3DViewer::initializeGL(void)
{
    ACGL::init();
    openGLCriticalErrorOccured();

    mpViewWorld->init();

    // QTime timers used, e.g., for FPS measurements:
    mRenderLoopTimer.start();
    mFPSTimer.start();
}

/////////////////////////////////////////////////////////////////////////////////////////////////
//
// This gets called as often as possible to render our game.
//
void Form3DViewer::paintGL(void)
{

#ifdef ACGL_OPENGL_PROFILE_CORE
    static bool firstFrame = true;
    if (firstFrame) {
        firstFrame = !firstFrame;
        // QT will call glGetString(GL_EXTENSIONS); prior to the first frame rendering, which will generate an
        // invalid enum on core contexts
        glGetError(); // just to get silently rid of the error
    }
#endif
    openGLCommonError();

    // update all resources:
    // this is something you don't want to do in a final application but it helps during
    // development because you can change for example shader files, save and they get reloaded
    // automatically!
    ShaderProgramFileManager::the()->updateAll();
    VertexBufferObjectFileManager::the()->updateAll();
    TextureFileManager::the()->updateAll();

    // update the scene dependent on the elapsed time
    double dElapsedTime = mRenderLoopTimer.elapsed() / 1000.0; // convert msec to sec
    mRenderLoopTimer.restart();
    mpControlWorld->update((float)dElapsedTime);

    // The FPS counter shown in the title of the window gets set here
    static int frameCount = 0;
    frameCount++;
    int secoundsToMeasure = 1;

    double elapsedTimeInMsec = mFPSTimer.elapsed();

    if (elapsedTimeInMsec > (1000*secoundsToMeasure)) {
       double elapsedTimeInSec = elapsedTimeInMsec/1000.0;
       double fps = frameCount / (double)elapsedTimeInSec;
       emit signalUpdateFPS(fps);
       frameCount = 0;
       mFPSTimer.restart();
    }
    /*
    QPainter painter;
    painter.begin(this);
    painter.beginNativePainting();
    */
    //program->bind();
    mpViewWorld->paint(dElapsedTime);
    //program->release();
    //painter.endNativePainting();

    // Paint the info and exit buttons.
    //painter.setRenderHint(QPainter::SmoothPixmapTransform, true);

    //painter.drawText(/*infoRect.x() * 1.5f, infoRect.y() + 100 * 0.07f*/QPoint(100,100), QString("HOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOLA"));
    //painter.drawLine(QPoint(100,100),QPoint(500,500));
    //painter.end();

    // let QT update the widget:
    update();
}

/*
 * When the window gets resized, this function gets called
 */
void Form3DViewer::resizeGL(int iWidth, int iHeight)
{
    openGLRareError();

    glViewport(0, 0, iWidth, iHeight);

    mpViewWorld->resize(iWidth, iHeight);

    openGLRareError();
}

void Form3DViewer::keyPressEvent(QKeyEvent* pKeyEvent)
{
    mpControlWorld->keyPressEvent(pKeyEvent);
    mpViewWorld->pressedKey((Qt::Key)pKeyEvent->key());
}

void Form3DViewer::keyReleaseEvent(QKeyEvent* pKeyEvent)
{
    mpControlWorld->keyReleaseEvent(pKeyEvent);
    mpViewWorld->releasedKey((Qt::Key)pKeyEvent->key());
}

void Form3DViewer::mousePressEvent(QMouseEvent* pMouseEvent)
{
    mInitMousePosition = pMouseEvent->globalPos();
    mpControlWorld->mousePressEvent(pMouseEvent);
}

void Form3DViewer::mouseReleaseEvent(QMouseEvent* pMouseEvent)
{
    setCursor(mArrowCursor);
    mpControlWorld->mouseReleaseEvent(pMouseEvent);
}

void Form3DViewer::mouseMoveEvent(QMouseEvent* pMouseEvent)
{
    if(!(pMouseEvent->modifiers() & Qt::ControlModifier))
    {
        setCursor(mBlankCursor);
        mpControlWorld->mouseMoveEvent(pMouseEvent, QPoint(pMouseEvent->globalX() - mInitMousePosition.x(), pMouseEvent->globalY() - mInitMousePosition.y()));
        QCursor::setPos(mInitMousePosition);
    }
}

void Form3DViewer::wheelEvent(QWheelEvent* pWheelEvent)
{
    mpControlWorld->wheelEvent(pWheelEvent);
}
