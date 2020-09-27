////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2011, Computer Graphics Group RWTH Aachen University         //
// All rights reserved.                                                       //
////////////////////////////////////////////////////////////////////////////////

#ifndef ACGL_TEMPLATE_VIEWWORLD_HH
#define ACGL_TEMPLATE_VIEWWORLD_HH

class ViewWorld
{
public:
    ViewWorld(void) {}
    virtual ~ViewWorld(void) {}

    virtual void init(void) = 0;
    virtual void paint(double timeStep) = 0;
    virtual void resize(int iWidth, int iHeight) = 0;

    // Game extras for key inputs
    virtual void pressedKey(Qt::Key key) = 0;
    virtual void releasedKey(Qt::Key key) = 0;
};


#endif // ACGL_TEMPLATE_VIEWWORLD_HH
