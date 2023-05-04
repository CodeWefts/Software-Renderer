#include "matrix.h"

ostream& operator<<(ostream& stream, const Matrix& matrix)
{
	for (int i = 0; i < matrix.sizeM; i++)
	{
		stream << "\n";
		for (int j = 0; j < matrix.sizeN; j++)
			stream << matrix.value[i][j] << " ";
	}
	stream << "\n";
	return stream;
}
Matrix operator+(const Matrix& matrix1, const Matrix& matrix2)
{
	assert(matrix1.sizeM == matrix2.sizeM);
	assert(matrix1.sizeN == matrix2.sizeN);

	Matrix sumMatrix(matrix1.sizeM, matrix1.sizeN);

	for (int i = 0; i < sumMatrix.sizeM; i++)
	{
		for (int j = 0; j < sumMatrix.sizeN; j++)
		{
			sumMatrix.value[i][j] = matrix1.value[i][j] + matrix2.value[i][j];
		}
	}
	
	return sumMatrix;
}
Matrix operator*(const Matrix& matrix,const double scalar )
{
	Matrix multipMatrix(matrix.sizeM, matrix.sizeN);

	for (int i = 0; i < multipMatrix.sizeM; i++)
	{
		for (int j = 0; j < multipMatrix.sizeN; j++)
		{
			multipMatrix.value[i][j] = matrix.value[i][j] * scalar;
		}
	}

	return multipMatrix;
}
Matrix operator*(const Matrix& matrix1, const Matrix& matrix2)
{
	assert(matrix1.sizeN == matrix2.sizeM, " Impossible");

	Matrix multipMatrix(matrix1.sizeM, matrix2.sizeN);

	for (int i = 0; i < multipMatrix.sizeM; i++)
	{
		for (int j = 0; j < multipMatrix.sizeN; j++)
		{
			for (int k = 0; k < matrix1.sizeN; k++)
			{
				multipMatrix.value[i][j] += matrix1.value[i][k] * matrix2.value[k][j];
			}
		} 
	}

	return multipMatrix;
}
Matrix operator/(const Matrix& matrix1, const Matrix& matrix2)
{
	assert(matrix1.sizeM == matrix2.sizeM);
	assert(matrix1.sizeN == matrix2.sizeN);

	Matrix sumMatrix(matrix1.sizeM, matrix1.sizeN);

	for (int i = 0; i < sumMatrix.sizeM; i++)
	{
		for (int j = 0; j < sumMatrix.sizeN; j++)
		{
			sumMatrix.value[i][j] = matrix1.value[i][j] / matrix2.value[i][j];
		}
	}

	return sumMatrix;
}
Matrix operator/(const Matrix& matrix,const double scalar )
{
	Matrix multipMatrix(matrix.sizeM, matrix.sizeN);

	for (int i = 0; i < multipMatrix.sizeM; i++)
	{
		for (int j = 0; j < multipMatrix.sizeN; j++)
		{
			multipMatrix.value[i][j]= matrix.value[i][j] / scalar;
		}
	}
	return multipMatrix;
}
Matrix operator-(const Matrix& matrix1, const Matrix& matrix2)
{
	assert(matrix1.sizeM == matrix2.sizeM);
	assert(matrix1.sizeN == matrix2.sizeN);

	Matrix sumMatrix(matrix1.sizeM, matrix1.sizeN);

	for (int i = 0; i < sumMatrix.sizeM; i++)
	{
		for (int j = 0; j < sumMatrix.sizeN; j++)
		{
			sumMatrix.value[i][j] = matrix1.value[i][j] - matrix2.value[i][j];
		}
	}
	return sumMatrix;
}



Matrix::Matrix(int sizeM , int sizeN)
{
	this->sizeM = sizeM;
	this->sizeN = sizeN;

	for (int i = 0; i < sizeM; i++)
			this->value.push_back(vector<double>(sizeN, 0.f));
}

Matrix oppositeMatrix(Matrix& matrix)
{
	for (int i = 0; i < matrix.sizeM; i++)
		for (int j = 0; j < matrix.sizeN; j++)
			matrix.value[i][j] = -matrix.value[i][j];

	return matrix;
}

