#include "Robot.hh"

Robot::Robot(int aId, Country aTeam, vec3 initPos):
        id(aId),
        team(aTeam),
        nGoals(0),
        body(new RigidBody(initPos, 80.0, "/Robot/NpV_Robot.obj")),
        volleyKick(new RigidBody(vec3(), 10.0, "/Robot/NpV_Kick_Volley.obj")),
        isFlatKick(Off),
        isVolleyKick(Off)
{
    flatKick = new RigidBody(vec3(), 10.0, "/Robot/NpV_Kick_Flat.obj");
}

void Robot::initRender(SharedUniformMatrix3f mpUniformNormalMatrix, SharedUniformMatrix4f mpUniformModelViewMatrix,
                       SharedUniformMatrix4f mpUniformModelViewProjectionMatrix, SharedTexture pTextureScreenSizeColor,
                       SharedTexture pTextureScreenSizeDepth, vec4 vPositionLight, vec3 vAttenuationLight,
                       char* shaderBody, char* shaderFlat, char* shaderVolley,
                       char* pathTexBody, char* pathTexFlat, char* pathTexVolley)
{
    // store for later adjustemnt on the renderer
    mmpUniformNormalMatrix = mpUniformNormalMatrix;
    mmpUniformModelViewMatrix = mpUniformModelViewMatrix;
    mmpUniformModelViewProjectionMatrix = mpUniformModelViewProjectionMatrix;
    mpTextureScreenSizeColor = pTextureScreenSizeColor;
    mpTextureScreenSizeDepth = pTextureScreenSizeDepth;
    mvPositionLight = vPositionLight;
    mvAttenuationLight =vAttenuationLight;

    body->initRender(mpUniformNormalMatrix, mpUniformModelViewMatrix, mpUniformModelViewProjectionMatrix,
                        pTextureScreenSizeColor, pTextureScreenSizeDepth, shaderBody, pathTexBody, vPositionLight, vAttenuationLight);
    flatKick->initRender(mpUniformNormalMatrix, mpUniformModelViewMatrix, mpUniformModelViewProjectionMatrix,
                        pTextureScreenSizeColor, pTextureScreenSizeDepth, shaderFlat, pathTexFlat, vPositionLight, vAttenuationLight);
    volleyKick->initRender(mpUniformNormalMatrix, mpUniformModelViewMatrix, mpUniformModelViewProjectionMatrix,
                        pTextureScreenSizeColor, pTextureScreenSizeDepth, shaderVolley, pathTexVolley, vPositionLight, vAttenuationLight);
}

void Robot::updateTexture() {

    char* pathTexture;

    switch (team) {
        case Spain:
            pathTexture = "Players/Robot_Spa.png";
            break;
        case Germany:
            pathTexture = "Players/Robot_Ger.png";
            break;
        case Holland:
            pathTexture = "Players/Robot_Hol.png";
            break;
        case Italy:
            pathTexture = "Players/Robot_Ita.png";
            break;
        case Brazil:
            pathTexture = "Players/Robot_Bra.png";
            break;
        case Argentina:
            pathTexture = "Players/Robot_Arg.png";
            break;
        case RWTHi8:
            pathTexture = "Players/Robot_i8.png";
            break;
        deafault:
            ;
    }

    body->initRender(mmpUniformNormalMatrix, mmpUniformModelViewMatrix, mmpUniformModelViewProjectionMatrix,
                     mpTextureScreenSizeColor, mpTextureScreenSizeDepth, "Phong", pathTexture , mvPositionLight, mvAttenuationLight);
}

