#include "Matrix.h"

#include "Vectors.h"

#pragma region Matrix3x3

Matrix3x3::Matrix3x3() {
	Matrix3x3::Identity();
}

void Matrix3x3::operator=(const Matrix3x3& matrix3x3)
{
	Matrix3x3::_matrix[0][0] = matrix3x3._matrix[0][0];
	Matrix3x3::_matrix[0][1] = matrix3x3._matrix[0][1];
	Matrix3x3::_matrix[0][2] = matrix3x3._matrix[0][2];
	Matrix3x3::_matrix[0][3] = matrix3x3._matrix[0][3];

	Matrix3x3::_matrix[1][0] = matrix3x3._matrix[1][0];
	Matrix3x3::_matrix[1][1] = matrix3x3._matrix[1][1];
	Matrix3x3::_matrix[1][2] = matrix3x3._matrix[1][2];
	Matrix3x3::_matrix[1][3] = matrix3x3._matrix[1][3];

	Matrix3x3::_matrix[2][0] = matrix3x3._matrix[2][0];
	Matrix3x3::_matrix[2][1] = matrix3x3._matrix[2][1];
	Matrix3x3::_matrix[2][2] = matrix3x3._matrix[2][2];
	Matrix3x3::_matrix[2][3] = matrix3x3._matrix[2][3];
}

void Matrix3x3::Identity()
{
	//First row
	Matrix3x3::_matrix[0][0] = 1;
	Matrix3x3::_matrix[0][1] = 0;
	Matrix3x3::_matrix[0][2] = 0;


	//Second row
	Matrix3x3::_matrix[1][0] = 0;
	Matrix3x3::_matrix[1][1] = 1;
	Matrix3x3::_matrix[1][2] = 0;


	//Third row
	Matrix3x3::_matrix[2][0] = 0;
	Matrix3x3::_matrix[2][1] = 0;
	Matrix3x3::_matrix[2][2] = 1;
}
void Matrix3x3::Zero()
{
	//First row
	Matrix3x3::_matrix[0][0] = 0;
	Matrix3x3::_matrix[0][1] = 0;
	Matrix3x3::_matrix[0][2] = 0;


	//Second row
	Matrix3x3::_matrix[1][0] = 0;
	Matrix3x3::_matrix[1][1] = 0;
	Matrix3x3::_matrix[1][2] = 0;


	//Third row
	Matrix3x3::_matrix[2][0] = 0;
	Matrix3x3::_matrix[2][1] = 0;
	Matrix3x3::_matrix[2][2] = 0;
}
void Matrix3x3::Constant(float value)
{
	//First row
	Matrix3x3::_matrix[0][0] = value;
	Matrix3x3::_matrix[0][1] = value;
	Matrix3x3::_matrix[0][2] = value;
	Matrix3x3::_matrix[0][3] = value;


	//Second row
	Matrix3x3::_matrix[1][0] = value;
	Matrix3x3::_matrix[1][1] = value;
	Matrix3x3::_matrix[1][2] = value;
	Matrix3x3::_matrix[1][3] = value;


	//Third row
	Matrix3x3::_matrix[2][0] = value;
	Matrix3x3::_matrix[2][1] = value;
	Matrix3x3::_matrix[2][2] = value;
	Matrix3x3::_matrix[2][3] = value;
}

void Matrix3x3::Scale(const Vector4& factor)
{
	Matrix3x3 buffer = Matrix3x3();

	buffer._matrix[0][0] = factor.X;
	buffer._matrix[1][1] = factor.Y;
	buffer._matrix[2][2] = factor.Z;

	MatrixMath::MultiplyMatrix(*this, Matrix3x3::GetMatrix(), buffer);
}
void Matrix3x3::Translation(const Vector4& translation)
{
	Matrix3x3 buffer = Matrix3x3();

	buffer._matrix[0][3] = translation.X;
	buffer._matrix[1][3] = translation.Y;
	buffer._matrix[2][3] = translation.Z;

	MatrixMath::MultiplyMatrix(*this, Matrix3x3::GetMatrix(), buffer);
}
void Matrix3x3::Rotation(const Vector4& r)
{
	Matrix3x3::RotationX(r.X);
	Matrix3x3::RotationY(r.Y);
	Matrix3x3::RotationZ(r.Z);
}
void Matrix3x3::Rotation(const Vector4& v, float rv)
{
	Matrix3x3::RotationX(v.X * rv);
	Matrix3x3::RotationY(v.Y * rv);
	Matrix3x3::RotationZ(v.Z * rv);
}

void Matrix3x3::RotationX(float rx)
{
	Matrix3x3 buffer = Matrix3x3();

	const float rad = M_PI / 180 * rx;

	buffer._matrix[1][1] = std::cos(rad);
	buffer._matrix[1][2] = -std::sin(rad);
	buffer._matrix[2][1] = std::sin(rad);
	buffer._matrix[2][2] = std::cos(rad);

	MatrixMath::MultiplyMatrix(*this, Matrix3x3::GetMatrix(), buffer);
}
void Matrix3x3::RotationY(float ry)
{
	Matrix3x3 buffer = Matrix3x3();

	const float rad = M_PI / 180 * ry;

	buffer._matrix[0][0] = std::cos(rad);
	buffer._matrix[0][2] = std::sin(rad);
	buffer._matrix[2][0] = -std::sin(rad);
	buffer._matrix[2][2] = std::cos(rad);

	MatrixMath::MultiplyMatrix(*this, Matrix3x3::GetMatrix(), buffer);
}
void Matrix3x3::RotationZ(float rz) {
	Matrix3x3 buffer = Matrix3x3();

	const float rad = M_PI / 180 * rz;

	buffer._matrix[0][0] = std::cos(rad);
	buffer._matrix[0][1] = -std::sin(rad);
	buffer._matrix[1][0] = std::sin(rad);
	buffer._matrix[1][1] = std::cos(rad);

	MatrixMath::MultiplyMatrix(*this, Matrix3x3::GetMatrix(), buffer);
}

/*Get new example of current matrix*/
Matrix3x3 Matrix3x3::GetMatrix() {
	return *this;
}
#pragma endregion