Vector diagonalMatrix(Matrix& matrix)
{
	assert(matrix.sizeM == matrix.sizeN);

	Vector diag(matrix.sizeM);

	for (int i = 0; i < matrix.sizeM; i++)
		for (int j = 0; j < matrix.sizeN; j++)
		{
			if (i == j)
				diag.value[i] = matrix.value[i][j];
		}

	return diag;
}

double traceMatrix(Matrix& matrix)
{
	assert(matrix.sizeM == matrix.sizeN, "THIS IS NOT A QUAD MATRIX");

	Vector diag(matrix.sizeM);
	diag = diagonalMatrix(matrix);

	double trace = 0;

	for (int i = 0; i < matrix.sizeM; i++)
		trace += diag.value[i];

	return trace;


}

Matrix transMatrix(Matrix& matrix)
{
	Matrix trans(matrix.sizeN, matrix.sizeM);
	

	for (int j = 0; j < matrix.sizeM; j++)
	{
		Vector vec(matrix.sizeN);
		for (int i = 0; i < matrix.sizeN; i++)
		{
			vec.value[i] = matrix.value[i][j];
		}
		trans.value[j] = vec.value;
	}
	
	return trans;
}

Matrix UpRightMatrix(Matrix& matrix, Matrix& matrix1)
{
	Matrix increase = matrix;

	for (int i = 0; i < matrix.sizeM; i++)
		for (int j = 0; j < matrix1.sizeN; j++)
			increase.value[i].push_back(matrix1.value[i][j]);
	increase.sizeN = increase.value[0].size();

	return increase;
}

double detMatrix(Matrix& matrix)
{
	assert(matrix.sizeM == matrix.sizeN, "NOT A QUAD MATRIX");

	if (matrix.sizeM == 2)
		return (matrix.value[0][0] * matrix.value[1][1]) - (matrix.value[1][0] * matrix.value[0][1]);
	
	else
	{
		double result = 0;
		for (int i = 0; i < matrix.sizeN; i++)
		{
			Matrix newMatrix(matrix.sizeM - 1, matrix.sizeN - 1);
			double value = matrix.value[i][matrix.sizeN - 1]; // FACT

			int k = 0;
			for (int j = 0; j < matrix.sizeN; j++)
			{
				if (j != i)
				{
					newMatrix.value[k] = matrix.value[j];
					k++;
				}
			}
			result += pow(-1, i + matrix.sizeN - 1) * (value * detMatrix(newMatrix));
			
		}
		return result;
	}
}

double maxIndex(Matrix& matrix, int indexM, int indexN)
{
	double max = indexM;
	for (int i = indexM; i < matrix.sizeM; i++) // Parcours les lignes
	{
		if (matrix.value[indexM][indexN] < matrix.value[i][indexN])
			max = i;
	}
	return max; // line index
}

Matrix swapMatrix(Matrix& matrix, int indexFirst, int indexMax)	
{
	Matrix newMatrix(matrix.sizeM, matrix.sizeN);

	for (int i = 0; i < matrix.sizeM; i++)
	{
		if (matrix.value[i] == matrix.value[indexFirst])
			newMatrix.value[i] = matrix.value[indexMax];

		else if(matrix.value[i] == matrix.value[indexMax])
			newMatrix.value[i] = matrix.value[indexFirst];

		else
			newMatrix.value[i] = matrix.value[i];
	}

	return newMatrix;
}

Matrix alphaCalcMatrix(Matrix& matrix, double indexPivot, int indexAlpha)
{
	Matrix a(1, matrix.sizeN), b(1, matrix.sizeN);
	b.value[0] = matrix.value[indexPivot];
	
	for (int i = 0; i < matrix.sizeM; i++)
	{
		if (i != indexPivot)
		{
			double alpha = matrix.value[i][indexAlpha]; // ALPHA
			a.value[0] = matrix.value[i];// NOT LINE OF PIVOT
			a = a - (b * alpha);
			matrix.value[i] = a.value[0];
		}
	}
	return matrix;
}

Matrix pivotMatrix(Matrix& matrix)
{
	int r = 0;
	int j = 0;
	for (int i = 0; i < matrix.sizeM; i++)
	{
		//max line
		double index = maxIndex(matrix, i, j); // index max begin by ligne i and colum j
		while (matrix.value[index][j] == 0) { j++; index = maxIndex(matrix, i, j);}
		matrix = swapMatrix(matrix, i, index);
		double normalize = matrix.value[i][j];

		if (normalize != 0)
		{
			for(int j = 0; j < matrix.sizeN ; j++)
				matrix.value[i][j] = matrix.value[i][j] / normalize;
			r++;
		}

		// CALCUL a - alpha * b
		matrix = alphaCalcMatrix(matrix, i, j);

		j++;
	}
	return matrix;
}

