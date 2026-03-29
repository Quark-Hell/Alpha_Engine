#include "System.h"
#include "Core/World.h"

namespace Core {
    System::System(const std::vector<std::string> &tokens, const size_t order) : _tokens(tokens), _order(order) {
        Core::World::AddSystem(_order, this);
    };

    const std::vector<std::string>& System::GetTokens() {
        return _tokens;
    }
}