#include "ColliderPresets.h"

ColliderPresets::ColliderPresets() {

}
ColliderPresets::~ColliderPresets() {

}

Vector3 ColliderPresets::GetPosition() {
	return ColliderPresets::_position;
}
void ColliderPresets::SetPosition(Vector3 newPosition) {
	ColliderPresets::_position = newPosition;
}

void ColliderPresets::CreateMeshModel() {

}

void ColliderPresets::ApplyTransformation() {
	for (size_t it = 0; it < ColliderPresets::_vertexCount * 3; it += 3)
	{
		glm::vec4 buf(ColliderPresets::_vertex[it], ColliderPresets::_vertex[it + 1], ColliderPresets::_vertex[it + 2], 1);

		glm::vec4 res;
		res = ColliderPresets::_transformMatrix * buf;
		ColliderPresets::_vertex[it] = res.x;
		ColliderPresets::_vertex[it + 1] = res.y;
		ColliderPresets::_vertex[it + 2] = res.z;
	}

	ColliderPresets::_transformMatrix = glm::mat4x4(1.0f);
}