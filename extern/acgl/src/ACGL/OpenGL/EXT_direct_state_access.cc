#include "ACGL/OpenGL/EXT_direct_state_access.hh"
#include <ACGL/OpenGL/Tools.hh>

// not all functions are implemented right now, so ignore warnings about unused parameters

#if (((__GNUC__ == 4) && (__GNUC_MINOR__ >= 6)) || (__GNUC__ > 4))
#   pragma GCC diagnostic push
#endif
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wunused-variable"

namespace ACGL{
namespace OpenGL{

#if (defined(ACGL_OPENGL_ES) && defined(PLATFORM_IOS))
void mapProgramUniformFromEXTiOS();
#endif
void mapProgramUniformFromEXT();
void mapProgramUniformFromEMULATION();
void mapDSAFromEMULATION();

void initDirectStateAccessFunctions()
{
    //
    // Handle glProgramUniform*() calls
    //
#   if defined(ACGL_OPENGL_ES)
#       if ( defined(PLATFORM_IOS) && defined(GL_EXT_separate_shader_objects) )
            // iOS >= 5.0 with 2011 hardware should implement the seperate_shader_objects
            // extension which provides glProgramUniform*EXT calls
            mapProgramUniformFromEXTiOS();
#       else
            // old iOS versions and other OpenGL ES implementations have to emulate the
            // calls to glProgramUniform*()
            mapProgramUniformFromEMULATION();
#       endif
        // other OpenGL ES targets:
        mapProgramUniformFromEMULATION();
#   else
        // desktop:
        if (getOpenGLVersionNumber() < 41) {
            // glUniformProgram*() is part of GL 4.1, so there's nothing to do from 4.1 on
#           ifdef ACGL_USE_GLEW
                if (GLEW_ARB_separate_shader_objects || GLEW_EXT_direct_state_access) {
                    mapProgramUniformFromEXT();
                } else {
                    mapProgramUniformFromEMULATION();
                }
#           else
                mapProgramUniformFromEMULATION();
#           endif
        }
#   endif

    //
    // other DSA functions:
    //
#   ifdef ACGL_USE_GLEW
        if (GLEW_EXT_direct_state_access) {
            ACGL::Utils::debug() << "native EXT_direct_state_access detected" << std::endl;
        } else {
            ACGL::Utils::message() << "EXT_direct_state_access has to be emulated - some of the functions could be missing..." << std::endl;
            mapDSAFromEMULATION();
        }
#   else
        mapDSAFromEMULATION();
#   endif
}

#if (defined(ACGL_OPENGL_ES) && defined(PLATFORM_IOS))
// TODO: testing
void mapProgramUniformFromEXTiOS()
{
    glProgramUniform1f = glProgramUniform1fEXT;
    glProgramUniform1fv = glProgramUniform1fvEXT;
    glProgramUniform1i = glProgramUniform1iEXT;
    glProgramUniform1iv = glProgramUniform1ivEXT;
    glProgramUniform2f = glProgramUniform2fEXT;
    glProgramUniform2fv = glProgramUniform2fvEXT;
    glProgramUniform2i = glProgramUniform2iEXT;
    glProgramUniform2iv = glProgramUniform2ivEXT;
    glProgramUniform3f = glProgramUniform3fEXT;
    glProgramUniform3fv = glProgramUniform3fvEXT;
    glProgramUniform3i = glProgramUniform3iEXT;
    glProgramUniform3iv = glProgramUniform3ivEXT;
    glProgramUniform4f = glProgramUniform4fEXT;
    glProgramUniform4fv = glProgramUniform4fvEXT;
    glProgramUniform4i = glProgramUniform4iEXT;
    glProgramUniform4iv = glProgramUniform4ivEXT;
    glProgramUniformMatrix2fv = glProgramUniformMatrix2fvEXT;
    glProgramUniformMatrix3fv = glProgramUniformMatrix3fvEXT;
    glProgramUniformMatrix4fv = glProgramUniformMatrix4fvEXT;
}
#endif


void mapProgramUniformFromEXT()
{
    glProgramUniform1f = glProgramUniform1fEXT;
    glProgramUniform1fv = glProgramUniform1fvEXT;
    glProgramUniform1i = glProgramUniform1iEXT;
    glProgramUniform1iv = glProgramUniform1ivEXT;
    glProgramUniform1ui = glProgramUniform1uiEXT;
    glProgramUniform1uiv = glProgramUniform1uivEXT;
    glProgramUniform2f = glProgramUniform2fEXT;
    glProgramUniform2fv = glProgramUniform2fvEXT;
    glProgramUniform2i = glProgramUniform2iEXT;
    glProgramUniform2iv = glProgramUniform2ivEXT;
    glProgramUniform2ui = glProgramUniform2uiEXT;
    glProgramUniform2uiv = glProgramUniform2uivEXT;
    glProgramUniform3f = glProgramUniform3fEXT;
    glProgramUniform3fv = glProgramUniform3fvEXT;
    glProgramUniform3i = glProgramUniform3iEXT;
    glProgramUniform3iv = glProgramUniform3ivEXT;
    glProgramUniform3ui = glProgramUniform3uiEXT;
    glProgramUniform3uiv = glProgramUniform3uivEXT;
    glProgramUniform4f = glProgramUniform4fEXT;
    glProgramUniform4fv = glProgramUniform4fvEXT;
    glProgramUniform4i = glProgramUniform4iEXT;
    glProgramUniform4iv = glProgramUniform4ivEXT;
    glProgramUniform4ui = glProgramUniform4uiEXT;
    glProgramUniform4uiv = glProgramUniform4uivEXT;
    glProgramUniformMatrix2fv = glProgramUniformMatrix2fvEXT;
    glProgramUniformMatrix2x3fv = glProgramUniformMatrix2x3fvEXT;
    glProgramUniformMatrix2x4fv = glProgramUniformMatrix2x4fvEXT;
    glProgramUniformMatrix3fv = glProgramUniformMatrix3fvEXT;
    glProgramUniformMatrix3x2fv = glProgramUniformMatrix3x2fvEXT;
    glProgramUniformMatrix3x4fv = glProgramUniformMatrix3x4fvEXT;
    glProgramUniformMatrix4fv = glProgramUniformMatrix4fvEXT;
    glProgramUniformMatrix4x2fv = glProgramUniformMatrix4x2fvEXT;
    glProgramUniformMatrix4x3fv = glProgramUniformMatrix4x3fvEXT;
}

void mapProgramUniformFromEMULATION()
{
    glProgramUniform1f = glProgramUniform1fEMULATION;
    glProgramUniform1fv = glProgramUniform1fvEMULATION;
    glProgramUniform1i = glProgramUniform1iEMULATION;
    glProgramUniform1iv = glProgramUniform1ivEMULATION;
    glProgramUniform1ui = glProgramUniform1uiEMULATION;
    glProgramUniform1uiv = glProgramUniform1uivEMULATION;
    glProgramUniform2f = glProgramUniform2fEMULATION;
    glProgramUniform2fv = glProgramUniform2fvEMULATION;
    glProgramUniform2i = glProgramUniform2iEMULATION;
    glProgramUniform2iv = glProgramUniform2ivEMULATION;
    glProgramUniform2ui = glProgramUniform2uiEMULATION;
    glProgramUniform2uiv = glProgramUniform2uivEMULATION;
    glProgramUniform3f = glProgramUniform3fEMULATION;
    glProgramUniform3fv = glProgramUniform3fvEMULATION;
    glProgramUniform3i = glProgramUniform3iEMULATION;
    glProgramUniform3iv = glProgramUniform3ivEMULATION;
    glProgramUniform3ui = glProgramUniform3uiEMULATION;
    glProgramUniform3uiv = glProgramUniform3uivEMULATION;
    glProgramUniform4f = glProgramUniform4fEMULATION;
    glProgramUniform4fv = glProgramUniform4fvEMULATION;
    glProgramUniform4i = glProgramUniform4iEMULATION;
    glProgramUniform4iv = glProgramUniform4ivEMULATION;
    glProgramUniform4ui = glProgramUniform4uiEMULATION;
    glProgramUniform4uiv = glProgramUniform4uivEMULATION;
    glProgramUniformMatrix2fv = glProgramUniformMatrix2fvEMULATION;
    glProgramUniformMatrix2x3fv = glProgramUniformMatrix2x3fvEMULATION;
    glProgramUniformMatrix2x4fv = glProgramUniformMatrix2x4fvEMULATION;
    glProgramUniformMatrix3fv = glProgramUniformMatrix3fvEMULATION;
    glProgramUniformMatrix3x2fv = glProgramUniformMatrix3x2fvEMULATION;
    glProgramUniformMatrix3x4fv = glProgramUniformMatrix3x4fvEMULATION;
    glProgramUniformMatrix4fv = glProgramUniformMatrix4fvEMULATION;
    glProgramUniformMatrix4x2fv = glProgramUniformMatrix4x2fvEMULATION;
    glProgramUniformMatrix4x3fv = glProgramUniformMatrix4x3fvEMULATION;

    //
    // just to be sure the EXT versions are also defined
    // (we can't put them in mapDSAFromEMULATION in case they are defined
    // from the GLEW_ARB_separate_shader_objects extension!)
    //
    glProgramUniform1fEXT = glProgramUniform1fEMULATION;
    glProgramUniform1fvEXT = glProgramUniform1fvEMULATION;
    glProgramUniform1iEXT = glProgramUniform1iEMULATION;
    glProgramUniform1ivEXT = glProgramUniform1ivEMULATION;
    glProgramUniform1uiEXT = glProgramUniform1uiEMULATION;
    glProgramUniform1uivEXT = glProgramUniform1uivEMULATION;
    glProgramUniform2fEXT = glProgramUniform2fEMULATION;
    glProgramUniform2fvEXT = glProgramUniform2fvEMULATION;
    glProgramUniform2iEXT = glProgramUniform2iEMULATION;
    glProgramUniform2ivEXT = glProgramUniform2ivEMULATION;
    glProgramUniform2uiEXT = glProgramUniform2uiEMULATION;
    glProgramUniform2uivEXT = glProgramUniform2uivEMULATION;
    glProgramUniform3fEXT = glProgramUniform3fEMULATION;
    glProgramUniform3fvEXT = glProgramUniform3fvEMULATION;
    glProgramUniform3iEXT = glProgramUniform3iEMULATION;
    glProgramUniform3ivEXT = glProgramUniform3ivEMULATION;
    glProgramUniform3uiEXT = glProgramUniform3uiEMULATION;
    glProgramUniform3uivEXT = glProgramUniform3uivEMULATION;
    glProgramUniform4fEXT = glProgramUniform4fEMULATION;
    glProgramUniform4fvEXT = glProgramUniform4fvEMULATION;
    glProgramUniform4iEXT = glProgramUniform4iEMULATION;
    glProgramUniform4ivEXT = glProgramUniform4ivEMULATION;
    glProgramUniform4uiEXT = glProgramUniform4uiEMULATION;
    glProgramUniform4uivEXT = glProgramUniform4uivEMULATION;
    glProgramUniformMatrix2fvEXT = glProgramUniformMatrix2fvEMULATION;
    glProgramUniformMatrix2x3fvEXT = glProgramUniformMatrix2x3fvEMULATION;
    glProgramUniformMatrix2x4fvEXT = glProgramUniformMatrix2x4fvEMULATION;
    glProgramUniformMatrix3fvEXT = glProgramUniformMatrix3fvEMULATION;
    glProgramUniformMatrix3x2fvEXT = glProgramUniformMatrix3x2fvEMULATION;
    glProgramUniformMatrix3x4fvEXT = glProgramUniformMatrix3x4fvEMULATION;
    glProgramUniformMatrix4fvEXT = glProgramUniformMatrix4fvEMULATION;
    glProgramUniformMatrix4x2fvEXT = glProgramUniformMatrix4x2fvEMULATION;
    glProgramUniformMatrix4x3fvEXT = glProgramUniformMatrix4x3fvEMULATION;
}

void mapDSAFromEMULATION()
{
    glBindMultiTextureEXT = glBindMultiTextureEMULATION;
    glCheckNamedFramebufferStatusEXT = glCheckNamedFramebufferStatusEMULATION;
    glClientAttribDefaultEXT = glClientAttribDefaultEMULATION;
    glCompressedMultiTexImage1DEXT = glCompressedMultiTexImage1DEMULATION;
    glCompressedMultiTexImage2DEXT = glCompressedMultiTexImage2DEMULATION;
    glCompressedMultiTexImage3DEXT = glCompressedMultiTexImage3DEMULATION;
    glCompressedMultiTexSubImage1DEXT = glCompressedMultiTexSubImage1DEMULATION;
    glCompressedMultiTexSubImage2DEXT = glCompressedMultiTexSubImage2DEMULATION;
    glCompressedMultiTexSubImage3DEXT = glCompressedMultiTexSubImage3DEMULATION;
    glCompressedTextureImage1DEXT = glCompressedTextureImage1DEMULATION;
    glCompressedTextureImage2DEXT = glCompressedTextureImage2DEMULATION;
    glCompressedTextureImage3DEXT = glCompressedTextureImage3DEMULATION;
    glCompressedTextureSubImage1DEXT = glCompressedTextureSubImage1DEMULATION;
    glCompressedTextureSubImage2DEXT = glCompressedTextureSubImage2DEMULATION;
    glCompressedTextureSubImage3DEXT = glCompressedTextureSubImage3DEMULATION;
    glCopyMultiTexImage1DEXT = glCopyMultiTexImage1DEMULATION;
    glCopyMultiTexImage2DEXT = glCopyMultiTexImage2DEMULATION;
    glCopyMultiTexSubImage1DEXT = glCopyMultiTexSubImage1DEMULATION;
    glCopyMultiTexSubImage2DEXT = glCopyMultiTexSubImage2DEMULATION;
    glCopyMultiTexSubImage3DEXT = glCopyMultiTexSubImage3DEMULATION;
    glCopyTextureImage1DEXT = glCopyTextureImage1DEMULATION;
    glCopyTextureImage2DEXT = glCopyTextureImage2DEMULATION;
    glCopyTextureSubImage1DEXT = glCopyTextureSubImage1DEMULATION;
    glCopyTextureSubImage2DEXT = glCopyTextureSubImage2DEMULATION;
    glCopyTextureSubImage3DEXT = glCopyTextureSubImage3DEMULATION;
    glDisableVertexArrayAttribEXT = glDisableVertexArrayAttribEMULATION;
    glDisableVertexArrayEXT = glDisableVertexArrayEMULATION;
    glEnableVertexArrayAttribEXT = glEnableVertexArrayAttribEMULATION;
    glEnableVertexArrayEXT = glEnableVertexArrayEMULATION;
    glFlushMappedNamedBufferRangeEXT = glFlushMappedNamedBufferRangeEMULATION;
    glFramebufferDrawBufferEXT = glFramebufferDrawBufferEMULATION;
    glFramebufferDrawBuffersEXT = glFramebufferDrawBuffersEMULATION;
    glFramebufferReadBufferEXT = glFramebufferReadBufferEMULATION;
    glGenerateMultiTexMipmapEXT = glGenerateMultiTexMipmapEMULATION;
    glGenerateTextureMipmapEXT = glGenerateTextureMipmapEMULATION;
    glGetCompressedMultiTexImageEXT = glGetCompressedMultiTexImageEMULATION;
    glGetCompressedTextureImageEXT = glGetCompressedTextureImageEMULATION;
    glGetDoubleIndexedvEXT = glGetDoubleIndexedvEMULATION;
    glGetDoublei_vEXT = glGetDoublei_vEMULATION;
    glGetFloatIndexedvEXT = glGetFloatIndexedvEMULATION;
    glGetFloati_vEXT = glGetFloati_vEMULATION;
    glGetFramebufferParameterivEXT = glGetFramebufferParameterivEMULATION;
    glGetMultiTexLevelParameterfvEXT = glGetMultiTexLevelParameterfvEMULATION;
    glGetMultiTexLevelParameterivEXT = glGetMultiTexLevelParameterivEMULATION;
    glGetMultiTexParameterIivEXT = glGetMultiTexParameterIivEMULATION;
    glGetMultiTexParameterIuivEXT = glGetMultiTexParameterIuivEMULATION;
    glGetMultiTexParameterfvEXT = glGetMultiTexParameterfvEMULATION;
    glGetMultiTexParameterivEXT = glGetMultiTexParameterivEMULATION;
    glGetNamedBufferParameterivEXT = glGetNamedBufferParameterivEMULATION;
    glGetNamedBufferPointervEXT = glGetNamedBufferPointervEMULATION;
    glGetNamedBufferSubDataEXT = glGetNamedBufferSubDataEMULATION;
    glGetNamedFramebufferAttachmentParameterivEXT = glGetNamedFramebufferAttachmentParameterivEMULATION;
    glGetNamedProgramLocalParameterIivEXT = glGetNamedProgramLocalParameterIivEMULATION;
    glGetNamedProgramLocalParameterIuivEXT = glGetNamedProgramLocalParameterIuivEMULATION;
    glGetNamedProgramLocalParameterdvEXT = glGetNamedProgramLocalParameterdvEMULATION;
    glGetNamedProgramLocalParameterfvEXT = glGetNamedProgramLocalParameterfvEMULATION;
    glGetNamedProgramStringEXT = glGetNamedProgramStringEMULATION;
    glGetNamedProgramivEXT = glGetNamedProgramivEMULATION;
    glGetNamedRenderbufferParameterivEXT = glGetNamedRenderbufferParameterivEMULATION;
    glGetPointerIndexedvEXT = glGetPointerIndexedvEMULATION;
    glGetPointeri_vEXT = glGetPointeri_vEMULATION;
    glGetTextureImageEXT = glGetTextureImageEMULATION;
    glGetTextureLevelParameterfvEXT = glGetTextureLevelParameterfvEMULATION;
    glGetTextureLevelParameterivEXT = glGetTextureLevelParameterivEMULATION;
    glGetTextureParameterIivEXT = glGetTextureParameterIivEMULATION;
    glGetTextureParameterIuivEXT = glGetTextureParameterIuivEMULATION;
    glGetTextureParameterfvEXT = glGetTextureParameterfvEMULATION;
    glGetTextureParameterivEXT = glGetTextureParameterivEMULATION;
    glGetVertexArrayIntegeri_vEXT = glGetVertexArrayIntegeri_vEMULATION;
    glGetVertexArrayIntegervEXT = glGetVertexArrayIntegervEMULATION;
    glGetVertexArrayPointeri_vEXT = glGetVertexArrayPointeri_vEMULATION;
    glGetVertexArrayPointervEXT = glGetVertexArrayPointervEMULATION;
    glMapNamedBufferEXT = glMapNamedBufferEMULATION;
    glMapNamedBufferRangeEXT = glMapNamedBufferRangeEMULATION;
    glMultiTexBufferEXT = glMultiTexBufferEMULATION;
    glMultiTexImage1DEXT = glMultiTexImage1DEMULATION;
    glMultiTexImage2DEXT = glMultiTexImage2DEMULATION;
    glMultiTexImage3DEXT = glMultiTexImage3DEMULATION;
    glMultiTexParameterIivEXT = glMultiTexParameterIivEMULATION;
    glMultiTexParameterIuivEXT = glMultiTexParameterIuivEMULATION;
    glMultiTexParameterfEXT = glMultiTexParameterfEMULATION;
    glMultiTexParameterfvEXT = glMultiTexParameterfvEMULATION;
    glMultiTexParameteriEXT = glMultiTexParameteriEMULATION;
    glMultiTexParameterivEXT = glMultiTexParameterivEMULATION;
    glMultiTexRenderbufferEXT = glMultiTexRenderbufferEMULATION;
    glMultiTexSubImage1DEXT = glMultiTexSubImage1DEMULATION;
    glMultiTexSubImage2DEXT = glMultiTexSubImage2DEMULATION;
    glMultiTexSubImage3DEXT = glMultiTexSubImage3DEMULATION;
    glNamedBufferDataEXT = glNamedBufferDataEMULATION;
    glNamedBufferSubDataEXT = glNamedBufferSubDataEMULATION;
    glNamedCopyBufferSubDataEXT = glNamedCopyBufferSubDataEMULATION;
    glNamedFramebufferRenderbufferEXT = glNamedFramebufferRenderbufferEMULATION;
    glNamedFramebufferTexture1DEXT = glNamedFramebufferTexture1DEMULATION;
    glNamedFramebufferTexture2DEXT = glNamedFramebufferTexture2DEMULATION;
    glNamedFramebufferTexture3DEXT = glNamedFramebufferTexture3DEMULATION;
    glNamedFramebufferTextureEXT = glNamedFramebufferTextureEMULATION;
    glNamedFramebufferTextureFaceEXT = glNamedFramebufferTextureFaceEMULATION;
    glNamedFramebufferTextureLayerEXT = glNamedFramebufferTextureLayerEMULATION;
    glNamedProgramLocalParameter4dEXT = glNamedProgramLocalParameter4dEMULATION;
    glNamedProgramLocalParameter4dvEXT = glNamedProgramLocalParameter4dvEMULATION;
    glNamedProgramLocalParameter4fEXT = glNamedProgramLocalParameter4fEMULATION;
    glNamedProgramLocalParameter4fvEXT = glNamedProgramLocalParameter4fvEMULATION;
    glNamedProgramLocalParameterI4iEXT = glNamedProgramLocalParameterI4iEMULATION;
    glNamedProgramLocalParameterI4ivEXT = glNamedProgramLocalParameterI4ivEMULATION;
    glNamedProgramLocalParameterI4uiEXT = glNamedProgramLocalParameterI4uiEMULATION;
    glNamedProgramLocalParameterI4uivEXT = glNamedProgramLocalParameterI4uivEMULATION;
    glNamedProgramLocalParameters4fvEXT = glNamedProgramLocalParameters4fvEMULATION;
    glNamedProgramLocalParametersI4ivEXT = glNamedProgramLocalParametersI4ivEMULATION;
    glNamedProgramLocalParametersI4uivEXT = glNamedProgramLocalParametersI4uivEMULATION;
    glNamedProgramStringEXT = glNamedProgramStringEMULATION;
    glNamedRenderbufferStorageEXT = glNamedRenderbufferStorageEMULATION;
    glNamedRenderbufferStorageMultisampleCoverageEXT = glNamedRenderbufferStorageMultisampleCoverageEMULATION;
    glNamedRenderbufferStorageMultisampleEXT = glNamedRenderbufferStorageMultisampleEMULATION;
    glTextureBufferEXT = glTextureBufferEMULATION;
    glTextureImage1DEXT = glTextureImage1DEMULATION;
    glTextureImage2DEXT = glTextureImage2DEMULATION;
    glTextureImage3DEXT = glTextureImage3DEMULATION;
    glTextureParameterIivEXT = glTextureParameterIivEMULATION;
    glTextureParameterIuivEXT = glTextureParameterIuivEMULATION;
    glTextureParameterfEXT = glTextureParameterfEMULATION;
    glTextureParameterfvEXT = glTextureParameterfvEMULATION;
    glTextureParameteriEXT = glTextureParameteriEMULATION;
    glTextureParameterivEXT = glTextureParameterivEMULATION;
    glTextureRenderbufferEXT = glTextureRenderbufferEMULATION;
    glTextureSubImage1DEXT = glTextureSubImage1DEMULATION;
    glTextureSubImage2DEXT = glTextureSubImage2DEMULATION;
    glTextureSubImage3DEXT = glTextureSubImage3DEMULATION;
    glUnmapNamedBufferEXT = glUnmapNamedBufferEMULATION;
    glVertexArrayVertexAttribIOffsetEXT = glVertexArrayVertexAttribIOffsetEMULATION;
    glVertexArrayVertexAttribOffsetEXT = glVertexArrayVertexAttribOffsetEMULATION;

    #ifndef ACGL_OPENGL_PROFILE_CORE
    glVertexArrayColorOffsetEXT = glVertexArrayColorOffsetEMULATION;
    glVertexArrayEdgeFlagOffsetEXT = glVertexArrayEdgeFlagOffsetEMULATION;
    glVertexArrayFogCoordOffsetEXT = glVertexArrayFogCoordOffsetEMULATION;
    glVertexArrayIndexOffsetEXT = glVertexArrayIndexOffsetEMULATION;
    glVertexArrayMultiTexCoordOffsetEXT = glVertexArrayMultiTexCoordOffsetEMULATION;
    glVertexArrayNormalOffsetEXT = glVertexArrayNormalOffsetEMULATION;
    glVertexArraySecondaryColorOffsetEXT = glVertexArraySecondaryColorOffsetEMULATION;
    glVertexArrayTexCoordOffsetEXT = glVertexArrayTexCoordOffsetEMULATION;
    glVertexArrayVertexOffsetEXT = glVertexArrayVertexOffsetEMULATION;
    glDisableClientStateIndexedEXT = glDisableClientStateIndexedEMULATION;
    glDisableClientStateiEXT = glDisableClientStateiEMULATION;
    glEnableClientStateIndexedEXT = glEnableClientStateIndexedEMULATION;
    glEnableClientStateiEXT = glEnableClientStateiEMULATION;
    glGetMultiTexEnvfvEXT = glGetMultiTexEnvfvEMULATION;
    glGetMultiTexEnvivEXT = glGetMultiTexEnvivEMULATION;
    glGetMultiTexGendvEXT = glGetMultiTexGendvEMULATION;
    glGetMultiTexGenfvEXT = glGetMultiTexGenfvEMULATION;
    glGetMultiTexGenivEXT = glGetMultiTexGenivEMULATION;
    glGetMultiTexImageEXT = glGetMultiTexImageEMULATION;
    glMatrixFrustumEXT = glMatrixFrustumEMULATION;
    glMatrixLoadIdentityEXT = glMatrixLoadIdentityEMULATION;
    glMatrixLoadTransposedEXT = glMatrixLoadTransposedEMULATION;
    glMatrixLoadTransposefEXT = glMatrixLoadTransposefEMULATION;
    glMatrixLoaddEXT = glMatrixLoaddEMULATION;
    glMatrixLoadfEXT = glMatrixLoadfEMULATION;
    glMatrixMultTransposedEXT = glMatrixMultTransposedEMULATION;
    glMatrixMultTransposefEXT = glMatrixMultTransposefEMULATION;
    glMatrixMultdEXT = glMatrixMultdEMULATION;
    glMatrixMultfEXT = glMatrixMultfEMULATION;
    glMatrixOrthoEXT = glMatrixOrthoEMULATION;
    glMatrixPopEXT = glMatrixPopEMULATION;
    glMatrixPushEXT = glMatrixPushEMULATION;
    glMatrixRotatedEXT = glMatrixRotatedEMULATION;
    glMatrixRotatefEXT = glMatrixRotatefEMULATION;
    glMatrixScaledEXT = glMatrixScaledEMULATION;
    glMatrixScalefEXT = glMatrixScalefEMULATION;
    glMatrixTranslatedEXT = glMatrixTranslatedEMULATION;
    glMatrixTranslatefEXT = glMatrixTranslatefEMULATION;
    glMultiTexCoordPointerEXT = glMultiTexCoordPointerEMULATION;
    glMultiTexEnvfEXT = glMultiTexEnvfEMULATION;
    glMultiTexEnvfvEXT = glMultiTexEnvfvEMULATION;
    glMultiTexEnviEXT = glMultiTexEnviEMULATION;
    glMultiTexEnvivEXT = glMultiTexEnvivEMULATION;
    glMultiTexGendEXT = glMultiTexGendEMULATION;
    glMultiTexGendvEXT = glMultiTexGendvEMULATION;
    glMultiTexGenfEXT = glMultiTexGenfEMULATION;
    glMultiTexGenfvEXT = glMultiTexGenfvEMULATION;
    glMultiTexGeniEXT = glMultiTexGeniEMULATION;
    glMultiTexGenivEXT = glMultiTexGenivEMULATION;
    glPushClientAttribDefaultEXT = glPushClientAttribDefaultEMULATION;
    #endif
}

} // OpenGL
} // ACGL

