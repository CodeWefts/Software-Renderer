#pragma once
#include <vector>
#include <iostream>
#define _USE_MATH_DEFINES

using namespace std;

class Vector
{
private:
	unsigned int size;

public:
	vector<float> m_vector; //TO DO : CHANGE TO FLOAT
	Vector(unsigned int m_vectorSize, double defaultValue);
	Vector();
	Vector(const std::initializer_list<float>& values);
	~Vector();
	
	Vector operator=(const Vector& vector);
	Vector operator+(const Vector& vector);
	Vector operator-(const Vector& vector);
	friend ostream& operator<<(ostream& os, const Vector& vector);

	Vector oppositeVec();
	static double scalProduct(const Vector& vector1, const Vector& vector2);
	//double angleVector(Vector vector1, Vector vector2);
	double normVector() const;
	static double vect2Product(const Vector& vector1, const Vector& vector2);
	static Vector vect3Product(const Vector& vector1, const Vector& vector2);
	static double angleVector(Vector vector1, Vector vector2);
	static double distVector(Vector vector1, Vector vector2);
	Vector NormalizeVector() const;
};




class Vector2
{
public:
	float x;
	float y;

	Vector2();
	Vector2(float x, float y);
};