void Robot::paint(ACGL::OpenGL::SharedUniformMatrix4f mpUniformModelViewProjectionMatrix, ACGL::OpenGL::SharedUniformMatrix4f mpUniformModelViewMatrix,
                  ACGL::OpenGL::SharedUniformMatrix3f mpUniformNormalMatrix, std::tr1::shared_ptr<World> mpWorld)
{
    // Render Main Robot Body
    ModelViewMatrixStack::the()->pushMatrix();
        ModelViewMatrixStack::the()->translate(body->getPos());
        ModelViewMatrixStack::the()->rotate(body->getAngleY(), vec3(0.0,1.0,0.0));
        mpUniformModelViewMatrix->setValue(ModelViewMatrixStack::the()->topMatrix());
        mpUniformModelViewProjectionMatrix->setValue( mpWorld->getCamera()->getProjectionMatrix() * ModelViewMatrixStack::the()->topMatrix() );
        mpUniformNormalMatrix->setValue(ModelViewMatrixStack::the()->topNormalMatrix());
        body->getRender()->render();
    ModelViewMatrixStack::the()->popMatrix();
    // Render Flat Kick Object
    ModelViewMatrixStack::the()->pushMatrix();
        ModelViewMatrixStack::the()->translate(body->getPos());
        ModelViewMatrixStack::the()->rotate(body->getAngleY(), vec3(0.0,1.0,0.0));
        ModelViewMatrixStack::the()->translate(flatKick->getPos());
        mpUniformModelViewMatrix->setValue(ModelViewMatrixStack::the()->topMatrix());
        mpUniformModelViewProjectionMatrix->setValue( mpWorld->getCamera()->getProjectionMatrix() * ModelViewMatrixStack::the()->topMatrix() );
        mpUniformNormalMatrix->setValue(ModelViewMatrixStack::the()->topNormalMatrix());
        flatKick->getRender()->render();
    ModelViewMatrixStack::the()->popMatrix();
    // Render Volley Kick Object
    ModelViewMatrixStack::the()->pushMatrix();
        ModelViewMatrixStack::the()->translate(body->getPos());
        ModelViewMatrixStack::the()->rotate(body->getAngleY(), vec3(0.0,1.0,0.0));
        ModelViewMatrixStack::the()->translate(vec3(1.0,1.0,0.0));
        ModelViewMatrixStack::the()->rotate(volleyKick->getAngleZ(),vec3(0.0,0.0,1.0));
        ModelViewMatrixStack::the()->translate(vec3(-1.0,-1.0,0.0));
        mpUniformModelViewMatrix->setValue(ModelViewMatrixStack::the()->topMatrix());
        mpUniformNormalMatrix->setValue(ModelViewMatrixStack::the()->topNormalMatrix());
        mpUniformModelViewProjectionMatrix->setValue( mpWorld->getCamera()->getProjectionMatrix() * ModelViewMatrixStack::the()->topMatrix() );
        volleyKick->getRender()->render();
    ModelViewMatrixStack::the()->popMatrix();
}

void Robot::nextStep(double timeStep, float gravity, float damping, vec3 inputForce, vec3 inputTorque, bool nowFlatKick, bool nowVolleyKick)
{
    // Physics of normal static body
    body->nextStep(timeStep, gravity, damping, inputForce, inputTorque);

    // Physics of the flat kick
    if(nowFlatKick && isVolleyKick == Off)
    {
        isFlatKick = On;
        flatKick->setVel(vec3(15.0,0.0,0.0));
        flatKick->nextStep(timeStep, 0.0, 0.0, vec3());
    }
    else if(isFlatKick == On)
    {
        flatKick->nextStep(timeStep, 0.0, 0.0, vec3(-1000.0,0.0,0.0));
        if(flatKick->getPosX() < 0.0f)
        {
            flatKick->setPos(vec3());
            flatKick->setPos0(vec3());
            flatKick->setVel(vec3());
            flatKick->setVel0(vec3());
            isFlatKick = Off;
        }
    }
    else
    {        
        flatKick->nextStep(timeStep, 0.0, 0.0);
    }

    // Physics of the volley kick
    if(nowVolleyKick && !isFlatKick)
    {
        isVolleyKick = On;
        volleyKick->setAngVel(vec3(0.0,0.0,725.0));
        volleyKick->nextStep(timeStep, 0.0, 0.0);
    }
    else if(isVolleyKick == On)
    {
        volleyKick->nextStep(timeStep, 0.0, 0.0, vec3(), vec3(0.0,0.0,-5000.0));
        if(volleyKick->getAngleZ() < 0.0 || volleyKick->getAngleZ() > 90.0)
        {
            volleyKick->setAngle(vec3());
            volleyKick->setAngle0(vec3());
            volleyKick->setAngVel(vec3());
            volleyKick->setAngVel0(vec3());
            isVolleyKick = Off;
        }
    }
    else
        volleyKick->nextStep(timeStep, 0.0, 0.0);
}

