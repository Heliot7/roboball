////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2011, Computer Graphics Group RWTH Aachen University         //
// All rights reserved.                                                       //
////////////////////////////////////////////////////////////////////////////////

#ifndef ACGL_TYPES_HH
#define ACGL_TYPES_HH

#include <stdint.h>

namespace ACGL{

/*
 * Our datatypes have fixed bit width like the C99 types from stdint,
 * ours are just nicer to read ;-)
 */
typedef int8_t   byte_t;
typedef uint8_t  ubyte_t;
typedef int16_t  short_t;
typedef uint16_t ushort_t;
typedef int32_t  int_t;
typedef uint32_t uint_t;
typedef int64_t  long_t;
typedef uint64_t ulong_t;

} // ACGL

#endif // ACGL_TYPES_HH
