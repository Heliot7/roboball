////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2011, Computer Graphics Group RWTH Aachen University         //
// All rights reserved.                                                       //
////////////////////////////////////////////////////////////////////////////////

#ifndef ACGL_OPENGL_CONTROLLER_HH
#define ACGL_OPENGL_CONTROLLER_HH

/*
 * A shortcut to include all controller of OpenGL objects.
 * Will also include the objects themself!
 */

#include <ACGL/ACGL.hh>

#include <ACGL/OpenGL/Objects.hh>

#include <ACGL/Resource/NameManager.hh>
#include <ACGL/Resource/FileManager.hh>

#include <ACGL/OpenGL/Controller/ArrayBufferControl.hh>
#include <ACGL/OpenGL/Controller/ArrayBufferControlFileATB.hh>
#include <ACGL/OpenGL/Controller/ElementArrayBufferControl.hh>
#include <ACGL/OpenGL/Controller/FrameBufferObjectControl.hh>
#include <ACGL/OpenGL/Controller/RenderBufferControl.hh>
#include <ACGL/OpenGL/Controller/RenderObjectControl.hh>
#include <ACGL/OpenGL/Controller/ShaderControlFile.hh>
#include <ACGL/OpenGL/Controller/ShaderProgramControlAutoFiles.hh>
#include <ACGL/OpenGL/Controller/ShaderProgramControlFiles.hh>
#include <ACGL/OpenGL/Controller/ShaderProgramObjectControl.hh>
#include <ACGL/OpenGL/Controller/TextureDataControlFileFactory.hh>
#include <ACGL/OpenGL/Controller/TextureDataControlFileJPG.hh>
#include <ACGL/OpenGL/Controller/TextureControl.hh>
#include <ACGL/OpenGL/Controller/TextureControlCubeMap.hh>
#include <ACGL/OpenGL/Controller/TextureControlFile.hh>
#include <ACGL/OpenGL/Controller/TextureControlFileJPG.hh>
#include <ACGL/OpenGL/Controller/UniformControl.hh>
#include <ACGL/OpenGL/Controller/VertexBufferObjectControl.hh>
#include <ACGL/OpenGL/Controller/VertexBufferObjectControlFileOBJ.hh>
#include <ACGL/OpenGL/Controller/ViewportControl.hh>

#endif // ACGL_OPENGL_CONTROLLER_HH
