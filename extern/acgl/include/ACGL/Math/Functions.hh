////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2011, Computer Graphics Group RWTH Aachen University         //
// All rights reserved.                                                       //
////////////////////////////////////////////////////////////////////////////////

#ifndef ACGL_MATH_FUNCTIONS_HH
#define ACGL_MATH_FUNCTIONS_HH

/*
 * Some basic math functions.
 *
 * DON'T INCLUDE THIS DIRECTLY! Include <ACGL/Math.hh> instead!
 */

#include <ACGL/ACGL.hh>
#include <ACGL/Math/Constants.hh>

#include <cmath>
#include <limits>

/*
 * Swizzling has to be defined before the glm.hpp gets first included, no not forget
 * this, you should never include glm yourself, but include always our ACGL/Math.hh!
 */
#define GLM_SWIZZL
#include <glm/glm.hpp>

namespace ACGL{
namespace Math{
namespace Functions{

//functions to change from degree to radians and back
inline float  calcDegToRad(float  d) {return (d * Constants::DEG_TO_RAD_FLOAT);}
inline double calcDegToRad(double d) {return (d * Constants::DEG_TO_RAD_DOUBLE);}
inline float  calcRadToDeg(float  r) {return (r * Constants::RAD_TO_DEG_FLOAT);}
inline double calcRadToDeg(double r) {return (r * Constants::RAD_TO_DEG_DOUBLE);}
 
//sine, cosine and tangens
inline float sinRad(float r) {return (::sinf(r));}
inline float cosRad(float r) {return (::cosf(r));}
inline float tanRad(float r) {return (::tanf(r));}
inline float sinDeg(float d) {return (::sinf(d * Constants::DEG_TO_RAD_FLOAT));}
inline float cosDeg(float d) {return (::cosf(d * Constants::DEG_TO_RAD_FLOAT));}
inline float tanDeg(float d) {return (::tanf(d * Constants::DEG_TO_RAD_FLOAT));}

inline double sinRad(double r) {return (::sin(r));}
inline double cosRad(double r) {return (::cos(r));}
inline double tanRad(double r) {return (::tan(r));}
inline double sinDeg(double d) {return (::sin(d * Constants::DEG_TO_RAD_DOUBLE));}
inline double cosDeg(double d) {return (::cos(d * Constants::DEG_TO_RAD_DOUBLE));}
inline double tanDeg(double d) {return (::tan(d * Constants::DEG_TO_RAD_DOUBLE));}

//and back! (asin, acos and atan)
inline float asinRad (float v)          {return (::asinf (v));}
inline float acosRad (float v)          {return (::acosf (v));}
inline float atanRad (float v)          {return (::atanf (v));}
inline float atan2Rad(float a, float b) {return (::atan2f(a, b));}
inline float asinDeg (float v)          {return (::asinf (v) * Constants::RAD_TO_DEG_FLOAT);}
inline float acosDeg (float v)          {return (::acosf (v) * Constants::RAD_TO_DEG_FLOAT);}
inline float atanDeg (float v)          {return (::atanf (v) * Constants::RAD_TO_DEG_FLOAT);}
inline float atan2Deg(float a, float b) {return (::atan2f(a, b) * Constants::RAD_TO_DEG_FLOAT);}

inline double asinRad(double v)            {return (::asin (v));}
inline double acosRad(double v)            {return (::acos (v));}
inline double atanRad(double v)            {return (::atan (v));}
inline double atan2Rad(double a, double b) {return (::atan2(a, b));}
inline double asinDeg(double v)            {return (::asin (v) * Constants::RAD_TO_DEG_DOUBLE);}
inline double acosDeg(double v)            {return (::acos (v) * Constants::RAD_TO_DEG_DOUBLE);}
inline double atanDeg(double v)            {return (::atan (v) * Constants::RAD_TO_DEG_DOUBLE);}
inline double atan2Deg(double a, double b) {return (::atan2(a, b) * Constants::RAD_TO_DEG_DOUBLE);}

//Helpers
inline int32_t round(float a)  {return (a < 0.5f)? ceil(a-0.5f) : floor(a+0.5f);}
inline int32_t round(double a) {return (a < 0.5 )? ceil(a-0.5 ) : floor(a+0.5 );}

inline float  pow(float a,  float  b) { return ::powf(a, b); }
inline double pow(double a, double b) { return ::pow(a, b); }

inline float  ceil(float a)  {return ::ceilf(a);}
inline double ceil(double a) {return ::ceil(a);}

inline float  floor(float a)  {return ::floorf(a);}
inline double floor(double a) {return ::floor(a);}

inline float  sqrt(float a)  {return(::sqrtf(a));}
inline double sqrt(double a) {return(::sqrt (a));}

inline float  sig(float a)  {return(a < 0.0f ? -1.0f : 1.0f);}
inline double sig(double a) {return(a < 0.0  ? -1.0  : 1.0 );}

inline float  abs(float a)  {return(a < 0.0f ? -a : a);}
inline double abs(double a) {return(a < 0.0  ? -a : a);}
inline int_t  abs(int_t a)  {return(a < 0    ? -a : a);}

inline double  randD   (double  _from = 0.0, double  _to = 1.0) { return (_to - _from) * (double(rand()) / double(RAND_MAX)) + _from; }
inline int32_t randI32 (int32_t _from =   0, int32_t _to =   1) { return (rand() % (_to - _from + 1)) + _from; }

template<typename T>
inline T max(T a, T b) {return(a > b ? a : b);}

template<typename T>
inline T min(T a, T b) {return(a < b ? a : b);}

inline uint_t ring(int_t a, uint_t mod) {bool b = a < 0; a = abs(a) % mod; return(b ? mod - a : a);}

inline glm::mat3 rotationMatrixX(float degree)
{
    glm::mat3 matrix;
    matrix[0][0] = 1.0f; matrix[1][0] = 0.0f;           matrix[2][0] =  0.0f;
    matrix[0][1] = 0.0f; matrix[1][1] = cosDeg(degree); matrix[2][1] = -sinDeg(degree);
    matrix[0][2] = 0.0f; matrix[1][2] = sinDeg(degree); matrix[2][2] =  cosDeg(degree);
    return matrix;
}

inline glm::mat3 rotationMatrixY(float degree)
{
    glm::mat3 matrix;
    matrix[0][0] =  cosDeg(degree); matrix[1][0] = 0.0f; matrix[2][0] = sinDeg(degree);
    matrix[0][1] =  0.0f;           matrix[1][1] = 1.0f; matrix[2][1] = 0.0f;
    matrix[0][2] = -sinDeg(degree); matrix[1][2] = 0.0f; matrix[2][2] = cosDeg(degree);
    return matrix;
}

inline glm::mat3 rotationMatrixZ(float degree)
{
    glm::mat3 matrix;
    matrix[0][0] = cosDeg(degree); matrix[1][0] = -sinDeg(degree); matrix[2][0] = 0.0f;
    matrix[0][1] = sinDeg(degree); matrix[1][1] =  cosDeg(degree); matrix[2][1] = 0.0f;
    matrix[0][2] = 0.0f;           matrix[1][2] =  0.0f;           matrix[2][2] = 1.0f;
    return matrix;
}

inline glm::mat3 normalMatrix(const glm::mat4& matrix)
{
    return glm::inverseTranspose( glm::mat3( matrix ) );
}

} // Functions
} // Math
} // ACGL

#endif // ACGL_MATH_FUNCTIONS_HH