void Robot::checkCollisionWall(RigidBody* aBody)
{
    // Body
    Collision collisionBody = getBody()->isCollisionTreeWall(aBody);
    if(collisionBody.isCollision)
    {
        RigidBody::addImpulses(collisionBody, getBody(), aBody);
    }
    // Flat kick
    vec3 offsetKick1 = getKickFlat()->getPos();
    getKickFlat()->setPos(getBody()->getPos() + RigidBody::rotateYaxis(offsetKick1, getBody()->getAngleY()));
    getKickFlat()->setAngle(getBody()->getAngle());
    vec3 vel0Kick1 = getKickFlat()->getVel0();
    getKickFlat()->setVel0(getBody()->getVel0() + RigidBody::rotateYaxis(vel0Kick1, getBody()->getAngle0().y));
    vec3 velKick1 = getKickFlat()->getVel();
    getKickFlat()->setVel(getBody()->getVel() + RigidBody::rotateYaxis(velKick1, getBody()->getAngleY()));
    float kilos1 = getKickFlat()->getMass();
    getKickFlat()->setMass(getBody()->getMass());
    Collision collisionFlat = getKickFlat()->isCollisionBoxWall(aBody);
    if(collisionFlat.isCollision)
    {
        RigidBody::addImpulses(collisionFlat, getKickFlat(), aBody);
    }
    getKickFlat()->setPos(offsetKick1);
    getKickFlat()->setAngle(vec3());
    getKickFlat()->setVel(velKick1);
    getKickFlat()->setVel0(vel0Kick1);
    getKickFlat()->setMass(kilos1);
    // Volley Kick
    getKickVolley()->setPos(getBody()->getPos());
    getKickVolley()->setAngleY(getBody()->getAngleY());
    vec3 baseVel0 = vec3(getKickVolley()->getAngVel0().z,0.0f,0.0f);
    vec3 baseVel = vec3(getKickVolley()->getAngVel().z,0.0f,0.0f);
    getKickVolley()->setVel0(getBody()->getVel0() + RigidBody::rotateYaxis(RigidBody::rotateZaxis(baseVel0, getKickVolley()->getAngle0().z), getBody()->getAngle0().y));
    getKickVolley()->setVel(getBody()->getVel() + RigidBody::rotateYaxis(RigidBody::rotateZaxis(baseVel, getKickVolley()->getAngleZ()), getBody()->getAngleY()));
    float kilos2 = getKickVolley()->getMass();
    getKickVolley()->setMass(getBody()->getMass());
    Collision collisionVolley = getKickVolley()->isCollisionTreeWall(aBody);
    if(collisionVolley.isCollision)
    {
        RigidBody::addImpulses(collisionVolley, getKickVolley(), aBody);        
    }
    getKickVolley()->setPos(vec3());
    getKickVolley()->setAngleY(0.0f);
    getKickVolley()->setVel(vec3());
    getKickVolley()->setVel0(vec3());
    getKickVolley()->setMass(kilos2);
}