Matrix identityMatrix(Matrix& matrix)
{
	assert(matrix.sizeM == matrix.sizeN, "THIS IS NOT A QUAD MATRIX");

	for (int i = 0; i < matrix.sizeM; i++)
		for (int j = 0; j < matrix.sizeN; j++)
		{
			if (i == j)
				matrix.value[i][j] = 1;

			else
				matrix.value[i][j] = 0;

		}

	return matrix;
}

Matrix reverseMatrix(Matrix& matrix)
{
	assert(matrix.sizeM == matrix.sizeN, "THIS IS NOT A QUAD MATRIX");

	Matrix newMatrix(matrix.sizeM, matrix.sizeN);
	Matrix newFinishMatrix(matrix.sizeM, matrix.sizeN);
	newMatrix = identityMatrix(newMatrix);
	newMatrix = UpRightMatrix(matrix, newMatrix);
	newMatrix = pivotMatrix(newMatrix);

	int k = 0;

	for (int i = 0; i < matrix.sizeM; i++)
	{
		k = 0;
		for (int j = newMatrix.sizeN / 2; j < newMatrix.sizeN; j++)
		{
			newFinishMatrix.value[i][k] = newMatrix.value[i][j];
			k++;
		}
	}

	return newFinishMatrix;
}

Matrix rotationMatrix2X2(double angle)
{
	Matrix newMatrix(2, 2);
	newMatrix.value = { {cosf(angle), -sinf(angle)},{sinf(angle), cosf(angle)} };

	return newMatrix;
}
Matrix rotationMatrix3X3(double x, double y, double z, double angle)
{
	Matrix newMatrix(3, 3);
	
	newMatrix.value =
	{ 
		{x * x * (1 - cosf(angle)) + cosf(angle), y * x * (1 - cosf(angle)) - z * sinf(angle), z * x * (1 - cosf(angle)) + y * sinf(angle)} ,
		{x * y * (1 - cosf(angle)) + z * sinf(angle), y * y * (1 - cosf(angle)) + cosf(angle), z * y * (1 - cosf(angle)) - x * sinf(angle)} ,
		{x * z * (1 - cosf(angle)) - y * sinf(angle), y * z * (1 - cosf(angle)) - x * sinf(angle), z * z * (1 - cosf(angle)) + cosf(angle)}
	};
	
	return newMatrix;
}

Matrix scalingMatrix2X2(Vector& vector)
{
	assert(vector.size == 2);
	Matrix matrix(2, 2);

	matrix.value = { {vector.value[0], 0},{0 ,vector.value[1]} };

	return matrix;
}
Matrix scalingMatrix3X3(Vector& vector)
{
	assert(vector.size == 3);
	Matrix matrix(3, 3);

	matrix.value = { {vector.value[0], 0, 0},{0 ,vector.value[1], 0}, {0,0,vector.value[2]} };

	return matrix;
}

Matrix TRS(Vector& angle, Vector& vectorTrans, Vector& vectorScaling, Vector& axes)
{
	Matrix rotation(3, 3);
	Matrix R(4, 4);
	Matrix S(4, 4);
	Matrix T(4, 4);

	//TRANSLATE
	T = identityMatrix(T);
	T.value[0][3] = vectorTrans.value[0];
	T.value[1][3] = vectorTrans.value[1];
	T.value[2][3] = vectorTrans.value[2];

	//ROTATION
	Matrix rX(3, 3) , rY(3,3), rZ(3,3);
	rX = rotationMatrix3X3(axes.value[0], 0, 0, angle.value[0]);
	rY = rotationMatrix3X3(0, axes.value[1], 0, angle.value[1]);
	rZ = rotationMatrix3X3(0, 0, axes.value[2], angle.value[2]);

	rotation = rZ * (rX * rY) ;

	R.value = 
	{
		{rotation.value[0][0], rotation.value[0][1], rotation.value[0][2], 0},
		{rotation.value[1][0], rotation.value[1][1], rotation.value[1][2], 0},
		{rotation.value[2][0] ,rotation.value[2][1], rotation.value[2][2], 0},
		{0,0,0,1}
	};

	//SCALING
	S = identityMatrix(S);
	S.value[0][0] = vectorScaling.value[0];
	S.value[1][1] = vectorScaling.value[1];
	S.value[2][2] = vectorScaling.value[2];

	return (T * R) * S;
}



