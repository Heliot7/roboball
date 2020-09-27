#ifndef GOALVIEW_H
#define GOALVIEW_H

#include <ACGL/OpenGL/Objects.hh>
#include <ACGL/OpenGL/GL.hh>
#include <ACGL/OpenGL/Tools.hh>
#include <ACGL/OpenGL/Managers.hh>
#include <ACGL/Scene/MatrixStack.hh>
#include <ACGL/Math/Math.hh>
#include <ACGL/Animations/Animation.hh>

#include "../Model/World.hh"

using namespace ACGL::Math;
using namespace ACGL::Utils;
using namespace ACGL::OpenGL;
using namespace ACGL::Resource;
using namespace ACGL::Scene;
using namespace ACGL::Animations;
using namespace std;

class GoalView
{
public:
    GoalView(const std::tr1::shared_ptr<World>& world);
    void paint(double time);
    void initView(SharedTexture sizeDepth, SharedTexture sizeColour);
    void updatResize(int w, int h);

private:
    // Camera View matrix to keep letters static also if resizing
        glm::mat4 matView;
        void setMatView(glm::vec3 translation, glm::vec3 scaling);
        // Orthogonal View matrix
        glm::mat4 matOrtho;
        void setOrthoView();

        int mWidth, mHeight;
        float mAR;

    // ProjectionMatrix
        ACGL::OpenGL::SharedUniformMatrix4f mpUniformModelViewProjectionMatrix;

    // Pointer of World
        std::tr1::shared_ptr<World> mpWorld;

        ACGL::OpenGL::ConstSharedRenderObject mGoal;

        ACGL::Animations::ConstSharedAnimation mAnimation;
};

#endif // GOALVIEW_H
