#include "World.h"
#include "GameModels.h"
//#include <Windows.h>
//#pragma comment(lib, "winmm.lib")

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
	//What? Why i should mult this by 0.000001f?
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
	//PlaySound("E:\\3D-Engine\\ALPHA_Engine\\EINS_ZWEI_POLIZEI.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);

	std::vector<std::shared_ptr<Node>> nodeBuffer;
	std::vector<std::shared_ptr<Leaf>> leavesBuffer;

	std::vector<Collider*> colliderBuffer;
	colliderBuffer.reserve(World::CollidersOnScene.size());
	colliderBuffer = { World::CollidersOnScene.begin(), World::CollidersOnScene.end() };


	while (colliderBuffer.size() != 0)
	{
		leavesBuffer.push_back(std::make_shared<Leaf>());

		leavesBuffer[leavesBuffer.size() - 1]->PushBack(colliderBuffer[colliderBuffer.size() - 1]);
		colliderBuffer.pop_back();

		World::FindNearestCollider(*leavesBuffer[leavesBuffer.size() - 1], colliderBuffer, 150);
	}

	while (leavesBuffer.size() != 0)
	{
		nodeBuffer.push_back(std::make_shared<Node>());

		nodeBuffer[nodeBuffer.size() - 1]->PushBack(leavesBuffer[leavesBuffer.size() - 1]);
		leavesBuffer.pop_back();

		World::CreateAABBvolume(*nodeBuffer[nodeBuffer.size() - 1], leavesBuffer);
	}

	//TODO: Does not work if nodeBuffer size bigger than 1
	while (nodeBuffer.size() > 1)
	{
		nodeBuffer.push_back(std::make_shared<Node>(true));

		nodeBuffer[nodeBuffer.size() - 1]->PushBack(nodeBuffer[leavesBuffer.size() - 1]);
		nodeBuffer.pop_back();

		//World::CreateAABBvolume(*nodeBuffer[nodeBuffer.size() - 1], leavesBuffer);
	}

	RootBVHnode = nodeBuffer[0];
}

