#include "RobotConfigView.hh"

RobotConfigView::RobotConfigView(const std::tr1::shared_ptr<World>& world, State *state, int *maxGoals, int *maxTime):
    mpUniformModelViewProjectionMatrix(UniformMatrix4fControl().create()),
    mpWorld(world),
    mSelectedCountryA(0),
    mSelectedCountryB(1),
    mCurrentSelection(0)
{
    mState = state;
    mCurrentGoals = maxGoals;
    mCurrentTime = maxTime;
}

string convertIntToString(int number)
{
   stringstream ss;
   ss << number;
   return ss.str();
}

void RobotConfigView::initView(SharedTexture sizeDepth, SharedTexture sizeColour, Robot *RobotA, Robot *RobotB)
{

    mTitle = RenderObjectControl(
            VertexBufferObjectFileManager::the()->get(VertexBufferObjectControlFileOBJ("Quad.obj")),
        ShaderProgramObjectControl(ShaderProgramFileManager::the()->get(ShaderProgramControlAutoFiles("Number"))).
            uniform("uModelViewProjectionMatrix",   mpUniformModelViewProjectionMatrix).
            uniformTexture("uSamplerBaseColor",     UniformTextureControl(TextureFileManager::the()->get(TextureControlFileJPG("ConfigMenu/title.png"))).create()).
            create(),
        FrameBufferObjectControl(). colorTexture("fFragDataColor", sizeColour).depthTexture(sizeDepth).create()).
        create();

    mTitleTeamA = RenderObjectControl(
            VertexBufferObjectFileManager::the()->get(VertexBufferObjectControlFileOBJ("Quad.obj")),
        ShaderProgramObjectControl(ShaderProgramFileManager::the()->get(ShaderProgramControlAutoFiles("Number"))).
            uniform("uModelViewProjectionMatrix",   mpUniformModelViewProjectionMatrix).
            uniformTexture("uSamplerBaseColor",     UniformTextureControl(TextureFileManager::the()->get(TextureControlFileJPG("ConfigMenu/titleTeamA.png"))).create()).
            create(),
        FrameBufferObjectControl(). colorTexture("fFragDataColor", sizeColour).depthTexture(sizeDepth).create()).
        create();

    mTitleTeamB = RenderObjectControl(
            VertexBufferObjectFileManager::the()->get(VertexBufferObjectControlFileOBJ("Quad.obj")),
        ShaderProgramObjectControl(ShaderProgramFileManager::the()->get(ShaderProgramControlAutoFiles("Number"))).
            uniform("uModelViewProjectionMatrix",   mpUniformModelViewProjectionMatrix).
            uniformTexture("uSamplerBaseColor",     UniformTextureControl(TextureFileManager::the()->get(TextureControlFileJPG("ConfigMenu/titleTeamB.png"))).create()).
            create(),
        FrameBufferObjectControl(). colorTexture("fFragDataColor", sizeColour).depthTexture(sizeDepth).create()).
        create();

    for (int i=0; i<7; i++) {
        std::string path = "Status/Flags/raw/";
        std::string format = ".png";
        mCountrys[i] = RenderObjectControl(
                VertexBufferObjectFileManager::the()->get(VertexBufferObjectControlFileOBJ("Quad.obj")),
            ShaderProgramObjectControl(ShaderProgramFileManager::the()->get(ShaderProgramControlAutoFiles("Number"))).
                uniform("uModelViewProjectionMatrix",   mpUniformModelViewProjectionMatrix).
                    uniformTexture("uSamplerBaseColor",     UniformTextureControl(TextureFileManager::the()->get(TextureControlFileJPG(path + Countrys[i] + format))).create()).
                create(),
            FrameBufferObjectControl(). colorTexture("fFragDataColor", sizeColour).depthTexture(sizeDepth).create()).
            create();
    }

    for (int i=0; i<10; i++) {
        std::string path = "Status/Numbers/Score/";
        std::string format = ".png";

        mNumbers[i] = RenderObjectControl(
                VertexBufferObjectFileManager::the()->get(VertexBufferObjectControlFileOBJ("Quad.obj")),
            ShaderProgramObjectControl(ShaderProgramFileManager::the()->get(ShaderProgramControlAutoFiles("Number"))).
                uniform("uModelViewProjectionMatrix",   mpUniformModelViewProjectionMatrix).
                    uniformTexture("uSamplerBaseColor",     UniformTextureControl(TextureFileManager::the()->get(TextureControlFileJPG(path + convertIntToString(i) + format))).create()).
                create(),
            FrameBufferObjectControl(). colorTexture("fFragDataColor", sizeColour).depthTexture(sizeDepth).create()).
            create();
    }

        mSelection = RenderObjectControl(
                VertexBufferObjectFileManager::the()->get(VertexBufferObjectControlFileOBJ("Quad.obj")),
            ShaderProgramObjectControl(ShaderProgramFileManager::the()->get(ShaderProgramControlAutoFiles("Number"))).
                uniform("uModelViewProjectionMatrix",   mpUniformModelViewProjectionMatrix).
                uniformTexture("uSamplerBaseColor",     UniformTextureControl(TextureFileManager::the()->get(TextureControlFileJPG("ConfigMenu/selection.png"))).create()).
                create(),
            FrameBufferObjectControl(). colorTexture("fFragDataColor", sizeColour).depthTexture(sizeDepth).create()).
            create();

        mSave = RenderObjectControl(
                VertexBufferObjectFileManager::the()->get(VertexBufferObjectControlFileOBJ("Quad.obj")),
            ShaderProgramObjectControl(ShaderProgramFileManager::the()->get(ShaderProgramControlAutoFiles("Number"))).
                uniform("uModelViewProjectionMatrix",   mpUniformModelViewProjectionMatrix).
                uniformTexture("uSamplerBaseColor",     UniformTextureControl(TextureFileManager::the()->get(TextureControlFileJPG("ConfigMenu/save.png"))).create()).
                create(),
            FrameBufferObjectControl(). colorTexture("fFragDataColor", sizeColour).depthTexture(sizeDepth).create()).
            create();

        mGoals = RenderObjectControl(
                    VertexBufferObjectFileManager::the()->get(VertexBufferObjectControlFileOBJ("Quad.obj")),
                ShaderProgramObjectControl(ShaderProgramFileManager::the()->get(ShaderProgramControlAutoFiles("Number"))).
                    uniform("uModelViewProjectionMatrix",   mpUniformModelViewProjectionMatrix).
                    uniformTexture("uSamplerBaseColor",     UniformTextureControl(TextureFileManager::the()->get(TextureControlFileJPG("ConfigMenu/MaxGoals.png"))).create()).
                    create(),
                FrameBufferObjectControl(). colorTexture("fFragDataColor", sizeColour).depthTexture(sizeDepth).create()).
                create();

        mTime = RenderObjectControl(
                    VertexBufferObjectFileManager::the()->get(VertexBufferObjectControlFileOBJ("Quad.obj")),
                ShaderProgramObjectControl(ShaderProgramFileManager::the()->get(ShaderProgramControlAutoFiles("Number"))).
                    uniform("uModelViewProjectionMatrix",   mpUniformModelViewProjectionMatrix).
                    uniformTexture("uSamplerBaseColor",     UniformTextureControl(TextureFileManager::the()->get(TextureControlFileJPG("ConfigMenu/MaxTime.png"))).create()).
                    create(),
                FrameBufferObjectControl(). colorTexture("fFragDataColor", sizeColour).depthTexture(sizeDepth).create()).
                create();

        mBackground = RenderObjectControl(
                VertexBufferObjectFileManager::the()->get(VertexBufferObjectControlFileOBJ("Quad.obj")),
            ShaderProgramObjectControl(ShaderProgramFileManager::the()->get(ShaderProgramControlAutoFiles("Number"))).
                uniform("uModelViewProjectionMatrix",   mpUniformModelViewProjectionMatrix).
                uniformTexture("uSamplerBaseColor",     UniformTextureControl(TextureFileManager::the()->get(TextureControlFileJPG("ConfigMenu/background.png"))).create()).
                create(),
            FrameBufferObjectControl(). colorTexture("fFragDataColor", sizeColour).depthTexture(sizeDepth).create()).
            create();

        mRobotA = RobotA;
        mRobotB = RobotB;

}

