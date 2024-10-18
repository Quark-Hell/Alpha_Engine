#pragma once
#include "Core/Components/Component.h"

namespace AnomalyEngine::WindowsManager {
    class Window;
}
namespace Core {
    class Factory;
}

namespace AnomalyEngine::Render {
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

        void GetCameraInfo(float* Fov, float* Aspect, float* ZNear, float* ZFar);
    };
}