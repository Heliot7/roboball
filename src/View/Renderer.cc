////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2011, Computer Graphics Group RWTH Aachen University         //
// All rights reserved.                                                       //
////////////////////////////////////////////////////////////////////////////////

#include "Renderer.hh"
#include "../Physics/Object.hh"
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

Renderer::Renderer(
    const std::tr1::shared_ptr<World>& _pWorld, QGLWidget* parent)
:   ViewWorld(),
    mpWorld(_pWorld),
    mpRenderObjectFullscreenClear(),
    mpRenderObjectVertexColorGrid(),
    mpRenderObjectPostProcessGrayScale(),
    mpUniformModelViewProjectionMatrix(UniformMatrix4fControl().create()),
    mpUniformModelViewMatrix(UniformMatrix4fControl().create()),
    mpUniformNormalMatrix(UniformMatrix3fControl().create()),
    vAttenuationLight(glm::vec3(0.0,0.0,0.002)),
    vPositionLight(glm::vec4(0.0,15.0,15.0,1.0)),
    mpArrayBufferGrid(),
    mScreenSizeRenderTargets(),
    qglW(parent),
    mStats(new Stats(parent, _pWorld)),
    mRobot1(new Robot(1, Spain, glm::vec3(-5.0,0.0,0.0))),
    mRobot2(new Robot(2, Germany, glm::vec3(5.0,0.0,0.0))),
    mBall(new RigidBody(glm::vec3(0.0,0.0,0.0), 1, "/NpV_Ball.obj", 0.55f)),
    mLeftWall(new RigidBody(glm::vec3(0.0,0.0,0.0), 9999, "/Field/LeftSideMain.obj")),
    mLeftGoalBase(new RigidBody(glm::vec3(0.0,0.0,0.0), 9999, "/Field/LeftSideGoalBase.obj")),
    mLeftGoalTop(new RigidBody(glm::vec3(0.0,0.0,0.0), 9999, "/Field/LeftSideGoalTop.obj")),
    mLeftGoalLeft(new RigidBody(glm::vec3(0.0,0.0,0.0), 9999, "/Field/LeftSideGoalLeft.obj")),
    mLeftGoalRight(new RigidBody(glm::vec3(0.0,0.0,0.0), 9999, "/Field/LeftSideGoalRight.obj")),
    mLeftGoalBack(new RigidBody(glm::vec3(0.0,0.0,0.0), 9999, "/Field/LeftSideGoalBack.obj")),
    mRightWall(new RigidBody(glm::vec3(0.0,0.0,0.0), 9999, "/Field/RightSideMain.obj")),
    mRightGoalBase(new RigidBody(glm::vec3(0.0,0.0,0.0), 9999, "/Field/RightSideGoalBase.obj")),
    mRightGoalTop(new RigidBody(glm::vec3(0.0,0.0,0.0), 9999, "/Field/RightSideGoalTop.obj")),
    mRightGoalLeft(new RigidBody(glm::vec3(0.0,0.0,0.0), 9999, "/Field/RightSideGoalLeft.obj")),
    mRightGoalRight(new RigidBody(glm::vec3(0.0,0.0,0.0), 9999, "/Field/RightSideGoalRight.obj")),
    mRightGoalBack(new RigidBody(glm::vec3(0.0,0.0,0.0), 9999, "/Field/RightSideGoalBack.obj")),
    mBackWall(new RigidBody(glm::vec3(0.0,0.0,0.0), 9999, "/Field/BackSide.obj")),
    mStand(new RigidBody(glm::vec3(0.0,0.0,0.0), 9999, "/Field/Stand.obj")),
    mFrontWall(new RigidBody(glm::vec3(0.0,0.0,0.0), 9999, "/Field/FrontSide.obj")),
    mFrontWallFake(new RigidBody(glm::vec3(0.0,0.0,0.0), 9999, "/Field/BackSide.obj")),
    mGround(new RigidBody(glm::vec3(0.0,0.0,0.0), 9999, "/Field/Ground.obj")),
    gravity(-9.8),
    damping(500),
    time(-0.999),
    endTime(5.0),
    maxTime(60.0),
    mState(Config),
    mRobotConfigView(new RobotConfigView(_pWorld,&mState,&maxGoals,&maxTime)),
    mFinishView(new FinishView(_pWorld)),
    mGoalView(new GoalView(_pWorld)),
    mGrass(new GrassBlade()),
    maxGoals(3),
    fakeWall(false)
{
    listWalls.push_back(mGround);
    listWalls.push_back(mBackWall);
    listWalls.push_back(mFrontWall);
    listSideWalls.push_back(mLeftWall);
    listSideWalls.push_back(mRightWall);
    listGoalies.push_back(mRightGoalBase);
    listGoalies.push_back(mRightGoalTop);
    listGoalies.push_back(mRightGoalLeft);
    listGoalies.push_back(mRightGoalRight);
    listGoalies.push_back(mRightGoalBack);
    listGoalies.push_back(mLeftGoalBase);
    listGoalies.push_back(mLeftGoalTop);
    listGoalies.push_back(mLeftGoalLeft);
    listGoalies.push_back(mLeftGoalRight);
    listGoalies.push_back(mLeftGoalBack);
}

void Renderer::setQGLWidget(QGLWidget* qglwidget)
{
    qglW = qglwidget;
}

Renderer::~Renderer(void)
{}

/*
 * This will set everything graphics related up before the renderloop gets called the first time.
 */
