////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2011, Computer Graphics Group RWTH Aachen University         //
// All rights reserved.                                                       //
////////////////////////////////////////////////////////////////////////////////

#ifndef ACGL_BASE_STRINGOPERATIONS_HH
#define ACGL_BASE_STRINGOPERATIONS_HH

/*
 * Provides a set of primitive functions which operate on std::strings which are
 * used at multiple points within the library.
 */

#include <ACGL/ACGL.hh>

#include <sstream>
#include <vector>
#include <string>

namespace ACGL{
namespace Base{

namespace StringOperations
{
    bool splitFileExtension    (const std::string& _full, std::string& _file, std::string& _extension   );
    bool splitLastFileOrFolder (const std::string& _full, std::string& _path, std::string& _fileOrFolder);
    bool startsWith            (const std::string& _string, const std::string& _prefix);
    
    std::vector<std::string> split (const std::string& _string, char _splitChar, bool _skipEmptyStrings = true);

    //! Convert a primitive type to a string (e.g. string s = toString(1.5f))
    template<class T>
    std::string toString(const T& _t);

    //! Convert a string to a primitive type (e.g. float f = to<float>("1.5"))
    template<class T>
    T to(const std::string& _string, bool* _OK = NULL)
    {
        std::stringstream stream(_string);
        T t;
        stream >> t;
        if(_OK)
            *_OK = !stream.fail();
        return t;
    }
}

} // Base
} // ACGL

#endif // ACGL_BASE_STRINGOPERATIONS_HH