#pragma region Matrix4x4

Matrix4x4::Matrix4x4() {
	Matrix4x4::Identity();
}

void Matrix4x4::operator=(const Matrix4x4& matrix4X4)
{
	Matrix4x4::_matrix[0][0] = matrix4X4._matrix[0][0];
	Matrix4x4::_matrix[0][1] = matrix4X4._matrix[0][1];
	Matrix4x4::_matrix[0][2] = matrix4X4._matrix[0][2];
	Matrix4x4::_matrix[0][3] = matrix4X4._matrix[0][3];

	Matrix4x4::_matrix[1][0] = matrix4X4._matrix[1][0];
	Matrix4x4::_matrix[1][1] = matrix4X4._matrix[1][1];
	Matrix4x4::_matrix[1][2] = matrix4X4._matrix[1][2];
	Matrix4x4::_matrix[1][3] = matrix4X4._matrix[1][3];

	Matrix4x4::_matrix[2][0] = matrix4X4._matrix[2][0];
	Matrix4x4::_matrix[2][1] = matrix4X4._matrix[2][1];
	Matrix4x4::_matrix[2][2] = matrix4X4._matrix[2][2];
	Matrix4x4::_matrix[2][3] = matrix4X4._matrix[2][3];

	Matrix4x4::_matrix[3][0] = matrix4X4._matrix[3][0];
	Matrix4x4::_matrix[3][1] = matrix4X4._matrix[3][1];
	Matrix4x4::_matrix[3][2] = matrix4X4._matrix[3][2];
	Matrix4x4::_matrix[3][3] = matrix4X4._matrix[3][3];
}

void Matrix4x4::Identity()
{
	//First row
	Matrix4x4::_matrix[0][0] = 1;
	Matrix4x4::_matrix[0][1] = 0;
	Matrix4x4::_matrix[0][2] = 0;
	Matrix4x4::_matrix[0][3] = 0;


	//Second row
	Matrix4x4::_matrix[1][0] = 0;
	Matrix4x4::_matrix[1][1] = 1;
	Matrix4x4::_matrix[1][2] = 0;
	Matrix4x4::_matrix[1][3] = 0;


	//Third row
	Matrix4x4::_matrix[2][0] = 0;
	Matrix4x4::_matrix[2][1] = 0;
	Matrix4x4::_matrix[2][2] = 1;
	Matrix4x4::_matrix[2][3] = 0;


	//Fourth row
	Matrix4x4::_matrix[3][0] = 0;
	Matrix4x4::_matrix[3][1] = 0;
	Matrix4x4::_matrix[3][2] = 0;
	Matrix4x4::_matrix[3][3] = 1;
}
void Matrix4x4::Zero()
{
	//First row
	Matrix4x4::_matrix[0][0] = 0;
	Matrix4x4::_matrix[0][1] = 0;
	Matrix4x4::_matrix[0][2] = 0;
	Matrix4x4::_matrix[0][3] = 0;


	//Second row
	Matrix4x4::_matrix[1][0] = 0;
	Matrix4x4::_matrix[1][1] = 0;
	Matrix4x4::_matrix[1][2] = 0;
	Matrix4x4::_matrix[1][3] = 0;


	//Third row
	Matrix4x4::_matrix[2][0] = 0;
	Matrix4x4::_matrix[2][1] = 0;
	Matrix4x4::_matrix[2][2] = 0;
	Matrix4x4::_matrix[2][3] = 0;


	//Fourth row
	Matrix4x4::_matrix[3][0] = 0;
	Matrix4x4::_matrix[3][1] = 0;
	Matrix4x4::_matrix[3][2] = 0;
	Matrix4x4::_matrix[3][3] = 0;
}
void Matrix4x4::Constant(float value)
{
	//First row
	Matrix4x4::_matrix[0][0] = value;
	Matrix4x4::_matrix[0][1] = value;
	Matrix4x4::_matrix[0][2] = value;
	Matrix4x4::_matrix[0][3] = value;


	//Second row
	Matrix4x4::_matrix[1][0] = value;
	Matrix4x4::_matrix[1][1] = value;
	Matrix4x4::_matrix[1][2] = value;
	Matrix4x4::_matrix[1][3] = value;


	//Third row
	Matrix4x4::_matrix[2][0] = value;
	Matrix4x4::_matrix[2][1] = value;
	Matrix4x4::_matrix[2][2] = value;
	Matrix4x4::_matrix[2][3] = value;


	//Fourth row
	Matrix4x4::_matrix[3][0] = value;
	Matrix4x4::_matrix[3][1] = value;
	Matrix4x4::_matrix[3][2] = value;
	Matrix4x4::_matrix[3][3] = value;
}

void Matrix4x4::Scale(const Vector4& factor)
{
	Matrix4x4 buffer = Matrix4x4();

	buffer._matrix[0][0] = factor.X;
	buffer._matrix[1][1] = factor.Y;
	buffer._matrix[2][2] = factor.Z;
	buffer._matrix[3][3] = factor.W;

	MatrixMath::MultiplyMatrix(*this, Matrix4x4::GetMatrix(), buffer);
}
void Matrix4x4::Translation(const Vector4& translation)
{
	Matrix4x4 buffer = Matrix4x4();

	buffer._matrix[0][3] = translation.X;
	buffer._matrix[1][3] = translation.Y;
	buffer._matrix[2][3] = translation.Z;
	buffer._matrix[3][3] = translation.W;

	MatrixMath::MultiplyMatrix(*this, Matrix4x4::GetMatrix(), buffer);
}
void Matrix4x4::Rotation(const Vector4& r)
{
	Matrix4x4::RotationX(r.X);
	Matrix4x4::RotationY(r.Y);
	Matrix4x4::RotationZ(r.Z);
}
void Matrix4x4::Rotation(const Vector4& v, float rv)
{
	Matrix4x4::RotationX(v.X * rv);
	Matrix4x4::RotationY(v.Y * rv);
	Matrix4x4::RotationZ(v.Z * rv);
}

