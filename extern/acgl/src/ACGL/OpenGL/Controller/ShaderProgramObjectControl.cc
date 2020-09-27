////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2011, Computer Graphics Group RWTH Aachen University         //
// All rights reserved.                                                       //
////////////////////////////////////////////////////////////////////////////////

#include <ACGL/OpenGL/Controller/ShaderProgramObjectControl.hh>

using namespace ACGL::OpenGL;

SharedShaderProgramObject ShaderProgramObjectControl::create(void)
{
    SharedShaderProgramObject shaderProgramObject(new ShaderProgramObject(mShaderProgram));

    for(UniformAttachmentDefineVec::size_type i = 0; i < mUniformAttachmentDefines.size(); i++)
        shaderProgramObject->attachUniform(mUniformAttachmentDefines[i].name, mUniformAttachmentDefines[i].uniform);

    for(UniformTextureAttachmentDefineVec::size_type i = 0; i < mUniformTextureAttachmentDefines.size(); i++)
        shaderProgramObject->attachUniformTexture(mUniformTextureAttachmentDefines[i].name, mUniformTextureAttachmentDefines[i].uniformTexture);

    return shaderProgramObject;
}
