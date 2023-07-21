#include "BoxCollider.h"

BoxCollider::BoxCollider(float height, float width, float length) {
	BoxCollider::_height = height;
	BoxCollider::_width = width;
	BoxCollider::_lenght = length;

	BoxCollider::_vertex = new float[BoxCollider::_vertexCount];

	BoxCollider::CreateMeshModel();
}
BoxCollider::~BoxCollider() {

}

ModulesList BoxCollider::GetType() {
	return::BoxColliderType;
}


float BoxCollider::GetHeight() {
	return BoxCollider::_height;
}
void BoxCollider::SetHeight(float heigth) {
	float delta = BoxCollider::_height / heigth;

	BoxCollider::_height = heigth;
	BoxCollider::_transformMatrix = glm::scale(BoxCollider::_transformMatrix, glm::vec3(1, 1 / delta, 1));

	BoxCollider::ApplyTransformation();
}

float BoxCollider::GetWidth() {
	return BoxCollider::_width;
}
void BoxCollider::SetWidth(float width) {
	float delta = BoxCollider::_width / width;

	BoxCollider::_width = width;
	BoxCollider::_transformMatrix = glm::scale(BoxCollider::_transformMatrix, glm::vec3(1, 1, 1 / delta));

	BoxCollider::ApplyTransformation();
}

float BoxCollider::GetLength() {
	return BoxCollider::_lenght;
}
void BoxCollider::SetLength(float length) {
	float delta = BoxCollider::_lenght / length;

	BoxCollider::_lenght = length;
	BoxCollider::_transformMatrix = glm::scale(BoxCollider::_transformMatrix, glm::vec3(1 / delta, 1, 1));

	BoxCollider::ApplyTransformation();
}

void BoxCollider::CreateMeshModel() {
	BoxCollider::Create("\\Models\\Primitives\\Cube.fbx", true, false);
}