void Matrix4x4::RotationX(float rx)
{
	Matrix4x4 buffer = Matrix4x4();

	const float rad = M_PI / 180 * rx;

	buffer._matrix[1][1] = std::cos(rad);
	buffer._matrix[1][2] = -std::sin(rad);
	buffer._matrix[2][1] = std::sin(rad);
	buffer._matrix[2][2] = std::cos(rad);

	MatrixMath::MultiplyMatrix(*this, Matrix4x4::GetMatrix(), buffer);
}
void Matrix4x4::RotationY(float ry)
{
	Matrix4x4 buffer = Matrix4x4();

	const float rad = M_PI / 180 * ry;

	buffer._matrix[0][0] = std::cos(rad);
	buffer._matrix[0][2] = std::sin(rad);
	buffer._matrix[2][0] = -std::sin(rad);
	buffer._matrix[2][2] = std::cos(rad);

	MatrixMath::MultiplyMatrix(*this, Matrix4x4::GetMatrix(), buffer);
}
void Matrix4x4::RotationZ(float rz) {
	Matrix4x4 buffer = Matrix4x4();

	const float rad = M_PI / 180 * rz;

	buffer._matrix[0][0] = std::cos(rad);
	buffer._matrix[0][1] = -std::sin(rad);
	buffer._matrix[1][0] = std::sin(rad);
	buffer._matrix[1][1] = std::cos(rad);

	MatrixMath::MultiplyMatrix(*this, Matrix4x4::GetMatrix(), buffer);
}

/*Get new example of current matrix*/
Matrix4x4 Matrix4x4::GetMatrix() {
	return *this;
}

#pragma endregion

#pragma region Matrix3x3 math

void MatrixMath::MultiplyMatrix(Matrix3x3& outputMatrix, const Matrix3x3& firstMatrix3x3, const Matrix3x3& secondMatrix3x3) {
	//First row
	outputMatrix._matrix[0][0] =
		firstMatrix3x3._matrix[0][0] * secondMatrix3x3._matrix[0][0] +
		firstMatrix3x3._matrix[0][1] * secondMatrix3x3._matrix[1][0] +
		firstMatrix3x3._matrix[0][2] * secondMatrix3x3._matrix[2][0];
	outputMatrix._matrix[0][1] =
		firstMatrix3x3._matrix[0][0] * secondMatrix3x3._matrix[0][1] +
		firstMatrix3x3._matrix[0][1] * secondMatrix3x3._matrix[1][1] +
		firstMatrix3x3._matrix[0][2] * secondMatrix3x3._matrix[2][1];
	outputMatrix._matrix[0][2] =
		firstMatrix3x3._matrix[0][0] * secondMatrix3x3._matrix[0][2] +
		firstMatrix3x3._matrix[0][1] * secondMatrix3x3._matrix[1][2] +
		firstMatrix3x3._matrix[0][2] * secondMatrix3x3._matrix[2][2];
	outputMatrix._matrix[0][3] =
		firstMatrix3x3._matrix[0][0] * secondMatrix3x3._matrix[0][3] +
		firstMatrix3x3._matrix[0][1] * secondMatrix3x3._matrix[1][3] +
		firstMatrix3x3._matrix[0][2] * secondMatrix3x3._matrix[2][3];


	//Second row
	outputMatrix._matrix[1][0] =
		firstMatrix3x3._matrix[1][0] * secondMatrix3x3._matrix[0][0] +
		firstMatrix3x3._matrix[1][1] * secondMatrix3x3._matrix[1][0] +
		firstMatrix3x3._matrix[1][2] * secondMatrix3x3._matrix[2][0];
	outputMatrix._matrix[1][1] =
		firstMatrix3x3._matrix[1][0] * secondMatrix3x3._matrix[0][1] +
		firstMatrix3x3._matrix[1][1] * secondMatrix3x3._matrix[1][1] +
		firstMatrix3x3._matrix[1][2] * secondMatrix3x3._matrix[2][1];
	outputMatrix._matrix[1][2] =
		firstMatrix3x3._matrix[1][0] * secondMatrix3x3._matrix[0][2] +
		firstMatrix3x3._matrix[1][1] * secondMatrix3x3._matrix[1][2] +
		firstMatrix3x3._matrix[1][2] * secondMatrix3x3._matrix[2][2];
	outputMatrix._matrix[1][3] =
		firstMatrix3x3._matrix[1][0] * secondMatrix3x3._matrix[0][3] +
		firstMatrix3x3._matrix[1][1] * secondMatrix3x3._matrix[1][3] +
		firstMatrix3x3._matrix[1][2] * secondMatrix3x3._matrix[2][3];


	//Third row
	outputMatrix._matrix[2][0] =
		firstMatrix3x3._matrix[2][0] * secondMatrix3x3._matrix[0][0] +
		firstMatrix3x3._matrix[2][1] * secondMatrix3x3._matrix[1][0] +
		firstMatrix3x3._matrix[2][2] * secondMatrix3x3._matrix[2][0];
	outputMatrix._matrix[2][1] =
		firstMatrix3x3._matrix[2][0] * secondMatrix3x3._matrix[0][1] +
		firstMatrix3x3._matrix[2][1] * secondMatrix3x3._matrix[1][1] +
		firstMatrix3x3._matrix[2][2] * secondMatrix3x3._matrix[2][1];
	outputMatrix._matrix[2][2] =
		firstMatrix3x3._matrix[2][0] * secondMatrix3x3._matrix[0][2] +
		firstMatrix3x3._matrix[2][1] * secondMatrix3x3._matrix[1][2] +
		firstMatrix3x3._matrix[2][2] * secondMatrix3x3._matrix[2][2];
	outputMatrix._matrix[2][3] =
		firstMatrix3x3._matrix[2][0] * secondMatrix3x3._matrix[0][3] +
		firstMatrix3x3._matrix[2][1] * secondMatrix3x3._matrix[1][3] +
		firstMatrix3x3._matrix[2][2] * secondMatrix3x3._matrix[2][3];
}
void MatrixMath::MultiplyMatrix(Matrix3x1& outputMatrix, const Matrix3x3& firstMatrix3x3, const Matrix3x1& secondMatrix3x1) {
	//First row
	outputMatrix._matrix[0][0] =
		firstMatrix3x3._matrix[0][0] * secondMatrix3x1._matrix[0][0] +
		firstMatrix3x3._matrix[0][1] * secondMatrix3x1._matrix[1][0] +
		firstMatrix3x3._matrix[0][2] * secondMatrix3x1._matrix[2][0];
	outputMatrix._matrix[1][0] =
		firstMatrix3x3._matrix[1][0] * secondMatrix3x1._matrix[0][0] +
		firstMatrix3x3._matrix[1][1] * secondMatrix3x1._matrix[1][0] +
		firstMatrix3x3._matrix[1][2] * secondMatrix3x1._matrix[2][0];
	outputMatrix._matrix[2][0] =
		firstMatrix3x3._matrix[2][0] * secondMatrix3x1._matrix[0][0] +
		firstMatrix3x3._matrix[2][1] * secondMatrix3x1._matrix[1][0] +
		firstMatrix3x3._matrix[2][2] * secondMatrix3x1._matrix[2][0];
	outputMatrix._matrix[3][0] =
		firstMatrix3x3._matrix[3][0] * secondMatrix3x1._matrix[0][0] +
		firstMatrix3x3._matrix[3][1] * secondMatrix3x1._matrix[1][0] +
		firstMatrix3x3._matrix[3][2] * secondMatrix3x1._matrix[2][0];
}
void MatrixMath::MultiplyMatrix(Matrix3x1& outputMatrix, const Matrix3x3& firstMatrix3x3, const Vector3& secondMatrix3x1) {
	//First row
	outputMatrix._matrix[0][0] =
		firstMatrix3x3._matrix[0][0] * secondMatrix3x1.X +
		firstMatrix3x3._matrix[0][1] * secondMatrix3x1.Y +
		firstMatrix3x3._matrix[0][2] * secondMatrix3x1.Z;
	outputMatrix._matrix[1][0] =
		firstMatrix3x3._matrix[1][0] * secondMatrix3x1.X +
		firstMatrix3x3._matrix[1][1] * secondMatrix3x1.Y +
		firstMatrix3x3._matrix[1][2] * secondMatrix3x1.Z;
	outputMatrix._matrix[2][0] =
		firstMatrix3x3._matrix[2][0] * secondMatrix3x1.X +
		firstMatrix3x3._matrix[2][1] * secondMatrix3x1.Y +
		firstMatrix3x3._matrix[2][2] * secondMatrix3x1.Z;
}
void MatrixMath::MultiplyMatrix(Vector3& outputMatrix, const Matrix3x3& firstMatrix3x3, const Vector3& secondMatrix3x1) {
	//First row
	outputMatrix.X =
		firstMatrix3x3._matrix[0][0] * secondMatrix3x1.X +
		firstMatrix3x3._matrix[0][1] * secondMatrix3x1.Y +
		firstMatrix3x3._matrix[0][2] * secondMatrix3x1.Z;
	outputMatrix.Y =
		firstMatrix3x3._matrix[1][0] * secondMatrix3x1.X +
		firstMatrix3x3._matrix[1][1] * secondMatrix3x1.Y +
		firstMatrix3x3._matrix[1][2] * secondMatrix3x1.Z;
	outputMatrix.Z =
		firstMatrix3x3._matrix[2][0] * secondMatrix3x1.X +
		firstMatrix3x3._matrix[2][1] * secondMatrix3x1.Y +
		firstMatrix3x3._matrix[2][2] * secondMatrix3x1.Z;
}