void Renderer::init(void)
{    
    glDisable(GL_DEPTH_TEST);
    glDepthMask(GL_FALSE);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    TextureControl screenSizeDepthTexture = TextureControl().
        target(GL_TEXTURE_2D).
        size(16, 16).
        internalFormat(GL_DEPTH24_STENCIL8).
        format(GL_DEPTH_STENCIL).
        type(GL_UNSIGNED_INT_24_8).
        minFilter(GL_NEAREST).
        magFilter(GL_NEAREST);

    TextureControl screenSizeColorTexture = TextureControl().
        target(GL_TEXTURE_RECTANGLE).
        size(16, 16).
        internalFormat(GL_RGBA).
        format(GL_RGBA).
        type(GL_FLOAT).
        minFilter(GL_NEAREST).
        magFilter(GL_NEAREST);

    pTextureScreenSizeDepth = screenSizeDepthTexture.create();
    pTextureScreenSizeColor = screenSizeColorTexture.create();

    mScreenSizeRenderTargets.push_back( pTextureScreenSizeDepth );
    mScreenSizeRenderTargets.push_back( pTextureScreenSizeColor );

    openGLCriticalErrorOccured();

    /////////////////////////////////////////////////////////////////////////////////////////////////
    //
    // Here we create a fullscreen quad:
    //

    float quadData[] = {
    //  Vx,   Vy,   Vz,   Vw
      -1.0,  1.0,  0.0,  1.0,
      -1.0, -1.0,  0.0,  1.0,
       1.0,  1.0,  0.0,  1.0,
       1.0, -1.0,  0.0,  1.0
    };
    unsigned int quadIndices[] = {0, 1, 2, 2, 1, 3};

    ConstSharedVertexBufferObject pVertexBufferObjectQuad = VertexBufferObjectControl().
        index(ElementArrayBufferControl().
            mode(GL_TRIANGLES).
            usage(GL_STATIC_DRAW).
            type(GL_UNSIGNED_INT).
            data(quadIndices, 6).
            create()).
        data(ArrayBufferControl().
            mode(GL_TRIANGLES).
            usage(GL_STATIC_DRAW).
            attribute("aPosition", GL_FLOAT, 4).
            data(quadData, 4).
            create()).
        attribute("aPosition", "aPosition").
        create();

    //
    // End of the fullscreen quad creation
    //
    /////////////////////////////////////////////////////////////////////////////////////////////////

    //Pass 1: Clear the background to some gradient color
    // something like glClear will also do, but we want not only to clear some buffers but render a nice color gradient at the same time
    mpRenderObjectFullscreenClear = RenderObjectControl(
        pVertexBufferObjectQuad,
        ShaderProgramObjectControl(ShaderProgramFileManager::the()->get(ShaderProgramControlAutoFiles("GradientClear"))).
            uniform("uFirstColor",  Uniform3fControl(glm::vec3(0.9411, 0.9411, 0.9411)).create()).
            uniform("uSecondColor", Uniform3fControl(glm::vec3(0.9, 0.9, 1.0)).create()).
            create(),
        FrameBufferObjectControl().
            colorTexture("fFragDataGradient", pTextureScreenSizeColor).
            create()).
        create();

    //Pass 3: Render the grid on top
    mpArrayBufferGrid = ArrayBufferControl().
            mode(GL_LINES).
            usage(GL_STREAM_DRAW).
            attribute("aPosition", GL_FLOAT, 4).
            attribute("aColor", GL_FLOAT, 4).
        create();
    mpRenderObjectVertexColorGrid = RenderObjectControl(
        VertexBufferObjectControl().
            data(mpArrayBufferGrid).
            attribute("aPosition", "aPosition").
            attribute("aColor", "aColor").
            create(),
        ShaderProgramObjectControl(ShaderProgramFileManager::the()->get(ShaderProgramControlAutoFiles("VertexColor"))).
            uniform("uModelViewProjectionMatrix", mpUniformModelViewProjectionMatrix).
            create(),
        FrameBufferObjectControl().
            colorTexture("fFragDataColor", pTextureScreenSizeColor).
            depthTexture(pTextureScreenSizeDepth).
            create()).
        create();

    //Pass 4: Send the color texture and thereby also apply some simple post process
    mpRenderObjectPostProcessGrayScale = RenderObjectControl(
        pVertexBufferObjectQuad,
        ShaderProgramObjectControl(ShaderProgramFileManager::the()->get(ShaderProgramControlAutoFiles("PostProcessGrayScale"))).
            uniformTexture("uSamplerImage", UniformTextureControl(pTextureScreenSizeColor).create()).
            create()).
        create();

    //Pass Robo-ball:
    // - Init. camera
    updateCameraPosition();

    // - Cage
    mGround->initRender(mpUniformNormalMatrix, mpUniformModelViewMatrix, mpUniformModelViewProjectionMatrix,
                        pTextureScreenSizeColor, pTextureScreenSizeDepth, "Phong", "Field/Grass.png", vPositionLight, vAttenuationLight);
    mLeftWall->initRender(mpUniformNormalMatrix, mpUniformModelViewMatrix, mpUniformModelViewProjectionMatrix,
                        pTextureScreenSizeColor, pTextureScreenSizeDepth, "Bump", "Field/LeftSide.png", "Field/LeftSide_NRM.png", vPositionLight, vAttenuationLight);
    mLeftGoalTop->initRender(mpUniformNormalMatrix, mpUniformModelViewMatrix, mpUniformModelViewProjectionMatrix,
                        pTextureScreenSizeColor, pTextureScreenSizeDepth, "Phong", "Field/Goal1.png", vPositionLight, vAttenuationLight);
    mLeftGoalBack->initRender(mpUniformNormalMatrix, mpUniformModelViewMatrix, mpUniformModelViewProjectionMatrix,
                        pTextureScreenSizeColor, pTextureScreenSizeDepth, "Phong", "Field/Goal1.png", vPositionLight, vAttenuationLight);
    mLeftGoalLeft->initRender(mpUniformNormalMatrix, mpUniformModelViewMatrix, mpUniformModelViewProjectionMatrix,
                        pTextureScreenSizeColor, pTextureScreenSizeDepth, "Phong", "Field/Goal2.png", vPositionLight, vAttenuationLight);
    mLeftGoalRight->initRender(mpUniformNormalMatrix, mpUniformModelViewMatrix, mpUniformModelViewProjectionMatrix,
                        pTextureScreenSizeColor, pTextureScreenSizeDepth, "Phong", "Field/Goal2.png", vPositionLight, vAttenuationLight);
    mLeftGoalBase->initRender(mpUniformNormalMatrix, mpUniformModelViewMatrix, mpUniformModelViewProjectionMatrix,
                        pTextureScreenSizeColor, pTextureScreenSizeDepth, "Phong", "Field/Goal1.png", vPositionLight, vAttenuationLight);
    mRightWall->initRender(mpUniformNormalMatrix, mpUniformModelViewMatrix, mpUniformModelViewProjectionMatrix,
                        pTextureScreenSizeColor, pTextureScreenSizeDepth, "Bump", "Field/RightSide.png","Field/RightSide_NRM.png", vPositionLight, vAttenuationLight);
    mRightGoalTop->initRender(mpUniformNormalMatrix, mpUniformModelViewMatrix, mpUniformModelViewProjectionMatrix,
                        pTextureScreenSizeColor, pTextureScreenSizeDepth, "Phong", "Field/Goal1.png", vPositionLight, vAttenuationLight);
    mRightGoalBack->initRender(mpUniformNormalMatrix, mpUniformModelViewMatrix, mpUniformModelViewProjectionMatrix,
                        pTextureScreenSizeColor, pTextureScreenSizeDepth, "Phong", "Field/Goal1.png", vPositionLight, vAttenuationLight);
    mRightGoalLeft->initRender(mpUniformNormalMatrix, mpUniformModelViewMatrix, mpUniformModelViewProjectionMatrix,
                        pTextureScreenSizeColor, pTextureScreenSizeDepth, "Phong", "Field/Goal2.png", vPositionLight, vAttenuationLight);
    mRightGoalRight->initRender(mpUniformNormalMatrix, mpUniformModelViewMatrix, mpUniformModelViewProjectionMatrix,
                        pTextureScreenSizeColor, pTextureScreenSizeDepth, "Phong", "Field/Goal2.png", vPositionLight, vAttenuationLight);
    mRightGoalBase->initRender(mpUniformNormalMatrix, mpUniformModelViewMatrix, mpUniformModelViewProjectionMatrix,
                        pTextureScreenSizeColor, pTextureScreenSizeDepth, "Phong", "Field/Goal1.png", vPositionLight, vAttenuationLight);
    mBackWall->initRender(mpUniformNormalMatrix, mpUniformModelViewMatrix, mpUniformModelViewProjectionMatrix,
                        pTextureScreenSizeColor, pTextureScreenSizeDepth, "Bump", "Field/BackSide.png", "Field/BackSide_NRM.png", vPositionLight, vAttenuationLight);
    mFrontWallFake->initRender(mpUniformNormalMatrix, mpUniformModelViewMatrix, mpUniformModelViewProjectionMatrix,
                        pTextureScreenSizeColor, pTextureScreenSizeDepth, "Mirror", "Field/Mirror.png", vPositionLight, vAttenuationLight);
    mStand->initRender(mpUniformNormalMatrix, mpUniformModelViewMatrix, mpUniformModelViewProjectionMatrix,
                        pTextureScreenSizeColor, pTextureScreenSizeDepth, "Phong", "Field/Stand.png", vPositionLight, vAttenuationLight);
    // - Ball
    mBall->initRender(mpUniformNormalMatrix, mpUniformModelViewMatrix, mpUniformModelViewProjectionMatrix,
                      pTextureScreenSizeColor, pTextureScreenSizeDepth, "Bump", "Ball/Ball.png", "Ball/Ball_NRM.jpg", vPositionLight, vAttenuationLight);
    mBall->setPos(vec3(0.0,0.0,0.0));
    mBall->setVel(vec3(0.0,0.0,0.0));
    mBall->setAngVel(vec3(0.0,0.0,0.0));

    // - Robot1
    mRobot1->initRender(mpUniformNormalMatrix, mpUniformModelViewMatrix, mpUniformModelViewProjectionMatrix,
                        pTextureScreenSizeColor, pTextureScreenSizeDepth, vPositionLight, vAttenuationLight,
                        "Phong", "Phong", "Phong", "Players/Robot_Hol.png", "Robot/Kick_Flat_Texture.png", "Robot/Kick_Volley_Texture.png");
    mRobot2->initRender(mpUniformNormalMatrix, mpUniformModelViewMatrix, mpUniformModelViewProjectionMatrix,
                        pTextureScreenSizeColor, pTextureScreenSizeDepth, vPositionLight, vAttenuationLight,
                        "Phong", "Phong", "Phong", "Players/Robot_Ita.png", "Robot/Kick_Flat_Texture.png", "Robot/Kick_Volley_Texture.png");
    //mRobot2->getBody()->setAngleY(180.0);
    mRobot1->getBody()->setAngleY(180.0);
    mRobot1->getBody()->setPos(vec3(5.0,0.0,0.0));
    mRobot2->getBody()->setPos(vec3(0.0,0.0,10.0));

    mRobotConfigView->initView(pTextureScreenSizeDepth, pTextureScreenSizeColor, mRobot1, mRobot2);
    mGoalView->initView(pTextureScreenSizeDepth, pTextureScreenSizeColor);
    mFinishView->initView(pTextureScreenSizeDepth, pTextureScreenSizeColor);


    // Init stats
    mStats->initStats(pTextureScreenSizeDepth, pTextureScreenSizeColor);

    mGrass->initGrass(mpUniformModelViewProjectionMatrix, pTextureScreenSizeDepth, pTextureScreenSizeColor);

    if (openGLCriticalErrorOccured()) error() << "init failed!" << std::endl;
}

