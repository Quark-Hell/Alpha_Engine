#include "Timer.h"

#include "World.h"

float Timer::GetDelay() {
	return Timer::_delay;
}
float Timer::GetElapsed() {
	return Timer::_elapsed;
}

void Timer::StartTimer() {
	Timer::_timerState = TimerState::Activate;
}
void Timer::RestartTimer() {
	Timer::_elapsed = Timer::_delay;
	Timer::_timerState = TimerState::OnStart;
}

void Timer::SetDelay(float newDelay) {
	Timer::_delay = newDelay;
	Timer::_timerState = TimerState::OnStart;
	Timer::RestartTimer();
}

void Timer::PauseTimer() {
	Timer::_timerState = TimerState::OnPause;
}

bool Timer::IsLeft() {
	if (!(Timer::_timerState == TimerState::OnEnd)) { return true; }
	return false;
}

void Timer::TimerLogic() {
	if (!(Timer::_timerState == TimerState::Activate)) { return; }
	if (!(Timer::_elapsed - World::GetDeltaTime() < 0)) { Timer::_timerState = TimerState::OnEnd; return; }

	Timer::_elapsed -= World::GetDeltaTime();
}