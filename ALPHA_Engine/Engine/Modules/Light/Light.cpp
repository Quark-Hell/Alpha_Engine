#include "Light.h"

Light::Light() {
    bool isHave = false;
    for (size_t i = 0; i < World::LightsOnScene.size(); i++) {
        if (this == World::LightsOnScene[i]) {
            isHave = true;
        }
    }
    
    if (isHave == true)
        return;
    
    World::LightsOnScene.push_back(this);
}

Light::~Light() {
    for (size_t i = 0; i < World::LightsOnScene.size(); i++) {
        if (this == World::LightsOnScene[i]) {
            World::LightsOnScene.erase(World::LightsOnScene.begin() + i);
            return;
        }
    }
}

ModulesList Light::GetType() {
	return ModulesList::LightType;
}


void Light::AddPosition(float X, float Y, float Z) {
    Light::_position.X += X;
    Light::_position.Y += Y;
    Light::_position.Z += Z;

    Light::_origin.X += X;
    Light::_origin.Y += Y;
    Light::_origin.Z += Z;
}
void Light::AddPosition(Vector3 position) {
    Light::_position += position;
    Light::_origin += position;
}

void Light::SetPosition(float X, float Y, float Z) {
    Vector3 direction = Vector3(X, Y, Z) - Light::_position;

    Light::AddPosition(direction);
}
void Light::SetPosition(Vector3 position) {
    Vector3 direction = position - Light::_position;

    Light::AddPosition(direction);
}

//TODO: Translate matrix
void Light::AddOriginPosition(float X, float Y, float Z) {
    Light::_origin.X += X;
    Light::_origin.Y += Y;
    Light::_origin.Z += Z;
}
void Light::AddOriginPosition(Vector3 position) {
    Light::_origin += position;
}

void Light::SetOriginPosition(float X, float Y, float Z) {
    Vector3 direction = Vector3(X, Y, Z) - Light::_origin;

    Light::AddOriginPosition(direction);
}
void Light::SetOriginPosition(Vector3 position) {
    Vector3 direction = position - Light::_origin;

    Light::AddOriginPosition(direction);
}


void Light::AddRotation(float X, float Y, float Z) {
    Light::_rotation.X += X;
    Light::_rotation.Y += Y;
    Light::_rotation.Z += Z;

    glm::mat4x4 rotMat(1.0f);

    const float radX = M_PI / 180 * X;
    const float radY = M_PI / 180 * Y;
    const float radZ = M_PI / 180 * Z;

    rotMat = glm::rotate(rotMat, radX, glm::vec3(1.0f, 0.0f, 0.0f));
    rotMat = glm::rotate(rotMat, radY, glm::vec3(0.0f, 1.0f, 0.0f));
    rotMat = glm::rotate(rotMat, radZ, glm::vec3(0.0f, 0.0f, 1.0f));

    Light::_transformMatrix = rotMat;

    glm::vec4 lookP = glm::vec4(Light::_lookingPoint.X, Light::_lookingPoint.Y, Light::_lookingPoint.Z, 0);
    lookP = Light::_transformMatrix * lookP;
    Light::_lookingPoint = Vector3(lookP.x, lookP.y, lookP.z);

    Light::_transformMatrix = glm::mat4x4();

    //TODO: Take out to Transform class
    while (Light::_rotation.X > 360)
    {
        Light::_rotation.X -= 360;
    }
    while (Light::_rotation.Y > 360)
    {
        Light::_rotation.Y -= 360;
    }
    while (Light::_rotation.Z > 360)
    {
        Light::_rotation.Z -= 360;
    }
}
void Light::AddRotation(Vector3 rotation) {
    Light::_rotation.X += rotation.X;
    Light::_rotation.Y += rotation.Y;
    Light::_rotation.Z += rotation.Z;

    glm::mat4x4 rotMat(1.0f);

    const float radX = M_PI / 180 * rotation.X;
    const float radY = M_PI / 180 * rotation.Y;
    const float radZ = M_PI / 180 * rotation.Z;

    rotMat = glm::rotate(rotMat, radX, glm::vec3(1.0f, 0.0f, 0.0f));
    rotMat = glm::rotate(rotMat, radY, glm::vec3(0.0f, 1.0f, 0.0f));
    rotMat = glm::rotate(rotMat, radZ, glm::vec3(0.0f, 0.0f, 1.0f));

    Light::_transformMatrix = rotMat;

    glm::vec4 lookP = glm::vec4(Light::_lookingPoint.X, Light::_lookingPoint.Y, Light::_lookingPoint.Z, 0);
    lookP = Light::_transformMatrix * lookP;
    Light::_lookingPoint = Vector3(lookP.x, lookP.y, lookP.z);

    Light::_transformMatrix = glm::mat4x4();

    //TODO: Take out to Transform class
    while (Light::_rotation.X > 360)
    {
        Light::_rotation.X -= 360;
    }
    while (Light::_rotation.Y > 360)
    {
        Light::_rotation.Y -= 360;
    }
    while (Light::_rotation.Z > 360)
    {
        Light::_rotation.Z -= 360;
    }
}

void Light::SetRotation(float X, float Y, float Z) {
    Vector3 direction = Vector3(X, Y, Z) - Light::_rotation;

    Light::AddRotation(direction);
}
void Light::SetRotation(Vector3 rotation) {
    Vector3 direction = rotation - Light::_rotation;

    Light::AddRotation(direction);
}

void Light::ApplyTransformation()
{
}

Vector3 Light::GetDirection()
{
    return Vector3::GetNormalize(-Light::_lookingPoint);
}
