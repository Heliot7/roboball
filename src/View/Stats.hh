#ifndef STATS_HH
#define STATS_HH

#include "../Model/World.hh"
#include "../Agents/Robot.hh"
#include <ACGL/OpenGL/Objects.hh>

#include <QtOpenGL/QGLWidget>
#include <QString>
#include <QColor>
#include <QFontDatabase>
#include <QFont>

class Stats
{
public:
    Stats(QGLWidget* parent, const std::tr1::shared_ptr<World>& world);

    void initStats(ACGL::OpenGL::SharedTexture sizeDepth, ACGL::OpenGL::SharedTexture sizeColour);
    void paintStats(int iTime = 60);
    void updatResize(int w, int h);
    void incrScore(int nRobot);
    void setTeam(int nRobot, Country team);
    void setOrthoView();
    int getStats() {return (nGoals1<nGoals2)?nGoals2:nGoals1;}
    void resetStats() {nGoals1=0, nGoals2=0;}

private:

    // Attributes
    QGLWidget *parentGL;
    int mWidth, mHeight;
    float mAR;
    int mTime;
    int nGoals1, nGoals2;
    Country team1, team2;

    // Others for rendering
    // Camera View matrix to keep letters stati
    glm::mat4 matView;
    void setMatView(glm::vec3 translation, glm::vec3 scaling);
    // Orthogonal View matrix
    glm::mat4 matOrtho;
    // Uniforms
    ACGL::OpenGL::SharedUniformMatrix4f mpUniformModelViewProjectionMatrix;
    ACGL::OpenGL::SharedUniformMatrix4f mpUniformModelViewMatrix;
    ACGL::OpenGL::SharedUniformMatrix3f mpUniformNormalMatrix;
    // Pointer of World
    std::tr1::shared_ptr<World> mpWorld;

    // Draw Symbols
    void drawSymbol(char c, glm::vec3 translation, glm::vec3 scaling, bool score = true);
    ACGL::OpenGL::ConstSharedRenderObject backScore;
    ACGL::OpenGL::ConstSharedRenderObject backTime;
    ACGL::OpenGL::ConstSharedRenderObject team1Flag;
    ACGL::OpenGL::ConstSharedRenderObject team2Flag;
    ACGL::OpenGL::ConstSharedRenderObject numScore0, numScore1, numScore2, numScore3, numScore4;
    ACGL::OpenGL::ConstSharedRenderObject numScore5, numScore6, numScore7, numScore8, numScore9;
    ACGL::OpenGL::ConstSharedRenderObject numTime0, numTime1, numTime2, numTime3, numTime4;
    ACGL::OpenGL::ConstSharedRenderObject numTime5, numTime6, numTime7, numTime8, numTime9;
    ACGL::OpenGL::ConstSharedRenderObject timer;
    void drawFlag(Country c, glm::vec3 translation, glm::vec3 scaling, bool left = true);
    ACGL::OpenGL::ConstSharedRenderObject leftSpa, leftGer, leftHol, leftIta, leftBra, leftArg;
    ACGL::OpenGL::ConstSharedRenderObject rightSpa, rightGer, rightHol, rightIta, rightBra, rightArg;
    ACGL::OpenGL::ConstSharedRenderObject flagI8;
};

#endif // STATS_HH
