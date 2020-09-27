#include "Rigidbody.hh"

#define MIN 0.00000000000000001

RigidBody::RigidBody(vec3 initPos, float mass, char* aPathBody, float aElasticity):
        _pos(initPos),
        _mass(mass),
        pathBody(aPathBody),
        _elasticity(aElasticity),
        renderObj(),
        _vel(vec3()),
        _angle(vec3()),
        _angVel(vec3())
{
    objBody = new Object(aPathBody);
    _centerMass = objBody->boundingBox().centreBox();
    // Calculate momentum of inertia
    for(int i = 0; i < objBody->vertices.size(); ++i)
    {
        vec3 distCenter = (objBody->boundingBox().centreBox() - objBody->vertices.at(i).coord)*(objBody->boundingBox().centreBox() - objBody->vertices.at(i).coord);
        _inertia += vec3(_mass*(distCenter.y + distCenter.z), _mass*(distCenter.x + distCenter.z), _mass*(distCenter.x + distCenter.y));
    }
    _inertia = _inertia / ((float)objBody->vertices.size()*2);

    // For spheres
    //_inertia = (2.0f/5.0f) * _mass * objBody->boundingBox().dist()/2.0f;
    //cout << "Momentum inertia #2: " << endl;
    //cout << _inertia.x << " " << _inertia.y << " " << _inertia.z << endl;

}

