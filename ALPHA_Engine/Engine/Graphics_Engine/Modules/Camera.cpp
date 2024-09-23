#define _USE_MATH_DEFINES

#include "Camera.h"

#include "Core/Modules/Module.h"
#include "Core/Modules/Transform.h"
#include "Core/Math/Vectors.h"
#include "Core/Object.h"

#include "ModuleList.h"


#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

//OpenGL
#pragma comment(lib, "opengl32")
#pragma comment(lib, "glu32")
#include <Gl/gl.h>
#include <Gl/glu.h>



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

void Camera::UpdateProjectionMatrix() {
    if (_projectionMode == ProjectionMode::Perspective)
    {
        float aspect = 16.0f / 9.0f;
        float fov = 60;
        //float far = 1000;

        _projectionMatrix = glm::perspective(glm::radians(fov), aspect, ZNear, ZFar);
    }
}
