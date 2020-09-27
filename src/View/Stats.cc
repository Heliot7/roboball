#include "Stats.hh"

#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <math.h>

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

#define FONT_SIZE 24
#define FONT_FAMILY "Courier"

Stats::Stats(QGLWidget* parent, const std::tr1::shared_ptr<World>& world):
        mpUniformModelViewProjectionMatrix(UniformMatrix4fControl().create()),
        mpUniformModelViewMatrix(UniformMatrix4fControl().create()),
        mpUniformNormalMatrix(UniformMatrix3fControl().create()),
        parentGL(parent),
        mpWorld(world),
        mWidth(world->getCamera()->getWidth()),
        mHeight(world->getCamera()->getHeight()),
        mAR((float)world->getCamera()->getWidth()/(float)world->getCamera()->getHeight()),
        nGoals1(0),
        nGoals2(0),
        mTime(0)
{}

/* Setters */
void Stats::initStats(SharedTexture sizeDepth, SharedTexture sizeColour)
{
    setOrthoView();

    // - Background
    backScore = RenderObjectControl(
            VertexBufferObjectFileManager::the()->get(VertexBufferObjectControlFileOBJ("Quad.obj")),
        ShaderProgramObjectControl(ShaderProgramFileManager::the()->get(ShaderProgramControlAutoFiles("Number"))).
            uniform("uModelViewProjectionMatrix",   mpUniformModelViewProjectionMatrix).
            uniformTexture("uSamplerBaseColor",     UniformTextureControl(TextureFileManager::the()->get(TextureControlFileJPG("Status/backScore.png"))).create()).
            create(),
        FrameBufferObjectControl(). colorTexture("fFragDataColor", sizeColour).depthTexture(sizeDepth).create()).
        create();
    backTime = RenderObjectControl(
            VertexBufferObjectFileManager::the()->get(VertexBufferObjectControlFileOBJ("Quad.obj")),
        ShaderProgramObjectControl(ShaderProgramFileManager::the()->get(ShaderProgramControlAutoFiles("Number"))).
            uniform("uModelViewProjectionMatrix",   mpUniformModelViewProjectionMatrix).
            uniformTexture("uSamplerBaseColor",     UniformTextureControl(TextureFileManager::the()->get(TextureControlFileJPG("Status/backTime.png"))).create()).
            create(),
        FrameBufferObjectControl(). colorTexture("fFragDataColor", sizeColour).depthTexture(sizeDepth).create()).
        create();
    // - Team Flags
    // Left Spain
    leftSpa = RenderObjectControl(
            VertexBufferObjectFileManager::the()->get(VertexBufferObjectControlFileOBJ("Quad.obj")),
        ShaderProgramObjectControl(ShaderProgramFileManager::the()->get(ShaderProgramControlAutoFiles("Number"))).
            uniform("uModelViewProjectionMatrix",   mpUniformModelViewProjectionMatrix).
            uniformTexture("uSamplerBaseColor",     UniformTextureControl(TextureFileManager::the()->get(TextureControlFileJPG("Status/Flags/leftSpa.gif"))).create()).
            create(),
        FrameBufferObjectControl(). colorTexture("fFragDataColor", sizeColour).depthTexture(sizeDepth).create()).
        create();
    // Right Spain
    rightSpa = RenderObjectControl(
            VertexBufferObjectFileManager::the()->get(VertexBufferObjectControlFileOBJ("Quad.obj")),
        ShaderProgramObjectControl(ShaderProgramFileManager::the()->get(ShaderProgramControlAutoFiles("Number"))).
            uniform("uModelViewProjectionMatrix",   mpUniformModelViewProjectionMatrix).
            uniformTexture("uSamplerBaseColor",     UniformTextureControl(TextureFileManager::the()->get(TextureControlFileJPG("Status/Flags/rightSpa.gif"))).create()).
            create(),
        FrameBufferObjectControl(). colorTexture("fFragDataColor", sizeColour).depthTexture(sizeDepth).create()).
        create();
    // Left Germany
    leftGer = RenderObjectControl(
            VertexBufferObjectFileManager::the()->get(VertexBufferObjectControlFileOBJ("Quad.obj")),
        ShaderProgramObjectControl(ShaderProgramFileManager::the()->get(ShaderProgramControlAutoFiles("Number"))).
            uniform("uModelViewProjectionMatrix",   mpUniformModelViewProjectionMatrix).
            uniformTexture("uSamplerBaseColor",     UniformTextureControl(TextureFileManager::the()->get(TextureControlFileJPG("Status/Flags/leftGer.gif"))).create()).
            create(),
        FrameBufferObjectControl(). colorTexture("fFragDataColor", sizeColour).depthTexture(sizeDepth).create()).
        create();
    // Right Germany
    rightGer = RenderObjectControl(
            VertexBufferObjectFileManager::the()->get(VertexBufferObjectControlFileOBJ("Quad.obj")),
        ShaderProgramObjectControl(ShaderProgramFileManager::the()->get(ShaderProgramControlAutoFiles("Number"))).
            uniform("uModelViewProjectionMatrix",   mpUniformModelViewProjectionMatrix).
            uniformTexture("uSamplerBaseColor",     UniformTextureControl(TextureFileManager::the()->get(TextureControlFileJPG("Status/Flags/rightGer.gif"))).create()).
            create(),
        FrameBufferObjectControl(). colorTexture("fFragDataColor", sizeColour).depthTexture(sizeDepth).create()).
        create();
    // Left Holland
    leftHol = RenderObjectControl(
            VertexBufferObjectFileManager::the()->get(VertexBufferObjectControlFileOBJ("Quad.obj")),
        ShaderProgramObjectControl(ShaderProgramFileManager::the()->get(ShaderProgramControlAutoFiles("Number"))).
            uniform("uModelViewProjectionMatrix",   mpUniformModelViewProjectionMatrix).
            uniformTexture("uSamplerBaseColor",     UniformTextureControl(TextureFileManager::the()->get(TextureControlFileJPG("Status/Flags/leftHol.gif"))).create()).
            create(),
        FrameBufferObjectControl(). colorTexture("fFragDataColor", sizeColour).depthTexture(sizeDepth).create()).
        create();
    // Right Holland
    rightHol = RenderObjectControl(
            VertexBufferObjectFileManager::the()->get(VertexBufferObjectControlFileOBJ("Quad.obj")),
        ShaderProgramObjectControl(ShaderProgramFileManager::the()->get(ShaderProgramControlAutoFiles("Number"))).
            uniform("uModelViewProjectionMatrix",   mpUniformModelViewProjectionMatrix).
            uniformTexture("uSamplerBaseColor",     UniformTextureControl(TextureFileManager::the()->get(TextureControlFileJPG("Status/Flags/rightHol.gif"))).create()).
            create(),
        FrameBufferObjectControl(). colorTexture("fFragDataColor", sizeColour).depthTexture(sizeDepth).create()).
        create();
    // Left Italy
    leftIta = RenderObjectControl(
            VertexBufferObjectFileManager::the()->get(VertexBufferObjectControlFileOBJ("Quad.obj")),
        ShaderProgramObjectControl(ShaderProgramFileManager::the()->get(ShaderProgramControlAutoFiles("Number"))).
            uniform("uModelViewProjectionMatrix",   mpUniformModelViewProjectionMatrix).
            uniformTexture("uSamplerBaseColor",     UniformTextureControl(TextureFileManager::the()->get(TextureControlFileJPG("Status/Flags/leftIta.gif"))).create()).
            create(),
        FrameBufferObjectControl(). colorTexture("fFragDataColor", sizeColour).depthTexture(sizeDepth).create()).
        create();
    // Right Italy
    rightIta = RenderObjectControl(
            VertexBufferObjectFileManager::the()->get(VertexBufferObjectControlFileOBJ("Quad.obj")),
        ShaderProgramObjectControl(ShaderProgramFileManager::the()->get(ShaderProgramControlAutoFiles("Number"))).
            uniform("uModelViewProjectionMatrix",   mpUniformModelViewProjectionMatrix).
            uniformTexture("uSamplerBaseColor",     UniformTextureControl(TextureFileManager::the()->get(TextureControlFileJPG("Status/Flags/rightIta.gif"))).create()).
            create(),
        FrameBufferObjectControl(). colorTexture("fFragDataColor", sizeColour).depthTexture(sizeDepth).create()).
        create();
    // Left Brazil
    leftBra = RenderObjectControl(
            VertexBufferObjectFileManager::the()->get(VertexBufferObjectControlFileOBJ("Quad.obj")),
        ShaderProgramObjectControl(ShaderProgramFileManager::the()->get(ShaderProgramControlAutoFiles("Number"))).
            uniform("uModelViewProjectionMatrix",   mpUniformModelViewProjectionMatrix).
            uniformTexture("uSamplerBaseColor",     UniformTextureControl(TextureFileManager::the()->get(TextureControlFileJPG("Status/Flags/leftBra.gif"))).create()).
            create(),
        FrameBufferObjectControl(). colorTexture("fFragDataColor", sizeColour).depthTexture(sizeDepth).create()).
        create();
    // Right Brazil
    rightBra = RenderObjectControl(
            VertexBufferObjectFileManager::the()->get(VertexBufferObjectControlFileOBJ("Quad.obj")),
        ShaderProgramObjectControl(ShaderProgramFileManager::the()->get(ShaderProgramControlAutoFiles("Number"))).
            uniform("uModelViewProjectionMatrix",   mpUniformModelViewProjectionMatrix).
            uniformTexture("uSamplerBaseColor",     UniformTextureControl(TextureFileManager::the()->get(TextureControlFileJPG("Status/Flags/rightBra.gif"))).create()).
            create(),
        FrameBufferObjectControl(). colorTexture("fFragDataColor", sizeColour).depthTexture(sizeDepth).create()).
        create();
    // Left Argentina
    leftArg = RenderObjectControl(
            VertexBufferObjectFileManager::the()->get(VertexBufferObjectControlFileOBJ("Quad.obj")),
        ShaderProgramObjectControl(ShaderProgramFileManager::the()->get(ShaderProgramControlAutoFiles("Number"))).
            uniform("uModelViewProjectionMatrix",   mpUniformModelViewProjectionMatrix).
            uniformTexture("uSamplerBaseColor",     UniformTextureControl(TextureFileManager::the()->get(TextureControlFileJPG("Status/Flags/leftArg.gif"))).create()).
            create(),
        FrameBufferObjectControl(). colorTexture("fFragDataColor", sizeColour).depthTexture(sizeDepth).create()).
        create();
    // Right Argentina
    rightArg = RenderObjectControl(
            VertexBufferObjectFileManager::the()->get(VertexBufferObjectControlFileOBJ("Quad.obj")),
        ShaderProgramObjectControl(ShaderProgramFileManager::the()->get(ShaderProgramControlAutoFiles("Number"))).
            uniform("uModelViewProjectionMatrix",   mpUniformModelViewProjectionMatrix).
            uniformTexture("uSamplerBaseColor",     UniformTextureControl(TextureFileManager::the()->get(TextureControlFileJPG("Status/Flags/rightArg.gif"))).create()).
            create(),
        FrameBufferObjectControl(). colorTexture("fFragDataColor", sizeColour).depthTexture(sizeDepth).create()).
        create();
    // i8
    flagI8 = RenderObjectControl(
            VertexBufferObjectFileManager::the()->get(VertexBufferObjectControlFileOBJ("Quad.obj")),
        ShaderProgramObjectControl(ShaderProgramFileManager::the()->get(ShaderProgramControlAutoFiles("Number"))).
            uniform("uModelViewProjectionMatrix",   mpUniformModelViewProjectionMatrix).
            uniformTexture("uSamplerBaseColor",     UniformTextureControl(TextureFileManager::the()->get(TextureControlFileJPG("Status/Flags/raw/RWTHi8.png"))).create()).
            create(),
        FrameBufferObjectControl(). colorTexture("fFragDataColor", sizeColour).depthTexture(sizeDepth).create()).
        create();

    // - Numbers (Score)
    // (0)
    numScore0 = RenderObjectControl(
            VertexBufferObjectFileManager::the()->get(VertexBufferObjectControlFileOBJ("Quad.obj")),
        ShaderProgramObjectControl(ShaderProgramFileManager::the()->get(ShaderProgramControlAutoFiles("Number"))).
            uniform("uModelViewProjectionMatrix",   mpUniformModelViewProjectionMatrix).
            uniformTexture("uSamplerBaseColor",     UniformTextureControl(TextureFileManager::the()->get(TextureControlFileJPG("Status/Numbers/Score/0.png"))).create()).
            create(),
        FrameBufferObjectControl(). colorTexture("fFragDataColor", sizeColour).depthTexture(sizeDepth).create()).
        create();
    // (1)
    numScore1 = RenderObjectControl(
            VertexBufferObjectFileManager::the()->get(VertexBufferObjectControlFileOBJ("Quad.obj")),
        ShaderProgramObjectControl(ShaderProgramFileManager::the()->get(ShaderProgramControlAutoFiles("Number"))).
            uniform("uModelViewProjectionMatrix",   mpUniformModelViewProjectionMatrix).
            uniformTexture("uSamplerBaseColor",     UniformTextureControl(TextureFileManager::the()->get(TextureControlFileJPG("Status/Numbers/Score/1.png"))).create()).
            create(),
        FrameBufferObjectControl(). colorTexture("fFragDataColor", sizeColour).depthTexture(sizeDepth).create()).
        create();
    // (2)
    numScore2 = RenderObjectControl(
            VertexBufferObjectFileManager::the()->get(VertexBufferObjectControlFileOBJ("Quad.obj")),
        ShaderProgramObjectControl(ShaderProgramFileManager::the()->get(ShaderProgramControlAutoFiles("Number"))).
            uniform("uModelViewProjectionMatrix",   mpUniformModelViewProjectionMatrix).
            uniformTexture("uSamplerBaseColor",     UniformTextureControl(TextureFileManager::the()->get(TextureControlFileJPG("Status/Numbers/Score/2.png"))).create()).
            create(),
        FrameBufferObjectControl(). colorTexture("fFragDataColor", sizeColour).depthTexture(sizeDepth).create()).
        create();
    // (3)
    numScore3 = RenderObjectControl(
            VertexBufferObjectFileManager::the()->get(VertexBufferObjectControlFileOBJ("Quad.obj")),
        ShaderProgramObjectControl(ShaderProgramFileManager::the()->get(ShaderProgramControlAutoFiles("Number"))).
            uniform("uModelViewProjectionMatrix",   mpUniformModelViewProjectionMatrix).
            uniformTexture("uSamplerBaseColor",     UniformTextureControl(TextureFileManager::the()->get(TextureControlFileJPG("Status/Numbers/Score/3.png"))).create()).
            create(),
        FrameBufferObjectControl(). colorTexture("fFragDataColor", sizeColour).depthTexture(sizeDepth).create()).
        create();
    // (4)
    numScore4 = RenderObjectControl(
            VertexBufferObjectFileManager::the()->get(VertexBufferObjectControlFileOBJ("Quad.obj")),
        ShaderProgramObjectControl(ShaderProgramFileManager::the()->get(ShaderProgramControlAutoFiles("Number"))).
            uniform("uModelViewProjectionMatrix",   mpUniformModelViewProjectionMatrix).
            uniformTexture("uSamplerBaseColor",     UniformTextureControl(TextureFileManager::the()->get(TextureControlFileJPG("Status/Numbers/Score/4.png"))).create()).
            create(),
        FrameBufferObjectControl(). colorTexture("fFragDataColor", sizeColour).depthTexture(sizeDepth).create()).
        create();
    // (5)
    numScore5 = RenderObjectControl(
            VertexBufferObjectFileManager::the()->get(VertexBufferObjectControlFileOBJ("Quad.obj")),
        ShaderProgramObjectControl(ShaderProgramFileManager::the()->get(ShaderProgramControlAutoFiles("Number"))).
            uniform("uModelViewProjectionMatrix",   mpUniformModelViewProjectionMatrix).
            uniformTexture("uSamplerBaseColor",     UniformTextureControl(TextureFileManager::the()->get(TextureControlFileJPG("Status/Numbers/Score/5.png"))).create()).
            create(),
        FrameBufferObjectControl(). colorTexture("fFragDataColor", sizeColour).depthTexture(sizeDepth).create()).
        create();
    // (6)
    numScore6 = RenderObjectControl(
            VertexBufferObjectFileManager::the()->get(VertexBufferObjectControlFileOBJ("Quad.obj")),
        ShaderProgramObjectControl(ShaderProgramFileManager::the()->get(ShaderProgramControlAutoFiles("Number"))).
            uniform("uModelViewProjectionMatrix",   mpUniformModelViewProjectionMatrix).
            uniformTexture("uSamplerBaseColor",     UniformTextureControl(TextureFileManager::the()->get(TextureControlFileJPG("Status/Numbers/Score/6.png"))).create()).
            create(),
        FrameBufferObjectControl(). colorTexture("fFragDataColor", sizeColour).depthTexture(sizeDepth).create()).
        create();
    // (7)
    numScore7 = RenderObjectControl(
            VertexBufferObjectFileManager::the()->get(VertexBufferObjectControlFileOBJ("Quad.obj")),
        ShaderProgramObjectControl(ShaderProgramFileManager::the()->get(ShaderProgramControlAutoFiles("Number"))).
            uniform("uModelViewProjectionMatrix",   mpUniformModelViewProjectionMatrix).
            uniformTexture("uSamplerBaseColor",     UniformTextureControl(TextureFileManager::the()->get(TextureControlFileJPG("Status/Numbers/Score/7.png"))).create()).
            create(),
        FrameBufferObjectControl(). colorTexture("fFragDataColor", sizeColour).depthTexture(sizeDepth).create()).
        create();
    // (8)
    numScore8 = RenderObjectControl(
            VertexBufferObjectFileManager::the()->get(VertexBufferObjectControlFileOBJ("Quad.obj")),
        ShaderProgramObjectControl(ShaderProgramFileManager::the()->get(ShaderProgramControlAutoFiles("Number"))).
            uniform("uModelViewProjectionMatrix",   mpUniformModelViewProjectionMatrix).
            uniformTexture("uSamplerBaseColor",     UniformTextureControl(TextureFileManager::the()->get(TextureControlFileJPG("Status/Numbers/Score/8.png"))).create()).
            create(),
        FrameBufferObjectControl(). colorTexture("fFragDataColor", sizeColour).depthTexture(sizeDepth).create()).
        create();
    // (9)
    numScore9 = RenderObjectControl(
            VertexBufferObjectFileManager::the()->get(VertexBufferObjectControlFileOBJ("Quad.obj")),
        ShaderProgramObjectControl(ShaderProgramFileManager::the()->get(ShaderProgramControlAutoFiles("Number"))).
            uniform("uModelViewProjectionMatrix",   mpUniformModelViewProjectionMatrix).
            uniformTexture("uSamplerBaseColor",     UniformTextureControl(TextureFileManager::the()->get(TextureControlFileJPG("Status/Numbers/Score/9.png"))).create()).
            create(),
        FrameBufferObjectControl(). colorTexture("fFragDataColor", sizeColour).depthTexture(sizeDepth).create()).
        create();
    // - Numbers (Time)
    // (0)
    numTime0 = RenderObjectControl(
            VertexBufferObjectFileManager::the()->get(VertexBufferObjectControlFileOBJ("Quad.obj")),
        ShaderProgramObjectControl(ShaderProgramFileManager::the()->get(ShaderProgramControlAutoFiles("Number"))).
            uniform("uModelViewProjectionMatrix",   mpUniformModelViewProjectionMatrix).
            uniformTexture("uSamplerBaseColor",     UniformTextureControl(TextureFileManager::the()->get(TextureControlFileJPG("Status/Numbers/Time/0.png"))).create()).
            create(),
        FrameBufferObjectControl(). colorTexture("fFragDataColor", sizeColour).depthTexture(sizeDepth).create()).
        create();
    // (1)
    numTime1 = RenderObjectControl(
            VertexBufferObjectFileManager::the()->get(VertexBufferObjectControlFileOBJ("Quad.obj")),
        ShaderProgramObjectControl(ShaderProgramFileManager::the()->get(ShaderProgramControlAutoFiles("Number"))).
            uniform("uModelViewProjectionMatrix",   mpUniformModelViewProjectionMatrix).
            uniformTexture("uSamplerBaseColor",     UniformTextureControl(TextureFileManager::the()->get(TextureControlFileJPG("Status/Numbers/Time/1.png"))).create()).
            create(),
        FrameBufferObjectControl(). colorTexture("fFragDataColor", sizeColour).depthTexture(sizeDepth).create()).
        create();
    // (2)
    numTime2 = RenderObjectControl(
            VertexBufferObjectFileManager::the()->get(VertexBufferObjectControlFileOBJ("Quad.obj")),
        ShaderProgramObjectControl(ShaderProgramFileManager::the()->get(ShaderProgramControlAutoFiles("Number"))).
            uniform("uModelViewProjectionMatrix",   mpUniformModelViewProjectionMatrix).
            uniformTexture("uSamplerBaseColor",     UniformTextureControl(TextureFileManager::the()->get(TextureControlFileJPG("Status/Numbers/Time/2.png"))).create()).
            create(),
        FrameBufferObjectControl(). colorTexture("fFragDataColor", sizeColour).depthTexture(sizeDepth).create()).
        create();
    // (3)
    numTime3 = RenderObjectControl(
            VertexBufferObjectFileManager::the()->get(VertexBufferObjectControlFileOBJ("Quad.obj")),
        ShaderProgramObjectControl(ShaderProgramFileManager::the()->get(ShaderProgramControlAutoFiles("Number"))).
            uniform("uModelViewProjectionMatrix",   mpUniformModelViewProjectionMatrix).
            uniformTexture("uSamplerBaseColor",     UniformTextureControl(TextureFileManager::the()->get(TextureControlFileJPG("Status/Numbers/Time/3.png"))).create()).
            create(),
        FrameBufferObjectControl(). colorTexture("fFragDataColor", sizeColour).depthTexture(sizeDepth).create()).
        create();
    // (4)
    numTime4 = RenderObjectControl(
            VertexBufferObjectFileManager::the()->get(VertexBufferObjectControlFileOBJ("Quad.obj")),
        ShaderProgramObjectControl(ShaderProgramFileManager::the()->get(ShaderProgramControlAutoFiles("Number"))).
            uniform("uModelViewProjectionMatrix",   mpUniformModelViewProjectionMatrix).
            uniformTexture("uSamplerBaseColor",     UniformTextureControl(TextureFileManager::the()->get(TextureControlFileJPG("Status/Numbers/Time/4.png"))).create()).
            create(),
        FrameBufferObjectControl(). colorTexture("fFragDataColor", sizeColour).depthTexture(sizeDepth).create()).
        create();
    // (5)
    numTime5 = RenderObjectControl(
            VertexBufferObjectFileManager::the()->get(VertexBufferObjectControlFileOBJ("Quad.obj")),
        ShaderProgramObjectControl(ShaderProgramFileManager::the()->get(ShaderProgramControlAutoFiles("Number"))).
            uniform("uModelViewProjectionMatrix",   mpUniformModelViewProjectionMatrix).
            uniformTexture("uSamplerBaseColor",     UniformTextureControl(TextureFileManager::the()->get(TextureControlFileJPG("Status/Numbers/Time/5.png"))).create()).
            create(),
        FrameBufferObjectControl(). colorTexture("fFragDataColor", sizeColour).depthTexture(sizeDepth).create()).
        create();
    // (6)
    numTime6 = RenderObjectControl(
            VertexBufferObjectFileManager::the()->get(VertexBufferObjectControlFileOBJ("Quad.obj")),
        ShaderProgramObjectControl(ShaderProgramFileManager::the()->get(ShaderProgramControlAutoFiles("Number"))).
            uniform("uModelViewProjectionMatrix",   mpUniformModelViewProjectionMatrix).
            uniformTexture("uSamplerBaseColor",     UniformTextureControl(TextureFileManager::the()->get(TextureControlFileJPG("Status/Numbers/Time/6.png"))).create()).
            create(),
        FrameBufferObjectControl(). colorTexture("fFragDataColor", sizeColour).depthTexture(sizeDepth).create()).
        create();
    // (7)
    numTime7 = RenderObjectControl(
            VertexBufferObjectFileManager::the()->get(VertexBufferObjectControlFileOBJ("Quad.obj")),
        ShaderProgramObjectControl(ShaderProgramFileManager::the()->get(ShaderProgramControlAutoFiles("Number"))).
            uniform("uModelViewProjectionMatrix",   mpUniformModelViewProjectionMatrix).
            uniformTexture("uSamplerBaseColor",     UniformTextureControl(TextureFileManager::the()->get(TextureControlFileJPG("Status/Numbers/Time/7.png"))).create()).
            create(),
        FrameBufferObjectControl(). colorTexture("fFragDataColor", sizeColour).depthTexture(sizeDepth).create()).
        create();
    // (8)
    numTime8 = RenderObjectControl(
            VertexBufferObjectFileManager::the()->get(VertexBufferObjectControlFileOBJ("Quad.obj")),
        ShaderProgramObjectControl(ShaderProgramFileManager::the()->get(ShaderProgramControlAutoFiles("Number"))).
            uniform("uModelViewProjectionMatrix",   mpUniformModelViewProjectionMatrix).
            uniformTexture("uSamplerBaseColor",     UniformTextureControl(TextureFileManager::the()->get(TextureControlFileJPG("Status/Numbers/Time/8.png"))).create()).
            create(),
        FrameBufferObjectControl(). colorTexture("fFragDataColor", sizeColour).depthTexture(sizeDepth).create()).
        create();
    // (9)
    numTime9 = RenderObjectControl(
            VertexBufferObjectFileManager::the()->get(VertexBufferObjectControlFileOBJ("Quad.obj")),
        ShaderProgramObjectControl(ShaderProgramFileManager::the()->get(ShaderProgramControlAutoFiles("Number"))).
            uniform("uModelViewProjectionMatrix",   mpUniformModelViewProjectionMatrix).
            uniformTexture("uSamplerBaseColor",     UniformTextureControl(TextureFileManager::the()->get(TextureControlFileJPG("Status/Numbers/Time/9.png"))).create()).
            create(),
        FrameBufferObjectControl(). colorTexture("fFragDataColor", sizeColour).depthTexture(sizeDepth).create()).
        create();
    // (Timer)
    timer = RenderObjectControl(
            VertexBufferObjectFileManager::the()->get(VertexBufferObjectControlFileOBJ("Quad.obj")),
        ShaderProgramObjectControl(ShaderProgramFileManager::the()->get(ShaderProgramControlAutoFiles("Number"))).
            uniform("uModelViewProjectionMatrix",   mpUniformModelViewProjectionMatrix).
            uniformTexture("uSamplerBaseColor",     UniformTextureControl(TextureFileManager::the()->get(TextureControlFileJPG("Status/Numbers/Time/timer.png"))).create()).
            create(),
        FrameBufferObjectControl(). colorTexture("fFragDataColor", sizeColour).depthTexture(sizeDepth).create()).
        create();

}