void MatrixMath::AddMatrix(Matrix3x3& outputMatrix, const Matrix3x3& firstMatrix3x3, const Matrix3x3& secondMatrix3x3) {
	//First row
	outputMatrix._matrix[0][0] = firstMatrix3x3._matrix[0][0] + secondMatrix3x3._matrix[0][0];
	outputMatrix._matrix[0][1] = firstMatrix3x3._matrix[0][1] + secondMatrix3x3._matrix[0][1];
	outputMatrix._matrix[0][2] = firstMatrix3x3._matrix[0][2] + secondMatrix3x3._matrix[0][2];

	//Second row
	outputMatrix._matrix[1][0] = firstMatrix3x3._matrix[1][0] + secondMatrix3x3._matrix[1][0];
	outputMatrix._matrix[1][1] = firstMatrix3x3._matrix[1][1] + secondMatrix3x3._matrix[1][1];
	outputMatrix._matrix[1][2] = firstMatrix3x3._matrix[1][2] + secondMatrix3x3._matrix[1][2];

	//Third row
	outputMatrix._matrix[2][0] = firstMatrix3x3._matrix[2][0] + secondMatrix3x3._matrix[2][0];
	outputMatrix._matrix[2][1] = firstMatrix3x3._matrix[2][1] + secondMatrix3x3._matrix[2][1];
	outputMatrix._matrix[2][2] = firstMatrix3x3._matrix[2][2] + secondMatrix3x3._matrix[2][2];

	//Fourth row
	outputMatrix._matrix[3][0] = firstMatrix3x3._matrix[3][0] + secondMatrix3x3._matrix[3][0];
	outputMatrix._matrix[3][1] = firstMatrix3x3._matrix[3][1] + secondMatrix3x3._matrix[3][1];
	outputMatrix._matrix[3][2] = firstMatrix3x3._matrix[3][2] + secondMatrix3x3._matrix[3][2];
}


