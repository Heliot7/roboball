////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2011, Computer Graphics Group RWTH Aachen University         //
// All rights reserved.                                                       //
////////////////////////////////////////////////////////////////////////////////

#ifndef ACGL_OPENGL_INITSTATICFILETYPES_HH
#define ACGL_OPENGL_INITSTATICFILETYPES_HH

namespace ACGL{
namespace OpenGL{

/*
 *   Here is a citation from stack overflow, why we need the initStaticFileTypes function:
 *
 *   If you have an object in a static library that is not EXPLICITLY used in the application.
 *   Then the linker will not pull that object from the lib into the application.
 *
 *   There is a big difference between static and dynamic libraries.
 *
 *   Dynamic Library:
 *   At compile time nothing is pulled from the dynamic library. Extra code is added to
 *   explicitly load and resolve the symbols at run-time. At run time the whole library is
 *   loaded and thus object initializers are called (though when is implementation detail).
 *
 *   Static libraries are handled very differently:
 *   When you link against a static library it pulls all the items that are not defined in
 *   application that are defined in the library into the application. This is repeated until
 *   there are no more dependencies that the library can resolve. The side effect of this is
 *   that objects/functions not explicitly used are not pulled form the library (thus global
 *   variables that are not directly accessed will not be pulled).
 */

void initStaticFileTypes(void);

} // OpenGL
} // ACGL

#endif // ACGL_OPENGL_INITSTATICFILETYPES_HH

