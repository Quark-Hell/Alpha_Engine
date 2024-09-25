#include "World.h"

#include "ModuleList.h"
#include "Core/Host/Host.h"

Core::World::World() {
	_host = Core::Host::MakeHost();
}
Core::World::~World() {

}

void Core::World::CloseGame() {
	IsCloseGame = true;
}

bool Core::World::GetStateOfGame() {
	return IsCloseGame;
}

double Core::World::GetTimeLong() {
	return World::_timeLong;
}
float Core::World::GetDeltaTime() {
	return World::_deltaTime;
}

void Core::World::StartFrame() {
	World::_startTime = std::chrono::high_resolution_clock::now();
}
void Core::World::EndFrame() {
	World::_endTime = std::chrono::high_resolution_clock::now();
	//What? Why i should mult this by 0.000001f?
	World::_deltaTime = std::chrono::duration_cast	<std::chrono::microseconds>(World::_endTime - World::_startTime).count() * 0.000001f;
	World::_timeLong += World::_deltaTime;
}

void Core::World::SetSimulationSpeed(float simSpeed) {
	if (simSpeed < 0) {
		World::SimulationSpeed = simSpeed;
	}
}


void Core::World::Simulation() {
#if __has_include("Graphics_Engine/GraphicsEngineConfig.h")
	//_host->StartRender();
#endif

//	while (IsCloseGame)
//	{
//#if __has_include("Graphics_Engine/GraphicsEngineConfig.h")
//		//_host->Graphics();
//#endif
//		//_host->Physics();
//	}
}
