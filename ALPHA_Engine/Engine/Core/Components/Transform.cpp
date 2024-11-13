#define _USE_MATH_DEFINES
#include "Transform.h"

#include "Core/Math/Vectors.h"

Core::Transform::Transform() {
    SetPosition(0,0,0);
    SetRotation(0,0,0);
    SetScale(1,1,1);
}

Core::Vector3 Core::Transform::GetPosition() {
    return Transform::_position;
}
void Core::Transform::AddPosition(const float X, const float Y, const float Z) {
    Transform::_position.X += X;
    Transform::_position.Y += Y;
    Transform::_position.Z += Z;

    Transform::_transformMatrix = glm::translate(Transform::_transformMatrix, glm::vec3(X,Y,Z));
}
void Core::Transform::AddPosition(const Vector3& position) {
    Transform::_position.X += position.X;
    Transform::_position.Y += position.Y;
    Transform::_position.Z += position.Z;

    Transform::_transformMatrix = glm::translate(Transform::_transformMatrix, glm::vec3(position.X,position.Y,position.Z));
}
void Core::Transform::SetPosition(const float X, const float Y, const float Z) {
    const Vector3 direction = Vector3(X, Y, Z) - Transform::_position;

    Transform::AddPosition(direction);
}
void Core::Transform::SetPosition(const Vector3& position) {
    const Vector3 direction = position - Transform::_position;

    Transform::AddPosition(direction);
}
void Core::Transform::AddOriginPosition(const float X, const float Y, const float Z) {
    Transform::_origin.X += X;
    Transform::_origin.Y += Y;
    Transform::_origin.Z += Z;
}
void Core::Transform::AddOriginPosition(const Vector3& position) {
    Transform::_origin += position;
}
void Core::Transform::SetOriginPosition(const float X, const float Y, const float Z) {
    const Vector3 direction = Vector3(X, Y, Z) - Transform::_origin;

    Transform::AddOriginPosition(direction);
}
void Core::Transform::SetOriginPosition(const Vector3& position) {
    const Vector3 direction = position - Transform::_origin;

    Transform::AddOriginPosition(direction);
}

glm::mat4x4 Core::Transform::GetTransformMatrix()
{
    return Transform::_transformMatrix;
}



Core::Vector4 Core::Transform::GetRotation() {
    return Transform::_rotation;
}
void Core::Transform::AddRotation(const float X, const float Y, const float Z) {
    const float radX = M_PI / 180.0f * X;
    const float radY = M_PI / 180.0f * Y;
    const float radZ = M_PI / 180.0f * Z;

    Transform::_transformMatrix = glm::rotate(Transform::_transformMatrix, radX, glm::vec3(1.0f, 0.0f, 0.0f));
    Transform::_transformMatrix = glm::rotate(Transform::_transformMatrix, radY, glm::vec3(0.0f, 1.0f, 0.0f));
    Transform::_transformMatrix = glm::rotate(Transform::_transformMatrix, radZ, glm::vec3(0.0f, 0.0f, 1.0f));

    Transform::_rotation.X += X;
    Transform::_rotation.Y += Y;
    Transform::_rotation.Z += Z;
}
void Core::Transform::AddRotation(Vector3 rotation) {
    const float radX = M_PI / 180.0f * rotation.X;
    const float radY = M_PI / 180.0f * rotation.Y;
    const float radZ = M_PI / 180.0f * rotation.Z;

    Transform::_transformMatrix = glm::rotate(Transform::_transformMatrix, radX, glm::vec3(1.0f, 0.0f, 0.0f));
    Transform::_transformMatrix = glm::rotate(Transform::_transformMatrix, radY, glm::vec3(0.0f, 1.0f, 0.0f));
    Transform::_transformMatrix = glm::rotate(Transform::_transformMatrix, radZ, glm::vec3(0.0f, 0.0f, 1.0f));

    Transform::_rotation.X += rotation.X;
    Transform::_rotation.Y += rotation.Y;
    Transform::_rotation.Z += rotation.Z;
}
void Core::Transform::SetRotation(const float X, const float Y, const float Z) {
    const Vector3 direction = Vector3(X, Y, Z) - Transform::_rotation;

    Transform::AddRotation(direction);
}
void Core::Transform::SetRotation(Vector3 rotation) {
    const Vector3 direction = rotation - Transform::_rotation;

    Transform::AddRotation(direction);
}


Core::Vector3 Core::Transform::GetScale() {
    return Transform::_scale;
}
void Core::Transform::SetScale(const float X, const float Y, const float Z) {
    const Vector3 delta = Transform::_scale / Vector3(X, Y, Z);
    Transform::_transformMatrix = glm::scale(Transform::_transformMatrix, glm::vec3(1 / delta.X, 1 / delta.Y, 1 / delta.Z));

    Transform::_scale.X = X;
    Transform::_scale.Y = Y;
    Transform::_scale.Z = Z;
}
void Core::Transform::SetScale(Vector3 scale) {
    const Vector3 delta = Transform::_scale / scale;
    Transform::_transformMatrix = glm::scale(Transform::_transformMatrix, glm::vec3(1 / delta.X, 1 / delta.Y, 1 / delta.Z));

    Transform::_scale.X = scale.X;
    Transform::_scale.Y = scale.Y;
    Transform::_scale.Z = scale.Z;
}