#ifndef ACGL_USE_GLEW
//
// Without GLEW we use our own pointers:
//
PFNGLBINDMULTITEXTUREEXTPROC glBindMultiTextureEXT;
PFNGLCHECKNAMEDFRAMEBUFFERSTATUSEXTPROC glCheckNamedFramebufferStatusEXT;
PFNGLCLIENTATTRIBDEFAULTEXTPROC glClientAttribDefaultEXT;
PFNGLCOMPRESSEDMULTITEXIMAGE1DEXTPROC glCompressedMultiTexImage1DEXT;
PFNGLCOMPRESSEDMULTITEXIMAGE2DEXTPROC glCompressedMultiTexImage2DEXT;
PFNGLCOMPRESSEDMULTITEXIMAGE3DEXTPROC glCompressedMultiTexImage3DEXT;
PFNGLCOMPRESSEDMULTITEXSUBIMAGE1DEXTPROC glCompressedMultiTexSubImage1DEXT;
PFNGLCOMPRESSEDMULTITEXSUBIMAGE2DEXTPROC glCompressedMultiTexSubImage2DEXT;
PFNGLCOMPRESSEDMULTITEXSUBIMAGE3DEXTPROC glCompressedMultiTexSubImage3DEXT;
PFNGLCOMPRESSEDTEXTUREIMAGE1DEXTPROC glCompressedTextureImage1DEXT;
PFNGLCOMPRESSEDTEXTUREIMAGE2DEXTPROC glCompressedTextureImage2DEXT;
PFNGLCOMPRESSEDTEXTUREIMAGE3DEXTPROC glCompressedTextureImage3DEXT;
PFNGLCOMPRESSEDTEXTURESUBIMAGE1DEXTPROC glCompressedTextureSubImage1DEXT;
PFNGLCOMPRESSEDTEXTURESUBIMAGE2DEXTPROC glCompressedTextureSubImage2DEXT;
PFNGLCOMPRESSEDTEXTURESUBIMAGE3DEXTPROC glCompressedTextureSubImage3DEXT;
PFNGLCOPYMULTITEXIMAGE1DEXTPROC glCopyMultiTexImage1DEXT;
PFNGLCOPYMULTITEXIMAGE2DEXTPROC glCopyMultiTexImage2DEXT;
PFNGLCOPYMULTITEXSUBIMAGE1DEXTPROC glCopyMultiTexSubImage1DEXT;
PFNGLCOPYMULTITEXSUBIMAGE2DEXTPROC glCopyMultiTexSubImage2DEXT;
PFNGLCOPYMULTITEXSUBIMAGE3DEXTPROC glCopyMultiTexSubImage3DEXT;
PFNGLCOPYTEXTUREIMAGE1DEXTPROC glCopyTextureImage1DEXT;
PFNGLCOPYTEXTUREIMAGE2DEXTPROC glCopyTextureImage2DEXT;
PFNGLCOPYTEXTURESUBIMAGE1DEXTPROC glCopyTextureSubImage1DEXT;
PFNGLCOPYTEXTURESUBIMAGE2DEXTPROC glCopyTextureSubImage2DEXT;
PFNGLCOPYTEXTURESUBIMAGE3DEXTPROC glCopyTextureSubImage3DEXT;
PFNGLDISABLECLIENTSTATEINDEXEDEXTPROC glDisableClientStateIndexedEXT;
PFNGLDISABLECLIENTSTATEIEXTPROC glDisableClientStateiEXT;
PFNGLDISABLEVERTEXARRAYATTRIBEXTPROC glDisableVertexArrayAttribEXT;
PFNGLDISABLEVERTEXARRAYEXTPROC glDisableVertexArrayEXT;
PFNGLENABLECLIENTSTATEINDEXEDEXTPROC glEnableClientStateIndexedEXT;
PFNGLENABLECLIENTSTATEIEXTPROC glEnableClientStateiEXT;
PFNGLENABLEVERTEXARRAYATTRIBEXTPROC glEnableVertexArrayAttribEXT;
PFNGLENABLEVERTEXARRAYEXTPROC glEnableVertexArrayEXT;
PFNGLFLUSHMAPPEDNAMEDBUFFERRANGEEXTPROC glFlushMappedNamedBufferRangeEXT;
PFNGLFRAMEBUFFERDRAWBUFFEREXTPROC glFramebufferDrawBufferEXT;
PFNGLFRAMEBUFFERDRAWBUFFERSEXTPROC glFramebufferDrawBuffersEXT;
PFNGLFRAMEBUFFERREADBUFFEREXTPROC glFramebufferReadBufferEXT;
PFNGLGENERATEMULTITEXMIPMAPEXTPROC glGenerateMultiTexMipmapEXT;
PFNGLGENERATETEXTUREMIPMAPEXTPROC glGenerateTextureMipmapEXT;
PFNGLGETCOMPRESSEDMULTITEXIMAGEEXTPROC glGetCompressedMultiTexImageEXT;
PFNGLGETCOMPRESSEDTEXTUREIMAGEEXTPROC glGetCompressedTextureImageEXT;
PFNGLGETDOUBLEINDEXEDVEXTPROC glGetDoubleIndexedvEXT;
PFNGLGETDOUBLEI_VEXTPROC glGetDoublei_vEXT;
PFNGLGETFLOATINDEXEDVEXTPROC glGetFloatIndexedvEXT;
PFNGLGETFLOATI_VEXTPROC glGetFloati_vEXT;
PFNGLGETFRAMEBUFFERPARAMETERIVEXTPROC glGetFramebufferParameterivEXT;
PFNGLGETMULTITEXENVFVEXTPROC glGetMultiTexEnvfvEXT;
PFNGLGETMULTITEXENVIVEXTPROC glGetMultiTexEnvivEXT;
PFNGLGETMULTITEXGENDVEXTPROC glGetMultiTexGendvEXT;
PFNGLGETMULTITEXGENFVEXTPROC glGetMultiTexGenfvEXT;
PFNGLGETMULTITEXGENIVEXTPROC glGetMultiTexGenivEXT;
PFNGLGETMULTITEXIMAGEEXTPROC glGetMultiTexImageEXT;
PFNGLGETMULTITEXLEVELPARAMETERFVEXTPROC glGetMultiTexLevelParameterfvEXT;
PFNGLGETMULTITEXLEVELPARAMETERIVEXTPROC glGetMultiTexLevelParameterivEXT;
PFNGLGETMULTITEXPARAMETERIIVEXTPROC glGetMultiTexParameterIivEXT;
PFNGLGETMULTITEXPARAMETERIUIVEXTPROC glGetMultiTexParameterIuivEXT;
PFNGLGETMULTITEXPARAMETERFVEXTPROC glGetMultiTexParameterfvEXT;
PFNGLGETMULTITEXPARAMETERIVEXTPROC glGetMultiTexParameterivEXT;
PFNGLGETNAMEDBUFFERPARAMETERIVEXTPROC glGetNamedBufferParameterivEXT;
PFNGLGETNAMEDBUFFERPOINTERVEXTPROC glGetNamedBufferPointervEXT;
PFNGLGETNAMEDBUFFERSUBDATAEXTPROC glGetNamedBufferSubDataEXT;
PFNGLGETNAMEDFRAMEBUFFERATTACHMENTPARAMETERIVEXTPROC glGetNamedFramebufferAttachmentParameterivEXT;
PFNGLGETNAMEDPROGRAMLOCALPARAMETERIIVEXTPROC glGetNamedProgramLocalParameterIivEXT;
PFNGLGETNAMEDPROGRAMLOCALPARAMETERIUIVEXTPROC glGetNamedProgramLocalParameterIuivEXT;
PFNGLGETNAMEDPROGRAMLOCALPARAMETERDVEXTPROC glGetNamedProgramLocalParameterdvEXT;
PFNGLGETNAMEDPROGRAMLOCALPARAMETERFVEXTPROC glGetNamedProgramLocalParameterfvEXT;
PFNGLGETNAMEDPROGRAMSTRINGEXTPROC glGetNamedProgramStringEXT;
PFNGLGETNAMEDPROGRAMIVEXTPROC glGetNamedProgramivEXT;
PFNGLGETNAMEDRENDERBUFFERPARAMETERIVEXTPROC glGetNamedRenderbufferParameterivEXT;
PFNGLGETPOINTERINDEXEDVEXTPROC glGetPointerIndexedvEXT;
PFNGLGETPOINTERI_VEXTPROC glGetPointeri_vEXT;
PFNGLGETTEXTUREIMAGEEXTPROC glGetTextureImageEXT;
PFNGLGETTEXTURELEVELPARAMETERFVEXTPROC glGetTextureLevelParameterfvEXT;
PFNGLGETTEXTURELEVELPARAMETERIVEXTPROC glGetTextureLevelParameterivEXT;
PFNGLGETTEXTUREPARAMETERIIVEXTPROC glGetTextureParameterIivEXT;
PFNGLGETTEXTUREPARAMETERIUIVEXTPROC glGetTextureParameterIuivEXT;
PFNGLGETTEXTUREPARAMETERFVEXTPROC glGetTextureParameterfvEXT;
PFNGLGETTEXTUREPARAMETERIVEXTPROC glGetTextureParameterivEXT;
PFNGLGETVERTEXARRAYINTEGERI_VEXTPROC glGetVertexArrayIntegeri_vEXT;
PFNGLGETVERTEXARRAYINTEGERVEXTPROC glGetVertexArrayIntegervEXT;
PFNGLGETVERTEXARRAYPOINTERI_VEXTPROC glGetVertexArrayPointeri_vEXT;
PFNGLGETVERTEXARRAYPOINTERVEXTPROC glGetVertexArrayPointervEXT;
PFNGLMAPNAMEDBUFFEREXTPROC glMapNamedBufferEXT;
PFNGLMAPNAMEDBUFFERRANGEEXTPROC glMapNamedBufferRangeEXT;
PFNGLMATRIXFRUSTUMEXTPROC glMatrixFrustumEXT;
PFNGLMATRIXLOADIDENTITYEXTPROC glMatrixLoadIdentityEXT;
PFNGLMATRIXLOADTRANSPOSEDEXTPROC glMatrixLoadTransposedEXT;
PFNGLMATRIXLOADTRANSPOSEFEXTPROC glMatrixLoadTransposefEXT;
PFNGLMATRIXLOADDEXTPROC glMatrixLoaddEXT;
PFNGLMATRIXLOADFEXTPROC glMatrixLoadfEXT;
PFNGLMATRIXMULTTRANSPOSEDEXTPROC glMatrixMultTransposedEXT;
PFNGLMATRIXMULTTRANSPOSEFEXTPROC glMatrixMultTransposefEXT;
PFNGLMATRIXMULTDEXTPROC glMatrixMultdEXT;
PFNGLMATRIXMULTFEXTPROC glMatrixMultfEXT;
PFNGLMATRIXORTHOEXTPROC glMatrixOrthoEXT;
PFNGLMATRIXPOPEXTPROC glMatrixPopEXT;
PFNGLMATRIXPUSHEXTPROC glMatrixPushEXT;
PFNGLMATRIXROTATEDEXTPROC glMatrixRotatedEXT;
PFNGLMATRIXROTATEFEXTPROC glMatrixRotatefEXT;
PFNGLMATRIXSCALEDEXTPROC glMatrixScaledEXT;
PFNGLMATRIXSCALEFEXTPROC glMatrixScalefEXT;
PFNGLMATRIXTRANSLATEDEXTPROC glMatrixTranslatedEXT;
PFNGLMATRIXTRANSLATEFEXTPROC glMatrixTranslatefEXT;
PFNGLMULTITEXBUFFEREXTPROC glMultiTexBufferEXT;
PFNGLMULTITEXCOORDPOINTEREXTPROC glMultiTexCoordPointerEXT;
PFNGLMULTITEXENVFEXTPROC glMultiTexEnvfEXT;
PFNGLMULTITEXENVFVEXTPROC glMultiTexEnvfvEXT;
PFNGLMULTITEXENVIEXTPROC glMultiTexEnviEXT;
PFNGLMULTITEXENVIVEXTPROC glMultiTexEnvivEXT;
PFNGLMULTITEXGENDEXTPROC glMultiTexGendEXT;
PFNGLMULTITEXGENDVEXTPROC glMultiTexGendvEXT;
PFNGLMULTITEXGENFEXTPROC glMultiTexGenfEXT;
PFNGLMULTITEXGENFVEXTPROC glMultiTexGenfvEXT;
PFNGLMULTITEXGENIEXTPROC glMultiTexGeniEXT;
PFNGLMULTITEXGENIVEXTPROC glMultiTexGenivEXT;
PFNGLMULTITEXIMAGE1DEXTPROC glMultiTexImage1DEXT;
PFNGLMULTITEXIMAGE2DEXTPROC glMultiTexImage2DEXT;
PFNGLMULTITEXIMAGE3DEXTPROC glMultiTexImage3DEXT;
PFNGLMULTITEXPARAMETERIIVEXTPROC glMultiTexParameterIivEXT;
PFNGLMULTITEXPARAMETERIUIVEXTPROC glMultiTexParameterIuivEXT;
PFNGLMULTITEXPARAMETERFEXTPROC glMultiTexParameterfEXT;
PFNGLMULTITEXPARAMETERFVEXTPROC glMultiTexParameterfvEXT;
PFNGLMULTITEXPARAMETERIEXTPROC glMultiTexParameteriEXT;
PFNGLMULTITEXPARAMETERIVEXTPROC glMultiTexParameterivEXT;
PFNGLMULTITEXRENDERBUFFEREXTPROC glMultiTexRenderbufferEXT;
PFNGLMULTITEXSUBIMAGE1DEXTPROC glMultiTexSubImage1DEXT;
PFNGLMULTITEXSUBIMAGE2DEXTPROC glMultiTexSubImage2DEXT;
PFNGLMULTITEXSUBIMAGE3DEXTPROC glMultiTexSubImage3DEXT;
PFNGLNAMEDBUFFERDATAEXTPROC glNamedBufferDataEXT;
PFNGLNAMEDBUFFERSUBDATAEXTPROC glNamedBufferSubDataEXT;
PFNGLNAMEDCOPYBUFFERSUBDATAEXTPROC glNamedCopyBufferSubDataEXT;
PFNGLNAMEDFRAMEBUFFERRENDERBUFFEREXTPROC glNamedFramebufferRenderbufferEXT;
PFNGLNAMEDFRAMEBUFFERTEXTURE1DEXTPROC glNamedFramebufferTexture1DEXT;
PFNGLNAMEDFRAMEBUFFERTEXTURE2DEXTPROC glNamedFramebufferTexture2DEXT;
PFNGLNAMEDFRAMEBUFFERTEXTURE3DEXTPROC glNamedFramebufferTexture3DEXT;
PFNGLNAMEDFRAMEBUFFERTEXTUREEXTPROC glNamedFramebufferTextureEXT;
PFNGLNAMEDFRAMEBUFFERTEXTUREFACEEXTPROC glNamedFramebufferTextureFaceEXT;
PFNGLNAMEDFRAMEBUFFERTEXTURELAYEREXTPROC glNamedFramebufferTextureLayerEXT;
PFNGLNAMEDPROGRAMLOCALPARAMETER4DEXTPROC glNamedProgramLocalParameter4dEXT;
PFNGLNAMEDPROGRAMLOCALPARAMETER4DVEXTPROC glNamedProgramLocalParameter4dvEXT;
PFNGLNAMEDPROGRAMLOCALPARAMETER4FEXTPROC glNamedProgramLocalParameter4fEXT;
PFNGLNAMEDPROGRAMLOCALPARAMETER4FVEXTPROC glNamedProgramLocalParameter4fvEXT;
PFNGLNAMEDPROGRAMLOCALPARAMETERI4IEXTPROC glNamedProgramLocalParameterI4iEXT;
PFNGLNAMEDPROGRAMLOCALPARAMETERI4IVEXTPROC glNamedProgramLocalParameterI4ivEXT;
PFNGLNAMEDPROGRAMLOCALPARAMETERI4UIEXTPROC glNamedProgramLocalParameterI4uiEXT;
PFNGLNAMEDPROGRAMLOCALPARAMETERI4UIVEXTPROC glNamedProgramLocalParameterI4uivEXT;
PFNGLNAMEDPROGRAMLOCALPARAMETERS4FVEXTPROC glNamedProgramLocalParameters4fvEXT;
PFNGLNAMEDPROGRAMLOCALPARAMETERSI4IVEXTPROC glNamedProgramLocalParametersI4ivEXT;
PFNGLNAMEDPROGRAMLOCALPARAMETERSI4UIVEXTPROC glNamedProgramLocalParametersI4uivEXT;
PFNGLNAMEDPROGRAMSTRINGEXTPROC glNamedProgramStringEXT;
PFNGLNAMEDRENDERBUFFERSTORAGEEXTPROC glNamedRenderbufferStorageEXT;
PFNGLNAMEDRENDERBUFFERSTORAGEMULTISAMPLECOVERAGEEXTPROC glNamedRenderbufferStorageMultisampleCoverageEXT;
PFNGLNAMEDRENDERBUFFERSTORAGEMULTISAMPLEEXTPROC glNamedRenderbufferStorageMultisampleEXT;
PFNGLPROGRAMUNIFORM1FEXTPROC glProgramUniform1fEXT;
PFNGLPROGRAMUNIFORM1FVEXTPROC glProgramUniform1fvEXT;
PFNGLPROGRAMUNIFORM1IEXTPROC glProgramUniform1iEXT;
PFNGLPROGRAMUNIFORM1IVEXTPROC glProgramUniform1ivEXT;
PFNGLPROGRAMUNIFORM1UIEXTPROC glProgramUniform1uiEXT;
PFNGLPROGRAMUNIFORM1UIVEXTPROC glProgramUniform1uivEXT;
PFNGLPROGRAMUNIFORM2FEXTPROC glProgramUniform2fEXT;
PFNGLPROGRAMUNIFORM2FVEXTPROC glProgramUniform2fvEXT;
PFNGLPROGRAMUNIFORM2IEXTPROC glProgramUniform2iEXT;
PFNGLPROGRAMUNIFORM2IVEXTPROC glProgramUniform2ivEXT;
PFNGLPROGRAMUNIFORM2UIEXTPROC glProgramUniform2uiEXT;
PFNGLPROGRAMUNIFORM2UIVEXTPROC glProgramUniform2uivEXT;
PFNGLPROGRAMUNIFORM3FEXTPROC glProgramUniform3fEXT;
PFNGLPROGRAMUNIFORM3FVEXTPROC glProgramUniform3fvEXT;
PFNGLPROGRAMUNIFORM3IEXTPROC glProgramUniform3iEXT;
PFNGLPROGRAMUNIFORM3IVEXTPROC glProgramUniform3ivEXT;
PFNGLPROGRAMUNIFORM3UIEXTPROC glProgramUniform3uiEXT;
PFNGLPROGRAMUNIFORM3UIVEXTPROC glProgramUniform3uivEXT;
PFNGLPROGRAMUNIFORM4FEXTPROC glProgramUniform4fEXT;
PFNGLPROGRAMUNIFORM4FVEXTPROC glProgramUniform4fvEXT;
PFNGLPROGRAMUNIFORM4IEXTPROC glProgramUniform4iEXT;
PFNGLPROGRAMUNIFORM4IVEXTPROC glProgramUniform4ivEXT;
PFNGLPROGRAMUNIFORM4UIEXTPROC glProgramUniform4uiEXT;
PFNGLPROGRAMUNIFORM4UIVEXTPROC glProgramUniform4uivEXT;
PFNGLPROGRAMUNIFORMMATRIX2FVEXTPROC glProgramUniformMatrix2fvEXT;
PFNGLPROGRAMUNIFORMMATRIX2X3FVEXTPROC glProgramUniformMatrix2x3fvEXT;
PFNGLPROGRAMUNIFORMMATRIX2X4FVEXTPROC glProgramUniformMatrix2x4fvEXT;
PFNGLPROGRAMUNIFORMMATRIX3FVEXTPROC glProgramUniformMatrix3fvEXT;
PFNGLPROGRAMUNIFORMMATRIX3X2FVEXTPROC glProgramUniformMatrix3x2fvEXT;
PFNGLPROGRAMUNIFORMMATRIX3X4FVEXTPROC glProgramUniformMatrix3x4fvEXT;
PFNGLPROGRAMUNIFORMMATRIX4FVEXTPROC glProgramUniformMatrix4fvEXT;
PFNGLPROGRAMUNIFORMMATRIX4X2FVEXTPROC glProgramUniformMatrix4x2fvEXT;
PFNGLPROGRAMUNIFORMMATRIX4X3FVEXTPROC glProgramUniformMatrix4x3fvEXT;
PFNGLPUSHCLIENTATTRIBDEFAULTEXTPROC glPushClientAttribDefaultEXT;
PFNGLTEXTUREBUFFEREXTPROC glTextureBufferEXT;
PFNGLTEXTUREIMAGE1DEXTPROC glTextureImage1DEXT;
PFNGLTEXTUREIMAGE2DEXTPROC glTextureImage2DEXT;
PFNGLTEXTUREIMAGE3DEXTPROC glTextureImage3DEXT;
PFNGLTEXTUREPARAMETERIIVEXTPROC glTextureParameterIivEXT;
PFNGLTEXTUREPARAMETERIUIVEXTPROC glTextureParameterIuivEXT;
PFNGLTEXTUREPARAMETERFEXTPROC glTextureParameterfEXT;
PFNGLTEXTUREPARAMETERFVEXTPROC glTextureParameterfvEXT;
PFNGLTEXTUREPARAMETERIEXTPROC glTextureParameteriEXT;
PFNGLTEXTUREPARAMETERIVEXTPROC glTextureParameterivEXT;
PFNGLTEXTURERENDERBUFFEREXTPROC glTextureRenderbufferEXT;
PFNGLTEXTURESUBIMAGE1DEXTPROC glTextureSubImage1DEXT;
PFNGLTEXTURESUBIMAGE2DEXTPROC glTextureSubImage2DEXT;
PFNGLTEXTURESUBIMAGE3DEXTPROC glTextureSubImage3DEXT;
PFNGLUNMAPNAMEDBUFFEREXTPROC glUnmapNamedBufferEXT;
PFNGLVERTEXARRAYCOLOROFFSETEXTPROC glVertexArrayColorOffsetEXT;
PFNGLVERTEXARRAYEDGEFLAGOFFSETEXTPROC glVertexArrayEdgeFlagOffsetEXT;
PFNGLVERTEXARRAYFOGCOORDOFFSETEXTPROC glVertexArrayFogCoordOffsetEXT;
PFNGLVERTEXARRAYINDEXOFFSETEXTPROC glVertexArrayIndexOffsetEXT;
PFNGLVERTEXARRAYMULTITEXCOORDOFFSETEXTPROC glVertexArrayMultiTexCoordOffsetEXT;
PFNGLVERTEXARRAYNORMALOFFSETEXTPROC glVertexArrayNormalOffsetEXT;
PFNGLVERTEXARRAYSECONDARYCOLOROFFSETEXTPROC glVertexArraySecondaryColorOffsetEXT;
PFNGLVERTEXARRAYTEXCOORDOFFSETEXTPROC glVertexArrayTexCoordOffsetEXT;
PFNGLVERTEXARRAYVERTEXATTRIBIOFFSETEXTPROC glVertexArrayVertexAttribIOffsetEXT;
PFNGLVERTEXARRAYVERTEXATTRIBOFFSETEXTPROC glVertexArrayVertexAttribOffsetEXT;
PFNGLVERTEXARRAYVERTEXOFFSETEXTPROC glVertexArrayVertexOffsetEXT;


