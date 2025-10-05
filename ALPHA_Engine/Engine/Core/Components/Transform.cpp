#define _USE_MATH_DEFINES
#include "Transform.h"

#include "Core/Math/Vectors.h"

namespace Core {
    Transform::Transform() {
        SetPosition(0, 0, 0);
        SetRotation(0, 0, 0);
        SetScale(1, 1, 1);
    }

    glm::vec3 Transform::GetPosition() { return Transform::_position; }
    void Transform::AddPosition(const float X, const float Y, const float Z) {
        Transform::_position.x += X;
        Transform::_position.y += Y;
        Transform::_position.z += Z;

        Transform::_transformMatrix = glm::translate(Transform::_transformMatrix, glm::vec3(X, Y, Z));
    }
    void Transform::AddPosition(const glm::vec3& position) {
        Transform::_position.x += position.x;
        Transform::_position.y += position.y;
        Transform::_position.z += position.z;

        Transform::_transformMatrix = glm::translate(Transform::_transformMatrix, glm::vec3(position.x, position.y, position.z));
    }
    void Transform::SetPosition(const float X, const float Y, const float Z) {
        const glm::vec3 direction = glm::vec3(X, Y, Z) - Transform::_position;

        Transform::AddPosition(direction);
    }
    void Transform::SetPosition(const glm::vec3& position) {
        const glm::vec3 direction = position - Transform::_position;

        Transform::AddPosition(direction);
    }

    glm::vec4 Transform::GetRotation() { return Transform::_rotation; }
    void Transform::AddRotation(const float X, const float Y, const float Z) {
        const float radX = M_PI / 180.0f * X;
        const float radY = M_PI / 180.0f * Y;
        const float radZ = M_PI / 180.0f * Z;

        Transform::_transformMatrix = glm::rotate(Transform::_transformMatrix, radX, glm::vec3(1.0f, 0.0f, 0.0f));
        Transform::_transformMatrix = glm::rotate(Transform::_transformMatrix, radY, glm::vec3(0.0f, 1.0f, 0.0f));
        Transform::_transformMatrix = glm::rotate(Transform::_transformMatrix, radZ, glm::vec3(0.0f, 0.0f, 1.0f));

        Transform::_rotation.x += X;
        Transform::_rotation.y += Y;
        Transform::_rotation.z += Z;
    }
    void Transform::AddRotation(glm::vec3 rotation) {
        const float radX = M_PI / 180.0f * rotation.x;
        const float radY = M_PI / 180.0f * rotation.y;
        const float radZ = M_PI / 180.0f * rotation.z;

        Transform::_transformMatrix = glm::rotate(Transform::_transformMatrix, radX, glm::vec3(1.0f, 0.0f, 0.0f));
        Transform::_transformMatrix = glm::rotate(Transform::_transformMatrix, radY, glm::vec3(0.0f, 1.0f, 0.0f));
        Transform::_transformMatrix = glm::rotate(Transform::_transformMatrix, radZ, glm::vec3(0.0f, 0.0f, 1.0f));

        Transform::_rotation.x += rotation.x;
        Transform::_rotation.y += rotation.y;
        Transform::_rotation.z += rotation.z;
    }
    void Transform::SetRotation(const float X, const float Y, const float Z) {
        const glm::vec3 direction = glm::vec3(X, Y, Z) - glm::vec3(_rotation.x, _rotation.y, _rotation.z);

        Transform::AddRotation(direction);
    }
    void Core::Transform::SetRotation(glm::vec3 rotation) {
        const glm::vec3 direction = rotation - glm::vec3(_rotation.x, _rotation.y, _rotation.z);

        Transform::AddRotation(direction);
    }


    glm::vec3 Transform::GetScale() { return Transform::_scale; }
    void Transform::SetScale(const float X, const float Y, const float Z) {
        const glm::vec3 delta = Transform::_scale / glm::vec3(X, Y, Z);
        Transform::_transformMatrix = glm::scale(Transform::_transformMatrix, glm::vec3(1 / delta.x, 1 / delta.y, 1 / delta.z));

        Transform::_scale.x = X;
        Transform::_scale.y = Y;
        Transform::_scale.z = Z;
    }
    void Transform::SetScale(glm::vec3 scale) {
        const glm::vec3 delta = Transform::_scale / scale;
        Transform::_transformMatrix = glm::scale(Transform::_transformMatrix, glm::vec3(1 / delta.x, 1 / delta.y, 1 / delta.z));

        Transform::_scale.x = scale.x;
        Transform::_scale.y = scale.y;
        Transform::_scale.z = scale.z;
    }

    glm::mat4x4 Transform::GetTransformMatrix() { return Transform::_transformMatrix; }
}