void Stats::updatResize(int w, int h)
{
    mWidth = w;
    mHeight = h;
    mAR = (float)w/(float)h;
}

void Stats::paintStats(int iTime)
{
    mTime = iTime;

    // Draw both background bases
    drawSymbol('s', glm::vec3(-16.0f,-32.0f,-1.0f),glm::vec3(8.0f,1.3*3.0f,1.0f));
    drawSymbol('t', glm::vec3(18.0f,-32.0f,-1.0f),glm::vec3(5.0f,3.0f,1.0f));

    // Draw Flags

    if(team1 != RWTHi8)
        drawFlag(team1, glm::vec3(-21.60f,-28.95f,1.0f),glm::vec3(5.5f,1.3*3.0f,1.0f));
    else
        drawFlag(team1, glm::vec3(-21.10f,-28.90f,1.0f),glm::vec3(1.5f,8.0f/6.0f*1.5f,1.0f));
    if(team2 != RWTHi8)
        drawFlag(team2, glm::vec3(-10.40f,-28.95f,1.0f),glm::vec3(5.5f,1.3*3.0f,1.0f), false);
    else
        drawFlag(team2, glm::vec3(-10.90f,-28.90f,1.0f),glm::vec3(1.5,8.0f/6.0f*1.5f,1.0f), false);

    // Draw Score
    ostringstream ostr;
    ostr << nGoals1;
    string s1 = ostr.str();
    ostr.str("");
    ostr << nGoals2;
    string s2 = ostr.str();
    ostr.str("");
    drawSymbol(s1[0],glm::vec3(-17.90f,-30.5f,0.0f),glm::vec3(1.0f,2.0,1.0f), true);
    drawSymbol(s2[0],glm::vec3(-14.75f,-30.5f,0.0f),glm::vec3(1.0f,2.0,1.0f), true);

    // Update & Draw time
    ostr << mTime;
    string sTime = ostr.str();
    ostr.str("");
    char d1, d2;
    d1 = '0';
    if(sTime.size() > 1)
    {
        d1 = sTime[0];
        d2 = sTime[1];
        //cout << "Time Left " << d1 << d2 << endl;
    }
    else
        d2 = sTime[0];
    drawSymbol(d1,glm::vec3(19.00f,-32.5f,0.0f),glm::vec3(3.0f,6.0f,1.0f), false);
    drawSymbol(d2,glm::vec3(22.00f,-32.5f,0.0f),glm::vec3(3.0f,6.0f,1.0f), false);
    // Draw timer
    drawSymbol('o',glm::vec3(14.75f,-30.5f,0.0f),glm::vec3(1.0f,1.5f,1.0f), false);

}

