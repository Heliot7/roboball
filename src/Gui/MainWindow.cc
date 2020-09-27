////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2011, Computer Graphics Group RWTH Aachen University         //
// All rights reserved.                                                       //
////////////////////////////////////////////////////////////////////////////////

#include "MainWindow.hh"
#include "Form3DViewer.hh"

#include <QtGui/QLabel>
#include <QtGui/QHBoxLayout>
#include <QGLFormat>

MainWindow::MainWindow(QWidget *pParent)
:   QMainWindow(pParent)
{
    // ...it should have a minimum size...
    setMinimumSize(800,600);

    // ... and has a central widget which we only need to add more widgets to it,
    // for that we need a layout in it...
    QWidget* pCentralWidget = new QWidget();
    setCentralWidget(pCentralWidget);
    QHBoxLayout* pLayoutMain = new QHBoxLayout(pCentralWidget);
    pLayoutMain->setContentsMargins(0, 0, 0, 0);

    // ...the interesting stuff are the two forms we define now:
    QGLFormat openGLFormat;
    //openGLFormat.setVersion( 3, 2 );
    //openGLFormat.setProfile( QGLFormat::CoreProfile );
    Form3DViewer *pForm3DViewer = new Form3DViewer(this,openGLFormat);

    // lets add them to our window:
    pLayoutMain->addWidget(pForm3DViewer);

    connect(pForm3DViewer, SIGNAL(signalUpdateFPS(double)), this, SLOT(slotUpdateFPS(double)));
}

MainWindow::~MainWindow(void)
{
}

void MainWindow::slotUpdateFPS(double _fps)
{
    setWindowTitle(
        "SimpleForwardRenderer (" +
            QString("%1").arg(width()) +
            "x" +
            QString("%1").arg(height()) +
            " @ " +
            QString("%1").arg(_fps) +
            " FPS)");
}
