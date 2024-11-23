#pragma once
#include "Core/Components/Component.h"
#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"

struct GLFWwindow;

namespace AnomalyEngine {
    class Camera final : public Core::Component {
        friend class CamerasBuffer;
        friend class RenderEngine;

    private:
        Camera(size_t width = 100, size_t height = 100, float fov = 60, float aspect = 1.3333333, float zNear = 0.01, float zFar = 10000);
        GLFWwindow* _window = nullptr;

        float _fov;
        float _aspect;
        float _zNear;
        float _zFar;

        bool _isPerspective = true;

        size_t _width;
        size_t _height;

    public:
        ~Camera();

        void SetProjection(bool isPerspective);
        //True = perspective matrix
        //otherwise ortho matrix
        [[nodiscard]] bool GetProjection() const;
        glm::mat4x4 GetProjectionMatrix();

        void SetRenderWindow(GLFWwindow* window);

        void SetFov(float fov);
        void SetAspect(float aspect);
        void SetZNear(float zNear);
        void SetZFar(float zFar);
        void SetWidth(size_t width);
        void SetHeight(size_t height);

        [[nodiscard]] size_t GetWidth() const;
        [[nodiscard]] size_t GetHeight() const;

        void SetCameraInfo(float Fov, float Aspect, float ZNear, float ZFar);
        void GetCameraInfo(float* Fov, float* Aspect, float* ZNear, float* ZFar);
    };
}