void testMatrix()
{
	/*
	cout << "\n ================  MATRIX  ====================" << endl;

	// Create Matrix with M and N elements
	Matrix matrix(2, 4);
	Matrix matrix1(2, 2);
	Matrix matrix2(2, 2);

	matrix.value = { {1,2,3,4} ,{5,6,7,8} };
	matrix1.value = { {1,2} ,{5,6} };
	matrix2.value = { {2,2} ,{7,6} };

	cout << "MATRIX 0 : " << matrix;
	cout << "MATRIX 1 : " << matrix1;
	cout << "MATRIX 2 : " << matrix2;
	cout << "\n";

	oppositeMatrix(matrix);

	cout << "DIAGONAL of MATRIX  :" << diagonalMatrix(matrix1) << endl;
	cout << "TRACE of MATRIX  : " << traceMatrix(matrix1) << endl;
	cout << "TRANS of MATRIX  : " << transMatrix(matrix1) << endl;

	Matrix sumMatrix(2, 2);
	Matrix mulMatrix(2, 2);

	sumMatrix = matrix1 + matrix2;
	mulMatrix =   matrix2 * 5;

	Matrix rix = matrix1 * matrix;

	matrix.sizeM = 3;
	matrix.sizeN = 3;
	matrix.value = {{1,2,3} ,{4,5,6}, {7,8,9}};

	cout << "Up MATRIX  : " << UpRightMatrix(matrix1, matrix2) << endl;

	cout << "MATRIX 0 : " << matrix;

	Matrix ab(4, 4);
	ab.value = { {1,3,1,4},{3,9,5,15},{0,1,8,1},{0,1,3,2} };

	cout << "DET MATRIX  : " << detMatrix(ab) << endl;

	Matrix a(3, 3);
	Matrix b(3, 3);
	a.value = { {2,2,2},{2,2,2},{2,2,2} };
	b.value = { {3,3,3},{3,3,3},{3,3,3} };

	cout << " \n" << a * b;

	cout << ab;

	double max = maxIndex(ab, 0, 2);
	cout << "MAX index MATRIX : " << max <<endl;
	cout << "SWAP index MATRIX : " << swapMatrix(ab,0,max) <<endl;


	Matrix ac(4, 4);
	ac.value = { {1,3,1,4},{3,9,5,15},{0,1,8,1},{0,1,3,2} };
	cout << "PIVOT GAUSS : " << pivotMatrix(ac) << endl;

	Matrix ad(2, 3);
	ad.value = { {1,2,3},{4,9,7} };
	cout << "PIVOT GAUSS : " << pivotMatrix(ad) << endl;

	Matrix ae(2, 3);
	ae.value = { {1,0,3},{4,0,7} };
	cout << "PIVOT GAUSS : " << pivotMatrix(ae) << endl;

	Matrix af(3, 5);
	af.value = { {3,2,1,-4,1},{2,3,0,-1,-1} ,{1,-6,3,-8,7} };
	cout << "PIVOT GAUSS : " << pivotMatrix(af) << endl;


	Matrix ag(3, 3);
	ag.value = { {1,2,3},{4,5,6} ,{7,8,0} };
	cout << "REVERSE : " << reverseMatrix(ag) << endl;


	cout << "---------------------------------------------------" << endl;

	cout << "ROTATION MATRIX :  " << rotationMatrix3X3(1, 0, 0, 0) << endl;

	Vector vecTrans(3);
	Vector vecScaling(3);
	Vector vecAxes(3); // no
	Vector angle(3);

	vecTrans.value = { 1,1,1 };
	vecScaling.value = { 1,2,3 };
	vecAxes.value = {1,1,1};
	angle.value = { M_PI , M_PI / 4 , M_PI / 3 };

	cout << "TRS MATRIX :  " << TRS(angle, vecTrans, vecScaling, vecAxes);*/
}