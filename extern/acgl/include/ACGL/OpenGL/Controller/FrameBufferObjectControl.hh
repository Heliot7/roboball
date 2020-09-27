////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2011, Computer Graphics Group RWTH Aachen University         //
// All rights reserved.                                                       //
////////////////////////////////////////////////////////////////////////////////

#ifndef ACGL_OPENGL_CONTROLLER_FRAMEBUFFEROBJECTCONTROL_HH
#define ACGL_OPENGL_CONTROLLER_FRAMEBUFFEROBJECTCONTROL_HH

#include <ACGL/ACGL.hh>

#include <ACGL/Resource/BasicCreateController.hh>
#include <ACGL/OpenGL/Objects/FrameBufferObject.hh>
#include <ACGL/OpenGL/GL.hh>

#include <ACGL/OpenGL/Objects/Texture.hh>
#include <ACGL/OpenGL/Objects/RenderBuffer.hh>
#include <ACGL/OpenGL/Objects/ShaderProgram.hh>

#include <vector>

namespace ACGL{
namespace OpenGL{

class FrameBufferObjectControl : public Resource::BasicCreateController<FrameBufferObject>
{
    // ========================================================================================================= \/
    // ============================================================================================ CONSTRUCTORS \/
    // ========================================================================================================= \/
public:
    FrameBufferObjectControl(void)
    :   mColorAttachments(),
        mDepthAttachment(),
        mpShaderProgram()
    {
        mDepthAttachment.name         = "";
        mDepthAttachment.texture      = ConstSharedTexture();
        mDepthAttachment.renderBuffer = ConstSharedRenderBuffer();
    }
    virtual ~FrameBufferObjectControl() {}

    // ==================================================================================================== \/
    // ============================================================================================ METHODS \/
    // ==================================================================================================== \/
public:
    inline FrameBufferObjectControl& depthTexture      (const ConstSharedTexture& _pDepthTexture)           { mDepthAttachment.texture = _pDepthTexture;           return *this; }
    inline FrameBufferObjectControl& depthRenderBuffer (const ConstSharedRenderBuffer& _pDepthRenderBuffer) { mDepthAttachment.renderBuffer = _pDepthRenderBuffer; return *this; }
    inline FrameBufferObjectControl& shaderProgram     (const ConstSharedShaderProgram& _shaderProgram)     { mpShaderProgram = _shaderProgram;                    return *this; }

    inline FrameBufferObjectControl& colorTexture(const std::string& _name, const ConstSharedTexture& _texture)
    {
        FrameBufferObject::Attachment attachment = {_name, _texture, SharedRenderBuffer()};
        mColorAttachments.push_back(attachment);
        return *this;
    }
    inline FrameBufferObjectControl& colorRenderBuffer(const std::string& _name, const ConstSharedRenderBuffer& _renderBuffer)
    {
        FrameBufferObject::Attachment attachment = {_name, SharedTexture(), _renderBuffer};
        mColorAttachments.push_back(attachment);
        return *this;
    }

    // ===================================================================================================== \/
    // ============================================================================================ OVERRIDE \/
    // ===================================================================================================== \/
public:
    virtual SharedFrameBufferObject create (void);

    // =================================================================================================== \/
    // ============================================================================================ FIELDS \/
    // =================================================================================================== \/
protected:
    FrameBufferObject::AttachmentVec mColorAttachments;
    FrameBufferObject::Attachment    mDepthAttachment;
    ConstSharedShaderProgram         mpShaderProgram;
};

} // OpenGL
} // ACGL

#endif // ACGL_OPENGL_CONTROLLER_FRAMEBUFFERCONTROL_HH
