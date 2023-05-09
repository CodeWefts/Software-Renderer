#include "matrix.hpp"

#include <assert.h>

using namespace std;


Matrix::Matrix(unsigned int m_matrixRow, unsigned int m_matrixColumn, double defaultValue)
{
	m_row = m_matrixRow;
	m_column = m_matrixColumn;
	for (int i = 0; i < m_row; i++)
	{
		vector<double> tab(m_column, defaultValue);
		m_matrix.push_back(tab);
	}
}

Matrix::Matrix(const Matrix& copiedMatrix)
{
	m_matrix = copiedMatrix.m_matrix;
	m_row = copiedMatrix.m_row;
	m_column = copiedMatrix.m_column;
}

Matrix::Matrix(vector<vector<double> > matrix)
{
	m_row = matrix.size();
	m_column = matrix[0].size();
	m_matrix = matrix;
}

Matrix::~Matrix()
{

}

Matrix Matrix::operator=(const Matrix& otherMatrix)
{
	m_column = otherMatrix.m_column;
	m_row = otherMatrix.m_row;
	m_matrix = otherMatrix.m_matrix;
	return *this;
}

Matrix Matrix::operator+(const Matrix& otherMatrix)
{
	assert(m_row == otherMatrix.m_row && m_column == otherMatrix.m_column);
	Matrix newMatrix(*this);
	for (int i = 0; i < m_row; i++)
	{
		for (int j = 0; j < m_column; j++)
		{
			newMatrix.m_matrix[i][j] += otherMatrix.m_matrix[i][j];
		}
	}
	return newMatrix;
}

Matrix Matrix::operator-(const Matrix& otherMatrix)
{
	assert(m_row == otherMatrix.m_row && m_column == otherMatrix.m_column);
	Matrix newMatrix(*this);
	for (int i = 0; i < m_row; i++)
	{
		for (int j = 0; j < m_column; j++)
		{
			newMatrix.m_matrix[i][j] -= otherMatrix.m_matrix[i][j];
		}
	}
	return newMatrix;
}

Matrix::Matrix()
{

}

Matrix Matrix::operator*(const Matrix& otherMatrix)
{
	assert(m_column == otherMatrix.m_row);
	Matrix newMatrix(m_row, otherMatrix.m_column, 0);
	for (int i = 0; i < m_row; i++)
	{
		for (int j = 0; j < otherMatrix.m_column; j++)
		{
			for (int h = 0; h < m_column; h++)
			{
				newMatrix.m_matrix[i][j] += m_matrix[i][h] * otherMatrix.m_matrix[h][j];
			}
		}
	}
	return newMatrix;
}

Matrix& Matrix::operator+=(const Matrix& otherMatrix)
{
	assert(m_row == otherMatrix.m_row && m_column == otherMatrix.m_column);
	for (int i = 0; i < m_row; i++)
	{
		for (int j = 0; j < m_column; j++)
		{
			m_matrix[i][j] += otherMatrix.m_matrix[i][j];
		}
	}
	return *this;
}

Matrix& Matrix::operator-=(const Matrix& otherMatrix)
{
	assert(m_row == otherMatrix.m_row && m_column == otherMatrix.m_column);
	for (int i = 0; i < m_row; i++)
	{
		for (int j = 0; j < m_column; j++)
		{
			m_matrix[i][j] -= otherMatrix.m_matrix[i][j];
		}
	}
	return *this;
}

Matrix& Matrix::operator*=(const Matrix& otherMatrix)
{
	assert(m_column == otherMatrix.m_row);
	Matrix newMatrix(m_row, otherMatrix.m_column, 0);
	for (int i = 0; i < m_row; i++)
	{
		for (int j = 0; j < otherMatrix.m_column; j++)
		{
			for (int h = 0; h < m_column; h++)
			{
				newMatrix.m_matrix[i][j] += m_matrix[i][h] * otherMatrix.m_matrix[h][j];
			}
		}
	}
	*this = newMatrix;
	return *this;
}

ostream & operator<<(ostream & os, const Matrix & matrix)
{
	for (int i = 0; i < matrix.m_row; i++)
	{
		os << "[";
		for (int j = 0; j < matrix.m_column; j++)
		{
			double value = matrix.m_matrix[i][j];
			os << value;
			if (j < matrix.m_column - 1)
			{
				os << ", ";
			}
		}
		os << "]\n" ;
	}
	return os;
}

Matrix Matrix::oppositeMatrix()
{
	Matrix newMatrix(*this);
	for (int i = 0; i < m_row; i++)
	{
		for (int j = 0; j < m_column; j++)
		{
			newMatrix.m_matrix[i][j] =  -m_matrix[i][j];
		}
	}
	return newMatrix;
}

