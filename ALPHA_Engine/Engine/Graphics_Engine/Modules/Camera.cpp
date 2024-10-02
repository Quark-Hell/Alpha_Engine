#define _USE_MATH_DEFINES

#include "Camera.h"
#include "Core/Components/Transform.h"
#include "Core/Math/Vectors.h"
#include "Core/Object.h"


#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

//OpenGL
#pragma comment(lib, "opengl32")
#pragma comment(lib, "glu32")
#include <Gl/gl.h>
#include <Gl/glu.h>



GraphicsEngine::Camera::Camera() {
    Camera::UpdateProjectionMatrix();
}
GraphicsEngine::Camera::~Camera() {

}

void GraphicsEngine::Camera::SetCameraInfo(float Fov, float Aspect, float ZNear, float ZFar) {
    Camera::Fov = Fov;
    Camera::Aspect = Aspect;
    Camera::ZNear = ZNear;
    Camera::ZFar = ZFar;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(Fov, Aspect, ZNear, ZFar);
}
void GraphicsEngine::Camera::GetCameraInfo(float* Fov, float* Aspect, float* ZNear, float* ZFar) {
    *Fov = Camera::Fov;
    *Aspect = Camera::Aspect;
    *ZNear = Camera::ZNear;
    *ZFar = Camera::ZFar;
}

void GraphicsEngine::Camera::SetParentObject(const Core::Object& parent) {
    Core::Component::SetParentObject(parent);
}

float GraphicsEngine::Camera::GetFov() {
    return Camera::Fov;
}
float GraphicsEngine::Camera::GetAspect() {
    return Camera::Aspect;
}
float GraphicsEngine::Camera::GetZNear() {
    return Camera::ZNear;
}
float GraphicsEngine::Camera::GetZFar() {
    return Camera::ZFar;
}

glm::mat4x4 GraphicsEngine::Camera::GetProjectionMatrix()
{
    return Camera::_projectionMatrix;
}

void GraphicsEngine::Camera::UpdateProjectionMatrix() {
    if (_projectionMode == ProjectionMode::Perspective)
    {
        float aspect = 16.0f / 9.0f;
        float fov = 60;
        //float far = 1000;

        _projectionMatrix = glm::perspective(glm::radians(fov), aspect, ZNear, ZFar);
    }
}
