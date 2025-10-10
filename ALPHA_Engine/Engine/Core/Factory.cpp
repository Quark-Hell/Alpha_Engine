#include "Factory.h"

#include "World.h"
#include "Objects/GameObject.h"
#include "Objects/FakeObject.h"

#include "Logger/Logger.h"

namespace Core {
    Core::GameObject& Factory::CreateObject() {
        World::GetGameObjects()->emplace_back(std::unique_ptr<Core::GameObject>(new Core::GameObject()));
        Core::Logger::LogInfo("Object created");
        return *World::GetGameObjects()->back().get();
    }

    Core::FakeObject& Factory::CreateFakeObject() {
        World::GetFakeObjects()->emplace_back(std::unique_ptr<Core::FakeObject>(new Core::FakeObject()));
        Core::Logger::LogInfo("Fake Object created");
        return *World::GetFakeObjects()->back().get();
    }
}