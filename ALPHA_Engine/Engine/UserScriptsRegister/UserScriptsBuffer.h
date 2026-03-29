#pragma once

#include "Core/Factory.h"
#include "Core/Objects/GameObject.h"

#include "UserScript.h"
#include "Core/ECS/TSystemData.h"

namespace Register {
    class UserScriptsBuffer final : public Core::TSystemData<UserScript> {
    public:
        UserScriptsBuffer(size_t initialBufferSize = 0);

        template<typename T>
        requires std::derived_from<T, UserScript>
        T* CreateUserScript() {
            _data.emplace_back(std::unique_ptr<UserScript>(new T()));
            T* script = static_cast<T*>(_data.back().get());

            Core::Logger::LogInfo("User script created");

            return script;
        }

        template<typename T>
        requires std::derived_from<T, UserScript>
        T* CreateActor(const std::string& name = "Actor") {
            _data.emplace_back(std::unique_ptr<UserScript>(new T()));
            T* script = static_cast<T*>(_data.back().get());

            Core::GameObject& obj = Core::Factory::CreateObject<Core::GameObject>();

            obj.AddComponent(*script);
            obj.SetName(name);

            Core::Logger::LogInfo("Actor created");

            return script;
        }

        ~UserScriptsBuffer() override = default;
    };
}
