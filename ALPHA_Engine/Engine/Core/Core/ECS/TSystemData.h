#pragma once

#include <vector>
#include <memory>
#include "Core/ECS/SystemData.h"
#include "Core/Logger/Logger.h"

namespace Core {
    template<typename T>
    class TSystemData : public SystemData {
    protected:
        std::vector<std::unique_ptr<T>> _data{};

    protected:
        TSystemData() = delete;
        TSystemData(const std::string& token, size_t initialBufferSize = 0) : SystemData(token) { _data.reserve(initialBufferSize); };

    public:
        ~TSystemData() override = default;

        T& GetData(size_t pos) const {
            if (pos >= _data.size()) {
                Logger::LogCritical("Data index out of bounds: " + __LOGERROR__);
            }
            return *_data[pos];
        }
        const std::vector<std::unique_ptr<T>>& GetAllData() {
            return _data;
        }

        bool DestroyData(size_t pos) {
            if (pos >= _data.size()) {
                Logger::LogError("Data index out of bounds: " + __LOGERROR__);
                return false;
            }

            _data.erase(_data.begin() + pos);
            Logger::LogInfo("Data was destroyed");
            return true;
        }
        bool DestroyData(T* ptr) {
            if (ptr == nullptr) {
                Logger::LogError("Data is nullptr: " + __LOGERROR__);
                return false;
            }

            for (auto it = _data.begin(); it != _data.end();) {
                if (it->get() == ptr) {
                    _data.erase(it);
                    Logger::LogInfo("Data was destroyed");
                    return true;
                }
                ++it;
            }

            Logger::LogError("Data does not exist: " + __LOGERROR__);
            return false;
        }

        TSystemData(const TSystemData&) = delete;
        TSystemData& operator=(const TSystemData&) = delete;
        TSystemData(TSystemData&&) = delete;
        TSystemData& operator=(TSystemData&&) = delete;
    };
}