void World::FindNearestCollider(Leaf& leafBuffer, std::vector<Collider*>& objectsBuffer, float maxDistance) {
	std::vector<std::pair<size_t, float>> distancesToObjects;
	distancesToObjects.reserve(objectsBuffer.size());
	
	Collider* colPtr = nullptr;
	leafBuffer.Get(&colPtr, 0);

	Vector3 basePos = colPtr->GetParentObject()->GetPosition() + colPtr->GetPosition();
	
	for (size_t i = 0; i < distancesToObjects.capacity(); i++) {
		if (objectsBuffer.size() <= i)
			break;

		distancesToObjects.push_back({ i,0 });
	
		Vector3 nextPos = objectsBuffer[i]->GetParentObject()->GetPosition() + objectsBuffer[i]->GetPosition();
		distancesToObjects[i].second = Vector3::GetNonSqrtMagnitude(basePos - nextPos);
	}
	
	size_t passedCount = 0;

	float minX = 0, minY = 0, minZ = 0;
	float maxX = 0, maxY = 0, maxZ = 0;

	colPtr->GetSize(minX, maxX, minY, maxY, minZ, maxZ);

	minX += basePos.X; minY += basePos.Y; minZ += basePos.Z;
	maxX += basePos.X; maxY += basePos.Y; maxZ += basePos.Z;

	for (size_t i = 0; i < leafBuffer.GetCapacity(); i++) {
		if (distancesToObjects.size() <= i) {
			leafBuffer.AABBvolume.SetSize(minX, maxX, minY, maxY, minZ, maxZ);
			return;
		}

		if (distancesToObjects[i].second > maxDistance)
			continue;
	
		leafBuffer.PushBack(objectsBuffer[distancesToObjects[i - passedCount].first]);
		objectsBuffer.erase(objectsBuffer.begin() + distancesToObjects[i - passedCount].first);
		passedCount++;

		//Building leaf AABB
		leafBuffer.Get(&colPtr, leafBuffer.GetSize() - 1);

		basePos = colPtr->GetParentObject()->GetPosition() + colPtr->GetPosition();

		//Min
		if (minX > colPtr->GetMinX() + basePos.X)
			minX = colPtr->GetMinX() + basePos.X;

		if (minY > colPtr->GetMinY() + basePos.Y)
			minY = colPtr->GetMinY() + basePos.Y;

		if (minZ > colPtr->GetMinZ() + basePos.Z)
			minZ = colPtr->GetMinZ() + basePos.Z;


		//Max
		if (maxX < colPtr->GetMaxX() + basePos.X)
			maxX = colPtr->GetMaxX() + basePos.X;

		if (maxY < colPtr->GetMaxY() + basePos.Y)
			maxY = colPtr->GetMaxY() + basePos.Y;

		if (maxZ < colPtr->GetMaxZ() + basePos.Z)
			maxZ = colPtr->GetMaxZ() + basePos.Z;
	}

	leafBuffer.AABBvolume.SetSize(minX, maxX, minY, maxY, minZ, maxZ);
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

	Leaf* leafPtr = nullptr;
	outputNode.Get(&leafPtr, 0);
	Vector3 basePos = leafPtr->AABBvolume.GetAABBPosition();

	float minX = 0, minY = 0, minZ = 0;
	float maxX = 0, maxY = 0, maxZ = 0;

	leafPtr->AABBvolume.GetSize(minX, maxX, minY, maxY, minZ, maxZ);

	if (leavesBuffer.size() == 0) {
		outputNode.AABBvolume.SetSize(minX, maxX, minY, maxY, minZ, maxZ);
		return;
	}

	for (size_t i = 0; i < distancesToLeaves.capacity(); i++) {
		if (leavesBuffer.size() <= i)
			break;

		distancesToLeaves.push_back({ i,0 });

		Vector3 nextPos = leavesBuffer[i]->AABBvolume.GetAABBPosition();
		distancesToLeaves[i].second = Vector3::GetNonSqrtMagnitude(basePos - nextPos);
	}

	std::sort(distancesToLeaves.begin(), distancesToLeaves.end(), compareDistance);

	for (size_t i = 0; i < outputNode.GetCapacity() && i < leavesBuffer.size(); i++) {
		basePos = leavesBuffer[i]->AABBvolume.GetAABBPosition();

		//Min
		if (minX > leavesBuffer[i]->AABBvolume.GetMinX())
			minX = leavesBuffer[i]->AABBvolume.GetMinX();

		if (minY > leavesBuffer[i]->AABBvolume.GetMinY())
			minY = leavesBuffer[i]->AABBvolume.GetMinY();

		if (minZ > leavesBuffer[i]->AABBvolume.GetMinZ())
			minZ = leavesBuffer[i]->AABBvolume.GetMinZ();


		//Max
		if (maxX < leavesBuffer[i]->AABBvolume.GetMaxX())
			maxX = leavesBuffer[i]->AABBvolume.GetMaxX();

		if (maxY < leavesBuffer[i]->AABBvolume.GetMaxY())
			maxY = leavesBuffer[i]->AABBvolume.GetMaxY();

		if (maxZ < leavesBuffer[i]->AABBvolume.GetMaxZ())
			maxZ = leavesBuffer[i]->AABBvolume.GetMaxZ();
	}

	outputNode.AABBvolume.SetSize(minX, maxX, minY, maxY, minZ, maxZ);
}

void World::Init()
{
	World::SkyBox = Primitives::Cube({ 0,0,0 }, Vector4(0, 0, 0, 1), Vector3(1, 1, 1));

	if (!SkyBox->ObjectTag.SetTag("SkyBox")) {
		std::cout << "Cannot set tag to SkyBox object";
		abort();
	}

	SkyBox->Name = "SkyBox";
}
