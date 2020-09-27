////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2011, Computer Graphics Group RWTH Aachen University         //
// All rights reserved.                                                       //
////////////////////////////////////////////////////////////////////////////////

#include <ACGL/ACGL.hh>
#include <ACGL/OpenGL/GL.hh>
#include <ACGL/OpenGL/Tools.hh>
#include <ACGL/OpenGL/Objects/VertexArrayObject.hh>
#include <ACGL/OpenGL/InitStaticFileTypes.hh>

#include <ACGL/OpenGL/Controller/TextureDataControlFileFactory.hh>
#include <ACGL/OpenGL/Controller/TextureDataControlFileJPG.hh>

namespace ACGL
{

bool init(void)
{
    //
    // init GLEW
    //
#ifdef ACGL_USE_GLEW
#   ifdef ACGL_OPENGL_PROFILE_CORE
        glewExperimental = TRUE;
#   endif

        GLenum errorCode = glewInit();
        if ((errorCode != GLEW_OK) || (openGLCriticalErrorOccured())) {
            Utils::error() << "could not init GLEW!" << std::endl;
            #ifdef ACGL_OPENGL_PROFILE_CORE
            Utils::error() << "Make sure your version of GLEW is compatible with core contexts (see glew branch coreprofile)" << std::endl;
            #endif
            return false;
        }
#endif // GLEW

    //
    // check OpenGL version
    //
    Utils::debug() << "OpenGL Version: " << OpenGL::getOpenGLMajorVersionNumber() << "." << OpenGL::getOpenGLMinorVersionNumber() << std::endl;

    if (OpenGL::getOpenGLVersionNumber() < ACGL_OPENGL_VERSION) {
       Utils::error() << "At compile time an OpenGL context of version " << ACGL_OPENGL_VERSION
                      << " was requested, but the current context only supports " << OpenGL::getOpenGLVersionNumber() << std::endl;
       return false;
    }

    //
    // Init DirectStateAccess functions:
    // (using the extension versions or our own (slower) emulation)
    //
    OpenGL::initDirectStateAccessFunctions();

    //
    // Register file types for loading. This has to be done if the library is
    // linked statically, because otherwise, the static registration of the
    // file types is not performed.
    //
    OpenGL::initStaticFileTypes();

    return true;
}
    
}

