#pragma once
#include <vector>
#include <iostream>

#include "vector.hpp"
#include"Vector4.hpp"

class Matrix4x4
{
public:

	vector<vector<float>> value;

	Matrix4x4();
	friend ostream& operator<<(ostream& stream, const Matrix4x4& matrix);
	Matrix4x4 operator*(const Matrix4x4& matrix);
	Vector4 operator*(const Vector4& vect);
	
	Matrix4x4 IdentityMatrix();
};