void Renderer::moveCameratoGoal(int duration, double currentTime) {

    //mpWorld->getCamera()->setPosition(vec3(0.0f,26.875f,17.5f));
    //mpWorld->getCamera()->setOrientation(-57, 0, 0);

    //mpWorld->getCamera()->setPosition(vec3(-16.20f,5.25f,-5.57));
    //mpWorld->getCamera()->setOrientation(-30, 145, 0);

    //mpWorld->getCamera()->setPosition(vec3(16.20f,5.25f,-5.57));
    //mpWorld->getCamera()->setOrientation(-30, -145, 0);

    //vec3 position = mpWorld->getCamera()->getPosition();
    //float pitch = mpWorld->getCamera()->getPitch();
    //float yaw = mpWorld->getCamera()->getYaw();

    double step = currentTime/duration;
    if(isGoal(-1)) {
    mpWorld->getCamera()->setPosition(vec3(0.0f-step*16.20f,26.875-step*21.625,17.5f-step*23.07));
    mpWorld->getCamera()->setOrientation(-57+step*27, 0+step*145, 0);
    }

    if(isGoal(1)) {
    mpWorld->getCamera()->setPosition(vec3(0.0f+step*16.20f,26.875-step*21.625,17.5f-step*23.07));
    mpWorld->getCamera()->setOrientation(-57+step*27, 0-step*145, 0);
    }

}

