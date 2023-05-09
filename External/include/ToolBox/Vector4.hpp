#pragma once


class Vector4
{
public:
	float w;
	float x;
	float y;
	float z;

	Vector4();
	Vector4(float x, float y, float z, float w);
	Vector4(float wxyz);
	float& operator[](int i);
	Vector4 operator*(const Vector4& vec);
	Vector4 operator*(const float x);
	float operator[](int i) const;
};