void RigidBody::nextStep(double timeStep, float gravity, float damping, vec3 inputForce, vec3 inputTorque)
{
    //timeStep = 0.002;
    // Keep state
    _pos0 = _pos;
    _vel0 = _vel;
    _angle0 = _angle;
    _angVel0 = _angVel;

    // Calculate next position by applying Runge Kutta Algorithm for solving 4th order diff eq.
    vec3 dPos[5], dRot[5], dVel[5], dAng[5];
    vec3 R = objBody->boundingBox().dist();

    // In the air there is no grass friction
    if(_pos.y > 0.1f)
        damping = 0.0f;
    // And we assume there is no gravity when touching the ground
    if(_pos.y <= 0.0f)
        gravity = 0.0f;    

    vec3 _accVel = (inputForce - vec3(damping,0.0,damping)*_vel + _mass*vec3(0.0,gravity,0.0)) / _mass;
    vec3 _accAng = (inputTorque - damping*_angVel) / _inertia;

    //_vel += _accVel * vec3(timeStep,timeStep,timeStep);
    //_pos += _vel * vec3(timeStep,timeStep,timeStep);
    //_angVel += _accAng * vec3(timeStep,timeStep,timeStep);
    //_angle += _angVel * vec3(timeStep,timeStep,timeStep);

    //Runge-Kutta method
    // First intermed step
    dPos[1] = _vel;
    dRot[1] = _angVel;
    dVel[1] = _accVel;
    dAng[1] = _accAng;

    // - Get values at "time0 + timeStep/2" for next calculation
    dPos[0] = _vel + dPos[1] * vec3(timeStep/2.0, timeStep/2.0, timeStep/2.0);
    dRot[0] = _angVel + dRot[1] * vec3(timeStep/2.0, timeStep/2.0, timeStep/2.0);
    dVel[0] = _accVel + dVel[1] * vec3(timeStep/2.0, timeStep/2.0, timeStep/2.0);
    dAng[0] = _accAng + dAng[1] * vec3(timeStep/2.0, timeStep/2.0, timeStep/2.0);

    // Second intermed step
    dPos[2] = dPos[0];
    dRot[2] = dRot[0];
    dVel[2] = dVel[0];
    dAng[2] = dAng[0];
    // - Get values at "time0 + timeStep/2 + timeStep/2" for next calculation
    dPos[0] = _vel + dPos[2] * vec3(timeStep/2.0, timeStep/2.0, timeStep/2.0);
    dRot[0] = _angVel + dRot[2] * vec3(timeStep/2.0, timeStep/2.0, timeStep/2.0);
    dVel[0] = _accVel + dVel[2] * vec3(timeStep/2.0, timeStep/2.0, timeStep/2.0);
    dAng[0] = _accAng + dAng[2] * vec3(timeStep/2.0, timeStep/2.0, timeStep/2.0);

    // Third intermed step
    dPos[3] = dPos[0];
    dRot[3] = dRot[0];
    dVel[3] = dVel[0];
    dAng[3] = dAng[0];
    // - Get values at "time0 + timeStep/2 + timeStep/2 + timeStep" for next calculation
    dPos[0] = _vel + dPos[3] * vec3(timeStep, timeStep, timeStep);
    dRot[0] = _angVel + dRot[3] * vec3(timeStep, timeStep, timeStep);
    dVel[0] = _accVel + dVel[3] * vec3(timeStep, timeStep, timeStep);
    dAng[0] = _accAng + dAng[3] * vec3(timeStep, timeStep, timeStep);

    // Fourth intermed step
    dPos[4] = dPos[0];
    dRot[4] = dRot[0];
    dVel[4] = dVel[0];
    dAng[4] = dAng[0];

    // Final interpolation
    _pos.x += (dPos[1].x+2*dPos[2].x+2*dPos[3].x+dPos[4].x)*timeStep/6;
    _pos.y += (dPos[1].y+2*dPos[2].y+2*dPos[3].y+dPos[4].y)*timeStep/6;
    _pos.z += (dPos[1].z+2*dPos[2].z+2*dPos[3].z+dPos[4].z)*timeStep/6;
    _angle.x += (dRot[1].x+2*dRot[2].x+2*dRot[3].x+dRot[4].x)*timeStep/6;
    _angle.y += (dRot[1].y+2*dRot[2].y+2*dRot[3].y+dRot[4].y)*timeStep/6;
    _angle.z += (dRot[1].z+2*dRot[2].z+2*dRot[3].z+dRot[4].z)*timeStep/6;
    _vel.x += (dVel[1].x+2*dVel[2].x+2*dVel[3].x+dVel[4].x)*timeStep/6;
    _vel.y += (dVel[1].y+2*dVel[2].y+2*dVel[3].y+dVel[4].y)*timeStep/6;

    _vel.z += (dVel[1].z+2*dVel[2].z+2*dVel[3].z+dVel[4].z)*timeStep/6;
    if(_vel.length() < MIN)
        _vel = vec3();
    _angVel.x += (dAng[1].x+2*dAng[2].x+2*dAng[3].x+dAng[4].x)*timeStep/6;
    _angVel.y += (dAng[1].y+2*dAng[2].y+2*dAng[3].y+dAng[4].y)*timeStep/6;
    _angVel.z += (dAng[1].z+2*dAng[2].z+2*dAng[3].z+dAng[4].z)*timeStep/6;
    if(_angVel.length() < MIN)
        _angVel = vec3();
}

void RigidBody::undoNextStep()
{
    _pos = _pos0;
    _vel = _vel0;
    _angle = _angle0;
    _angVel = _angVel0;
}

void RigidBody::undoPositions()
{
    _pos = _pos0;
    _angle = _angle0;
}

void RigidBody::undoVelocities()
{
    _vel = _vel0;
    _angVel = _angVel0;
}

void RigidBody::updatePositions(float timeStep)
{
    _pos0 = _pos;
    _pos += _vel * vec3(timeStep,timeStep,timeStep);
    _angle0 = _angle;
    _angle += _angVel * vec3(timeStep,timeStep,timeStep);
}

void RigidBody::updateVelocities()
{
    if(isImpulse())
    {
        // Linear Velocity
        _vel0 = _vel;
        vec3 auxVel;
        foreach(vec3 v, impulseV)
            auxVel += v;
        _vel = auxVel / (float)impulseV.size();
        // Angular Velocity
        _angVel0 = _angVel;
        vec3 auxW;
        foreach(vec3 w, impulseW)
            auxW += w;
        _angVel = auxW / (float)impulseW.size();
    }
}

