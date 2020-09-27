#ifndef ACGL_OPENGL_EXT_DIRECT_STATE_ACCESS_HH
#define ACGL_OPENGL_EXT_DIRECT_STATE_ACCESS_HH
/*
 * Direct state access (DSA for short) makes it easier to change OpenGL objects because it does not
 * require this object to be bound at that moment.
 * Let's look at one example:
 *
 * glUseProgram( shader );
 * glUniform1f( location, 1.0f );
 *
 * can now be expressed as:
 *
 * glProgramUniform1f( shader, 1.0f );
 *
 * If you forget the glUseProgram, bad things can happen. Also: the bound shader program changed, if
 * you want to set a uniform without sideeffects, you'll have to save the currently bound shader,
 * use the other one, set the uniform and restore the old shader. That's what the emulation of the DSA
 * function will do! So the emulation can be slower but less error prone.
 *
 */

#include <ACGL/ACGL.hh>
#include <ACGL/OpenGL/GL.hh>

namespace ACGL{
namespace OpenGL{

/*
 * This should get called AFTER glewInit but BEFORE any ACGL or DSA *EXT functions get called.
 * Normally this gets called by acglInit!
 *
 * If EXT_direct_state_access is not available, this will map GLEWs function pointers for this
 * extension to our emulation functions.
 */
void initDirectStateAccessFunctions();

} // OpenGL
} // ACGL

//
// On some windows configurations ACGLAPIENTRY can be defined wrong which leads to compile
// errors when setting the function pointers.
// Also, if there is no GLEW, we have to define this anyway!
//
#if defined(__MINGW32__) || defined(__CYGWIN__)
#  define ACGLAPIENTRY __stdcall
#elif (_MSC_VER >= 800) || defined(_STDCALL_SUPPORTED) || defined(__BORLANDC__)
#  define ACGLAPIENTRY __stdcall
#else
#  define ACGLAPIENTRY
#endif

//
// GLEW defines function pointers for the DSA extension functions, if there is no GLEW we have
// to it our self:
#ifndef ACGL_USE_GLEW

#define GL_PROGRAM_MATRIX_ACGL             0x8E2D
#define GL_TRANSPOSE_PROGRAM_MATRIX_ACGL   0x8E2E
#define GL_PROGRAM_MATRIX_STACK_DEPTH_ACGL 0x8E2F

typedef ptrdiff_t GLintptr;
typedef ptrdiff_t GLsizeiptr;

