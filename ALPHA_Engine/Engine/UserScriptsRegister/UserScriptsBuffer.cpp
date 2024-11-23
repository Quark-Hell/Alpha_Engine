#include "UserScriptsBuffer.h"
#include "Core/Logger/Logger.h"

namespace Register {
    UserScriptsBuffer::UserScriptsBuffer() : Core::TSystemData<UserScript>("UserScriptsBuffer") {
        _data.reserve(64);
    }

    UserScript* UserScriptsBuffer::CreateUserScript(UserScript* script) {
        for (auto& it : _data) {
            if (script == it.get()) {
                Core::Logger::LogError("User script already exist: " + __LOGERROR__);
                return nullptr;
            }
        }
        _data.emplace_back(std::unique_ptr<Register::UserScript>(script));
        return _data.back().get();
    }
}