void RobotConfigView::updatResize(int w, int h)
{
    mWidth = w;
    mHeight = h;
    mAR = (float)w/(float)h;
    setOrthoView();
}

void RobotConfigView::setOrthoView()
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

void RobotConfigView::setMatView(glm::vec3 trans, glm::vec3 scal)
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
}

void RobotConfigView::paint()
{

    /*
    // Draw Title
    glm::mat4 title = glm::scale(glm::mat4(1.0f),glm::vec3(0.8f,0.1f,0.0f));
    title = glm::translate(title, glm::vec3(0.0f,8.0f,0.0f));
    mpUniformModelViewProjectionMatrix->setValue(title);
    mTitle->render();

    // Draw Country selection for Robot A
    glm::mat4 titleTeamA = glm::scale(glm::mat4(1.0f),glm::vec3(0.4f,0.1f,0.0f));
    titleTeamA = glm::translate(titleTeamA, glm::vec3(-1.0f,5.0f,0.0f));
    mpUniformModelViewProjectionMatrix->setValue(titleTeamA);
    mTitleTeamA->render();

    glm::mat4 Country = glm::scale(glm::mat4(1.0f),glm::vec3(0.1f,0.1f,0.0f));
    Country = glm::translate(Country, glm::vec3(2.0f,5.0f,0.0f));
    mpUniformModelViewProjectionMatrix->setValue(Country);
    mCountrys[0]->render();

    // Draw Country selection for Robot B
    glm::mat4 titleTeamB = glm::scale(glm::mat4(1.0f),glm::vec3(0.4f,0.1f,0.0f));
    titleTeamB = glm::translate(titleTeamB, glm::vec3(-1.0f,2.0f,0.0f));
    mpUniformModelViewProjectionMatrix->setValue(titleTeamB);
    mTitleTeamB->render();

    Country = glm::translate(Country, glm::vec3(0.0f,-3.0f,0.0f));
    mpUniformModelViewProjectionMatrix->setValue(Country);
    mCountrys[1]->render();
    )
    */

    // Draw background
    setMatView(glm::vec3(0.0f,3.5f,-1.0f),glm::vec3(20.0f,31.0f,0.0f));
    mpUniformModelViewProjectionMatrix->setValue(matOrtho * matView );
    mBackground->render();

    // Draw Title
    setMatView(glm::vec3(0.0f,30.0f,0.0f),glm::vec3(10.0f,5.0f,0.0f));
    mpUniformModelViewProjectionMatrix->setValue(matOrtho * matView );
    mTitle->render();

    // Draw Country selection for Robot A
    setMatView(glm::vec3(-10.0f,20.0f,0.0f),glm::vec3(7.0f,4.0f,0.0f));
    mpUniformModelViewProjectionMatrix->setValue(matOrtho * matView );
    mTitleTeamA->render();

    setMatView(glm::vec3(10.0f,20.0f,0.0f),glm::vec3(4.0f));
    mpUniformModelViewProjectionMatrix->setValue(matOrtho * matView );
    mCountrys[mSelectedCountryA]->render();

    if (mCurrentSelection == 0) {
        setMatView(glm::vec3(-20.0f,20.0f,0.0f),glm::vec3(2.0f));
        mpUniformModelViewProjectionMatrix->setValue(matOrtho * matView );
        mSelection->render();
    }


    // Draw Country selection for Robot B
    setMatView(glm::vec3(-10.0f,10.0f,0.0f),glm::vec3(7.0f,4.0f,0.0f));
    mpUniformModelViewProjectionMatrix->setValue(matOrtho * matView );
    mTitleTeamB->render();

    setMatView(glm::vec3(10.0f,10.0f,0.0f),glm::vec3(4.0f));
    mpUniformModelViewProjectionMatrix->setValue(matOrtho * matView );
    mCountrys[mSelectedCountryB]->render();

    if (mCurrentSelection == 1) {
        setMatView(glm::vec3(-20.0f,10.0f,0.0f),glm::vec3(2.0f,2.0f, 1.0f));
        mpUniformModelViewProjectionMatrix->setValue(matOrtho * matView );
        mSelection->render();
    }

    // Draw maxGoals
    setMatView(glm::vec3(-10.0f,0.0f,0.0f),glm::vec3(7.0f,4.0f,0.0f));
    mpUniformModelViewProjectionMatrix->setValue(matOrtho * matView);
    mGoals->render();

    setMatView(glm::vec3(10.0f,0.0f,0.0f),glm::vec3(4.0f));
    mpUniformModelViewProjectionMatrix->setValue(matOrtho * matView );
    mNumbers[*mCurrentGoals]->render();

    if (mCurrentSelection == 2) {
        setMatView(glm::vec3(-20.0f,0.0f,0.0f),glm::vec3(2.0f,2.0f, 1.0f));
        mpUniformModelViewProjectionMatrix->setValue(matOrtho * matView );
        mSelection->render();
    }

    // Draw maxTime
    setMatView(glm::vec3(-10.0f,-10.0f,0.0f),glm::vec3(7.5f,4.0f,0.0f));
    mpUniformModelViewProjectionMatrix->setValue(matOrtho * matView);
    mTime->render();

    setMatView(glm::vec3(10.0f,-10.0f,0.0f),glm::vec3(4.0f));
    mpUniformModelViewProjectionMatrix->setValue(matOrtho * matView );
    mNumbers[0]->render();

    setMatView(glm::vec3(5.0f,-10.0f,0.0f),glm::vec3(4.0f));
    mpUniformModelViewProjectionMatrix->setValue(matOrtho * matView );
    mNumbers[*mCurrentTime/10]->render();

    if (mCurrentSelection == 3) {
        setMatView(glm::vec3(-20.0f,-10.0f,0.0f),glm::vec3(2.0f,2.0f, 1.0f));
        mpUniformModelViewProjectionMatrix->setValue(matOrtho * matView );
        mSelection->render();
    }

    // Draw Save & Exit Button
    setMatView(glm::vec3(0.0f,-20.0f,0.0f),glm::vec3(7.0f,4.0f,0.0f));
    mpUniformModelViewProjectionMatrix->setValue(matOrtho * matView);
    mSave->render();

    if (mCurrentSelection == 4) {
        setMatView(glm::vec3(-10.0f,-20.0f,0.0f),glm::vec3(2.0f, 2.0f, 1.0f));
        mpUniformModelViewProjectionMatrix->setValue(matOrtho * matView );
        mSelection->render();
    }

}

