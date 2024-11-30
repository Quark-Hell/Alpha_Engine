#include "BindsBuffer.h"

#include <Core/World.h>

namespace BindsEngine {
    BindsBuffer::BindsBuffer() : Core::TSystemData<Bind>("BindsBuffer") {
        _data.reserve(64);
    }

    Bind& BindsBuffer::CreateMouseButtonsBind(
        const std::vector<std::function<void()>> &Operations,
        const std::vector<EnumMouseKeysStates> &MouseKeysState,
        const std::vector<EnumMouseTable> &MouseKeys,
        WindowsManager::Window *window) {

        _data.emplace_back(std::unique_ptr<Bind>(new Bind()));
        _data.back().get()->Create(Operations, {}, {}, MouseKeysState, MouseKeys, {}, window);

        Core::Logger::LogInfo("Mouse button bind created");
        return *_data.back().get();
    }

    Bind& BindsBuffer::CreateMouseSensorBind(
        const std::vector<std::function<void()>> &Operations,
        const std::vector<EnumMouseSensorStates>& MouseSensorState,
        WindowsManager::Window *window) {

        _data.emplace_back(std::unique_ptr<Bind>(new Bind()));
        _data.back().get()->Create(Operations, {}, {}, {}, {}, MouseSensorState, window);

        Core::Logger::LogInfo("Mouse sensor bind created");
        return *_data.back().get();
    }

    Bind& BindsBuffer::CreateKeyboardBind(
        const std::vector<std::function<void()>> &Operations,
        const std::vector<EnumKeyboardKeysStates> &KeysState,
        const std::vector<EnumKeyboardTable> &KeyboardKeys,
        WindowsManager::Window *window) {

        _data.emplace_back(std::unique_ptr<Bind>(new Bind()));
        _data.back().get()->Create(Operations,KeysState,KeyboardKeys,{},{},{},window);

        Core::Logger::LogInfo("Keyboard bind created");

        return *_data.back().get();
    }
}
