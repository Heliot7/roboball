////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2011, Computer Graphics Group RWTH Aachen University         //
// All rights reserved.                                                       //
////////////////////////////////////////////////////////////////////////////////

#ifndef ACGL_OPENGL_OBJECTS_SHADERPROGRAM_HH
#define ACGL_OPENGL_OBJECTS_SHADERPROGRAM_HH

/*
 * A ShaderProgram is a wrapper around an OpenGL Program: A combination of Shaders
 * that are linked together to controll the programmable pipeline stages.
 *
 * A ShaderProgram is still quite low-level and just wraps the OpenGL object itself.
 *
 * One note on uniforms:
 * There are basically four ways to set uniform values here:
 *
 * setUniform(        GLint       _location, VALUE );
 * setUniform(        std::string _location, VALUE );
 * setProgramUniform( GLint       _location, VALUE );
 * setProgramUniform( std::string _location, VALUE );
 *
 * The versions with a std::string as a location are easy to use, just provide the name
 * the uniform is called in the shaderfile. But it will have to query the uniform location
 * each call and thus is inefficient! It would be faster to query the location once using
 * getUniformLocation( std::string ); and use the returned value in combination with the
 * set*Uniform( GLint, ...) versions.
 *
 * Both are provided as setUniform and setProgramUniform:
 * In order for setUniform(...) to work as intendet the ShaderProgram has to be active ( use() ),
 * setProgramUniform(...) does not have this limitation and is based on direct state access
 * (via an extension or a basic simulation of the extension).
 * Use setProgramUniform if you can't know which program is in use right now, setUniform should
 * be prefered for performance critical parts of your app.
 *
 * In short: setProgramUniform( std::string _location, VALUE ); is the most error proof option
 *           and good for testing out new stuff
 *           setUniform( GLint _location, VALUE ); is best for performance critical code thats
 *           well tested
 *
 */

#include <ACGL/ACGL.hh>

#include <ACGL/Base/Macros.hh>
#include <ACGL/OpenGL/GL.hh>
#include <ACGL/OpenGL/Objects/Shader.hh>
#include <ACGL/OpenGL/Objects/Texture.hh>
#include <ACGL/Math/Math.hh>

#include <vector>
#include <tr1/memory>

namespace ACGL{
namespace OpenGL{

class ShaderProgram
{
    ACGL_NOT_COPYABLE(ShaderProgram)

    // ===================================================================================================== \/
    // ============================================================================================ TYPEDEFS \/
    // ===================================================================================================== \/
public:
    typedef std::vector< ConstSharedShader > ConstSharedShaderVec;

    // ========================================================================================================= \/
    // ============================================================================================ CONSTRUCTORS \/
    // ========================================================================================================= \/
public:
    ShaderProgram(void)
    :   mObjectName(0),
        mShaders()
    {
        mObjectName = glCreateProgram();
    }

    virtual ~ShaderProgram(void)
    {
        // "DeleteProgram will silently ignore the value zero." - GL Spec
        glDeleteProgram(mObjectName);
    }

    // ==================================================================================================== \/
    // ============================================================================================ GETTERS \/
    // ==================================================================================================== \/
public:
    inline       GLuint                operator()   (void) const { return mObjectName; }
    inline       GLuint                getObjectName(void) const { return mObjectName; }
    inline const ConstSharedShaderVec& getShaders   (void) const { return mShaders;    }

    // ===================================================================================================== \/
    // ============================================================================================ WRAPPERS \/
    // ===================================================================================================== \/
public:
    inline GLint getUniformLocation      (const std::string& _nameInShader) const { return glGetUniformLocation (mObjectName, _nameInShader.c_str()); }
#if (ACGL_OPENGL_VERSION >= 30)
    inline GLint getAttributeLocation    (const std::string& _nameInShader) const { return glGetAttribLocation  (mObjectName, _nameInShader.c_str()); }
    inline GLint getFragmentDataLocation (const std::string& _nameInShader) const { return glGetFragDataLocation(mObjectName, _nameInShader.c_str()); }
    inline void bindAttributeLocation    (const std::string& _nameInShader, GLuint _location) const { glBindAttribLocation   (mObjectName, _location, _nameInShader.c_str()); }
    inline void bindFragmentDataLocation (const std::string& _nameInShader, GLuint _location) const { glBindFragDataLocation (mObjectName, _location, _nameInShader.c_str()); }
#endif // OpenGL >= 3.0
    inline void use(void) const { glUseProgram(mObjectName); }

