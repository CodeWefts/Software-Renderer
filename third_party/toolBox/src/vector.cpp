#include "vector.h"

ostream& operator<<(ostream& stream, const Vector& vector)
{
	stream << "\n";
	for (int i = 0; i < vector.size; i++)
	{
		stream << vector.value[i] << " ";

	}
	stream << "\n";
	return stream;
}
Vector operator+( const Vector& vector1,  const Vector& vector2)
{
	assert(vector1.size == vector2.size);
	Vector sumVector(vector1.size);

	for (int i = 0; i < vector1.size; i++)
		sumVector.value[i] =  vector1.value[i] + vector2.value[i];

	return sumVector;
}
Vector operator-(const Vector& vector1, const Vector& vector2)
{
	assert(vector1.size == vector2.size);
	Vector sumVector(vector1.size);

	for (int i = 0; i < vector1.size; i++)
		sumVector.value[i] = vector1.value[i] - vector2.value[i];

	return sumVector;
}


double normVector(Vector vector)
{
	double sum = pow(vector.value[0], 2);

	for (int i = 1; i < vector.size; i++)
	{
		sum += pow(vector.value[i], 2);
	}

	double norm = sqrt(sum);
	cout << "NORM : " << norm;
	cout << "\n";

	return norm;
}

Vector oppositeVector(Vector vector1)
{
	for (int i = 0; i < vector1.size; i++)
		vector1.value[i] = -vector1.value[i];

	cout << "OPPOSITE VECTOR : " << vector1 << endl;
	return vector1;
}

double scalarVector(Vector vector1, Vector vector2)
{
	assert(vector1.size == vector2.size);
	double scalarVector = 0;

	for (int i = 0; i < vector1.size; i++)
		scalarVector += vector1.value[i] * vector2.value[i];

	return scalarVector;
}

double angleVector(Vector vector1, Vector vector2)
{
	return (acosf(scalarVector(vector1, vector2) / (normVector(vector1) * normVector(vector2)))) * (180/M_PI);
}

double crossVector2(Vector vector1, Vector vector2)
{
	assert(vector1.size == vector2.size);
	assert(vector1.size == 2);
	return vector1.value[0] * vector2.value[1] - vector1.value[1] * vector2.value[0];

}

Vector crossVector3(Vector vector1, Vector vector2)
{
	assert(vector1.size == vector2.size);
	assert(vector1.size == 3);

	Vector v1(vector1.size);
	v1.value[0] = vector1.value[1] * vector2.value[2] - vector1.value[2] * vector2.value[1];
	v1.value[1] = vector1.value[2] * vector2.value[0] - vector1.value[0] * vector2.value[2];
	v1.value[2] = vector1.value[0] * vector2.value[1] - vector1.value[1] * vector2.value[0];

	return v1;
}

double distVector(Vector vector1, Vector vector2)
{
	assert(vector1.size == vector2.size);
	return normVector(vector2 - vector1);
}


Vector::Vector(int size)
{
	this->size = size;

	for (int i = 0; i < size; i++)
	{
		this->value.push_back(0.f);
	}
}



void testVector()
{
	/*
	cout << "\n ================  VECTOR  ====================" << endl;

	// Create Vector with M elements
	Vector vec(3);
	Vector vec1(3);
	Vector vec2(2);
	Vector vec3(2);

	vec.value = { 1,2,3 };
	vec1.value = { 1,5,7 };
	vec2.value = { 1,2 };
	vec3.value = { 1,2 };

	cout <<"VECTOR : " << vec;
	cout << "\n";

	double norm = normVector(vec);
	cout << "\n";

	Vector sumVector(4);
	sumVector = vec + vec1;

	cout << "SUM : " << sumVector << endl;

	double scalarVec = scalarVector(vec, vec1);
	cout << "SCALAR V1 V2 : " << scalarVec << endl;
	cout << "\n";

	double crossVector2D = crossVector2(vec2, vec3);
	cout << "CROSS V1 V2 (2D) : " << crossVector2D << endl;
	cout << "\n";

	Vector crossVector3D = crossVector3(vec, vec1);
	cout << "CROSS V1 V2 (3D): " << crossVector3D;
	cout << "\n";

	double angle = angleVector(vec, vec1);
	cout << "ANGLE BETWEEN V1 & V2 : " << angle << endl;
	cout << "\n";

	double angle1 = angleVector(vec2, vec3);
	cout << "ANGLE BETWEEN V3 & V4 : " << angle1 << endl;
	cout << "\n";

	double distVec = distVector(vec, vec1);
	cout << "DISTANCE BETWEEN V1 & V2 : " << distVec << endl;
	cout << "\n";

	oppositeVector(vec);*/


}