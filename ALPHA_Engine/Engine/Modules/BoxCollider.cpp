#include "BoxCollider.h"
#include "Object.h"
#include "Modules/Mesh.h"

BoxCollider::BoxCollider() {
	BoxCollider::_vertex = new float[BoxCollider::_vertexCount];

	BoxCollider::InitCollider();
	BoxCollider::SetScale(Vector3{ 1,1,1 });
	//TODO: Work only if debug build
	BoxCollider::Create("\\Models\\Primitives\\Cube.fbx");
}

BoxCollider::~BoxCollider() {

}

void BoxCollider::ReExpandedCollider() {
	BoxCollider::SetRotation(BoxCollider::GetParentObject()->GetRotation());
	BoxCollider::SetScale(BoxCollider::CalculateCoverScale());
}

void BoxCollider::InitCollider() {
	//front side
	BoxCollider::_points[0] = -0.5f;
	BoxCollider::_points[1] = -0.5f;
	BoxCollider::_points[2] = 0.5f;

	BoxCollider::_points[3] = -0.5f;
	BoxCollider::_points[4] = 0.5f;
	BoxCollider::_points[5] = 0.5f;

	BoxCollider::_points[6] = 0.5f;
	BoxCollider::_points[7] = 0.5f;
	BoxCollider::_points[8] = 0.5f;

	BoxCollider::_points[9] = 0.5f;
	BoxCollider::_points[10] = -0.5f;
	BoxCollider::_points[11] = 0.5f;

	//back side
	BoxCollider::_points[12] = -0.5f;
	BoxCollider::_points[13] = -0.5f;
	BoxCollider::_points[14] = -0.5f;

	BoxCollider::_points[15] = -0.5f;
	BoxCollider::_points[16] = 0.5f;
	BoxCollider::_points[17] = -0.5f;

	BoxCollider::_points[18] = 0.5f;
	BoxCollider::_points[19] = 0.5f;
	BoxCollider::_points[20] = -0.5f;

	BoxCollider::_points[21] = 0.5f;
	BoxCollider::_points[22] = -0.5f;
	BoxCollider::_points[23] = -0.5f;
}
Vector3 BoxCollider::CalculateCoverScale() {
	//std::vector<std::shared_ptr<Module>> buffer = BoxCollider::GetParentObject()->GetModuleByTypes({ MeshType });
	Vector3 maxSize(0, 0, 0);
	//
	//for (size_t i = 0; i < buffer.size(); i++) {
	//	Vector3 currentScale = std::dynamic_pointer_cast<Mesh>(buffer[i])->GetScale();
	//	if (maxSize.X < currentScale.X)
	//		maxSize.X = currentScale.X;
	//
	//	if (maxSize.Y < currentScale.Y)
	//		maxSize.Y = currentScale.Y;
	//
	//	if (maxSize.Z < currentScale.Z)
	//		maxSize.Z = currentScale.Z;
	//}
	if (maxSize.X < BoxCollider::GetParentObject()->GetScale().X)
		maxSize.X = BoxCollider::GetParentObject()->GetScale().X;

	if (maxSize.Y < BoxCollider::GetParentObject()->GetScale().Y)
		maxSize.Y = BoxCollider::GetParentObject()->GetScale().Y;

	if (maxSize.Z < BoxCollider::GetParentObject()->GetScale().Z)
		maxSize.Z = BoxCollider::GetParentObject()->GetScale().Z;

	return maxSize;
}

Vector3 BoxCollider::FindFurthestPoint(Vector3 direction) {
	Vector3 maxPoint = { 0,0,0 };
	float maxDistance = -FLT_MAX;
	Vector3 vertexPos = { 0,0,0 };

	for (size_t it = 0; it < 24; it += 3) {

		vertexPos.X = BoxCollider::_points[it];
		vertexPos.Y = BoxCollider::_points[it + 1];
		vertexPos.Z = BoxCollider::_points[it + 2];

		float distance = Vector3::DotProduct(vertexPos, direction);
		if (distance > maxDistance) {
			maxDistance = distance;
			maxPoint = vertexPos;
		}
	}

	return maxPoint + BoxCollider::_position + BoxCollider::GetParentObject()->GetPosition();
}

void BoxCollider::ApplyTransformation() {
	for (size_t jt = 0; jt < BoxCollider::_vertexCount * 3; jt += 3)
	{
		glm::vec4 buf(BoxCollider::_vertex[jt], BoxCollider::_vertex[jt + 1], BoxCollider::_vertex[jt + 2], 1);

		glm::vec4 res;
		res = BoxCollider::_transformMatrix * buf;
		BoxCollider::_vertex[jt] = res.x;
		BoxCollider::_vertex[jt + 1] = res.y;
		BoxCollider::_vertex[jt + 2] = res.z;
	}

	for (size_t jt = 0; jt < 24; jt += 3)
	{
		glm::vec4 buf(BoxCollider::_points[jt], BoxCollider::_points[jt + 1], BoxCollider::_points[jt + 2], 1);

		glm::vec4 res;
		res = BoxCollider::_transformMatrix * buf;
		BoxCollider::_points[jt] = res.x;
		BoxCollider::_points[jt + 1] = res.y;
		BoxCollider::_points[jt + 2] = res.z;
	}

	BoxCollider::_transformMatrix = glm::mat4x4(1.0f);
}

ModulesList BoxCollider::GetType() {
	return::BoxColliderType;
}