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
}
void Light::AddRotation(Vector3 rotation) {
    Light::_rotation.X += rotation.X;
    Light::_rotation.Y += rotation.Y;
    Light::_rotation.Z += rotation.Z;
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