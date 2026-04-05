//This class exist only for user API
//Do not use some function from this in Engine

#pragma once

#include "Core/Objects/Object.h"
#include "Core/Objects/FakeObject.h"
#include "Core/Objects/GameObject.h"

#include "Resources/Resource.h"

#include "Core/World.h"

namespace Core {;
    class Component;

    class Factory {
    private:
        Factory() = default;
        ~Factory() = default;

    public:
        
        template<typename T>
        requires std::derived_from <T, Core::Object>
        static T& CreateObject() {
            if constexpr (std::is_same_v <T, Core::GameObject>) {
                World::GetGameObjects()->emplace_back(std::unique_ptr<Core::GameObject>(new Core::GameObject()));
                Core::Logger::LogInfo("Game Object created");
                return *World::GetGameObjects()->back().get();
            }
            else
            {
                World::GetFakeObjects()->emplace_back(std::unique_ptr<Core::FakeObject>(new Core::FakeObject()));
                Core::Logger::LogInfo("Fake Object created");
                return *World::GetFakeObjects()->back().get();
            }
        }

        template<typename T>
        requires std::derived_from <T, Core::Resource>
        static T& CreateResource() {
            auto& resources = *World::GetResources();
            resources.emplace_back(std::make_unique<T>());

            Core::Logger::LogInfo("Resource created: ");

            return *static_cast<T*>(resources.back().get());
        }
    };
}