void RigidBody::initRender(SharedUniformMatrix3f mpUniformNormalMatrix, SharedUniformMatrix4f mpUniformModelViewMatrix,
                           SharedUniformMatrix4f mpUniformModelViewProjectionMatrix, SharedTexture pTextureScreenSizeColor,
                           SharedTexture pTextureScreenSizeDepth, char* shader, char* pathTex, vec4 vPositionLight, vec3 vAttenuationLight)
{
    renderObj = RenderObjectControl(
        VertexBufferObjectFileManager::the()->get(VertexBufferObjectControlFileOBJ(pathBody)),
        ShaderProgramObjectControl(ShaderProgramFileManager::the()->get(ShaderProgramControlAutoFiles(shader))).
            uniform("uNormalMatrix",                mpUniformNormalMatrix).
            uniform("uModelViewMatrix",             mpUniformModelViewMatrix).
            uniform("uModelViewProjectionMatrix",   mpUniformModelViewProjectionMatrix).
            uniformTexture("uSamplerBaseColor",     UniformTextureControl(TextureFileManager::the()->get(TextureControlFileJPG(pathTex))).create()).
            uniform("uTextureFit",                  Uniform2fControl(glm::vec2(1.0, 1.0)).create()).
            uniform("uEyeLightPosition",            Uniform4fControl(vPositionLight).create()).
            uniform("uAmbientLight",                Uniform3fControl(glm::vec3(0.45, 0.45, 0.35)).create()).
            uniform("uDiffuseLight",                Uniform3fControl(glm::vec3(0.75, 0.75, 0.75)).create()).
            uniform("uSpecularLight",               Uniform3fControl(glm::vec3(0.25,0.25,0.25)).create()).
            uniform("uAttenuationLight",            Uniform3fControl(vAttenuationLight).create()).
            uniform("uSceneColor",                  Uniform3fControl(glm::vec3(0.5, 0.5, 0.5)).create()).
            uniform("uAmbientMaterial",             Uniform3fControl(glm::vec3(0.3, 0.3, 0.3)).create()).
            uniform("uDiffuseMaterial",             Uniform3fControl(glm::vec3(1.0, 1.0, 0.85)).create()).
            uniform("uSpecularMaterial",            Uniform3fControl(glm::vec3(0.9, 0.9, 0.8)).create()).
            uniform("uShininessMaterial",           Uniform1fControl(5.0f).create()).
            create(),
        FrameBufferObjectControl().
            colorTexture("fFragDataColor", pTextureScreenSizeColor).
            depthTexture(pTextureScreenSizeDepth).
            create()).
        create();
}

