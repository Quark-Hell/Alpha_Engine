// ALPHA_Engine.cpp : Defines the entry point for the application.
#include "Core/World.h"
#include "Logger/Logger.h"

int main(int argc, char** argv) {
	Logger::Logger::LogInfo("Engine integrated successfully");
	auto worldInstance = Core::World::GetWorld();
	Logger::Logger::LogInfo("World created");

	worldInstance->Simulation();

	return 0;
}
