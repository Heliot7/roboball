#ifndef ROBOT_HH
#define ROBOT_HH

#include "../Physics/Rigidbody.hh"
#include "../Model/World.hh"

enum Country { Spain, Germany, Holland, Italy, Brazil, Argentina, RWTHi8 };
enum Action  { Off, On, Back };

class Robot
{
public:
    Robot(int id, Country team, vec3 initPos);

    // Getters
    int getId() { return id; }
    Country getCountry() { return team; }
    int getGoals() { return nGoals; }
    RigidBody* getBody() { return body; }
    RigidBody* getKickFlat() { return flatKick; }
    Action getKickFlatAction() { return isFlatKick; }
    RigidBody* getKickVolley() { return volleyKick; }
    Action getKickVolleyAction() { return isVolleyKick; }
    // Setters
    void setId(int aId) { id = aId; }
    void setCountry(Country aTeam) { team = aTeam; this->updateTexture();}
    void setGoals(int aGoals) { nGoals = aGoals; }
    void setBody(RigidBody* aBody) { body = aBody; }
    void setKickFlat(RigidBody* aFlatKick) { flatKick= aFlatKick; }
    void setKickVolley(RigidBody* aVolleyKick) { volleyKick= aVolleyKick; }

    // Methods
    void initRender(SharedUniformMatrix3f mpUniformNormalMatrix, SharedUniformMatrix4f mpUniformModelViewMatrix,
                    SharedUniformMatrix4f mpUniformModelViewProjectionMatrix, SharedTexture pTextureScreenSizeColor,
                    SharedTexture pTextureScreenSizeDepth, vec4 vPositionLight, vec3 vAttenuationLight,
                    char* shaderBody, char* shaderFlat, char* shaderVolley,
                    char* pathTexBody, char* pathTexFlat, char* pathTexVolley);

    void paint(ACGL::OpenGL::SharedUniformMatrix4f mpUniformModelViewProjectionMatrix, ACGL::OpenGL::SharedUniformMatrix4f mpUniformModelViewMatrix,
               ACGL::OpenGL::SharedUniformMatrix3f mpUniformNormalMatrix, std::tr1::shared_ptr<World> mpWorld);

    void nextStep(double timeStep, float gravity, float damping, vec3 inputForce, vec3 inputTorque, bool flatKick, bool volleyKick);
    void undoNextStep() { body->undoNextStep(); flatKick->undoNextStep(); volleyKick->undoNextStep(); }
    void undoPositions() { body->undoPositions(); flatKick->undoPositions(); volleyKick->undoPositions(); }
    void undoVelocities() { body->undoVelocities(); flatKick->undoVelocities(); volleyKick->undoVelocities(); }
    void checkCollisionWall(RigidBody* wall);
    void checkCollisionBall(RigidBody* ball);
    void updatePositions(float timeStep);
    void updateVelocities();
    void resetVelocities() { body->setVel(vec3()); }
    void resetImpulses() { body->resetImpulses(); flatKick->resetImpulses(); volleyKick->resetImpulses(); }
    void updateTexture();

private:

    /* Attributes */

    // Personal fields
    int id;
    Country team;
    int nGoals;

    // Set of rigid bodies that form the robot
    RigidBody* body;
    RigidBody* flatKick;
    Action isFlatKick;
    RigidBody* volleyKick;
    Action isVolleyKick;

    SharedUniformMatrix3f mmpUniformNormalMatrix;
    SharedUniformMatrix4f mmpUniformModelViewMatrix;
    SharedUniformMatrix4f mmpUniformModelViewProjectionMatrix;
    SharedTexture mpTextureScreenSizeColor;
    SharedTexture mpTextureScreenSizeDepth;
    vec4 mvPositionLight;
    vec3 mvAttenuationLight;
};

#endif // ROBOT_HH
