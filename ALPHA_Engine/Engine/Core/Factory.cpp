#include "Factory.h"

#include "World.h"
#include "Object.h"

#include "Logger/Logger.h"

bool Core::Factory::RemoveObject(const Core::Object* object) {
    auto& list = *World::GetObjects(); 

    for (auto it = list.begin(); it != list.end(); ++it) {
        if (it->get() == object) { 
            Core::Logger::LogInfo("Removing object");
            list.erase(it);
            Core::Logger::LogInfo("Object removed");
            return true;
        }
    }

    Core::Logger::LogInfo("Object does not exist");
    return false;
}

Core::Object& Core::Factory::CreateObject() {
  World::GetObjects()->emplace_back(std::unique_ptr<Core::Object>(new Core::Object()));
  Core::Logger::LogInfo("Object created");
  return *World::GetObjects()->back().get();
}