    inline void attachShader(const ConstSharedShader& _shader)
    {
        mShaders.push_back(_shader);
        glAttachShader( mObjectName, _shader->getObjectName() );
    }

    bool link (void) const;


    // ===================================================================================================== \/
    // ============================================================================================ UNIFORMS \/
    // ===================================================================================================== \/

    // int by location
    inline void setUniform (GLint _location, GLint _v)             const { glUniform1i (_location, _v); }
    inline void setUniform (GLint _location, const glm::ivec2& _v) const { glUniform2iv(_location, 1, glm::value_ptr(_v)); }
    inline void setUniform (GLint _location, const glm::ivec3& _v) const { glUniform3iv(_location, 1, glm::value_ptr(_v)); }
    inline void setUniform (GLint _location, const glm::ivec4& _v) const { glUniform4iv(_location, 1, glm::value_ptr(_v)); }

    // int DSA by location
    inline void setProgramUniform (GLint _location, GLint _v)             const { glProgramUniform1i (mObjectName, _location, _v); }
    inline void setProgramUniform (GLint _location, const glm::ivec2& _v) const { glProgramUniform2iv(mObjectName, _location, 1, glm::value_ptr(_v)); }
    inline void setProgramUniform (GLint _location, const glm::ivec3& _v) const { glProgramUniform3iv(mObjectName, _location, 1, glm::value_ptr(_v)); }
    inline void setProgramUniform (GLint _location, const glm::ivec4& _v) const { glProgramUniform4iv(mObjectName, _location, 1, glm::value_ptr(_v)); }

#if (ACGL_OPENGL_VERSION >= 30)
    // unsigned int by location
    inline void setUniform (GLint _location, GLuint _v)            const { glUniform1ui (_location, _v); }
    inline void setUniform (GLint _location, const glm::uvec2& _v) const { glUniform2uiv(_location, 1, glm::value_ptr(_v)); }
    inline void setUniform (GLint _location, const glm::uvec3& _v) const { glUniform3uiv(_location, 1, glm::value_ptr(_v)); }
    inline void setUniform (GLint _location, const glm::uvec4& _v) const { glUniform4uiv(_location, 1, glm::value_ptr(_v)); }

    // unsigned int DSA by location
    inline void setProgramUniform (GLint _location, GLuint _v)            const { glProgramUniform1ui (mObjectName, _location, _v); }
    inline void setProgramUniform (GLint _location, const glm::uvec2& _v) const { glProgramUniform2uiv(mObjectName, _location, 1, glm::value_ptr(_v)); }
    inline void setProgramUniform (GLint _location, const glm::uvec3& _v) const { glProgramUniform3uiv(mObjectName, _location, 1, glm::value_ptr(_v)); }
    inline void setProgramUniform (GLint _location, const glm::uvec4& _v) const { glProgramUniform4uiv(mObjectName, _location, 1, glm::value_ptr(_v)); }
#endif // OpenGL >= 3.0

    // float by location
    inline void setUniform (GLint _location, GLfloat _v)          const { glUniform1f (_location, _v); }
    inline void setUniform (GLint _location, const glm::vec2& _v) const { glUniform2fv(_location, 1, glm::value_ptr(_v)); }
    inline void setUniform (GLint _location, const glm::vec3& _v) const { glUniform3fv(_location, 1, glm::value_ptr(_v)); }
    inline void setUniform (GLint _location, const glm::vec4& _v) const { glUniform4fv(_location, 1, glm::value_ptr(_v)); }

