#include "Transform.h"

Transform::Transform() {
	Transform::_transformMatrix = glm::mat4x4(1.0f);
}
Transform::~Transform() {

}

Vector3 Transform::GetPosition() {
    return Transform::_position;
}
void Transform::AddPosition(float X, float Y, float Z) {
    Transform::_position.X += X;
    Transform::_position.Y += Y;
    Transform::_position.Z += Z;
}
void Transform::AddPosition(Vector3 position) {
    Transform::_position.X += position.X;
    Transform::_position.Y += position.Y;
    Transform::_position.Z += position.Z;
}
void Transform::SetPosition(float X, float Y, float Z) {
    Vector3 direction = Vector3(X, Y, Z) - Transform::_position;

    Transform::AddPosition(direction);
}
void Transform::SetPosition(Vector3 position) {
    Vector3 direction = position - Transform::_position;

    Transform::AddPosition(direction);
}
void Transform::AddOriginPosition(float X, float Y, float Z) {
    Transform::_origin.X += X;
    Transform::_origin.Y += Y;
    Transform::_origin.Z += Z;
}
void Transform::AddOriginPosition(Vector3 position) {
    Transform::_origin += position;
}
void Transform::SetOriginPosition(float X, float Y, float Z) {
    Vector3 direction = Vector3(X, Y, Z) - Transform::_origin;

    Transform::AddOriginPosition(direction);
}
void Transform::SetOriginPosition(Vector3 position) {
    Vector3 direction = position - Transform::_origin;

    Transform::AddOriginPosition(direction);
}



Vector3 Transform::GetRotation() {
    return Transform::_rotation;
}
void Transform::AddRotation(float X, float Y, float Z) {
    const float radX = M_PI / 180.0f * X;
    const float radY = M_PI / 180.0f * Y;
    const float radZ = M_PI / 180.0f * Z;

    Transform::_transformMatrix = glm::rotate(Transform::_transformMatrix, radX, glm::vec3(1.0f, 0.0f, 0.0f));
    Transform::_transformMatrix = glm::rotate(Transform::_transformMatrix, radY, glm::vec3(0.0f, 1.0f, 0.0f));
    Transform::_transformMatrix = glm::rotate(Transform::_transformMatrix, radZ, glm::vec3(0.0f, 0.0f, 1.0f));

    Transform::_rotation.X += X;
    Transform::_rotation.Y += Y;
    Transform::_rotation.Z += Z;

    Transform::_isShifted = true;
}
void Transform::AddRotation(Vector3 rotation) {
    const float radX = M_PI / 180.0f * rotation.X;
    const float radY = M_PI / 180.0f * rotation.Y;
    const float radZ = M_PI / 180.0f * rotation.Z;

    Transform::_transformMatrix = glm::rotate(Transform::_transformMatrix, radX, glm::vec3(1.0f, 0.0f, 0.0f));
    Transform::_transformMatrix = glm::rotate(Transform::_transformMatrix, radY, glm::vec3(0.0f, 1.0f, 0.0f));
    Transform::_transformMatrix = glm::rotate(Transform::_transformMatrix, radZ, glm::vec3(0.0f, 0.0f, 1.0f));

    Transform::_rotation.X += rotation.X;
    Transform::_rotation.Y += rotation.Y;
    Transform::_rotation.Z += rotation.Z;

    Transform::_isShifted = true;
}
void Transform::SetRotation(float X, float Y, float Z) {
    Vector3 direction = Vector3(X, Y, Z) - Transform::_rotation;

    Transform::AddRotation(direction);
}
void Transform::SetRotation(Vector3 rotation) {
    Vector3 direction = rotation - Transform::_rotation;

    Transform::AddRotation(direction);
}


Vector3 Transform::GetScale() {
    return Transform::_scale;
}
void Transform::SetScale(float X, float Y, float Z) {
    Vector3 delta = Transform::_scale / Vector3(X, Y, Z);
    Transform::_transformMatrix = glm::scale(Transform::_transformMatrix, glm::vec3(1 / delta.X, 1 / delta.Y, 1 / delta.Z));

    Transform::_scale.X = X;
    Transform::_scale.Y = Y;
    Transform::_scale.Z = Z;

    ApplyTransformation();
}
void Transform::SetScale(Vector3 scale) {
    Vector3 delta = Transform::_scale / scale;
    Transform::_transformMatrix = glm::scale(Transform::_transformMatrix, glm::vec3(1 / delta.X, 1 / delta.Y, 1 / delta.Z));

    Transform::_scale.X = scale.X;
    Transform::_scale.Y = scale.Y;
    Transform::_scale.Z = scale.Z;

    ApplyTransformation();
}