void MatrixMath::MultiplyMatrix(Matrix3x1& outputMatrix, const Matrix3x3& firstMatrix3x3, const std::array<float, 3>& secondMatrix3x1) {
	//First row
	outputMatrix._matrix[0][0] =
		firstMatrix3x3._matrix[0][0] * secondMatrix3x1[0] +
		firstMatrix3x3._matrix[0][1] * secondMatrix3x1[1] +
		firstMatrix3x3._matrix[0][2] * secondMatrix3x1[2];
	outputMatrix._matrix[1][0] =
		firstMatrix3x3._matrix[1][0] * secondMatrix3x1[0] +
		firstMatrix3x3._matrix[1][1] * secondMatrix3x1[1] +
		firstMatrix3x3._matrix[1][2] * secondMatrix3x1[2];
	outputMatrix._matrix[2][0] =
		firstMatrix3x3._matrix[2][0] * secondMatrix3x1[0] +
		firstMatrix3x3._matrix[2][1] * secondMatrix3x1[1] +
		firstMatrix3x3._matrix[2][2] * secondMatrix3x1[2];
	outputMatrix._matrix[3][0] =
		firstMatrix3x3._matrix[3][0] * secondMatrix3x1[0] +
		firstMatrix3x3._matrix[3][1] * secondMatrix3x1[1] +
		firstMatrix3x3._matrix[3][2] * secondMatrix3x1[2];
}
void MatrixMath::MultiplyMatrix(std::array<float, 3>& outputMatrix3x1, const Matrix3x3& firstMatrix3x3, const std::array<float, 3>& secondMatrix3x1) {
	//First row
	outputMatrix3x1[0] =
		firstMatrix3x3._matrix[0][0] * secondMatrix3x1[0] +
		firstMatrix3x3._matrix[0][1] * secondMatrix3x1[1] +
		firstMatrix3x3._matrix[0][2] * secondMatrix3x1[2];
	outputMatrix3x1[1] =
		firstMatrix3x3._matrix[1][0] * secondMatrix3x1[0] +
		firstMatrix3x3._matrix[1][1] * secondMatrix3x1[1] +
		firstMatrix3x3._matrix[1][2] * secondMatrix3x1[2];
	outputMatrix3x1[2] =
		firstMatrix3x3._matrix[2][0] * secondMatrix3x1[0] +
		firstMatrix3x3._matrix[2][1] * secondMatrix3x1[1] +
		firstMatrix3x3._matrix[2][2] * secondMatrix3x1[2];
}

void MatrixMath::MultiplyMatrix(
	float& outputMatrix3x1Xvalue,
	float& outputMatrix3x1Yvalue,
	float& outputMatrix3x1Zvalue,
	const Matrix3x3& firstMatrix3x3,
	const std::array<float, 3>& secondMatrix3x1) {

	//First row
	outputMatrix3x1Xvalue =
		firstMatrix3x3._matrix[0][0] * secondMatrix3x1[0] +
		firstMatrix3x3._matrix[0][1] * secondMatrix3x1[1] +
		firstMatrix3x3._matrix[0][2] * secondMatrix3x1[2];
	outputMatrix3x1Yvalue =
		firstMatrix3x3._matrix[1][0] * secondMatrix3x1[0] +
		firstMatrix3x3._matrix[1][1] * secondMatrix3x1[1] +
		firstMatrix3x3._matrix[1][2] * secondMatrix3x1[2];
	outputMatrix3x1Zvalue =
		firstMatrix3x3._matrix[2][0] * secondMatrix3x1[0] +
		firstMatrix3x3._matrix[2][1] * secondMatrix3x1[1] +
		firstMatrix3x3._matrix[2][2] * secondMatrix3x1[2];
}

#pragma endregion

#pragma region Matrix4x4 math