void Stats::drawSymbol(char c, glm::vec3 translation, glm::vec3 scaling, bool score)
{
    setMatView(translation, scaling);
    mpUniformModelViewProjectionMatrix->setValue(matOrtho * matView );
    switch(c)
    {
        case'0':
        {
            score ? numScore0->render() : numTime0->render();
            break;
        }
        case'1':
        {
            score ? numScore1->render() : numTime1->render();
            break;
        }
        case'2':
        {
            score ? numScore2->render() : numTime2->render();
            break;
        }
        case'3':
        {
            score ? numScore3->render() : numTime3->render();
            break;
        }
        case'4':
        {
            score ? numScore4->render() : numTime4->render();
            break;
        }
        case'5':
        {
            score ? numScore5->render() : numTime5->render();
            break;
        }
        case'6':
        {
            score ? numScore6->render() : numTime6->render();
            break;
        }
        case'7':
        {
            score ? numScore7->render() : numTime7->render();
            break;
        }
        case'8':
        {
            score ? numScore8->render() : numTime8->render();
            break;
        }
        case'9':
        {
            score ? numScore9->render() : numTime9->render();
            break;
        }
        case'o':
        {
            timer->render();
            break;
        }
        case's':
        {
            backScore->render();
            break;
        }
        case't':
        {
            backTime->render();
            break;
        }
    }
}

