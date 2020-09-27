////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2011, Computer Graphics Group RWTH Aachen University         //
// All rights reserved.                                                       //
////////////////////////////////////////////////////////////////////////////////

#ifndef ACGL_OPENGL_CONTROLLER_TEXTUREDATACONTROLFILEFACTORY_HH
#define ACGL_OPENGL_CONTROLLER_TEXTUREDATACONTROLFILEFACTORY_HH

#include <ACGL/ACGL.hh>

#include <ACGL/Base/Singleton.hh>
#include <ACGL/OpenGL/Controller/TextureDataControlFile.hh>

#include <map>
#include <string>

namespace ACGL{
namespace OpenGL{

class TextureDataControlFileFactory : public Base::Singleton< TextureDataControlFileFactory >
{
    ACGL_SINGLETON(TextureDataControlFileFactory)

    // ========================================================================================================= \/
    // ================================================================================================ TYPEDEFS \/
    // ========================================================================================================= \/
private:
    typedef SharedTextureDataControlFile (*factoryCreate)(const std::string&);
    typedef std::map<std::string, factoryCreate> FactoryMap;

    // ========================================================================================================= \/
    // ============================================================================================ CONSTRUCTORS \/
    // ========================================================================================================= \/
protected:
    TextureDataControlFileFactory(void) : mRegisteredTypes(0), mFactoryMap() {}

public:
    virtual ~TextureDataControlFileFactory(void) {}

    // ========================================================================================================= \/
    // ================================================================================================= METHODS \/
    // ========================================================================================================= \/
public:
    int_t getRegisteredTypes(void) const { return mRegisteredTypes; }
    int_t registerType(const std::string& _type, factoryCreate _creator);
    SharedTextureDataControlFile create(const std::string& _filename) const;

    // ========================================================================================================= \/
    // ================================================================================================== FIELDS \/
    // ========================================================================================================= \/
private:
    int_t mRegisteredTypes;
    FactoryMap mFactoryMap;
};

} // OpenGL
} // ACGL

#endif // ACGL_OPENGL_CONTROLLER_TEXTUREDATACONTROLFILEFACTORY_HH