void MatrixMath::MultiplyMatrix(Matrix4x4& outputMatrix, const Matrix4x4& firstMatrix4x4, const Matrix4x4& secondMatrix4x4) {
	//First row
	outputMatrix._matrix[0][0] =
		firstMatrix4x4._matrix[0][0] * secondMatrix4x4._matrix[0][0] +
		firstMatrix4x4._matrix[0][1] * secondMatrix4x4._matrix[1][0] +
		firstMatrix4x4._matrix[0][2] * secondMatrix4x4._matrix[2][0] +
		firstMatrix4x4._matrix[0][3] * secondMatrix4x4._matrix[3][0];
	outputMatrix._matrix[0][1] =
		firstMatrix4x4._matrix[0][0] * secondMatrix4x4._matrix[0][1] +
		firstMatrix4x4._matrix[0][1] * secondMatrix4x4._matrix[1][1] +
		firstMatrix4x4._matrix[0][2] * secondMatrix4x4._matrix[2][1] +
		firstMatrix4x4._matrix[0][3] * secondMatrix4x4._matrix[3][1];
	outputMatrix._matrix[0][2] =
		firstMatrix4x4._matrix[0][0] * secondMatrix4x4._matrix[0][2] +
		firstMatrix4x4._matrix[0][1] * secondMatrix4x4._matrix[1][2] +
		firstMatrix4x4._matrix[0][2] * secondMatrix4x4._matrix[2][2] +
		firstMatrix4x4._matrix[0][3] * secondMatrix4x4._matrix[3][2];
	outputMatrix._matrix[0][3] =
		firstMatrix4x4._matrix[0][0] * secondMatrix4x4._matrix[0][3] +
		firstMatrix4x4._matrix[0][1] * secondMatrix4x4._matrix[1][3] +
		firstMatrix4x4._matrix[0][2] * secondMatrix4x4._matrix[2][3] +
		firstMatrix4x4._matrix[0][3] * secondMatrix4x4._matrix[3][3];


	//Second row
	outputMatrix._matrix[1][0] =
		firstMatrix4x4._matrix[1][0] * secondMatrix4x4._matrix[0][0] +
		firstMatrix4x4._matrix[1][1] * secondMatrix4x4._matrix[1][0] +
		firstMatrix4x4._matrix[1][2] * secondMatrix4x4._matrix[2][0] +
		firstMatrix4x4._matrix[1][3] * secondMatrix4x4._matrix[3][0];
	outputMatrix._matrix[1][1] =
		firstMatrix4x4._matrix[1][0] * secondMatrix4x4._matrix[0][1] +
		firstMatrix4x4._matrix[1][1] * secondMatrix4x4._matrix[1][1] +
		firstMatrix4x4._matrix[1][2] * secondMatrix4x4._matrix[2][1] +
		firstMatrix4x4._matrix[1][3] * secondMatrix4x4._matrix[3][1];
	outputMatrix._matrix[1][2] =
		firstMatrix4x4._matrix[1][0] * secondMatrix4x4._matrix[0][2] +
		firstMatrix4x4._matrix[1][1] * secondMatrix4x4._matrix[1][2] +
		firstMatrix4x4._matrix[1][2] * secondMatrix4x4._matrix[2][2] +
		firstMatrix4x4._matrix[1][3] * secondMatrix4x4._matrix[3][2];
	outputMatrix._matrix[1][3] =
		firstMatrix4x4._matrix[1][0] * secondMatrix4x4._matrix[0][3] +
		firstMatrix4x4._matrix[1][1] * secondMatrix4x4._matrix[1][3] +
		firstMatrix4x4._matrix[1][2] * secondMatrix4x4._matrix[2][3] +
		firstMatrix4x4._matrix[1][3] * secondMatrix4x4._matrix[3][3];


	//Third row
	outputMatrix._matrix[2][0] =
		firstMatrix4x4._matrix[2][0] * secondMatrix4x4._matrix[0][0] +
		firstMatrix4x4._matrix[2][1] * secondMatrix4x4._matrix[1][0] +
		firstMatrix4x4._matrix[2][2] * secondMatrix4x4._matrix[2][0] +
		firstMatrix4x4._matrix[2][3] * secondMatrix4x4._matrix[3][0];
	outputMatrix._matrix[2][1] =
		firstMatrix4x4._matrix[2][0] * secondMatrix4x4._matrix[0][1] +
		firstMatrix4x4._matrix[2][1] * secondMatrix4x4._matrix[1][1] +
		firstMatrix4x4._matrix[2][2] * secondMatrix4x4._matrix[2][1] +
		firstMatrix4x4._matrix[2][3] * secondMatrix4x4._matrix[3][1];
	outputMatrix._matrix[2][2] =
		firstMatrix4x4._matrix[2][0] * secondMatrix4x4._matrix[0][2] +
		firstMatrix4x4._matrix[2][1] * secondMatrix4x4._matrix[1][2] +
		firstMatrix4x4._matrix[2][2] * secondMatrix4x4._matrix[2][2] +
		firstMatrix4x4._matrix[2][3] * secondMatrix4x4._matrix[3][2];
	outputMatrix._matrix[2][3] =
		firstMatrix4x4._matrix[2][0] * secondMatrix4x4._matrix[0][3] +
		firstMatrix4x4._matrix[2][1] * secondMatrix4x4._matrix[1][3] +
		firstMatrix4x4._matrix[2][2] * secondMatrix4x4._matrix[2][3] +
		firstMatrix4x4._matrix[2][3] * secondMatrix4x4._matrix[3][3];


	//Fourth row
	outputMatrix._matrix[3][0] =
		firstMatrix4x4._matrix[3][0] * secondMatrix4x4._matrix[0][0] +
		firstMatrix4x4._matrix[3][1] * secondMatrix4x4._matrix[1][0] +
		firstMatrix4x4._matrix[3][2] * secondMatrix4x4._matrix[2][0] +
		firstMatrix4x4._matrix[3][3] * secondMatrix4x4._matrix[3][0];
	outputMatrix._matrix[3][1] =
		firstMatrix4x4._matrix[3][0] * secondMatrix4x4._matrix[0][1] +
		firstMatrix4x4._matrix[3][1] * secondMatrix4x4._matrix[1][1] +
		firstMatrix4x4._matrix[3][2] * secondMatrix4x4._matrix[2][1] +
		firstMatrix4x4._matrix[3][3] * secondMatrix4x4._matrix[3][1];
	outputMatrix._matrix[3][2] =
		firstMatrix4x4._matrix[3][0] * secondMatrix4x4._matrix[0][2] +
		firstMatrix4x4._matrix[3][1] * secondMatrix4x4._matrix[1][2] +
		firstMatrix4x4._matrix[3][2] * secondMatrix4x4._matrix[2][2] +
		firstMatrix4x4._matrix[3][3] * secondMatrix4x4._matrix[3][2];
	outputMatrix._matrix[3][3] =
		firstMatrix4x4._matrix[3][0] * secondMatrix4x4._matrix[0][3] +
		firstMatrix4x4._matrix[3][1] * secondMatrix4x4._matrix[1][3] +
		firstMatrix4x4._matrix[3][2] * secondMatrix4x4._matrix[2][3] +
		firstMatrix4x4._matrix[3][3] * secondMatrix4x4._matrix[3][3];
}
void MatrixMath::MultiplyMatrix(Matrix4x1& outputMatrix, const Matrix4x4& firstMatrix4x4, const Matrix4x1& secondMatrix4x1) {
	//First row
	outputMatrix._matrix[0][0] =
		firstMatrix4x4._matrix[0][0] * secondMatrix4x1._matrix[0][0] +
		firstMatrix4x4._matrix[0][1] * secondMatrix4x1._matrix[1][0] +
		firstMatrix4x4._matrix[0][2] * secondMatrix4x1._matrix[2][0] +
		firstMatrix4x4._matrix[0][3] * secondMatrix4x1._matrix[3][0];
	outputMatrix._matrix[1][0] =
		firstMatrix4x4._matrix[1][0] * secondMatrix4x1._matrix[0][0] +
		firstMatrix4x4._matrix[1][1] * secondMatrix4x1._matrix[1][0] +
		firstMatrix4x4._matrix[1][2] * secondMatrix4x1._matrix[2][0] +
		firstMatrix4x4._matrix[1][3] * secondMatrix4x1._matrix[3][0];
	outputMatrix._matrix[2][0] =
		firstMatrix4x4._matrix[2][0] * secondMatrix4x1._matrix[0][0] +
		firstMatrix4x4._matrix[2][1] * secondMatrix4x1._matrix[1][0] +
		firstMatrix4x4._matrix[2][2] * secondMatrix4x1._matrix[2][0] +
		firstMatrix4x4._matrix[2][3] * secondMatrix4x1._matrix[3][0];
	outputMatrix._matrix[3][0] =
		firstMatrix4x4._matrix[3][0] * secondMatrix4x1._matrix[0][0] +
		firstMatrix4x4._matrix[3][1] * secondMatrix4x1._matrix[1][0] +
		firstMatrix4x4._matrix[3][2] * secondMatrix4x1._matrix[2][0] +
		firstMatrix4x4._matrix[3][3] * secondMatrix4x1._matrix[3][0];
}
void MatrixMath::MultiplyMatrix(Matrix4x1& outputMatrix, const Matrix4x4& firstMatrix4x4, const Vector4& secondMatrix4x1) {
	//First row
	outputMatrix._matrix[0][0] =
		firstMatrix4x4._matrix[0][0] * secondMatrix4x1.X +
		firstMatrix4x4._matrix[0][1] * secondMatrix4x1.Y +
		firstMatrix4x4._matrix[0][2] * secondMatrix4x1.Z +
		firstMatrix4x4._matrix[0][3] * secondMatrix4x1.W;
	outputMatrix._matrix[1][0] =
		firstMatrix4x4._matrix[1][0] * secondMatrix4x1.X +
		firstMatrix4x4._matrix[1][1] * secondMatrix4x1.Y +
		firstMatrix4x4._matrix[1][2] * secondMatrix4x1.Z +
		firstMatrix4x4._matrix[1][3] * secondMatrix4x1.W;
	outputMatrix._matrix[2][0] =
		firstMatrix4x4._matrix[2][0] * secondMatrix4x1.X +
		firstMatrix4x4._matrix[2][1] * secondMatrix4x1.Y +
		firstMatrix4x4._matrix[2][2] * secondMatrix4x1.Z +
		firstMatrix4x4._matrix[2][3] * secondMatrix4x1.W;
	outputMatrix._matrix[3][0] =
		firstMatrix4x4._matrix[3][0] * secondMatrix4x1.X +
		firstMatrix4x4._matrix[3][1] * secondMatrix4x1.Y +
		firstMatrix4x4._matrix[3][2] * secondMatrix4x1.Z +
		firstMatrix4x4._matrix[3][3] * secondMatrix4x1.W;
}
void MatrixMath::MultiplyMatrix(Vector4& outputMatrix, const Matrix4x4& firstMatrix4x4, const Vector4& secondMatrix4x1) {
	//First row
	outputMatrix.X =
		firstMatrix4x4._matrix[0][0] * secondMatrix4x1.X +
		firstMatrix4x4._matrix[0][1] * secondMatrix4x1.Y +
		firstMatrix4x4._matrix[0][2] * secondMatrix4x1.Z +
		firstMatrix4x4._matrix[0][3] * secondMatrix4x1.W;
	outputMatrix.Y =
		firstMatrix4x4._matrix[1][0] * secondMatrix4x1.X +
		firstMatrix4x4._matrix[1][1] * secondMatrix4x1.Y +
		firstMatrix4x4._matrix[1][2] * secondMatrix4x1.Z +
		firstMatrix4x4._matrix[1][3] * secondMatrix4x1.W;
	outputMatrix.Z =
		firstMatrix4x4._matrix[2][0] * secondMatrix4x1.X +
		firstMatrix4x4._matrix[2][1] * secondMatrix4x1.Y +
		firstMatrix4x4._matrix[2][2] * secondMatrix4x1.Z +
		firstMatrix4x4._matrix[2][3] * secondMatrix4x1.W;
	outputMatrix.W =
		firstMatrix4x4._matrix[3][0] * secondMatrix4x1.X +
		firstMatrix4x4._matrix[3][1] * secondMatrix4x1.Y +
		firstMatrix4x4._matrix[3][2] * secondMatrix4x1.Z +
		firstMatrix4x4._matrix[3][3] * secondMatrix4x1.W;
}
void MatrixMath::MultiplyMatrix(Vector3& outputMatrix, const Matrix4x4& firstMatrix4x4, const Vector3& secondMatrix4x1) {
	//First row
	outputMatrix.X =
		firstMatrix4x4._matrix[0][0] * secondMatrix4x1.X +
		firstMatrix4x4._matrix[0][1] * secondMatrix4x1.Y +
		firstMatrix4x4._matrix[0][2] * secondMatrix4x1.Z +
		firstMatrix4x4._matrix[0][3] * 1;
	outputMatrix.Y =
		firstMatrix4x4._matrix[1][0] * secondMatrix4x1.X +
		firstMatrix4x4._matrix[1][1] * secondMatrix4x1.Y +
		firstMatrix4x4._matrix[1][2] * secondMatrix4x1.Z +
		firstMatrix4x4._matrix[1][3] * 1;
	outputMatrix.Z =
		firstMatrix4x4._matrix[2][0] * secondMatrix4x1.X +
		firstMatrix4x4._matrix[2][1] * secondMatrix4x1.Y +
		firstMatrix4x4._matrix[2][2] * secondMatrix4x1.Z +
		firstMatrix4x4._matrix[2][3] * 1;
}

