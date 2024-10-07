// ALPHA_Engine.cpp : Defines the entry point for the application.
//
//#include "ALPHA_Engine.h"
//#include "Core/World.h"
//#include "BaseConfig.h"

#include "Core/World.h"

int main(int argc, char** argv) {
	std::cout << "Engine integrated successfully";
	Core::World& worldInstance = Core::World::GetWorld();

	worldInstance.Simulation();

	return 0;
}