void Robot::checkCollisionBall(RigidBody* mBall)
{
    // Body
    Collision collidesBody1 = getBody()->isCollisionTreeInSphere(mBall);
    if(collidesBody1.isCollision)
    {
        RigidBody::addImpulses(collidesBody1, mBall, getBody());
    }
    // Flat Kick
    vec3 offsetKick1 = getKickFlat()->getPos();
    getKickFlat()->setPos(getBody()->getPos() + RigidBody::rotateYaxis(offsetKick1, getBody()->getAngleY()));
    getKickFlat()->setAngle(getBody()->getAngle());
    vec3 vel0Kick1 = getKickFlat()->getVel0();
    getKickFlat()->setVel0(getBody()->getVel0() + RigidBody::rotateYaxis(vel0Kick1, getBody()->getAngleY()));
    vec3 velKick1 = getKickFlat()->getVel();
    getKickFlat()->setVel(getBody()->getVel() + RigidBody::rotateYaxis(velKick1, getBody()->getAngleY()));
    Collision collisionFlat = getKickFlat()->isCollisionBoxSphere(mBall);
    if(collisionFlat.isCollision)
    {
        vec3 centerBox = getKickFlat()->getObj()->boundingBox().centreBox();
        getKickFlat()->getObj()->boundingBox().centreBox() += offsetKick1;
        getKickFlat()->setPos(getBody()->getPos());
        RigidBody::addImpulses(collisionFlat, mBall, getKickFlat());

        getKickFlat()->getObj()->boundingBox().centreBox() = centerBox;
    }
    getKickFlat()->setPos(offsetKick1);
    getKickFlat()->setAngle(vec3());
    getKickFlat()->setVel(velKick1);
    getKickFlat()->setVel0(vel0Kick1);
    // Volley Kick
    getKickVolley()->setPos(getBody()->getPos());
    getKickVolley()->setAngleY(getBody()->getAngleY());
    vec3 baseVel0 = vec3(getKickVolley()->getAngVel0().z/10.0f,0.0f,0.0f);
    vec3 baseVel = vec3(getKickVolley()->getAngVel().z/10.0f,0.0f,0.0f);
    getKickVolley()->setVel0(getBody()->getVel0() + RigidBody::rotateYaxis(RigidBody::rotateZaxis(baseVel0, getKickVolley()->getAngle0().z), getBody()->getAngle0().y));
    getKickVolley()->setVel(getBody()->getVel() + RigidBody::rotateYaxis(RigidBody::rotateZaxis(baseVel, getKickVolley()->getAngleZ()), getBody()->getAngleY()));
    Collision collisionVolley = getKickVolley()->isCollisionTreeInSphere(mBall);
    if(collisionVolley.isCollision)
    {
        RigidBody::addImpulses(collisionVolley, mBall, getKickVolley());
    }
    getKickVolley()->setPos(vec3());
    getKickVolley()->setAngleY(0.0f);
    getKickVolley()->setVel(vec3());
    getKickVolley()->setVel0(vec3());    
}

void Robot::updatePositions(float timeStep)
{
    body->updatePositions(timeStep);
    flatKick->updatePositions(timeStep);
    volleyKick->updatePositions(timeStep);
}

void Robot::updateVelocities()
{
    if(flatKick->getPos().x > 0.1f)
    {
        for(int i = 0; i < flatKick->getImpulseV()->size(); ++i)
        {
            vec3 v = flatKick->getImpulseV()->at(i);
            flatKick->getImpulseV()->at(i) = vec3(-sqrt(v.x*v.x+v.y*v.y+v.z*v.z), 0.0f, 0.0f);
        }
        for(int i = 0; i < flatKick->getImpulseW()->size(); ++i)
            flatKick->getImpulseW()->at(i) = vec3();
        flatKick->updateVelocities();
    }
    else
    {
        for(int i = 0; i < flatKick->getImpulseV()->size(); ++i)
            body->addImpulseV(flatKick->getImpulseV()->at(i));
        for(int i = 0; i < flatKick->getImpulseW()->size(); ++i)
            body->addImpulseW(flatKick->getImpulseW()->at(i));
    }

    if(volleyKick->getAngleZ() > 0.1f)
    {
        for(int i = 0; i < volleyKick->getImpulseV()->size(); ++i)
            volleyKick->getImpulseV()->at(i) = vec3();
        for(int i = 0; i < volleyKick->getImpulseW()->size(); ++i)
        {
            vec3 v = volleyKick->getImpulseW()->at(i);
            volleyKick->getImpulseW()->at(i) = vec3(0.0f, 0.0f, -sqrt(v.x*v.x+v.y*v.y+v.z*v.z));
        }
    }
    body->updateVelocities();
}
