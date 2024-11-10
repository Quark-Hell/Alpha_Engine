#pragma once

#include <chrono>
#include <string>

namespace Core {

    class Timer
    {
    public:
        Timer();
        void Reset();
        [[nodiscard]] float Elapsed() const;
        [[nodiscard]] float ElapsedMillis() const;
    private:
        std::chrono::time_point<std::chrono::high_resolution_clock> _start;
    };

    class ScopedTimer
    {
    private:
        Timer _timer;
        std::string _name;

    public:
        ScopedTimer(std::string_view name);
        ~ScopedTimer();
    };

}