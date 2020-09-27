////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2011, Computer Graphics Group RWTH Aachen University         //
// All rights reserved.                                                       //
////////////////////////////////////////////////////////////////////////////////

#ifndef ACGL_RESOURCE_NAMEMANAGER_HH
#define ACGL_RESOURCE_NAMEMANAGER_HH

#include <ACGL/ACGL.hh>
#include <ACGL/Base/Singleton.hh>
#include <ACGL/Resource/BasicCreateController.hh>

#include <tr1/memory>
#include <map>
#include <string>

namespace ACGL{
namespace Resource{

template<typename RESOURCE>
class NameManager : public Base::Singleton< NameManager<RESOURCE> >
{
    friend class Base::Singleton< NameManager<RESOURCE> >;
    
public:
    typedef std::tr1::shared_ptr<RESOURCE> SharedResource;
    typedef std::map<std::string, SharedResource> ResourceMap;
    typedef ResourceMap ResourceContainer;
    
    virtual ~NameManager(void) {}

    SharedResource get(const std::string& _key, BasicCreateController<RESOURCE>& _controller);
    SharedResource query(const std::string& _key);
    bool exists(const std::string& _key);
    bool deleteResource(const std::string& key);
    void clearAllResources(void);

    typename ResourceMap::const_iterator begin(void) const { return mResourceMap.begin(); }
    typename ResourceMap::const_iterator end(void) const { return mResourceMap.end(); }
    
protected:
    NameManager(void)
    :   mResourceMap()
    {}
private:
    NameManager(const NameManager&) {}
    
private:
    ResourceMap mResourceMap;
};

template<typename RESOURCE>
typename NameManager<RESOURCE>::SharedResource NameManager<RESOURCE>::get(const std::string& _key, BasicCreateController<RESOURCE>& _controller)
{
    typename ResourceMap::iterator existingResource = mResourceMap.find(_key);
    if(existingResource != mResourceMap.end())
        return existingResource->second;

    SharedResource pResource = _controller.create();
    if(pResource)
    {
        mResourceMap[_key] = pResource;
        Utils::debug() << "NameManager::getResource: Resource loaded: " << _key << std::endl;
        return pResource;
    }
    else
    {
        Utils::warning() << "NameManager::getResource: Resource could not be loaded: " << _key << std::endl;
    }
    return SharedResource();
}

template<typename RESOURCE>
typename NameManager<RESOURCE>::SharedResource NameManager<RESOURCE>::query(const std::string& _key)
{
    typename ResourceMap::iterator existingResource = mResourceMap.find(_key);
    if(existingResource != mResourceMap.end())
        return existingResource->second;
    return SharedResource();
}

template<typename RESOURCE>
bool NameManager<RESOURCE>::exists(const std::string& _key)
{
    typename ResourceMap::iterator existingResource = mResourceMap.find(_key);
    if(existingResource != mResourceMap.end())
        return true;
    return false;
}

template<typename RESOURCE>
bool NameManager<RESOURCE>::deleteResource(const std::string& _key)
{
    typename ResourceMap::iterator existingResource = mResourceMap.find(_key);
    if(existingResource != mResourceMap.end())
    {
        mResourceMap.erase(existingResource);
        Utils::debug() << "NameManager::Resource deleted: " << _key << std::endl;
        return true;
    }
    Utils::warning() << "NameManager::Resource not found for deletion! " << std::endl;
    return false;
}

template<typename RESOURCE>
void NameManager<RESOURCE>::clearAllResources(void)
{
    mResourceMap.clear();
}

} // Resource
} // ACGL

#endif // ACGL_RESOURCE_NAMEMANAGER_HH