/////////////////////////////////////////////////////////////////////////////////////////////////
//
// This gets called as often as possible to render our game.
//
void Renderer::paint(double timeStep)
{
    ModelViewMatrixStack::the()->loadMatrix( mpWorld->getCamera()->getViewMatrix() );
    /////////////////////////////////////////////////////////////////////////////////////////////////
    // clear with a gradient color
    //
    mpRenderObjectFullscreenClear->render();
    //
    /////////////////////////////////////////////////////////////////////////////////////////////////

    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);

    /////////////////////////////////////////////////////////////////////////////////////////////////
    // And extra walls to complete the field
    //
    /*
    ModelViewMatrixStack::the()->pushMatrix();
        ModelViewMatrixStack::the()->rotate(-90.0,1.0,0.0,0.0);
        ModelViewMatrixStack::the()->scale(25.0,25.0,25.0);
        ModelViewMatrixStack::the()->translate(0.0,-1.0,0.0);
        ModelViewMatrixStack::the()->translate(-mBackWall->getObj()->boundingBox().centreBox());
        mpUniformModelViewMatrix->setValue(ModelViewMatrixStack::the()->topMatrix());
        mpUniformNormalMatrix->setValue(ModelViewMatrixStack::the()->topNormalMatrix());
        mpUniformModelViewProjectionMatrix->setValue( mpWorld->getCamera()->getProjectionMatrix() * ModelViewMatrixStack::the()->topMatrix() );
        mBackWall->getRender()->render();
    ModelViewMatrixStack::the()->popMatrix();
    */
    //
    /////////////////////////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////
    // Rendering of example objects
    //
    ModelViewMatrixStack::the()->pushMatrix();
        mpUniformModelViewProjectionMatrix->setValue( mpWorld->getCamera()->getProjectionMatrix() * ModelViewMatrixStack::the()->topMatrix() );
        mpUniformModelViewMatrix->setValue(ModelViewMatrixStack::the()->topMatrix());
        mpUniformNormalMatrix->setValue(ModelViewMatrixStack::the()->topNormalMatrix());
        mGround->getRender()->enable();
        glClear(GL_DEPTH_BUFFER_BIT);
        mGround->getRender()->draw();
        mGround->getRender()->disable();
        mLeftWall->getRender()->render();
        mLeftGoalTop->getRender()->render();
        mLeftGoalBack->getRender()->render();
        mLeftGoalBase->getRender()->render();
        mLeftGoalLeft->getRender()->render();
        mLeftGoalRight->getRender()->render();
        mRightWall->getRender()->render();
        mRightGoalTop->getRender()->render();
        mRightGoalBack->getRender()->render();
        mRightGoalBase->getRender()->render();
        mRightGoalLeft->getRender()->render();
        mRightGoalRight->getRender()->render();
        mBackWall->getRender()->render();
    ModelViewMatrixStack::the()->popMatrix();

    for(float i = 0.0f; i < 10.0f; ++i)
    {
        ModelViewMatrixStack::the()->pushMatrix();
            ModelViewMatrixStack::the()->translate(0.0f, i, i);
            mpUniformModelViewProjectionMatrix->setValue( mpWorld->getCamera()->getProjectionMatrix() * ModelViewMatrixStack::the()->topMatrix() );
            mStand->getRender()->render();
            ModelViewMatrixStack::the()->translate(0.0f, 0.0f, 12.0f);
            ModelViewMatrixStack::the()->rotate(-90.0f, 1.0f, 0.0f, 0.0f);
            ModelViewMatrixStack::the()->translate(0.0f, 0.0f, -13.0f);
            mpUniformModelViewProjectionMatrix->setValue( mpWorld->getCamera()->getProjectionMatrix() * ModelViewMatrixStack::the()->topMatrix() );
            mpUniformModelViewMatrix->setValue(ModelViewMatrixStack::the()->topMatrix());
            mpUniformNormalMatrix->setValue(ModelViewMatrixStack::the()->topNormalMatrix());
            mStand->getRender()->render();
        ModelViewMatrixStack::the()->popMatrix();
    }

    ModelViewMatrixStack::the()->pushMatrix();
        ModelViewMatrixStack::the()->translate(mBall->getPos());
        ModelViewMatrixStack::the()->translate(mBall->getObj()->boundingBox().centreBox());
        ModelViewMatrixStack::the()->rotate(mBall->getAngleY(), vec3(0.0,1.0,0.0));
        ModelViewMatrixStack::the()->rotate(mBall->getAngleZ(), vec3(0.0,0.0,1.0));
        ModelViewMatrixStack::the()->rotate(mBall->getAngleX(), vec3(1.0,0.0,0.0));
        ModelViewMatrixStack::the()->translate(-mBall->getObj()->boundingBox().centreBox());
        mpUniformModelViewMatrix->setValue(ModelViewMatrixStack::the()->topMatrix());
        mpUniformNormalMatrix->setValue(ModelViewMatrixStack::the()->topNormalMatrix());
        mpUniformModelViewProjectionMatrix->setValue( mpWorld->getCamera()->getProjectionMatrix() * ModelViewMatrixStack::the()->topMatrix() );        
        mBall->getRender()->render();
    ModelViewMatrixStack::the()->popMatrix();

    mRobot1->paint(mpUniformModelViewProjectionMatrix, mpUniformModelViewMatrix, mpUniformNormalMatrix, mpWorld);
    mRobot2->paint(mpUniformModelViewProjectionMatrix, mpUniformModelViewMatrix, mpUniformNormalMatrix, mpWorld);

    /////////////////////////////////////////////////////////////////////////////////////////////////
    // draw fake front wall
    //
    if(fakeWall)
    {
        glEnable(GL_BLEND);
        ModelViewMatrixStack::the()->pushMatrix();
        ModelViewMatrixStack::the()->translate(0.0f, 0.0f, mFrontWall->getObj()->boundingBox().min.z - mFrontWallFake->getObj()->boundingBox().min.z);
        mpUniformModelViewProjectionMatrix->setValue( mpWorld->getCamera()->getProjectionMatrix() * ModelViewMatrixStack::the()->topMatrix() );
        mpUniformModelViewMatrix->setValue(ModelViewMatrixStack::the()->topMatrix());
        mpUniformNormalMatrix->setValue(ModelViewMatrixStack::the()->topNormalMatrix());
        mFrontWallFake->getRender()->render();
        ModelViewMatrixStack::the()->popMatrix();
        glDisable(GL_BLEND);
    }
    //
    /////////////////////////////////////////////////////////////////////////////////////////////////

    switch (mState) {
        case Play:
        /////////////////////////////////////////////////////////////////////////////////////////////////
        // draw all status of the game (score, timing, team names,...)
        //
        updatePhysics(timeStep);
        updateGame(timeStep);
        glEnable(GL_BLEND);
        mStats->paintStats((int)(maxTime - time));
        glDisable(GL_BLEND);
        //
        /////////////////////////////////////////////////////////////////////////////////////////////////
        break;

       case Goal:
            glEnable(GL_BLEND);
            mStats->paintStats((int)(maxTime - time));
            glDisable(GL_BLEND);
            // draw goal screen
            glEnable(GL_BLEND);
             mGoalView->paint(exp(waitTime));
            glDisable(GL_BLEND);
            //wait 2s
            waitTime += timeStep;
            moveCameratoGoal(2, waitTime);
            if (waitTime > 2)
            {
                // reset Player and Ball
                this->resetBallAndRobots();
                // reset view
                mpWorld->getCamera()->setPosition(vec3(0.0f,26.875f,17.5f));
                mpWorld->getCamera()->setOrientation(-57, 0, 0);
                mState = Play;
            }

        break;

         case Finish:
        glEnable(GL_BLEND);
        mStats->paintStats((int)(maxTime - time));
        glDisable(GL_BLEND);
        glEnable(GL_BLEND);
        mFinishView->paint();
        glDisable(GL_BLEND);
            // draw Finish Screen (and the winner)
        endTime -= timeStep;
        if(endTime < 0)
        {
            endTime = 5.0;
            mState = Config;
        }
        break;

        case Config: // will also be the starting screen?
        // reset Player and Ball
        this->resetBallAndRobots();
        // reset Time -> TODO: Move this to the config Menu
        time = 0;
        // reset Goals -> TODO: Move this to the config Menu
        mStats->resetStats();

        // draw config screen
        glEnable(GL_BLEND);
        mRobotConfigView->paint();
        glDisable(GL_BLEND);

        break;
    }

    glDepthMask(GL_FALSE);
    glDisable(GL_DEPTH_TEST);

    /////////////////////////////////////////////////////////////////////////////////////////////////
    // bring the rendered texture to the screen
    //
    mpRenderObjectPostProcessGrayScale->render();
    //
    /////////////////////////////////////////////////////////////////////////////////////////////////

    openGLRareErrorOccured(); // rare error checks have to be enabled to get compiled into the app,
                              // (because it should be rare that an error occured here). but if we get an
                              // error somewhere and we don't know what triggered it, just activate all rare checks
                              // and hopefully we will find the problem more easily.
}