void Stats::drawFlag(Country c, glm::vec3 translation, glm::vec3 scaling, bool left)
{
    setMatView(translation, scaling);
    mpUniformModelViewProjectionMatrix->setValue(matOrtho * matView );
    switch(c)
    {
        case Spain:
        {
            left ? leftSpa->render() : rightSpa->render();
            break;
        }
        case Germany:
        {
            left ? leftGer->render() : rightGer->render();
            break;
        }
        case Holland:
        {
            left ? leftHol->render() : rightHol->render();
            break;
        }
        case Italy:
        {
            left ? leftIta->render() : rightIta->render();
            break;
        }
        case Brazil:
        {
            left ? leftBra->render() : rightBra->render();
            break;
        }
        case Argentina:
        {
            left ? leftArg->render() : rightArg->render();
            break;
        }
        case RWTHi8:
        {
            flagI8->render();
            break;
        }
    }
}

void Stats::setOrthoView()
{
    // Orthogonal matrix - only once at the begining is enough (assuming no windows resize)
    float near = -100.0f, far = 100.0f;
    float left = -20.0f*(mAR);
    float right = 20.0f*(mAR);
    float bottom = -20.0f;
    float top = 20.0f;
    if(mWidth < mHeight )
    {
        left = -20.0f;
        right = 20.0f;
        bottom = -20.0f/(mAR);
        top = 20.0f/(mAR);
    }

    // First Column
    matOrtho[0][0] = 2.0f / (right - left);
    // Second Column
    matOrtho[1][1] = 2.0f / (top - bottom);
    // Third Column
    matOrtho[2][2] = -2.0f / (far - near);
    // Fourth Column
    matOrtho[3][0] = -(right + left) / (right - left);
    matOrtho[3][1] = -(top + bottom) / (top - bottom);
    matOrtho[3][2] = -(far + near) / (far - near);
    matOrtho[3][3] = 1.0f;
}

