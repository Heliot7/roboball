////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2011, Computer Graphics Group RWTH Aachen University         //
// All rights reserved.                                                       //
////////////////////////////////////////////////////////////////////////////////

#ifndef ACGL_BASE_FILEOPERATIONS_HH
#define ACGL_BASE_FILEOPERATIONS_HH

#include <ACGL/ACGL.hh>

#include <string>

namespace ACGL{
namespace Base{

namespace FileOperations
{
    bool rawData(const std::string& _filename, char*& _pData, ACGL::long_t& _size);
}

} // Base
} // ACGL

#endif // ACGL_BASE_FILEOPERATIONS_HH