PFNGLPROGRAMUNIFORM1FEXTPROC glProgramUniform1f;
PFNGLPROGRAMUNIFORM1FVEXTPROC glProgramUniform1fv;
PFNGLPROGRAMUNIFORM1IEXTPROC glProgramUniform1i;
PFNGLPROGRAMUNIFORM1IVEXTPROC glProgramUniform1iv;
PFNGLPROGRAMUNIFORM1UIEXTPROC glProgramUniform1ui;
PFNGLPROGRAMUNIFORM1UIVEXTPROC glProgramUniform1uiv;
PFNGLPROGRAMUNIFORM2FEXTPROC glProgramUniform2f;
PFNGLPROGRAMUNIFORM2FVEXTPROC glProgramUniform2fv;
PFNGLPROGRAMUNIFORM2IEXTPROC glProgramUniform2i;
PFNGLPROGRAMUNIFORM2IVEXTPROC glProgramUniform2iv;
PFNGLPROGRAMUNIFORM2UIEXTPROC glProgramUniform2ui;
PFNGLPROGRAMUNIFORM2UIVEXTPROC glProgramUniform2uiv;
PFNGLPROGRAMUNIFORM3FEXTPROC glProgramUniform3f;
PFNGLPROGRAMUNIFORM3FVEXTPROC glProgramUniform3fv;
PFNGLPROGRAMUNIFORM3IEXTPROC glProgramUniform3i;
PFNGLPROGRAMUNIFORM3IVEXTPROC glProgramUniform3iv;
PFNGLPROGRAMUNIFORM3UIEXTPROC glProgramUniform3ui;
PFNGLPROGRAMUNIFORM3UIVEXTPROC glProgramUniform3uiv;
PFNGLPROGRAMUNIFORM4FEXTPROC glProgramUniform4f;
PFNGLPROGRAMUNIFORM4FVEXTPROC glProgramUniform4fv;
PFNGLPROGRAMUNIFORM4IEXTPROC glProgramUniform4i;
PFNGLPROGRAMUNIFORM4IVEXTPROC glProgramUniform4iv;
PFNGLPROGRAMUNIFORM4UIEXTPROC glProgramUniform4ui;
PFNGLPROGRAMUNIFORM4UIVEXTPROC glProgramUniform4uiv;
PFNGLPROGRAMUNIFORMMATRIX2FVEXTPROC glProgramUniformMatrix2fv;
PFNGLPROGRAMUNIFORMMATRIX2X3FVEXTPROC glProgramUniformMatrix2x3fv;
PFNGLPROGRAMUNIFORMMATRIX2X4FVEXTPROC glProgramUniformMatrix2x4fv;
PFNGLPROGRAMUNIFORMMATRIX3FVEXTPROC glProgramUniformMatrix3fv;
PFNGLPROGRAMUNIFORMMATRIX3X2FVEXTPROC glProgramUniformMatrix3x2fv;
PFNGLPROGRAMUNIFORMMATRIX3X4FVEXTPROC glProgramUniformMatrix3x4fv;
PFNGLPROGRAMUNIFORMMATRIX4FVEXTPROC glProgramUniformMatrix4fv;
PFNGLPROGRAMUNIFORMMATRIX4X2FVEXTPROC glProgramUniformMatrix4x2fv;
PFNGLPROGRAMUNIFORMMATRIX4X3FVEXTPROC glProgramUniformMatrix4x3fv;