void RigidBody::initRender(SharedUniformMatrix3f mpUniformNormalMatrix, SharedUniformMatrix4f mpUniformModelViewMatrix,
                           SharedUniformMatrix4f mpUniformModelViewProjectionMatrix, SharedTexture pTextureScreenSizeColor,
                           SharedTexture pTextureScreenSizeDepth, char* shader, char* pathTex, char* pathTexNormal, vec4 vPositionLight, vec3 vAttenuationLight)
{

    ConstSharedVertexBufferObject pPathBody = VertexBufferObjectFileManager::the()->get(VertexBufferObjectControlFileOBJ(pathBody));

    // TODO: push tangents to the shader ...
    //pPathBody->attachArrayBuffer();
    //pPathBody->attachAttribute();

    renderObj = RenderObjectControl(
        pPathBody,
        ShaderProgramObjectControl(ShaderProgramFileManager::the()->get(ShaderProgramControlAutoFiles(shader))).
            uniform("uNormalMatrix",                mpUniformNormalMatrix).
            uniform("uModelViewMatrix",             mpUniformModelViewMatrix).
            uniform("uModelViewProjectionMatrix",   mpUniformModelViewProjectionMatrix).
            uniformTexture("uSamplerBaseColor",     UniformTextureControl(TextureFileManager::the()->get(TextureControlFileJPG(pathTex))).create()).
            uniformTexture("uNormalTexture",        UniformTextureControl(TextureFileManager::the()->get(TextureControlFileJPG(pathTexNormal))).create()).
            uniform("uTextureFit",                  Uniform2fControl(glm::vec2(1.0, 1.0)).create()).
            uniform("uEyeLightPosition",            Uniform4fControl(vPositionLight).create()).
            uniform("uAmbientLight",                Uniform3fControl(glm::vec3(0.25, 0.25, 0.25)).create()).
            uniform("uDiffuseLight",                Uniform3fControl(glm::vec3(0.75, 0.75, 0.75)).create()).
            uniform("uSpecularLight",               Uniform3fControl(glm::vec3(0.25,0.25,0.25)).create()).
            uniform("uAttenuationLight",            Uniform3fControl(vAttenuationLight).create()).
            uniform("uSceneColor",                  Uniform3fControl(glm::vec3(0.5, 0.5, 0.5)).create()).
            uniform("uAmbientMaterial",             Uniform3fControl(glm::vec3(0.3, 0.3, 0.3)).create()).
            uniform("uDiffuseMaterial",             Uniform3fControl(glm::vec3(0.75, 0.75, 0.75)).create()).
            uniform("uSpecularMaterial",            Uniform3fControl(glm::vec3(0.9, 0.9, 0.8)).create()).
            uniform("uShininessMaterial",           Uniform1fControl(5.0f).create()).
            create(),
        FrameBufferObjectControl().
            colorTexture("fFragDataColor", pTextureScreenSizeColor).
            depthTexture(pTextureScreenSizeDepth).
            create()).
        create();
}

Collision RigidBody::isCollisionSpheres(RigidBody* sphere)
{
    Collision c;
    vec3 d = (getPos() + getObj()->boundingBox().centreBox()) - (sphere->getPos() + sphere->getObj()->boundingBox().centreBox());
    float dist = sqrt(d.x*d.x + d.y*d.y + d.z*d.z);
    float minDist = getObj()->boundingBox().radius() + sphere->getObj()->boundingBox().radius();    
    c.isCollision = dist <=  minDist;
    c.normal = c.normal = normalize(d);
    c.point = getPos() + getObj()->boundingBox().centreBox() + getObj()->boundingBox().radius()*-d;
    return c;
}

Collision RigidBody::isCollisionAABoxes(RigidBody* cube)
{
    Collision c;
    vec3 d = (getPos() + getObj()->boundingBox().centreBox()) - (cube->getPos() + cube->getObj()->boundingBox().centreBox());
    c.isCollision = (fabs(d.x) < getObj()->boundingBox().distX()/2 + cube->getObj()->boundingBox().distX()/2
        && fabs(d.y) < getObj()->boundingBox().distY()/2 + cube->getObj()->boundingBox().distY()/2
        && fabs(d.z) < getObj()->boundingBox().distZ()/2 + cube->getObj()->boundingBox().distZ()/2);    
    c.normal = BoundingBox::rayFromCenterNormal(d);
    c.point = c.point = getPos() + getObj()->boundingBox().closestVertexToPlane(c.normal);
    return c;
}

