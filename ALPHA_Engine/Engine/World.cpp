#include "World.h"

World::World() {

}

void World::CloseGame() {
	IsCloseGame = true;
}

bool World::GetStateOfGame() {
	return IsCloseGame;
}

double World::GetTimeLong() {
	return World::_timeLong;
}
float World::GetDeltaTime() {
	return World::_deltaTime;
}

void World::StartFrame() {
	// Get starting timepoint
	World::_startTime = std::chrono::high_resolution_clock::now();
}
void World::EndFrame() {
	World::_endTime = std::chrono::high_resolution_clock::now();
	World::_deltaTime = std::chrono::duration_cast	<std::chrono::microseconds>(World::_endTime - World::_startTime).count() * 0.000001f;
	World::_timeLong += World::_deltaTime;
}

void World::BuildTransformationThread(const std::vector<Object*> objects) {
	for (size_t it = 0; it < objects.size(); it++)
	{
		objects[it]->ApplyTransformation();
	}
}

void World::ApplyingSceneTransformation() {
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

void World::SetSimulationSpeed(float simSpeed) {
	if (simSpeed < 0) {
		World::SimulationSpeed = simSpeed;
	}
}

void World::CreateWorldTree() {
	std::vector<std::shared_ptr<Node>> nodeBuffer;
	std::vector<std::shared_ptr<Leaf>> leavesBuffer;
	
	std::vector<Object*> objectBuffer; 
	objectBuffer.reserve(World::ObjectsOnScene.size());
	objectBuffer = { World::ObjectsOnScene.begin(), World::ObjectsOnScene.end() };
	
	while (objectBuffer.size() != 0)
	{
		leavesBuffer.push_back(std::make_shared<Leaf>());

		leavesBuffer[leavesBuffer.size() - 1]->objectsPtr.push_back(objectBuffer[objectBuffer.size() - 1]);
		objectBuffer.pop_back();
	
		World::FindNearestObject(*leavesBuffer[leavesBuffer.size() - 1], objectBuffer, 150);
	}

	while (leavesBuffer.size() != 0)
	{
		nodeBuffer.push_back(std::make_shared<Node>());

		nodeBuffer[nodeBuffer.size() - 1]->leavesPtr.push_back(leavesBuffer[leavesBuffer.size() - 1]);
		leavesBuffer.pop_back();

		World::CreateAABBvolume(*nodeBuffer[nodeBuffer.size() - 1], leavesBuffer);
	}
}

void World::FindNearestObject(Leaf& leafBuffer, std::vector<Object*>& objectsBuffer, float maxDistance) {
	std::vector<std::pair<size_t, float>> distancesToObjects;
	distancesToObjects.reserve(objectsBuffer.size());
	
	Vector3 basePos = leafBuffer.objectsPtr[0]->GetPosition();
	
	for (size_t i = 0; i < distancesToObjects.capacity(); i++) {
		if (objectsBuffer.size() <= i)
			break;

		distancesToObjects.push_back({ i,0 });
	
		Vector3 nextPos = objectsBuffer[i]->GetPosition();
		distancesToObjects[i].second = Vector3::GetNonSqrtMagnitude(basePos - nextPos);
	}
	
	
	size_t passedCount = 0;
	for (size_t i = 0; i < leafBuffer.objectsPtr.capacity(); i++) {
		if (distancesToObjects.size() <= i)
			return;
		if (distancesToObjects[i].second > maxDistance)
			continue;
	
		leafBuffer.objectsPtr.push_back(objectsBuffer[distancesToObjects[i - passedCount].first]);
		objectsBuffer.erase(objectsBuffer.begin() + distancesToObjects[i - passedCount].first);
		passedCount++;

		//Min
		if (leafBuffer.AABBvolume.MinX > leafBuffer.objectsPtr[leafBuffer.objectsPtr.size() - 1]->_aabbVolume.MinX)
			leafBuffer.AABBvolume.MinX = leafBuffer.objectsPtr[leafBuffer.objectsPtr.size() - 1]->_aabbVolume.MinX;

		if (leafBuffer.AABBvolume.MinY > leafBuffer.objectsPtr[leafBuffer.objectsPtr.size() - 1]->_aabbVolume.MinY)
			leafBuffer.AABBvolume.MinY = leafBuffer.objectsPtr[leafBuffer.objectsPtr.size() - 1]->_aabbVolume.MinY;

		if (leafBuffer.AABBvolume.MinZ > leafBuffer.objectsPtr[leafBuffer.objectsPtr.size() - 1]->_aabbVolume.MinZ)
			leafBuffer.AABBvolume.MinZ = leafBuffer.objectsPtr[leafBuffer.objectsPtr.size() - 1]->_aabbVolume.MinZ;


		//Max
		if (leafBuffer.AABBvolume.MaxX > leafBuffer.objectsPtr[leafBuffer.objectsPtr.size() - 1]->_aabbVolume.MaxX)
			leafBuffer.AABBvolume.MaxX = leafBuffer.objectsPtr[leafBuffer.objectsPtr.size() - 1]->_aabbVolume.MaxX;

		if (leafBuffer.AABBvolume.MaxY > leafBuffer.objectsPtr[leafBuffer.objectsPtr.size() - 1]->_aabbVolume.MaxY)
			leafBuffer.AABBvolume.MaxY = leafBuffer.objectsPtr[leafBuffer.objectsPtr.size() - 1]->_aabbVolume.MaxY;

		if (leafBuffer.AABBvolume.MaxZ > leafBuffer.objectsPtr[leafBuffer.objectsPtr.size() - 1]->_aabbVolume.MaxZ)
			leafBuffer.AABBvolume.MaxZ = leafBuffer.objectsPtr[leafBuffer.objectsPtr.size() - 1]->_aabbVolume.MaxZ;
	}


}

void World::CreateAABBvolume(Node& outputNode, std::vector<std::shared_ptr<Leaf>>& leavesBuffer) {

	auto compareDistance = [](const std::pair<size_t, float>& leaf1, const std::pair<size_t, float>& leaf2) {
		if (leaf1.second < leaf2.second) {
			return true;
		}
		return false;
	};

	std::vector<std::pair<size_t, float>> distancesToLeaves;
	distancesToLeaves.reserve(distancesToLeaves.size());

	Vector3 basePos = outputNode.leavesPtr[0]->GetPosition();

	//Min
	outputNode.AABBvolume.MinX = outputNode.leavesPtr[0]->AABBvolume.MinX;
	outputNode.AABBvolume.MinY = outputNode.leavesPtr[0]->AABBvolume.MinY;
	outputNode.AABBvolume.MinZ = outputNode.leavesPtr[0]->AABBvolume.MinZ;

	//Max
	outputNode.AABBvolume.MaxX = outputNode.leavesPtr[0]->AABBvolume.MaxX;
	outputNode.AABBvolume.MaxY = outputNode.leavesPtr[0]->AABBvolume.MaxY;
	outputNode.AABBvolume.MaxZ = outputNode.leavesPtr[0]->AABBvolume.MaxZ;

	if (leavesBuffer.size() == 0)
		return;

	for (size_t i = 0; i < distancesToLeaves.capacity(); i++) {
		if (leavesBuffer.size() <= i)
			break;

		distancesToLeaves.push_back({ i,0 });

		Vector3 nextPos = leavesBuffer[i]->GetPosition();
		distancesToLeaves[i].second = Vector3::GetNonSqrtMagnitude(basePos - nextPos);
	}

	std::sort(distancesToLeaves.begin(), distancesToLeaves.end(), compareDistance);

	for (size_t i = 0; i < outputNode.leavesPtr.capacity(); i++) {
		if (leavesBuffer.size() <= i)
			return;

		//Min
		if (outputNode.AABBvolume.MinX > leavesBuffer[i]->AABBvolume.MinX)
			outputNode.AABBvolume.MinX = leavesBuffer[i]->AABBvolume.MinX;

		if (outputNode.AABBvolume.MinY > leavesBuffer[i]->AABBvolume.MinY)
			outputNode.AABBvolume.MinY = leavesBuffer[i]->AABBvolume.MinY;

		if (outputNode.AABBvolume.MinZ > leavesBuffer[i]->AABBvolume.MinZ)
			outputNode.AABBvolume.MinZ = leavesBuffer[i]->AABBvolume.MinZ;


		//Max
		if (outputNode.AABBvolume.MaxX > leavesBuffer[i]->AABBvolume.MaxX)
			outputNode.AABBvolume.MaxX = leavesBuffer[i]->AABBvolume.MaxX;

		if (outputNode.AABBvolume.MaxY > leavesBuffer[i]->AABBvolume.MaxY)
			outputNode.AABBvolume.MaxY = leavesBuffer[i]->AABBvolume.MaxY;

		if (outputNode.AABBvolume.MaxZ > leavesBuffer[i]->AABBvolume.MaxZ)
			outputNode.AABBvolume.MaxZ = leavesBuffer[i]->AABBvolume.MaxZ;
	}
}