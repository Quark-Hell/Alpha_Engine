#include "Timer.h"

#include <iostream>

namespace Core {
    Timer::Timer() {
      Reset();
    }

    void Timer::Reset() {
      _start = std::chrono::high_resolution_clock::now();
    }

    float Timer::Elapsed() const {
      return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - _start).count() * 0.001f * 0.001f;
    }

    float Timer::ElapsedMillis() const {
      return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - _start).count() * 0.001f;
    }


    ScopedTimer::ScopedTimer(std::string_view name) : _name(name) {}

    ScopedTimer::~ScopedTimer()
    {
      float time = _timer.ElapsedMillis();
      std::cout << _name << " - " << time << "ms" << std::endl;
    }
}