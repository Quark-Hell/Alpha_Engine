#pragma once

#include "Core/Factory.h"
#include "Core/Objects/GameObject.h"

#include "UserScript.h"
#include "Core/ECS/TSystemData.h"

namespace Register {
    class UserScriptsBuffer final : public Core::TSystemData<UserScript> {
    public:
        UserScriptsBuffer(size_t initialBufferSize = 0);

        template<typename T,
        typename K = std::enable_if_t<std::is_base_of_v<T, UserScript>>>
        T* CreateUserScript() {
            T* userScript = new T();

            _data.emplace_back(std::unique_ptr<UserScript>(userScript));
            Core::Logger::LogInfo("User script created");

            return userScript;
        }

        template<typename T,
        typename K = std::enable_if_t<std::is_base_of_v<UserScript, T>>>
        T* CreateActor(const std::string& name = "Actor") {
            T* userScript = new T();

            _data.emplace_back(std::unique_ptr<UserScript>(new T()));
            Core::GameObject& obj = Core::Factory::CreateObject<Core::GameObject>();

            obj.AddComponent(*_data.back().get());
            obj.SetName(name);

            Core::Logger::LogInfo("Actor created");

            return userScript;
        }

        ~UserScriptsBuffer() override = default;
    };
}
