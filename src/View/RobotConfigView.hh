#ifndef ROBOTCONFIGVIEW_HH
#define ROBOTCONFIGVIEW_HH

#include "../Agents/Robot.hh"
#include "../Model/World.hh"

const string Countrys[7] = {"Spain", "Germany", "Holland", "Italy", "Brazil", "Argentina", "RWTHi8"};


class RobotConfigView
{
public:
    RobotConfigView(const std::tr1::shared_ptr<World>& world, State *state, int *maxGoals, int *maxTime);
    void initView(SharedTexture sizeDepth, SharedTexture sizeColour, Robot *RobotA, Robot *RobotB);
    void paint();
    void updatResize(int w, int h);

    // key Event Handling
    void handleKeys(Qt::Key key);

private:

    // Camera View matrix to keep letters static also if resizing
        glm::mat4 matView;
        void setMatView(glm::vec3 translation, glm::vec3 scaling);
        // Orthogonal View matrix
        glm::mat4 matOrtho;
        void setOrthoView();

        int mWidth, mHeight;
        float mAR;

    // link to the Robots
        Robot* mRobotA;
        Robot* mRobotB;

     // link to the state
        State *mState;

    // slected country for each robot
        int mSelectedCountryA;
        int mSelectedCountryB;

    // current selection of the menu
        int mCurrentSelection;

        int *mCurrentGoals;
        int *mCurrentTime;

    // ProjectionMatrix
        ACGL::OpenGL::SharedUniformMatrix4f mpUniformModelViewProjectionMatrix;

    // Pointer of World
        std::tr1::shared_ptr<World> mpWorld;

    // Objects in the config menu
        ACGL::OpenGL::ConstSharedRenderObject mTitle;
        ACGL::OpenGL::ConstSharedRenderObject mTitleTeamA;
        ACGL::OpenGL::ConstSharedRenderObject mTitleTeamB;
        ACGL::OpenGL::ConstSharedRenderObject mCountrys[7];
        ACGL::OpenGL::ConstSharedRenderObject mNumbers[10];
        ACGL::OpenGL::ConstSharedRenderObject mSelection;
        ACGL::OpenGL::ConstSharedRenderObject mSave;
        ACGL::OpenGL::ConstSharedRenderObject mTime;
        ACGL::OpenGL::ConstSharedRenderObject mGoals;
        ACGL::OpenGL::ConstSharedRenderObject mBackground;

        Country getCountryfromInt(int i);
};

#endif // ROBOTCONFIGVIEW_HH
