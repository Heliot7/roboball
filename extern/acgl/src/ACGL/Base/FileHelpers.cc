////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2011, Computer Graphics Group RWTH Aachen University         //
// All rights reserved.                                                       //
////////////////////////////////////////////////////////////////////////////////

#include <ACGL/Base/FileHelpers.hh>

#include <cstdio> // fopen etc.
#include <string>
#include <vector>
#include <sstream>
#include <iostream>

namespace ACGL{
namespace Base{

namespace FileHelpers
{
    /*
    char *readTextFile( const std::string &fileName )
    {
        FILE *fp;
        char *content = NULL;

        int32_t count = 0;
        if ( fileName != "" ) {
            fp = fopen( fileName.c_str() ,"rt" ); // "rt"
            if ( fp != NULL ) {
                fseek( fp, 0, SEEK_END );
                count = ftell( fp );
                rewind( fp );

                if ( count > 0 ) {
                    content = new char[ count+1 ];
                    count = fread( content, sizeof(char), count, fp );
                    content[ count ] = '\0';
                }
                fclose( fp );
            }
        }
        // if the file was not readable we will return a NULL pointer
        return content;
    }
*/


    bool stringEndsWith( const std::string &theString, const std::string &theEnding )
    {
        int32_t stringLenght = theString.size();
        int32_t endingLenght = theEnding.size();

        if ( stringLenght < endingLenght ) return false;

        std::string end = theString.substr( stringLenght - endingLenght, endingLenght );

        if ( end == theEnding ) return true;

        return false;
    }

    /*
    bool stringBeginsWith( const std::string &theString, const std::string &thePrefix )
    {
        int32_t stringLenght = theString.size();
        int32_t prefixLenght = thePrefix.size();

        if ( stringLenght < prefixLenght ) return false;

        std::string begin = theString.substr( 0, prefixLenght );

        if ( begin == thePrefix ) return true;

        return false;
    }

    // copied from stackoverflow
    void splitString(const std::string &s, char delim, std::vector<std::string> &elems)
    {
        std::stringstream ss(s);
        std::string item;
        while (std::getline(ss, item, delim)) {
            //ignore empty elements if the delimer was a space only:
            if ((delim == ' ') && (item == "")) {
                continue;
            }

            elems.push_back(item);
        }
    }
    */

    #ifndef PLATFORM_IOS
    std::string getDeviceDependentPathFor( const std::string &resource )
    {
        return resource;
    }
    #endif


    FileModificationTime getFileModificationTime( const std::string &fileName )
    {
        struct stat fileStats;

        stat(fileName.c_str(), &fileStats);
        return fileStats.st_mtime;
    }

    bool fileExists(const std::string &fileName)
    {
        std::ifstream file( fileName.c_str() );
        return file.good();
    }
}

} // Base
} // ACGL

