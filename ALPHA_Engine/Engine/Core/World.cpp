#include "World.h"
#include "Host/Host.h"
#include "Core/Object.h"

Core::World::World() {
	_host = Core::Host::MakeHost();
}
Core::World::~World() {

}

std::list<std::shared_ptr<Core::Object>>& Core::World::GetObjects() {
	static std::list<std::shared_ptr<Core::Object>> objects{};
	return objects;
}

std::unique_ptr<Core::World> Core::World::MakeWorld() {
	return std::unique_ptr<Core::World>(new Core::World());
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
	_host->StartRender();

	while (IsCloseGame)
	{
		_host->Regestry();
		_host->Graphics();

//		//_host->Physics();
	}
}
