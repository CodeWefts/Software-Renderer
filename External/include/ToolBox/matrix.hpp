#pragma once
#include <vector>
#include <iostream>

#include "vector.hpp"

using namespace std;

class Matrix
{
private:
	unsigned int m_row;
	unsigned int m_column;

public:
	vector<vector<double> > m_matrix;
	Matrix(unsigned int m_matrixRow, unsigned int m_matrixColumn, double defaultValue = 0);
	Matrix(const Matrix& copiedMatrix);
	Matrix(vector<vector<double> > matrix);
	Matrix();
	~Matrix();

	Matrix operator=(const Matrix& matrix);
	Matrix operator+(const Matrix& matrix);
	Matrix operator-(const Matrix& matrix);
	Matrix operator*(const Matrix& matrix);
	Matrix& operator+=(const Matrix& matrix);
	Matrix& operator-=(const Matrix& matrix);
	Matrix& operator*=(const Matrix& matrix);
	friend ostream& operator<<(ostream& os, const Matrix& matrix);

	Matrix oppositeMatrix();
	Matrix transMatrix();
	Matrix scalarMultiply(int scal);
	Vector diagMatrix();
	double detMatrix();
	double traceMatrix();
	Matrix augmentedMatrix(Matrix& matrix2);
	Matrix identity();
	Matrix swapMatrix(int indexMin, int indexMax);
	Matrix alphaCalculate(double indexPivot, int indexAlpha);
	double maxIndex(int indexRow, int indexColumn);
	Matrix pivotGauss();
	Matrix reversedMatrix();
	Matrix rotateMatrix2(double angle);
	Matrix rotateMatrix3(double x, double y, double z, double angle);
	Matrix scaleMatrix2(Vector& vector);
	Matrix scaleMatrix3(Vector& vector);
	Matrix TRS(Vector& angle, Vector& transVect, Vector& scaleVect, Vector& axis);
};

class Matrix2x2
{
	Matrix2x2();
	Matrix2x2(
		float r00, float r01,
		float r10, float r11
	);
};

class Matrix3x3
{
	Matrix3x3();
	Matrix3x3(
		float r00, float r01, float r02,
		float r10, float r11, float r12,
		float r20, float r21, float r22
	);
};







