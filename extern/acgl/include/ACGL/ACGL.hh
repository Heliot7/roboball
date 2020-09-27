////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2011, Computer Graphics Group RWTH Aachen University         //
// All rights reserved.                                                       //
////////////////////////////////////////////////////////////////////////////////

#ifndef ACGL_ACGL_HH
#define ACGL_ACGL_HH

/*!
 * Include this in all ACGL (header)-files. It will include stuff that is used in
 * almost every file:
   * the used datatypes
   * macros and defines used at compile-time
   * logging
 *
 * Also the librarys init function is defined here.
 */

#include <ACGL/Base/CompileTimeSettings.hh>
#include <ACGL/Types.hh>
#include <ACGL/Utils/Log.hh>

namespace ACGL
{

/*
 * This should get called as soon as a valid OpenGL context exists,
 * it will init glew (if used).
 * Call this before calling any OpenGL functions or OpenGL related
 * ACGL stuff.
 *
 * Returns false if a critical error occured, in that case the ACGL behavior is
 * not defined.
 */
bool init(void);
    
};

#endif // ACGL_ACGL_HH

