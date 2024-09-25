// ALPHA_Engine.cpp : Defines the entry point for the application.
//
#include "ALPHA_Engine.h"
#include "Core/World.h"

void GameFunction::Start() {

}

void GameFunction::Update() {

}

int main()
{
    std::unique_ptr<Core::World> world = std::make_unique<Core::World>();
    world->Simulation();

    std::cout << "Hello World";
}
