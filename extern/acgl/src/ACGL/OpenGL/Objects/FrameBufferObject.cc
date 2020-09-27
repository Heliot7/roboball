////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2011, Computer Graphics Group RWTH Aachen University         //
// All rights reserved.                                                       //
////////////////////////////////////////////////////////////////////////////////

#include <ACGL/OpenGL/Objects/FrameBufferObject.hh>

using namespace ACGL;
using namespace ACGL::OpenGL;

/*
 * We can't use the constants GL_COLOR_ATTACHMENT1 to GL_COLOR_ATTACHMENT7 here
 * because OpenGL ES does not know these yet.
 */
 GLuint FrameBufferObject::msBuffers[8] = {
    GL_COLOR_ATTACHMENT0,
    GL_COLOR_ATTACHMENT0+1,
    GL_COLOR_ATTACHMENT0+2,
    GL_COLOR_ATTACHMENT0+3,
    GL_COLOR_ATTACHMENT0+4,
    GL_COLOR_ATTACHMENT0+5,
    GL_COLOR_ATTACHMENT0+6,
    GL_COLOR_ATTACHMENT0+7};


int_t FrameBufferObject::getColorAttachmentIndexByName(const std::string& _name) const
{
     for(AttachmentVec::size_type i = 0; i < mColorAttachments.size(); i++)
     {
         if(mColorAttachments[i].name == _name)
             return i;
     }

     return -1;
 }

void FrameBufferObject::validate(void) const
{
    if(mColorAttachments.size() > 0)
    {
        int width  = -1;
        int height = -1;

        if(mColorAttachments[0].texture)
        {
            width  = mColorAttachments[0].texture->getWidth();
            height = mColorAttachments[0].texture->getHeight();
        }
        else
        {
            width  = mColorAttachments[0].renderBuffer->getWidth();
            height = mColorAttachments[0].renderBuffer->getHeight();
        }

        for(AttachmentVec::size_type k = 0; k < mColorAttachments.size(); k++)
        {
            bool fail = false;

            if(mColorAttachments[k].texture)
                fail = (mColorAttachments[k].texture->getWidth() != width || mColorAttachments[k].texture->getHeight() != height);
            else //otherwise its a RenderBuffer
                fail = (mColorAttachments[k].renderBuffer->getWidth() != width || mColorAttachments[k].renderBuffer->getHeight() != height);

            if(fail)
                Utils::error() << "FrameBufferObject validation failed: Color attachment "<< k << " has different size." << std::endl;
        }
    }
    else
        Utils::error() << "FrameBufferObject validation failed: No color attachments."<< std::endl;
}