void MatrixMath::AddMatrix(Matrix4x4& outputMatrix, const Matrix4x4& firstMatrix4x4, const Matrix4x4& secondMatrix4x4) {
	//First row
	outputMatrix._matrix[0][0] = firstMatrix4x4._matrix[0][0] + secondMatrix4x4._matrix[0][0];
	outputMatrix._matrix[0][1] = firstMatrix4x4._matrix[0][1] + secondMatrix4x4._matrix[0][1];
	outputMatrix._matrix[0][2] = firstMatrix4x4._matrix[0][2] + secondMatrix4x4._matrix[0][2];
	outputMatrix._matrix[0][3] = firstMatrix4x4._matrix[0][3] + secondMatrix4x4._matrix[0][3];

	//Second row
	outputMatrix._matrix[1][0] = firstMatrix4x4._matrix[1][0] + secondMatrix4x4._matrix[1][0];
	outputMatrix._matrix[1][1] = firstMatrix4x4._matrix[1][1] + secondMatrix4x4._matrix[1][1];
	outputMatrix._matrix[1][2] = firstMatrix4x4._matrix[1][2] + secondMatrix4x4._matrix[1][2];
	outputMatrix._matrix[1][3] = firstMatrix4x4._matrix[1][3] + secondMatrix4x4._matrix[1][3];

	//Third row
	outputMatrix._matrix[2][0] = firstMatrix4x4._matrix[2][0] + secondMatrix4x4._matrix[2][0];
	outputMatrix._matrix[2][1] = firstMatrix4x4._matrix[2][1] + secondMatrix4x4._matrix[2][1];
	outputMatrix._matrix[2][2] = firstMatrix4x4._matrix[2][2] + secondMatrix4x4._matrix[2][2];
	outputMatrix._matrix[2][3] = firstMatrix4x4._matrix[2][3] + secondMatrix4x4._matrix[2][3];

	//Fourth row
	outputMatrix._matrix[3][0] = firstMatrix4x4._matrix[3][0] + secondMatrix4x4._matrix[3][0];
	outputMatrix._matrix[3][1] = firstMatrix4x4._matrix[3][1] + secondMatrix4x4._matrix[3][1];
	outputMatrix._matrix[3][2] = firstMatrix4x4._matrix[3][2] + secondMatrix4x4._matrix[3][2];
	outputMatrix._matrix[3][3] = firstMatrix4x4._matrix[3][3] + secondMatrix4x4._matrix[3][3];
}


