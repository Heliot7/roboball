#include "FinishView.hh"

FinishView::FinishView(const std::tr1::shared_ptr<World>& world):
    mpWorld(world),
    mpUniformModelViewProjectionMatrix(UniformMatrix4fControl().create())
{
}

void FinishView::updatResize(int w, int h)
{
    mWidth = w;
    mHeight = h;
    mAR = (float)w/(float)h;
    setOrthoView();
}

void FinishView::setOrthoView()
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

void FinishView::setMatView(glm::vec3 trans, glm::vec3 scal)
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

void FinishView::paint()
{
    setMatView(glm::vec3(0.0f,15.0f,0.0f),glm::vec3(20.0f,10.0f,0.0f));
    mpUniformModelViewProjectionMatrix->setValue(matOrtho * matView );
    mFinish->render();
}

void FinishView::initView(SharedTexture sizeDepth, SharedTexture sizeColour)
{
    mFinish = RenderObjectControl(
            VertexBufferObjectFileManager::the()->get(VertexBufferObjectControlFileOBJ("Quad.obj")),
        ShaderProgramObjectControl(ShaderProgramFileManager::the()->get(ShaderProgramControlAutoFiles("Number"))).
            uniform("uModelViewProjectionMatrix",   mpUniformModelViewProjectionMatrix).
            uniformTexture("uSamplerBaseColor",     UniformTextureControl(TextureFileManager::the()->get(TextureControlFileJPG("Finish.png"))).create()).
            create(),
        FrameBufferObjectControl(). colorTexture("fFragDataColor", sizeColour).depthTexture(sizeDepth).create()).
        create();
}
