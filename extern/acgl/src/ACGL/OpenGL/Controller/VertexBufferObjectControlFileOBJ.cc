////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2011, Computer Graphics Group RWTH Aachen University         //
// All rights reserved.                                                       //
////////////////////////////////////////////////////////////////////////////////

#include <ACGL/OpenGL/Controller/VertexBufferObjectControlFileOBJ.hh>
#include <ACGL/OpenGL/Controller/ArrayBufferControl.hh>
#include <ACGL/OpenGL/Controller/ElementArrayBufferControl.hh>
#include <ACGL/OpenGL/Controller/VertexBufferObjectControl.hh>
#include <ACGL/Base/StringOperations.hh>

#include <vector>
#include <iostream>
#include <fstream>

using namespace ACGL;
using namespace ACGL::Base;
using namespace ACGL::Utils;
using namespace ACGL::OpenGL;

SharedVertexBufferObject VertexBufferObjectControlFileOBJ::create(void)
{
    updateFileModificationTime();

    mElementArrayBuffer = ElementArrayBufferControl().
        mode(GL_TRIANGLES).
        usage(GL_STATIC_DRAW).
        create();
    mArrayBuffer = ArrayBufferControl().
        mode(GL_TRIANGLES).
        usage(GL_STATIC_DRAW).
        create();
    SharedVertexBufferObject vertexBuffer = VertexBufferObjectControl().
        index(mElementArrayBuffer).
        data(mArrayBuffer).
        create();

    if(loadOBJ(vertexBuffer))
        return vertexBuffer;

    return SharedVertexBufferObject();
}

bool VertexBufferObjectControlFileOBJ::update(SharedVertexBufferObject& _vertexBuffer)
{
    if(fileIsUpToDate())
        return false;

    if(!loadOBJ(_vertexBuffer))
        return false;

    updateFileModificationTime();
    return true;
}

