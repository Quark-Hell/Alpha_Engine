#include "Timer.h"

#include "World.h"

inline float Timer::GetDelay() {
	return Timer::_delay;
}
inline float Timer::GetElapsed() {
	return Timer::_elapsed;
}

inline void Timer::StartTimer() {
	Timer::_timerState = TimerState::Activate;
}
inline void Timer::RestartTimer() {
	Timer::_elapsed = Timer::_delay;
	Timer::_timerState = TimerState::OnStart;
}

inline void Timer::SetDelay(float newDelay) {
	Timer::_delay = newDelay;
	Timer::_timerState = TimerState::OnStart;
	Timer::RestartTimer();
}

inline void Timer::PauseTimer() {
	Timer::_timerState = TimerState::OnPause;
}

inline bool Timer::IsLeft() {
	if (!(Timer::_timerState == TimerState::OnEnd)) { return true; }
	return false;
}

inline void Timer::TimerLogic() {
	if (!(Timer::_timerState == TimerState::Activate)) { return; }
	if (!(Timer::_elapsed - World::GetDeltaTime() < 0)) { Timer::_timerState = TimerState::OnEnd; return; }

	Timer::_elapsed -= World::GetDeltaTime();
}