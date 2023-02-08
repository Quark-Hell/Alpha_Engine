#pragma once
#include "Basical_Type.h"

class Timer
{
	enum TimerState
	{
		OnStart = 0,
		Activate = 1,
		OnPause = 2,
		OnEnd = 3
	};

private:
	float _delay = 0;
	float _elapsed = 0;
	Timer::TimerState _timerState;

public:
	float GetDelay();
	float GetElapsed();
	
	void SetDelay(float newDelay);
	void StartTimer();
	void RestartTimer();
	void PauseTimer();

	bool IsLeft();

	Timer();	
	~Timer();


private:
	void TimerLogic();
};

Timer::Timer()
{
}

Timer::~Timer()
{
}