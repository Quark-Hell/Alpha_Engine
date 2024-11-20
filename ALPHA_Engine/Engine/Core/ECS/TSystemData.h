#pragma once

#include <vector>
#include <memory>
#include "Core/ECS/SystemData.h"

namespace Core {
    template<typename T>
    class TSystemData : public SystemData { //<T, std::enable_if_t<std::is_convertible_v<Core::Component, T>>> {
    protected:
        std::vector<std::unique_ptr<T>> _data{};

    protected:
        TSystemData() = delete;
        TSystemData(const std::string& token) : SystemData(token) {};

    public:
        virtual ~TSystemData() = default;

        virtual T& GetData(size_t pos) = 0;
        virtual const std::vector<std::unique_ptr<T>>& GetAllData() = 0;

        virtual bool DestroyData(size_t pos) = 0;
        virtual bool DestroyData(T* ptr) = 0;

        TSystemData(const TSystemData&) = delete;
        TSystemData& operator=(const TSystemData&) = delete;
        TSystemData(TSystemData&&) = delete;
        TSystemData& operator=(TSystemData&&) = delete;
    };
}