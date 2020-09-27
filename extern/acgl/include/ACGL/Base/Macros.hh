////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2011, Computer Graphics Group RWTH Aachen University         //
// All rights reserved.                                                       //
////////////////////////////////////////////////////////////////////////////////

#ifndef ACGL_BASE_MACROS_HH
#define ACGL_BASE_MACROS_HH

//Macro to make a class not copyable
#define ACGL_NOT_COPYABLE(Class) \
private:\
    Class(const Class& ){ }\
    void operator=(Class& ){ }

#define ACGL_SHARED_TYPEDEF(Class) \
    typedef std::tr1::shared_ptr<Class> Shared ## Class; \
    typedef std::tr1::shared_ptr<const Class> ConstShared ## Class; \
    typedef std::tr1::weak_ptr<Class> Weak ## Class; \
    typedef std::tr1::weak_ptr<const Class> ConstWeak ## Class;


#endif // MACROS_HH
