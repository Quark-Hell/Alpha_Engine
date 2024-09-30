// ALPHA_Engine.cpp : Defines the entry point for the application.
//
//#include "ALPHA_Engine.h"
//#include "Core/World.h"
//#include "BaseConfig.h"


#ifdef ALPHA_Engine
#include <iostream>
#include "Engine/Core/World.h"

int main(int argc, char** argv) {
	std::cout << "Engine integrated successfully";
	std::unique_ptr<Core::World> worldInstance = Core::World::MakeWorld();

	worldInstance->Simulation();

	return 0;
}
#endif
