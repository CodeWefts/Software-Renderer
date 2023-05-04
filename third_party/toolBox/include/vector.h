#pragma once
#include <iostream>
#include <vector>
#define _USE_MATH_DEFINES
#include <math.h>
#include <cassert>

using namespace std;

class Vector
{
private:

public :

	int size;
	vector<double> value;
	Vector(int size);

};
ostream& operator<<(ostream& stream, const Vector& vector);
Vector operator+(const Vector &vector1, const Vector &vector2);
Vector operator-(const Vector& vector1, const Vector& vector2);

double normVector(Vector vector); 
Vector oppositeVector(Vector vector1);
double scalarVector(Vector vector1, Vector vector2); 
double angleVector(Vector vector1, Vector vector2);
double crossVector2(Vector vector1, Vector vector2);
Vector crossVector3(Vector vector1, Vector vector2);
double distVector(Vector vector1, Vector vector2);

void testVector();