#endif



namespace ACGL{
namespace OpenGL{
////////////////////////////////////////////////////////////////////////////////////////////////////
// The emulation functions:
// Note: not all are implemented yet ;-)
//
void glBindMultiTextureEMULATION (GLenum texunit, GLenum target, GLuint texture) { ACGL::Utils::error() << "NOT IMPLEMENTED YET" << std::endl; }
GLenum glCheckNamedFramebufferStatusEMULATION (GLuint framebuffer, GLenum target) { ACGL::Utils::error() << "NOT IMPLEMENTED YET" << std::endl; return 0;}
void glClientAttribDefaultEMULATION (GLbitfield mask) { ACGL::Utils::error() << "NOT IMPLEMENTED YET" << std::endl; }
void glCompressedTextureImage1DEMULATION (GLuint texture, GLenum target, GLint level, GLenum internalformat, GLsizei width, GLint border, GLsizei imageSize, const void* data) { ACGL::Utils::error() << "NOT IMPLEMENTED YET" << std::endl; }
void glCompressedTextureImage2DEMULATION (GLuint texture, GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const void* data) { ACGL::Utils::error() << "NOT IMPLEMENTED YET" << std::endl; }
void glCompressedTextureImage3DEMULATION (GLuint texture, GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, const void* data) { ACGL::Utils::error() << "NOT IMPLEMENTED YET" << std::endl; }
void glCompressedTextureSubImage1DEMULATION (GLuint texture, GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, const void* data) { ACGL::Utils::error() << "NOT IMPLEMENTED YET" << std::endl; }
void glCompressedTextureSubImage2DEMULATION (GLuint texture, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const void* data) { ACGL::Utils::error() << "NOT IMPLEMENTED YET" << std::endl; }
void glCompressedTextureSubImage3DEMULATION (GLuint texture, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const void* data) { ACGL::Utils::error() << "NOT IMPLEMENTED YET" << std::endl; }

void glCopyTextureImage1DEMULATION (GLuint texture, GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLint border) { ACGL::Utils::error() << "NOT IMPLEMENTED YET" << std::endl; }
void glCopyTextureImage2DEMULATION (GLuint texture, GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border) { ACGL::Utils::error() << "NOT IMPLEMENTED YET" << std::endl; }
void glCopyTextureSubImage1DEMULATION (GLuint texture, GLenum target, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width) { ACGL::Utils::error() << "NOT IMPLEMENTED YET" << std::endl; }
void glCopyTextureSubImage2DEMULATION (GLuint texture, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height) { ACGL::Utils::error() << "NOT IMPLEMENTED YET" << std::endl; }
void glCopyTextureSubImage3DEMULATION (GLuint texture, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height) { ACGL::Utils::error() << "NOT IMPLEMENTED YET" << std::endl; }
void glEnableVertexArrayEMULATION  (GLuint vaobj, GLenum array) { ACGL::Utils::error() << "NOT IMPLEMENTED YET" << std::endl; }
void glDisableVertexArrayEMULATION (GLuint vaobj, GLenum array) { ACGL::Utils::error() << "NOT IMPLEMENTED YET" << std::endl; }

void glFlushMappedNamedBufferRangeEMULATION (GLuint buffer, GLintptr offset, GLsizeiptr length) { ACGL::Utils::error() << "NOT IMPLEMENTED YET" << std::endl; }
void glFramebufferDrawBufferEMULATION (GLuint framebuffer, GLenum mode) { ACGL::Utils::error() << "NOT IMPLEMENTED YET" << std::endl; }
void glFramebufferDrawBuffersEMULATION (GLuint framebuffer, GLsizei n, const GLenum* bufs) { ACGL::Utils::error() << "NOT IMPLEMENTED YET" << std::endl; }
void glFramebufferReadBufferEMULATION (GLuint framebuffer, GLenum mode) { ACGL::Utils::error() << "NOT IMPLEMENTED YET" << std::endl; }
void glGenerateMultiTexMipmapEMULATION (GLenum texunit, GLenum target) { ACGL::Utils::error() << "NOT IMPLEMENTED YET" << std::endl; }
void glGenerateTextureMipmapEMULATION (GLuint texture, GLenum target) { ACGL::Utils::error() << "NOT IMPLEMENTED YET" << std::endl; }
void glGetCompressedTextureImageEMULATION (GLuint texture, GLenum target, GLint level, void* img) { ACGL::Utils::error() << "NOT IMPLEMENTED YET" << std::endl; }
void glGetDoubleIndexedvEMULATION (GLenum target, GLuint index, GLdouble* params) { ACGL::Utils::error() << "NOT IMPLEMENTED YET" << std::endl; }
void glGetDoublei_vEMULATION (GLenum pname, GLuint index, GLdouble* params) { ACGL::Utils::error() << "NOT IMPLEMENTED YET" << std::endl; }
void glGetFloatIndexedvEMULATION (GLenum target, GLuint index, GLfloat* params) { ACGL::Utils::error() << "NOT IMPLEMENTED YET" << std::endl; }
void glGetFloati_vEMULATION (GLenum pname, GLuint index, GLfloat* params) { ACGL::Utils::error() << "NOT IMPLEMENTED YET" << std::endl; }
void glGetFramebufferParameterivEMULATION (GLuint framebuffer, GLenum pname, GLint* param) { ACGL::Utils::error() << "NOT IMPLEMENTED YET" << std::endl; }


#define GET_MULTI_TEX_PREFIX  int savedActiveTexture, savedClientActiveTexture; \
                              glGetIntegerv(GL_ACTIVE_TEXTURE, &savedActiveTexture); \
                              glActiveTexture(texunit);

#define GET_MULTI_TEX_POSTFIX glActiveTexture( savedActiveTexture ); \
                              openGLRareError();

void glGetMultiTexImageEMULATION (GLenum texunit, GLenum target, GLint level, GLenum format, GLenum type, void* pixels) {
    GET_MULTI_TEX_PREFIX;
    glGetTexImage(  target,  level,  format,  type, pixels);
    GET_MULTI_TEX_POSTFIX;
}

void glGetMultiTexLevelParameterfvEMULATION (GLenum texunit, GLenum target, GLint level, GLenum pname, GLfloat* params) {
    GET_MULTI_TEX_PREFIX;
    glGetTexLevelParameterfv(  target,  level,  pname, params);
    GET_MULTI_TEX_POSTFIX;
}

void glGetMultiTexLevelParameterivEMULATION (GLenum texunit, GLenum target, GLint level, GLenum pname, GLint* params) {
    GET_MULTI_TEX_PREFIX;
    glGetTexLevelParameteriv(  target,  level,  pname, params);
    GET_MULTI_TEX_POSTFIX;
}

void glGetMultiTexParameterIivEMULATION (GLenum texunit, GLenum target, GLenum pname, GLint* params) {
    GET_MULTI_TEX_PREFIX;
    glGetTexParameterIiv(  target,  pname, params);
    GET_MULTI_TEX_POSTFIX;
}

void glGetMultiTexParameterIuivEMULATION (GLenum texunit, GLenum target, GLenum pname, GLuint* params) {
    GET_MULTI_TEX_PREFIX;
    glGetTexParameterIuiv(  target,  pname,  params);
    GET_MULTI_TEX_POSTFIX;
}

void glGetMultiTexParameterfvEMULATION (GLenum texunit, GLenum target, GLenum pname, GLfloat* params) {
    GET_MULTI_TEX_PREFIX;
    glGetTexParameterfv(  target,  pname, params);
    GET_MULTI_TEX_POSTFIX;
}

void glGetMultiTexParameterivEMULATION (GLenum texunit, GLenum target, GLenum pname, GLint* params) {
    GET_MULTI_TEX_PREFIX;
    glGetTexParameteriv(  target,  pname, params);
    GET_MULTI_TEX_POSTFIX;
}

void glGetCompressedMultiTexImageEMULATION (GLenum texunit, GLenum target, GLint level, void* img) {
    GET_MULTI_TEX_PREFIX;
    glGetCompressedTexImage(  target,  level,  img);
    GET_MULTI_TEX_POSTFIX;
}

#undef GET_MULTI_TEX_PREFIX
#undef GET_MULTI_TEX_POSTFIX


void glGetNamedBufferParameterivEMULATION (GLuint buffer, GLenum pname, GLint* params) { ACGL::Utils::error() << "NOT IMPLEMENTED YET" << std::endl; }
void glGetNamedBufferPointervEMULATION (GLuint buffer, GLenum pname, void** params) { ACGL::Utils::error() << "NOT IMPLEMENTED YET" << std::endl; }
void glGetNamedBufferSubDataEMULATION (GLuint buffer, GLintptr offset, GLsizeiptr size, void* data) { ACGL::Utils::error() << "NOT IMPLEMENTED YET" << std::endl; }
void glGetNamedFramebufferAttachmentParameterivEMULATION (GLuint framebuffer, GLenum attachment, GLenum pname, GLint* params) { ACGL::Utils::error() << "NOT IMPLEMENTED YET" << std::endl; }
void glGetNamedProgramLocalParameterIivEMULATION (GLuint program, GLenum target, GLuint index, GLint* params) { ACGL::Utils::error() << "NOT IMPLEMENTED YET" << std::endl; }
void glGetNamedProgramLocalParameterIuivEMULATION (GLuint program, GLenum target, GLuint index, GLuint* params) { ACGL::Utils::error() << "NOT IMPLEMENTED YET" << std::endl; }
void glGetNamedProgramLocalParameterdvEMULATION (GLuint program, GLenum target, GLuint index, GLdouble* params) { ACGL::Utils::error() << "NOT IMPLEMENTED YET" << std::endl; }
void glGetNamedProgramLocalParameterfvEMULATION (GLuint program, GLenum target, GLuint index, GLfloat* params) { ACGL::Utils::error() << "NOT IMPLEMENTED YET" << std::endl; }
void glGetNamedProgramStringEMULATION (GLuint program, GLenum target, GLenum pname, void* string) { ACGL::Utils::error() << "NOT IMPLEMENTED YET" << std::endl; }
void glGetNamedProgramivEMULATION (GLuint program, GLenum target, GLenum pname, GLint* params) { ACGL::Utils::error() << "NOT IMPLEMENTED YET" << std::endl; }
void glGetNamedRenderbufferParameterivEMULATION (GLuint renderbuffer, GLenum pname, GLint* params) { ACGL::Utils::error() << "NOT IMPLEMENTED YET" << std::endl; }
void glGetPointerIndexedvEMULATION (GLenum target, GLuint index, GLvoid** params) { ACGL::Utils::error() << "NOT IMPLEMENTED YET" << std::endl; }
void glGetPointeri_vEMULATION (GLenum pname, GLuint index, GLvoid** params) { ACGL::Utils::error() << "NOT IMPLEMENTED YET" << std::endl; }
void glGetTextureImageEMULATION (GLuint texture, GLenum target, GLint level, GLenum format, GLenum type, void* pixels) { ACGL::Utils::error() << "NOT IMPLEMENTED YET" << std::endl; }
void glGetTextureLevelParameterfvEMULATION (GLuint texture, GLenum target, GLint level, GLenum pname, GLfloat* params) { ACGL::Utils::error() << "NOT IMPLEMENTED YET" << std::endl; }
void glGetTextureLevelParameterivEMULATION (GLuint texture, GLenum target, GLint level, GLenum pname, GLint* params) { ACGL::Utils::error() << "NOT IMPLEMENTED YET" << std::endl; }
void glGetTextureParameterIivEMULATION (GLuint texture, GLenum target, GLenum pname, GLint* params) { ACGL::Utils::error() << "NOT IMPLEMENTED YET" << std::endl; }
void glGetTextureParameterIuivEMULATION (GLuint texture, GLenum target, GLenum pname, GLuint* params) { ACGL::Utils::error() << "NOT IMPLEMENTED YET" << std::endl; }
void glGetTextureParameterfvEMULATION (GLuint texture, GLenum target, GLenum pname, GLfloat* params) { ACGL::Utils::error() << "NOT IMPLEMENTED YET" << std::endl; }
void glGetTextureParameterivEMULATION (GLuint texture, GLenum target, GLenum pname, GLint* params) { ACGL::Utils::error() << "NOT IMPLEMENTED YET" << std::endl; }
void glGetVertexArrayIntegeri_vEMULATION (GLuint vaobj, GLuint index, GLenum pname, GLint* param) { ACGL::Utils::error() << "NOT IMPLEMENTED YET" << std::endl; }
void glGetVertexArrayIntegervEMULATION (GLuint vaobj, GLenum pname, GLint* param) { ACGL::Utils::error() << "NOT IMPLEMENTED YET" << std::endl; }
void glGetVertexArrayPointeri_vEMULATION (GLuint vaobj, GLuint index, GLenum pname, GLvoid** param) { ACGL::Utils::error() << "NOT IMPLEMENTED YET" << std::endl; }
void glGetVertexArrayPointervEMULATION (GLuint vaobj, GLenum pname, GLvoid** param) { ACGL::Utils::error() << "NOT IMPLEMENTED YET" << std::endl; }
GLvoid * glMapNamedBufferEMULATION (GLuint buffer, GLenum access) { ACGL::Utils::error() << "NOT IMPLEMENTED YET" << std::endl; return NULL; }
GLvoid * glMapNamedBufferRangeEMULATION (GLuint buffer, GLintptr offset, GLsizeiptr length, GLbitfield access) { ACGL::Utils::error() << "NOT IMPLEMENTED YET" << std::endl; return NULL; }



/*
// first, probably wrong definition in the specs
void glMultiTexCoordPointerEMULATION (GLenum texunit, GLint size, GLenum type, GLsizei stride, const void* pointer) {
    GLint savedClientActiveTexture;

    glGetIntegerv(GL_CLIENT_ACTIVE_TEXTURE, &savedClientActiveTexture);
    glClientActiveTexture(texunit);
    glTexCoordPointer(size, type, stride, pointer);
    glClientActiveTexture(savedClientActiveTexture);
    openGLRareError();
}*/


//
// Texture
//

#define MULTI_TEX_PREFIX  GLint savedActiveTexture; \
                          glGetIntegerv(GL_ACTIVE_TEXTURE, &savedActiveTexture); \
                          glActiveTexture(texunit);

#define MULTI_TEX_POSTFIX glActiveTexture(savedActiveTexture); \
                          openGLRareError();

void glMultiTexImage1DEMULATION (GLenum texunit, GLenum target, GLint level, GLint internalformat, GLsizei width, GLint border, GLenum format, GLenum type, const void* pixels) {
    MULTI_TEX_PREFIX;
    glTexImage1D( target, level, internalformat, width, border, format, type,  pixels);
    MULTI_TEX_POSTFIX;
}

void glMultiTexImage2DEMULATION (GLenum texunit, GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const void* pixels) {
    MULTI_TEX_PREFIX;
    glTexImage2D( target,  level,  internalformat,  width,  height, border, format, type,  pixels);
    MULTI_TEX_POSTFIX;
}

void glMultiTexImage3DEMULATION (GLenum texunit, GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const void* pixels) {
    MULTI_TEX_PREFIX;
    glTexImage3D( target,  level,  internalformat,  width,  height, depth, border, format, type,  pixels);
    MULTI_TEX_POSTFIX;
}

void glMultiTexParameterIivEMULATION (GLenum texunit, GLenum target, GLenum pname, const GLint* params) {
    MULTI_TEX_PREFIX;
    glTexParameterIiv( target,  pname, params);
    MULTI_TEX_POSTFIX;
}

void glMultiTexParameterIuivEMULATION (GLenum texunit, GLenum target, GLenum pname, const GLuint* params) {
    MULTI_TEX_PREFIX;
    glTexParameterIuiv( target,  pname, params);
    MULTI_TEX_POSTFIX;
}

void glMultiTexParameterfEMULATION (GLenum texunit, GLenum target, GLenum pname, GLfloat param) {
    MULTI_TEX_PREFIX;
    glTexParameterf( target,  pname, param);
    MULTI_TEX_POSTFIX;
}

void glMultiTexParameterfvEMULATION (GLenum texunit, GLenum target, GLenum pname, const GLfloat* param) {
    MULTI_TEX_PREFIX;
    glTexParameterfv( target,  pname, param);
    MULTI_TEX_POSTFIX;
}

void glMultiTexParameteriEMULATION (GLenum texunit, GLenum target, GLenum pname, GLint param) {
    MULTI_TEX_PREFIX;
    glTexParameteri( target,  pname, param);
    MULTI_TEX_POSTFIX;
}

void glMultiTexParameterivEMULATION (GLenum texunit, GLenum target, GLenum pname, const GLint* param) {
    MULTI_TEX_PREFIX;
    glTexParameteriv( target,  pname, param);
    MULTI_TEX_POSTFIX;
}

void glMultiTexSubImage1DEMULATION (GLenum texunit, GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const void* pixels) {
    MULTI_TEX_PREFIX;
    glTexSubImage1D( target,  level,  xoffset,  width,format, type,  pixels);
    MULTI_TEX_POSTFIX;
}

void glMultiTexSubImage2DEMULATION (GLenum texunit, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void* pixels) {
    MULTI_TEX_PREFIX;
    glTexSubImage2D( target,  level,  xoffset,  yoffset,  width,  height,format, type,  pixels);
    MULTI_TEX_POSTFIX;
}

void glMultiTexSubImage3DEMULATION (GLenum texunit, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void* pixels) {
    MULTI_TEX_PREFIX;
    glTexSubImage3D( target,  level,  xoffset,  yoffset,  zoffset,  width,  height,  depth,format, type,  pixels);
    MULTI_TEX_POSTFIX;
}

void glCopyMultiTexImage1DEMULATION (GLenum texunit, GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLint border) {
    MULTI_TEX_PREFIX;
    glCopyTexImage1D( target,  level,  internalformat,  x,  y,  width,  border);
    MULTI_TEX_POSTFIX;
}

void glCopyMultiTexImage2DEMULATION (GLenum texunit, GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border) {
    MULTI_TEX_PREFIX;
    glCopyTexImage2D( target,  level,  internalformat,  x,  y,  width,  height,  border);
    MULTI_TEX_POSTFIX;
}

void glCopyMultiTexSubImage1DEMULATION (GLenum texunit, GLenum target, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width) {
    MULTI_TEX_PREFIX;
    glCopyTexSubImage1D( target,  level,  xoffset,  x,  y,  width);
    MULTI_TEX_POSTFIX;
}

void glCopyMultiTexSubImage2DEMULATION (GLenum texunit, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height) {
    MULTI_TEX_PREFIX;
    glCopyTexSubImage2D( target,  level,  xoffset,  yoffset,  x,  y,  width,  height);
    MULTI_TEX_POSTFIX;
}

void glCopyMultiTexSubImage3DEMULATION (GLenum texunit, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height) {
    MULTI_TEX_PREFIX;
    glCopyTexSubImage3D( target,  level,  xoffset,  yoffset,  zoffset,  x,  y,  width,  height);
    MULTI_TEX_POSTFIX;
}

void glCompressedMultiTexImage1DEMULATION (GLenum texunit, GLenum target, GLint level, GLenum internalformat, GLsizei width, GLint border, GLsizei imageSize, const void* data) {
    MULTI_TEX_PREFIX;
    glCompressedTexImage1D( target,  level,  internalformat,  width,  border,  imageSize, data);
    MULTI_TEX_POSTFIX;
}

void glCompressedMultiTexImage2DEMULATION (GLenum texunit, GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const void* data) {
    MULTI_TEX_PREFIX;
    glCompressedTexImage2D( target,  level,  internalformat,  width,  height,  border,  imageSize, data);
    MULTI_TEX_POSTFIX;
}

void glCompressedMultiTexImage3DEMULATION (GLenum texunit, GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, const void* data) {
    MULTI_TEX_PREFIX;
    glCompressedTexImage3D( target,  level,  internalformat,  width,  height,  depth,  border,  imageSize, data);
    MULTI_TEX_POSTFIX;
}

void glCompressedMultiTexSubImage1DEMULATION (GLenum texunit, GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, const void* data) {
    MULTI_TEX_PREFIX;
    glCompressedTexSubImage1D( target,  level,  xoffset,  width,  format,  imageSize, data);
    MULTI_TEX_POSTFIX;
}

void glCompressedMultiTexSubImage2DEMULATION (GLenum texunit, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const void* data) {
    MULTI_TEX_PREFIX;
    glCompressedTexSubImage2D( target,  level,  xoffset,  yoffset,  width,  height,  format,  imageSize, data);
    MULTI_TEX_POSTFIX;
}

void glCompressedMultiTexSubImage3DEMULATION (GLenum texunit, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const void* data) {
    MULTI_TEX_PREFIX;
    glCompressedTexSubImage3D( target,  level,  xoffset,  yoffset,  zoffset,  width,  height,  depth,  format,  imageSize, data);
    MULTI_TEX_POSTFIX;
}

void glMultiTexBufferEMULATION (GLenum texunit, GLenum target, GLenum internalformat, GLuint buffer) {
    MULTI_TEX_PREFIX;
    glTexBuffer( target,  internalformat,  buffer);
    MULTI_TEX_POSTFIX;
}


void glMultiTexRenderbufferEMULATION (GLenum texunit, GLenum target, GLuint renderbuffer) {
    ACGL::Utils::error() << "NOT IMPLEMENTED YET" << std::endl;
    //MULTI_TEX_PREFIX;
    //glTexRenderbuffer( target, renderbuffer);
    //MULTI_TEX_POSTFIX;
}

#undef MULTI_TEX_PREFIX
#undef MULTI_TEX_POSTFIX




void glNamedBufferDataEMULATION (GLuint buffer, GLsizeiptr size, const void* data, GLenum usage) { ACGL::Utils::error() << "NOT IMPLEMENTED YET" << std::endl; }
void glNamedBufferSubDataEMULATION (GLuint buffer, GLintptr offset, GLsizeiptr size, const void* data) { ACGL::Utils::error() << "NOT IMPLEMENTED YET" << std::endl; }
void glNamedCopyBufferSubDataEMULATION (GLuint readBuffer, GLuint writeBuffer, GLintptr readOffset, GLintptr writeOffset, GLsizeiptr size) { ACGL::Utils::error() << "NOT IMPLEMENTED YET" << std::endl; }
void glNamedFramebufferRenderbufferEMULATION (GLuint framebuffer, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer) { ACGL::Utils::error() << "NOT IMPLEMENTED YET" << std::endl; }
void glNamedFramebufferTexture1DEMULATION (GLuint framebuffer, GLenum attachment, GLenum textarget, GLuint texture, GLint level) { ACGL::Utils::error() << "NOT IMPLEMENTED YET" << std::endl; }
void glNamedFramebufferTexture2DEMULATION (GLuint framebuffer, GLenum attachment, GLenum textarget, GLuint texture, GLint level) { ACGL::Utils::error() << "NOT IMPLEMENTED YET" << std::endl; }
void glNamedFramebufferTexture3DEMULATION (GLuint framebuffer, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLint zoffset) { ACGL::Utils::error() << "NOT IMPLEMENTED YET" << std::endl; }
void glNamedFramebufferTextureEMULATION (GLuint framebuffer, GLenum attachment, GLuint texture, GLint level) { ACGL::Utils::error() << "NOT IMPLEMENTED YET" << std::endl; }
void glNamedFramebufferTextureFaceEMULATION (GLuint framebuffer, GLenum attachment, GLuint texture, GLint level, GLenum face) { ACGL::Utils::error() << "NOT IMPLEMENTED YET" << std::endl; }
void glNamedFramebufferTextureLayerEMULATION (GLuint framebuffer, GLenum attachment, GLuint texture, GLint level, GLint layer) { ACGL::Utils::error() << "NOT IMPLEMENTED YET" << std::endl; }
void glNamedProgramLocalParameter4dEMULATION (GLuint program, GLenum target, GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w) { ACGL::Utils::error() << "NOT IMPLEMENTED YET" << std::endl; }
void glNamedProgramLocalParameter4dvEMULATION (GLuint program, GLenum target, GLuint index, const GLdouble* params) { ACGL::Utils::error() << "NOT IMPLEMENTED YET" << std::endl; }
void glNamedProgramLocalParameter4fEMULATION (GLuint program, GLenum target, GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w) { ACGL::Utils::error() << "NOT IMPLEMENTED YET" << std::endl; }
void glNamedProgramLocalParameter4fvEMULATION (GLuint program, GLenum target, GLuint index, const GLfloat* params) { ACGL::Utils::error() << "NOT IMPLEMENTED YET" << std::endl; }
void glNamedProgramLocalParameterI4iEMULATION (GLuint program, GLenum target, GLuint index, GLint x, GLint y, GLint z, GLint w) { ACGL::Utils::error() << "NOT IMPLEMENTED YET" << std::endl; }
void glNamedProgramLocalParameterI4ivEMULATION (GLuint program, GLenum target, GLuint index, const GLint* params) { ACGL::Utils::error() << "NOT IMPLEMENTED YET" << std::endl; }
void glNamedProgramLocalParameterI4uiEMULATION (GLuint program, GLenum target, GLuint index, GLuint x, GLuint y, GLuint z, GLuint w) { ACGL::Utils::error() << "NOT IMPLEMENTED YET" << std::endl; }
void glNamedProgramLocalParameterI4uivEMULATION (GLuint program, GLenum target, GLuint index, const GLuint* params) { ACGL::Utils::error() << "NOT IMPLEMENTED YET" << std::endl; }
void glNamedProgramLocalParameters4fvEMULATION (GLuint program, GLenum target, GLuint index, GLsizei count, const GLfloat* params) { ACGL::Utils::error() << "NOT IMPLEMENTED YET" << std::endl; }
void glNamedProgramLocalParametersI4ivEMULATION (GLuint program, GLenum target, GLuint index, GLsizei count, const GLint* params) { ACGL::Utils::error() << "NOT IMPLEMENTED YET" << std::endl; }
void glNamedProgramLocalParametersI4uivEMULATION (GLuint program, GLenum target, GLuint index, GLsizei count, const GLuint* params) { ACGL::Utils::error() << "NOT IMPLEMENTED YET" << std::endl; }
void glNamedProgramStringEMULATION (GLuint program, GLenum target, GLenum format, GLsizei len, const void* string) { ACGL::Utils::error() << "NOT IMPLEMENTED YET" << std::endl; }
void glNamedRenderbufferStorageEMULATION (GLuint renderbuffer, GLenum internalformat, GLsizei width, GLsizei height) { ACGL::Utils::error() << "NOT IMPLEMENTED YET" << std::endl; }
void glNamedRenderbufferStorageMultisampleCoverageEMULATION (GLuint renderbuffer, GLsizei coverageSamples, GLsizei colorSamples, GLenum internalformat, GLsizei width, GLsizei height) { ACGL::Utils::error() << "NOT IMPLEMENTED YET" << std::endl; }
void glNamedRenderbufferStorageMultisampleEMULATION (GLuint renderbuffer, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height) { ACGL::Utils::error() << "NOT IMPLEMENTED YET" << std::endl; }

//
// set uniforms:
//

#define GL_UNIFORM_PROGRAM_PREFIX   GLint oldProgram; \
                                    ACGL::Utils::debug() << "Emulating DSA" << std::endl; \
                                    glGetIntegerv( GL_CURRENT_PROGRAM, &oldProgram ); \
                                    glUseProgram( program );

#define GL_UNIFORM_PROGRAM_POSTFIX  glUseProgram( oldProgram ); \
                                    openGLRareError();


void glProgramUniform1fEMULATION ( GLuint program, GLint location, GLfloat v0) {
    GL_UNIFORM_PROGRAM_PREFIX;
    glUniform1f( location, v0);
    GL_UNIFORM_PROGRAM_POSTFIX;
}

void glProgramUniform1fvEMULATION ( GLuint program, GLint location, GLsizei count, const GLfloat* value) {
    GL_UNIFORM_PROGRAM_PREFIX;
    glUniform1fv( location,  count, value);
    GL_UNIFORM_PROGRAM_POSTFIX;
}

void glProgramUniform1iEMULATION ( GLuint program, GLint location, GLint v0) {
    GL_UNIFORM_PROGRAM_PREFIX;
    glUniform1i( location,  v0);
    GL_UNIFORM_PROGRAM_POSTFIX;
}

void glProgramUniform1ivEMULATION ( GLuint program, GLint location, GLsizei count, const GLint* value) {
    GL_UNIFORM_PROGRAM_PREFIX;
    glUniform1iv( location,  count, value);
    GL_UNIFORM_PROGRAM_POSTFIX;
}

void glProgramUniform1uiEMULATION ( GLuint program, GLint location, GLuint v0) {
    GL_UNIFORM_PROGRAM_PREFIX;
    glUniform1ui( location,  v0);
    GL_UNIFORM_PROGRAM_POSTFIX;
}

void glProgramUniform1uivEMULATION ( GLuint program, GLint location, GLsizei count, const GLuint* value) {
    GL_UNIFORM_PROGRAM_PREFIX;
    glUniform1uiv( location,  count, value);
    GL_UNIFORM_PROGRAM_POSTFIX;
}

void glProgramUniform2fEMULATION ( GLuint program, GLint location, GLfloat v0, GLfloat v1) {
    GL_UNIFORM_PROGRAM_PREFIX;
    glUniform2f( location,  v0, v1);
    GL_UNIFORM_PROGRAM_POSTFIX;
}

void glProgramUniform2fvEMULATION ( GLuint program, GLint location, GLsizei count, const GLfloat* value) {
    GL_UNIFORM_PROGRAM_PREFIX;
    glUniform2fv( location,  count, value);
    GL_UNIFORM_PROGRAM_POSTFIX;
}

void glProgramUniform2iEMULATION ( GLuint program, GLint location, GLint v0, GLint v1) {
    GL_UNIFORM_PROGRAM_PREFIX;
    glUniform2i( location,  v0, v1);
    GL_UNIFORM_PROGRAM_POSTFIX;
}

void glProgramUniform2ivEMULATION ( GLuint program, GLint location, GLsizei count, const GLint* value) {
    GL_UNIFORM_PROGRAM_PREFIX;
    glUniform2iv( location,  count, value);
    GL_UNIFORM_PROGRAM_POSTFIX;
}

void glProgramUniform2uiEMULATION ( GLuint program, GLint location, GLuint v0, GLuint v1) {
    GL_UNIFORM_PROGRAM_PREFIX;
    glUniform2ui( location,  v0, v1);
    GL_UNIFORM_PROGRAM_POSTFIX;
}

void glProgramUniform2uivEMULATION ( GLuint program, GLint location, GLsizei count, const GLuint* value) {
    GL_UNIFORM_PROGRAM_PREFIX;
    glUniform2uiv( location,  count, value);
    GL_UNIFORM_PROGRAM_POSTFIX;
}

void glProgramUniform3fEMULATION ( GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2) {
    GL_UNIFORM_PROGRAM_PREFIX;
    glUniform3f( location,  v0, v1, v2);
    GL_UNIFORM_PROGRAM_POSTFIX;
}

void glProgramUniform3fvEMULATION ( GLuint program, GLint location, GLsizei count, const GLfloat* value) {
    GL_UNIFORM_PROGRAM_PREFIX;
    glUniform3fv( location,  count, value);
    GL_UNIFORM_PROGRAM_POSTFIX;
}

void glProgramUniform3iEMULATION ( GLuint program, GLint location, GLint v0, GLint v1, GLint v2) {
    GL_UNIFORM_PROGRAM_PREFIX;
    glUniform3i( location,  v0, v1, v2);
    GL_UNIFORM_PROGRAM_POSTFIX;
}

void glProgramUniform3ivEMULATION ( GLuint program, GLint location, GLsizei count, const GLint* value) {
    GL_UNIFORM_PROGRAM_PREFIX;
    glUniform3iv( location,  count, value);
    GL_UNIFORM_PROGRAM_POSTFIX;
}

void glProgramUniform3uiEMULATION ( GLuint program, GLint location, GLuint v0, GLuint v1, GLuint v2) {
    GL_UNIFORM_PROGRAM_PREFIX;
    glUniform3ui( location,  v0, v1, v2);
    GL_UNIFORM_PROGRAM_POSTFIX;
}

void glProgramUniform3uivEMULATION ( GLuint program, GLint location, GLsizei count, const GLuint* value) {
    GL_UNIFORM_PROGRAM_PREFIX;
    glUniform3uiv( location,  count, value);
    GL_UNIFORM_PROGRAM_POSTFIX;
}

void glProgramUniform4fEMULATION ( GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3) {
    GL_UNIFORM_PROGRAM_PREFIX;
    glUniform4f( location,  v0, v1, v2, v3);
    GL_UNIFORM_PROGRAM_POSTFIX;
}

void glProgramUniform4fvEMULATION ( GLuint program, GLint location, GLsizei count, const GLfloat* value) {
    GL_UNIFORM_PROGRAM_PREFIX;
    glUniform4fv( location,  count, value);
    GL_UNIFORM_PROGRAM_POSTFIX;
}

void glProgramUniform4iEMULATION ( GLuint program, GLint location, GLint v0, GLint v1, GLint v2, GLint v3) {
    GL_UNIFORM_PROGRAM_PREFIX;
    glUniform4i( location,  v0, v1, v2, v3);
    GL_UNIFORM_PROGRAM_POSTFIX;
}

void glProgramUniform4ivEMULATION ( GLuint program, GLint location, GLsizei count, const GLint* value) {
    GL_UNIFORM_PROGRAM_PREFIX;
    glUniform4iv( location,  count, value);
    GL_UNIFORM_PROGRAM_POSTFIX;
}

void glProgramUniform4uiEMULATION ( GLuint program, GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3) {
    GL_UNIFORM_PROGRAM_PREFIX;
    glUniform4ui( location,  v0, v1, v2, v3);
    GL_UNIFORM_PROGRAM_POSTFIX;
}

void glProgramUniform4uivEMULATION ( GLuint program, GLint location, GLsizei count, const GLuint* value) {
    GL_UNIFORM_PROGRAM_PREFIX;
    glUniform4uiv( location,  count, value);
    GL_UNIFORM_PROGRAM_POSTFIX;
}

void glProgramUniformMatrix2fvEMULATION ( GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value) {
    GL_UNIFORM_PROGRAM_PREFIX;
    glUniformMatrix2fv( location,  count,  transpose, value);
    GL_UNIFORM_PROGRAM_POSTFIX;
}

void glProgramUniformMatrix2x3fvEMULATION ( GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value) {
    GL_UNIFORM_PROGRAM_PREFIX;
    glUniformMatrix2x3fv( location,  count,  transpose, value);
    GL_UNIFORM_PROGRAM_POSTFIX;
}

void glProgramUniformMatrix2x4fvEMULATION ( GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value) {
    GL_UNIFORM_PROGRAM_PREFIX;
    glUniformMatrix2x4fv( location,  count,  transpose, value);
    GL_UNIFORM_PROGRAM_POSTFIX;
}

void glProgramUniformMatrix3fvEMULATION ( GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value) {
    GL_UNIFORM_PROGRAM_PREFIX;
    glUniformMatrix3fv( location,  count,  transpose, value);
    GL_UNIFORM_PROGRAM_POSTFIX;
}

void glProgramUniformMatrix3x2fvEMULATION ( GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value) {
    GL_UNIFORM_PROGRAM_PREFIX;
    glUniformMatrix3x2fv( location,  count,  transpose, value);
    GL_UNIFORM_PROGRAM_POSTFIX;
}

void glProgramUniformMatrix3x4fvEMULATION ( GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value) {
    GL_UNIFORM_PROGRAM_PREFIX;
    glUniformMatrix3x4fv( location,  count,  transpose, value);
    GL_UNIFORM_PROGRAM_POSTFIX;
}

void glProgramUniformMatrix4fvEMULATION ( GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value) {
    GL_UNIFORM_PROGRAM_PREFIX;
    glUniformMatrix4fv( location,  count,  transpose, value);
    GL_UNIFORM_PROGRAM_POSTFIX;
}

void glProgramUniformMatrix4x2fvEMULATION ( GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value) {
    GL_UNIFORM_PROGRAM_PREFIX;
    glUniformMatrix4x2fv( location,  count,  transpose, value);
    GL_UNIFORM_PROGRAM_POSTFIX;
}

void glProgramUniformMatrix4x3fvEMULATION ( GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value) {
    GL_UNIFORM_PROGRAM_PREFIX;
    glUniformMatrix4x3fv( location,  count,  transpose, value);
    GL_UNIFORM_PROGRAM_POSTFIX;
}

#undef GL_UNIFORM_PROGRAM_PREFIX
#undef GL_UNIFORM_PROGRAM_POSTFIX

void glTextureBufferEMULATION (GLuint texture, GLenum target, GLenum internalformat, GLuint buffer) { ACGL::Utils::error() << "NOT IMPLEMENTED YET" << std::endl; }
void glTextureImage1DEMULATION (GLuint texture, GLenum target, GLint level, GLint internalformat, GLsizei width, GLint border, GLenum format, GLenum type, const void* pixels) { ACGL::Utils::error() << "NOT IMPLEMENTED YET" << std::endl; }
void glTextureImage2DEMULATION (GLuint texture, GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const void* pixels) { ACGL::Utils::error() << "NOT IMPLEMENTED YET" << std::endl; }
void glTextureImage3DEMULATION (GLuint texture, GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const void* pixels) { ACGL::Utils::error() << "NOT IMPLEMENTED YET" << std::endl; }
void glTextureParameterIivEMULATION (GLuint texture, GLenum target, GLenum pname, const GLint* params) { ACGL::Utils::error() << "NOT IMPLEMENTED YET" << std::endl; }
void glTextureParameterIuivEMULATION (GLuint texture, GLenum target, GLenum pname, const GLuint* params) { ACGL::Utils::error() << "NOT IMPLEMENTED YET" << std::endl; }
void glTextureParameterfEMULATION (GLuint texture, GLenum target, GLenum pname, GLfloat param) { ACGL::Utils::error() << "NOT IMPLEMENTED YET" << std::endl; }
void glTextureParameterfvEMULATION (GLuint texture, GLenum target, GLenum pname, const GLfloat* param) { ACGL::Utils::error() << "NOT IMPLEMENTED YET" << std::endl; }
void glTextureParameteriEMULATION (GLuint texture, GLenum target, GLenum pname, GLint param) { ACGL::Utils::error() << "NOT IMPLEMENTED YET" << std::endl; }
void glTextureParameterivEMULATION (GLuint texture, GLenum target, GLenum pname, const GLint* param) { ACGL::Utils::error() << "NOT IMPLEMENTED YET" << std::endl; }
void glTextureRenderbufferEMULATION (GLuint texture, GLenum target, GLuint renderbuffer) { ACGL::Utils::error() << "NOT IMPLEMENTED YET" << std::endl; }
void glTextureSubImage1DEMULATION (GLuint texture, GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const void* pixels) { ACGL::Utils::error() << "NOT IMPLEMENTED YET" << std::endl; }
void glTextureSubImage2DEMULATION (GLuint texture, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void* pixels) { ACGL::Utils::error() << "NOT IMPLEMENTED YET" << std::endl; }
void glTextureSubImage3DEMULATION (GLuint texture, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void* pixels) { ACGL::Utils::error() << "NOT IMPLEMENTED YET" << std::endl; }
GLboolean glUnmapNamedBufferEMULATION (GLuint buffer) { ACGL::Utils::error() << "NOT IMPLEMENTED YET" << std::endl; return GL_FALSE; }

//
// Vertex Array Object related functions
//
#if (ACGL_OPENGL_VERSION < 30)
void glVertexArrayVertexAttribIOffsetEMULATION (GLuint vaobj, GLuint buffer, GLuint index, GLint size, GLenum type, GLsizei stride, GLintptr offset)                      { ACGL::Utils::error() << "VertexArrayObjects are not supported pre OpenGL 3" << std::endl; }
void glVertexArrayVertexAttribOffsetEMULATION (GLuint vaobj, GLuint buffer, GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, GLintptr offset) { ACGL::Utils::error() << "VertexArrayObjects are not supported pre OpenGL 3" << std::endl; }
void glEnableVertexArrayAttribEMULATION (GLuint vaobj, GLuint index)                                                                                                      { ACGL::Utils::error() << "VertexArrayObjects are not supported pre OpenGL 3" << std::endl; }
void glDisableVertexArrayAttribEMULATION (GLuint vaobj, GLuint index)                                                                                                     { ACGL::Utils::error() << "VertexArrayObjects are not supported pre OpenGL 3" << std::endl; }
#else

#define VAO_PREFIX  GLint oldVAO; \
                    glGetIntegerv( GL_VERTEX_ARRAY_BINDING, &oldVAO ); \
                    glBindVertexArray( vaobj );

#define VAO_POSTFIX if ((GLuint)oldVAO != vaobj) {\
                        glBindVertexArray( oldVAO );\
                    } \
                    openGLRareError();

void glVertexArrayVertexAttribIOffsetEMULATION (GLuint vaobj, GLuint buffer, GLuint index, GLint size, GLenum type, GLsizei stride, GLintptr offset)
{
    VAO_PREFIX;
    GLint oldArrayBuffer;
    glGetIntegerv( GL_ARRAY_BUFFER_BINDING, &oldArrayBuffer );
    glBindBuffer(GL_ARRAY_BUFFER, buffer);

    glVertexAttribIPointer( index, size, type, stride, (void*) offset );

    glBindBuffer(GL_ARRAY_BUFFER, oldArrayBuffer);
    VAO_POSTFIX;
}

void glVertexArrayVertexAttribOffsetEMULATION (GLuint vaobj, GLuint buffer, GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, GLintptr offset)
{
    VAO_PREFIX;
    GLint oldArrayBuffer;
    glGetIntegerv( GL_ARRAY_BUFFER_BINDING, &oldArrayBuffer );
    glBindBuffer(GL_ARRAY_BUFFER, buffer);

    glVertexAttribPointer( index, size, type, normalized, stride, (void*) offset );

    glBindBuffer(GL_ARRAY_BUFFER, oldArrayBuffer);
    VAO_POSTFIX;
}

void glEnableVertexArrayAttribEMULATION (GLuint vaobj, GLuint index)
{
    VAO_PREFIX;
    glEnableVertexAttribArray( index );
    VAO_POSTFIX;
}

void glDisableVertexArrayAttribEMULATION (GLuint vaobj, GLuint index)
{
    VAO_PREFIX;
    glDisableVertexAttribArray( index );
    VAO_POSTFIX;
}

#endif

#ifndef ACGL_OPENGL_PROFILE_CORE
void glVertexArrayVertexOffsetEMULATION (GLuint vaobj, GLuint buffer, GLint size, GLenum type, GLsizei stride, GLintptr offset) { ACGL::Utils::error() << "NOT IMPLEMENTED YET" << std::endl; }
void glVertexArrayColorOffsetEMULATION (GLuint vaobj, GLuint buffer, GLint size, GLenum type, GLsizei stride, GLintptr offset) { ACGL::Utils::error() << "NOT IMPLEMENTED YET" << std::endl; }
void glVertexArrayEdgeFlagOffsetEMULATION (GLuint vaobj, GLuint buffer, GLsizei stride, GLintptr offset) { ACGL::Utils::error() << "NOT IMPLEMENTED YET" << std::endl; }
void glVertexArrayFogCoordOffsetEMULATION (GLuint vaobj, GLuint buffer, GLenum type, GLsizei stride, GLintptr offset) { ACGL::Utils::error() << "NOT IMPLEMENTED YET" << std::endl; }
void glVertexArrayIndexOffsetEMULATION (GLuint vaobj, GLuint buffer, GLenum type, GLsizei stride, GLintptr offset) { ACGL::Utils::error() << "NOT IMPLEMENTED YET" << std::endl; }
void glVertexArrayMultiTexCoordOffsetEMULATION (GLuint vaobj, GLuint buffer, GLenum texunit, GLint size, GLenum type, GLsizei stride, GLintptr offset) { ACGL::Utils::error() << "NOT IMPLEMENTED YET" << std::endl; }
void glVertexArrayNormalOffsetEMULATION (GLuint vaobj, GLuint buffer, GLenum type, GLsizei stride, GLintptr offset) { ACGL::Utils::error() << "NOT IMPLEMENTED YET" << std::endl; }
void glVertexArraySecondaryColorOffsetEMULATION (GLuint vaobj, GLuint buffer, GLint size, GLenum type, GLsizei stride, GLintptr offset) { ACGL::Utils::error() << "NOT IMPLEMENTED YET" << std::endl; }
void glVertexArrayTexCoordOffsetEMULATION (GLuint vaobj, GLuint buffer, GLint size, GLenum type, GLsizei stride, GLintptr offset) { ACGL::Utils::error() << "NOT IMPLEMENTED YET" << std::endl; }

#define GET_MULTI_TEX_PREFIX  int savedActiveTexture, savedClientActiveTexture; \
                              glGetIntegerv(GL_ACTIVE_TEXTURE, &savedActiveTexture); \
                              glActiveTexture(texunit);

#define GET_MULTI_TEX_POSTFIX glActiveTexture( savedActiveTexture ); \
                              openGLRareError();

void glGetMultiTexEnvfvEMULATION (GLenum texunit, GLenum target, GLenum pname, GLfloat* params) {
    GET_MULTI_TEX_PREFIX;
    glGetTexEnvfv(  target,  pname, params);
    GET_MULTI_TEX_POSTFIX;
}

void glGetMultiTexEnvivEMULATION (GLenum texunit, GLenum target, GLenum pname, GLint* params) {
    GET_MULTI_TEX_PREFIX;
    glGetTexEnviv(  target,  pname, params);
    GET_MULTI_TEX_POSTFIX;
}

void glGetMultiTexGendvEMULATION (GLenum texunit, GLenum coord, GLenum pname, GLdouble* params) {
    GET_MULTI_TEX_PREFIX;
    glGetTexGendv(  coord,  pname, params);
    GET_MULTI_TEX_POSTFIX;
}

void glGetMultiTexGenfvEMULATION (GLenum texunit, GLenum coord, GLenum pname, GLfloat* params) {
    GET_MULTI_TEX_PREFIX;
    glGetTexGenfv(  coord,  pname, params);
    GET_MULTI_TEX_POSTFIX;
}

void glGetMultiTexGenivEMULATION (GLenum texunit, GLenum coord, GLenum pname, GLint* params) {
    GET_MULTI_TEX_PREFIX;
    glGetTexGeniv(  coord,  pname, params);
    GET_MULTI_TEX_POSTFIX;
}
#undef GET_MULTI_TEX_PREFIX
#undef GET_MULTI_TEX_POSTFIX

//
// Matrix operations
//
#define MATRIX_OPERATIONS_PREFIX    GLint savedMatrixMode; \
                                    glGetIntegerv(GL_MATRIX_MODE, &savedMatrixMode); \
                                    if (matrixMode >= GL_TEXTURE0 && matrixMode <= GL_TEXTURE31) { \
                                       int savedActiveTexture; \
                                       glMatrixMode(GL_TEXTURE); \
                                       glGetIntegerv(GL_ACTIVE_TEXTURE, &savedActiveTexture); \
                                       glActiveTexture(matrixMode);

#define MATRIX_OPERATIONS_INFIX        glActiveTexture(savedActiveTexture); \
                                    } else { \
                                       glMatrixMode(matrixMode);

#define MATRIX_OPERATIONS_POSTFIX   } \
                                    glMatrixMode(savedMatrixMode); \
                                    openGLRareError();


void glMatrixFrustumEMULATION (GLenum matrixMode, GLdouble l, GLdouble r, GLdouble b, GLdouble t, GLdouble n, GLdouble f) {
    MATRIX_OPERATIONS_PREFIX;
    glFrustum(l, r, b, t, n, f);
    MATRIX_OPERATIONS_INFIX;
    glFrustum(l, r, b, t, n, f);
    MATRIX_OPERATIONS_POSTFIX;
}

void glMatrixLoadIdentityEMULATION (GLenum matrixMode) {
    MATRIX_OPERATIONS_PREFIX;
    glLoadIdentity();
    MATRIX_OPERATIONS_INFIX;
    glLoadIdentity();
    MATRIX_OPERATIONS_POSTFIX;
}

void glMatrixLoadTransposedEMULATION (GLenum matrixMode, const GLdouble* m) {
    MATRIX_OPERATIONS_PREFIX;
    glLoadTransposeMatrixd( m );
    MATRIX_OPERATIONS_INFIX;
    glLoadTransposeMatrixd( m );
    MATRIX_OPERATIONS_POSTFIX;
}


void glMatrixLoadTransposefEMULATION (GLenum matrixMode, const GLfloat* m) {
    MATRIX_OPERATIONS_PREFIX;
    glLoadTransposeMatrixf( m );
    MATRIX_OPERATIONS_INFIX;
    glLoadTransposeMatrixf( m );
    MATRIX_OPERATIONS_POSTFIX;
}


void glMatrixLoaddEMULATION (GLenum matrixMode, const GLdouble* m) {
    MATRIX_OPERATIONS_PREFIX;
    glLoadMatrixd( m );
    MATRIX_OPERATIONS_INFIX;
    glLoadMatrixd( m );
    MATRIX_OPERATIONS_POSTFIX;
}


void glMatrixLoadfEMULATION (GLenum matrixMode, const GLfloat* m) {
    MATRIX_OPERATIONS_PREFIX;
    glLoadMatrixf( m );
    MATRIX_OPERATIONS_INFIX;
    glLoadMatrixf( m );
    MATRIX_OPERATIONS_POSTFIX;
}


void glMatrixMultTransposedEMULATION (GLenum matrixMode, const GLdouble* m) {
    MATRIX_OPERATIONS_PREFIX;
    glMultTransposeMatrixd( m );
    MATRIX_OPERATIONS_INFIX;
    glMultTransposeMatrixd( m );
    MATRIX_OPERATIONS_POSTFIX;
}


void glMatrixMultTransposefEMULATION (GLenum matrixMode, const GLfloat* m) {
    MATRIX_OPERATIONS_PREFIX;
    glMultTransposeMatrixf( m );
    MATRIX_OPERATIONS_INFIX;
    glMultTransposeMatrixf( m );
    MATRIX_OPERATIONS_POSTFIX;
}


void glMatrixMultdEMULATION (GLenum matrixMode, const GLdouble* m) {
    MATRIX_OPERATIONS_PREFIX;
    glMultMatrixd( m );
    MATRIX_OPERATIONS_INFIX;
    glMultMatrixd( m );
    MATRIX_OPERATIONS_POSTFIX;
}


void glMatrixMultfEMULATION (GLenum matrixMode, const GLfloat* m) {
    MATRIX_OPERATIONS_PREFIX;
    glMultMatrixf( m );
    MATRIX_OPERATIONS_INFIX;
    glMultMatrixf( m );
    MATRIX_OPERATIONS_POSTFIX;
}


void glMatrixOrthoEMULATION (GLenum matrixMode, GLdouble l, GLdouble r, GLdouble b, GLdouble t, GLdouble n, GLdouble f) {
    MATRIX_OPERATIONS_PREFIX;
    glOrtho(l, r, b, t, n, f);
    MATRIX_OPERATIONS_INFIX;
    glOrtho(l, r, b, t, n, f);
    MATRIX_OPERATIONS_POSTFIX;
}


void glMatrixPopEMULATION (GLenum matrixMode) {
    MATRIX_OPERATIONS_PREFIX;
    glPopMatrix();
    MATRIX_OPERATIONS_INFIX;
    glPopMatrix();
    MATRIX_OPERATIONS_POSTFIX;
}


void glMatrixPushEMULATION (GLenum matrixMode) {
    MATRIX_OPERATIONS_PREFIX;
    glPushMatrix();
    MATRIX_OPERATIONS_INFIX;
    glPushMatrix();
    MATRIX_OPERATIONS_POSTFIX;
}

void glMatrixRotatedEMULATION (GLenum matrixMode, GLdouble angle, GLdouble x, GLdouble y, GLdouble z) {
    MATRIX_OPERATIONS_PREFIX;
    glRotated( angle, x, y, z );
    MATRIX_OPERATIONS_INFIX;
    glRotated( angle, x, y, z );
    MATRIX_OPERATIONS_POSTFIX;
}


void glMatrixRotatefEMULATION (GLenum matrixMode, GLfloat angle, GLfloat x, GLfloat y, GLfloat z) {
    MATRIX_OPERATIONS_PREFIX;
    glRotatef( angle, x, y, z );
    MATRIX_OPERATIONS_INFIX;
    glRotatef( angle, x, y, z );
    MATRIX_OPERATIONS_POSTFIX;
}


void glMatrixScaledEMULATION (GLenum matrixMode, GLdouble x, GLdouble y, GLdouble z) {
    MATRIX_OPERATIONS_PREFIX;
    glScaled( x, y, z );
    MATRIX_OPERATIONS_INFIX;
    glScaled( x, y, z );
    MATRIX_OPERATIONS_POSTFIX;
}


void glMatrixScalefEMULATION (GLenum matrixMode, GLfloat x, GLfloat y, GLfloat z) {
    MATRIX_OPERATIONS_PREFIX;
    glScalef( x, y, z );
    MATRIX_OPERATIONS_INFIX;
    glScalef( x, y, z );
    MATRIX_OPERATIONS_POSTFIX;
}


void glMatrixTranslatedEMULATION (GLenum matrixMode, GLdouble x, GLdouble y, GLdouble z) {
    MATRIX_OPERATIONS_PREFIX;
    glTranslated( x, y, z );
    MATRIX_OPERATIONS_INFIX;
    glTranslated( x, y, z );
    MATRIX_OPERATIONS_POSTFIX;
}


void glMatrixTranslatefEMULATION (GLenum matrixMode, GLfloat x, GLfloat y, GLfloat z) {
    MATRIX_OPERATIONS_PREFIX;
    glTranslatef( x, y, z );
    MATRIX_OPERATIONS_INFIX;
    glTranslatef( x, y, z );
    MATRIX_OPERATIONS_POSTFIX;
}

#undef MATRIX_OPERATIONS_PREFIX
#undef MATRIX_OPERATIONS_INFIX
#undef MATRIX_OPERATIONS_POSTFIX

#define MULTI_TEX_PREFIX  GLint savedActiveTexture; \
                          glGetIntegerv(GL_ACTIVE_TEXTURE, &savedActiveTexture); \
                          glActiveTexture(texunit);

#define MULTI_TEX_POSTFIX glActiveTexture(savedActiveTexture); \
                          openGLRareError();

void glMultiTexCoordPointerEMULATION (GLenum texunit, GLint size, GLenum type, GLsizei stride, const void* pointer) {
    MULTI_TEX_PREFIX;
    glTexCoordPointer( size, type, stride, pointer);
    MULTI_TEX_POSTFIX;
}

void glMultiTexEnvfEMULATION (GLenum texunit, GLenum target, GLenum pname, GLfloat param) {
    MULTI_TEX_PREFIX;
    glTexEnvf( target,  pname, param);
    MULTI_TEX_POSTFIX;
}

void glMultiTexEnvfvEMULATION (GLenum texunit, GLenum target, GLenum pname, const GLfloat* params) {
    MULTI_TEX_PREFIX;
    glTexEnvfv( target, pname, params);
    MULTI_TEX_POSTFIX;
}

void glMultiTexEnviEMULATION (GLenum texunit, GLenum target, GLenum pname, GLint param) {
    MULTI_TEX_PREFIX;
    glTexEnvi( target,  pname, param);
    MULTI_TEX_POSTFIX;
}

void glMultiTexEnvivEMULATION (GLenum texunit, GLenum target, GLenum pname, const GLint* params) {
    MULTI_TEX_PREFIX;
    glTexEnviv( target,  pname, params);
    MULTI_TEX_POSTFIX;
}

void glMultiTexGendEMULATION (GLenum texunit, GLenum coord, GLenum pname, GLdouble param) {
    MULTI_TEX_PREFIX;
    glTexGend(  coord,  pname, param);
    MULTI_TEX_POSTFIX;
}

void glMultiTexGendvEMULATION (GLenum texunit, GLenum coord, GLenum pname, const GLdouble* params) {
    MULTI_TEX_PREFIX;
    glTexGendv(  coord, pname, params);
    MULTI_TEX_POSTFIX;
}

void glMultiTexGenfEMULATION (GLenum texunit, GLenum coord, GLenum pname, GLfloat param) {
    MULTI_TEX_PREFIX;
    glTexGenf(  coord,  pname, param);
    MULTI_TEX_POSTFIX;
}

void glMultiTexGenfvEMULATION (GLenum texunit, GLenum coord, GLenum pname, const GLfloat* params) {
    MULTI_TEX_PREFIX;
    glTexGenfv(  coord,  pname, params);
    MULTI_TEX_POSTFIX;
}

void glMultiTexGeniEMULATION (GLenum texunit, GLenum coord, GLenum pname, GLint param) {
    MULTI_TEX_PREFIX;
    glTexGeni(  coord,  pname, param);
    MULTI_TEX_POSTFIX;
}

void glMultiTexGenivEMULATION (GLenum texunit, GLenum coord, GLenum pname, const GLint* params) {
    MULTI_TEX_PREFIX;
    glTexGeniv(  coord,  pname, params);
    MULTI_TEX_POSTFIX;
}
#undef MULTI_TEX_PREFIX
#undef MULTI_TEX_POSTFIX

void glPushClientAttribDefaultEMULATION (GLbitfield mask) {
    glPushClientAttrib( mask );
    glClientAttribDefaultEMULATION( mask );
}

//
// Vertex Arrays:
// the *ClientStatei and *ClientStateIndexed versions do the same, but this seems to be
// correct according to the DSA spec...
//
#define ENABLE_DISABLE_CLIENT_STATE_PREFIX  if (array == GL_TEXTURE_COORD_ARRAY) { \
                                                GLint savedClientActiveTexture; \
                                                glGetIntegerv(GL_CLIENT_ACTIVE_TEXTURE, &savedClientActiveTexture); \
                                                glClientActiveTexture(GL_TEXTURE0 + index);
#define ENABLE_DISABLE_CLIENT_STATE_POSTFIX     glClientActiveTexture(savedClientActiveTexture); \
                                            } else { \
                                                 ACGL::Utils::error() << "GL_INVALID_ENUM in DSA emulation at line: " << __LINE__ << std::endl; \
                                            } \
                                            openGLRareError();

void glEnableClientStateIndexedEMULATION (GLenum array, GLuint index) {
    ENABLE_DISABLE_CLIENT_STATE_PREFIX;
    glEnableClientState(array);
    ENABLE_DISABLE_CLIENT_STATE_POSTFIX;
}

void glDisableClientStateIndexedEMULATION (GLenum array, GLuint index) {
    ENABLE_DISABLE_CLIENT_STATE_PREFIX;
    glDisableClientState(array);
    ENABLE_DISABLE_CLIENT_STATE_POSTFIX;
}

void glEnableClientStateiEMULATION (GLenum array, GLuint index) {
    ENABLE_DISABLE_CLIENT_STATE_PREFIX;
    glEnableClientState(array);
    ENABLE_DISABLE_CLIENT_STATE_POSTFIX;
}

void glDisableClientStateiEMULATION (GLenum array, GLuint index) {
    ENABLE_DISABLE_CLIENT_STATE_PREFIX;
    glDisableClientState(array);
    ENABLE_DISABLE_CLIENT_STATE_POSTFIX;
}

#undef ENABLE_DISABLE_CLIENT_STATE_PREFIX
#undef ENABLE_DISABLE_CLIENT_STATE_POSTFIX
#endif

} // OpenGL
} // ACGL


#if (((__GNUC__ == 4) && (__GNUC_MINOR__ >= 6)) || (__GNUC__ > 4))
#   pragma GCC diagnostic pop
#endif

