#include "World.h"
#include <cassert>
#include <memory>
#include "Host/Host.h"
#include "EngineConfig.h"

Core::World::World() {
	_host = Core::Host::MakeHost();
}
Core::World::~World() = default;

#pragma region ObjectManager
#include "Core/Object.h"
std::list<std::unique_ptr<Core::Object>>* Core::World::GetObjects() {
	static std::list<std::unique_ptr<Core::Object>> objects{};
	return &objects;
}

bool Core::World::RemoveObject(const Core::Object* object) {
	const auto list = GetObjects();
	auto it = std::begin(*list);

	for (size_t i = 0; i < GetObjects()->size(); ++i) {
		if (it->get() == &object[i]) {
			std::cout << "Removing object " << std::endl;
			GetObjects()->erase(it);
			std::cout << "Removed object " << std::endl;
			return true;
		}
		std::advance(it, 1);
	}

	assert("Object cannot be removed");
	return false;
}

Core::Object& Core::World::CreateObject() {
	GetObjects()->push_back(std::unique_ptr<Core::Object>(new Core::Object()));
	return *World::GetObjects()->back().get();
}
#pragma endregion

#pragma region UserScriptManager
#if USER_SCRIPTS_REGISTER_INCLUDED
std::list<std::unique_ptr<Register::UserScript>>* Core::World::GetUserScripts() {
	static std::list<std::unique_ptr<Register::UserScript>> userScripts{};
	return &userScripts;
}

bool Core::World::RemoveUserScript(const Register::UserScript* script) {
	const auto list = GetUserScripts();
	auto it = std::begin(*list);

	for (size_t i = 0; i < GetObjects()->size(); ++i) {
		if (it->get() == &script[i]) {
			std::cout << "Removing user script" << std::endl;
			GetUserScripts()->erase(it);
			std::cout << "Removed user script" << std::endl;
			return true;
		}
		std::advance(it, 1);
	}

	assert("User script cannot be removed");
	return false;
}
Register::UserScript& Core::World::CreateUserScript() {
	GetUserScripts()->push_back(std::unique_ptr<Register::UserScript>(new Register::UserScript()));
	return *World::GetUserScripts()->back().get();
}

Register::UserScript* Core::World::CreateUserScript(Register::UserScript* script) {
	const auto list = GetUserScripts();
	auto it = std::begin(*list);

	for (size_t i = 0; i < GetObjects()->size(); ++i) {
		if (it->get() == &script[i]) {
			assert("User script already exist");
		}
		std::advance(it, 1);
	}

	GetUserScripts()->push_back(std::unique_ptr<Register::UserScript>(script));
	return World::GetUserScripts()->back().get();
}

#endif
#pragma endregion

#pragma region WorldFunctions
Core::World& Core::World::GetWorld() {
	return *new Core::World();
}

void Core::World::CloseGame() {
	IsCloseGame = true;
}

bool Core::World::GetStateOfGame() const {
	return IsCloseGame;
}

double Core::World::GetTimeLong() const {
	return World::_timeLong;
}
float Core::World::GetDeltaTime() const {
	return World::_deltaTime;
}

void Core::World::StartFrame() {
	//World::_startTime = std::chrono::high_resolution_clock::now();
}
void Core::World::EndFrame() {
	//World::_endTime = std::chrono::high_resolution_clock::now();
	//What? Why i should mult this by 0.000001f?
	//World::_deltaTime = std::chrono::duration_cast	<std::chrono::microseconds>(World::_endTime - World::_startTime).count() * 0.000001f;
	//World::_timeLong += World::_deltaTime;
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
#ifdef USER_SCRIPTS_REGISTER_INCLUDED
		_host->Registry(GetUserScripts());
#endif
		_host->Graphics();

		//_host->Physics();
	}
}
#pragma endregion
