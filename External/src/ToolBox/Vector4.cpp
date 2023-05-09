#include "Vector4.hpp"
#include <assert.h>


Vector4::Vector4()
	:w(0), x(0), y(0), z(0)
{

}

Vector4::Vector4(float x, float y, float z, float w)
	:x(x), y(y), z(z), w(w)
{

}

Vector4::Vector4(float wxyz)
	:x(wxyz), y(wxyz), z(wxyz), w(wxyz)
{

}

float& Vector4::operator[](int i)
{
	assert(i >= 0 && i <= 3 && "Vector 4 subscript out of range");

	return (&x)[i];
}

float Vector4::operator[](int i) const
{
	assert(i >= 0 && i <= 3 && "Vector 4 subscript out of range");

	return (&x)[i];
}

Vector4 Vector4::operator*(const Vector4& vec)
{
	return Vector4(vec.x * x, vec.y * y, vec.z * z, vec.w * w);
}

Vector4 Vector4::operator*(const float x)
{
	return Vector4(this->x * x, this->y * y, this->z * z, this->w * w);
}