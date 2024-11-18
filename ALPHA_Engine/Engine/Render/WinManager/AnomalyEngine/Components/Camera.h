#pragma once
#include "Core/Components/Component.h"
#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"

namespace Render::WindowsManager {
    class Window;
}
namespace Core {
    class Factory;
}

namespace Render::WindowsManager::AnomalyEngine {
    class Camera : public Core::Component {
    friend class Core::Factory;

    private:
        explicit Camera(float fov = 60,float aspect = 1.3333333,float zNear = 0.01,float zFar = 10000);
        Render::WindowsManager::Window* _window = nullptr;

        float _fov;
        float _aspect;
        float _zNear;
        float _zFar;

        bool _isPerspective = true;

    public:
        ~Camera();

        void SetProjection(bool isPerspective);
        //True = perspective matrix
        //otherwise ortho matrix
        [[nodiscard]] bool GetProjection() const;
        glm::mat4x4 GetProjectionMatrix();

        void SetFov(float fov);
        void SetAspect(float aspect);
        void SetZNear(float zNear);
        void SetZFar(float zFar);

        void SetCameraInfo(float Fov, float Aspect, float ZNear, float ZFar);
        void GetCameraInfo(float* Fov, float* Aspect, float* ZNear, float* ZFar);
    };
}