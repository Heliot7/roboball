#ifndef GRASSBLADE_HH
#define GRASSBLADE_HH

#include <ACGL/OpenGL/Objects.hh>
#include <ACGL/OpenGL/GL.hh>
#include <ACGL/OpenGL/Tools.hh>
#include <ACGL/OpenGL/Managers.hh>
#include <ACGL/Scene/MatrixStack.hh>
#include <ACGL/Math/Math.hh>

using namespace ACGL::Math;
using namespace ACGL::Utils;
using namespace ACGL::OpenGL;
using namespace ACGL::Resource;
using namespace ACGL::Scene;
using namespace std;

class GrassBlade
{
public:
    GrassBlade();

    ACGL::OpenGL::ConstSharedRenderObject getRender() { return renderObj; }
    void initGrass(SharedUniformMatrix4f mpUniformModelViewProjectionMatrix, SharedTexture sizeDepth, SharedTexture sizeColour);
    void paint();

private:
    // Render object for drawing
    ACGL::OpenGL::ConstSharedRenderObject renderObj;


    ACGL::OpenGL::SharedUniformMatrix4f mpUniformModelViewProjectionMatrix;
};

#endif // GRASSBLADE_HH