    // float DSA by location
    inline void setProgramUniform (GLint _location, GLfloat _v)          const { glProgramUniform1f (mObjectName, _location, _v); }
    inline void setProgramUniform (GLint _location, const glm::vec2& _v) const { glProgramUniform2fv(mObjectName, _location, 1, glm::value_ptr(_v)); }
    inline void setProgramUniform (GLint _location, const glm::vec3& _v) const { glProgramUniform3fv(mObjectName, _location, 1, glm::value_ptr(_v)); }
    inline void setProgramUniform (GLint _location, const glm::vec4& _v) const { glProgramUniform4fv(mObjectName, _location, 1, glm::value_ptr(_v)); }

#if (ACGL_OPENGL_VERSION >= 40)
    // double by location
    inline void setUniform (GLint _location, GLdouble _v)          const { glUniform1d (_location, _v); }
    inline void setUniform (GLint _location, const glm::dvec2& _v) const { glUniform2dv(_location, 1, glm::value_ptr(_v)); }
    inline void setUniform (GLint _location, const glm::dvec3& _v) const { glUniform3dv(_location, 1, glm::value_ptr(_v)); }
    inline void setUniform (GLint _location, const glm::dvec4& _v) const { glUniform4dv(_location, 1, glm::value_ptr(_v)); }

    // double DSA by location
    inline void setProgramUniform (GLint _location, GLdouble _v)          const { glProgramUniform1d (mObjectName, _location, _v); }
    inline void setProgramUniform (GLint _location, const glm::dvec2& _v) const { glProgramUniform2dv(mObjectName, _location, 1, glm::value_ptr(_v)); }
    inline void setProgramUniform (GLint _location, const glm::dvec3& _v) const { glProgramUniform3dv(mObjectName, _location, 1, glm::value_ptr(_v)); }
    inline void setProgramUniform (GLint _location, const glm::dvec4& _v) const { glProgramUniform4dv(mObjectName, _location, 1, glm::value_ptr(_v)); }
#endif // OpenGL >= 4.0

    // float matrix by location
    inline void setUniform (GLint _location, const glm::mat2&   _v, GLboolean _transpose = GL_FALSE) const { glUniformMatrix2fv(_location, 1, _transpose, glm::value_ptr(_v)); }
    inline void setUniform (GLint _location, const glm::mat2x3& _v, GLboolean _transpose = GL_FALSE) const { glUniformMatrix2x3fv(_location, 1, _transpose, glm::value_ptr(_v)); }
    inline void setUniform (GLint _location, const glm::mat2x4& _v, GLboolean _transpose = GL_FALSE) const { glUniformMatrix2x4fv(_location, 1, _transpose, glm::value_ptr(_v)); }
    inline void setUniform (GLint _location, const glm::mat3x2& _v, GLboolean _transpose = GL_FALSE) const { glUniformMatrix3x2fv(_location, 1, _transpose, glm::value_ptr(_v)); }
    inline void setUniform (GLint _location, const glm::mat3&   _v, GLboolean _transpose = GL_FALSE) const { glUniformMatrix3fv  (_location, 1, _transpose, glm::value_ptr(_v)); }
    inline void setUniform (GLint _location, const glm::mat3x4& _v, GLboolean _transpose = GL_FALSE) const { glUniformMatrix3x4fv(_location, 1, _transpose, glm::value_ptr(_v)); }
    inline void setUniform (GLint _location, const glm::mat4x2& _v, GLboolean _transpose = GL_FALSE) const { glUniformMatrix4x2fv(_location, 1, _transpose, glm::value_ptr(_v)); }
    inline void setUniform (GLint _location, const glm::mat4x3& _v, GLboolean _transpose = GL_FALSE) const { glUniformMatrix4x3fv(_location, 1, _transpose, glm::value_ptr(_v)); }
    inline void setUniform (GLint _location, const glm::mat4&   _v, GLboolean _transpose = GL_FALSE) const { glUniformMatrix4fv  (_location, 1, _transpose, glm::value_ptr(_v)); }

