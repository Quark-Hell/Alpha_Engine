// ALPHA_Engine.cpp : Defines the entry point for the application.
#include "Core/World.h"
#include "Core/Logger/Logger.h"

int main(int argc, char** argv) {
	Core::Logger::LogInfo("Engine integrated successfully");
	auto worldInstance = Core::World::GetWorld();
	Core::Logger::LogInfo("World created");

	worldInstance->Simulation();

	return 0;
}
