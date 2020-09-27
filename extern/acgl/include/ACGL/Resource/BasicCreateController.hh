////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2011, Computer Graphics Group RWTH Aachen University         //
// All rights reserved.                                                       //
////////////////////////////////////////////////////////////////////////////////

#ifndef ACGL_RESOURCE_BASICCREATECONTROLLER_HH
#define ACGL_RESOURCE_BASICCREATECONTROLLER_HH

/*
 * Base class for all controllers.
 *
 * Controllers can provide more flexible ways of creating objects, they are also
 * making managers more flexibe.
 */

#include <tr1/memory>

#include <ACGL/ACGL.hh>

namespace ACGL{
namespace Resource{

template<typename RESOURCE>
class BasicCreateController
{
    // ==================================================================================================== \/
    // ========================================================================================== INTERFACE \/
    // ==================================================================================================== \/
public:
    virtual std::tr1::shared_ptr<RESOURCE> create(void) = 0;
};

} // Resource
} // ACGL

#endif // ACGL_RESOURCE_BASICCONTROLLER_HH