void RobotConfigView::handleKeys(Qt::Key key) {
// Handle key inputs into the scenario
    switch(key)
    {
        case Qt::Key_Up:
        mCurrentSelection = (mCurrentSelection+5-1)%5;
            break;
        case Qt::Key_Down:
        mCurrentSelection = (mCurrentSelection+5+1)%5;
            break;
        case Qt::Key_Left:
        switch(mCurrentSelection){
            case 0:
                mSelectedCountryA = (mSelectedCountryA+7-1)%7;
                break;

            case 1:
                mSelectedCountryB = (mSelectedCountryB+7-1)%7;
                break;
            case 2:
                *mCurrentGoals = (*mCurrentGoals+10-1)%10;
                if(*mCurrentGoals == 0)
                    *mCurrentGoals = 9;
                break;
            case 3:
                *mCurrentTime = (*mCurrentTime+100-10)%100;
                if(*mCurrentTime == 0)
                    *mCurrentTime = 90;
            }
            break;
        case Qt::Key_Right:
            switch(mCurrentSelection){
            case 0:
                mSelectedCountryA = (mSelectedCountryA+1)%7;
                break;

            case 1:
                mSelectedCountryB = (mSelectedCountryB+1)%7;
                break;
            case 2:
                *mCurrentGoals = (*mCurrentGoals+10+1)%10;
                if(*mCurrentGoals == 0)
                    *mCurrentGoals = 1;
                break;
            case 3:
                *mCurrentTime = (*mCurrentTime+100+10)%100;
                if(*mCurrentTime == 0)
                    *mCurrentTime = 10;
            }
           break;
        case Qt::Key_Return:
            if (mCurrentSelection == 4) {
                mRobotA->setCountry(getCountryfromInt(mSelectedCountryA));
                mRobotB->setCountry(getCountryfromInt(mSelectedCountryB));
                *mState = Play;
            }
        default:
        break;
    }

}

Country RobotConfigView::getCountryfromInt(int i)
{
    switch (i)
    {
        case 0:  return Spain;
        case 1:  return Germany;
        case 2:  return Holland;
        case 3:  return Italy;
        case 4:  return Brazil;
        case 5:  return Argentina;
        case 6:  return RWTHi8;
        default: ;
    }
}
