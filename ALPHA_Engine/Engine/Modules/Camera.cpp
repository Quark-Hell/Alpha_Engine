#include "Camera.h"

#include "Object.h"

Camera::Camera() {

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

//TODO:
Vector3 Camera::GetDirectionOfView() {
    DirectionOfView = GetParentObject()->GetRotation();

    //DirectionOfView.NormilizeSelf();

    return DirectionOfView;
}