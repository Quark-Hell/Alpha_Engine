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

    glm::vec3 Transform::GetPosition() const noexcept { return Transform::_position; }
    void Transform::AddPosition(const float X, const float Y, const float Z) {
        Transform::_position.x += X;
        Transform::_position.y += Y;
        Transform::_position.z += Z;

        Transform::RecalculateTransformMatrix();
    }
    void Transform::AddPosition(const glm::vec3& position) {
        Transform::_position.x += position.x;
        Transform::_position.y += position.y;
        Transform::_position.z += position.z;

        Transform::RecalculateTransformMatrix();
    }
    void Transform::SetPosition(const float X, const float Y, const float Z) {
        Transform::_position.x = X;
        Transform::_position.y = Y;
        Transform::_position.z = Z;

        Transform::RecalculateTransformMatrix();
    }
    void Transform::SetPosition(const glm::vec3& position) {
        Transform::_position.x = position.x;
        Transform::_position.y = position.y;
        Transform::_position.z = position.z;

        Transform::RecalculateTransformMatrix();
    }

    glm::vec3 Transform::GetRotation() const noexcept { 
        const glm::vec3 euler = glm::eulerAngles(_rotation);
        const glm::vec3 degrees = glm::degrees(euler);

        return degrees;
    }
    glm::quat Transform::GetRotationQuat() const noexcept {
        return _rotation;
    }


    void Transform::AddRotation(const float X, const float Y, const float Z) {
        const float radX = glm::radians(X);
        const float radY = glm::radians(Y);
        const float radZ = glm::radians(Z);

        glm::quat delta = glm::quat(glm::vec3(radX, radY, radZ));
        _rotation = glm::normalize(delta * _rotation);

        RecalculateTransformMatrix();
    }
    void Transform::AddRotation(glm::vec3 rotation) {
        const float radX = glm::radians(rotation.x);
        const float radY = glm::radians(rotation.y);
        const float radZ = glm::radians(rotation.z);

        glm::quat delta = glm::quat(glm::vec3(radX, radY, radZ));
        _rotation = glm::normalize(delta * _rotation);

        RecalculateTransformMatrix();
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

    glm::vec3 Transform::GetScale() const noexcept { return Transform::_scale; }

    void Transform::AddScale(const float X, const float Y, const float Z) {
        Transform::_scale.x += X;
        Transform::_scale.y += Y;
        Transform::_scale.z += Z;

        Transform::RecalculateTransformMatrix();
    }

    void Transform::AddScale(glm::vec3 scale) {
        Transform::_scale.x += scale.x;
        Transform::_scale.y += scale.y;
        Transform::_scale.z += scale.z;

        Transform::RecalculateTransformMatrix();
    }

    void Transform::SetScale(const float X, const float Y, const float Z) {
        Transform::_scale.x = X;
        Transform::_scale.y = Y;
        Transform::_scale.z = Z;

        Transform::RecalculateTransformMatrix();
    }
    void Transform::SetScale(glm::vec3 scale) {
        Transform::_scale.x = scale.x;
        Transform::_scale.y = scale.y;
        Transform::_scale.z = scale.z;

        Transform::RecalculateTransformMatrix();
    }

    glm::mat4x4 Transform::GetTransformMatrix() const noexcept { return Transform::_transformMatrix; }
    void Transform::RecalculateTransformMatrix() {
        glm::mat4 T = glm::translate(glm::mat4(1.0f), _position);
        glm::mat4 R = glm::toMat4(glm::normalize(_rotation));
        glm::mat4 S = glm::scale(glm::mat4(1.0f), _scale);

        if (IsCamera) {
            _transformMatrix = R * T * S;
        }
        else
        {
            _transformMatrix = T * R * S;
        }
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