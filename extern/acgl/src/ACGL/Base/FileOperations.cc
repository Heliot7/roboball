////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2011, Computer Graphics Group RWTH Aachen University         //
// All rights reserved.                                                       //
////////////////////////////////////////////////////////////////////////////////

#include <ACGL/Base/FileOperations.hh>

#include <stdio.h>
#include <stdlib.h>

using namespace std;
using namespace ACGL;
using namespace ACGL::Utils;
using namespace ACGL::Base;

bool FileOperations::rawData(const std::string& _filename, char*& _pData, long_t& _size)
{
    FILE* pFile;
    size_t result;
    
    pFile = fopen(_filename.c_str(), "rb");
    if(pFile==NULL)
    {
        warning() << "Opening error!" << std::endl;
        return false;
    }
    
    // obtain file size:
    fseek(pFile, 0, SEEK_END);
    _size = ftell(pFile);
    rewind(pFile);
    
    // allocate memory to contain the whole file:
    _pData = new char[sizeof(char)*_size];
    if(_pData == NULL)
    {
        error() << "Memory error!" << std::endl;
        return false;
    }
    
    // copy the file into the buffer:
    result = fread(_pData, 1, _size, pFile);
    if ( (long_t)result != _size)
    {
        error() << "Reading error!" << std::endl;
        return false;
    }
    
    /* the whole file is now loaded in the memory buffer. */
    
    // terminate
    fclose (pFile);
    return true;
}