void Stats::setMatView(glm::vec3 trans, glm::vec3 scal)
{
    // MAKE A PERSONALIZED VIEW MATRIX TO ALWAYS REMAIN STATIC, NO MATTER WHAT CAMERA DOES
    matView = mpWorld->getCamera()->getViewMatrix();
    // (6) Apply currect camera positions (with respect of the initial one)
    glm::vec3 mPos = mpWorld->getCamera()->getPosition();
    matView = glm::translate(matView,glm::vec3(mPos.x-mpWorld->INIT_CAM_X, mPos.y-mpWorld->INIT_CAM_Y, mPos.z-mpWorld->INIT_CAM_Z));
    // (5) Add camera initial position
    matView = glm::translate(matView,glm::vec3(mpWorld->INIT_CAM_X, mpWorld->INIT_CAM_Y, mpWorld->INIT_CAM_Z));
    // (4) Apply currect camera rotations
    matView = glm::rotate(matView, mpWorld->getCamera()->getYaw(), glm::vec3(0.0f,1.0f,0.0f));
    matView = glm::rotate(matView, mpWorld->getCamera()->getPitch(), glm::vec3(1.0f,0.0f,0.0f));
    // (3) Substract initial camera rotation (only X axis)
    matView = glm::rotate(matView, -mpWorld->INIT_PITCH, glm::vec3(1.0f,0.0f,0.0f));
    // (2) Substract camera initial position
    matView = glm::translate(matView,glm::vec3(-mpWorld->INIT_CAM_X, -mpWorld->INIT_CAM_Y, -mpWorld->INIT_CAM_Z));
    // (1) Wherever we want in the 2D-screen: no offset means centered (x_pos,y_pos,size)
    matView = glm::translate(matView,glm::vec3(trans.x, trans.y, trans.z));
    // (0) Scaling for font's size
    matView = glm::scale(matView, glm::vec3(scal.x, scal.y, scal.z));

    /*
    // (6) Apply currect camera positions (with respect of the initial one)
    ModelViewMatrixStack::the()->translate(mpWorld->getCamera()->getPosition().x-mpWorld->INIT_CAM_X,
                                           mpWorld->getCamera()->getPosition().y-mpWorld->INIT_CAM_Y,
                                           mpWorld->getCamera()->getPosition().z-mpWorld->INIT_CAM_Z);
    // (5) Add camera initial position
    ModelViewMatrixStack::the()->translate(mpWorld->INIT_CAM_X, mpWorld->INIT_CAM_Y, mpWorld->INIT_CAM_Z);
    // (4) Apply currect camera rotations
    ModelViewMatrixStack::the()->rotate(mpWorld->getCamera()->getYaw(),0.0f,1.0f,0.0f);
    ModelViewMatrixStack::the()->rotate(mpWorld->getCamera()->getPitch(),1.0f,0.0f,0.0f);
    // (3) Substract initial camera rotation (only X axis)
    ModelViewMatrixStack::the()->rotate(-mpWorld->INIT_PITCH,1.0f,0.0f,0.0f);
    // (2) Substract camera initial position
    ModelViewMatrixStack::the()->translate(-mpWorld->INIT_CAM_X, -mpWorld->INIT_CAM_Y, -mpWorld->INIT_CAM_Z);
    // (1) Wherever we want in the 2D-screen: no offset means centered (x_pos,y_pos,size)
    ModelViewMatrixStack::the()->translate(5.0f,5.0f,0.0f);
    */
}

void Stats::incrScore(int nRobot)
{
    if(nRobot == 1)
        nGoals1++;
    else
        nGoals2++;
}

void Stats::setTeam(int nRobot, Country team)
{
    if(nRobot == 1)
        team1 = team;
    else
       team2 = team;
}
