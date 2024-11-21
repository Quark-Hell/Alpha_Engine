#include "BindsBuffer.h"

namespace Render::WindowsManager::BindsEngine {
    BindsBuffer::BindsBuffer() : Core::TSystemData<Bind>("BindsBuffer") {
        _data.reserve(64);
    }

    BindsBuffer* BindsBuffer::GetInstance() {
        static BindsBuffer buffer;
        return &buffer;
    }

    Bind *BindsBuffer::CreateMouseButtonsBind(
        const std::vector<std::function<void()>> &Operations,
        const std::vector<EnumMouseKeysStates> &MouseKeysState,
        const std::vector<EnumMouseTable> &MouseKeys,
        Window *window) {

        const auto buffer = BindsBuffer::GetInstance();
        buffer->_data.emplace_back(std::unique_ptr<Bind>(new Bind()));

        buffer->_data.back().get()->Create(Operations, {}, {}, MouseKeysState, MouseKeys, {}, window);

        Logger::Logger::LogInfo("Mouse button bind created");
        return buffer->_data.back().get();
    }

    Bind *BindsBuffer::CreateMouseSensorBind(
        const std::vector<std::function<void()>> &Operations,
        const std::vector<EnumMouseSensorStates>& MouseSensorState,
        Window *window) {

        const auto buffer = BindsBuffer::GetInstance();

        buffer->_data.emplace_back(std::unique_ptr<Bind>(new Bind()));
        buffer->_data.back().get()->Create(Operations, {}, {}, {}, {}, MouseSensorState, window);

        Logger::Logger::LogInfo("Mouse sensor bind created");
        return buffer->_data.back().get();
    }

    Bind *BindsBuffer::CreateKeyboardBind(
        const std::vector<std::function<void()>> &Operations,
        const std::vector<EnumKeyboardKeysStates> &KeysState,
        const std::vector<EnumKeyboardTable> &KeyboardKeys,
        Window *window) {

        const auto buffer = BindsBuffer::GetInstance();

        buffer->_data.emplace_back(std::unique_ptr<Bind>(new Bind()));
        buffer->_data.back().get()->Create(Operations,KeysState,KeyboardKeys,{},{},{},window);

        Logger::Logger::LogInfo("Keyboard bind created");

        return buffer->_data.back().get();
    }
}