////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2011, Computer Graphics Group RWTH Aachen University         //
// All rights reserved.                                                       //
////////////////////////////////////////////////////////////////////////////////

#include <ACGL/OpenGL/Controller/ShaderControlFile.hh>
#include <ACGL/Base/StringOperations.hh>

using namespace ACGL::Base;
using namespace ACGL::OpenGL;

SharedShader ShaderControlFile::create(void)
{
    updateFileModificationTime();

    if(mType == GL_INVALID_ENUM)
    {
        std::string filename;
        std::string extension;
        if(!StringOperations::splitFileExtension(mFilename, filename, extension))
            return SharedShader();

        if(extension == "vsh")
            mType = GL_VERTEX_SHADER;
        else if(extension == "tcsh")
            mType = GL_TESS_CONTROL_SHADER;
        else if(extension == "tesh")
            mType = GL_TESS_EVALUATION_SHADER;
        else if(extension == "gsh")
            mType = GL_GEOMETRY_SHADER;
        else if(extension == "fsh")
            mType = GL_FRAGMENT_SHADER;
        else
            return SharedShader();
    }

    SharedShader shader(new Shader(mType));
    if(shader->setFromFile(mFullFilePath))
        return shader;
    return SharedShader();
}

bool ShaderControlFile::update(SharedShader& shader)
{
    if(fileIsUpToDate())
        return false;

    if(!shader->setFromFile(mFullFilePath))
        return false;

    updateFileModificationTime();
    return true;
}