Collision RigidBody::isCollisionRotBoxes(RigidBody* cube)
{
    Collision c;
    vector<vec3> vertices = getObj()->boundingBox().getAllVertices();
    for(int i = 0; i < vertices.size(); ++i)
    {
        vec3 pInit = vertices.at(i);
        vec3 p = rotateYaxis(pInit, getAngleY());
        p += ( getPos() - cube->getPos() );
        p = rotateYaxis(p, -cube->getAngleY());
        c.isCollision = cube->getObj()->boundingBox().contains(p);
        vec3 d = (getPos() + getObj()->boundingBox().centreBox()) - (cube->getPos() + cube->getObj()->boundingBox().centreBox());
        c.normal = BoundingBox::rayFromCenterNormal(d);
        c.point = rotateYaxis(pInit, getAngleY()) + getPos();
        if(c.isCollision)
            return c;
    }

    vertices = cube->getObj()->boundingBox().getAllVertices();
    for(int i = 0; i < vertices.size(); ++i)
    {
        vec3 pInit = vertices.at(i);
        vec3 p = rotateYaxis(pInit, cube->getAngleY());
        p += ( cube->getPos() - getPos());
        p = rotateYaxis(p, -getAngleY());
        c.isCollision = getObj()->boundingBox().contains(p);
        vec3 d = (getPos() + getObj()->boundingBox().centreBox()) - (cube->getPos() + cube->getObj()->boundingBox().centreBox());
        c.normal = BoundingBox::rayFromCenterNormal(d);
        c.point = rotateYaxis(pInit, getAngleY()) + getPos();
        if(c.isCollision)
            return c;
    }
    return c;
}

Collision RigidBody::isCollisionBoxSphere(RigidBody* sphere)
{
    Collision c;
    vec3 dir = (getPos() + getObj()->boundingBox().centreBox()) - (sphere->getPos() + sphere->getObj()->boundingBox().centreBox());
    dir = dir / sqrt(dir.x*dir.x + dir.y*dir.y + dir.z*dir.z);
    dir = dir*(sphere->getObj()->boundingBox().dist()/2.0f);
    vec3 p = (sphere->getPos()-getPos()) + sphere->getObj()->boundingBox().centreBox() + dir;
    p = rotateYaxis(p, -getAngleY());
    c.isCollision = getObj()->boundingBox().contains(p);
    c.normal = normalize(RigidBody::rotateYaxis(vec3(1.0,0.0,0.0), getAngleY()));
    c.point = sphere->getPos() + sphere->getObj()->boundingBox().centreBox() + getObj()->boundingBox().radius()*-c.normal;
    return c;
}

Collision RigidBody::isCollisionTree(vec3 p)
{
    return isCollisionTreeRecursive(getObj()->getCollisionTree(), p);
}

Collision RigidBody::isCollisionTreeRecursive(BoxTree* bbTree, vec3 p)
{
    Collision c;
    // Base case
    if(bbTree->isEnd)
    {
        if(bbTree->isObject && bbTree->box.contains(p))
        {
            c.isCollision = dot(p,bbTree->parent->normal) < dot(bbTree->point,bbTree->parent->normal);
        }
        c.normal = normalize(bbTree->normal);
        c.point = getPos()+RigidBody::rotateYaxis(bbTree->point, getAngleY());
        return c;
    }
    // Keep checking - recursivity
    else
    {
        if(!bbTree->box.contains(p))
            return c;

        c = isCollisionTreeRecursive(bbTree->topLeftNear, p);
        if(c.isCollision)
            return c;
        c = isCollisionTreeRecursive(bbTree->topLeftFar, p);
        if(c.isCollision)
            return c;
        c = isCollisionTreeRecursive(bbTree->topRightNear, p);
        if(c.isCollision)
            return c;
        c = isCollisionTreeRecursive(bbTree->topRightFar, p);
        if(c.isCollision)
            return c;
        c = isCollisionTreeRecursive(bbTree->bottomLeftNear, p);
        if(c.isCollision)
            return c;
        c = isCollisionTreeRecursive(bbTree->bottomLeftFar, p);
        if(c.isCollision)
            return c;
        c = isCollisionTreeRecursive(bbTree->bottomRightNear, p);
        if(c.isCollision)
            return c;
        c = isCollisionTreeRecursive(bbTree->bottomRightFar, p);
        return c;
    }
}

