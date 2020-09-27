////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2011, Computer Graphics Group RWTH Aachen University         //
// All rights reserved.                                                       //
////////////////////////////////////////////////////////////////////////////////

#ifndef ACGL_OPENGL_OBJECTS_FRAMEBUFFEROBJECT_HH
#define ACGL_OPENGL_OBJECTS_FRAMEBUFFEROBJECT_HH

/*
 * This FrameBufferObject class encapsulates an OpenGL frame buffer object (FBO).
 * A FrameBufferObject is a target for rendering and thus consists of different "layers":
 *
 * one or no depthbuffer
 * one or no stencilbuffer
 * one (OpenGL ES) to many (hardware dependent limit) colorbuffers
 *
 * These buffers get attached to the FrameBufferObject.
 *
 * There exists one system-provided frame buffer object for rendering to the screen
 * and optionaly multiple user defined frame buffer objects for offscreen rendering.
 *
 * This class does not encapsulate the system-provided FBO.
 */

#include <ACGL/ACGL.hh>

#include <ACGL/Base/Macros.hh>
#include <ACGL/Base/StringOperations.hh>
#include <ACGL/OpenGL/GL.hh>
#include <ACGL/OpenGL/Tools.hh>
#include <ACGL/OpenGL/Objects/RenderBuffer.hh>
#include <ACGL/OpenGL/Objects/Texture.hh>

#include <vector>
#include <map>
#include <tr1/memory>

namespace ACGL{
namespace OpenGL{

class FrameBufferObject
{
    ACGL_NOT_COPYABLE(FrameBufferObject)

    // =================================================================================================== \/
    // ============================================================================================ STATIC \/
    // =================================================================================================== \/
private:
    static GLuint msBuffers[8];

    // ==================================================================================================== \/
    // ============================================================================================ STRUCTS \/
    // ==================================================================================================== \/
public:
    //! An attachment can be a texture or a render buffer
    struct Attachment
    {
        std::string name;
        ConstSharedTexture texture;
        ConstSharedRenderBuffer renderBuffer;
    };

    // ===================================================================================================== \/
    // ============================================================================================ TYPEDEFS \/
    // ===================================================================================================== \/
public:
    typedef std::vector< Attachment > AttachmentVec;

    // ========================================================================================================= \/
    // ============================================================================================ CONSTRUCTORS \/
    // ========================================================================================================= \/
public:
    FrameBufferObject(void)
    :   mObjectName(0),
        mDrawBuffers(0),
        mColorAttachments(),
        mDepthAttachment()
    {
        glGenFramebuffers(1, &mObjectName);
        if (openGLCriticalErrorOccured() ) {
            ACGL::Utils::error() << "could not generate FrameBufferObject!" << std::endl;
            return;
        }
        mDepthAttachment.name = "";
        mDepthAttachment.texture = ConstSharedTexture();
        mDepthAttachment.renderBuffer = ConstSharedRenderBuffer();
    }

    virtual ~FrameBufferObject(void)
    {
        // buffer 0 will get ignored by OpenGL
        glDeleteFramebuffers(1, &mObjectName);
    }

    // ==================================================================================================== \/
    // ============================================================================================ GETTERS \/
    // ==================================================================================================== \/
public:
    inline       GLuint         operator()          (void) const { return mObjectName; }
    inline       GLuint         getObjectName       (void) const { return mObjectName; }
    inline const AttachmentVec& getColorAttachments (void) const { return mColorAttachments; }
    inline const Attachment&    getDepthAttachment  (void) const { return mDepthAttachment;  }

    // ===================================================================================================== \/
    // ============================================================================================ WRAPPERS \/
    // ===================================================================================================== \/
public:
     int_t getColorAttachmentIndexByName(const std::string& _name) const;

     void validate (void) const;

    /**
     * Per default a FrameBufferObject gets used for read/write operations, but we can
     * bind two different FrameBufferObjects for these operations!
     */
    inline void bind(GLenum _type = GL_FRAMEBUFFER) const
    {
        glBindFramebuffer(_type, mObjectName);
        openGLRareError(); // glBindFramebuffer can only fail if the object name is no valid FBO which shouldn't happen using this framework
    }

    inline void bindAsRenderTarget(GLenum _type = GL_FRAMEBUFFER) const
    {
        glBindFramebuffer(_type, mObjectName);
        glDrawBuffers(mDrawBuffers, msBuffers);
        openGLRareError();
    }

    /*
    inline void bindAsRenderTarget(GLint _x, GLint _y, GLsizei _w, GLsizei _h, GLenum _type = GL_FRAMEBUFFER) const
    {
        glBindFramebuffer(_type, mObjectName);
        glDrawBuffers(mDrawBuffers, msBuffers);
        openGLRareError();
    }*/

