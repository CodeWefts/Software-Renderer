#pragma once
#include "vector.h"


class Matrix
{
private:

public:
	int sizeM , sizeN;

	vector<vector<double>> value;

	Matrix(int sizeM , int sizeN);
};

ostream& operator<<(ostream& stream, const Matrix& matrix);
Matrix operator+(const Matrix& matrix1, const Matrix& matrix2);
Matrix operator*(const Matrix& matrix,const double scalar );
Matrix operator*(const Matrix& matrix1, const Matrix& matrix2);
Matrix operator/(const Matrix& matrix1, const Matrix& matrix2);
Matrix operator/(const Matrix& matrix,const double scalar);
Matrix operator-(const Matrix& matrix1, const Matrix& matrix2);

void testMatrix();
Matrix oppositeMatrix(Matrix& matrix);
Vector diagonalMatrix(Matrix& matrix); 
double traceMatrix(Matrix& matrix);
Matrix transMatrix(Matrix& matrix);
Matrix UpRightMatrix(Matrix& matrix, Matrix& matrix1);
double detMatrix(Matrix& matrix);

double maxIndex(Matrix& matrix, int indexM, int indexN);
Matrix swapMatrix(Matrix& matrix, int indexFirst , int indexMax);
Matrix alphaCalcMatrix(Matrix& matrix, double indexPivot, int indexAlpha);
Matrix pivotMatrix(Matrix& matrix);
Matrix identityMatrix(Matrix& matrix);
Matrix reverseMatrix(Matrix& matrix);

Matrix rotationMatrix2X2(double angle);
Matrix rotationMatrix3X3(double indexX, double indexY, double indexZ, double angle);

Matrix scalingMatrix2X2(Vector& vector);
Matrix scalingMatrix3X3(Vector& vector);

Matrix TRS(Vector& angle, Vector& vectorTrans, Vector& vectorScaling, Vector& axes);

