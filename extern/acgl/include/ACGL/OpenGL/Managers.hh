////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2011, Computer Graphics Group RWTH Aachen University         //
// All rights reserved.                                                       //
////////////////////////////////////////////////////////////////////////////////

#ifndef ACGL_OPENGL_MANAGER_HH
#define ACGL_OPENGL_MANAGER_HH

/*
 * A shortcut to include all manager of OpenGL objects.
 * Will also include the Objects & Controllers!
 */

#include <ACGL/ACGL.hh>

#include <ACGL/OpenGL/Controller.hh>

#include <ACGL/Resource/NameManager.hh>
#include <ACGL/Resource/FileManager.hh>

namespace ACGL{
namespace OpenGL{

typedef Resource::NameManager<ArrayBuffer> ArrayBufferNameManager;
typedef Resource::FileManager<ArrayBuffer> ArrayBufferFileManager;

typedef Resource::NameManager<ElementArrayBuffer> ElementArrayBufferNameManager;

typedef Resource::NameManager<FrameBufferObject> FrameBufferObjectNameManager;

typedef Resource::NameManager<RenderBuffer> RenderBufferNameManager;

typedef Resource::NameManager<Shader> ShaderNameManager;
typedef Resource::FileManager<Shader> ShaderFileManager;

typedef Resource::NameManager<ShaderProgram> ShaderProgramNameManager;
typedef Resource::FileManager<ShaderProgram> ShaderProgramFileManager;

typedef Resource::NameManager<ShaderProgramObject> ShaderProgramObjectNameManager;

typedef Resource::NameManager<Texture> TextureNameManager;
typedef Resource::FileManager<Texture> TextureFileManager;

typedef Resource::NameManager<TextureData> TextureDataNameManager;
typedef Resource::FileManager<TextureData> TextureDataFileManager;

typedef Resource::NameManager<Uniform1f> Uniform1fNameManager;
typedef Resource::NameManager<Uniform2f> Uniform2fNameManager;
typedef Resource::NameManager<Uniform3f> Uniform3fNameManager;
typedef Resource::NameManager<Uniform4f> Uniform4fNameManager;
typedef Resource::NameManager<UniformMatrix2f> UniformMatrix2fNameManager;
typedef Resource::NameManager<UniformMatrix3f> UniformMatrix3fNameManager;
typedef Resource::NameManager<UniformMatrix4f> UniformMatrix4fNameManager;
typedef Resource::NameManager<UniformTexture> UniformTextureNameManager;

typedef Resource::NameManager<VertexBufferObject> VertexBufferObjectNameManager;
typedef Resource::FileManager<VertexBufferObject> VertexBufferObjectFileManager;

typedef Resource::NameManager<Viewport> ViewportNameManager;

#if (ACGL_OPENGL_VERSION >= 30)
typedef Resource::NameManager<RenderObject> RenderObjectNameManager;
#endif // GL >= 3.0

} // OpenGL
} // ACGL

//note: when we start having managers for non-OpenGL objects we should move this ;-)
#define ACGL_FOR_EACH_RESOURCE(MANAGER,RESOURCE,ELEMENT) \
    for(ACGL::Resource::MANAGER<RESOURCE>::ResourceContainer::const_iterator ELEMENT = ACGL::Resource::MANAGER<RESOURCE>::the()->begin(); \
        ELEMENT != MANAGER<RESOURCE>::the()->end(); \
        ++ELEMENT)


#endif // ACGL_OPENGL_MANAGER_HH
