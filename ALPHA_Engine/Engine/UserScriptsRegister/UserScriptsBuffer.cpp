#include "UserScriptsBuffer.h"
#include "Logger/Logger.h"

namespace Register {
    UserScriptsBuffer::UserScriptsBuffer() : Core::TSystemData<UserScript>("UserScriptsBuffer") {
        _data.reserve(64);
    }

    UserScriptsBuffer* UserScriptsBuffer::GetInstance() {
        static UserScriptsBuffer buffer;
        return &buffer;
    }

    UserScript* UserScriptsBuffer::CreateUserScript(UserScript* script) {
        const auto buffer = UserScriptsBuffer::GetInstance();

        for (auto& it : buffer->_data) {
            if (script == it.get()) {
                Logger::Logger::LogError("User script already exist: " + std::string(__FILE__) + ":" + std::to_string(__LINE__));
                return nullptr;
            }
        }
        buffer->_data.emplace_back(std::unique_ptr<Register::UserScript>(script));
        return buffer->_data.back().get();
    }
}