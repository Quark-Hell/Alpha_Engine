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
}

namespace Register {
    class UserScript;
}

namespace Render {
    namespace WindowsManager {
        class Window;

        namespace BindsEngine {
            enum class EnumMouseSensorStates : uint8_t;
            enum class EnumMouseKeysStates : uint8_t;
            enum class EnumKeyboardTable : uint16_t;
            class Bind;
        }
    }

    namespace AnomalyEngine::Components {
        class Mesh;
        class Camera;
        class DirectLight;
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

#if USER_SCRIPTS_REGISTER_INCLUDED
        static Register::UserScript *CreateUserScript(Core::Component *script);
        static bool RemoveUserScript(const Core::Component *object);
        static Register::UserScript *CreateUserScript();
#endif

#if RENDER_INCLUDED
        static Render::WindowsManager::Window *CreateWindow(int width, int height, const char *title);
#endif

#if ANOMALY_ENGINE_INCLUDED
        static Render::AnomalyEngine::Components::Camera *CreateCamera(float fov = 60, float aspect = 1,
                                                                       float zNear = 0.1f, float zFar = 10000);
        static bool RemoveCamera(const Render::AnomalyEngine::Components::Camera *camera);

        static Render::AnomalyEngine::Components::Mesh *CreateMesh();
        static Render::AnomalyEngine::Components::Mesh *CreateMesh(const std::string &path);

        static Render::AnomalyEngine::Components::DirectLight *CreateDirectLight(const Core::Vector3& direction = Core::Vector3(0, 0.7, 0.3));
#endif

#if BINDS_ENGINE_INCLUDED
        static Render::WindowsManager::BindsEngine::Bind *CreateGeneralBind();

        static Render::WindowsManager::BindsEngine::Bind *CreateMouseButtonsBind(
            const std::vector<std::function<void(void)> > &Operations,
            const std::vector<Render::WindowsManager::BindsEngine::EnumMouseKeysStates> &MouseKeysState,
            const std::vector<Render::WindowsManager::BindsEngine::EnumMouseTable> &MouseKeys,
            Render::WindowsManager::Window *window);

        static Render::WindowsManager::BindsEngine::Bind *CreateMouseSensorBind(
            const std::vector<std::function<void(void)> > &Operations,
            const Render::WindowsManager::BindsEngine::EnumMouseSensorStates MouseSensorState,
            Render::WindowsManager::Window *window);

        static Render::WindowsManager::BindsEngine::Bind *CreateKeyboardBind(
            const std::vector<std::function<void(void)> > &Operations,
            const std::vector<Render::WindowsManager::BindsEngine::EnumKeyboardKeysStates> &KeysState,
            const std::vector<Render::WindowsManager::BindsEngine::EnumKeyboardTable> &KeyboardKeys,
            Render::WindowsManager::Window *window);

        static void RemoveBind(const Render::WindowsManager::BindsEngine::Bind *removedBind);
#endif
    };
}
