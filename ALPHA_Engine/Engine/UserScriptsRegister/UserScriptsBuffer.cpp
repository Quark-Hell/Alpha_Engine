#include "UserScriptsBuffer.h"
#include "Logger/Logger.h"

namespace Register {
    UserScriptsBuffer* buffer = UserScriptsBuffer::GetInstance();

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

    UserScript& UserScriptsBuffer::GetData(const size_t pos) {
        if (pos >= _data.size()) {
            Logger::Logger::LogError("Script index out of bounds" + std::string(__FILE__) + ":" + std::to_string(__LINE__));
        }
        return *_data[pos];
    }
    const std::vector<std::unique_ptr<UserScript>>& UserScriptsBuffer::GetAllData() {
        return _data;
    }

    bool UserScriptsBuffer::DestroyData(const size_t pos) {
        if (pos >= _data.size()) {
            Logger::Logger::LogError("Script index out of bounds" + std::string(__FILE__) + ":" + std::to_string(__LINE__));
            return false;
        }

        _data.erase(_data.begin() + pos);
        Logger::Logger::LogInfo("Script was destroyed");
        return true;
    }
    bool UserScriptsBuffer::DestroyData(UserScript* ptr) {
        if (ptr == nullptr) {
            Logger::Logger::LogError("Script is nullptr" + std::string(__FILE__) + ":" + std::to_string(__LINE__));
            return false;
        }

        for (auto it = _data.begin(); it != _data.end();) {
            if (it->get() == ptr) {
                _data.erase(it);
                Logger::Logger::LogInfo("Script was destroyed");
                return true;
            }
            ++it;
        }

        Logger::Logger::LogError("Script does not exist" + std::string(__FILE__) + ":" + std::to_string(__LINE__));
        return false;
    }

}