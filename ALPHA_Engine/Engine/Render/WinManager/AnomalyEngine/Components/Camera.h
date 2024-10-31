#pragma once
#include "Core/Components/Component.h"
#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"

namespace AnomalyEngine::WindowsManager {
    class Window;
}
namespace Core {
    class Factory;
}

namespace AnomalyEngine::Render::Components {
    class Camera : public Core::Component {
    friend class Core::Factory;

    private:
        explicit Camera(float fov = 90,float aspect = 1,float zNear = -1,float zFar = 1);
        AnomalyEngine::WindowsManager::Window* _window = nullptr;

        float _fov;
        float _aspect;
        float _zNear;
        float _zFar;

        bool _isPerspective = false;

    public:
        ~Camera();

        void SetProjection(bool isPerspective);
        //True = perspective matrix
        //otherwise ortho matrix
        bool GetProjection() const;
        glm::mat4x4 GetProjectionMatrix();

        void GetCameraInfo(float* Fov, float* Aspect, float* ZNear, float* ZFar);
    };
}