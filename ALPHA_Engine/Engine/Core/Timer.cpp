#include "Timer.h"

#include "Logger/Logger.h"

namespace Core {
    Timer::Timer() {
      Reset();
    }

    void Timer::Reset() {
      _start = std::chrono::high_resolution_clock::now();
    }

    double Timer::Elapsed() const {
      return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - _start).count() * 0.001f * 0.001f;
    }

    double Timer::ElapsedMillis() const {
      return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - _start).count() * 0.001f;
    }


    ScopedTimer::ScopedTimer(const std::string_view name) : _name(name) {}

    ScopedTimer::~ScopedTimer()
    {
      const float time = _timer.ElapsedMillis();
      Logger::Logger::LogInfo(_name, " - ", time, "ms");
    }
}