typedef void (ACGLAPIENTRY* PFNGLBINDMULTITEXTUREEXTPROC) (GLenum texunit, GLenum target, GLuint texture);
typedef GLenum (ACGLAPIENTRY* PFNGLCHECKNAMEDFRAMEBUFFERSTATUSEXTPROC) (GLuint framebuffer, GLenum target);
typedef void (ACGLAPIENTRY* PFNGLCLIENTATTRIBDEFAULTEXTPROC) (GLbitfield mask);
typedef void (ACGLAPIENTRY* PFNGLCOMPRESSEDMULTITEXIMAGE1DEXTPROC) (GLenum texunit, GLenum target, GLint level, GLenum internalformat, GLsizei width, GLint border, GLsizei imageSize, const void* data);
typedef void (ACGLAPIENTRY* PFNGLCOMPRESSEDMULTITEXIMAGE2DEXTPROC) (GLenum texunit, GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const void* data);
typedef void (ACGLAPIENTRY* PFNGLCOMPRESSEDMULTITEXIMAGE3DEXTPROC) (GLenum texunit, GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, const void* data);
typedef void (ACGLAPIENTRY* PFNGLCOMPRESSEDMULTITEXSUBIMAGE1DEXTPROC) (GLenum texunit, GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, const void* data);
typedef void (ACGLAPIENTRY* PFNGLCOMPRESSEDMULTITEXSUBIMAGE2DEXTPROC) (GLenum texunit, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const void* data);
typedef void (ACGLAPIENTRY* PFNGLCOMPRESSEDMULTITEXSUBIMAGE3DEXTPROC) (GLenum texunit, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const void* data);
typedef void (ACGLAPIENTRY* PFNGLCOMPRESSEDTEXTUREIMAGE1DEXTPROC) (GLuint texture, GLenum target, GLint level, GLenum internalformat, GLsizei width, GLint border, GLsizei imageSize, const void* data);
typedef void (ACGLAPIENTRY* PFNGLCOMPRESSEDTEXTUREIMAGE2DEXTPROC) (GLuint texture, GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const void* data);
typedef void (ACGLAPIENTRY* PFNGLCOMPRESSEDTEXTUREIMAGE3DEXTPROC) (GLuint texture, GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, const void* data);
typedef void (ACGLAPIENTRY* PFNGLCOMPRESSEDTEXTURESUBIMAGE1DEXTPROC) (GLuint texture, GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, const void* data);
typedef void (ACGLAPIENTRY* PFNGLCOMPRESSEDTEXTURESUBIMAGE2DEXTPROC) (GLuint texture, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const void* data);
typedef void (ACGLAPIENTRY* PFNGLCOMPRESSEDTEXTURESUBIMAGE3DEXTPROC) (GLuint texture, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const void* data);
typedef void (ACGLAPIENTRY* PFNGLCOPYMULTITEXIMAGE1DEXTPROC) (GLenum texunit, GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLint border);
typedef void (ACGLAPIENTRY* PFNGLCOPYMULTITEXIMAGE2DEXTPROC) (GLenum texunit, GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border);
typedef void (ACGLAPIENTRY* PFNGLCOPYMULTITEXSUBIMAGE1DEXTPROC) (GLenum texunit, GLenum target, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width);
typedef void (ACGLAPIENTRY* PFNGLCOPYMULTITEXSUBIMAGE2DEXTPROC) (GLenum texunit, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height);
typedef void (ACGLAPIENTRY* PFNGLCOPYMULTITEXSUBIMAGE3DEXTPROC) (GLenum texunit, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height);
typedef void (ACGLAPIENTRY* PFNGLCOPYTEXTUREIMAGE1DEXTPROC) (GLuint texture, GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLint border);
typedef void (ACGLAPIENTRY* PFNGLCOPYTEXTUREIMAGE2DEXTPROC) (GLuint texture, GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border);
typedef void (ACGLAPIENTRY* PFNGLCOPYTEXTURESUBIMAGE1DEXTPROC) (GLuint texture, GLenum target, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width);
typedef void (ACGLAPIENTRY* PFNGLCOPYTEXTURESUBIMAGE2DEXTPROC) (GLuint texture, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height);
typedef void (ACGLAPIENTRY* PFNGLCOPYTEXTURESUBIMAGE3DEXTPROC) (GLuint texture, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height);
typedef void (ACGLAPIENTRY* PFNGLDISABLECLIENTSTATEINDEXEDEXTPROC) (GLenum array, GLuint index);
typedef void (ACGLAPIENTRY* PFNGLDISABLECLIENTSTATEIEXTPROC) (GLenum array, GLuint index);
typedef void (ACGLAPIENTRY* PFNGLDISABLEVERTEXARRAYATTRIBEXTPROC) (GLuint vaobj, GLuint index);
typedef void (ACGLAPIENTRY* PFNGLDISABLEVERTEXARRAYEXTPROC) (GLuint vaobj, GLenum array);
typedef void (ACGLAPIENTRY* PFNGLENABLECLIENTSTATEINDEXEDEXTPROC) (GLenum array, GLuint index);
typedef void (ACGLAPIENTRY* PFNGLENABLECLIENTSTATEIEXTPROC) (GLenum array, GLuint index);
typedef void (ACGLAPIENTRY* PFNGLENABLEVERTEXARRAYATTRIBEXTPROC) (GLuint vaobj, GLuint index);
typedef void (ACGLAPIENTRY* PFNGLENABLEVERTEXARRAYEXTPROC) (GLuint vaobj, GLenum array);
typedef void (ACGLAPIENTRY* PFNGLFLUSHMAPPEDNAMEDBUFFERRANGEEXTPROC) (GLuint buffer, GLintptr offset, GLsizeiptr length);
typedef void (ACGLAPIENTRY* PFNGLFRAMEBUFFERDRAWBUFFEREXTPROC) (GLuint framebuffer, GLenum mode);
typedef void (ACGLAPIENTRY* PFNGLFRAMEBUFFERDRAWBUFFERSEXTPROC) (GLuint framebuffer, GLsizei n, const GLenum* bufs);
typedef void (ACGLAPIENTRY* PFNGLFRAMEBUFFERREADBUFFEREXTPROC) (GLuint framebuffer, GLenum mode);
typedef void (ACGLAPIENTRY* PFNGLGENERATEMULTITEXMIPMAPEXTPROC) (GLenum texunit, GLenum target);
typedef void (ACGLAPIENTRY* PFNGLGENERATETEXTUREMIPMAPEXTPROC) (GLuint texture, GLenum target);
typedef void (ACGLAPIENTRY* PFNGLGETCOMPRESSEDMULTITEXIMAGEEXTPROC) (GLenum texunit, GLenum target, GLint level, void* img);
typedef void (ACGLAPIENTRY* PFNGLGETCOMPRESSEDTEXTUREIMAGEEXTPROC) (GLuint texture, GLenum target, GLint level, void* img);
typedef void (ACGLAPIENTRY* PFNGLGETDOUBLEINDEXEDVEXTPROC) (GLenum target, GLuint index, GLdouble* params);
typedef void (ACGLAPIENTRY* PFNGLGETDOUBLEI_VEXTPROC) (GLenum pname, GLuint index, GLdouble* params);
typedef void (ACGLAPIENTRY* PFNGLGETFLOATINDEXEDVEXTPROC) (GLenum target, GLuint index, GLfloat* params);
typedef void (ACGLAPIENTRY* PFNGLGETFLOATI_VEXTPROC) (GLenum pname, GLuint index, GLfloat* params);
typedef void (ACGLAPIENTRY* PFNGLGETFRAMEBUFFERPARAMETERIVEXTPROC) (GLuint framebuffer, GLenum pname, GLint* param);
typedef void (ACGLAPIENTRY* PFNGLGETMULTITEXENVFVEXTPROC) (GLenum texunit, GLenum target, GLenum pname, GLfloat* params);
typedef void (ACGLAPIENTRY* PFNGLGETMULTITEXENVIVEXTPROC) (GLenum texunit, GLenum target, GLenum pname, GLint* params);
typedef void (ACGLAPIENTRY* PFNGLGETMULTITEXGENDVEXTPROC) (GLenum texunit, GLenum coord, GLenum pname, GLdouble* params);
typedef void (ACGLAPIENTRY* PFNGLGETMULTITEXGENFVEXTPROC) (GLenum texunit, GLenum coord, GLenum pname, GLfloat* params);
typedef void (ACGLAPIENTRY* PFNGLGETMULTITEXGENIVEXTPROC) (GLenum texunit, GLenum coord, GLenum pname, GLint* params);
typedef void (ACGLAPIENTRY* PFNGLGETMULTITEXIMAGEEXTPROC) (GLenum texunit, GLenum target, GLint level, GLenum format, GLenum type, void* pixels);
typedef void (ACGLAPIENTRY* PFNGLGETMULTITEXLEVELPARAMETERFVEXTPROC) (GLenum texunit, GLenum target, GLint level, GLenum pname, GLfloat* params);
typedef void (ACGLAPIENTRY* PFNGLGETMULTITEXLEVELPARAMETERIVEXTPROC) (GLenum texunit, GLenum target, GLint level, GLenum pname, GLint* params);
typedef void (ACGLAPIENTRY* PFNGLGETMULTITEXPARAMETERIIVEXTPROC) (GLenum texunit, GLenum target, GLenum pname, GLint* params);
typedef void (ACGLAPIENTRY* PFNGLGETMULTITEXPARAMETERIUIVEXTPROC) (GLenum texunit, GLenum target, GLenum pname, GLuint* params);
typedef void (ACGLAPIENTRY* PFNGLGETMULTITEXPARAMETERFVEXTPROC) (GLenum texunit, GLenum target, GLenum pname, GLfloat* params);
typedef void (ACGLAPIENTRY* PFNGLGETMULTITEXPARAMETERIVEXTPROC) (GLenum texunit, GLenum target, GLenum pname, GLint* params);
typedef void (ACGLAPIENTRY* PFNGLGETNAMEDBUFFERPARAMETERIVEXTPROC) (GLuint buffer, GLenum pname, GLint* params);
typedef void (ACGLAPIENTRY* PFNGLGETNAMEDBUFFERPOINTERVEXTPROC) (GLuint buffer, GLenum pname, void** params);
typedef void (ACGLAPIENTRY* PFNGLGETNAMEDBUFFERSUBDATAEXTPROC) (GLuint buffer, GLintptr offset, GLsizeiptr size, void* data);
typedef void (ACGLAPIENTRY* PFNGLGETNAMEDFRAMEBUFFERATTACHMENTPARAMETERIVEXTPROC) (GLuint framebuffer, GLenum attachment, GLenum pname, GLint* params);
typedef void (ACGLAPIENTRY* PFNGLGETNAMEDPROGRAMLOCALPARAMETERIIVEXTPROC) (GLuint program, GLenum target, GLuint index, GLint* params);
typedef void (ACGLAPIENTRY* PFNGLGETNAMEDPROGRAMLOCALPARAMETERIUIVEXTPROC) (GLuint program, GLenum target, GLuint index, GLuint* params);
typedef void (ACGLAPIENTRY* PFNGLGETNAMEDPROGRAMLOCALPARAMETERDVEXTPROC) (GLuint program, GLenum target, GLuint index, GLdouble* params);
typedef void (ACGLAPIENTRY* PFNGLGETNAMEDPROGRAMLOCALPARAMETERFVEXTPROC) (GLuint program, GLenum target, GLuint index, GLfloat* params);
typedef void (ACGLAPIENTRY* PFNGLGETNAMEDPROGRAMSTRINGEXTPROC) (GLuint program, GLenum target, GLenum pname, void* string);
typedef void (ACGLAPIENTRY* PFNGLGETNAMEDPROGRAMIVEXTPROC) (GLuint program, GLenum target, GLenum pname, GLint* params);
typedef void (ACGLAPIENTRY* PFNGLGETNAMEDRENDERBUFFERPARAMETERIVEXTPROC) (GLuint renderbuffer, GLenum pname, GLint* params);
typedef void (ACGLAPIENTRY* PFNGLGETPOINTERINDEXEDVEXTPROC) (GLenum target, GLuint index, GLvoid** params);
typedef void (ACGLAPIENTRY* PFNGLGETPOINTERI_VEXTPROC) (GLenum pname, GLuint index, GLvoid** params);
typedef void (ACGLAPIENTRY* PFNGLGETTEXTUREIMAGEEXTPROC) (GLuint texture, GLenum target, GLint level, GLenum format, GLenum type, void* pixels);
typedef void (ACGLAPIENTRY* PFNGLGETTEXTURELEVELPARAMETERFVEXTPROC) (GLuint texture, GLenum target, GLint level, GLenum pname, GLfloat* params);
typedef void (ACGLAPIENTRY* PFNGLGETTEXTURELEVELPARAMETERIVEXTPROC) (GLuint texture, GLenum target, GLint level, GLenum pname, GLint* params);
typedef void (ACGLAPIENTRY* PFNGLGETTEXTUREPARAMETERIIVEXTPROC) (GLuint texture, GLenum target, GLenum pname, GLint* params);
typedef void (ACGLAPIENTRY* PFNGLGETTEXTUREPARAMETERIUIVEXTPROC) (GLuint texture, GLenum target, GLenum pname, GLuint* params);
typedef void (ACGLAPIENTRY* PFNGLGETTEXTUREPARAMETERFVEXTPROC) (GLuint texture, GLenum target, GLenum pname, GLfloat* params);
typedef void (ACGLAPIENTRY* PFNGLGETTEXTUREPARAMETERIVEXTPROC) (GLuint texture, GLenum target, GLenum pname, GLint* params);
typedef void (ACGLAPIENTRY* PFNGLGETVERTEXARRAYINTEGERI_VEXTPROC) (GLuint vaobj, GLuint index, GLenum pname, GLint* param);
typedef void (ACGLAPIENTRY* PFNGLGETVERTEXARRAYINTEGERVEXTPROC) (GLuint vaobj, GLenum pname, GLint* param);
typedef void (ACGLAPIENTRY* PFNGLGETVERTEXARRAYPOINTERI_VEXTPROC) (GLuint vaobj, GLuint index, GLenum pname, GLvoid** param);
typedef void (ACGLAPIENTRY* PFNGLGETVERTEXARRAYPOINTERVEXTPROC) (GLuint vaobj, GLenum pname, GLvoid** param);
typedef GLvoid * (ACGLAPIENTRY* PFNGLMAPNAMEDBUFFEREXTPROC) (GLuint buffer, GLenum access);
typedef GLvoid * (ACGLAPIENTRY* PFNGLMAPNAMEDBUFFERRANGEEXTPROC) (GLuint buffer, GLintptr offset, GLsizeiptr length, GLbitfield access);
typedef void (ACGLAPIENTRY* PFNGLMATRIXFRUSTUMEXTPROC) (GLenum matrixMode, GLdouble l, GLdouble r, GLdouble b, GLdouble t, GLdouble n, GLdouble f);
typedef void (ACGLAPIENTRY* PFNGLMATRIXLOADIDENTITYEXTPROC) (GLenum matrixMode);
typedef void (ACGLAPIENTRY* PFNGLMATRIXLOADTRANSPOSEDEXTPROC) (GLenum matrixMode, const GLdouble* m);
typedef void (ACGLAPIENTRY* PFNGLMATRIXLOADTRANSPOSEFEXTPROC) (GLenum matrixMode, const GLfloat* m);
typedef void (ACGLAPIENTRY* PFNGLMATRIXLOADDEXTPROC) (GLenum matrixMode, const GLdouble* m);
typedef void (ACGLAPIENTRY* PFNGLMATRIXLOADFEXTPROC) (GLenum matrixMode, const GLfloat* m);
typedef void (ACGLAPIENTRY* PFNGLMATRIXMULTTRANSPOSEDEXTPROC) (GLenum matrixMode, const GLdouble* m);
typedef void (ACGLAPIENTRY* PFNGLMATRIXMULTTRANSPOSEFEXTPROC) (GLenum matrixMode, const GLfloat* m);
typedef void (ACGLAPIENTRY* PFNGLMATRIXMULTDEXTPROC) (GLenum matrixMode, const GLdouble* m);
typedef void (ACGLAPIENTRY* PFNGLMATRIXMULTFEXTPROC) (GLenum matrixMode, const GLfloat* m);
typedef void (ACGLAPIENTRY* PFNGLMATRIXORTHOEXTPROC) (GLenum matrixMode, GLdouble l, GLdouble r, GLdouble b, GLdouble t, GLdouble n, GLdouble f);
typedef void (ACGLAPIENTRY* PFNGLMATRIXPOPEXTPROC) (GLenum matrixMode);
typedef void (ACGLAPIENTRY* PFNGLMATRIXPUSHEXTPROC) (GLenum matrixMode);
typedef void (ACGLAPIENTRY* PFNGLMATRIXROTATEDEXTPROC) (GLenum matrixMode, GLdouble angle, GLdouble x, GLdouble y, GLdouble z);
typedef void (ACGLAPIENTRY* PFNGLMATRIXROTATEFEXTPROC) (GLenum matrixMode, GLfloat angle, GLfloat x, GLfloat y, GLfloat z);
typedef void (ACGLAPIENTRY* PFNGLMATRIXSCALEDEXTPROC) (GLenum matrixMode, GLdouble x, GLdouble y, GLdouble z);
typedef void (ACGLAPIENTRY* PFNGLMATRIXSCALEFEXTPROC) (GLenum matrixMode, GLfloat x, GLfloat y, GLfloat z);
typedef void (ACGLAPIENTRY* PFNGLMATRIXTRANSLATEDEXTPROC) (GLenum matrixMode, GLdouble x, GLdouble y, GLdouble z);
typedef void (ACGLAPIENTRY* PFNGLMATRIXTRANSLATEFEXTPROC) (GLenum matrixMode, GLfloat x, GLfloat y, GLfloat z);
typedef void (ACGLAPIENTRY* PFNGLMULTITEXBUFFEREXTPROC) (GLenum texunit, GLenum target, GLenum internalformat, GLuint buffer);
typedef void (ACGLAPIENTRY* PFNGLMULTITEXCOORDPOINTEREXTPROC) (GLenum texunit, GLint size, GLenum type, GLsizei stride, const void* pointer);
typedef void (ACGLAPIENTRY* PFNGLMULTITEXENVFEXTPROC) (GLenum texunit, GLenum target, GLenum pname, GLfloat param);
typedef void (ACGLAPIENTRY* PFNGLMULTITEXENVFVEXTPROC) (GLenum texunit, GLenum target, GLenum pname, const GLfloat* params);
typedef void (ACGLAPIENTRY* PFNGLMULTITEXENVIEXTPROC) (GLenum texunit, GLenum target, GLenum pname, GLint param);
typedef void (ACGLAPIENTRY* PFNGLMULTITEXENVIVEXTPROC) (GLenum texunit, GLenum target, GLenum pname, const GLint* params);
typedef void (ACGLAPIENTRY* PFNGLMULTITEXGENDEXTPROC) (GLenum texunit, GLenum coord, GLenum pname, GLdouble param);
typedef void (ACGLAPIENTRY* PFNGLMULTITEXGENDVEXTPROC) (GLenum texunit, GLenum coord, GLenum pname, const GLdouble* params);
typedef void (ACGLAPIENTRY* PFNGLMULTITEXGENFEXTPROC) (GLenum texunit, GLenum coord, GLenum pname, GLfloat param);
typedef void (ACGLAPIENTRY* PFNGLMULTITEXGENFVEXTPROC) (GLenum texunit, GLenum coord, GLenum pname, const GLfloat* params);
typedef void (ACGLAPIENTRY* PFNGLMULTITEXGENIEXTPROC) (GLenum texunit, GLenum coord, GLenum pname, GLint param);
typedef void (ACGLAPIENTRY* PFNGLMULTITEXGENIVEXTPROC) (GLenum texunit, GLenum coord, GLenum pname, const GLint* params);
typedef void (ACGLAPIENTRY* PFNGLMULTITEXIMAGE1DEXTPROC) (GLenum texunit, GLenum target, GLint level, GLint internalformat, GLsizei width, GLint border, GLenum format, GLenum type, const void* pixels);
typedef void (ACGLAPIENTRY* PFNGLMULTITEXIMAGE2DEXTPROC) (GLenum texunit, GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const void* pixels);
typedef void (ACGLAPIENTRY* PFNGLMULTITEXIMAGE3DEXTPROC) (GLenum texunit, GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const void* pixels);
typedef void (ACGLAPIENTRY* PFNGLMULTITEXPARAMETERIIVEXTPROC) (GLenum texunit, GLenum target, GLenum pname, const GLint* params);
typedef void (ACGLAPIENTRY* PFNGLMULTITEXPARAMETERIUIVEXTPROC) (GLenum texunit, GLenum target, GLenum pname, const GLuint* params);
typedef void (ACGLAPIENTRY* PFNGLMULTITEXPARAMETERFEXTPROC) (GLenum texunit, GLenum target, GLenum pname, GLfloat param);
typedef void (ACGLAPIENTRY* PFNGLMULTITEXPARAMETERFVEXTPROC) (GLenum texunit, GLenum target, GLenum pname, const GLfloat* param);
typedef void (ACGLAPIENTRY* PFNGLMULTITEXPARAMETERIEXTPROC) (GLenum texunit, GLenum target, GLenum pname, GLint param);
typedef void (ACGLAPIENTRY* PFNGLMULTITEXPARAMETERIVEXTPROC) (GLenum texunit, GLenum target, GLenum pname, const GLint* param);
typedef void (ACGLAPIENTRY* PFNGLMULTITEXRENDERBUFFEREXTPROC) (GLenum texunit, GLenum target, GLuint renderbuffer);
typedef void (ACGLAPIENTRY* PFNGLMULTITEXSUBIMAGE1DEXTPROC) (GLenum texunit, GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const void* pixels);
typedef void (ACGLAPIENTRY* PFNGLMULTITEXSUBIMAGE2DEXTPROC) (GLenum texunit, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void* pixels);
typedef void (ACGLAPIENTRY* PFNGLMULTITEXSUBIMAGE3DEXTPROC) (GLenum texunit, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void* pixels);
typedef void (ACGLAPIENTRY* PFNGLNAMEDBUFFERDATAEXTPROC) (GLuint buffer, GLsizeiptr size, const void* data, GLenum usage);
typedef void (ACGLAPIENTRY* PFNGLNAMEDBUFFERSUBDATAEXTPROC) (GLuint buffer, GLintptr offset, GLsizeiptr size, const void* data);
typedef void (ACGLAPIENTRY* PFNGLNAMEDCOPYBUFFERSUBDATAEXTPROC) (GLuint readBuffer, GLuint writeBuffer, GLintptr readOffset, GLintptr writeOffset, GLsizeiptr size);
typedef void (ACGLAPIENTRY* PFNGLNAMEDFRAMEBUFFERRENDERBUFFEREXTPROC) (GLuint framebuffer, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);
typedef void (ACGLAPIENTRY* PFNGLNAMEDFRAMEBUFFERTEXTURE1DEXTPROC) (GLuint framebuffer, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
typedef void (ACGLAPIENTRY* PFNGLNAMEDFRAMEBUFFERTEXTURE2DEXTPROC) (GLuint framebuffer, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
typedef void (ACGLAPIENTRY* PFNGLNAMEDFRAMEBUFFERTEXTURE3DEXTPROC) (GLuint framebuffer, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLint zoffset);
typedef void (ACGLAPIENTRY* PFNGLNAMEDFRAMEBUFFERTEXTUREEXTPROC) (GLuint framebuffer, GLenum attachment, GLuint texture, GLint level);
typedef void (ACGLAPIENTRY* PFNGLNAMEDFRAMEBUFFERTEXTUREFACEEXTPROC) (GLuint framebuffer, GLenum attachment, GLuint texture, GLint level, GLenum face);
typedef void (ACGLAPIENTRY* PFNGLNAMEDFRAMEBUFFERTEXTURELAYEREXTPROC) (GLuint framebuffer, GLenum attachment, GLuint texture, GLint level, GLint layer);
typedef void (ACGLAPIENTRY* PFNGLNAMEDPROGRAMLOCALPARAMETER4DEXTPROC) (GLuint program, GLenum target, GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w);
typedef void (ACGLAPIENTRY* PFNGLNAMEDPROGRAMLOCALPARAMETER4DVEXTPROC) (GLuint program, GLenum target, GLuint index, const GLdouble* params);
typedef void (ACGLAPIENTRY* PFNGLNAMEDPROGRAMLOCALPARAMETER4FEXTPROC) (GLuint program, GLenum target, GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
typedef void (ACGLAPIENTRY* PFNGLNAMEDPROGRAMLOCALPARAMETER4FVEXTPROC) (GLuint program, GLenum target, GLuint index, const GLfloat* params);
typedef void (ACGLAPIENTRY* PFNGLNAMEDPROGRAMLOCALPARAMETERI4IEXTPROC) (GLuint program, GLenum target, GLuint index, GLint x, GLint y, GLint z, GLint w);
typedef void (ACGLAPIENTRY* PFNGLNAMEDPROGRAMLOCALPARAMETERI4IVEXTPROC) (GLuint program, GLenum target, GLuint index, const GLint* params);
typedef void (ACGLAPIENTRY* PFNGLNAMEDPROGRAMLOCALPARAMETERI4UIEXTPROC) (GLuint program, GLenum target, GLuint index, GLuint x, GLuint y, GLuint z, GLuint w);
typedef void (ACGLAPIENTRY* PFNGLNAMEDPROGRAMLOCALPARAMETERI4UIVEXTPROC) (GLuint program, GLenum target, GLuint index, const GLuint* params);
typedef void (ACGLAPIENTRY* PFNGLNAMEDPROGRAMLOCALPARAMETERS4FVEXTPROC) (GLuint program, GLenum target, GLuint index, GLsizei count, const GLfloat* params);
typedef void (ACGLAPIENTRY* PFNGLNAMEDPROGRAMLOCALPARAMETERSI4IVEXTPROC) (GLuint program, GLenum target, GLuint index, GLsizei count, const GLint* params);
typedef void (ACGLAPIENTRY* PFNGLNAMEDPROGRAMLOCALPARAMETERSI4UIVEXTPROC) (GLuint program, GLenum target, GLuint index, GLsizei count, const GLuint* params);
typedef void (ACGLAPIENTRY* PFNGLNAMEDPROGRAMSTRINGEXTPROC) (GLuint program, GLenum target, GLenum format, GLsizei len, const void* string);
typedef void (ACGLAPIENTRY* PFNGLNAMEDRENDERBUFFERSTORAGEEXTPROC) (GLuint renderbuffer, GLenum internalformat, GLsizei width, GLsizei height);
typedef void (ACGLAPIENTRY* PFNGLNAMEDRENDERBUFFERSTORAGEMULTISAMPLECOVERAGEEXTPROC) (GLuint renderbuffer, GLsizei coverageSamples, GLsizei colorSamples, GLenum internalformat, GLsizei width, GLsizei height);
typedef void (ACGLAPIENTRY* PFNGLNAMEDRENDERBUFFERSTORAGEMULTISAMPLEEXTPROC) (GLuint renderbuffer, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height);
typedef void (ACGLAPIENTRY* PFNGLPROGRAMUNIFORM1FEXTPROC) (GLuint program, GLint location, GLfloat v0);
typedef void (ACGLAPIENTRY* PFNGLPROGRAMUNIFORM1FVEXTPROC) (GLuint program, GLint location, GLsizei count, const GLfloat* value);
typedef void (ACGLAPIENTRY* PFNGLPROGRAMUNIFORM1IEXTPROC) (GLuint program, GLint location, GLint v0);
typedef void (ACGLAPIENTRY* PFNGLPROGRAMUNIFORM1IVEXTPROC) (GLuint program, GLint location, GLsizei count, const GLint* value);
typedef void (ACGLAPIENTRY* PFNGLPROGRAMUNIFORM1UIEXTPROC) (GLuint program, GLint location, GLuint v0);
typedef void (ACGLAPIENTRY* PFNGLPROGRAMUNIFORM1UIVEXTPROC) (GLuint program, GLint location, GLsizei count, const GLuint* value);
typedef void (ACGLAPIENTRY* PFNGLPROGRAMUNIFORM2FEXTPROC) (GLuint program, GLint location, GLfloat v0, GLfloat v1);
typedef void (ACGLAPIENTRY* PFNGLPROGRAMUNIFORM2FVEXTPROC) (GLuint program, GLint location, GLsizei count, const GLfloat* value);
typedef void (ACGLAPIENTRY* PFNGLPROGRAMUNIFORM2IEXTPROC) (GLuint program, GLint location, GLint v0, GLint v1);
typedef void (ACGLAPIENTRY* PFNGLPROGRAMUNIFORM2IVEXTPROC) (GLuint program, GLint location, GLsizei count, const GLint* value);
typedef void (ACGLAPIENTRY* PFNGLPROGRAMUNIFORM2UIEXTPROC) (GLuint program, GLint location, GLuint v0, GLuint v1);
typedef void (ACGLAPIENTRY* PFNGLPROGRAMUNIFORM2UIVEXTPROC) (GLuint program, GLint location, GLsizei count, const GLuint* value);
typedef void (ACGLAPIENTRY* PFNGLPROGRAMUNIFORM3FEXTPROC) (GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
typedef void (ACGLAPIENTRY* PFNGLPROGRAMUNIFORM3FVEXTPROC) (GLuint program, GLint location, GLsizei count, const GLfloat* value);
typedef void (ACGLAPIENTRY* PFNGLPROGRAMUNIFORM3IEXTPROC) (GLuint program, GLint location, GLint v0, GLint v1, GLint v2);
typedef void (ACGLAPIENTRY* PFNGLPROGRAMUNIFORM3IVEXTPROC) (GLuint program, GLint location, GLsizei count, const GLint* value);
typedef void (ACGLAPIENTRY* PFNGLPROGRAMUNIFORM3UIEXTPROC) (GLuint program, GLint location, GLuint v0, GLuint v1, GLuint v2);
typedef void (ACGLAPIENTRY* PFNGLPROGRAMUNIFORM3UIVEXTPROC) (GLuint program, GLint location, GLsizei count, const GLuint* value);
typedef void (ACGLAPIENTRY* PFNGLPROGRAMUNIFORM4FEXTPROC) (GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
typedef void (ACGLAPIENTRY* PFNGLPROGRAMUNIFORM4FVEXTPROC) (GLuint program, GLint location, GLsizei count, const GLfloat* value);
typedef void (ACGLAPIENTRY* PFNGLPROGRAMUNIFORM4IEXTPROC) (GLuint program, GLint location, GLint v0, GLint v1, GLint v2, GLint v3);
typedef void (ACGLAPIENTRY* PFNGLPROGRAMUNIFORM4IVEXTPROC) (GLuint program, GLint location, GLsizei count, const GLint* value);
typedef void (ACGLAPIENTRY* PFNGLPROGRAMUNIFORM4UIEXTPROC) (GLuint program, GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3);
typedef void (ACGLAPIENTRY* PFNGLPROGRAMUNIFORM4UIVEXTPROC) (GLuint program, GLint location, GLsizei count, const GLuint* value);
typedef void (ACGLAPIENTRY* PFNGLPROGRAMUNIFORMMATRIX2FVEXTPROC) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
typedef void (ACGLAPIENTRY* PFNGLPROGRAMUNIFORMMATRIX2X3FVEXTPROC) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
typedef void (ACGLAPIENTRY* PFNGLPROGRAMUNIFORMMATRIX2X4FVEXTPROC) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
typedef void (ACGLAPIENTRY* PFNGLPROGRAMUNIFORMMATRIX3FVEXTPROC) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
typedef void (ACGLAPIENTRY* PFNGLPROGRAMUNIFORMMATRIX3X2FVEXTPROC) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
typedef void (ACGLAPIENTRY* PFNGLPROGRAMUNIFORMMATRIX3X4FVEXTPROC) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
typedef void (ACGLAPIENTRY* PFNGLPROGRAMUNIFORMMATRIX4FVEXTPROC) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
typedef void (ACGLAPIENTRY* PFNGLPROGRAMUNIFORMMATRIX4X2FVEXTPROC) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
typedef void (ACGLAPIENTRY* PFNGLPROGRAMUNIFORMMATRIX4X3FVEXTPROC) (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
typedef void (ACGLAPIENTRY* PFNGLPUSHCLIENTATTRIBDEFAULTEXTPROC) (GLbitfield mask);
typedef void (ACGLAPIENTRY* PFNGLTEXTUREBUFFEREXTPROC) (GLuint texture, GLenum target, GLenum internalformat, GLuint buffer);
typedef void (ACGLAPIENTRY* PFNGLTEXTUREIMAGE1DEXTPROC) (GLuint texture, GLenum target, GLint level, GLint internalformat, GLsizei width, GLint border, GLenum format, GLenum type, const void* pixels);
typedef void (ACGLAPIENTRY* PFNGLTEXTUREIMAGE2DEXTPROC) (GLuint texture, GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const void* pixels);
typedef void (ACGLAPIENTRY* PFNGLTEXTUREIMAGE3DEXTPROC) (GLuint texture, GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const void* pixels);
typedef void (ACGLAPIENTRY* PFNGLTEXTUREPARAMETERIIVEXTPROC) (GLuint texture, GLenum target, GLenum pname, const GLint* params);
typedef void (ACGLAPIENTRY* PFNGLTEXTUREPARAMETERIUIVEXTPROC) (GLuint texture, GLenum target, GLenum pname, const GLuint* params);
typedef void (ACGLAPIENTRY* PFNGLTEXTUREPARAMETERFEXTPROC) (GLuint texture, GLenum target, GLenum pname, GLfloat param);
typedef void (ACGLAPIENTRY* PFNGLTEXTUREPARAMETERFVEXTPROC) (GLuint texture, GLenum target, GLenum pname, const GLfloat* param);
typedef void (ACGLAPIENTRY* PFNGLTEXTUREPARAMETERIEXTPROC) (GLuint texture, GLenum target, GLenum pname, GLint param);
typedef void (ACGLAPIENTRY* PFNGLTEXTUREPARAMETERIVEXTPROC) (GLuint texture, GLenum target, GLenum pname, const GLint* param);
typedef void (ACGLAPIENTRY* PFNGLTEXTURERENDERBUFFEREXTPROC) (GLuint texture, GLenum target, GLuint renderbuffer);
typedef void (ACGLAPIENTRY* PFNGLTEXTURESUBIMAGE1DEXTPROC) (GLuint texture, GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const void* pixels);
typedef void (ACGLAPIENTRY* PFNGLTEXTURESUBIMAGE2DEXTPROC) (GLuint texture, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void* pixels);
typedef void (ACGLAPIENTRY* PFNGLTEXTURESUBIMAGE3DEXTPROC) (GLuint texture, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void* pixels);
typedef GLboolean (ACGLAPIENTRY* PFNGLUNMAPNAMEDBUFFEREXTPROC) (GLuint buffer);
typedef void (ACGLAPIENTRY* PFNGLVERTEXARRAYCOLOROFFSETEXTPROC) (GLuint vaobj, GLuint buffer, GLint size, GLenum type, GLsizei stride, GLintptr offset);
typedef void (ACGLAPIENTRY* PFNGLVERTEXARRAYEDGEFLAGOFFSETEXTPROC) (GLuint vaobj, GLuint buffer, GLsizei stride, GLintptr offset);
typedef void (ACGLAPIENTRY* PFNGLVERTEXARRAYFOGCOORDOFFSETEXTPROC) (GLuint vaobj, GLuint buffer, GLenum type, GLsizei stride, GLintptr offset);
typedef void (ACGLAPIENTRY* PFNGLVERTEXARRAYINDEXOFFSETEXTPROC) (GLuint vaobj, GLuint buffer, GLenum type, GLsizei stride, GLintptr offset);
typedef void (ACGLAPIENTRY* PFNGLVERTEXARRAYMULTITEXCOORDOFFSETEXTPROC) (GLuint vaobj, GLuint buffer, GLenum texunit, GLint size, GLenum type, GLsizei stride, GLintptr offset);
typedef void (ACGLAPIENTRY* PFNGLVERTEXARRAYNORMALOFFSETEXTPROC) (GLuint vaobj, GLuint buffer, GLenum type, GLsizei stride, GLintptr offset);
typedef void (ACGLAPIENTRY* PFNGLVERTEXARRAYSECONDARYCOLOROFFSETEXTPROC) (GLuint vaobj, GLuint buffer, GLint size, GLenum type, GLsizei stride, GLintptr offset);
typedef void (ACGLAPIENTRY* PFNGLVERTEXARRAYTEXCOORDOFFSETEXTPROC) (GLuint vaobj, GLuint buffer, GLint size, GLenum type, GLsizei stride, GLintptr offset);
typedef void (ACGLAPIENTRY* PFNGLVERTEXARRAYVERTEXATTRIBIOFFSETEXTPROC) (GLuint vaobj, GLuint buffer, GLuint index, GLint size, GLenum type, GLsizei stride, GLintptr offset);
typedef void (ACGLAPIENTRY* PFNGLVERTEXARRAYVERTEXATTRIBOFFSETEXTPROC) (GLuint vaobj, GLuint buffer, GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, GLintptr offset);
typedef void (ACGLAPIENTRY* PFNGLVERTEXARRAYVERTEXOFFSETEXTPROC) (GLuint vaobj, GLuint buffer, GLint size, GLenum type, GLsizei stride, GLintptr offset);

//
// If the extension is not present, we map our emulation functions to the glew provided function pointers,
// if however there is no GLEW, we define these pointers ourself!
//

extern PFNGLBINDMULTITEXTUREEXTPROC glBindMultiTextureEXT;
extern PFNGLCHECKNAMEDFRAMEBUFFERSTATUSEXTPROC glCheckNamedFramebufferStatusEXT;
extern PFNGLCLIENTATTRIBDEFAULTEXTPROC glClientAttribDefaultEXT;
extern PFNGLCOMPRESSEDMULTITEXIMAGE1DEXTPROC glCompressedMultiTexImage1DEXT;
extern PFNGLCOMPRESSEDMULTITEXIMAGE2DEXTPROC glCompressedMultiTexImage2DEXT;
extern PFNGLCOMPRESSEDMULTITEXIMAGE3DEXTPROC glCompressedMultiTexImage3DEXT;
extern PFNGLCOMPRESSEDMULTITEXSUBIMAGE1DEXTPROC glCompressedMultiTexSubImage1DEXT;
extern PFNGLCOMPRESSEDMULTITEXSUBIMAGE2DEXTPROC glCompressedMultiTexSubImage2DEXT;
extern PFNGLCOMPRESSEDMULTITEXSUBIMAGE3DEXTPROC glCompressedMultiTexSubImage3DEXT;
extern PFNGLCOMPRESSEDTEXTUREIMAGE1DEXTPROC glCompressedTextureImage1DEXT;
extern PFNGLCOMPRESSEDTEXTUREIMAGE2DEXTPROC glCompressedTextureImage2DEXT;
extern PFNGLCOMPRESSEDTEXTUREIMAGE3DEXTPROC glCompressedTextureImage3DEXT;
extern PFNGLCOMPRESSEDTEXTURESUBIMAGE1DEXTPROC glCompressedTextureSubImage1DEXT;
extern PFNGLCOMPRESSEDTEXTURESUBIMAGE2DEXTPROC glCompressedTextureSubImage2DEXT;
extern PFNGLCOMPRESSEDTEXTURESUBIMAGE3DEXTPROC glCompressedTextureSubImage3DEXT;
extern PFNGLCOPYMULTITEXIMAGE1DEXTPROC glCopyMultiTexImage1DEXT;
extern PFNGLCOPYMULTITEXIMAGE2DEXTPROC glCopyMultiTexImage2DEXT;
extern PFNGLCOPYMULTITEXSUBIMAGE1DEXTPROC glCopyMultiTexSubImage1DEXT;
extern PFNGLCOPYMULTITEXSUBIMAGE2DEXTPROC glCopyMultiTexSubImage2DEXT;
extern PFNGLCOPYMULTITEXSUBIMAGE3DEXTPROC glCopyMultiTexSubImage3DEXT;
extern PFNGLCOPYTEXTUREIMAGE1DEXTPROC glCopyTextureImage1DEXT;
extern PFNGLCOPYTEXTUREIMAGE2DEXTPROC glCopyTextureImage2DEXT;
extern PFNGLCOPYTEXTURESUBIMAGE1DEXTPROC glCopyTextureSubImage1DEXT;
extern PFNGLCOPYTEXTURESUBIMAGE2DEXTPROC glCopyTextureSubImage2DEXT;
extern PFNGLCOPYTEXTURESUBIMAGE3DEXTPROC glCopyTextureSubImage3DEXT;
extern PFNGLDISABLECLIENTSTATEINDEXEDEXTPROC glDisableClientStateIndexedEXT;
extern PFNGLDISABLECLIENTSTATEIEXTPROC glDisableClientStateiEXT;
extern PFNGLDISABLEVERTEXARRAYATTRIBEXTPROC glDisableVertexArrayAttribEXT;
extern PFNGLDISABLEVERTEXARRAYEXTPROC glDisableVertexArrayEXT;
extern PFNGLENABLECLIENTSTATEINDEXEDEXTPROC glEnableClientStateIndexedEXT;
extern PFNGLENABLECLIENTSTATEIEXTPROC glEnableClientStateiEXT;
extern PFNGLENABLEVERTEXARRAYATTRIBEXTPROC glEnableVertexArrayAttribEXT;
extern PFNGLENABLEVERTEXARRAYEXTPROC glEnableVertexArrayEXT;
extern PFNGLFLUSHMAPPEDNAMEDBUFFERRANGEEXTPROC glFlushMappedNamedBufferRangeEXT;
extern PFNGLFRAMEBUFFERDRAWBUFFEREXTPROC glFramebufferDrawBufferEXT;
extern PFNGLFRAMEBUFFERDRAWBUFFERSEXTPROC glFramebufferDrawBuffersEXT;
extern PFNGLFRAMEBUFFERREADBUFFEREXTPROC glFramebufferReadBufferEXT;
extern PFNGLGENERATEMULTITEXMIPMAPEXTPROC glGenerateMultiTexMipmapEXT;
extern PFNGLGENERATETEXTUREMIPMAPEXTPROC glGenerateTextureMipmapEXT;
extern PFNGLGETCOMPRESSEDMULTITEXIMAGEEXTPROC glGetCompressedMultiTexImageEXT;
extern PFNGLGETCOMPRESSEDTEXTUREIMAGEEXTPROC glGetCompressedTextureImageEXT;
extern PFNGLGETDOUBLEINDEXEDVEXTPROC glGetDoubleIndexedvEXT;
extern PFNGLGETDOUBLEI_VEXTPROC glGetDoublei_vEXT;
extern PFNGLGETFLOATINDEXEDVEXTPROC glGetFloatIndexedvEXT;
extern PFNGLGETFLOATI_VEXTPROC glGetFloati_vEXT;
extern PFNGLGETFRAMEBUFFERPARAMETERIVEXTPROC glGetFramebufferParameterivEXT;
extern PFNGLGETMULTITEXENVFVEXTPROC glGetMultiTexEnvfvEXT;
extern PFNGLGETMULTITEXENVIVEXTPROC glGetMultiTexEnvivEXT;
extern PFNGLGETMULTITEXGENDVEXTPROC glGetMultiTexGendvEXT;
extern PFNGLGETMULTITEXGENFVEXTPROC glGetMultiTexGenfvEXT;
extern PFNGLGETMULTITEXGENIVEXTPROC glGetMultiTexGenivEXT;
extern PFNGLGETMULTITEXIMAGEEXTPROC glGetMultiTexImageEXT;
extern PFNGLGETMULTITEXLEVELPARAMETERFVEXTPROC glGetMultiTexLevelParameterfvEXT;
extern PFNGLGETMULTITEXLEVELPARAMETERIVEXTPROC glGetMultiTexLevelParameterivEXT;
extern PFNGLGETMULTITEXPARAMETERIIVEXTPROC glGetMultiTexParameterIivEXT;
extern PFNGLGETMULTITEXPARAMETERIUIVEXTPROC glGetMultiTexParameterIuivEXT;
extern PFNGLGETMULTITEXPARAMETERFVEXTPROC glGetMultiTexParameterfvEXT;
extern PFNGLGETMULTITEXPARAMETERIVEXTPROC glGetMultiTexParameterivEXT;
extern PFNGLGETNAMEDBUFFERPARAMETERIVEXTPROC glGetNamedBufferParameterivEXT;
extern PFNGLGETNAMEDBUFFERPOINTERVEXTPROC glGetNamedBufferPointervEXT;
extern PFNGLGETNAMEDBUFFERSUBDATAEXTPROC glGetNamedBufferSubDataEXT;
extern PFNGLGETNAMEDFRAMEBUFFERATTACHMENTPARAMETERIVEXTPROC glGetNamedFramebufferAttachmentParameterivEXT;
extern PFNGLGETNAMEDPROGRAMLOCALPARAMETERIIVEXTPROC glGetNamedProgramLocalParameterIivEXT;
extern PFNGLGETNAMEDPROGRAMLOCALPARAMETERIUIVEXTPROC glGetNamedProgramLocalParameterIuivEXT;
extern PFNGLGETNAMEDPROGRAMLOCALPARAMETERDVEXTPROC glGetNamedProgramLocalParameterdvEXT;
extern PFNGLGETNAMEDPROGRAMLOCALPARAMETERFVEXTPROC glGetNamedProgramLocalParameterfvEXT;
extern PFNGLGETNAMEDPROGRAMSTRINGEXTPROC glGetNamedProgramStringEXT;
extern PFNGLGETNAMEDPROGRAMIVEXTPROC glGetNamedProgramivEXT;
extern PFNGLGETNAMEDRENDERBUFFERPARAMETERIVEXTPROC glGetNamedRenderbufferParameterivEXT;
extern PFNGLGETPOINTERINDEXEDVEXTPROC glGetPointerIndexedvEXT;
extern PFNGLGETPOINTERI_VEXTPROC glGetPointeri_vEXT;
extern PFNGLGETTEXTUREIMAGEEXTPROC glGetTextureImageEXT;
extern PFNGLGETTEXTURELEVELPARAMETERFVEXTPROC glGetTextureLevelParameterfvEXT;
extern PFNGLGETTEXTURELEVELPARAMETERIVEXTPROC glGetTextureLevelParameterivEXT;
extern PFNGLGETTEXTUREPARAMETERIIVEXTPROC glGetTextureParameterIivEXT;
extern PFNGLGETTEXTUREPARAMETERIUIVEXTPROC glGetTextureParameterIuivEXT;
extern PFNGLGETTEXTUREPARAMETERFVEXTPROC glGetTextureParameterfvEXT;
extern PFNGLGETTEXTUREPARAMETERIVEXTPROC glGetTextureParameterivEXT;
extern PFNGLGETVERTEXARRAYINTEGERI_VEXTPROC glGetVertexArrayIntegeri_vEXT;
extern PFNGLGETVERTEXARRAYINTEGERVEXTPROC glGetVertexArrayIntegervEXT;
extern PFNGLGETVERTEXARRAYPOINTERI_VEXTPROC glGetVertexArrayPointeri_vEXT;
extern PFNGLGETVERTEXARRAYPOINTERVEXTPROC glGetVertexArrayPointervEXT;
extern PFNGLMAPNAMEDBUFFEREXTPROC glMapNamedBufferEXT;
extern PFNGLMAPNAMEDBUFFERRANGEEXTPROC glMapNamedBufferRangeEXT;
extern PFNGLMATRIXFRUSTUMEXTPROC glMatrixFrustumEXT;
extern PFNGLMATRIXLOADIDENTITYEXTPROC glMatrixLoadIdentityEXT;
extern PFNGLMATRIXLOADTRANSPOSEDEXTPROC glMatrixLoadTransposedEXT;
extern PFNGLMATRIXLOADTRANSPOSEFEXTPROC glMatrixLoadTransposefEXT;
extern PFNGLMATRIXLOADDEXTPROC glMatrixLoaddEXT;
extern PFNGLMATRIXLOADFEXTPROC glMatrixLoadfEXT;
extern PFNGLMATRIXMULTTRANSPOSEDEXTPROC glMatrixMultTransposedEXT;
extern PFNGLMATRIXMULTTRANSPOSEFEXTPROC glMatrixMultTransposefEXT;
extern PFNGLMATRIXMULTDEXTPROC glMatrixMultdEXT;
extern PFNGLMATRIXMULTFEXTPROC glMatrixMultfEXT;
extern PFNGLMATRIXORTHOEXTPROC glMatrixOrthoEXT;
extern PFNGLMATRIXPOPEXTPROC glMatrixPopEXT;
extern PFNGLMATRIXPUSHEXTPROC glMatrixPushEXT;
extern PFNGLMATRIXROTATEDEXTPROC glMatrixRotatedEXT;
extern PFNGLMATRIXROTATEFEXTPROC glMatrixRotatefEXT;
extern PFNGLMATRIXSCALEDEXTPROC glMatrixScaledEXT;
extern PFNGLMATRIXSCALEFEXTPROC glMatrixScalefEXT;
extern PFNGLMATRIXTRANSLATEDEXTPROC glMatrixTranslatedEXT;
extern PFNGLMATRIXTRANSLATEFEXTPROC glMatrixTranslatefEXT;
extern PFNGLMULTITEXBUFFEREXTPROC glMultiTexBufferEXT;
extern PFNGLMULTITEXCOORDPOINTEREXTPROC glMultiTexCoordPointerEXT;
extern PFNGLMULTITEXENVFEXTPROC glMultiTexEnvfEXT;
extern PFNGLMULTITEXENVFVEXTPROC glMultiTexEnvfvEXT;
extern PFNGLMULTITEXENVIEXTPROC glMultiTexEnviEXT;
extern PFNGLMULTITEXENVIVEXTPROC glMultiTexEnvivEXT;
extern PFNGLMULTITEXGENDEXTPROC glMultiTexGendEXT;
extern PFNGLMULTITEXGENDVEXTPROC glMultiTexGendvEXT;
extern PFNGLMULTITEXGENFEXTPROC glMultiTexGenfEXT;
extern PFNGLMULTITEXGENFVEXTPROC glMultiTexGenfvEXT;
extern PFNGLMULTITEXGENIEXTPROC glMultiTexGeniEXT;
extern PFNGLMULTITEXGENIVEXTPROC glMultiTexGenivEXT;
extern PFNGLMULTITEXIMAGE1DEXTPROC glMultiTexImage1DEXT;
extern PFNGLMULTITEXIMAGE2DEXTPROC glMultiTexImage2DEXT;
extern PFNGLMULTITEXIMAGE3DEXTPROC glMultiTexImage3DEXT;
extern PFNGLMULTITEXPARAMETERIIVEXTPROC glMultiTexParameterIivEXT;
extern PFNGLMULTITEXPARAMETERIUIVEXTPROC glMultiTexParameterIuivEXT;
extern PFNGLMULTITEXPARAMETERFEXTPROC glMultiTexParameterfEXT;
extern PFNGLMULTITEXPARAMETERFVEXTPROC glMultiTexParameterfvEXT;
extern PFNGLMULTITEXPARAMETERIEXTPROC glMultiTexParameteriEXT;
extern PFNGLMULTITEXPARAMETERIVEXTPROC glMultiTexParameterivEXT;
extern PFNGLMULTITEXRENDERBUFFEREXTPROC glMultiTexRenderbufferEXT;
extern PFNGLMULTITEXSUBIMAGE1DEXTPROC glMultiTexSubImage1DEXT;
extern PFNGLMULTITEXSUBIMAGE2DEXTPROC glMultiTexSubImage2DEXT;
extern PFNGLMULTITEXSUBIMAGE3DEXTPROC glMultiTexSubImage3DEXT;
extern PFNGLNAMEDBUFFERDATAEXTPROC glNamedBufferDataEXT;
extern PFNGLNAMEDBUFFERSUBDATAEXTPROC glNamedBufferSubDataEXT;
extern PFNGLNAMEDCOPYBUFFERSUBDATAEXTPROC glNamedCopyBufferSubDataEXT;
extern PFNGLNAMEDFRAMEBUFFERRENDERBUFFEREXTPROC glNamedFramebufferRenderbufferEXT;
extern PFNGLNAMEDFRAMEBUFFERTEXTURE1DEXTPROC glNamedFramebufferTexture1DEXT;
extern PFNGLNAMEDFRAMEBUFFERTEXTURE2DEXTPROC glNamedFramebufferTexture2DEXT;
extern PFNGLNAMEDFRAMEBUFFERTEXTURE3DEXTPROC glNamedFramebufferTexture3DEXT;
extern PFNGLNAMEDFRAMEBUFFERTEXTUREEXTPROC glNamedFramebufferTextureEXT;
extern PFNGLNAMEDFRAMEBUFFERTEXTUREFACEEXTPROC glNamedFramebufferTextureFaceEXT;
extern PFNGLNAMEDFRAMEBUFFERTEXTURELAYEREXTPROC glNamedFramebufferTextureLayerEXT;
extern PFNGLNAMEDPROGRAMLOCALPARAMETER4DEXTPROC glNamedProgramLocalParameter4dEXT;
extern PFNGLNAMEDPROGRAMLOCALPARAMETER4DVEXTPROC glNamedProgramLocalParameter4dvEXT;
extern PFNGLNAMEDPROGRAMLOCALPARAMETER4FEXTPROC glNamedProgramLocalParameter4fEXT;
extern PFNGLNAMEDPROGRAMLOCALPARAMETER4FVEXTPROC glNamedProgramLocalParameter4fvEXT;
extern PFNGLNAMEDPROGRAMLOCALPARAMETERI4IEXTPROC glNamedProgramLocalParameterI4iEXT;
extern PFNGLNAMEDPROGRAMLOCALPARAMETERI4IVEXTPROC glNamedProgramLocalParameterI4ivEXT;
extern PFNGLNAMEDPROGRAMLOCALPARAMETERI4UIEXTPROC glNamedProgramLocalParameterI4uiEXT;
extern PFNGLNAMEDPROGRAMLOCALPARAMETERI4UIVEXTPROC glNamedProgramLocalParameterI4uivEXT;
extern PFNGLNAMEDPROGRAMLOCALPARAMETERS4FVEXTPROC glNamedProgramLocalParameters4fvEXT;
extern PFNGLNAMEDPROGRAMLOCALPARAMETERSI4IVEXTPROC glNamedProgramLocalParametersI4ivEXT;
extern PFNGLNAMEDPROGRAMLOCALPARAMETERSI4UIVEXTPROC glNamedProgramLocalParametersI4uivEXT;
extern PFNGLNAMEDPROGRAMSTRINGEXTPROC glNamedProgramStringEXT;
extern PFNGLNAMEDRENDERBUFFERSTORAGEEXTPROC glNamedRenderbufferStorageEXT;
extern PFNGLNAMEDRENDERBUFFERSTORAGEMULTISAMPLECOVERAGEEXTPROC glNamedRenderbufferStorageMultisampleCoverageEXT;
extern PFNGLNAMEDRENDERBUFFERSTORAGEMULTISAMPLEEXTPROC glNamedRenderbufferStorageMultisampleEXT;
extern PFNGLPROGRAMUNIFORM1FEXTPROC glProgramUniform1fEXT;
extern PFNGLPROGRAMUNIFORM1FVEXTPROC glProgramUniform1fvEXT;
extern PFNGLPROGRAMUNIFORM1IEXTPROC glProgramUniform1iEXT;
extern PFNGLPROGRAMUNIFORM1IVEXTPROC glProgramUniform1ivEXT;
extern PFNGLPROGRAMUNIFORM1UIEXTPROC glProgramUniform1uiEXT;
extern PFNGLPROGRAMUNIFORM1UIVEXTPROC glProgramUniform1uivEXT;
extern PFNGLPROGRAMUNIFORM2FEXTPROC glProgramUniform2fEXT;
extern PFNGLPROGRAMUNIFORM2FVEXTPROC glProgramUniform2fvEXT;
extern PFNGLPROGRAMUNIFORM2IEXTPROC glProgramUniform2iEXT;
extern PFNGLPROGRAMUNIFORM2IVEXTPROC glProgramUniform2ivEXT;
extern PFNGLPROGRAMUNIFORM2UIEXTPROC glProgramUniform2uiEXT;
extern PFNGLPROGRAMUNIFORM2UIVEXTPROC glProgramUniform2uivEXT;
extern PFNGLPROGRAMUNIFORM3FEXTPROC glProgramUniform3fEXT;
extern PFNGLPROGRAMUNIFORM3FVEXTPROC glProgramUniform3fvEXT;
extern PFNGLPROGRAMUNIFORM3IEXTPROC glProgramUniform3iEXT;
extern PFNGLPROGRAMUNIFORM3IVEXTPROC glProgramUniform3ivEXT;
extern PFNGLPROGRAMUNIFORM3UIEXTPROC glProgramUniform3uiEXT;
extern PFNGLPROGRAMUNIFORM3UIVEXTPROC glProgramUniform3uivEXT;
extern PFNGLPROGRAMUNIFORM4FEXTPROC glProgramUniform4fEXT;
extern PFNGLPROGRAMUNIFORM4FVEXTPROC glProgramUniform4fvEXT;
extern PFNGLPROGRAMUNIFORM4IEXTPROC glProgramUniform4iEXT;
extern PFNGLPROGRAMUNIFORM4IVEXTPROC glProgramUniform4ivEXT;
extern PFNGLPROGRAMUNIFORM4UIEXTPROC glProgramUniform4uiEXT;
extern PFNGLPROGRAMUNIFORM4UIVEXTPROC glProgramUniform4uivEXT;
extern PFNGLPROGRAMUNIFORMMATRIX2FVEXTPROC glProgramUniformMatrix2fvEXT;
extern PFNGLPROGRAMUNIFORMMATRIX2X3FVEXTPROC glProgramUniformMatrix2x3fvEXT;
extern PFNGLPROGRAMUNIFORMMATRIX2X4FVEXTPROC glProgramUniformMatrix2x4fvEXT;
extern PFNGLPROGRAMUNIFORMMATRIX3FVEXTPROC glProgramUniformMatrix3fvEXT;
extern PFNGLPROGRAMUNIFORMMATRIX3X2FVEXTPROC glProgramUniformMatrix3x2fvEXT;
extern PFNGLPROGRAMUNIFORMMATRIX3X4FVEXTPROC glProgramUniformMatrix3x4fvEXT;
extern PFNGLPROGRAMUNIFORMMATRIX4FVEXTPROC glProgramUniformMatrix4fvEXT;
extern PFNGLPROGRAMUNIFORMMATRIX4X2FVEXTPROC glProgramUniformMatrix4x2fvEXT;
extern PFNGLPROGRAMUNIFORMMATRIX4X3FVEXTPROC glProgramUniformMatrix4x3fvEXT;
extern PFNGLPUSHCLIENTATTRIBDEFAULTEXTPROC glPushClientAttribDefaultEXT;
extern PFNGLTEXTUREBUFFEREXTPROC glTextureBufferEXT;
extern PFNGLTEXTUREIMAGE1DEXTPROC glTextureImage1DEXT;
extern PFNGLTEXTUREIMAGE2DEXTPROC glTextureImage2DEXT;
extern PFNGLTEXTUREIMAGE3DEXTPROC glTextureImage3DEXT;
extern PFNGLTEXTUREPARAMETERIIVEXTPROC glTextureParameterIivEXT;
extern PFNGLTEXTUREPARAMETERIUIVEXTPROC glTextureParameterIuivEXT;
extern PFNGLTEXTUREPARAMETERFEXTPROC glTextureParameterfEXT;
extern PFNGLTEXTUREPARAMETERFVEXTPROC glTextureParameterfvEXT;
extern PFNGLTEXTUREPARAMETERIEXTPROC glTextureParameteriEXT;
extern PFNGLTEXTUREPARAMETERIVEXTPROC glTextureParameterivEXT;
extern PFNGLTEXTURERENDERBUFFEREXTPROC glTextureRenderbufferEXT;
extern PFNGLTEXTURESUBIMAGE1DEXTPROC glTextureSubImage1DEXT;
extern PFNGLTEXTURESUBIMAGE2DEXTPROC glTextureSubImage2DEXT;
extern PFNGLTEXTURESUBIMAGE3DEXTPROC glTextureSubImage3DEXT;
extern PFNGLUNMAPNAMEDBUFFEREXTPROC glUnmapNamedBufferEXT;
extern PFNGLVERTEXARRAYCOLOROFFSETEXTPROC glVertexArrayColorOffsetEXT;
extern PFNGLVERTEXARRAYEDGEFLAGOFFSETEXTPROC glVertexArrayEdgeFlagOffsetEXT;
extern PFNGLVERTEXARRAYFOGCOORDOFFSETEXTPROC glVertexArrayFogCoordOffsetEXT;
extern PFNGLVERTEXARRAYINDEXOFFSETEXTPROC glVertexArrayIndexOffsetEXT;
extern PFNGLVERTEXARRAYMULTITEXCOORDOFFSETEXTPROC glVertexArrayMultiTexCoordOffsetEXT;
extern PFNGLVERTEXARRAYNORMALOFFSETEXTPROC glVertexArrayNormalOffsetEXT;
extern PFNGLVERTEXARRAYSECONDARYCOLOROFFSETEXTPROC glVertexArraySecondaryColorOffsetEXT;
extern PFNGLVERTEXARRAYTEXCOORDOFFSETEXTPROC glVertexArrayTexCoordOffsetEXT;
extern PFNGLVERTEXARRAYVERTEXATTRIBIOFFSETEXTPROC glVertexArrayVertexAttribIOffsetEXT;
extern PFNGLVERTEXARRAYVERTEXATTRIBOFFSETEXTPROC glVertexArrayVertexAttribOffsetEXT;
extern PFNGLVERTEXARRAYVERTEXOFFSETEXTPROC glVertexArrayVertexOffsetEXT;

extern PFNGLPROGRAMUNIFORM1FEXTPROC glProgramUniform1f;
extern PFNGLPROGRAMUNIFORM1FVEXTPROC glProgramUniform1fv;
extern PFNGLPROGRAMUNIFORM1IEXTPROC glProgramUniform1i;
extern PFNGLPROGRAMUNIFORM1IVEXTPROC glProgramUniform1iv;
extern PFNGLPROGRAMUNIFORM1UIEXTPROC glProgramUniform1ui;
extern PFNGLPROGRAMUNIFORM1UIVEXTPROC glProgramUniform1uiv;
extern PFNGLPROGRAMUNIFORM2FEXTPROC glProgramUniform2f;
extern PFNGLPROGRAMUNIFORM2FVEXTPROC glProgramUniform2fv;
extern PFNGLPROGRAMUNIFORM2IEXTPROC glProgramUniform2i;
extern PFNGLPROGRAMUNIFORM2IVEXTPROC glProgramUniform2iv;
extern PFNGLPROGRAMUNIFORM2UIEXTPROC glProgramUniform2ui;
extern PFNGLPROGRAMUNIFORM2UIVEXTPROC glProgramUniform2uiv;
extern PFNGLPROGRAMUNIFORM3FEXTPROC glProgramUniform3f;
extern PFNGLPROGRAMUNIFORM3FVEXTPROC glProgramUniform3fv;
extern PFNGLPROGRAMUNIFORM3IEXTPROC glProgramUniform3i;
extern PFNGLPROGRAMUNIFORM3IVEXTPROC glProgramUniform3iv;
extern PFNGLPROGRAMUNIFORM3UIEXTPROC glProgramUniform3ui;
extern PFNGLPROGRAMUNIFORM3UIVEXTPROC glProgramUniform3uiv;
extern PFNGLPROGRAMUNIFORM4FEXTPROC glProgramUniform4f;
extern PFNGLPROGRAMUNIFORM4FVEXTPROC glProgramUniform4fv;
extern PFNGLPROGRAMUNIFORM4IEXTPROC glProgramUniform4i;
extern PFNGLPROGRAMUNIFORM4IVEXTPROC glProgramUniform4iv;
extern PFNGLPROGRAMUNIFORM4UIEXTPROC glProgramUniform4ui;
extern PFNGLPROGRAMUNIFORM4UIVEXTPROC glProgramUniform4uiv;
extern PFNGLPROGRAMUNIFORMMATRIX2FVEXTPROC glProgramUniformMatrix2fv;
extern PFNGLPROGRAMUNIFORMMATRIX2X3FVEXTPROC glProgramUniformMatrix2x3fv;
extern PFNGLPROGRAMUNIFORMMATRIX2X4FVEXTPROC glProgramUniformMatrix2x4fv;
extern PFNGLPROGRAMUNIFORMMATRIX3FVEXTPROC glProgramUniformMatrix3fv;
extern PFNGLPROGRAMUNIFORMMATRIX3X2FVEXTPROC glProgramUniformMatrix3x2fv;
extern PFNGLPROGRAMUNIFORMMATRIX3X4FVEXTPROC glProgramUniformMatrix3x4fv;
extern PFNGLPROGRAMUNIFORMMATRIX4FVEXTPROC glProgramUniformMatrix4fv;
extern PFNGLPROGRAMUNIFORMMATRIX4X2FVEXTPROC glProgramUniformMatrix4x2fv;
extern PFNGLPROGRAMUNIFORMMATRIX4X3FVEXTPROC glProgramUniformMatrix4x3fv;
#endif


namespace ACGL{
namespace OpenGL{

//
// Emulation functions
//
void ACGLAPIENTRY glBindMultiTextureEMULATION (GLenum texunit, GLenum target, GLuint texture);
GLenum ACGLAPIENTRY glCheckNamedFramebufferStatusEMULATION (GLuint framebuffer, GLenum target);
void ACGLAPIENTRY glClientAttribDefaultEMULATION (GLbitfield mask);
void ACGLAPIENTRY glCompressedMultiTexImage1DEMULATION (GLenum texunit, GLenum target, GLint level, GLenum internalformat, GLsizei width, GLint border, GLsizei imageSize, const void* data);
void ACGLAPIENTRY glCompressedMultiTexImage2DEMULATION (GLenum texunit, GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const void* data);
void ACGLAPIENTRY glCompressedMultiTexImage3DEMULATION (GLenum texunit, GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, const void* data);
void ACGLAPIENTRY glCompressedMultiTexSubImage1DEMULATION (GLenum texunit, GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, const void* data);
void ACGLAPIENTRY glCompressedMultiTexSubImage2DEMULATION (GLenum texunit, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const void* data);
void ACGLAPIENTRY glCompressedMultiTexSubImage3DEMULATION (GLenum texunit, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const void* data);
void ACGLAPIENTRY glCompressedTextureImage1DEMULATION (GLuint texture, GLenum target, GLint level, GLenum internalformat, GLsizei width, GLint border, GLsizei imageSize, const void* data);
void ACGLAPIENTRY glCompressedTextureImage2DEMULATION (GLuint texture, GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const void* data);
void ACGLAPIENTRY glCompressedTextureImage3DEMULATION (GLuint texture, GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, const void* data);
void ACGLAPIENTRY glCompressedTextureSubImage1DEMULATION (GLuint texture, GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, const void* data);
void ACGLAPIENTRY glCompressedTextureSubImage2DEMULATION (GLuint texture, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const void* data);
void ACGLAPIENTRY glCompressedTextureSubImage3DEMULATION (GLuint texture, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const void* data);
void ACGLAPIENTRY glCopyMultiTexImage1DEMULATION (GLenum texunit, GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLint border);
void ACGLAPIENTRY glCopyMultiTexImage2DEMULATION (GLenum texunit, GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border);
void ACGLAPIENTRY glCopyMultiTexSubImage1DEMULATION (GLenum texunit, GLenum target, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width);
void ACGLAPIENTRY glCopyMultiTexSubImage2DEMULATION (GLenum texunit, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height);
void ACGLAPIENTRY glCopyMultiTexSubImage3DEMULATION (GLenum texunit, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height);
void ACGLAPIENTRY glCopyTextureImage1DEMULATION (GLuint texture, GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLint border);
void ACGLAPIENTRY glCopyTextureImage2DEMULATION (GLuint texture, GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border);
void ACGLAPIENTRY glCopyTextureSubImage1DEMULATION (GLuint texture, GLenum target, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width);
void ACGLAPIENTRY glCopyTextureSubImage2DEMULATION (GLuint texture, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height);
void ACGLAPIENTRY glCopyTextureSubImage3DEMULATION (GLuint texture, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height);
void ACGLAPIENTRY glDisableVertexArrayAttribEMULATION (GLuint vaobj, GLuint index);
void ACGLAPIENTRY glDisableVertexArrayEMULATION (GLuint vaobj, GLenum array);
void ACGLAPIENTRY glEnableVertexArrayAttribEMULATION (GLuint vaobj, GLuint index);
void ACGLAPIENTRY glEnableVertexArrayEMULATION (GLuint vaobj, GLenum array);
void ACGLAPIENTRY glFlushMappedNamedBufferRangeEMULATION (GLuint buffer, GLintptr offset, GLsizeiptr length);
void ACGLAPIENTRY glFramebufferDrawBufferEMULATION (GLuint framebuffer, GLenum mode);
void ACGLAPIENTRY glFramebufferDrawBuffersEMULATION (GLuint framebuffer, GLsizei n, const GLenum* bufs);
void ACGLAPIENTRY glFramebufferReadBufferEMULATION (GLuint framebuffer, GLenum mode);
void ACGLAPIENTRY glGenerateMultiTexMipmapEMULATION (GLenum texunit, GLenum target);
void ACGLAPIENTRY glGenerateTextureMipmapEMULATION (GLuint texture, GLenum target);
void ACGLAPIENTRY glGetCompressedMultiTexImageEMULATION (GLenum texunit, GLenum target, GLint level, void* img);
void ACGLAPIENTRY glGetCompressedTextureImageEMULATION (GLuint texture, GLenum target, GLint level, void* img);
void ACGLAPIENTRY glGetDoubleIndexedvEMULATION (GLenum target, GLuint index, GLdouble* params);
void ACGLAPIENTRY glGetDoublei_vEMULATION (GLenum pname, GLuint index, GLdouble* params);
void ACGLAPIENTRY glGetFloatIndexedvEMULATION (GLenum target, GLuint index, GLfloat* params);
void ACGLAPIENTRY glGetFloati_vEMULATION (GLenum pname, GLuint index, GLfloat* params);
void ACGLAPIENTRY glGetFramebufferParameterivEMULATION (GLuint framebuffer, GLenum pname, GLint* param);
void ACGLAPIENTRY glGetMultiTexImageEMULATION (GLenum texunit, GLenum target, GLint level, GLenum format, GLenum type, void* pixels);
void ACGLAPIENTRY glGetMultiTexLevelParameterfvEMULATION (GLenum texunit, GLenum target, GLint level, GLenum pname, GLfloat* params);
void ACGLAPIENTRY glGetMultiTexLevelParameterivEMULATION (GLenum texunit, GLenum target, GLint level, GLenum pname, GLint* params);
void ACGLAPIENTRY glGetMultiTexParameterIivEMULATION (GLenum texunit, GLenum target, GLenum pname, GLint* params);
void ACGLAPIENTRY glGetMultiTexParameterIuivEMULATION (GLenum texunit, GLenum target, GLenum pname, GLuint* params);
void ACGLAPIENTRY glGetMultiTexParameterfvEMULATION (GLenum texunit, GLenum target, GLenum pname, GLfloat* params);
void ACGLAPIENTRY glGetMultiTexParameterivEMULATION (GLenum texunit, GLenum target, GLenum pname, GLint* params);
void ACGLAPIENTRY glGetNamedBufferParameterivEMULATION (GLuint buffer, GLenum pname, GLint* params);
void ACGLAPIENTRY glGetNamedBufferPointervEMULATION (GLuint buffer, GLenum pname, void** params);
void ACGLAPIENTRY glGetNamedBufferSubDataEMULATION (GLuint buffer, GLintptr offset, GLsizeiptr size, void* data);
void ACGLAPIENTRY glGetNamedFramebufferAttachmentParameterivEMULATION (GLuint framebuffer, GLenum attachment, GLenum pname, GLint* params);
void ACGLAPIENTRY glGetNamedProgramLocalParameterIivEMULATION (GLuint program, GLenum target, GLuint index, GLint* params);
void ACGLAPIENTRY glGetNamedProgramLocalParameterIuivEMULATION (GLuint program, GLenum target, GLuint index, GLuint* params);
void ACGLAPIENTRY glGetNamedProgramLocalParameterdvEMULATION (GLuint program, GLenum target, GLuint index, GLdouble* params);
void ACGLAPIENTRY glGetNamedProgramLocalParameterfvEMULATION (GLuint program, GLenum target, GLuint index, GLfloat* params);
void ACGLAPIENTRY glGetNamedProgramStringEMULATION (GLuint program, GLenum target, GLenum pname, void* string);
void ACGLAPIENTRY glGetNamedProgramivEMULATION (GLuint program, GLenum target, GLenum pname, GLint* params);
void ACGLAPIENTRY glGetNamedRenderbufferParameterivEMULATION (GLuint renderbuffer, GLenum pname, GLint* params);
void ACGLAPIENTRY glGetPointerIndexedvEMULATION (GLenum target, GLuint index, GLvoid** params);
void ACGLAPIENTRY glGetPointeri_vEMULATION (GLenum pname, GLuint index, GLvoid** params);
void ACGLAPIENTRY glGetTextureImageEMULATION (GLuint texture, GLenum target, GLint level, GLenum format, GLenum type, void* pixels);
void ACGLAPIENTRY glGetTextureLevelParameterfvEMULATION (GLuint texture, GLenum target, GLint level, GLenum pname, GLfloat* params);
void ACGLAPIENTRY glGetTextureLevelParameterivEMULATION (GLuint texture, GLenum target, GLint level, GLenum pname, GLint* params);
void ACGLAPIENTRY glGetTextureParameterIivEMULATION (GLuint texture, GLenum target, GLenum pname, GLint* params);
void ACGLAPIENTRY glGetTextureParameterIuivEMULATION (GLuint texture, GLenum target, GLenum pname, GLuint* params);
void ACGLAPIENTRY glGetTextureParameterfvEMULATION (GLuint texture, GLenum target, GLenum pname, GLfloat* params);
void ACGLAPIENTRY glGetTextureParameterivEMULATION (GLuint texture, GLenum target, GLenum pname, GLint* params);
void ACGLAPIENTRY glGetVertexArrayIntegeri_vEMULATION (GLuint vaobj, GLuint index, GLenum pname, GLint* param);
void ACGLAPIENTRY glGetVertexArrayIntegervEMULATION (GLuint vaobj, GLenum pname, GLint* param);
void ACGLAPIENTRY glGetVertexArrayPointeri_vEMULATION (GLuint vaobj, GLuint index, GLenum pname, GLvoid** param);
void ACGLAPIENTRY glGetVertexArrayPointervEMULATION (GLuint vaobj, GLenum pname, GLvoid** param);
GLvoid * ACGLAPIENTRY glMapNamedBufferEMULATION (GLuint buffer, GLenum access);
GLvoid * ACGLAPIENTRY glMapNamedBufferRangeEMULATION (GLuint buffer, GLintptr offset, GLsizeiptr length, GLbitfield access);
void ACGLAPIENTRY glMultiTexBufferEMULATION (GLenum texunit, GLenum target, GLenum internalformat, GLuint buffer);
void ACGLAPIENTRY glMultiTexImage1DEMULATION (GLenum texunit, GLenum target, GLint level, GLint internalformat, GLsizei width, GLint border, GLenum format, GLenum type, const void* pixels);
void ACGLAPIENTRY glMultiTexImage2DEMULATION (GLenum texunit, GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const void* pixels);
void ACGLAPIENTRY glMultiTexImage3DEMULATION (GLenum texunit, GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const void* pixels);
void ACGLAPIENTRY glMultiTexParameterIivEMULATION (GLenum texunit, GLenum target, GLenum pname, const GLint* params);
void ACGLAPIENTRY glMultiTexParameterIuivEMULATION (GLenum texunit, GLenum target, GLenum pname, const GLuint* params);
void ACGLAPIENTRY glMultiTexParameterfEMULATION (GLenum texunit, GLenum target, GLenum pname, GLfloat param);
void ACGLAPIENTRY glMultiTexParameterfvEMULATION (GLenum texunit, GLenum target, GLenum pname, const GLfloat* param);
void ACGLAPIENTRY glMultiTexParameteriEMULATION (GLenum texunit, GLenum target, GLenum pname, GLint param);
void ACGLAPIENTRY glMultiTexParameterivEMULATION (GLenum texunit, GLenum target, GLenum pname, const GLint* param);
void ACGLAPIENTRY glMultiTexRenderbufferEMULATION (GLenum texunit, GLenum target, GLuint renderbuffer);
void ACGLAPIENTRY glMultiTexSubImage1DEMULATION (GLenum texunit, GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const void* pixels);
void ACGLAPIENTRY glMultiTexSubImage2DEMULATION (GLenum texunit, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void* pixels);
void ACGLAPIENTRY glMultiTexSubImage3DEMULATION (GLenum texunit, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void* pixels);
void ACGLAPIENTRY glNamedBufferDataEMULATION (GLuint buffer, GLsizeiptr size, const void* data, GLenum usage);
void ACGLAPIENTRY glNamedBufferSubDataEMULATION (GLuint buffer, GLintptr offset, GLsizeiptr size, const void* data);
void ACGLAPIENTRY glNamedCopyBufferSubDataEMULATION (GLuint readBuffer, GLuint writeBuffer, GLintptr readOffset, GLintptr writeOffset, GLsizeiptr size);
void ACGLAPIENTRY glNamedFramebufferRenderbufferEMULATION (GLuint framebuffer, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);
void ACGLAPIENTRY glNamedFramebufferTexture1DEMULATION (GLuint framebuffer, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
void ACGLAPIENTRY glNamedFramebufferTexture2DEMULATION (GLuint framebuffer, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
void ACGLAPIENTRY glNamedFramebufferTexture3DEMULATION (GLuint framebuffer, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLint zoffset);
void ACGLAPIENTRY glNamedFramebufferTextureEMULATION (GLuint framebuffer, GLenum attachment, GLuint texture, GLint level);
void ACGLAPIENTRY glNamedFramebufferTextureFaceEMULATION (GLuint framebuffer, GLenum attachment, GLuint texture, GLint level, GLenum face);
void ACGLAPIENTRY glNamedFramebufferTextureLayerEMULATION (GLuint framebuffer, GLenum attachment, GLuint texture, GLint level, GLint layer);
void ACGLAPIENTRY glNamedProgramLocalParameter4dEMULATION (GLuint program, GLenum target, GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w);
void ACGLAPIENTRY glNamedProgramLocalParameter4dvEMULATION (GLuint program, GLenum target, GLuint index, const GLdouble* params);
void ACGLAPIENTRY glNamedProgramLocalParameter4fEMULATION (GLuint program, GLenum target, GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
void ACGLAPIENTRY glNamedProgramLocalParameter4fvEMULATION (GLuint program, GLenum target, GLuint index, const GLfloat* params);
void ACGLAPIENTRY glNamedProgramLocalParameterI4iEMULATION (GLuint program, GLenum target, GLuint index, GLint x, GLint y, GLint z, GLint w);
void ACGLAPIENTRY glNamedProgramLocalParameterI4ivEMULATION (GLuint program, GLenum target, GLuint index, const GLint* params);
void ACGLAPIENTRY glNamedProgramLocalParameterI4uiEMULATION (GLuint program, GLenum target, GLuint index, GLuint x, GLuint y, GLuint z, GLuint w);
void ACGLAPIENTRY glNamedProgramLocalParameterI4uivEMULATION (GLuint program, GLenum target, GLuint index, const GLuint* params);
void ACGLAPIENTRY glNamedProgramLocalParameters4fvEMULATION (GLuint program, GLenum target, GLuint index, GLsizei count, const GLfloat* params);
void ACGLAPIENTRY glNamedProgramLocalParametersI4ivEMULATION (GLuint program, GLenum target, GLuint index, GLsizei count, const GLint* params);
void ACGLAPIENTRY glNamedProgramLocalParametersI4uivEMULATION (GLuint program, GLenum target, GLuint index, GLsizei count, const GLuint* params);
void ACGLAPIENTRY glNamedProgramStringEMULATION (GLuint program, GLenum target, GLenum format, GLsizei len, const void* string);
void ACGLAPIENTRY glNamedRenderbufferStorageEMULATION (GLuint renderbuffer, GLenum internalformat, GLsizei width, GLsizei height);
void ACGLAPIENTRY glNamedRenderbufferStorageMultisampleCoverageEMULATION (GLuint renderbuffer, GLsizei coverageSamples, GLsizei colorSamples, GLenum internalformat, GLsizei width, GLsizei height);
void ACGLAPIENTRY glNamedRenderbufferStorageMultisampleEMULATION (GLuint renderbuffer, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height);
void ACGLAPIENTRY glProgramUniform1fEMULATION (GLuint program, GLint location, GLfloat v0);
void ACGLAPIENTRY glProgramUniform1fvEMULATION (GLuint program, GLint location, GLsizei count, const GLfloat* value);
void ACGLAPIENTRY glProgramUniform1iEMULATION (GLuint program, GLint location, GLint v0);
void ACGLAPIENTRY glProgramUniform1ivEMULATION (GLuint program, GLint location, GLsizei count, const GLint* value);
void ACGLAPIENTRY glProgramUniform1uiEMULATION (GLuint program, GLint location, GLuint v0);
void ACGLAPIENTRY glProgramUniform1uivEMULATION (GLuint program, GLint location, GLsizei count, const GLuint* value);
void ACGLAPIENTRY glProgramUniform2fEMULATION (GLuint program, GLint location, GLfloat v0, GLfloat v1);
void ACGLAPIENTRY glProgramUniform2fvEMULATION (GLuint program, GLint location, GLsizei count, const GLfloat* value);
void ACGLAPIENTRY glProgramUniform2iEMULATION (GLuint program, GLint location, GLint v0, GLint v1);
void ACGLAPIENTRY glProgramUniform2ivEMULATION (GLuint program, GLint location, GLsizei count, const GLint* value);
void ACGLAPIENTRY glProgramUniform2uiEMULATION (GLuint program, GLint location, GLuint v0, GLuint v1);
void ACGLAPIENTRY glProgramUniform2uivEMULATION (GLuint program, GLint location, GLsizei count, const GLuint* value);
void ACGLAPIENTRY glProgramUniform3fEMULATION (GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
void ACGLAPIENTRY glProgramUniform3fvEMULATION (GLuint program, GLint location, GLsizei count, const GLfloat* value);
void ACGLAPIENTRY glProgramUniform3iEMULATION (GLuint program, GLint location, GLint v0, GLint v1, GLint v2);
void ACGLAPIENTRY glProgramUniform3ivEMULATION (GLuint program, GLint location, GLsizei count, const GLint* value);
void ACGLAPIENTRY glProgramUniform3uiEMULATION (GLuint program, GLint location, GLuint v0, GLuint v1, GLuint v2);
void ACGLAPIENTRY glProgramUniform3uivEMULATION (GLuint program, GLint location, GLsizei count, const GLuint* value);
void ACGLAPIENTRY glProgramUniform4fEMULATION (GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
void ACGLAPIENTRY glProgramUniform4fvEMULATION (GLuint program, GLint location, GLsizei count, const GLfloat* value);
void ACGLAPIENTRY glProgramUniform4iEMULATION (GLuint program, GLint location, GLint v0, GLint v1, GLint v2, GLint v3);
void ACGLAPIENTRY glProgramUniform4ivEMULATION (GLuint program, GLint location, GLsizei count, const GLint* value);
void ACGLAPIENTRY glProgramUniform4uiEMULATION (GLuint program, GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3);
void ACGLAPIENTRY glProgramUniform4uivEMULATION (GLuint program, GLint location, GLsizei count, const GLuint* value);
void ACGLAPIENTRY glProgramUniformMatrix2fvEMULATION (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
void ACGLAPIENTRY glProgramUniformMatrix2x3fvEMULATION (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
void ACGLAPIENTRY glProgramUniformMatrix2x4fvEMULATION (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
void ACGLAPIENTRY glProgramUniformMatrix3fvEMULATION (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
void ACGLAPIENTRY glProgramUniformMatrix3x2fvEMULATION (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
void ACGLAPIENTRY glProgramUniformMatrix3x4fvEMULATION (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
void ACGLAPIENTRY glProgramUniformMatrix4fvEMULATION (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
void ACGLAPIENTRY glProgramUniformMatrix4x2fvEMULATION (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
void ACGLAPIENTRY glProgramUniformMatrix4x3fvEMULATION (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
void ACGLAPIENTRY glTextureBufferEMULATION (GLuint texture, GLenum target, GLenum internalformat, GLuint buffer);
void ACGLAPIENTRY glTextureImage1DEMULATION (GLuint texture, GLenum target, GLint level, GLint internalformat, GLsizei width, GLint border, GLenum format, GLenum type, const void* pixels);
void ACGLAPIENTRY glTextureImage2DEMULATION (GLuint texture, GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const void* pixels);
void ACGLAPIENTRY glTextureImage3DEMULATION (GLuint texture, GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const void* pixels);
void ACGLAPIENTRY glTextureParameterIivEMULATION (GLuint texture, GLenum target, GLenum pname, const GLint* params);
void ACGLAPIENTRY glTextureParameterIuivEMULATION (GLuint texture, GLenum target, GLenum pname, const GLuint* params);
void ACGLAPIENTRY glTextureParameterfEMULATION (GLuint texture, GLenum target, GLenum pname, GLfloat param);
void ACGLAPIENTRY glTextureParameterfvEMULATION (GLuint texture, GLenum target, GLenum pname, const GLfloat* param);
void ACGLAPIENTRY glTextureParameteriEMULATION (GLuint texture, GLenum target, GLenum pname, GLint param);
void ACGLAPIENTRY glTextureParameterivEMULATION (GLuint texture, GLenum target, GLenum pname, const GLint* param);
void ACGLAPIENTRY glTextureRenderbufferEMULATION (GLuint texture, GLenum target, GLuint renderbuffer);
void ACGLAPIENTRY glTextureSubImage1DEMULATION (GLuint texture, GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const void* pixels);
void ACGLAPIENTRY glTextureSubImage2DEMULATION (GLuint texture, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void* pixels);
void ACGLAPIENTRY glTextureSubImage3DEMULATION (GLuint texture, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void* pixels);
GLboolean ACGLAPIENTRY glUnmapNamedBufferEMULATION (GLuint buffer);
void ACGLAPIENTRY glVertexArrayVertexAttribIOffsetEMULATION (GLuint vaobj, GLuint buffer, GLuint index, GLint size, GLenum type, GLsizei stride, GLintptr offset);
void ACGLAPIENTRY glVertexArrayVertexAttribOffsetEMULATION (GLuint vaobj, GLuint buffer, GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, GLintptr offset);

// DSA equivalents for deprecated functions:
#ifndef ACGL_OPENGL_PROFILE_CORE
void ACGLAPIENTRY glVertexArrayVertexOffsetEMULATION (GLuint vaobj, GLuint buffer, GLint size, GLenum type, GLsizei stride, GLintptr offset);
void ACGLAPIENTRY glVertexArrayColorOffsetEMULATION (GLuint vaobj, GLuint buffer, GLint size, GLenum type, GLsizei stride, GLintptr offset);
void ACGLAPIENTRY glVertexArrayEdgeFlagOffsetEMULATION (GLuint vaobj, GLuint buffer, GLsizei stride, GLintptr offset);
void ACGLAPIENTRY glVertexArrayFogCoordOffsetEMULATION (GLuint vaobj, GLuint buffer, GLenum type, GLsizei stride, GLintptr offset);
void ACGLAPIENTRY glVertexArrayIndexOffsetEMULATION (GLuint vaobj, GLuint buffer, GLenum type, GLsizei stride, GLintptr offset);
void ACGLAPIENTRY glVertexArrayMultiTexCoordOffsetEMULATION (GLuint vaobj, GLuint buffer, GLenum texunit, GLint size, GLenum type, GLsizei stride, GLintptr offset);
void ACGLAPIENTRY glVertexArrayNormalOffsetEMULATION (GLuint vaobj, GLuint buffer, GLenum type, GLsizei stride, GLintptr offset);
void ACGLAPIENTRY glVertexArraySecondaryColorOffsetEMULATION (GLuint vaobj, GLuint buffer, GLint size, GLenum type, GLsizei stride, GLintptr offset);
void ACGLAPIENTRY glVertexArrayTexCoordOffsetEMULATION (GLuint vaobj, GLuint buffer, GLint size, GLenum type, GLsizei stride, GLintptr offset);
void ACGLAPIENTRY glDisableClientStateIndexedEMULATION (GLenum array, GLuint index);
void ACGLAPIENTRY glDisableClientStateiEMULATION (GLenum array, GLuint index);
void ACGLAPIENTRY glEnableClientStateIndexedEMULATION (GLenum array, GLuint index);
void ACGLAPIENTRY glEnableClientStateiEMULATION (GLenum array, GLuint index);
void ACGLAPIENTRY glGetMultiTexEnvfvEMULATION (GLenum texunit, GLenum target, GLenum pname, GLfloat* params);
void ACGLAPIENTRY glGetMultiTexEnvivEMULATION (GLenum texunit, GLenum target, GLenum pname, GLint* params);
void ACGLAPIENTRY glGetMultiTexGendvEMULATION (GLenum texunit, GLenum coord, GLenum pname, GLdouble* params);
void ACGLAPIENTRY glGetMultiTexGenfvEMULATION (GLenum texunit, GLenum coord, GLenum pname, GLfloat* params);
void ACGLAPIENTRY glGetMultiTexGenivEMULATION (GLenum texunit, GLenum coord, GLenum pname, GLint* params);
void ACGLAPIENTRY glMatrixFrustumEMULATION (GLenum matrixMode, GLdouble l, GLdouble r, GLdouble b, GLdouble t, GLdouble n, GLdouble f);
void ACGLAPIENTRY glMatrixLoadIdentityEMULATION (GLenum matrixMode);
void ACGLAPIENTRY glMatrixLoadTransposedEMULATION (GLenum matrixMode, const GLdouble* m);
void ACGLAPIENTRY glMatrixLoadTransposefEMULATION (GLenum matrixMode, const GLfloat* m);
void ACGLAPIENTRY glMatrixLoaddEMULATION (GLenum matrixMode, const GLdouble* m);
void ACGLAPIENTRY glMatrixLoadfEMULATION (GLenum matrixMode, const GLfloat* m);
void ACGLAPIENTRY glMatrixMultTransposedEMULATION (GLenum matrixMode, const GLdouble* m);
void ACGLAPIENTRY glMatrixMultTransposefEMULATION (GLenum matrixMode, const GLfloat* m);
void ACGLAPIENTRY glMatrixMultdEMULATION (GLenum matrixMode, const GLdouble* m);
void ACGLAPIENTRY glMatrixMultfEMULATION (GLenum matrixMode, const GLfloat* m);
void ACGLAPIENTRY glMatrixOrthoEMULATION (GLenum matrixMode, GLdouble l, GLdouble r, GLdouble b, GLdouble t, GLdouble n, GLdouble f);
void ACGLAPIENTRY glMatrixPopEMULATION (GLenum matrixMode);
void ACGLAPIENTRY glMatrixPushEMULATION (GLenum matrixMode);
void ACGLAPIENTRY glMatrixRotatedEMULATION (GLenum matrixMode, GLdouble angle, GLdouble x, GLdouble y, GLdouble z);
void ACGLAPIENTRY glMatrixRotatefEMULATION (GLenum matrixMode, GLfloat angle, GLfloat x, GLfloat y, GLfloat z);
void ACGLAPIENTRY glMatrixScaledEMULATION (GLenum matrixMode, GLdouble x, GLdouble y, GLdouble z);
void ACGLAPIENTRY glMatrixScalefEMULATION (GLenum matrixMode, GLfloat x, GLfloat y, GLfloat z);
void ACGLAPIENTRY glMatrixTranslatedEMULATION (GLenum matrixMode, GLdouble x, GLdouble y, GLdouble z);
void ACGLAPIENTRY glMatrixTranslatefEMULATION (GLenum matrixMode, GLfloat x, GLfloat y, GLfloat z);
void ACGLAPIENTRY glMultiTexCoordPointerEMULATION (GLenum texunit, GLint size, GLenum type, GLsizei stride, const void* pointer);
void ACGLAPIENTRY glMultiTexEnvfEMULATION (GLenum texunit, GLenum target, GLenum pname, GLfloat param);
void ACGLAPIENTRY glMultiTexEnvfvEMULATION (GLenum texunit, GLenum target, GLenum pname, const GLfloat* params);
void ACGLAPIENTRY glMultiTexEnviEMULATION (GLenum texunit, GLenum target, GLenum pname, GLint param);
void ACGLAPIENTRY glMultiTexEnvivEMULATION (GLenum texunit, GLenum target, GLenum pname, const GLint* params);
void ACGLAPIENTRY glMultiTexGendEMULATION (GLenum texunit, GLenum coord, GLenum pname, GLdouble param);
void ACGLAPIENTRY glMultiTexGendvEMULATION (GLenum texunit, GLenum coord, GLenum pname, const GLdouble* params);
void ACGLAPIENTRY glMultiTexGenfEMULATION (GLenum texunit, GLenum coord, GLenum pname, GLfloat param);
void ACGLAPIENTRY glMultiTexGenfvEMULATION (GLenum texunit, GLenum coord, GLenum pname, const GLfloat* params);
void ACGLAPIENTRY glMultiTexGeniEMULATION (GLenum texunit, GLenum coord, GLenum pname, GLint param);
void ACGLAPIENTRY glMultiTexGenivEMULATION (GLenum texunit, GLenum coord, GLenum pname, const GLint* params);
void ACGLAPIENTRY glPushClientAttribDefaultEMULATION (GLbitfield mask);
#endif // no deprecated in CORE profile builds
} // OpenGL
} // ACGL


#endif // ACGL_OPENGL_EXT_DIRECT_STATE_ACCESS_HH
