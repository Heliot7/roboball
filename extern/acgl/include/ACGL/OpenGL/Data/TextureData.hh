////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2011, Computer Graphics Group RWTH Aachen University         //
// All rights reserved.                                                       //
////////////////////////////////////////////////////////////////////////////////

#ifndef ACGL_OPENGL_DATA_TEXTUREDATA_HH
#define ACGL_OPENGL_DATA_TEXTUREDATA_HH

#include <ACGL/ACGL.hh>

#include <ACGL/Base/Macros.hh>
#include <ACGL/OpenGL/GL.hh>

namespace ACGL{
namespace OpenGL{

class TextureData
{
    // ========================================================================================================= \/
    // ============================================================================================ CONSTRUCTORS \/
    // ========================================================================================================= \/
public:
    TextureData(void)
    :   pData(NULL),
        width(0),
        height(0),
        depth(0),
        format(GL_RGBA),
        type(GL_UNSIGNED_BYTE)
    {}
    virtual ~TextureData(void)
    {
        delete[] pData;
    }

    // ========================================================================================================= \/
    // ================================================================================================= GETTERS \/
    // ========================================================================================================= \/
public:
    GLubyte* getData    (void) const { return pData;   }
    GLsizei  getWidth   (void) const { return width;   }
    GLsizei  getHeight  (void) const { return height;  }
    GLsizei  getDepth   (void) const { return depth;   }
    GLenum   getFormat  (void) const { return format;  }
    GLenum   getType    (void) const { return type;    }

    // ========================================================================================================= \/
    // ================================================================================================= SETTERS \/
    // ========================================================================================================= \/
public:
    void setData  (GLubyte* _pData)  { pData  = _pData;  }
    void setWidth (GLsizei  _width)  { width  = _width;  }
    void setHeight(GLsizei  _height) { height = _height; }
    void setDepth (GLsizei  _depth)  { depth  = _depth;  }
    void setFormat(GLenum   _format) { format = _format; }
    void setType  (GLenum   _type)   { type   = _type;   }

    // ========================================================================================================= \/
    // ================================================================================================== FIELDS \/
    // ========================================================================================================= \/
private:
    GLubyte* pData;
    GLsizei  width;
    GLsizei  height;
    GLsizei  depth;
    GLenum   format;
    GLenum   type;
};

ACGL_SHARED_TYPEDEF(TextureData)

} // OpenGL
} // ACGL

#endif // ACGL_OPENGL_DATA_TEXTUREDATA_HH
