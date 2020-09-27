////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2011, Computer Graphics Group RWTH Aachen University         //
// All rights reserved.                                                       //
////////////////////////////////////////////////////////////////////////////////

#ifndef ACGL_BASE_SINGLETON_HH
#define ACGL_BASE_SINGLETON_HH

/*
 * A very simple Singleton as a template.
 * Not thread save etc.
 */

#include <ACGL/ACGL.hh>
#include <tr1/memory>

namespace ACGL{
namespace Base{

template<typename CLASS>
class Singleton
{
public:
    virtual ~Singleton(void) {}
    
    static std::tr1::shared_ptr<CLASS> the(void)
    {
        if(!spInstance)
            spInstance.reset(new CLASS());
        return(spInstance);
    }
    
protected:
    Singleton(void){}
private:
    Singleton(const Singleton&){}
    
private:
    static std::tr1::shared_ptr<CLASS> spInstance;
    
};

template<typename CLASS>
std::tr1::shared_ptr<CLASS> Singleton<CLASS>::spInstance = std::tr1::shared_ptr<CLASS>();

#define ACGL_SINGLETON(Class) \
friend class Base::Singleton< Class >; \
private:\
    Class(const Class& ){ }\
    void operator=(Class& ){ }

} // Base
} // ACGL

#endif
