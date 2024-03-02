#include "BoxCollider.h"
#include "Object.h"
#include "Modules/MeshCollider.h"
#include "Modules/Collider.h"
#include "Modules/Geometry.h"

BoxCollider::BoxCollider() {
	MeshCollider::Create("\\Models\\Primitives\\Cube.fbx");
	BoxCollider::SetScale(Vector3{ 1,1,1 });
	//AABB::UpdateAABB(Geometry::_vertex, Geometry::_vertex->size() / 3);
}

BoxCollider::~BoxCollider() {

}

void BoxCollider::SetParentObject(const Object& parent) {
	BoxCollider::ApplyTransformation();
	ParentObject = const_cast<Object*>(&parent);

	BoxCollider::ReExpandedCollider();

#ifdef _DEBUG
	BoxCollider::_debugMesh->SetParentObject(*MeshCollider::ParentObject);
#endif
}

void BoxCollider::ReExpandedCollider() {
	MeshCollider::ApplyTransformation();
	Geometry::SetRotation(BoxCollider::GetParentObject()->GetRotation());
	Geometry::SetScale(BoxCollider::CalculateCoverScale());
	MeshCollider::InitTransformatiom(*ParentObject);
}

void BoxCollider::InitCollider() {
	Geometry::_vertex->resize(8 * 3);

	//front side
	(*Geometry::_vertex)[0] = -1;
	(*Geometry::_vertex)[1] = -1;
	(*Geometry::_vertex)[2] = 1;
					   
	(*Geometry::_vertex)[3] = -1;
	(*Geometry::_vertex)[4] = 1;
	(*Geometry::_vertex)[5] = 1;
					   
	(*Geometry::_vertex)[6] = 1;
	(*Geometry::_vertex)[7] = 1;
	(*Geometry::_vertex)[8] = 1;
					   
	(*Geometry::_vertex)[9] = 1;
	(*Geometry::_vertex)[10] = -1;
	(*Geometry::_vertex)[11] = 1;

	//back side
	(*Geometry::_vertex)[12] = -1;
	(*Geometry::_vertex)[13] = -1;
	(*Geometry::_vertex)[14] = -1;

	(*Geometry::_vertex)[15] = -1;
	(*Geometry::_vertex)[16] = 1;
	(*Geometry::_vertex)[17] = -1;

	(*Geometry::_vertex)[18] = 1;
	(*Geometry::_vertex)[19] = 1;
	(*Geometry::_vertex)[20] = -1;

	(*Geometry::_vertex)[21] = 1;
	(*Geometry::_vertex)[22] = -1;
	(*Geometry::_vertex)[23] = -1;



	////front side
	//(*Geometry::_vertex)[0] = -0.5f;
	//(*Geometry::_vertex)[1] = -0.5f;
	//(*Geometry::_vertex)[2] = 0.5f;
	//
	//(*Geometry::_vertex)[3] = -0.5f;
	//(*Geometry::_vertex)[4] = 0.5f;
	//(*Geometry::_vertex)[5] = 0.5f;
	//
	//(*Geometry::_vertex)[6] = 0.5f;
	//(*Geometry::_vertex)[7] = 0.5f;
	//(*Geometry::_vertex)[8] = 0.5f;
	//
	//(*Geometry::_vertex)[9] = 0.5f;
	//(*Geometry::_vertex)[10] = -0.5f;
	//(*Geometry::_vertex)[11] = 0.5f;
	//
	////back side
	//(*Geometry::_vertex)[12] = -0.5f;
	//(*Geometry::_vertex)[13] = -0.5f;
	//(*Geometry::_vertex)[14] = -0.5f;
	//
	//(*Geometry::_vertex)[15] = -0.5f;
	//(*Geometry::_vertex)[16] = 0.5f;
	//(*Geometry::_vertex)[17] = -0.5f;
	//
	//(*Geometry::_vertex)[18] = 0.5f;
	//(*Geometry::_vertex)[19] = 0.5f;
	//(*Geometry::_vertex)[20] = -0.5f;
	//
	//(*Geometry::_vertex)[21] = 0.5f;
	//(*Geometry::_vertex)[22] = -0.5f;
	//(*Geometry::_vertex)[23] = -0.5f;
}
Vector3 BoxCollider::CalculateCoverScale() {
	//std::vector<std::shared_ptr<Module>> buffer = BoxCollider::GetParentObject()->GetModuleByTypes({ MeshType });
	Vector3 maxSize(0, 0, 0);


	//
	//for (size_t i = 0; i < buffer.size(); i++) {
	//	float xp = std::dynamic_pointer_cast<Mesh>(buffer[i])->FindFurthestPoint(Vector3(1, 0, 0)).X - buffer[i]->GetParentObject()->GetPosition().X;
	//	float yp = std::dynamic_pointer_cast<Mesh>(buffer[i])->FindFurthestPoint(Vector3(0, 1, 0)).Y - buffer[i]->GetParentObject()->GetPosition().Y;
	//	float zp = std::dynamic_pointer_cast<Mesh>(buffer[i])->FindFurthestPoint(Vector3(0, 0, 1)).Z - buffer[i]->GetParentObject()->GetPosition().Z;
	//
	//	if (maxSize.X < xp)
	//		maxSize.X = xp;
	//
	//	if (maxSize.Y < yp)
	//		maxSize.Y = yp;
	//
	//	if (maxSize.Z < zp)
	//		maxSize.Z = zp;
	//}
	if (maxSize.X < BoxCollider::GetParentObject()->GetScale().X)
		maxSize.X = BoxCollider::GetParentObject()->GetScale().X;
	
	if (maxSize.Y < BoxCollider::GetParentObject()->GetScale().Y)
		maxSize.Y = BoxCollider::GetParentObject()->GetScale().Y;
	
	if (maxSize.Z < BoxCollider::GetParentObject()->GetScale().Z)
		maxSize.Z = BoxCollider::GetParentObject()->GetScale().Z;

	//glm::mat4x4 scaleMat = glm::mat4x4(1.0f);
	//BoxCollider::_transformMatrix = glm::scale(scaleMat, glm::vec3(maxSize.X * 2, maxSize.Y * 2, maxSize.Z * 2));

#ifdef _DEBUG
	BoxCollider::_debugMesh->ApplyTransformation();
#endif



	return maxSize;
}

ModulesList BoxCollider::GetType() {
	return::BoxColliderType;
}