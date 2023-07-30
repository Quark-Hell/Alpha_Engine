#include "BoxCollider.h"
#include "Object.h"

BoxCollider::BoxCollider(float height, float width, float length) {
	BoxCollider::_height = height;
	BoxCollider::_width = width;
	BoxCollider::_lenght = length;

	BoxCollider::_vertex = new float[BoxCollider::_vertexCount];

	BoxCollider::InitCollider(false);
	//TODO: Work only if debug build
	BoxCollider::Create("\\Models\\Primitives\\Cube.fbx");


}
BoxCollider::~BoxCollider() {

}

void BoxCollider::InitCollider(bool isExpand) {
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

	if (isExpand) {

	}
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