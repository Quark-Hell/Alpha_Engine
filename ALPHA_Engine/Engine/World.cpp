#include "World.h"

#include "Object.h"

inline World::World() {

}

inline void World::CloseGame() {
	IsCloseGame = true;
}

inline bool World::GetStateOfGame() {
	return IsCloseGame;
}

inline double World::GetTimeLong() {
	return World::_timeLong;
}
inline float World::GetDeltaTime() {
	return World::_deltaTime;
}

inline void World::StartFrame() {
	// Get starting timepoint
	World::_startTime = std::chrono::high_resolution_clock::now();
}
inline void World::EndFrame() {
	World::_endTime = std::chrono::high_resolution_clock::now();
	World::_deltaTime = std::chrono::duration_cast	<std::chrono::microseconds>(World::_endTime - World::_startTime).count() / 1000.0;
	World::_timeLong += World::_deltaTime;
}

inline void World::BuildTransformationThread(const std::vector<Object*> objects) {
	for (size_t it = 0; it < objects.size(); it++)
	{
		objects[it]->ApplyTransform();
	}
}

inline void World::ApplyingSceneTransformation() {
	const unsigned int bufferCapacity = 500000;

	std::vector<std::thread> threads;
	std::vector<std::vector<Object*>> objectsPool;
	objectsPool.resize(1);

	unsigned long heaviness = 0;

	for (size_t it = 0; it < World::ObjectsOnScene.size(); it++)
	{
		Object* obj = World::ObjectsOnScene[it];

		heaviness += obj->GetGeometryHeaviness();
		if (heaviness > bufferCapacity) {
			objectsPool[objectsPool.size() - 1].push_back(obj);
			objectsPool.resize(objectsPool.size() + 1);
			heaviness = 0;

			threads.push_back(std::thread(BuildTransformationThread, objectsPool[objectsPool.size() - 2]));
		}
		else if (heaviness > 0) {
			objectsPool[objectsPool.size() - 1].push_back(obj);
		}
	}
	//set last callable 
	if (heaviness > 0) {
		threads.push_back(std::thread(BuildTransformationThread, objectsPool[objectsPool.size() - 1]));
	}

	for (size_t it = 0; it < threads.size(); it++)
	{
		threads[it].join();
	}
}

inline void World::SetSimulationSpeed(float simSpeed) {
	if (simSpeed < 0) {
		World::SimulationSpeed = simSpeed;
	}
}