Collision RigidBody::isCollisionSphereInTree(RigidBody* sphere)
{
    vec3 dir = (getPos() + getObj()->boundingBox().centreBox()) - (sphere->getPos() + sphere->getObj()->boundingBox().centreBox());
    dir = dir / sqrt(dir.x*dir.x + dir.y*dir.y + dir.z*dir.z);
    dir = dir*(sphere->getObj()->boundingBox().dist()/2.0f);
    vec3 p = (sphere->getPos()-getPos()) + sphere->getObj()->boundingBox().centreBox() + dir;
    p = rotateYaxis(p, -getAngleY());
    p = rotateZaxis(p, -getAngleZ());
    return isCollisionTree(p);
}

Collision  RigidBody::isCollisionTreeInSphere(RigidBody* sphere)
{
    Collision c;
    float bestDist = 9999.0f;
    for(int i = 0; i< (int)getObj()->getValuesTree().size(); ++i)
    {
        vec3 p = getObj()->getValuesTree().at(i);
        if(getAngleZ() > 0.0)
        {
            p -= vec3(1.0,1.0,0.0);
            p = rotateZaxis(p, getAngleZ());
            p += vec3(1.0,1.0,0.0);
        }
        p = rotateYaxis(p, getAngleY());
        p += getPos();
        vec3 d = (sphere->getPos() + sphere->getObj()->boundingBox().centreBox()) - p;
        float dist = std::sqrt(d.x*d.x+d.y*d.y+d.z*d.z);
        if(dist < bestDist)
        {
            bestDist = dist;
            c.point = p;
            c.normal = normalize(d + sphere->getObj()->boundingBox().centreBox());
            c.isCollision = (dist < sphere->getObj()->boundingBox().radius());
        }
    }
    return c;
}

// Check collision between a tree-based BB and a common BB (robot vs flat kick)
Collision RigidBody::isCollisionTreeInBB(RigidBody* cube)
{
    Collision c;
    for(int i = 0; i < (int)getObj()->getValuesTree().size(); ++i)
    {
        vec3 initP = getObj()->getValuesTree().at(i);
        vec3 p = rotateYaxis(initP, getAngleY());
        p += ( getPos() - cube->getPos() );
        p = rotateYaxis(p, -cube->getAngleY());
        c.isCollision = cube->getObj()->boundingBox().contains(p);
        if(c.isCollision)
        {
            vec3 d = (getPos() + getObj()->boundingBox().centreBox()) - (cube->getPos() + cube->getObj()->boundingBox().centreBox());
            c.normal = BoundingBox::rayFromCenterNormal(d);
            c.point = rotateYaxis(initP, getAngleY()) + getPos();
            return c;
        }
    }
    return c;
}

Collision RigidBody::isCollisionTreeTree(RigidBody* treeBB)
{
    Collision c;
    for(int i = 0; i < (int)getObj()->getValuesTree().size(); ++i)
    {
        vec3 initP = getObj()->getValuesTree().at(i);
        vec3 p = rotateYaxis(initP, getAngleY());
        p += ( getPos() - treeBB->getPos() );
        p = rotateYaxis(p, -treeBB->getAngleY());
        c = treeBB->isCollisionTree(p);
        if(c.isCollision)
            return c;
    }
    return c;
}

Collision RigidBody::isCollisionSphereWall(RigidBody* wall)
{
    Collision c;
    c.isWall = true;
    c.normal = normalize(wall->getObj()->vertices[0].normal);
    vec3 pSphere = getPos() + getObj()->boundingBox().centreBox();
    c.point = pSphere + getObj()->boundingBox().radius()*-c.normal;
    float D = dot(c.normal, wall->getObj()->boundingBox().min);
    float dist = dot(c.normal, pSphere) - D;
    c.isCollision = (fabs(dist) < getObj()->boundingBox().radius());
    return c;
}

