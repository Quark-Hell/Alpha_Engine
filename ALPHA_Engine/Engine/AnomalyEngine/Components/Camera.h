#pragma once
#include "Core/Components/Component.h"
#include "glm/glm.hpp"

namespace WindowsManager {
    class WindowsManager;
    class Window;
}
struct GLFWwindow;

namespace AnomalyEngine {
    class Camera final : public Core::Component {
        friend class CamerasBuffer;
        friend class RenderEngine;
        friend class WindowsManager::WindowsManager;

    private:
        Camera(size_t width = 100, size_t height = 100, float fov = 45, float aspect = 1.3333333, float zNear = 0.01, float zFar = 10000);
        WindowsManager::Window* _window = nullptr;

        bool _useRectangle = false;
        size_t _rectangleIndex = 0;

        float _fov;
        float _aspect;
        float _zNear;
        float _zFar;

        bool _isPerspective = true;

        size_t _width;
        size_t _height;

    private:
        void OnParentObjectChanged(Core::Object& newParent) override;

    public:
        ~Camera() override = default;

        void SetProjection(bool isPerspective);
        //True = perspective matrix
        //otherwise ortho matrix
        [[nodiscard]] bool GetProjection() const;
        glm::mat4x4 GetProjectionMatrix();

        void SetRenderWindow(WindowsManager::Window* window);

        void SetFov(float fov);
        void SetZNear(float zNear);
        void SetZFar(float zFar);
        void SetWidth(size_t width);
        void SetHeight(size_t height);
        void SetUseRectangle(bool use);
        void SetIndexRectangle(size_t index);

        [[nodiscard]] size_t GetWidth() const;
        [[nodiscard]] size_t GetHeight() const;
        [[nodiscard]] bool GetUseRectangle() const;
        [[nodiscard]] size_t GetRectangleIndex() const;
    };
}