#include "vector.hpp"
#include "assert.h"
#include <math.h>

using namespace std;

Vector::Vector(unsigned int m_vectorSize, double defaultValue)
{
	size = m_vectorSize;
	m_vector = vector<float>(size, defaultValue);
}

Vector::Vector(const std::initializer_list<float>& values)
{
	m_vector.resize(values.size());
	const float* it = values.begin();

	for (int i = 0; i < values.size(); i++)
	{
		m_vector[i] = it[i];
	}
}

Vector::Vector()
{
}


Vector::~Vector()
{

}

Vector Vector::operator=(const Vector& otherVector)
{
	size = otherVector.size;
	m_vector = otherVector.m_vector;
	return *this;
}

Vector Vector::operator+(const Vector& vector)
{
	assert(size == vector.size);
	Vector newVector(*this);
	for (int i = 0; i < size; i++)
	{
		newVector.m_vector[i] += vector.m_vector[i];
	}
	return newVector;
}

Vector Vector::operator-(const Vector& vector)
{
	assert(size == vector.size);
	Vector newVector(*this);
	for (int i = 0; i < size; i++)
	{
		newVector.m_vector[i] -= vector.m_vector[i];
	}
	return newVector;
}

ostream& operator<<(ostream& os, const Vector& vector)
{
	for (int i = 0; i < vector.size; i++)
	{
		os << "[";
		double value = vector.m_vector[i];
		os << value;
		os << "]\n";
	}
	return os;
}

Vector Vector::oppositeVec()
{
	Vector newVector(*this);
	for (int i = 0; i < newVector.size; i++)
	{
		newVector.m_vector[i] = -newVector.m_vector[i];
	}
	return newVector;
}

double Vector::scalProduct(const Vector& vector1, const Vector& vector2)
{
	assert(vector1.size == vector2.size);
	double product = 0;
	for (int i = 0; i < vector1.size; i++)
	{
		product += vector1.m_vector[i] * vector2.m_vector[i];
	}
	return product;
}

double Vector::normVector() const
{
	double norm = 0;
	for (int i = 0; i < size; i++)
	{
		norm += m_vector[i] * m_vector[i];
	}
	return sqrt(norm);
}

double Vector::vect2Product(const Vector& vector1, const Vector& vector2)
{
	assert(vector1.size == vector2.size && vector1.size == 2);
	double result = 0;
	result += vector1.m_vector[0] * vector2.m_vector[1] - vector1.m_vector[1] * vector2.m_vector[0];
	return result;
}

Vector Vector::vect3Product(const Vector& vector1, const Vector& vector2)
{
	assert(vector1.size == vector2.size && vector1.size == 3);
	Vector result(3, 1);
	result.m_vector[0] = (vector1.m_vector[1] * vector2.m_vector[2] - vector1.m_vector[2] * vector2.m_vector[1]);
	result.m_vector[1] = (vector1.m_vector[2] * vector2.m_vector[0] - vector1.m_vector[0] * vector2.m_vector[2]);
	result.m_vector[2] = (vector1.m_vector[0] * vector2.m_vector[1] - vector1.m_vector[1] * vector2.m_vector[0]);
	return result;
}

double Vector::angleVector(Vector vector1, Vector vector2)
{
	return (acosf(Vector::scalProduct(vector1, vector2) / (vector1.normVector() * vector2.normVector()))) * (180 / M_PI);
}

double Vector::distVector(Vector vector1, Vector vector2)
{
	assert(vector1.size == vector2.size);
	double dist = 0;
	dist = pow(vector2.m_vector[0] - vector1.m_vector[0], 2) + pow(vector2.m_vector[1] - vector1.m_vector[1], 2) + pow(vector2.m_vector[2] - vector1.m_vector[2], 2);
	return sqrt(dist);
}

Vector Vector::NormalizeVector() const
{
	Vector result;
	for (int i = 0; i < size; i++)
	{
		result.m_vector[i] = m_vector[i] / normVector();
	}
	return result;
}



Vector2::Vector2()
	:x(0), y(0)
{

}

Vector2::Vector2(float x, float y)
	:x(x), y(y)
{

}