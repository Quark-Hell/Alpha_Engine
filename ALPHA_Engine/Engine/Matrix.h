#pragma once
#define _USE_MATH_DEFINES

#include <array>
#include <cmath>

class Vector3;
class Vector4;

class Matrix3x1 {
private:
    std::array<std::array<float, 3>, 1> _matrix;

private:
    friend class MatrixMath;
};

class Matrix4x1 {
private:
    std::array<std::array<float, 4>, 1> _matrix;

private:
    friend class MatrixMath;
};

class Matrix2x2 {
private:
	std::array<std::array<float, 2>, 2> _matrix;

private:
    friend class MatrixMath;
};

class Matrix3x3 {
private:
	std::array<std::array<float, 3>, 3> _matrix;

private:
    friend class MatrixMath;

public:
    Matrix3x3();

    void operator=(const Matrix3x3& matrix4X4);

    void Identity();
    void Zero();
    void Constant(float value);

    void Scale(const Vector4& factor);
    void Translation(const Vector4& translation);
    void Rotation(const Vector4& r);
    void Rotation(const Vector4& v, float rv);

    void RotationX(float rx);
    void RotationY(float ry);
    void RotationZ(float rz);

    /*Get new example of current matrix*/
    Matrix3x3 GetMatrix();
};

class Matrix4x4 {
private:
	std::array<std::array<float, 4>, 4> _matrix;

private:
    friend class MatrixMath;

public:
    Matrix4x4();

    void operator=(const Matrix4x4& matrix4X4);

    void Identity();
    void Zero();
    void Constant(float value);

    void Scale(const Vector4& factor);
    void Translation(const Vector4& translation);
    void Rotation(const Vector4& r);
    void Rotation(const Vector4& v, float rv);

    void RotationX(float rx);
    void RotationY(float ry);
    void RotationZ(float rz);

    Matrix4x4 View(const Matrix4x4& transformMatrix);
    Matrix4x4 Projection(float fov = 90.0, float aspect = 1.0, float ZNear = 1.0, float ZFar = 10.0);
    Matrix4x4 ScreenSpace(int width, int height);

    /*Get new example of current matrix*/
    Matrix4x4 GetMatrix();
};

static class MatrixMath {
public:
    static void MultiplyMatrix(Matrix3x1& outputMatrix, const Matrix3x3& firstMatrix3x3, const std::array<float, 3>& secondMatrix3x1);
    static void MultiplyMatrix(std::array<float, 3>& outputMatrix3x1, const Matrix3x3& firstMatrix3x3, const std::array<float, 3>& secondMatrix3x1);

    static void MultiplyMatrix(
        float& outputMatrix3x1Xvalue,
        float& outputMatrix3x1Yvalue,
        float& outputMatrix3x1Zvalue,
        const Matrix3x3& firstMatrix3x3,
        const std::array<float, 3>& secondMatrix3x1);

    static void MultiplyMatrix(Matrix3x3& outputMatrix, const Matrix3x3& firstMatrix3x3, const Matrix3x3& secondMatrix3x3);
    static void MultiplyMatrix(Matrix3x1& outputMatrix, const Matrix3x3& firstMatrix3x3, const Matrix3x1& secondMatrix3x1);
    static void MultiplyMatrix(Matrix3x1& outputMatrix, const Matrix3x3& firstMatrix3x3, const Vector3& secondMatrix3x1);
    static void MultiplyMatrix(Vector3& outputMatrix, const Matrix3x3& firstMatrix3x3, const Vector3& secondMatrix3x1);

    static void AddMatrix(Matrix3x3& outputMatrix, const Matrix3x3& firstMatrix3x3, const Matrix3x3& secondMatrix3x3);

public:
    static void MultiplyMatrix(Matrix4x1& outputMatrix, const Matrix4x4& firstMatrix4x4, const std::array<float, 4>& secondMatrix4x1);
    static void MultiplyMatrix(std::array<float, 4>& outputMatrix4x1, const Matrix4x4& firstMatrix4x4, const std::array<float, 4>& secondMatrix4x1);
    
    static void MultiplyMatrix(
        float& outputMatrix4x1Xvalue, 
        float& outputMatrix4x1Yvalue,
        float& outputMatrix4x1Zvalue,
        float& outputMatrix4x1Wvalue,
        const Matrix4x4& firstMatrix4x4, 
        const std::array<float, 4>& secondMatrix4x1);

    static void MultiplyMatrix(Matrix4x4& outputMatrix , const Matrix4x4& firstMatrix4x4, const Matrix4x4& secondMatrix4x4);
    static void MultiplyMatrix(Matrix4x1& outputMatrix, const Matrix4x4& firstMatrix4x4, const Matrix4x1& secondMatrix4x1);
    static void MultiplyMatrix(Matrix4x1& outputMatrix, const Matrix4x4& firstMatrix4x4, const Vector4& secondMatrix4x1);
    static void MultiplyMatrix(Vector4& outputMatrix, const Matrix4x4& firstMatrix4x4, const Vector4& secondMatrix4x1);
    static void MultiplyMatrix(Vector3& outputMatrix, const Matrix4x4& firstMatrix4x4, const Vector3& secondMatrix4x1);

    static void AddMatrix(Matrix4x4& outputMatrix, const Matrix4x4& firstMatrix4x4, const Matrix4x4& secondMatrix4x4);
};
