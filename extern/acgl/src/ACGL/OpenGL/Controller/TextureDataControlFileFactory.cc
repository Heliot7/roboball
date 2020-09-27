////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2011, Computer Graphics Group RWTH Aachen University         //
// All rights reserved.                                                       //
////////////////////////////////////////////////////////////////////////////////

#include <ACGL/OpenGL/Controller/TextureDataControlFileFactory.hh>
#include <ACGL/Base/StringOperations.hh>

using namespace ACGL;
using namespace ACGL::OpenGL;
using namespace ACGL::Base::StringOperations;

int_t TextureDataControlFileFactory::registerType(const std::string& _type, factoryCreate _creator)
{
    ACGL::Utils::debug() << "TextureDataControlFileFactory register type: " << _type << std::endl;
    mFactoryMap[_type] = _creator;
    return mRegisteredTypes++;
}

SharedTextureDataControlFile TextureDataControlFileFactory::create(const std::string& _filename) const
{
    std::string file;
    std::string extension;
    splitFileExtension(_filename, file, extension);
    FactoryMap::const_iterator existingCreator = mFactoryMap.find(extension);
    if(existingCreator != mFactoryMap.end())
        return existingCreator->second(_filename);
    return SharedTextureDataControlFile();
}
