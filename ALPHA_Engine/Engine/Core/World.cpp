#include "World.h"



World::World() {
	_host = Host::MakeHost();
}

void World::CloseGame() {
	IsCloseGame = true;
}

bool World::GetStateOfGame() {
	return IsCloseGame;
}

double World::GetTimeLong() {
	return World::_timeLong;
}
float World::GetDeltaTime() {
	return World::_deltaTime;
}

void World::StartFrame() {
	World::_startTime = std::chrono::high_resolution_clock::now();
}
void World::EndFrame() {
	World::_endTime = std::chrono::high_resolution_clock::now();
	//What? Why i should mult this by 0.000001f?
	World::_deltaTime = std::chrono::duration_cast	<std::chrono::microseconds>(World::_endTime - World::_startTime).count() * 0.000001f;
	World::_timeLong += World::_deltaTime;
}

void World::SetSimulationSpeed(float simSpeed) {
	if (simSpeed < 0) {
		World::SimulationSpeed = simSpeed;
	}
}


void World::Simulation() {
#if __has_include("Graphics_Engine/GraphicsEngineConfig.h")
	_host->StartRender();
#endif

	while (IsCloseGame)
	{
#if __has_include("Graphics_Engine/GraphicsEngineConfig.h")
		_host->Graphics();
#endif
		_host->Physics();
	}
}
