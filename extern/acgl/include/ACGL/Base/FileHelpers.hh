////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2011, Computer Graphics Group RWTH Aachen University         //
// All rights reserved.                                                       //
////////////////////////////////////////////////////////////////////////////////

#ifndef ACGL_BASE_FILEHELPERS_HH
#define ACGL_BASE_FILEHELPERS_HH

#include <string>
#include <vector>

#include <time.h>
#include <utime.h>
#include <sys/stat.h>

#include <ACGL/ACGL.hh>

namespace ACGL{
namespace Base{

namespace FileHelpers
{
    /*
     * A small collection of helperfunctions to handle files and strings.
     */

    /*
     * Reads a file to a char buffer created with new[], the caller has to delete the buffer.
     * Will return a NULL pointer if the file does not exist or there were other errors opening the file.
     */
    //char *readTextFile( const std::string &fileName );

    /*
     * Checks if a string ends with a certain ending. Can be used to check for fileendings:
     * if (stringEndsWith( "foobar.txt", ".txt" )) cout << "textfile";
     */
    bool stringEndsWith( const std::string &theString, const std::string &theEnding );

    /*
     * Checks if a string begins with a certain prefix.
     */
    //bool stringBeginsWith( const std::string &theString, const std::string &thePrefix );

    /*
     * Splits a string at the delim char.
     */
    //void splitString(const std::string &s, char delim, std::vector<std::string> &elems);


    /*
     * On Desktops this will return the input string. But on iOS it will calculate the absolute
     * path to the file which is needed to access it (it's bundle dependent)
     */
    std::string getDeviceDependentPathFor( const std::string &resource );



    typedef time_t FileModificationTime;

    /*
     * Will return the modification time of the file.
     */
    FileModificationTime getFileModificationTime( const std::string &fileName ) ;

    /*
     * Checks whether a file with the given filename exists and is readable.
     */
    bool fileExists( const std::string &fileName );
}

} // Base
} // ACGL

#endif // FILEHELPERS_H
