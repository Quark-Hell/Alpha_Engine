#include "Factory.h"

#include "World.h"
#include "Objects/GameObject.h"
#include "Objects/FakeObject.h"

#include "Logger/Logger.h"

namespace Core {
    bool Factory::RemoveObject(const Core::GameObject* object) {
        auto& list = *World::GetObjects();

        for (auto it = list.begin(); it != list.end(); ++it) {
            if (it->get() == object) {
                Logger::LogInfo("Removing object");
                list.erase(it);
                Logger::LogInfo("Object removed");
                return true;
            }
        }

        Logger::LogWarning("Object does not exist");
        return false;
    }

    Core::GameObject& Factory::CreateObject() {
        World::GetObjects()->emplace_back(std::unique_ptr<Core::GameObject>(new Core::GameObject()));
        Core::Logger::LogInfo("Object created");
        return *World::GetObjects()->back().get();
    }

    Core::FakeObject& Factory::CreateFakeObject() {
        World::GetFakeObjects()->emplace_back(std::unique_ptr<Core::FakeObject>(new Core::FakeObject()));
        Core::Logger::LogInfo("Fake Object created");
        return *World::GetFakeObjects()->back().get();
    }
}