/*
 * When the window gets resized, this function gets called
 */
void Renderer::resize(int iWidth, int iHeight)
{
    mpWorld->getCamera()->setWidth(iWidth);
    mpWorld->getCamera()->setHeight(iHeight);
    mStats->updatResize(iWidth, iHeight);
    mStats->setOrthoView();
    mRobotConfigView->updatResize(iWidth, iHeight);
    mGoalView->updatResize(iWidth, iHeight);
    mFinishView->updatResize(iWidth, iHeight);
    updateCameraPosition();

    glViewport(0, 0, iWidth, iHeight);

    // Resize all textures:
    // In this app the textures used as render targets are not handled by a Manager but by this
    // class in a std::vector. We could however use a Manager if we like.
    for (unsigned int i = 0; i < mScreenSizeRenderTargets.size(); ++i ) {
        mScreenSizeRenderTargets[i]->setImageData2D( NULL, iWidth, iHeight );
    }
}

void Renderer::updateCameraPosition()
{
    float w = mpWorld->getCamera()->getWidth();
    float h = mpWorld->getCamera()->getHeight();
    mpWorld->INIT_CAM_X = 0.0f;
    mpWorld->INIT_CAM_Y = 1.25*21.5f;
    mpWorld->INIT_CAM_Z = 1.25*14.0f;
    glm::vec3 mUp = glm::vec3(0.0f,1.0f,0.0f);
    //if(w/h < 1.0)
    //    mpWorld->getCamera()->setPosition(glm::vec3(mpWorld->INIT_CAM_X/(w/h), mpWorld->INIT_CAM_Y/(w/h), mpWorld->INIT_CAM_Z/(w/h)), mUp, false);
    //else
    //    mpWorld->getCamera()->setPosition(glm::vec3(w/h*mpWorld->INIT_CAM_X, w/h*mpWorld->INIT_CAM_Y, w/h*mpWorld->INIT_CAM_Z), mUp, false);
    mpWorld->getCamera()->setPosition(glm::vec3(mpWorld->INIT_CAM_X, mpWorld->INIT_CAM_Y, mpWorld->INIT_CAM_Z), mUp, false);
    mpWorld->getCamera()->setRoll(0.0f);
    mpWorld->getCamera()->setYaw(0.0f);

    // New FOV to keep aspect ratio
    calcFrustum(w,h);

    // New pitch
    glm::vec3 mForward = glm::normalize(mpWorld->getCamera()->getTarget() - mpWorld->getCamera()->getPosition());
    glm::vec3 mRight = glm::normalize(glm::cross(mForward,mUp));
    mUp = glm::normalize(glm::cross(mRight,mForward));
    mpWorld->INIT_PITCH = Functions::atan2Deg(mForward.y,mUp.y);
    //mpWorld->getCamera()->setPitch(mpWorld->INIT_PITCH);
    //cout << "new pitch " << mpWorld->INIT_PITCH << endl;
}

void Renderer::calcFrustum(int width, int height)
{
    vec3 p = mpWorld->getCamera()->getPosition();
    float R = sqrt(p.x*p.x+p.y*p.y+p.z*p.z);
    float dist = 2 * R;
    float ar = (float)width / (float)height;
    // Angle calculation
    float alpha = 0.0, alphaH, lx, ly;
    // Depending on the AR we calculate angle so there are no deformations    
    if(ar >= 1)
        alpha = asin( R / dist);
    else if(ar < 1) {
        alphaH = asin( R / dist );
        lx = dist * tan( alphaH );
        ly = lx / ar;
        alpha = atan( ly / dist );
    }
    // We calculate FOV
    mpWorld->getCamera()->setFOV(2 * alpha*180.0/3.1416);
}

