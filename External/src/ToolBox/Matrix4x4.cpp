#include "matrix4x4.hpp"
#include "Vector3.hpp"

#include <assert.h>

using namespace std;

Matrix4x4::Matrix4x4()
{

}

Matrix4x4::Matrix4x4(float r00, float r01, float r02, float r03, float r10, float r11, float r12, float r13, float r20, float r21, float r22, float r23, float r30, float r31, float r32, float r33) : Row0(r00, r01, r02, r03), Row1(r10, r11, r12, r13), Row2(r20, r21, r22, r23), Row3(r30, r31, r32, r33)
{

}

Matrix4x4::Matrix4x4(Vector4 row0, Vector4 row1, Vector4 row2, Vector4 row3)
    : Row0(row0), Row1(row1), Row2(row2), Row3(row3)
{

}


Matrix4x4 Matrix4x4::operator=(const Matrix4x4& matrix)
{
	m_matrix = matrix.m_matrix;
	return *this;
}




Matrix4x4& Matrix4x4::Multiply(const Matrix4x4& mat)
{
    Row0 = Vector4(
        Row0.x * mat.Row0.x + Row0.y * mat.Row1.x + Row0.z * mat.Row2.x + Row0.w * mat.Row3.x,
        Row0.x * mat.Row0.y + Row0.y * mat.Row1.y + Row0.z * mat.Row2.y + Row0.w * mat.Row3.y,
        Row0.x * mat.Row0.z + Row0.y * mat.Row1.z + Row0.z * mat.Row2.z + Row0.w * mat.Row3.z,
        Row0.x * mat.Row0.w + Row0.y * mat.Row1.w + Row0.z * mat.Row2.w + Row0.w * mat.Row3.w
    );
    Row1 = Vector4(
        Row1.x * mat.Row0.x + Row1.y * mat.Row1.x + Row1.z * mat.Row2.x + Row1.w * mat.Row3.x,
        Row1.x * mat.Row0.y + Row1.y * mat.Row1.y + Row1.z * mat.Row2.y + Row1.w * mat.Row3.y,
        Row1.x * mat.Row0.z + Row1.y * mat.Row1.z + Row1.z * mat.Row2.z + Row1.w * mat.Row3.z,
        Row1.x * mat.Row0.w + Row1.y * mat.Row1.w + Row1.z * mat.Row2.w + Row1.w * mat.Row3.w
    );
    Row2 = Vector4(
        Row2.x * mat.Row0.x + Row2.y * mat.Row1.x + Row2.z * mat.Row2.x + Row2.w * mat.Row3.x,
        Row2.x * mat.Row0.y + Row2.y * mat.Row1.y + Row2.z * mat.Row2.y + Row2.w * mat.Row3.y,
        Row2.x * mat.Row0.z + Row2.y * mat.Row1.z + Row2.z * mat.Row2.z + Row2.w * mat.Row3.z,
        Row2.x * mat.Row0.w + Row2.y * mat.Row1.w + Row2.z * mat.Row2.w + Row2.w * mat.Row3.w
    );
    Row3 = Vector4(
        Row3.x * mat.Row0.x + Row3.y * mat.Row1.x + Row3.z * mat.Row2.x + Row3.w * mat.Row3.x,
        Row3.x * mat.Row0.y + Row3.y * mat.Row1.y + Row3.z * mat.Row2.y + Row3.w * mat.Row3.y,
        Row3.x * mat.Row0.z + Row3.y * mat.Row1.z + Row3.z * mat.Row2.z + Row3.w * mat.Row3.z,
        Row3.x * mat.Row0.w + Row3.y * mat.Row1.w + Row3.z * mat.Row2.w + Row3.w * mat.Row3.w
    );

    return *this;
}

Vector4 Matrix4x4::Multiply(const Vector4& vec)
{
    const float x = vec.x * Row0.x + vec.y * Row0.y + vec.z * Row0.z + vec.w * Row0.w;
    const float y = vec.x * Row1.x + vec.y * Row1.y + vec.z * Row1.z + vec.w * Row1.w;
    const float z = vec.x * Row2.x + vec.y * Row2.y + vec.z * Row2.z + vec.w * Row2.w;
    const float w = vec.x * Row3.x + vec.y * Row3.y + vec.z * Row3.z + vec.w * Row3.w;

    return Vector4(x, y, z, w);
}

ostream& operator<<(ostream& stream, const Matrix4x4& matrix)
{
	std::cout << "[ " << matrix.Row0.x << ", " << matrix.Row0.y << ", " << matrix.Row0.z << ", " << matrix.Row0.w << " ]" << std::endl;
	std::cout << "[ " << matrix.Row1.x << ", " << matrix.Row1.y << ", " << matrix.Row1.z << ", " << matrix.Row1.w << " ]" << std::endl;
	std::cout << "[ " << matrix.Row2.x << ", " << matrix.Row2.y << ", " << matrix.Row2.z << ", " << matrix.Row2.w << " ]" << std::endl;
	std::cout << "[ " << matrix.Row3.x << ", " << matrix.Row3.y << ", " << matrix.Row3.z << ", " << matrix.Row3.w << " ]" << std::endl;

    return stream;
}
