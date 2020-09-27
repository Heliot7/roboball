////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2011, Computer Graphics Group RWTH Aachen University         //
// All rights reserved.                                                       //
////////////////////////////////////////////////////////////////////////////////

#include <ACGL/OpenGL/Controller/ArrayBufferControlFileATB.hh>
#include <ACGL/OpenGL/Controller/ArrayBufferControl.hh>
#include <ACGL/OpenGL/Controller/ElementArrayBufferControl.hh>
#include <ACGL/OpenGL/Controller/ArrayBufferControl.hh>
#include <ACGL/Base/StringOperations.hh>

#include <vector>
#include <iostream>
#include <fstream>

using namespace ACGL;
using namespace ACGL::Base;
using namespace ACGL::Utils;
using namespace ACGL::OpenGL;

SharedArrayBuffer ArrayBufferControlFileATB::create(void)
{
    updateFileModificationTime();

    SharedArrayBuffer arrayBuffer = ArrayBufferControl().
            mode(GL_TRIANGLES).
            usage(GL_STATIC_DRAW).
            create();

    if(loadATB(arrayBuffer))
        return arrayBuffer;

    return SharedArrayBuffer();
}

bool ArrayBufferControlFileATB::update(SharedArrayBuffer& _arrayBuffer)
{
    if(fileIsUpToDate())
        return false;

    if(!loadATB(_arrayBuffer))
        return false;

    updateFileModificationTime();
    return true;
}

bool ArrayBufferControlFileATB::loadATB(SharedArrayBuffer& _arrayBuffer)
{
    std::string full = getFullFilePath();

    std::string line = "";

    std::ifstream fileStream(full.c_str(), std::ifstream::in);

    std::vector<GLfloat> sharedAttributeVector;
    uint_t attributeElements = 0;
    uint_t attributeDimension = 0;

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
            if(StringOperations::startsWith(line, "a"))
            {
                std::vector<std::string> elements = StringOperations::split(line, ' ');
                //The first occurence of vt gives us the number of texture coordinates per vertex.
                if(attributeElements == 0)
                {
                    attributeElements = elements.size();
                    attributeDimension = attributeElements - 1;
                    sharedAttributeVector.resize(attributeDimension);
                }
                if((uint_t)elements.size() == attributeElements)
                {
                    for(uint_t i = 1; i < attributeElements; ++i)
                        sharedAttributeVector.push_back(StringOperations::to<GLfloat>(elements[i], &elementOK));
                }
                else
                {
                    //If a later texture coordinate is defined wrong, we enter zeros, because
                    //otherwise the indices would be intermixed.
                    for(uint_t i = 1; i < attributeElements; ++i)
                        sharedAttributeVector.push_back(0.0f);
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

        std::vector<GLfloat> dataVector;

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
                        index++;
                        uint_t sharedIndex = StringOperations::to<uint_t>(elements[i], &elementOK);
                        for(uint_t i = 0; i < attributeDimension; ++i)
                            dataVector.push_back(sharedAttributeVector[attributeDimension * sharedIndex + i]);
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

        _arrayBuffer->removeAttributes();
        _arrayBuffer->attachAttribute("aAttribute", GL_FLOAT, attributeDimension, GL_FALSE);
        _arrayBuffer->bind();
        _arrayBuffer->setData(&dataVector[0], index);

        return true;
    }

    error() << "Failed to open file: " << getFullFilePath() << std::endl;
    return false;
}