    inline bool isFrameBufferObjectComplete(void) const
    {
        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        {
            Utils::error() << "Failed to make complete FrameBufferObject object: " << (glCheckFramebufferStatus(GL_FRAMEBUFFER)) << std::endl;
            return false;
        }
        return true;
    }

    inline bool attachColorRenderBuffer(const std::string _name, const ConstSharedRenderBuffer& _renderBuffer)
    {
        glFramebufferRenderbuffer( GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + mDrawBuffers, GL_RENDERBUFFER, _renderBuffer->getObjectName() );
        if (openGLCommonErrorOccured()) {
            Utils::error() << "Attaching of texture to the FBO failed" << std::endl;
            return false;
        }

        Attachment attachment = {_name, SharedTexture(), _renderBuffer};
        mColorAttachments.push_back(attachment);
        mColorAttachmentIndices[_name] = mDrawBuffers;
        mDrawBuffers++;
        return true;
    }

    inline bool attachColorTexture(const std::string _name, const ConstSharedTexture& _texture)
    {
        glFramebufferTexture2D( GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + mDrawBuffers, _texture->getTarget(), _texture->getObjectName(), 0 );
        if (openGLCommonErrorOccured()) {
            Utils::error() << "Attaching of texture to the FBO failed" << std::endl;
            return false;
        }

        Attachment attachment = {_name, _texture, SharedRenderBuffer()};
        mColorAttachments.push_back(attachment);
        mColorAttachmentIndices[_name] = mDrawBuffers;
        mDrawBuffers++;
        return true;
    }

    inline bool setColorRenderBuffer(const std::string _name, const ConstSharedRenderBuffer& _renderBuffer)
    {
        glFramebufferRenderbuffer( GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + mColorAttachmentIndices[_name], GL_RENDERBUFFER, _renderBuffer->getObjectName() );
        return true;
    }

    inline bool setColorTexture(const std::string _name, const ConstSharedTexture& _texture)
    {
        glFramebufferTexture2D( GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + mColorAttachmentIndices[_name], _texture->getTarget(), _texture->getObjectName(), 0 );
        return true;
    }

    inline bool setDepthRenderBuffer(const ConstSharedRenderBuffer& _renderBuffer)
    {
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, _renderBuffer->getObjectName() );
        #ifdef ACGL_OPENGL_ES
            if( _renderBuffer->getInternalFormat() == GL_DEPTH24_STENCIL8_OES ||
                _renderBuffer->getInternalFormat() == GL_DEPTH_STENCIL_OES)
                glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_RENDERBUFFER, _renderBuffer->getObjectName() );
        #else
            if( _renderBuffer->getInternalFormat() == GL_DEPTH24_STENCIL8 ||
                _renderBuffer->getInternalFormat() == GL_DEPTH_STENCIL)
                glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_RENDERBUFFER, _renderBuffer->getObjectName() );
        #endif
        mDepthAttachment.renderBuffer = _renderBuffer;
        return true;
    }

    inline bool setDepthTexture(const ConstSharedTexture& _texture)
    {
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, _texture->getTarget(), _texture->getObjectName(), 0);
        #ifdef ACGL_OPENGL_ES
            if( _texture->getInternalFormat() == GL_DEPTH24_STENCIL8_OES ||
                _texture->getInternalFormat() == GL_DEPTH_STENCIL_OES)
                glFramebufferTexture2D(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, _texture->getTarget(), _texture->getObjectName(), 0);
        #else
            if( _texture->getInternalFormat() == GL_DEPTH24_STENCIL8 ||
                _texture->getInternalFormat() == GL_DEPTH_STENCIL)
                glFramebufferTexture2D(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, _texture->getTarget(), _texture->getObjectName(), 0);
        #endif
        mDepthAttachment.texture = _texture;
        return true;
    }

    // =================================================================================================== \/
    // ============================================================================================ FIELDS \/
    // =================================================================================================== \/
protected:
    GLuint        mObjectName;
    GLsizei       mDrawBuffers;
    AttachmentVec mColorAttachments;
    //stores the attachment index (GL_COLOR_ATTACHMENT0 + i) of each color attachment by its name.
    std::map<std::string, int> mColorAttachmentIndices;
    Attachment    mDepthAttachment;  // depth and stencil are combined
};

ACGL_SHARED_TYPEDEF(FrameBufferObject)

} // OpenGL
} // ACGL

#endif // ACGL_OPENGL_OBJECTS_FRAMEBUFFEROBJECT_HH