void MatrixMath::MultiplyMatrix(Matrix4x1& outputMatrix, const Matrix4x4& firstMatrix4x4, const std::array<float, 4>& secondMatrix4x1) {
	//First row
	outputMatrix._matrix[0][0] =
		firstMatrix4x4._matrix[0][0] * secondMatrix4x1[0] +
		firstMatrix4x4._matrix[0][1] * secondMatrix4x1[1] +
		firstMatrix4x4._matrix[0][2] * secondMatrix4x1[2] +
		firstMatrix4x4._matrix[0][3] * secondMatrix4x1[3];
	outputMatrix._matrix[1][0] =
		firstMatrix4x4._matrix[1][0] * secondMatrix4x1[0] +
		firstMatrix4x4._matrix[1][1] * secondMatrix4x1[1] +
		firstMatrix4x4._matrix[1][2] * secondMatrix4x1[2] +
		firstMatrix4x4._matrix[1][3] * secondMatrix4x1[3];
	outputMatrix._matrix[2][0] =
		firstMatrix4x4._matrix[2][0] * secondMatrix4x1[0] +
		firstMatrix4x4._matrix[2][1] * secondMatrix4x1[1] +
		firstMatrix4x4._matrix[2][2] * secondMatrix4x1[2] +
		firstMatrix4x4._matrix[2][3] * secondMatrix4x1[3];
	outputMatrix._matrix[3][0] =
		firstMatrix4x4._matrix[3][0] * secondMatrix4x1[0] +
		firstMatrix4x4._matrix[3][1] * secondMatrix4x1[1] +
		firstMatrix4x4._matrix[3][2] * secondMatrix4x1[2] +
		firstMatrix4x4._matrix[3][3] * secondMatrix4x1[3];
}
void MatrixMath::MultiplyMatrix(std::array<float, 4>& outputMatrix4x1, const Matrix4x4& firstMatrix4x4, const std::array<float, 4>& secondMatrix4x1) {
	//First row
	outputMatrix4x1[0] =
		firstMatrix4x4._matrix[0][0] * secondMatrix4x1[0] +
		firstMatrix4x4._matrix[0][1] * secondMatrix4x1[1] +
		firstMatrix4x4._matrix[0][2] * secondMatrix4x1[2] +
		firstMatrix4x4._matrix[0][3] * secondMatrix4x1[3];
	outputMatrix4x1[1] =
		firstMatrix4x4._matrix[1][0] * secondMatrix4x1[0] +
		firstMatrix4x4._matrix[1][1] * secondMatrix4x1[1] +
		firstMatrix4x4._matrix[1][2] * secondMatrix4x1[2] +
		firstMatrix4x4._matrix[1][3] * secondMatrix4x1[3];
	outputMatrix4x1[2] =
		firstMatrix4x4._matrix[2][0] * secondMatrix4x1[0] +
		firstMatrix4x4._matrix[2][1] * secondMatrix4x1[1] +
		firstMatrix4x4._matrix[2][2] * secondMatrix4x1[2] +
		firstMatrix4x4._matrix[2][3] * secondMatrix4x1[3];
	outputMatrix4x1[3] =
		firstMatrix4x4._matrix[3][0] * secondMatrix4x1[0] +
		firstMatrix4x4._matrix[3][1] * secondMatrix4x1[1] +
		firstMatrix4x4._matrix[3][2] * secondMatrix4x1[2] +
		firstMatrix4x4._matrix[3][3] * secondMatrix4x1[3];
}

void MatrixMath::MultiplyMatrix(
	float& outputMatrix4x1Xvalue,
	float& outputMatrix4x1Yvalue,
	float& outputMatrix4x1Zvalue,
	float& outputMatrix4x1Wvalue,
	const Matrix4x4& firstMatrix4x4,
	const std::array<float, 4>& secondMatrix4x1) {

	//First row
	outputMatrix4x1Xvalue =
		firstMatrix4x4._matrix[0][0] * secondMatrix4x1[0] +
		firstMatrix4x4._matrix[0][1] * secondMatrix4x1[1] +
		firstMatrix4x4._matrix[0][2] * secondMatrix4x1[2] +
		firstMatrix4x4._matrix[0][3] * secondMatrix4x1[3];
	outputMatrix4x1Yvalue =
		firstMatrix4x4._matrix[1][0] * secondMatrix4x1[0] +
		firstMatrix4x4._matrix[1][1] * secondMatrix4x1[1] +
		firstMatrix4x4._matrix[1][2] * secondMatrix4x1[2] +
		firstMatrix4x4._matrix[1][3] * secondMatrix4x1[3];
	outputMatrix4x1Zvalue =
		firstMatrix4x4._matrix[2][0] * secondMatrix4x1[0] +
		firstMatrix4x4._matrix[2][1] * secondMatrix4x1[1] +
		firstMatrix4x4._matrix[2][2] * secondMatrix4x1[2] +
		firstMatrix4x4._matrix[2][3] * secondMatrix4x1[3];
	outputMatrix4x1Wvalue =
		firstMatrix4x4._matrix[3][0] * secondMatrix4x1[0] +
		firstMatrix4x4._matrix[3][1] * secondMatrix4x1[1] +
		firstMatrix4x4._matrix[3][2] * secondMatrix4x1[2] +
		firstMatrix4x4._matrix[3][3] * secondMatrix4x1[3];
}

#pragma endregion