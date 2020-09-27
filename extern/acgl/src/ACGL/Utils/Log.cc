////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2011, Computer Graphics Group RWTH Aachen University         //
// All rights reserved.                                                       //
////////////////////////////////////////////////////////////////////////////////

#include <ACGL/Utils/Log.hh>

#include <cstdio>
#include <iostream>

using namespace ACGL::Utils;

CoutLikeStreamBuffer::CoutLikeStreamBuffer() : base_type() {
    mBufferSize    = 0;
    mBufferMaxSize = 256;
    mBuffer        = new char[ mBufferMaxSize+1 ];
    mNewLineIsAboutToStart = true;
}

CoutLikeStreamBuffer::~CoutLikeStreamBuffer() {
    if ( mBufferSize > 0 ) {
        overflow( base_type::traits_type::eof() );
        sync();
    }
    delete[] mBuffer;
}

void CoutLikeStreamBuffer::setPrefix( const std::string &_prefix ) {
    mPrefix = _prefix;
}

CoutLikeStreamBuffer::base_type::int_type CoutLikeStreamBuffer::overflow(base_type::int_type ch) {
    // print buffer
    if ((mBufferSize >= mBufferMaxSize) || ( base_type::traits_type::eq_int_type(ch, base_type::traits_type::eof()))) {

        if (mNewLineIsAboutToStart) {
            std::cout << mPrefix;
            mNewLineIsAboutToStart = false;
        }
        if (mBufferSize > 0) {
            mBuffer[mBufferSize] = (char) 0;
            std::cout << mBuffer;
            mBufferSize = 0;
        }
    } else {
        mBuffer[ mBufferSize++ ] = (char) ch;
    }
    return base_type::traits_type::not_eof( ch );
}

// for each endl:
int CoutLikeStreamBuffer::sync() {
    overflow( base_type::traits_type::eof() );
    std::cout.flush();
    mNewLineIsAboutToStart = true;
    return base_type::sync();
}



