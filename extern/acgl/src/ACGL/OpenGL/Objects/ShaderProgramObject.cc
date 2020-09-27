////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2011, Computer Graphics Group RWTH Aachen University         //
// All rights reserved.                                                       //
////////////////////////////////////////////////////////////////////////////////

#include <ACGL/OpenGL/Objects/ShaderProgramObject.hh>

using namespace ACGL::OpenGL;

void ShaderProgramObject::use(void) const
{
    mpShaderProgram->use();
    updateUniforms();
}

void ShaderProgramObject::updateUniforms(void) const
{
    for(UniformAttachmentVec::size_type i = 0; i < mUniformAttachments.size(); ++i)
        mUniformAttachments[i].uniform->apply(mUniformAttachments[i].location);

    for(UniformTextureAttachmentVec::size_type i = 0; i < mUniformTextureAttachments.size(); ++i)
        mUniformTextureAttachments[i].uniformTexture->apply(mUniformTextureAttachments[i].location, i);
}
