#include "Factory.h"

#include "World.h"
#include "Object.h"

#include "Logger/Logger.h"

bool Core::Factory::RemoveObject(const Core::Object* object) {
  const auto list = World::GetObjects();
  auto it = std::begin(*list);

  for (size_t i = 0; i < World::GetObjects()->size(); ++i) {
    if (it->get() == &object[i]) {
      Core::Logger::LogInfo("Removing object");
      World::GetObjects()->erase(it);
      Core::Logger::LogInfo("Object removed");
      return true;
    }
    std::advance(it, 1);
  }

  Core::Logger::LogInfo("Object do not exist");
  return false;
}

Core::Object& Core::Factory::CreateObject() {
  World::GetObjects()->emplace_back(std::unique_ptr<Core::Object>(new Core::Object()));
  Core::Logger::LogInfo("Object created");
  return *World::GetObjects()->back().get();
}



