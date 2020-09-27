////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2011, Computer Graphics Group RWTH Aachen University         //
// All rights reserved.                                                       //
////////////////////////////////////////////////////////////////////////////////

#ifndef ACGL_UTILS_LOG_HH
#define ACGL_UTILS_LOG_HH

/*
 * Some classes, typedefs and defines to create a simple logging system:
 *
 * Can be used excactly like std::cout
 *
 * message stream:   log()     << "foo " << "bar" << var << std::endl;
 * warning stream:   warning() << "memory low" << std::endl;
 * error stream:     error()   << "shader compile failed: " << getErrorMsg() << std::endl;
 * debug stream:     debug()   << "i = " << i << std::endl;
 *
 * Streams can get muted and unmuted at runtime:
 *  debug().mute();
 *  debug() << "you will never see me!" << std::endl;
 *  debug().unmute();
 *
 * The Application can create own streams and set own prefixes:
 *
 *  log<6>().setPrefix("app specific: ");
 *  log<6>() << "logging" << std::endl;
 *
 * If no prefix was set, the number will be used as a prefix:
 *
 *  log<11>() << "up to 11!" << std::endl;
 */

#include <ACGL/ACGL.hh>
#include <ACGL/Base/Singleton.hh>

#include <string>
#include <cstdarg>
#include <iostream>
#include <fstream>
#include <sstream>

namespace ACGL{
namespace Utils{

/*
 * The stream buffer is internally used in the CoutLikeStream (see below).
 */
class CoutLikeStreamBuffer : public std::basic_streambuf<char, std::char_traits<char> >
{
    typedef std::basic_streambuf<char, std::char_traits<char> > base_type;

public:
    CoutLikeStreamBuffer();

    ~CoutLikeStreamBuffer();

    void setPrefix( const std::string &_prefix );

private:

    //virtual std::streamsize xsputn(const base_type::char_type* s, std::streamsize n)
    //{
        // TODO: implement me for better performance
    //}

    virtual base_type::int_type overflow(base_type::int_type ch);

    // for each endl:
    virtual int sync();

private:
    char *mBuffer;
    int   mBufferSize;    // how many bytes are used
    int   mBufferMaxSize; // size of the buffer

    std::string mPrefix;

    bool  mNewLineIsAboutToStart;
};

/*
 * This is the stream itself that behaves like an std::ostream with some custom
 * extensions (like adding the debug level prefix).
 */
template < unsigned int DEBUG_LEVEL >
class CoutLikeStream : public std::ostream, public Base::Singleton<CoutLikeStream<DEBUG_LEVEL> >
{
public:
    CoutLikeStream() : std::ostream( NULL ), mStreamBuffer(NULL) {
        mStreamBuffer = new CoutLikeStreamBuffer();
        switch (DEBUG_LEVEL) {
            case 0: mStreamBuffer->setPrefix("Debug:   ");
            break;
            case 1: mStreamBuffer->setPrefix("Message: ");
            break;
            case 2: mStreamBuffer->setPrefix("Warning: ");
            break;
            case 3: mStreamBuffer->setPrefix("Error:   ");
            break;
            default: {
                mStreamBuffer->setPrefix("> ");
                std::ostringstream streamName;

                streamName << DEBUG_LEVEL << ": ";
                mStreamBuffer->setPrefix( streamName.str() );
            }
        }

        unmute();
    }

    ~CoutLikeStream() {
        delete mStreamBuffer;
    }

    void setPrefix( const std::string &_prefix ) {
        if (mStreamBuffer) {
            mStreamBuffer->setPrefix(_prefix);
        }
    }
    void mute()   { rdbuf( NULL ); }
    void unmute() { rdbuf( mStreamBuffer ); }
private:
    CoutLikeStreamBuffer *mStreamBuffer;
};

/*
 * Defines the stream functions that should be used:
 */
inline CoutLikeStream<0>& debug()   { return (*CoutLikeStream<0>::the()); }
inline CoutLikeStream<1>& message() { return (*CoutLikeStream<1>::the()); }
inline CoutLikeStream<2>& warning() { return (*CoutLikeStream<2>::the()); }
inline CoutLikeStream<3>& error()   { return (*CoutLikeStream<3>::the()); }

/*
 * Generic streams: this way application specific streams can be created:
 */
template < unsigned int N >
inline CoutLikeStream<N>& log() { return (*CoutLikeStream<N>::the()); }

// alternative syntax
#define ACGL_DEBUG(STREAM)   ACGL::Utils::debug() << STREAM;
#define ACGL_MESSAGE(STREAM) ACGL::Utils::message() << STREAM;
#define ACGL_WARNING(STREAM) ACGL::Utils::warning() << STREAM;
#define ACGL_ERROR(STREAM)   ACGL::Utils::error() << STREAM;

#define ACGL_LOG(N,STREAM) ACGL::Utils::log<N>() << STREAM;

} // Utils
} // ACGL

#endif // ACGL_UTILS_LOG_HH
