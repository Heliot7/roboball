////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2011, Computer Graphics Group RWTH Aachen University         //
// All rights reserved.                                                       //
////////////////////////////////////////////////////////////////////////////////

#ifndef ACGL_SCENE_MATRIXSTACK_HH
#define ACGL_SCENE_MATRIXSTACK_HH

/*
 * A matrix stack that can mimic the old OpenGL matrix stack. It is only based on
 * glm, so it can be used without OpenGL easily.
 *
 * You can create as many independent stacks as you like or just use the
 * pre-defined ModelViewMatrixStack singleton.
 */

#include <ACGL/ACGL.hh>
#include <ACGL/Base/Singleton.hh>
#include <ACGL/Math/Math.hh>

#include <stack>

namespace ACGL{
namespace Scene{

class MatrixStack
{
public:
    MatrixStack() {}

    // does not change the stack
    // returns the top modelview matrix
    glm::mat4 topMatrix()
    {
        if (mStack.empty()) return glm::mat4();
        return mStack.top();
    }

    // returns the inverse transpose of the upper 3*3
    // modelview matrix
    glm::mat3 topNormalMatrix()
    {
        return Math::Functions::normalMatrix( topMatrix() );
    }

    void pushMatrix()
    {
        mStack.push( topMatrix() );
    }

    void popMatrix()
    {
        if (!mStack.empty()) mStack.pop();
    }


    // if the stack is empty this will return the identity
    glm::mat4 popAndGetMatrix()
    {
        if (mStack.empty()) {
            return glm::mat4();
        }
        glm::mat4 tmp = mStack.top();
        mStack.pop();
        return tmp;
    }

    // will change the top matrix
    void loadIdentity()
    {
        loadMatrix( glm::mat4() );
    }

    // will replace the top matrix with the given matrix
    void loadMatrix( glm::mat4 matrixToLoad )
    {
        popMatrix();
        mStack.push( matrixToLoad );
    }

    // the top matrix will be multiplied with the given one and
    // will then replace the top matrix
    void multMatrix( const glm::mat4 &rhs )
    {
        mStack.push( popAndGetMatrix() * rhs );
    }

    // like glRotate rotates the top matrix around a given axis a given degree phi
    void rotate(const float phi, const float x, const float y, const float z) { rotate( phi, glm::vec3( x,y,z )); }
    void rotate(const float phi, const glm::vec3 &axis )
    {
        mStack.push( glm::rotate( popAndGetMatrix(), phi, axis ) );
    }

    // like glTranslate
    void translate(float x, float y, float z) { translate( glm::vec3(x,y,z) ); }
    void translate( glm::vec3 vector )
    {
        mStack.push( glm::translate( popAndGetMatrix(), vector) );
    }

    // like glScale
    void scale( float s ) { scale( glm::vec3(s,s,s) ); }
    void scale( float x, float y, float z ) { scale( glm::vec3(x,y,z)); }
    void scale( const glm::vec3 &factor )
    {
        mStack.push( glm::scale( popAndGetMatrix(), factor ) );
    }

private:
    std::stack< glm::mat4 > mStack;
};

typedef Base::Singleton< MatrixStack > ModelViewMatrixStack;

} // Scene
} // ACGL

#endif // ACGL_SCENE_MATRIXSTACK_HH