    // float matrix DSA by location
    inline void setProgramUniform (GLint _location, const glm::mat2&   _v, GLboolean _transpose = GL_FALSE) const { glProgramUniformMatrix2fv  (mObjectName, _location, 1, _transpose, glm::value_ptr(_v)); }
    inline void setProgramUniform (GLint _location, const glm::mat2x3& _v, GLboolean _transpose = GL_FALSE) const { glProgramUniformMatrix2x3fv(mObjectName, _location, 1, _transpose, glm::value_ptr(_v)); }
    inline void setProgramUniform (GLint _location, const glm::mat2x4& _v, GLboolean _transpose = GL_FALSE) const { glProgramUniformMatrix2x4fv(mObjectName, _location, 1, _transpose, glm::value_ptr(_v)); }
    inline void setProgramUniform (GLint _location, const glm::mat3x2& _v, GLboolean _transpose = GL_FALSE) const { glProgramUniformMatrix3x2fv(mObjectName, _location, 1, _transpose, glm::value_ptr(_v)); }
    inline void setProgramUniform (GLint _location, const glm::mat3&   _v, GLboolean _transpose = GL_FALSE) const { glProgramUniformMatrix3fv  (mObjectName, _location, 1, _transpose, glm::value_ptr(_v)); }
    inline void setProgramUniform (GLint _location, const glm::mat3x4& _v, GLboolean _transpose = GL_FALSE) const { glProgramUniformMatrix3x4fv(mObjectName, _location, 1, _transpose, glm::value_ptr(_v)); }
    inline void setProgramUniform (GLint _location, const glm::mat4x2& _v, GLboolean _transpose = GL_FALSE) const { glProgramUniformMatrix4x2fv(mObjectName, _location, 1, _transpose, glm::value_ptr(_v)); }
    inline void setProgramUniform (GLint _location, const glm::mat4x3& _v, GLboolean _transpose = GL_FALSE) const { glProgramUniformMatrix4x3fv(mObjectName, _location, 1, _transpose, glm::value_ptr(_v)); }
    inline void setProgramUniform (GLint _location, const glm::mat4&   _v, GLboolean _transpose = GL_FALSE) const { glProgramUniformMatrix4fv  (mObjectName, _location, 1, _transpose, glm::value_ptr(_v)); }

#if (ACGL_OPENGL_VERSION >= 40)
    // double matrix by location
    inline void setUniform (GLint _location, const glm::dmat2&   _v, GLboolean _transpose = GL_FALSE) const { glUniformMatrix2dv(_location, 1, _transpose, glm::value_ptr(_v)); }
    inline void setUniform (GLint _location, const glm::dmat2x3& _v, GLboolean _transpose = GL_FALSE) const { glUniformMatrix2x3dv(_location, 1, _transpose, glm::value_ptr(_v)); }
    inline void setUniform (GLint _location, const glm::dmat2x4& _v, GLboolean _transpose = GL_FALSE) const { glUniformMatrix2x4dv(_location, 1, _transpose, glm::value_ptr(_v)); }
    inline void setUniform (GLint _location, const glm::dmat3x2& _v, GLboolean _transpose = GL_FALSE) const { glUniformMatrix3x2dv(_location, 1, _transpose, glm::value_ptr(_v)); }
    inline void setUniform (GLint _location, const glm::dmat3&   _v, GLboolean _transpose = GL_FALSE) const { glUniformMatrix3dv  (_location, 1, _transpose, glm::value_ptr(_v)); }
    inline void setUniform (GLint _location, const glm::dmat3x4& _v, GLboolean _transpose = GL_FALSE) const { glUniformMatrix3x4dv(_location, 1, _transpose, glm::value_ptr(_v)); }
    inline void setUniform (GLint _location, const glm::dmat4x2& _v, GLboolean _transpose = GL_FALSE) const { glUniformMatrix4x2dv(_location, 1, _transpose, glm::value_ptr(_v)); }
    inline void setUniform (GLint _location, const glm::dmat4x3& _v, GLboolean _transpose = GL_FALSE) const { glUniformMatrix4x3dv(_location, 1, _transpose, glm::value_ptr(_v)); }
    inline void setUniform (GLint _location, const glm::dmat4&   _v, GLboolean _transpose = GL_FALSE) const { glUniformMatrix4dv  (_location, 1, _transpose, glm::value_ptr(_v)); }