Matrix Matrix::scalarMultiply(int scal)
{
	for (int i = 0; i < m_row; i++)
	{
		for (int j = 0; j < m_column; j++)
		{
			m_matrix[i][j] *= scal;
		}
	}
	return *this;
}

Matrix Matrix::transMatrix()
{
	Matrix newMatrix(*this);
	newMatrix.m_column = m_row;
	newMatrix.m_row = m_column;
	for (int i = 0; i < m_row; i++)
	{
		for (int j = 0; j < m_column; j++)
		{
			m_matrix[i][j] = newMatrix.m_matrix[j][i];
		}
	}
	return *this;
}

Vector Matrix::diagMatrix()
{
	Vector diag(m_row, 0);
	for (int i = 0; i < m_row; i++)
	{
		for (int j = 0; j < m_column; j++)
		{
			if (i == j)
			{
				diag.m_vector[i] = m_matrix[i][j];
			}
		}
	}
	return diag;
}

double Matrix::detMatrix()
{
	assert(m_row == m_column);
	double det = 0;

	if (m_row == 2)
	{
		return m_matrix[0][0] * m_matrix[1][1] - m_matrix[1][0] * m_matrix[0][1];
	}
	for (int i = 0; i < m_row; i++)
	{
		vector<vector<double> > tab1;
		for (int currentRow = 0; currentRow < m_row; currentRow++)
		{
			vector<double> tab2;
			if (currentRow != i)
			{
				for (int j = 1; j < m_column; j++)
				{
					tab2.push_back(m_matrix[currentRow][j]);
				}
				tab1.push_back(tab2);
			}
		}
		Matrix newMatrix(tab1);
		if (i % 2 == 0)
		{
			det += m_matrix[i][0] * newMatrix.detMatrix();
		}

		else
		{
			det -= m_matrix[i][0] * newMatrix.detMatrix();
		}
	}
	return det;
}

double Matrix::traceMatrix()
{
	double trace = 0;
	Vector vec = diagMatrix();
	
	for (int i = 0; i < m_row; i++)
	{
		trace += vec.m_vector[i];
	}
	return trace;
}

Matrix Matrix::augmentedMatrix(Matrix& matrix2)
{
	assert(m_row == matrix2.m_row);
	Matrix newMatrix(*this);

	for (int i = 0; i < m_row; i++)
	{
		for (int j = 0; j < matrix2.m_column; j++)
		{
			newMatrix.m_matrix[i].push_back(matrix2.m_matrix[i][j]);
		}
		newMatrix.m_column = newMatrix.m_matrix[0].size();
	}
	return newMatrix;
}

Matrix Matrix::identity()
{
	assert(m_row == m_column);

	for (int i = 0; i < m_row; i++)
	{
		for (int j = 0; j < m_column; j++)
		{
			if (i == j)
			{
				m_matrix[i][j] = 1;
			}
			else
				m_matrix[i][j];
		}
	}
	return *this;
}

// CALCUL PIVOT DE GAUSS ---------------------------------------------

Matrix Matrix::swapMatrix(int indexMin, int indexMax)
{
	Matrix newMatrix(*this);

	for (int i = 0; i < m_row; i++)
	{
		if (m_matrix[i] == m_matrix[indexMin])
			newMatrix.m_matrix[i] = m_matrix[indexMax];

		else if (m_matrix[i] == m_matrix[indexMax])
			newMatrix.m_matrix[i] = m_matrix[indexMin];

		else
			newMatrix.m_matrix[i] = m_matrix[i];
	}
	return newMatrix;
}

Matrix Matrix::alphaCalculate(double indexPivot, int indexAlpha)
{
	Matrix matrix1(1, m_column), matrix2(1, m_column);
	matrix2.m_matrix[0] = m_matrix[indexPivot];

	for (int i = 0; i < m_row; i++)
	{
		if (i != indexPivot)
		{
			double alpha = m_matrix[i][indexAlpha];
			matrix1.m_matrix[0] = m_matrix[i];
			matrix1 = matrix1 - (matrix2.scalarMultiply(alpha));
			m_matrix[i] = matrix1.m_matrix[0];
		}
	}
	return *this;
}

double Matrix::maxIndex(int indexRow, int indexColumn)
{
	double max = indexRow;
	for (int i = indexRow; i < m_row; i++)
	{
		if (m_matrix[indexRow][indexColumn] < abs(m_matrix[i][indexColumn]))
		{
			max = i;
		}
	}
	return max;
}

Matrix Matrix::pivotGauss()
{
	int h = 0;
	int j = 0;
	for (int i = 0; i < m_row; i++)
	{
		double index = maxIndex(i, j);
		while (m_matrix[index][j] == 0)
		{
			if (j == m_column - 1) { return *this; }
			j++;
			index = maxIndex(i, j);
		}
		*this = swapMatrix(i, index);
		double normalize = m_matrix[i][j];
		cout << *this << endl;
		if (normalize != 0)
		{
			for (int j = 0; j < m_column; j++)
			{
				m_matrix[i][j] = m_matrix[i][j] / normalize;
			}
			h++;
		}

		cout <<"aaa111111111aa" << *this << endl;
		*this = alphaCalculate(i, j);
		cout << "aaa" << *this << endl;

		cout << i << endl;
		j++;
	}
	return *this;
}

