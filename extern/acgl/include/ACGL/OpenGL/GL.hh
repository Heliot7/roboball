////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2011, Computer Graphics Group RWTH Aachen University         //
// All rights reserved.                                                       //
////////////////////////////////////////////////////////////////////////////////

#ifndef ACGL_OPENGL_GL_HH
#define ACGL_OPENGL_GL_HH

/*
 * This simple OpenGL wrapper is used to include OpenGL and GLEW
 * on different platforms.
 *
 * While these includes are located in a subdirectory of GL/ on most systems,
 * Apple hides them on different locations.
 *
 *
 * This wrapper can get configured with external defines:
 * QT_OPENGL_LIB               : include also the QT OpenGL headers and maybe use QT for other
 *                               graphics related stuff, like image loading for textures.
 * ACGL_OPENGL_SUPPORT_CORE_41 : (or other versions): basicly ACGL_OPENGL_PROFILE_* and ACGL_OPENGL_VERSION_*
 *                               combined!
 * ACGL_OPENGL_PROFILE_CORE    : CORE: only support for CORE functions, demands a CORE OpenGL context
 *                               FULL: support for CORE and deprecated functions
 * ACGL_OPENGL_VERSION_41      : (or other versions): minimal OpenGL version that can be assumed to be present.
 *                               The app can't run on older contexts and will probably terminate at startup.
 *                               Set this to a low version and it will run on lost machines
 *                               Set this to a high version and less run-time checks have to be performed to
 *                               work around missing features (like querying extensions etc).
 * ACGL_PLATFORM_DESKTOP       : DESKTOP vs. MOBILE plattform = GL vs. GL ES
 */

// If there is a demand for a core context, we should include the new core headers as well,
// sadly, these are not very good supported yet, so this stays commented out for a while :-(
#ifdef ACGL_OPENGL_PROFILE_CORE
//#   define ACGL_OPENGL_PROFILE_CORE_HEADER
#endif

// To compare the OpenGL version number we define a new ACGL_OPENGL_VERSION XY define here
// analog to ACGL_OPENGL_VERSION_XY
#if   defined (ACGL_OPENGL_VERSION_21)
#     define   ACGL_OPENGL_VERSION 21
#elif defined (ACGL_OPENGL_VERSION_30)
#     define   ACGL_OPENGL_VERSION 30
#elif defined (ACGL_OPENGL_VERSION_31)
#     define   ACGL_OPENGL_VERSION 31
#elif defined (ACGL_OPENGL_VERSION_32)
#     define   ACGL_OPENGL_VERSION 32
#elif defined (ACGL_OPENGL_VERSION_33)
#     define   ACGL_OPENGL_VERSION 33
#elif defined (ACGL_OPENGL_VERSION_40)
#     define   ACGL_OPENGL_VERSION 40
#elif defined (ACGL_OPENGL_VERSION_41)
#     define   ACGL_OPENGL_VERSION 41
#elif defined (ACGL_OPENGL_VERSION_42)
#     define   ACGL_OPENGL_VERSION 42
#else
// failback:
#warning "NO ACGL_OPENGL_VERSION_XY SET! Default to 3.2"
#define ACGL_OPENGL_VERSION_32
#define ACGL_OPENGL_VERSION 32
#endif // version checks


// If we're compiling for an Apple system we need this to distinquish between Mac and iOS:
#ifdef __APPLE__
#include <TargetConditionals.h>
#endif

// always include glew unless on iOS
#define ACGL_USE_GLEW

#if (defined(TARGET_OS_IPHONE) || defined(TARGET_IPHONE_SIMULATOR))
#   if (TARGET_OS_IPHONE == 1)
#       define PLATFORM_IOS
#       define ACGL_OPENGL_ES
#       undef ACGL_USE_GLEW // no glew support on iOS
#   endif
#else
//  no iOS device...
#   ifdef ACGL_PLATFORM_MOBILE
//      ...but mobile:
//      maybe maemo or android: first one to program for these plattforms should add
//      the correct includes here!
#       error "UNKNOWN mobile plattform! Dont know what to include!"
#       define ACGL_OPENGL_ES
#   endif
#endif

// we have allways to include glew first!
#ifdef ACGL_USE_GLEW
    // if GLEW_STATIC is defined, GLEW gets linked statically. GLEW itself needs this define
    // but for us its the sign that a local version of GLEW gets used, so we find it on
    // GL/glew.h on every system.
    #ifdef GLEW_STATIC
        #include "GL/glew.h"
    #else
        #if defined(__APPLE__) || defined(MACOSX)
            #include <OpenGL/glew.h>
        #else
            #include <GL/glew.h>
        #endif
    #endif // !GLEW_LOCAL_PATH
#endif // ACGL_USE_GLEW


#if (defined(__APPLE__) || defined(MACOSX))
#   ifdef ACGL_OPENGL_ES
//      iOS:
#       import <OpenGLES/ES1/gl.h>
#       import <OpenGLES/ES1/glext.h>
#       import <OpenGLES/ES2/gl.h>
#       import <OpenGLES/ES2/glext.h>
#   else
//      Desktop MacOS X:
#       if (!defined(ACGL_OPENGL_PROFILE_CORE) && (ACGL_OPENGL_VERSION > 21))
//          e.g. FULL_32 on Mac won't work
#           warning "Mac OS X only supports OpenGL >= 3.2 with Core profile only"
#           define ACGL_OPENGL_PROFILE_CORE
#       endif
#       if defined(ACGL_OPENGL_PROFILE_CORE)
//          On MacOS X, theres only OpenGL up till 2.1 (<=10.6) or 3.2 (min. 10.7)
//          GLEW will define __gl_h_ and gl3.h will think we included gl.h and gl3.h,
//          to prevent a warning, define this flag:
#           define GL_DO_NOT_WARN_IF_MULTI_GL_VERSION_HEADERS_INCLUDED
#               include <OpenGL/gl3.h>
#           undef GL_DO_NOT_WARN_IF_MULTI_GL_VERSION_HEADERS_INCLUDED
#       else
//          old MacOS X / OpenGL 2.1
#           include <OpenGL/gl.h>
#       endif
#   endif
#else
//  Windows/Linux
#   ifdef ACGL_OPENGL_PROFILE_CORE_HEADER
#       include <GL3/gl3.h>
#   else
//      in contrast to MacOS 10.7, the "old" header can be used for post 3.0 OpenGL!
#       include <GL/gl.h>
#   endif
#endif

#ifdef QT_OPENGL_LIB
#   include <QtOpenGL/qgl.h>
#endif // USE_QT

//
// our own "extension":
//
#include <ACGL/OpenGL/EXT_direct_state_access.hh>

#endif // ACGL_OPENGL_GL_HH