bool VertexBufferObjectControlFileOBJ::loadOBJ(SharedVertexBufferObject& _vertexBuffer)
{
    std::string full = getFullFilePath();

    std::string line = "";

    std::ifstream fileStream(full.c_str(), std::ifstream::in);

    std::vector<GLfloat> sharedVertexVector;
    std::vector<GLfloat> sharedTexCoordVector;
    std::vector<GLfloat> sharedNormalVector;
    uint_t texCoordElements = 0;
    uint_t texCoordDimension = 0;

    sharedVertexVector.resize(4);
    sharedNormalVector.resize(3);

    bool elementOK = true;
    bool lineOK = true;

    uint_t lineNumber = 0;

    if(fileStream.is_open())
    {
        //Read the first line
        if(fileStream.good())
            std::getline(fileStream, line);

        while(fileStream.good())
        {
            if(StringOperations::startsWith(line, "vt"))
            {
                std::vector<std::string> elements = StringOperations::split(line, ' ');
                //The first occurence of vt gives us the number of texture coordinates per vertex.
                if(texCoordElements == 0)
                {
                    texCoordElements = elements.size();
                    texCoordDimension = texCoordElements - 1;
                    sharedTexCoordVector.resize(texCoordDimension);
                }
                if((uint_t)elements.size() == texCoordElements)
                {
                    for(uint_t i = 1; i < texCoordElements; ++i)
                        sharedTexCoordVector.push_back(StringOperations::to<GLfloat>(elements[i], &elementOK));
                }
                else
                {
                    //If a later texture coordinate is defined wrong, we enter zeros, because
                    //otherwise the indices would be intermixed.
                    for(uint_t i = 1; i < texCoordElements; ++i)
                        sharedTexCoordVector.push_back(0.0f);
                    lineOK = false;
                }
            }
            else if(StringOperations::startsWith(line, "vn"))
            {
                std::vector<std::string> elements = StringOperations::split(line, ' ');
                if(elements.size() == 4)
                {
                    sharedNormalVector.push_back(StringOperations::to<GLfloat>(elements[1], &elementOK));
                    sharedNormalVector.push_back(StringOperations::to<GLfloat>(elements[2], &elementOK));
                    sharedNormalVector.push_back(StringOperations::to<GLfloat>(elements[3], &elementOK));
                }
                else
                {
                    //If a later texture coordinate is defined wrong, we enter zeros, because
                    //otherwise the indices would be intermixed.
                    sharedNormalVector.push_back(0.0f);
                    sharedNormalVector.push_back(0.0f);
                    sharedNormalVector.push_back(0.0f);
                    lineOK = false;
                }
            }
            else if(StringOperations::startsWith(line, "v"))
            {
                std::vector<std::string> elements = StringOperations::split(line, ' ');
                if(elements.size() == 4)
                {
                    sharedVertexVector.push_back(StringOperations::to<GLfloat>(elements[1], &elementOK));
                    sharedVertexVector.push_back(StringOperations::to<GLfloat>(elements[2], &elementOK));
                    sharedVertexVector.push_back(StringOperations::to<GLfloat>(elements[3], &elementOK));
                    sharedVertexVector.push_back(1.0f);
                }
                else
                {
                    lineOK = false;
                }
            }
            else if(StringOperations::startsWith(line, "f"))
            {
                //As soon as the first f occurs, we assume that all vertex
                //positions, normals and tex coords have been defined!
                break;
            }

            if(!lineOK)
            {
                warning() << "Format of line " << lineNumber << " is wrong!" << std::endl;
                debug() << line << std::endl;
                lineOK = true;
            }
            if(!elementOK)
            {
                warning() << "Element in line " << lineNumber << " is wrong!" << std::endl;
                debug() << line << std::endl;
                elementOK = true;
            }
            ++lineNumber;
            getline(fileStream, line);

        }

        bool hasNormals = sharedNormalVector.size() != 3;
        if(!hasNormals) {
            message() << "The file " << full << " has no normals!" << std::endl;
        }

        //By default the number of attributes is 1 (only vertices)
        uint_t attributes = 1;
        //Then we check for other attributes like normals...
        if(hasNormals)
            attributes++;
        //...or tex coords
        if(texCoordDimension > 0)
            attributes++;

        //By default components is the size of 3, because vertices have 3 components (x,y,z)
        uint_t components = 3;
        //If there are normals we have to add another 3 elements
        if(hasNormals)
            components += 3;
        //We then add the number of tex coord components. This number is 0, if there are none
        components += texCoordDimension;

        std::vector<GLfloat> interleavedDataVector;
        typedef GLuint IndexType;
        GLenum indexType = GL_UNSIGNED_INT;
        std::vector<IndexType> indexVector;

        uint_t index = 0;
        while(fileStream.good())
        {
            if(StringOperations::startsWith(line, "f"))
            {
                std::vector<std::string> elements = StringOperations::split(line, ' ');
                uint_t uiPolygonSize = elements.size() - 1;
                if(uiPolygonSize > 2)
                {
                    for(size_t i = 1; i < elements.size(); ++i)
                    {
                        if(i > 3)
                        {
                            //If we have more than 3 vertices, we have to triangulate in a simple way.
                            //E.g. for a quad 1234 we should get 123 134.
                            indexVector.push_back(index - i + 1);
                            indexVector.push_back(index - 1);
                        }
                        indexVector.push_back(index++);
                        std::vector<std::string> indices = StringOperations::split(elements[i], '/', false);
                        if(indices.size() == 3 && hasNormals && texCoordDimension > 0)
                        {
                            uint_t sharedIndex = StringOperations::to<IndexType>(indices[0], &elementOK);
                            interleavedDataVector.push_back(sharedVertexVector[4 * sharedIndex]);
                            interleavedDataVector.push_back(sharedVertexVector[4 * sharedIndex + 1]);
                            interleavedDataVector.push_back(sharedVertexVector[4 * sharedIndex + 2]);
                            interleavedDataVector.push_back(sharedVertexVector[4 * sharedIndex + 3]);
                            sharedIndex = StringOperations::to<IndexType>(indices[2], &elementOK);
                            interleavedDataVector.push_back(sharedNormalVector[3 * sharedIndex]);
                            interleavedDataVector.push_back(sharedNormalVector[3 * sharedIndex + 1]);
                            interleavedDataVector.push_back(sharedNormalVector[3 * sharedIndex + 2]);
                            sharedIndex = StringOperations::to<IndexType>(indices[1], &elementOK);
                            for(uint_t i = 0; i < texCoordDimension; ++i)
                                interleavedDataVector.push_back(sharedTexCoordVector[texCoordDimension * sharedIndex + i]);
                        }
                        else if(indices.size() == 3 && hasNormals)
                        {
                            uint_t sharedIndex = StringOperations::to<IndexType>(indices[0], &elementOK);
                            interleavedDataVector.push_back(sharedVertexVector[4 * sharedIndex]);
                            interleavedDataVector.push_back(sharedVertexVector[4 * sharedIndex + 1]);
                            interleavedDataVector.push_back(sharedVertexVector[4 * sharedIndex + 2]);
                            interleavedDataVector.push_back(sharedVertexVector[4 * sharedIndex + 3]);
                            sharedIndex = StringOperations::to<IndexType>(indices[2], &elementOK);
                            interleavedDataVector.push_back(sharedNormalVector[3 * sharedIndex]);
                            interleavedDataVector.push_back(sharedNormalVector[3 * sharedIndex + 1]);
                            interleavedDataVector.push_back(sharedNormalVector[3 * sharedIndex + 2]);
                        }
                        else if(indices.size() == 2 && texCoordDimension > 0)
                        {
                            uint_t sharedIndex = StringOperations::to<IndexType>(indices[0], &elementOK);
                            interleavedDataVector.push_back(sharedVertexVector[4 * sharedIndex]);
                            interleavedDataVector.push_back(sharedVertexVector[4 * sharedIndex + 1]);
                            interleavedDataVector.push_back(sharedVertexVector[4 * sharedIndex + 2]);
                            interleavedDataVector.push_back(sharedVertexVector[4 * sharedIndex + 3]);
                            sharedIndex = StringOperations::to<IndexType>(indices[1], &elementOK);
                            for(uint_t i = 0; i < texCoordDimension; ++i)
                                interleavedDataVector.push_back(sharedTexCoordVector[texCoordDimension * sharedIndex + i]);
                        }
                        else if(indices.size() == 1)
                        {
                            uint_t sharedIndex = StringOperations::to<IndexType>(indices[0], &elementOK);
                            interleavedDataVector.push_back(sharedVertexVector[4 * sharedIndex]);
                            interleavedDataVector.push_back(sharedVertexVector[4 * sharedIndex + 1]);
                            interleavedDataVector.push_back(sharedVertexVector[4 * sharedIndex + 2]);
                            interleavedDataVector.push_back(sharedVertexVector[4 * sharedIndex + 3]);
                        }
                        else
                        {
                            for(uint_t j = 0; j < components; ++j)
                                interleavedDataVector.push_back(0.0f);
                            lineOK = false;
                        }
                    }
                }
                else
                {
                    lineOK = false;
                }
            }

            if(!lineOK)
            {
                warning() << "Format of line " << lineNumber << " is wrong!" << std::endl;
                debug() << line << std::endl;
                lineOK = true;
            }
            if(!elementOK)
            {
                warning() << "Element in line " << lineNumber << " is wrong!" << std::endl;
                debug() << line << std::endl;
                elementOK = true;
            }
            ++lineNumber;
            getline(fileStream, line);
        }

        fileStream.close();

        mArrayBuffer->removeAttributes();
        _vertexBuffer->removeAttributes();

#if (ACGL_OPENGL_VERSION >= 30)
        GLint shaderIndexPosition = (mpShaderProgram) ? mpShaderProgram->getAttributeLocation("aPosition") : 0;
        GLint shaderIndexNormal   = (mpShaderProgram) ? mpShaderProgram->getAttributeLocation("aNormal")   : 1;
        GLint shaderIndexTexCoord = (mpShaderProgram) ? mpShaderProgram->getAttributeLocation("aTexCoord") : ((hasNormals) ? 2 : 1);
#else
        GLint shaderIndexPosition = 0;
        GLint shaderIndexNormal   = 1;
        GLint shaderIndexTexCoord = ((hasNormals) ? 2 : 1);
#endif
        mArrayBuffer->attachAttribute("aPosition", GL_FLOAT, 4, GL_FALSE);
        _vertexBuffer->attachAttribute("aPosition", 0, "aPosition", shaderIndexPosition);
        if(hasNormals)
        {
            mArrayBuffer->attachAttribute("aNormal", GL_FLOAT, 3, GL_FALSE);
            _vertexBuffer->attachAttribute("aNormal", 0, "aNormal", shaderIndexNormal);
        }
        if(texCoordDimension > 0)
        {
            mArrayBuffer->attachAttribute("aTexCoord", GL_FLOAT, texCoordDimension, GL_FALSE);
            _vertexBuffer->attachAttribute("aTexCoord", 0, "aTexCoord", shaderIndexTexCoord);
        }

        mElementArrayBuffer->setType(indexType);
        mElementArrayBuffer->bind();
        mElementArrayBuffer->setData(&indexVector[0], indexVector.size());

        mArrayBuffer->bind();
        mArrayBuffer->setData(&interleavedDataVector[0], index);

        return true;
    }

    error() << "Failed to open file: " << getFullFilePath() << std::endl;
    return false;
}
