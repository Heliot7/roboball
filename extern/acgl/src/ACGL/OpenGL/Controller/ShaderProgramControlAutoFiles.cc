////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2011, Computer Graphics Group RWTH Aachen University         //
// All rights reserved.                                                       //
////////////////////////////////////////////////////////////////////////////////

#include <ACGL/OpenGL/Controller/ShaderProgramControlAutoFiles.hh>
#include <ACGL/OpenGL/Controller/ShaderControlFile.hh>
#include <ACGL/Resource/FileManager.hh>
#include <ACGL/OpenGL/Managers.hh>
#include <ACGL/Base/Settings.hh>
#include <ACGL/Base/FileHelpers.hh>

using namespace ACGL::Base;
using namespace ACGL::OpenGL;

SharedShaderProgram ShaderProgramControlAutoFiles::create(void)
{
    SharedShaderProgram shaderProgram(new ShaderProgram());
    if(ConstSharedShader shader = ShaderFileManager::the()->get(ShaderControlFile(mFilename + ".vsh").type(GL_VERTEX_SHADER)))
        shaderProgram->attachShader(shader);

    #ifndef ACGL_OPENGL_ES
        // this shader types are not defined for ES

        bool tessellationControlShaderPresent    = FileHelpers::fileExists(Base::Settings::the()->getFullShaderPath() + mFilename + ".tcsh");
        bool tessellationEvaluationShaderPresent = FileHelpers::fileExists(Base::Settings::the()->getFullShaderPath() + mFilename + ".tesh");

        if (OpenGL::doesSupportTessellationShader()) {
            if(tessellationControlShaderPresent && tessellationEvaluationShaderPresent) {
                // both tessellation stages are present -> load them
                if(ConstSharedShader shader = ShaderFileManager::the()->get(ShaderControlFile(mFilename + ".tcsh").type(GL_TESS_CONTROL_SHADER)))
                    shaderProgram->attachShader(shader);

                if(ConstSharedShader shader = ShaderFileManager::the()->get(ShaderControlFile(mFilename + ".tesh").type(GL_TESS_EVALUATION_SHADER)))
                    shaderProgram->attachShader(shader);
            } else {
                if (tessellationControlShaderPresent || tessellationEvaluationShaderPresent) {
                    // only ONE tessellation stage is present -> somethings wrong
                    ACGL::Utils::warning() << "only one of two tessellation shaders are present - ignored" << std::endl;
                }
            }
        } else if (tessellationControlShaderPresent || tessellationEvaluationShaderPresent) {
            ACGL::Utils::warning() << "tessellation shader present but hardware doesn't support those - ignored" << std::endl;
        }

        bool geometryShaderPresent = FileHelpers::fileExists(Base::Settings::the()->getFullShaderPath() + mFilename + ".gsh");
        if (OpenGL::doesSupportGeometryShader()) {
            if(geometryShaderPresent)
                if(ConstSharedShader shader = ShaderFileManager::the()->get(ShaderControlFile(mFilename + ".gsh").type(GL_GEOMETRY_SHADER)))
                    shaderProgram->attachShader(shader);
        } else if (geometryShaderPresent) {
            ACGL::Utils::warning() << "geometry shader present but hardware doesn't support it - ignored" << std::endl;
        }
    #endif

    if(ConstSharedShader shader = ShaderFileManager::the()->get(ShaderControlFile(mFilename + ".fsh").type(GL_FRAGMENT_SHADER)))
        shaderProgram->attachShader(shader);

#if (ACGL_OPENGL_VERSION >= 30)
    for (std::vector<std::string>::size_type i = 0; i < mAttributeLocations.size(); ++i)
        shaderProgram->bindAttributeLocation(mAttributeLocations[i], i);
    for (std::vector<std::string>::size_type i = 0; i < mFragmentDataLocations.size(); ++i)
        shaderProgram->bindFragmentDataLocation(mFragmentDataLocations[i], i);
#endif

    if(shaderProgram->link())
        return shaderProgram;

    return SharedShaderProgram();
}

bool ShaderProgramControlAutoFiles::update(SharedShaderProgram& shaderProgram)
{
    bool update = false;
    update |= ShaderFileManager::the()->update(mFilename + ".vsh");
    update |= ShaderFileManager::the()->update(mFilename + ".fsh");
    #ifndef ACGL_OPENGL_ES
        if (OpenGL::doesSupportGeometryShader()) {
            update |= ShaderFileManager::the()->update(mFilename + ".gsh");
        }
        if (OpenGL::doesSupportTessellationShader()) {
            update |= ShaderFileManager::the()->update(mFilename + ".tcsh");
            update |= ShaderFileManager::the()->update(mFilename + ".tesh");
        }
    #endif

    if(update)
        return shaderProgram->link();
    return false;
}
