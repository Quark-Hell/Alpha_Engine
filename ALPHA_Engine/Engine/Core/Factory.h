//This class exist only for user API
//Do not use some function from this in Engine

#pragma once

#include <string>
#include <vector>
#include <cstdint>
#include <functional>

#include "Math/Vectors.h"

namespace Render::WindowsManager::BindsEngine {
    enum class EnumMouseTable : uint8_t;
    enum class EnumKeyboardKeysStates : uint8_t;
    enum class EnumMouseSensorStates : uint8_t;
    enum class EnumMouseKeysStates : uint8_t;
    enum class EnumKeyboardTable : uint16_t;
    class Bind;
}


namespace Render::WindowsManager {
    class Window;
    namespace AnomalyEngine {
        class Mesh;
        class Camera;
        class DirectLight;
        class PointLight;
    }
}

namespace Core {
    class Object;
    class Component;

    class Factory {
    private:
        Factory() = default;
        ~Factory() = default;

    public:
        static bool RemoveObject(const Core::Object *object);
        static Core::Object *CreateObject();

#if ANOMALY_ENGINE_INCLUDED
        static Render::WindowsManager::AnomalyEngine::Camera *CreateCamera(float fov = 60, float aspect = 1,
                                                                       float zNear = 0.1f, float zFar = 10000);
        static bool RemoveCamera(const Render::WindowsManager::AnomalyEngine::Camera *camera);

        static Render::WindowsManager::AnomalyEngine::Mesh *CreateMesh();
        static Render::WindowsManager::AnomalyEngine::Mesh *CreateMesh(const std::string &path);

        static Render::WindowsManager::AnomalyEngine::DirectLight *CreateDirectLight(const Core::Vector3& direction = Core::Vector3(0, 0.7, 0.3));
        static Render::WindowsManager::AnomalyEngine::PointLight *CreatePointLight(float radius = 1.0f, float constant = 1.0f, float linear = 0.7f, float quadratic = 1.8f);
#endif
    };
}
