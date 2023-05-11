#include "matrix4x4.hpp"
#include "Vector3.hpp"

#include <assert.h>

using namespace std;


Matrix4x4::Matrix4x4()
{
    for (int i = 0; i < 4; i++)
        this->value.push_back(vector<float>(4, 0.f));
}

ostream& operator<<(ostream& stream, const Matrix4x4& matrix)
{
    for (int i = 0; i < 4; i++)
    {
        stream << "" << endl;
        for (int j = 0; j < 4; j++)
            stream << matrix.value[i][j] << " ";
    }
    stream << "" << endl;
    return stream;
}

Matrix4x4 Matrix4x4::operator*(const Matrix4x4& matrix)
{

    Matrix4x4 multipMatrix;

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            for (int k = 0; k < 4; k++)
            {
                multipMatrix.value[i][j] = multipMatrix.value[i][j] + (this->value[i][k] * matrix.value[k][j]);
            }
        }
    }

    return multipMatrix;
}

Vector4 Matrix4x4::operator*(const Vector4& vect)
{
    Vector4 multipMatrix;

    for (int j = 0; j < 4; j++)
    {
        for (int k = 0; k < 4; k++)
        {
            multipMatrix[j] = multipMatrix[j] + (this->value[j][k] * vect[k]);
        }
    }
    
    return multipMatrix;
}




Matrix4x4 Matrix4x4::IdentityMatrix()
{

    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
        {
            if (i == j)
                this->value[i][j] = 1;

            else
                this->value[i][j] = 0;

        }

    return *this;
}