Collision RigidBody::isCollisionBoxWall(RigidBody* wall)
{
    Collision c;
    c.isWall = true;
    c.normal = normalize(wall->getObj()->vertices[0].normal);
    vec3 min = RigidBody::rotateYaxis(getObj()->boundingBox().min, -getAngleY());
    vec3 max = RigidBody::rotateYaxis(getObj()->boundingBox().max, getAngleY());
    c.point = BoundingBox::closestVertexToPlane(c.normal, min, max) + getPos();
    float D = dot(c.normal, wall->getObj()->boundingBox().min);
    float dist = dot(c.normal, c.point) - D;    
    c.isCollision = (dist < 0.00f);
    return c;
}

Collision RigidBody::isCollisionTreeWall(RigidBody* wall)
{
    Collision c;
    c.isWall = true;
    c.normal = normalize(wall->getObj()->vertices[0].normal);
    if(c.normal == vec3(0.0,1.0,0.0))
        return c;
    float D = dot(c.normal, wall->getObj()->boundingBox().min);
    vec3 bestP = getObj()->getValuesTree().at(0);
    float bestDist = 99999999.0f;
    vec3 p = vec3();
    for(int i = 0; i < (int)getObj()->getValuesTree().size(); ++i)
    {
        p = getObj()->getValuesTree().at(i);        
        if(getAngleZ() > 0.0)
        {
            p -= vec3(1.0,1.0,0.0);
            p = rotateZaxis(p, getAngleZ());
            p += vec3(1.0,1.0,0.0);
        }
        p = rotateYaxis(p, getAngleY());
        p += getPos();
        if(dot(c.normal,p) - D < bestDist)
        {
            bestDist = dot(c.normal,p) - D;
            bestP = p;
        }
    }
    c.point = bestP;
    c.isCollision = (bestDist < 0.00f);
    return c;
}

/////////////////////////////////////////////////////////////////////////////////////////////////
//
// Store loaded OBJ files with normals per vertex
//
/*
// Load obj file
Object *obj = new Object();
// Calcaulte each normal per vertex
Object::setModel("/Geometry/Robot/Kick_Volley.obj", obj);
// Store results into a new OBJ file
ofstream newObj;
newObj.open("Geometry/Robot/NpV_Kick_Volley.obj");
if(newObj.is_open())
{
    // Store vertices
    for(int i = 0; i < obj->vertices.size(); ++i)
    {
        vec3 v = obj->vertices.at(i).coord;
        newObj << "v " << v.x << " " << v.y << " " << v.z << endl;
    }
    newObj << "# " << obj->vertices.size() << " vertices" << endl << endl;
    // store normals
    for(int i = 0; i < obj->vertices.size(); ++i)
    {
        vec3 n = obj->vertices.at(i).normal;
        newObj << "vn " << n.x << " " << n.y << " " << n.z << endl;
    }
    newObj << "# " << obj->vertices.size() << " normals (1 per vertex)" << endl << endl;
    // texture coordinates
    for(int i = 0; i < obj->texCoords.size(); ++i)
    {
        newObj << "vt " << obj->texCoords.at(i).x << " " << obj->texCoords.at(i).y << " " << obj->texCoords.at(i).z << endl;
    }
    newObj << "# " << obj->texCoords.size() << " texture coords" << endl << endl;
    // store faces
    for(int i = 0; i < obj->faces.size(); ++i)
    {
        Face f = obj->faces.at(i);
        newObj << "f ";
        newObj << f.vertices[0]+1 << "/" << f.texCoords[0]+1 << "/" << f.vertices[0]+1 << " ";
        newObj << f.vertices[1]+1 << "/" << f.texCoords[1]+1 << "/" << f.vertices[1]+1 << " ";
        newObj << f.vertices[2]+1 << "/" << f.texCoords[2]+1 << "/" << f.vertices[2]+1 << endl;
    }
    newObj << "# " << obj->faces.size() << " faces" << endl;
}
newObj.close();
*/

//
// End of OBJ normal per vertex conversion
//
/////////////////////////////////////////////////////////////////////////////////////////////////