//-------------------------------------------------------------------------


Matrix Matrix::reversedMatrix()
{
	assert(m_row == m_column);
	Matrix newMatrix(m_row, m_column);
	Matrix newEndMatrix(m_row, m_column);
	newMatrix = newMatrix.identity();
	newMatrix = augmentedMatrix(newMatrix);
	newMatrix = newMatrix.pivotGauss();

	int h = 0;

	for (int i = 0; i < m_row; i++)
	{
		h = 0;
		for (int j = newMatrix.m_column / 2; j < newMatrix.m_column; j++)
		{
			newEndMatrix.m_matrix[i][h] = newMatrix.m_matrix[i][j];
			h++;
		}
	}
	return newEndMatrix;
}

//Matrice TRS-------------------------------------------------------------------------------

Matrix Matrix::rotateMatrix2(double angle)
{
	Matrix newMatrix(2, 2);
	newMatrix.m_matrix = { {cosf(angle), -sinf(angle), sinf(angle), cosf(angle)} };
	return newMatrix;
}

Matrix Matrix::rotateMatrix3(double x, double y, double z, double angle)
{
	Matrix newMatrix(3, 3);
	newMatrix.m_matrix =
	{
		{x * x * (1 - cosf(angle)) + cosf(angle), y * x * (1 - cosf(angle)) - z * sinf(angle), z * x * (1 - cosf(angle)) + y * sinf(angle)},
		{x * y * (1 - cosf(angle)) + z * sinf(angle), y * y * (1 - cosf(angle)) + cosf(angle), z * y * (1 - cosf(angle)) - x * sinf(angle)},
		{x * z * (1 - cosf(angle)) + y * sinf(angle), y * z * (1 - cosf(angle)) - x * sinf(angle), z * z * (1 - cosf(angle)) + cosf(angle)}
	};

	return newMatrix;
}

Matrix Matrix::scaleMatrix2(Vector& vector)
{
	Matrix matrix(2, 2);
	matrix.m_matrix = { {vector.m_vector[0], 0}, {0, vector.m_vector[1]} };

	return matrix;
}

Matrix Matrix::scaleMatrix3(Vector& vector)
{
	Matrix matrix(3, 3);
	matrix.m_matrix = { {vector.m_vector[0], 0, 0}, {0, vector.m_vector[1], 0}, {0, 0, vector.m_vector[2]} };
	return matrix;
}

Matrix Matrix::TRS(Vector& angle, Vector& transVect, Vector& scaleVect, Vector& axis)
{
	Matrix rotate(3, 3);
	Matrix T(4, 4);
	Matrix R(4, 4);
	Matrix S(4, 4);

	T = T.identity();
	T.m_matrix[0][3] = transVect.m_vector[0];
	T.m_matrix[1][3] = transVect.m_vector[1];
	T.m_matrix[2][3] = transVect.m_vector[2];

	Matrix rAxisX(3, 3), rAxisY(3, 3), rAxisZ(3, 3);
	rAxisX = rotateMatrix3(axis.m_vector[0], 0, 0, angle.m_vector[0]);
	rAxisY = rotateMatrix3(0, axis.m_vector[1], 0, angle.m_vector[1]);
	rAxisZ = rotateMatrix3(0, 0, axis.m_vector[2], angle.m_vector[2]);

	rotate = rAxisZ * (rAxisX * rAxisY);

	R.m_matrix =
	{
		{rotate.m_matrix[0][0], rotate.m_matrix[0][1], rotate.m_matrix[0][2], 0},
		{rotate.m_matrix[1][0], rotate.m_matrix[1][1], rotate.m_matrix[1][2], 0},
		{rotate.m_matrix[2][0], rotate.m_matrix[2][1], rotate.m_matrix[2][2], 0},
		{0, 0, 0, 1}
	};

	S = S.identity();
	S.m_matrix[0][0] = scaleVect.m_vector[0];
	S.m_matrix[1][1] = scaleVect.m_vector[1];
	S.m_matrix[2][2] = scaleVect.m_vector[2];

	return (T * R) * S;
}



Matrix3x3::Matrix3x3()
{

}

Matrix3x3::Matrix3x3(
	float r00, float r01, float r02,
	float r10, float r11, float r12,
	float r20, float r21, float r22
)
{

}

Matrix2x2::Matrix2x2()
{

}

Matrix2x2::Matrix2x2(
	float r00, float r01,
	float r1, float r11
)
{

}

