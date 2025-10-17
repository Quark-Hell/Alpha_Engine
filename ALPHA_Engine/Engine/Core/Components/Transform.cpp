#define _USE_MATH_DEFINES
#include "Transform.h"

#include "Core/Logger/Logger.h"
#include "Core/Math/glmMath.h"

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

    glm::vec3 Transform::GetRotation() { 
        const glm::vec3 euler = glm::eulerAngles(_rotation);
        const glm::vec3 degrees = glm::degrees(euler);

        return degrees;
    }
    glm::quat Transform::GetRotationQuat() {
        return _rotation;
    }


    void Transform::AddRotation(const float X, const float Y, const float Z) {
        const float radX = glm::radians(X);
        const float radY = glm::radians(Y);
        const float radZ = glm::radians(Z);

        Transform::_transformMatrix = glm::rotate(Transform::_transformMatrix, radX, glm::vec3(1.0f, 0.0f, 0.0f));
        Transform::_transformMatrix = glm::rotate(Transform::_transformMatrix, radY, glm::vec3(0.0f, 1.0f, 0.0f));
        Transform::_transformMatrix = glm::rotate(Transform::_transformMatrix, radZ, glm::vec3(0.0f, 0.0f, 1.0f));


        glm::vec3 euler = glm::radians(glm::vec3(X, Y, Z));
        Transform::_rotation = glm::quat(euler);

        //Transform::_rotation.x += X;
        //Transform::_rotation.y += Y;
        //Transform::_rotation.z += Z;
    }
    void Transform::AddRotation(glm::vec3 rotation) {
        const float radX = glm::radians(rotation.x);
        const float radY = glm::radians(rotation.y);
        const float radZ = glm::radians(rotation.z);

        Transform::_transformMatrix = glm::rotate(Transform::_transformMatrix, radX, glm::vec3(1.0f, 0.0f, 0.0f));
        Transform::_transformMatrix = glm::rotate(Transform::_transformMatrix, radY, glm::vec3(0.0f, 1.0f, 0.0f));
        Transform::_transformMatrix = glm::rotate(Transform::_transformMatrix, radZ, glm::vec3(0.0f, 0.0f, 1.0f));

        glm::vec3 euler = glm::radians(rotation);
        Transform::_rotation = glm::quat(euler);

        //Transform::_rotation.x += rotation.x;
        //Transform::_rotation.y += rotation.y;
        //Transform::_rotation.z += rotation.z;
    }

    void Transform::SetRotation(const float X, const float Y, const float Z) {
        const glm::vec3 direction = glm::vec3(X, Y, Z) - glm::vec3(_rotation.x, _rotation.y, _rotation.z);

        Transform::AddRotation(direction);
    }
    void Core::Transform::SetRotation(glm::vec3 rotation) {
        const glm::vec3 direction = rotation - glm::vec3(_rotation.x, _rotation.y, _rotation.z);

        Transform::AddRotation(direction);
    }

    void Transform::SetRotationQuat(glm::quat rotation) {
        _rotation = glm::normalize(rotation);

        RecalculateTransformMatrix();
    }
    void Transform::SetRotationQuatSlerp(const glm::quat& targetQuat, float t) {

        glm::quat norm = glm::normalize(targetQuat);

        Transform::_rotation = glm::lerp(Transform::_rotation, norm, t);
        Transform::_rotation = glm::normalize(Transform::_rotation);

        RecalculateTransformMatrix();
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

    glm::mat4x4 Transform::GetTransformMatrix() const { return Transform::_transformMatrix; }
    void Transform::RecalculateTransformMatrix() {
        glm::mat4 T = glm::translate(glm::mat4(1.0f), _position);
        glm::mat4 R = glm::toMat4(glm::normalize(_rotation));
        glm::mat4 S = glm::scale(glm::mat4(1.0f), _scale);

        _transformMatrix = R * T * S;
    }

    glm::vec3 Transform::GetForward() const noexcept {
        glm::mat4x4 matrix = GetTransformMatrix();
        return glm::vec3(matrix[0][2], matrix[1][2], matrix[2][2]);
    }
    glm::vec3 Transform::GetRight() const noexcept {
        glm::mat4x4 matrix = GetTransformMatrix();
        return glm::vec3(matrix[0][0], matrix[1][0], matrix[2][0]);
    }
    glm::vec3 Transform::GetUp() const noexcept {
        glm::mat4x4 matrix = GetTransformMatrix();
        return glm::vec3(matrix[0][1], matrix[1][1], matrix[2][1]);
    }
}