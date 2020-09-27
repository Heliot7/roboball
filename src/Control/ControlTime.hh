////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2011, Computer Graphics Group RWTH Aachen University         //
// All rights reserved.                                                       //
////////////////////////////////////////////////////////////////////////////////

#ifndef ACGL_TEMPLATE_CONTROLTIME_HH
#define ACGL_TEMPLATE_CONTROLTIME_HH

class ControlTime
{
public:
    ControlTime(void){}
    virtual ~ControlTime(void) {}

    virtual void update(float) {}
};

#endif // ACGL_TEMPLATE_CONTROLTIME_HH
