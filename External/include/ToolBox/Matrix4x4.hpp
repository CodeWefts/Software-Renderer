#pragma once
#include <vector>
#include <iostream>

#include "vector.hpp"
#include"Vector4.hpp"

class Matrix4x4
{
public:
	Vector4 Row0;
	Vector4 Row1;
	Vector4 Row2;
	Vector4 Row3;


	vector<vector<float> > m_matrix;

	Matrix4x4();
	Matrix4x4(
	float r00, float r01, float r02, float r03,
	float r10, float r11, float r12, float r13,
	float r20, float r21, float r22, float r23,
	float r30, float r31, float r32, float r33
	);
	Matrix4x4(Vector4 row0, Vector4 row1, Vector4 row2, Vector4 row3);

	Matrix4x4 operator=(const Matrix4x4& matrix);
	friend ostream& operator<<(ostream& stream, const Matrix4x4& matrix);
	Matrix4x4& Multiply(const Matrix4x4& mat);
	Vector4 Multiply(const Vector4& vec);
};