    // double matrix DSA by location
    inline void setProgramUniform (GLint _location, const glm::dmat2&   _v, GLboolean _transpose = GL_FALSE) const { glProgramUniformMatrix2dv  (mObjectName, _location, 1, _transpose, glm::value_ptr(_v)); }
    inline void setProgramUniform (GLint _location, const glm::dmat2x3& _v, GLboolean _transpose = GL_FALSE) const { glProgramUniformMatrix2x3dv(mObjectName, _location, 1, _transpose, glm::value_ptr(_v)); }
    inline void setProgramUniform (GLint _location, const glm::dmat2x4& _v, GLboolean _transpose = GL_FALSE) const { glProgramUniformMatrix2x4dv(mObjectName, _location, 1, _transpose, glm::value_ptr(_v)); }
    inline void setProgramUniform (GLint _location, const glm::dmat3x2& _v, GLboolean _transpose = GL_FALSE) const { glProgramUniformMatrix3x2dv(mObjectName, _location, 1, _transpose, glm::value_ptr(_v)); }
    inline void setProgramUniform (GLint _location, const glm::dmat3&   _v, GLboolean _transpose = GL_FALSE) const { glProgramUniformMatrix3dv  (mObjectName, _location, 1, _transpose, glm::value_ptr(_v)); }
    inline void setProgramUniform (GLint _location, const glm::dmat3x4& _v, GLboolean _transpose = GL_FALSE) const { glProgramUniformMatrix3x4dv(mObjectName, _location, 1, _transpose, glm::value_ptr(_v)); }
    inline void setProgramUniform (GLint _location, const glm::dmat4x2& _v, GLboolean _transpose = GL_FALSE) const { glProgramUniformMatrix4x2dv(mObjectName, _location, 1, _transpose, glm::value_ptr(_v)); }
    inline void setProgramUniform (GLint _location, const glm::dmat4x3& _v, GLboolean _transpose = GL_FALSE) const { glProgramUniformMatrix4x3dv(mObjectName, _location, 1, _transpose, glm::value_ptr(_v)); }
    inline void setProgramUniform (GLint _location, const glm::dmat4&   _v, GLboolean _transpose = GL_FALSE) const { glProgramUniformMatrix4dv  (mObjectName, _location, 1, _transpose, glm::value_ptr(_v)); }
#endif // OpenGL >= 4.0

    // texture
    inline void setTexture        (GLint _location,                  const ConstSharedTexture& _texture, GLenum _unit = 0) const { glUniform1i(_location, _unit);                                        _texture->bind(_unit); }
    inline void setProgramTexture (const std::string& _nameInShader, const ConstSharedTexture& _texture, GLenum _unit = 0) const { setProgramUniform( getUniformLocation(_nameInShader), (GLint) _unit); _texture->bind(_unit); }

    // ======================================================================================================= \/
    // ============================================================================================ HIGH LEVEL \/
    // ======================================================================================================= \/

    // normal:
    template <typename T>
    inline void setUniform (const std::string& _nameInShader, T _v) const
    {
        setUniform( getUniformLocation(_nameInShader), _v);
    }

    // DSA:
    template <typename T>
    inline void setProgramUniform (const std::string& _nameInShader, T _v) const
    {
        setProgramUniform( getUniformLocation(_nameInShader), _v);
    }

    // normal for matrices with additional transpose parameter
    template <typename T>
    inline void setUniform (const std::string& _nameInShader, T _v, GLboolean _transpose) const
    {
        setUniform( getUniformLocation(_nameInShader), _v, _transpose);
    }

    // DSA for matrices with additional transpose parameter
    template <typename T>
    inline void setProgramUniform (const std::string& _nameInShader, T _v, GLboolean _transpose) const
    {
        setProgramUniform( getUniformLocation(_nameInShader), _v, _transpose);
    }

    inline void setTexture        (const std::string& _nameInShader, const ConstSharedTexture& _texture, GLenum _unit = 0) const { setUniform( getUniformLocation(_nameInShader), (GLint) _unit);        _texture->bind(_unit); }
    inline void setProgramTexture (GLint _location,                  const ConstSharedTexture& _texture, GLenum _unit = 0) const { glProgramUniform1i(mObjectName, _location, _unit);                    _texture->bind(_unit); }
    

    // =================================================================================================== \/
    // ============================================================================================ FIELDS \/
    // =================================================================================================== \/
protected:
    GLuint               mObjectName;
    ConstSharedShaderVec mShaders;
};

ACGL_SHARED_TYPEDEF(ShaderProgram)

} // OpenGL
} // ACGL

#endif // ACGL_OPENGL_OBJECTS_SHADERPROGRAM_HH
