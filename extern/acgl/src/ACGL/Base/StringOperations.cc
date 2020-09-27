////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2011, Computer Graphics Group RWTH Aachen University         //
// All rights reserved.                                                       //
////////////////////////////////////////////////////////////////////////////////

#include <ACGL/Base/StringOperations.hh>

#include <ACGL/Math/Math.hh>

namespace ACGL{
namespace Base{

namespace StringOperations
{
    bool splitFileExtension(const std::string& _full, std::string& _file, std::string& _extension)
    {
        size_t found;
        found = _full.find_last_of(".");
        if(found == std::string::npos)
            return false;
        _file = _full.substr(0,found);
        _extension = _full.substr(found+1);
        return true;
    }

    bool splitLastFileOrFolder(const std::string& _full, std::string& _path, std::string& _fileOrFolder)
    {
        size_t found;
        found = _full.find_last_of("/");
        if(found == std::string::npos)
            return false;
        _path = _full.substr(0,found);
        _fileOrFolder = _full.substr(found+1);
        return true;
    }

    bool startsWith(const std::string& _string, const std::string& _prefix)
    {
        if(_prefix.length() > _string.length())
            return false;

        for(std::size_t i = 0; i < _prefix.length(); i++)
            if(_prefix[i] != _string[i])
                return false;

        return true;
    }

    std::vector<std::string> split(const std::string& _string, char _splitChar, bool _skipEmptyStrings)
    {
        std::vector<std::string> stringList;
        std::stringstream ss(_string);
        std::string item;
        while(std::getline(ss, item, _splitChar))
        {
            //ignore empty elements if skip is defined
            if(_skipEmptyStrings ? item == "" : false)
                continue;

            stringList.push_back(item);
        }

        return stringList;
    }

    template<class T>
    std::string toString(const T& _t)
    {
        std::ostringstream stream;
        stream << _t;
        return stream.str();
    }

    template std::string toString<bool>(const bool& _t);
    template std::string toString<float>(const float& _t);
    template std::string toString<double>(const double& _t);
    template std::string toString<byte_t>(const byte_t& _t);
    template std::string toString<ubyte_t>(const ubyte_t& _t);
    template std::string toString<short_t>(const short_t& _t);
    template std::string toString<ushort_t>(const ushort_t& _t);
    template std::string toString<int_t>(const int_t& _t);
    template std::string toString<uint_t>(const uint_t& _t);
    template std::string toString<long_t>(const long_t& _t);
    template std::string toString<ulong_t>(const ulong_t& _t);

    template<> std::string toString(const glm::vec2& _t)
    {
        std::ostringstream stream;
        stream << "(" << _t.x << "," << _t.y << ")";
        return stream.str();
    }

    template<> std::string toString(const glm::vec3& _t)
    {
        std::ostringstream stream;
        stream << "(" << _t.x << "," << _t.y << "," << _t.z << ")";
        return stream.str();
    }

    template<> std::string toString(const glm::vec4& _t)
    {
        std::ostringstream stream;
        stream << "(" << _t.x << "," << _t.y << "," << _t.z << "," << _t.w << ")";
        return stream.str();
    }
}

} // Base
} // ACGL
