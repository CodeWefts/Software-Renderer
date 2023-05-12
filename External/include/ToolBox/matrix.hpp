#pragma once
#include <vector>
#include <iostream>

#include"Matrix4x4.hpp"


using namespace std;

class Matrix
{
private:
	unsigned int m_row;
	unsigned int m_column;

public:
	vector<vector<float_t> > m_matrix;
	Matrix(unsigned int m_matrixRow, unsigned int m_matrixColumn, float_t defaultValue = 0);
	Matrix(const Matrix& copiedMatrix);
	Matrix(vector<vector<float_t> > matrix);
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
	float_t detMatrix();
	float_t traceMatrix();
	Matrix augmentedMatrix(Matrix& matrix2);
	Matrix identity();
	Matrix swapMatrix(int indexMin, int indexMax);
	Matrix alphaCalculate(float_t indexPivot, int indexAlpha);
	float_t maxIndex(int indexRow, int indexColumn);
	Matrix pivotGauss();
	Matrix reversedMatrix();
	Matrix rotateMatrix2(float_t angle);
	static Matrix rotateMatrix3(float_t x, float_t y, float_t z, float_t angle);
	Matrix scaleMatrix2(Vector& vector);
	Matrix scaleMatrix3(Vector& vector);
	static Matrix4x4 TRS(Vector& angle, Vector& transVect, Vector& scaleVect);
};

class Matrix2x2
{
	Matrix2x2();
	Matrix2x2(
		float_t r00, float_t r01,
		float_t r10, float_t r11
	);
};

class Matrix3x3
{
	Matrix3x3();
	Matrix3x3(
		float_t r00, float_t r01, float_t r02,
		float_t r10, float_t r11, float_t r12,
		float_t r20, float_t r21, float_t r22
	);
};







