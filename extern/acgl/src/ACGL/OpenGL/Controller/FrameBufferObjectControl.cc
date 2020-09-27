////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2011, Computer Graphics Group RWTH Aachen University         //
// All rights reserved.                                                       //
////////////////////////////////////////////////////////////////////////////////

#include <ACGL/OpenGL/Controller/FrameBufferObjectControl.hh>

using namespace ACGL::OpenGL;

SharedFrameBufferObject FrameBufferObjectControl::create(void)
{
    SharedFrameBufferObject frameBuffer(new FrameBufferObject());
    frameBuffer->bind();

#if (ACGL_OPENGL_VERSION >= 30)
    if(mpShaderProgram)
    {
        std::vector<int_t> assignmentOrder(mColorAttachments.size());
        for(std::vector<int_t>::size_type i = 0; i < assignmentOrder.size(); ++i) assignmentOrder[i] = -1;

        for(FrameBufferObject::AttachmentVec::size_type i = 0; i < mColorAttachments.size(); ++i)
        {
            GLint location = mpShaderProgram->getFragmentDataLocation(mColorAttachments[i].name);
            if (location < 0) {
                ACGL::Utils::warning() << "ShaderProgram has no FragDataLocation named " << mColorAttachments[i].name << " - ignored" << std::endl;
            }
            assignmentOrder[location] = i;
        }

        for(std::vector<int_t>::size_type j = 0; j < assignmentOrder.size(); ++j)
        {
            if (assignmentOrder[j] < 0) continue;

            if(mColorAttachments[assignmentOrder[j]].texture)
                frameBuffer->attachColorTexture(mColorAttachments[assignmentOrder[j]].name, mColorAttachments[assignmentOrder[j]].texture);
            else if(mColorAttachments[assignmentOrder[j]].renderBuffer)
                frameBuffer->attachColorRenderBuffer(mColorAttachments[assignmentOrder[j]].name, mColorAttachments[assignmentOrder[j]].renderBuffer);
        }

    }
    else
#endif
    {
        for(FrameBufferObject::AttachmentVec::size_type i = 0; i < mColorAttachments.size(); ++i)
        {
            if(mColorAttachments[i].texture)
                frameBuffer->attachColorTexture(mColorAttachments[i].name, mColorAttachments[i].texture);
            else if(mColorAttachments[i].renderBuffer)
                frameBuffer->attachColorRenderBuffer(mColorAttachments[i].name, mColorAttachments[i].renderBuffer);
        }
    }

    if(mDepthAttachment.texture)
        frameBuffer->setDepthTexture(mDepthAttachment.texture);
    else if(mDepthAttachment.renderBuffer)
        frameBuffer->setDepthRenderBuffer(mDepthAttachment.renderBuffer);

    return frameBuffer;
}
