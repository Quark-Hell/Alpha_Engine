// ALPHA_Engine.cpp : Defines the entry point for the application.
#include "Core/World.h"

int main(int argc, char** argv) {
	std::cout << "Engine integrated successfully" << std::endl;
	auto worldInstance = Core::World::GetWorld();

	worldInstance->Simulation();

	return 0;
}
