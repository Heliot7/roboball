////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2011, Computer Graphics Group RWTH Aachen University         //
// All rights reserved.                                                       //
////////////////////////////////////////////////////////////////////////////////

#ifndef ACGL_RESOURCE_FILEMANAGER_HH
#define ACGL_RESOURCE_FILEMANAGER_HH

#include <ACGL/ACGL.hh>
#include <ACGL/Base/Singleton.hh>
#include <ACGL/Base/Macros.hh>
#include <ACGL/Resource/FileController.hh>

#include <tr1/memory>
#include <map>
#include <string>

namespace ACGL{
namespace Resource{

template<typename RESOURCE>
class FileManager : public Base::Singleton< FileManager<RESOURCE> >
{
    ACGL_SINGLETON(FileManager<RESOURCE>)
    
public:
    typedef std::tr1::shared_ptr< FileController<RESOURCE> > SharedController;
    ACGL_SHARED_TYPEDEF(RESOURCE)
    struct Resource
    {
        SharedController controller;
        SharedRESOURCE resource;
    };

    typedef std::map<std::string, Resource> ResourceMap;
    typedef ResourceMap ResourceContainer;
    
    virtual ~FileManager(void) {}

    template<typename CONTROLLER>
    ConstSharedRESOURCE get(const CONTROLLER& _controller);
    ConstSharedRESOURCE query(const std::string& _filename);
    bool exists(const std::string& _key);
    bool erase(const std::string& key);
    void eraseAll(void);
    bool update(const std::string& key);
    void updateAll(void);

    typename ResourceMap::const_iterator begin(void) const { return mResourceMap.begin(); }
    typename ResourceMap::const_iterator end(void) const { return mResourceMap.end(); }
    
protected:
    FileManager(void)
    :   mResourceMap()
    {}
    
private:
    ResourceMap mResourceMap;
};

template<typename RESOURCE> template<typename CONTROLLER>
typename FileManager<RESOURCE>::ConstSharedRESOURCE FileManager<RESOURCE>::get(const CONTROLLER& _controller)
{
    typename ResourceMap::iterator existingResource = mResourceMap.find(_controller.getFilename());
    if(existingResource != mResourceMap.end())
        return existingResource->second.resource;

    SharedController pController(new CONTROLLER(_controller));
    SharedRESOURCE pResource = pController->create();
    if(pResource)
    {
        Resource resource = { pController, pResource };
        mResourceMap[_controller.getFilename()] = resource;
        Utils::debug() << "FileManager::getResource: Resource loaded: " << _controller.getFilename() << std::endl;
        return pResource;
    }
    else
    {
        Utils::error() << "FileManager::getResource: Resource could not be loaded: " << _controller.getFilename() << std::endl;
    }
    return SharedRESOURCE();
}

template<typename RESOURCE>
typename FileManager<RESOURCE>::ConstSharedRESOURCE FileManager<RESOURCE>::query(const std::string& _key)
{
    typename ResourceMap::iterator existingResource = mResourceMap.find(_key);
    if(existingResource != mResourceMap.end())
        return existingResource->second.resource;
    return ConstSharedRESOURCE();
}

template<typename RESOURCE>
bool FileManager<RESOURCE>::exists(const std::string& _key)
{
    typename ResourceMap::iterator existingResource = mResourceMap.find(_key);
    if(existingResource != mResourceMap.end())
        return true;
    return false;
}

template<typename RESOURCE>
bool FileManager<RESOURCE>::erase(const std::string& _key)
{
    typename ResourceMap::iterator existingResource = mResourceMap.find(_key);
    if(existingResource != mResourceMap.end())
    {
        mResourceMap.erase(existingResource);
        Utils::debug() << "FileManager::Resource deleted: " << _key << std::endl;
        return true;
    }
    Utils::warning() << "FileManager::Resource not found for deletion! " << std::endl;
    return false;
}

template<typename RESOURCE>
void FileManager<RESOURCE>::eraseAll(void)
{
    mResourceMap.clear();
}

template<typename RESOURCE>
bool FileManager<RESOURCE>::update(const std::string& _key)
{
    typename ResourceMap::iterator existingResource = mResourceMap.find(_key);
    if(existingResource != mResourceMap.end())
        return existingResource->second.controller->update(existingResource->second.resource);
    return false;
}

template<typename RESOURCE>
void FileManager<RESOURCE>::updateAll(void)
{
    for(typename ResourceMap::iterator i = mResourceMap.begin();
        i != mResourceMap.end();
        ++i)
        i->second.controller->update(i->second.resource);
}

} // Resource
} // ACGL

#endif // ACGL_RESOURCE_NAMEMANAGER_HH
