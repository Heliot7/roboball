////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2011, Computer Graphics Group RWTH Aachen University         //
// All rights reserved.                                                       //
////////////////////////////////////////////////////////////////////////////////

#ifndef ACGL_TEMPLATE_RENDERER_HH
#define ACGL_TEMPLATE_RENDERER_HH

#include <QSet>
#include "ViewWorld.hh"
#include "Stats.hh"
#include "../Model/World.hh"
#include "../Agents/Robot.hh"
#include "RobotConfigView.hh"
#include "FinishView.hh"
#include "GoalView.hh"
#include "GrassRenderer.hh"

// for TESTING
#include "../Agents/GrassBlade.hh"

#include <ACGL/OpenGL/Objects.hh>
#include <ACGL/OpenGL/Controller/TextureControl.hh>
#include <QGLWidget>

enum Scenario { Default, Funny, Bricks };

class Renderer : public ViewWorld
{
public:
    Renderer(const std::tr1::shared_ptr<World>& _pWorld, QGLWidget* parent);
    virtual ~Renderer(void);

public:
    void init(void);
    void paint(double timeStep);
    void resize(int iWidth, int iHeight);

    void setQGLWidget(QGLWidget* qglwidget);

    // Inner game modifications
    void pressedKey(Qt::Key key);
    void releasedKey(Qt::Key key);

private:
    void buildCoordinateSystem(float r, float g, float b);

    QGLWidget* qglW;
    std::tr1::shared_ptr<Stats> mStats;
    std::tr1::shared_ptr<World> mpWorld;

    ACGL::OpenGL::ConstSharedRenderObject mpRenderObjectFullscreenClear;
    ACGL::OpenGL::ConstSharedRenderObject mpRenderObjectVertexColorGrid;
    ACGL::OpenGL::ConstSharedRenderObject mpRenderObjectPostProcessGrayScale;
    ACGL::OpenGL::SharedUniformMatrix4f mpUniformModelViewProjectionMatrix;
    ACGL::OpenGL::SharedUniformMatrix4f mpUniformModelViewMatrix;
    ACGL::OpenGL::SharedUniformMatrix3f mpUniformNormalMatrix;
    ACGL::OpenGL::SharedTexture pTextureScreenSizeDepth;
    ACGL::OpenGL::SharedTexture pTextureScreenSizeColor;

    glm::vec4 vPositionLight;
    glm::vec3 vAttenuationLight;

    ACGL::OpenGL::SharedArrayBuffer mpArrayBufferGrid;

    std::vector<ACGL::OpenGL::SharedTexture> mScreenSizeRenderTargets;

    // Views for the game
    RobotConfigView* mRobotConfigView;
    FinishView* mFinishView;
    GoalView* mGoalView;

    // renderer for the grass
    GrassBlade* mGrass;

    // Agents of the game
    bool fakeWall;
    Robot* mRobot1;
    Robot* mRobot2;
    RigidBody* mBall;
    RigidBody* mLeftWall;
    RigidBody* mLeftGoalBase;
    RigidBody* mLeftGoalLeft;
    RigidBody* mLeftGoalRight;
    RigidBody* mLeftGoalBack;
    RigidBody* mLeftGoalTop;
    RigidBody* mRightWall;
    RigidBody* mRightGoalBase;
    RigidBody* mRightGoalLeft;
    RigidBody* mRightGoalRight;
    RigidBody* mRightGoalBack;
    RigidBody* mRightGoalTop;
    RigidBody* mBackWall;
    RigidBody* mStand;
    RigidBody* mFrontWall;
    RigidBody* mFrontWallFake;
    RigidBody* mGround;
    vector<RigidBody*> listWalls, listSideWalls, listGoalies;

    // Physics related componentes
    QSet<Qt::Key> pressedKeys;
    void updatePhysics(double timeStep);
    void detectCollisions();
    bool isImpulse()
    {
        return (mRobot1->getBody()->isImpulse() || mRobot1->getKickFlat()->isImpulse() || mRobot1->getKickVolley()->isImpulse() ||
                mRobot2->getBody()->isImpulse() || mRobot2->getKickFlat()->isImpulse() || mRobot2->getKickVolley()->isImpulse() ||
                mBall->isImpulse());
    }

    void detectWallBall(RigidBody* ball);
    void detectWallRobot(Robot* robot);
    float gravity;
    float damping;

    // In-game parameters
    void updateCameraPosition();
    void calcFrustum(int w, int h);
    void updateGame(double timeStep);
    double time, waitTime, endTime;
    int maxGoals, maxTime;
    Scenario typeScene;
    bool isGoal(int side);

    void resetBallAndRobots();
    void moveCameratoGoal(int duration, double timeStep);

    State mState;
};


#endif // ACGL_TEMPLATE_RENDERER_HH
