////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2011, Computer Graphics Group RWTH Aachen University         //
// All rights reserved.                                                       //
////////////////////////////////////////////////////////////////////////////////

#ifndef ACGL_MATH_HH
#define ACGL_MATH_HH

#include <ACGL/ACGL.hh>

/*
 * For our basic vector math we use the GLM library.
 * This library has the advantage that it was designed to mimic the
 * syntax of GLSL for datatypes (vectors, matrices etc.) as well as functions.
 * It also supports swizzling similar to GLSL.
 *
 * Swizzling has to be defined before the glm.hpp gets first included, no not forget
 * this, you should never include glm yourself, but include always our ACGL/Math.hh!
 *
 * Pragmas: try to ignore warnings in GLM, so warnings can be activated for ACGL builds
 * and the log does not get flooded with GLM warnings that we can't fix anyway with the
 * risk of not seeing ACGL warnings.
 */
#if (((__GNUC__ == 4) && (__GNUC_MINOR__ >= 6)) || (__GNUC__ > 4))
#   pragma GCC diagnostic push
#endif
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wtype-limits"
#define GLM_SWIZZL
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#if (((__GNUC__ == 4) && (__GNUC_MINOR__ >= 6)) || (__GNUC__ > 4))
#   pragma GCC diagnostic pop
#endif

#include <ACGL/Math/Constants.hh>
#include <ACGL/Math/Functions.hh>

#endif // ACGL_MATH_HH
