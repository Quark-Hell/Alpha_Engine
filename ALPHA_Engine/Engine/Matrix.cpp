#include "Matrix.h"

#include "Vectors.h"

inline Matrix4x4::Matrix4x4() {
	Matrix4x4::Identity();
}

inline void Matrix4x4::operator=(const Matrix4x4& matrix4X4)
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

inline void Matrix4x4::Identity()
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
inline void Matrix4x4::Zero()
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
inline void Matrix4x4::Constant(float value)
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

inline void Matrix4x4::Scale(const Vector4& factor)
{
	Matrix4x4 buffer = Matrix4x4();

	buffer._matrix[0][0] = factor.X;
	buffer._matrix[1][1] = factor.Y;
	buffer._matrix[2][2] = factor.Z;
	buffer._matrix[3][3] = factor.W;

	MatrixMath::MultiplyMatrix(*this, Matrix4x4::GetMatrix(), buffer);
}
inline void Matrix4x4::Translation(const Vector4& translation)
{
	Matrix4x4 buffer = Matrix4x4();

	buffer._matrix[0][3] = translation.X;
	buffer._matrix[1][3] = translation.Y;
	buffer._matrix[2][3] = translation.Z;
	buffer._matrix[3][3] = translation.W;

	MatrixMath::MultiplyMatrix(*this, Matrix4x4::GetMatrix(), buffer);
}
inline void Matrix4x4::Rotation(const Vector4& r)
{
	Matrix4x4::RotationX(r.X);
	Matrix4x4::RotationY(r.Y);
	Matrix4x4::RotationZ(r.Z);
}
inline void Matrix4x4::Rotation(const Vector4& v, float rv)
{
	Matrix4x4::RotationX(v.X * rv);
	Matrix4x4::RotationY(v.Y * rv);
	Matrix4x4::RotationZ(v.Z * rv);
}

inline void Matrix4x4::RotationX(float rx)
{
	Matrix4x4 buffer = Matrix4x4();

	const float rad = M_PI / 180 * rx;

	buffer._matrix[1][1] = std::cos(rad);
	buffer._matrix[1][2] = -std::sin(rad);
	buffer._matrix[2][1] = std::sin(rad);
	buffer._matrix[2][2] = std::cos(rad);

	MatrixMath::MultiplyMatrix(*this, Matrix4x4::GetMatrix(), buffer);
}
inline void Matrix4x4::RotationY(float ry)
{
	Matrix4x4 buffer = Matrix4x4();

	const float rad = M_PI / 180 * ry;

	buffer._matrix[0][0] = std::cos(rad);
	buffer._matrix[0][2] = std::sin(rad);
	buffer._matrix[2][0] = -std::sin(rad);
	buffer._matrix[2][2] = std::cos(rad);

	MatrixMath::MultiplyMatrix(*this, Matrix4x4::GetMatrix(), buffer);
}
inline void Matrix4x4::RotationZ(float rz) {
	Matrix4x4 buffer = Matrix4x4();

	const float rad = M_PI / 180 * rz;

	buffer._matrix[0][0] = std::cos(rad);
	buffer._matrix[0][1] = -std::sin(rad);
	buffer._matrix[1][0] = std::sin(rad);
	buffer._matrix[1][1] = std::cos(rad);

	MatrixMath::MultiplyMatrix(*this, Matrix4x4::GetMatrix(), buffer);
}

/*Get new example of current matrix*/
inline Matrix4x4 Matrix4x4::GetMatrix() {
	return *this;
}

inline void MatrixMath::MultiplyMatrix(Matrix4x4& outputMatrix, const Matrix4x4& firstMatrix4x4, const Matrix4x4& secondMatrix4x4) {
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
inline void MatrixMath::MultiplyMatrix(Matrix4x1& outputMatrix, const Matrix4x4& firstMatrix4x4, const Matrix4x4& secondMatrix4x1) {
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
inline void MatrixMath::MultiplyMatrix(Matrix4x1& outputMatrix, const Matrix4x4& firstMatrix4x4, const Vector4& secondMatrix4x1) {
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
inline void MatrixMath::MultiplyMatrix(Vector4& outputMatrix, const Matrix4x4& firstMatrix4x4, const Vector4& secondMatrix4x1) {
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
inline void MatrixMath::MultiplyMatrix(Vector3& outputMatrix, const Matrix4x4& firstMatrix4x4, const Vector3& secondMatrix4x1) {
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

inline void MatrixMath::AddMatrix(Matrix4x4& outputMatrix, const Matrix4x4& firstMatrix4x4, const Matrix4x4& secondMatrix4x4) {
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


inline void MatrixMath::MultiplyMatrix(Matrix4x1& outputMatrix, const Matrix4x4& firstMatrix4x4, const std::array<float, 4>& secondMatrix4x1) {
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
inline void MatrixMath::MultiplyMatrix(std::array<float, 4>& outputMatrix4x1, const Matrix4x4& firstMatrix4x4, const std::array<float, 4>& secondMatrix4x1) {
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

inline void MatrixMath::MultiplyMatrix(
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