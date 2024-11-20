#include "SystemData.h"
#include "Core/World.h"

namespace Core {
    SystemData::SystemData(const std::string& token) : Token(token)  {
        World::AddSystemData(Token, this);
    }
}