void Renderer::updatePhysics(double timeStep)
{
    vec3 inputForce1 = vec3();
    vec3 inputForce2 = vec3();
    bool flatKick1 = false;
    bool volleyKick1 = false;
    vec3 inputTorque1 = vec3();
    vec3 inputTorque2 = vec3();
    bool flatKick2 = false;
    bool volleyKick2 = false;

    // Handle key inputs into the scenario
    foreach (Qt::Key key, pressedKeys)
    {
        switch(key)
        {

            // Player #1 keys
            case Qt::Key_Up:
                inputForce1 += RigidBody::rotateYaxis(vec3(5000.0,0.0,0.0),mRobot1->getBody()->getAngleY());
                break;
            case Qt::Key_Down:
                inputForce1 += RigidBody::rotateYaxis(vec3(-2500.0,0.0,0.0),mRobot1->getBody()->getAngleY());
                break;
            case Qt::Key_Left:
                inputTorque1.y += 50000.0;
                if(pressedKeys.contains(Qt::Key_Down))
                    inputTorque1.y += -100000.0;
                break;
            case Qt::Key_Right:
                inputTorque1.y += -50000.0;
                if(pressedKeys.contains(Qt::Key_Down))
                    inputTorque1.y += 100000.0;
                break;
            case Qt::Key_Control:
                if(mRobot1->getKickFlatAction() == Off)
                    flatKick1 = true;
                break;
            case Qt::Key_Shift:
                if(mRobot1->getKickVolleyAction() == Off)
                    volleyKick1 = true;
                break;
            // Place #2 Keys
            case Qt::Key_5:
                inputForce2 += RigidBody::rotateYaxis(vec3(5000.0,0.0,0.0),mRobot2->getBody()->getAngleY());
                break;
            case Qt::Key_2:
                inputForce2 += RigidBody::rotateYaxis(vec3(-2500.0,0.0,0.0),mRobot2->getBody()->getAngleY());
                break;
            case Qt::Key_1:
                inputTorque2.y += 50000.0;
                if(pressedKeys.contains(Qt::Key_2))
                    inputTorque2.y += -100000.0;
                break;
            case Qt::Key_3:
                inputTorque2.y += -50000.0;
                if(pressedKeys.contains(Qt::Key_2))
                    inputTorque2.y += 100000.0;
                break;
            case Qt::Key_Enter:
                if(mRobot2->getKickFlatAction() == Off)
                    flatKick2 = true;
                break;
            case Qt::Key_Plus:
                if(mRobot2->getKickVolleyAction() == Off)
                    volleyKick2 = true;
                break;
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////
    // (1) Handle collisions
    //

    // Calculate next step    
    mRobot1->nextStep(timeStep, gravity, damping, inputForce1, inputTorque1, flatKick1, volleyKick1);
    mRobot2->nextStep(timeStep, gravity, damping, inputForce2, inputTorque2, flatKick2, volleyKick2);
    mBall->nextStep(timeStep, gravity*5, 1.0f);
    /*
    mBall->setAngVel(25.0f*vec3(0.0, 0.0f,-RigidBody::norm(mBall->getVel()))/mBall->getObj()->boundingBox().radius());
    mBall->updateAngleZ(mBall->getAngVel().z*(float)timeStep);
    mBall->setAngleX(0.0f);
    */
    mBall->setAngVel(25.0f*vec3(mBall->getVel().z, 0.0f,-mBall->getVel().x)/mBall->getObj()->boundingBox().radius());
    mBall->updateAngle(mBall->getAngVel()*(float)timeStep);

    // Collision detection
    detectCollisions();

    // Rollback positions and velocities
    mRobot1->undoNextStep();
    mRobot2->undoNextStep();
    mBall->undoNextStep();
    //
    /////////////////////////////////////////////////////////////////////////////////////////////////

    /////////////////////////////////////////////////////////////////////////////////////////////////
    // (2) Update Velocities
    //

    bool isImpulse1 = false, isImpulse2 = false, isImpulseB = false;
    if(mRobot1->getBody()->isImpulse()|| mRobot1->getKickFlat()->isImpulse()|| mRobot1->getKickVolley()->isImpulse())
    {
        mRobot1->updateVelocities();
        isImpulse1 = true;
    }
    else
    {
        mRobot1->nextStep(timeStep, gravity, damping, inputForce1, inputTorque1, flatKick1, volleyKick1);
        mRobot1->undoPositions();
    }
    if(mRobot2->getBody()->isImpulse() || mRobot2->getKickFlat()->isImpulse() || mRobot2->getKickVolley()->isImpulse())
    {
        mRobot2->updateVelocities();
        isImpulse2 = true;      
    }
    else
    {
        mRobot2->nextStep(timeStep, gravity, damping, inputForce2, inputTorque2, flatKick2, volleyKick2);
        mRobot2->undoPositions();
    }
    if(mBall->isImpulse())
    {
        mBall->updateVelocities();
        isImpulseB = true;
    }
    else
    {
        mBall->nextStep(timeStep, gravity*5, 1.0f);
        mBall->undoPositions();
    }
    //
    /////////////////////////////////////////////////////////////////////////////////////////////////

    /////////////////////////////////////////////////////////////////////////////////////////////////
    // (3) Handle contacts
    //
    mRobot1->updatePositions(timeStep);
    mRobot2->updatePositions(timeStep);
    mBall->updatePositions(timeStep);
    // Update positions (next step + undoVelocities)
    //mRobot1->nextStep(timeStep, gravity, damping,  inputForce1, inputTorque1, flatKick1, volleyKick1);
    //if(isImpulse1)
    //    mRobot1->undoVelocities();
    //mRobot2->nextStep(timeStep, gravity, damping,  inputForce2, inputTorque2, flatKick2, volleyKick2);
    //if(isImpulse2)
    //    mRobot2->undoVelocities();
    //mBall->nextStep(timeStep, gravity*5, 1.0f);
    //if(isImpulseB)
    //    mBall->undoVelocities();
    mBall->setAngVel(25.0f*vec3(mBall->getVel().z,0.0f,-mBall->getVel().x)/mBall->getObj()->boundingBox().radius());
    mBall->updateAngle(mBall->getAngVel()*(float)timeStep);
    /*
    mBall->setAngleY(RigidBody::angleYvectors(vec3(1.0,0.0,0.0), mBall->getVel()));
    mBall->setAngVel(25.0f*vec3(0.0, 0.0f,-mBall->getVel().x)/mBall->getObj()->boundingBox().radius());
    mBall->updateAngleZ(mBall->getAngVel().z*(float)timeStep);
    mBall->setAngleX(0.0f);
    */
    
    // Collision detection
    detectCollisions();

    // Rollback positions
    mRobot1->undoPositions();
    mRobot2->undoPositions();
    mBall->undoPositions();

    // Add impulses
    if(mRobot1->getBody()->isImpulse()|| mRobot1->getKickFlat()->isImpulse()|| mRobot1->getKickVolley()->isImpulse())
    {
        mRobot1->updateVelocities();
        mRobot1->resetVelocities();
    }
    if(mRobot2->getBody()->isImpulse() || mRobot2->getKickFlat()->isImpulse() || mRobot2->getKickVolley()->isImpulse())
    {
        mRobot2->updateVelocities();
        mRobot2->resetVelocities();
    }
    if(mBall->isImpulse())
    {        
        mBall->updateVelocities();
        if(mBall->getPosY() < 0.01f && mBall->getVel().y < 0.1f)
            mBall->setPosY(0.0f);
    }
    //
    /////////////////////////////////////////////////////////////////////////////////////////////////

    /////////////////////////////////////////////////////////////////////////////////////////////////
    // (4) Update positions
    //
        mRobot1->updatePositions(timeStep);
        mRobot2->updatePositions(timeStep);
        mBall->updatePositions(timeStep);
    //
    /////////////////////////////////////////////////////////////////////////////////////////////////
}

void Renderer::pressedKey(Qt::Key key)
{
    pressedKeys += key;
    if (mState == Config) mRobotConfigView->handleKeys(key);
    if (key == Qt::Key_Escape) mState = Config;
}

void Renderer::releasedKey(Qt::Key key)
{
    pressedKeys -= key;
    switch(key)
    {
        // Reset positions
        case Qt::Key_R:
            resetBallAndRobots();
            break;
        // Show fake front mirror
        case Qt::Key_F:
            fakeWall = !fakeWall;
            break;
    }
}

void Renderer::detectCollisions()
{
    // Calculate collisions
    mRobot1->resetImpulses();
    mRobot2->resetImpulses();
    mBall->resetImpulses();
    // Ball vs ..
    //- Robot1
    mRobot1->checkCollisionBall(mBall);
    //- Robot2
    mRobot2->checkCollisionBall(mBall);

    // Between robots
    vec3 offsetKick1 = mRobot1->getKickFlat()->getPos();
    mRobot1->getKickFlat()->setPos(mRobot1->getBody()->getPos()+RigidBody::rotateYaxis(offsetKick1, mRobot1->getBody()->getAngleY()));
    mRobot1->getKickFlat()->setAngle(mRobot1->getBody()->getAngle());
    float kilos1 = mRobot1->getKickFlat()->getMass();
    mRobot1->getKickFlat()->setMass(mRobot1->getBody()->getMass());
    vec3 vel0Kick1 = mRobot1->getKickFlat()->getVel0();
    mRobot1->getKickFlat()->setVel0(mRobot1->getBody()->getVel0() + RigidBody::rotateYaxis(vel0Kick1, mRobot1->getBody()->getAngleY()));
    vec3 velKick1 = mRobot1->getKickFlat()->getVel();
    mRobot1->getKickFlat()->setVel(mRobot1->getBody()->getVel() + RigidBody::rotateYaxis(velKick1, mRobot1->getBody()->getAngleY()));
    vec3 offsetKick2 = mRobot2->getKickFlat()->getPos();
    mRobot2->getKickFlat()->setPos(mRobot2->getBody()->getPos()+RigidBody::rotateYaxis(offsetKick2, mRobot2->getBody()->getAngleY()));
    mRobot2->getKickFlat()->setAngle(mRobot2->getBody()->getAngle());
    float kilos2 = mRobot2->getKickFlat()->getMass();
    mRobot2->getKickFlat()->setMass(mRobot2->getBody()->getMass());
    vec3 vel0Kick2 = mRobot2->getKickFlat()->getVel0();
    mRobot2->getKickFlat()->setVel0(mRobot2->getBody()->getVel0() + RigidBody::rotateYaxis(vel0Kick2, mRobot2->getBody()->getAngleY()));
    vec3 velKick2 = mRobot2->getKickFlat()->getVel();
    mRobot2->getKickFlat()->setVel(mRobot2->getBody()->getVel() + RigidBody::rotateYaxis(velKick2, mRobot2->getBody()->getAngleY()));
    // Bodies
    Collision collideRobots = mRobot1->getBody()->isCollisionTreeTree(mRobot2->getBody());
    if(collideRobots.isCollision)
    {
        RigidBody::addImpulses(collideRobots, mRobot1->getBody(), mRobot2->getBody());
    }
    // Flat kicks
    Collision collideFlatKicks = mRobot1->getKickFlat()->isCollisionRotBoxes(mRobot2->getKickFlat());
    if(collideFlatKicks.isCollision)
    {
        vec3 centerBox1 = mRobot1->getKickFlat()->getObj()->boundingBox().centreBox();
        mRobot1->getKickFlat()->getObj()->boundingBox().centreBox() += offsetKick1;
        mRobot1->getKickFlat()->setPos(mRobot1->getBody()->getPos());
        vec3 centerBox2 = mRobot2->getKickFlat()->getObj()->boundingBox().centreBox();
        mRobot2->getKickFlat()->getObj()->boundingBox().centreBox() += offsetKick2;
        mRobot2->getKickFlat()->setPos(mRobot2->getBody()->getPos());

        RigidBody::addImpulses(collideFlatKicks, mRobot1->getKickFlat(), mRobot2->getKickFlat());

        mRobot1->getKickFlat()->getObj()->boundingBox().centreBox() = centerBox1;
        mRobot2->getKickFlat()->getObj()->boundingBox().centreBox() = centerBox2;
    }
    // Body-Flat
    Collision collideBodyFlat = mRobot1->getBody()->isCollisionTreeInBB(mRobot2->getKickFlat());
    if(collideBodyFlat.isCollision)
    {
        vec3 centerBox2 = mRobot2->getKickFlat()->getObj()->boundingBox().centreBox();
        mRobot2->getKickFlat()->getObj()->boundingBox().centreBox() += offsetKick2;
        mRobot2->getKickFlat()->setPos(mRobot2->getBody()->getPos());

        RigidBody::addImpulses(collideBodyFlat, mRobot1->getBody(), mRobot2->getKickFlat());

        mRobot2->getKickFlat()->getObj()->boundingBox().centreBox() = centerBox2;
    }
    // Flat-Body
    Collision collideFlatBody = mRobot2->getBody()->isCollisionTreeInBB(mRobot1->getKickFlat());
    if(collideFlatBody.isCollision)
    {
        vec3 centerBox1 = mRobot1->getKickFlat()->getObj()->boundingBox().centreBox();
        mRobot1->getKickFlat()->getObj()->boundingBox().centreBox() += offsetKick1;
        mRobot1->getKickFlat()->setPos(mRobot1->getBody()->getPos());

        RigidBody::addImpulses(collideFlatBody, mRobot2->getBody(), mRobot1->getKickFlat());
        
        mRobot1->getKickFlat()->getObj()->boundingBox().centreBox() = centerBox1;
    }
    // Volley kicks // Body-Volley // Volley-Body // Flat-Volley // Volley-Flat >>> not implemented

    mRobot1->getKickFlat()->setPos(offsetKick1);
    mRobot1->getKickFlat()->setAngle(vec3());
    mRobot1->getKickFlat()->setVel(velKick1);
    mRobot1->getKickFlat()->setVel0(vel0Kick1);
    mRobot1->getKickFlat()->setMass(kilos1);

    mRobot2->getKickFlat()->setPos(offsetKick2);
    mRobot2->getKickFlat()->setAngle(vec3());
    mRobot2->getKickFlat()->setVel(velKick2);
    mRobot2->getKickFlat()->setVel0(vel0Kick2);
    mRobot2->getKickFlat()->setMass(kilos2);

    //Ball vs. Wall
    detectWallBall(mBall);
    // Robot1 vs walls
    detectWallRobot(mRobot1);
    // Robot2 vs walls
    detectWallRobot(mRobot2);
}

void Renderer::detectWallBall(RigidBody* ball)
{
    Collision collision;
    // Check collision for common walls
    foreach(RigidBody* wall, listWalls)
    {
        collision.isCollision = false;
        collision = ball->isCollisionSphereWall(wall);
        if(collision.isCollision)
            RigidBody::addImpulses(collision, ball, wall);
    }
    // Check side wall collisions
    if(abs(ball->getPosX())+ball->getObj()->boundingBox().radius() > abs(dot(normalize(mRightWall->getObj()->vertices[0].normal), mRightWall->getObj()->boundingBox().min)))
    {
        float pMax = dot(normalize(mRightGoalRight->getObj()->vertices[0].normal), mRightGoalRight->getObj()->boundingBox().min);
        float pMin = -dot(normalize(mRightGoalLeft->getObj()->vertices[0].normal), mRightGoalLeft->getObj()->boundingBox().max);
        float pTop = -dot(normalize(mRightGoalTop->getObj()->vertices[0].normal), mRightGoalTop->getObj()->boundingBox().min);
        vec3 pBall = ball->getPos() + ball->getObj()->boundingBox().centreBox();
        vec3 offset = ball->getObj()->boundingBox().dist()/2.0f;
        // In case we are in the goal, check collisions with goal walls
        if(pBall.z - offset.z > pMax && pBall.z + offset.z < pMin && pBall.y + offset.y < pTop)
        {
            foreach(RigidBody* wall, listGoalies)
            {
                collision.isCollision = false;
                collision = ball->isCollisionSphereWall(wall);
                if(collision.isCollision)
                    RigidBody::addImpulses(collision, ball, wall);
            }
        }
        // If not, check with normal left and right walls
        else
        {
            foreach(RigidBody* wall, listSideWalls)
            {
                collision.isCollision = false;
                collision = ball->isCollisionSphereWall(wall);
                if(collision.isCollision)
                    RigidBody::addImpulses(collision, ball, wall);
            }
        }
    }
}

void Renderer::detectWallRobot(Robot* robot)
{
    // Check collision for common walls
    foreach(RigidBody* wall, listWalls)
        robot->checkCollisionWall(wall);
    // Check side wall collisions
    RigidBody* body = robot->getBody();
    if(abs(body->getPosX())+body->getObj()->boundingBox().distX()/2.0f > abs(dot(normalize(mRightWall->getObj()->vertices[0].normal), mRightWall->getObj()->boundingBox().min)))
    {
        float pMax = dot(normalize(mRightGoalRight->getObj()->vertices[0].normal), mRightGoalRight->getObj()->boundingBox().min);
        float pMin = -dot(normalize(mRightGoalLeft->getObj()->vertices[0].normal), mRightGoalLeft->getObj()->boundingBox().max);
        float pTop = -dot(normalize(mRightGoalTop->getObj()->vertices[0].normal), mRightGoalTop->getObj()->boundingBox().min);
        vec3 pBody = body->getPos() + body->getObj()->boundingBox().centreBox();
        vec3 offset = body->getObj()->boundingBox().dist()/2.0f;
        // In case we are in the goal, check collisions with goal walls        
        if(pBody.z - offset.z > pMax && pBody.z + offset.z < pMin && pBody.y + offset.y < pTop)
            foreach(RigidBody* wall, listGoalies)
                robot->checkCollisionWall(wall);
        // If not, check with normal left and right walls
        else
            foreach(RigidBody* wall, listSideWalls)
                robot->checkCollisionWall(wall);
    }
}

void Renderer::updateGame(double timeStep)
{
    //maxTime = 999999.0;
    // Update goal scored
    if(isGoal(-1)) {
        mStats->incrScore(2);
        mState = Goal;
        waitTime = 0;
    }
    if(isGoal(1)) {
        mStats->incrScore(1);
        mState = Goal;
        waitTime = 0;
    }

    // Set both teams
    mStats->setTeam(1, mRobot1->getCountry());
    mStats->setTeam(2, mRobot2->getCountry());

    // Update timing
    time += timeStep;

    //glEnable(GL_BLEND);
    //mStats->paintStats((int)(maxTime - time));
    //glDisable(GL_BLEND);

    if (maxTime - time < 0 || mStats->getStats() >= maxGoals)
    {
        mState = Finish;
    }
}

bool Renderer::isGoal(int side)
{
    return side*(mBall->getPosX()-side*mBall->getObj()->boundingBox().radius())
            >
            abs(dot(normalize(mLeftWall->getObj()->vertices[0].normal), mLeftWall->getObj()->boundingBox().min));
}

void Renderer::resetBallAndRobots() {
    // place ball
    mBall->setPos(vec3(0.0,0.0,0.0));
    mBall->setVel(vec3(0.0,0.0,0.0));
    mBall->setAngVel(vec3(0.0,0.0,0.0));

    // place Robots
    mRobot1->getBody()->setPos(vec3(-5.0,0.0,0.0));
    mRobot1->getBody()->setAngleY(0.0);
    mRobot1->resetVelocities();
    mRobot2->getBody()->setPos(vec3(5.0,0.0,0.0));
    mRobot2->getBody()->setAngleY(180.0);
    mRobot2->resetVelocities();
}
