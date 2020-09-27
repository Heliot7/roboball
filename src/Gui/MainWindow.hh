////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2011, Computer Graphics Group RWTH Aachen University         //
// All rights reserved.                                                       //
////////////////////////////////////////////////////////////////////////////////

#ifndef ACGL_TEMPLATE_MAINWINDOW_HH
#define ACGL_TEMPLATE_MAINWINDOW_HH

#include <QtGui/QMainWindow>

class FormRendererOpenGL;
class FormRenderSettings;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *pParent = NULL);
    virtual ~MainWindow(void);

private slots:
    void slotUpdateFPS(double _fps);
};

#endif // ACGL_TEMPLATE_MAINWINDOW_HH
