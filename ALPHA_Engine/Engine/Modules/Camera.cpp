#include "Camera.h"

#include "Object.h"

Camera::Camera() {
    Camera::UpdateProjectionMatrix();
}
Camera::~Camera() {

}

void Camera::SetCameraInfo(float Fov, float Aspect, float ZNear, float ZFar) {
    Camera::Fov = Fov;
    Camera::Aspect = Aspect;
    Camera::ZNear = ZNear;
    Camera::ZFar = ZFar;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(Fov, Aspect, ZNear, ZFar);
}
void Camera::GetCameraInfo(float* Fov, float* Aspect, float* ZNear, float* ZFar) {
    *Fov = Camera::Fov;
    *Aspect = Camera::Aspect;
    *ZNear = Camera::ZNear;
    *ZFar = Camera::ZFar;
}

ModulesList Camera::GetType() {
    return ModulesList::CameraType;
}

Object* Camera::GetParentObject() {
    return Module::GetParentObject();
}
void Camera::SetParentObject(const Object& parent) {
    Module::SetParentObject(parent);
}

float Camera::GetFov() {
    return Camera::Fov;
}
float Camera::GetAspect() {
    return Camera::Aspect;
}
float Camera::GetZNear() {
    return Camera::ZNear;
}
float Camera::GetZFar() {
    return Camera::ZFar;
}

glm::mat4x4 Camera::GetProjectionMatrix()
{
    return Camera::_projectionMatrix;
}

glm::mat4x4 Camera::GetTransformMatrix()
{
    return Camera::_transformMatrix;
}


void Camera::AddPosition(float X, float Y, float Z) {
    Camera::_position.X += X;
    Camera::_position.Y += Y;
    Camera::_position.Z += Z;

    Camera::_origin.X += X;
    Camera::_origin.Y += Y;
    Camera::_origin.Z += Z;

    //Camera::_isShifted = true;
}
void Camera::AddPosition(Vector3 position) {
    Camera::_position += position;
    Camera::_origin += position;

    //Camera::_isShifted = true;
}
void Camera::SetPosition(float X, float Y, float Z) {
    Vector3 direction = Vector3(X, Y, Z) - Camera::_position;

    Camera::AddPosition(direction);
}
void Camera::SetPosition(Vector3 position) {
    Vector3 direction = position - Camera::_position;

    Camera::AddPosition(direction);
}


void Camera::AddRotation(float X, float Y, float Z) {
    const float radX = M_PI / 180 * X;
    const float radY = M_PI / 180 * Y;
    const float radZ = M_PI / 180 * Z;

    Camera::_rotation.X += X;
    Camera::_rotation.Y += Y;
    Camera::_rotation.Z += Z;

    //Camera::_isShifted = true;
}
void Camera::AddRotation(Vector3 rotation) {
    const float radX = M_PI / 180 * rotation.X;
    const float radY = M_PI / 180 * rotation.Y;
    const float radZ = M_PI / 180 * rotation.Z;

    Camera::_rotation.X += rotation.X;
    Camera::_rotation.Y += rotation.Y;
    Camera::_rotation.Z += rotation.Z;

    //Camera::_isShifted = true;
}

void Camera::SetRotation(float X, float Y, float Z) {
    Vector3 direction = Vector3(X, Y, Z) - Camera::_rotation;

    Camera::AddRotation(direction);
}
void Camera::SetRotation(Vector3 rotation) {
    Vector3 direction = rotation - Camera::_rotation;

    Camera::AddRotation(direction);
}


void Camera::ApplyTransformation() {
    if (GetParentObject() == nullptr)
        return;

    Vector3 originShift = Camera::GetParentObject()->_origin - Camera::GetParentObject()->_position;

    Camera::UpdateProjectionMatrix();
    Camera::UpdateViewMatrix();
}

void Camera::UpdateProjectionMatrix() {
    if (_projectionMode == ProjectionMode::Perspective)
    {
        float r = 0.1f;
        float t = 0.1f;

        float aspect = 16.0f / 9.0f;
        float fov = 60;
        float far = 1000;


        _projectionMatrix = glm::perspective(glm::radians(fov), aspect, ZNear, ZFar);

        //_projectionMatrix = glm::mat4(
        //    ZNear / r, 0, 0, 0,
        //    0, ZNear / t, 0, 0,
        //    0, 0, (-ZFar - ZNear) / (ZFar - ZNear), -1,
        //    0, 0, -2 * ZFar * ZNear / (ZFar - ZNear), 0);

        //_projectionMatrix = glm::mat4(
        //    //ROW 1
        //    znear / width / 4.0 * zoomfactor, 0.0, left + right / width / 2, 0.0,
        //        //ROW 2
        //        0.0, znear / height / 4.0 * zoomfactor, top + bottom / height / 2, 0.0,
        //        //ROW 3
        //        0.0, 0.0, -(zfar + znear) / (zfar - znear), 2 * zfar * znear / zfar - znear,
        //        // ROW 4
        //        0.0, 0.0, -1.0, 0.0
        //);
    }
}

void Camera::UpdateViewMatrix()
{

    Vector4 parentRotation;
    Vector3 parentPosition;
    Vector3 parentScale;

    if (ParentObject != nullptr) {
        parentRotation = ParentObject->GetRotation();
        parentPosition = ParentObject->GetPosition();
        parentScale = ParentObject->GetScale();
    }

    glm::mat4x4 rotMat(1.0f);

    const float radX = M_PI / 180 * (Camera::_rotation.X + parentRotation.X);
    const float radY = M_PI / 180 * (Camera::_rotation.Y + parentRotation.Y);
    const float radZ = M_PI / 180 * (Camera::_rotation.Z + parentRotation.Z);

    rotMat = glm::rotate(rotMat, radX, glm::vec3(1.0f, 0.0f, 0.0f));
    rotMat = glm::rotate(rotMat, radY, glm::vec3(0.0f, 1.0f, 0.0f));
    rotMat = glm::rotate(rotMat, radZ, glm::vec3(0.0f, 0.0f, 1.0f));

    glm::mat4x4 transMat(1.0f);
    transMat = glm::translate(glm::vec3(
        Camera::_position.X + parentPosition.X,
        Camera::_position.Y + parentPosition.Y,
        Camera::_position.Z + parentPosition.Z));

    Camera::_transformMatrix = rotMat * transMat;
}
