#pragma once

#include "Core/Factory.h"
#include "UserScript.h"
#include "Core/ECS/TSystemData.h"

namespace Register {
    class UserScriptsBuffer final : public Core::TSystemData<UserScript> {
    public:
        UserScriptsBuffer();

        template<typename T,
        typename K = std::enable_if_t<std::is_convertible_v<T, UserScript>>>
        T* CreateUserScript() {
            T* userScript = new T();

            _data.emplace_back(std::unique_ptr<UserScript>(userScript));
            Core::Logger::LogInfo("User script created");

            return userScript;
        }

        template<typename T,
        typename K = std::enable_if_t<std::is_convertible_v<T, UserScript>>>
        T* CreateActor(const std::string& name = "Actor") {
            T* userScript = new T();

            _data.emplace_back(std::unique_ptr<UserScript>(new T()));
            Core::Object* obj = Core::Factory::CreateObject();

            obj->AddComponent(_data.back().get());
            obj->SetName(name);

            Core::Logger::LogInfo("Actor created");

            return userScript;
        }

        ~UserScriptsBuffer() override = default;
    };
}
