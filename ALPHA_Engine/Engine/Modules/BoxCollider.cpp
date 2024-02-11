#include "BoxCollider.h"
#include "Object.h"
#include "Modules/MeshCollider.h"
#include "Modules/Collider.h"
#include "Modules/Geometry.h"

BoxCollider::BoxCollider() {
	MeshCollider::Create("\\Models\\Primitives\\Cube.fbx");
	BoxCollider::SetScale(Vector3{ 1,1,1 });
	AABB::UpdateAABB(Geometry::_vertex, Geometry::_vertexCount);
}

BoxCollider::~BoxCollider() {

}

void BoxCollider::SetParentObject(const Object& parent) {
	BoxCollider::ApplyTransformation();
	ParentObject = const_cast<Object*>(&parent);
#ifdef _DEBUG
	BoxCollider::_debugMesh->SetParentObject(*MeshCollider::ParentObject);
#endif
	BoxCollider::ReExpandedCollider();
}

void BoxCollider::ReExpandedCollider() {
	BoxCollider::ApplyTransformation();
	BoxCollider::SetRotation(BoxCollider::GetParentObject()->GetRotation());
	BoxCollider::SetScale(BoxCollider::CalculateCoverScale());
}

void BoxCollider::InitCollider() {
	Geometry::_vertex = new float[24];
	Geometry::_vertexCount = 8;

	//front side
	Geometry::_vertex[0] = -0.5f;
	Geometry::_vertex[1] = -0.5f;
	Geometry::_vertex[2] = 0.5f;

	Geometry::_vertex[3] = -0.5f;
	Geometry::_vertex[4] = 0.5f;
	Geometry::_vertex[5] = 0.5f;

	Geometry::_vertex[6] = 0.5f;
	Geometry::_vertex[7] = 0.5f;
	Geometry::_vertex[8] = 0.5f;

	Geometry::_vertex[9] = 0.5f;
	Geometry::_vertex[10] = -0.5f;
	Geometry::_vertex[11] = 0.5f;

	//back side
	Geometry::_vertex[12] = -0.5f;
	Geometry::_vertex[13] = -0.5f;
	Geometry::_vertex[14] = -0.5f;

	Geometry::_vertex[15] = -0.5f;
	Geometry::_vertex[16] = 0.5f;
	Geometry::_vertex[17] = -0.5f;

	Geometry::_vertex[18] = 0.5f;
	Geometry::_vertex[19] = 0.5f;
	Geometry::_vertex[20] = -0.5f;

	Geometry::_vertex[21] = 0.5f;
	Geometry::_vertex[22] = -0.5f;
	Geometry::_vertex[23] = -0.5f;
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

ModulesList BoxCollider::GetType() {
	return::BoxColliderType;
}