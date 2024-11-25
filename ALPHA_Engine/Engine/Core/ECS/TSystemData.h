#pragma once

#include <vector>
#include <memory>
#include "Core/ECS/SystemData.h"
#include "Core/Logger/Logger.h"

namespace Core {
    template<typename T>
    class TSystemData : public SystemData { //<T, std::enable_if_t<std::is_convertible_v<Core::Component, T>>> {
    protected:
        std::vector<std::unique_ptr<T>> _data{};

    protected:
        TSystemData() = delete;
        TSystemData(const std::string& token) : SystemData(token) {};

    public:
        ~TSystemData() override = default;

        T& GetData(size_t pos) {
            if (pos >= _data.size()) {
                Logger::LogError("Data index out of bounds: " + std::string(__FILE__) + ":" + std::to_string(__LINE__));
            }
            return *_data[pos];
        }
        const std::vector<std::unique_ptr<T>>& GetAllData() {
            return _data;
        }

        bool DestroyData(size_t pos) {
            if (pos >= _data.size()) {
                Logger::LogError("Data index out of bounds: " + std::string(__FILE__) + ":" + std::to_string(__LINE__));
                return false;
            }

            _data.erase(_data.begin() + pos);
            Logger::LogInfo("Data was destroyed");
            return true;
        }
        bool DestroyData(T* ptr) {
            if (ptr == nullptr) {
                Logger::LogError("Data is nullptr: " + std::string(__FILE__) + ":" + std::to_string(__LINE__));
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

            Logger::LogError("Data does not exist: " + std::string(__FILE__) + ":" + std::to_string(__LINE__));
            return false;
        }

        TSystemData(const TSystemData&) = delete;
        TSystemData& operator=(const TSystemData&) = delete;
        TSystemData(TSystemData&&) = delete;
        TSystemData& operator=(TSystemData&&) = delete;
    };
}