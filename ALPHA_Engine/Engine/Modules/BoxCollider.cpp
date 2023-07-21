#include "BoxCollider.h"

BoxCollider::BoxCollider(float height, float width, float length) : ColliderPresets::ColliderPresets(72) {
	BoxCollider::_height = height;
	BoxCollider::_width = width;
	BoxCollider::_lenght = length;

	BoxCollider::_vertex = new float[BoxCollider::_vertexCount];

	BoxCollider::CreateMeshModel();
}
BoxCollider::~BoxCollider() {

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
	//Front face
	BoxCollider::_vertex[0] = -0.5f;
	BoxCollider::_vertex[1] = -0.5f;
	BoxCollider::_vertex[2] = 0.5f;

	BoxCollider::_vertex[3] = 0.5f;
	BoxCollider::_vertex[4] = -0.5f;
	BoxCollider::_vertex[5] = 0.5f;

	BoxCollider::_vertex[6] = 0.5f;
	BoxCollider::_vertex[7] = 0.5f;
	BoxCollider::_vertex[8] = 0.5f;

	BoxCollider::_vertex[9] = -0.5f;
	BoxCollider::_vertex[10] = 0.5f;
	BoxCollider::_vertex[11] = 0.5f;

	//Back face
	BoxCollider::_vertex[12] = -0.5f;
	BoxCollider::_vertex[13] = -0.5f;
	BoxCollider::_vertex[14] = -0.5f;

	BoxCollider::_vertex[15] = 0.5f;
	BoxCollider::_vertex[16] = -0.5f;
	BoxCollider::_vertex[17] = -0.5f;

	BoxCollider::_vertex[18] = 0.5f;
	BoxCollider::_vertex[19] = 0.5f;
	BoxCollider::_vertex[20] = -0.5f;

	BoxCollider::_vertex[21] = -0.5f;
	BoxCollider::_vertex[22] = 0.5f;
	BoxCollider::_vertex[23] = -0.5f;

	//Left face
	BoxCollider::_vertex[24] = -0.5f;
	BoxCollider::_vertex[25] = -0.5f;
	BoxCollider::_vertex[26] = -0.5f;

	BoxCollider::_vertex[27] = -0.5f;
	BoxCollider::_vertex[28] = -0.5f;
	BoxCollider::_vertex[29] = 0.5f;

	BoxCollider::_vertex[30] = -0.5f;
	BoxCollider::_vertex[31] = 0.5f;
	BoxCollider::_vertex[32] = 0.5f;

	BoxCollider::_vertex[33] = -0.5f;
	BoxCollider::_vertex[34] = 0.5f;
	BoxCollider::_vertex[35] = -0.5f;

	//Right face
	BoxCollider::_vertex[36] = 0.5f;
	BoxCollider::_vertex[37] = -0.5f;
	BoxCollider::_vertex[38] = -0.5f;

	BoxCollider::_vertex[39] = 0.5f;
	BoxCollider::_vertex[40] = -0.5f;
	BoxCollider::_vertex[41] = 0.5f;

	BoxCollider::_vertex[42] = 0.5f;
	BoxCollider::_vertex[43] = 0.5f;
	BoxCollider::_vertex[44] = 0.5f;

	BoxCollider::_vertex[45] = 0.5f;
	BoxCollider::_vertex[46] = 0.5f;
	BoxCollider::_vertex[47] = -0.5f;

	//Top face
	BoxCollider::_vertex[48] = -0.5f;
	BoxCollider::_vertex[49] = 0.5f;
	BoxCollider::_vertex[50] = -0.5f;

	BoxCollider::_vertex[51] = 0.5f;
	BoxCollider::_vertex[52] = 0.5f;
	BoxCollider::_vertex[53] = -0.5f;

	BoxCollider::_vertex[54] = 0.5f;
	BoxCollider::_vertex[55] = 0.5f;
	BoxCollider::_vertex[56] = 0.5f;

	BoxCollider::_vertex[57] = -0.5f;
	BoxCollider::_vertex[58] = 0.5f;
	BoxCollider::_vertex[59] = 0.5f;

	//Bottom face
	BoxCollider::_vertex[60] = -0.5f;
	BoxCollider::_vertex[61] = -0.5f;
	BoxCollider::_vertex[62] = -0.5f;

	BoxCollider::_vertex[63] = 0.5f;
	BoxCollider::_vertex[64] = -0.5f;
	BoxCollider::_vertex[65] = -0.5f;

	BoxCollider::_vertex[66] = 0.5f;
	BoxCollider::_vertex[67] = -0.5f;
	BoxCollider::_vertex[68] = 0.5f;

	BoxCollider::_vertex[69] = -0.5f;
	BoxCollider::_vertex[70] = -0.5f;
	BoxCollider::_vertex[71] = 0.5f;
}