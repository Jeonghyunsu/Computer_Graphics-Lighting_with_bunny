#pragma once
#include "stdafx.h"
#include <Windows.h>
#include <gl\GL.h>
#include <gl\GLU.h>
#include <gl\glut.h>
#include <iostream>
#include <string>
#include <cmath>
#include <regex>
#include <gl\glaux.h>

#define PI 3.141592
#define YAXIS 100
#define ZAXIS 101

using namespace std;



class Point
{
public:
	GLfloat p[3];
	Point() {}
	Point(GLfloat x, GLfloat y, GLfloat z)
	{
		p[0] = x; p[1] = y; p[2] = z;
	}
	void SetPoint(GLfloat x, GLfloat y, GLfloat z)
	{
		p[0] = x; p[1] = y; p[2] = z;
	}
};
class Vector3x1
{
public:
	double xyzArr[3];


	Vector3x1()
	{
		xyzArr[0] = 0; xyzArr[1] = 0; xyzArr[2] = 0;
	}
	Vector3x1(double x, double y, double z)
	{
		xyzArr[0] = x; xyzArr[1] = y; xyzArr[2] = z;
	}

	double* GetCoordinate()
	{
		return xyzArr;
	}
	void SetCoordinate(double x, double y, double z)
	{
		xyzArr[0] = x; xyzArr[1] = y; xyzArr[2] = z;
	}

	static Vector3x1* VectorAddition(Vector3x1* v1, Vector3x1* v2);
	static Vector3x1* VectorSubtraction(Vector3x1* v1, Vector3x1* v2);
	static Vector3x1* VectorNegation(Vector3x1* v1);
	static Vector3x1* ScalarMultiplication(Vector3x1* v1, double Scalar);
	static double DotProduct(Vector3x1* v1, Vector3x1* v2);
	static Vector3x1* CrossProduct(Vector3x1* v1, Vector3x1* v2);
	static double VectorLength(Vector3x1* v1);
};
class Matrix3x3
{
public:
	double mat[3][3];

	Matrix3x3()
	{
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				this->mat[i][j] = 0;
	}
	Matrix3x3(double identity)
	{
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
			{
				if (i == j) this->mat[i][j] = 1;
				else this->mat[i][j] = 0;

			}
	}
	Matrix3x3(double mat[3][3])
	{
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				this->mat[i][j] = mat[i][j];
	}

	double(*GetMatrix(void))[3]
	{
		return mat;
	}
		void SetMatrix(double mat[3][3])
	{
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				this->mat[i][j] = mat[i][j];
	}

	static Matrix3x3* MatrixAddtion(Matrix3x3* m1, Matrix3x3* m2);
	static Matrix3x3* MatrixSubtraction(Matrix3x3* m1, Matrix3x3* m2);
	static Matrix3x3*  MatrixNegation(Matrix3x3* m1);
	static Matrix3x3* ScalarMultiplication(Matrix3x3* m1, double Scalar);
	static Matrix3x3* MatrixMultiplication(Matrix3x3* m1, Matrix3x3* m2);
	static Vector3x1* Matrix_VectorMultiplication(Matrix3x3* m1, Vector3x1* v1);
	static Point Matrix3x3::MultMatPoint(Matrix3x3* m, Point* p);

	void Print()
	{
		cout << endl;
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
				cout << mat[i][j] << "  ";
			cout << endl;
		}
		cout << endl;
	}
};
class Matrix4x4
{
public:
	double mat[4][4];

	Matrix4x4()
	{
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				this->mat[i][j] = 0;
	}
	Matrix4x4(double identity)
	{
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
			{
				if (i == j) this->mat[i][j] = 1;
				else this->mat[i][j] = 0;

			}
	}
	Matrix4x4(double x, double y, double z)
	{
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
			{
				if (i == j) this->mat[i][j] = 1;
				else this->mat[i][j] = 0;
			}
		this->mat[3][0] = 0; this->mat[3][1] = 0; this->mat[3][2] = 0; this->mat[3][3] = 1;
		this->mat[0][3] = x; this->mat[1][3] = y; this->mat[2][3] = z;
	}
	Matrix4x4(int axis, double theta)
	{
		if (axis == YAXIS)
		{
			this->mat[0][0] = cos(theta); this->mat[0][1] = 0; this->mat[0][2] = sin(theta); this->mat[0][3] = 0;
			this->mat[1][0] = 0; this->mat[1][1] = 1; this->mat[1][2] = 0; this->mat[1][3] = 0;
			this->mat[2][0] = -sin(theta); this->mat[2][1] = 0; this->mat[2][2] = cos(theta); this->mat[2][3] = 0;
			this->mat[3][0] = 0; this->mat[3][1] = 0; this->mat[3][2] = 0; this->mat[3][3] = 1;
		}
		else if (axis == ZAXIS)
		{
			this->mat[0][0] = cos(theta); this->mat[0][1] = -sin(theta); this->mat[0][2] = 0; this->mat[0][3] = 0;
			this->mat[1][0] = sin(theta); this->mat[1][1] = cos(theta); this->mat[1][2] = 0; this->mat[1][3] = 0;
			this->mat[2][0] = 0; this->mat[2][1] = 0; this->mat[2][2] = 1; this->mat[2][3] = 0;
			this->mat[3][0] = 0; this->mat[3][1] = 0; this->mat[3][2] = 0; this->mat[3][3] = 1;
		}
	}




	double(*GetMatrix(void))[4]
	{
		return mat;
	}
		void SetMatrix(double mat[4][4])
	{
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				this->mat[i][j] = mat[i][j];
	}

	static Vector3x1* Matrix_VectorMultiplication(Matrix4x4* m1, Vector3x1* v1);
};
Vector3x1* Matrix4x4::Matrix_VectorMultiplication(Matrix4x4* m1, Vector3x1* v1)
{
	double xyz[4] = { 0 };
	xyz[3] = 1;
	double(*m1_mat)[4] = m1->GetMatrix();
	double* v1Coordinate = v1->GetCoordinate();

	for (int i = 0; i < 4; i++)
	{
		for (int k = 0; k < 4; k++)
		{
			if (k == 3) {
				xyz[i] += m1_mat[i][k] * 1;
			}
			else
				xyz[i] += m1_mat[i][k] * v1Coordinate[k];
		}

	}

	return new Vector3x1(xyz[0], xyz[1], xyz[2]);
}

Vector3x1* Vector3x1::VectorAddition(Vector3x1* v1, Vector3x1* v2)
{
	double* v1_xyzArr = v1->GetCoordinate();
	double* v2_xyzArr = v2->GetCoordinate();
	return new Vector3x1(v1_xyzArr[0] + v2_xyzArr[0], v1_xyzArr[1] + v2_xyzArr[1], v1_xyzArr[2] + v2_xyzArr[2]);
}
Vector3x1* Vector3x1::VectorSubtraction(Vector3x1* v1, Vector3x1* v2)
{
	double* v1_xyzArr = v1->GetCoordinate();
	double* v2_xyzArr = v2->GetCoordinate();
	return new Vector3x1(v1_xyzArr[0] - v2_xyzArr[0], v1_xyzArr[1] - v2_xyzArr[1], v1_xyzArr[2] - v2_xyzArr[2]);
}
Vector3x1* Vector3x1::VectorNegation(Vector3x1* v1)
{
	double* v1_xyzArr = v1->GetCoordinate();
	return new Vector3x1(-v1_xyzArr[0], -v1_xyzArr[1], -v1_xyzArr[2]);
}
Vector3x1* Vector3x1::ScalarMultiplication(Vector3x1* v1, double Scalar)
{
	double* v1_xyzArr = v1->GetCoordinate();
	return new Vector3x1(Scalar*v1_xyzArr[0], Scalar*v1_xyzArr[1], Scalar*v1_xyzArr[2]);
}
double Vector3x1::DotProduct(Vector3x1* v1, Vector3x1* v2)
{
	double* v1_xyzArr = v1->GetCoordinate();
	double* v2_xyzArr = v2->GetCoordinate();
	return v1_xyzArr[0] * v2_xyzArr[0] + v1_xyzArr[1] * v2_xyzArr[1] + v1_xyzArr[2] * v2_xyzArr[2];
}
Vector3x1* Vector3x1::CrossProduct(Vector3x1* v1, Vector3x1* v2)
{
	double* a = v1->GetCoordinate();
	double* b = v2->GetCoordinate();

	return new Vector3x1(a[1] * b[2] - a[2] * b[1], a[2] * b[0] - a[0] * b[2], a[0] * b[1] - a[1] * b[0]);
}
double Vector3x1::VectorLength(Vector3x1* v1)
{
	double* v1_xyzArr = v1->GetCoordinate();

	return sqrt(v1_xyzArr[0] * v1_xyzArr[0] + v1_xyzArr[1] * v1_xyzArr[1] + v1_xyzArr[2] * v1_xyzArr[2]);
}

Matrix3x3* Matrix3x3::MatrixAddtion(Matrix3x3* m1, Matrix3x3* m2)
{
	double mat[3][3] = { 0 };
	double(*m1_mat)[3] = m1->GetMatrix();
	double(*m2_mat)[3] = m2->GetMatrix();

	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
		{
			mat[i][j] = m1_mat[i][j] + m2_mat[i][j];
		}

	return new Matrix3x3(mat);
}
Matrix3x3* Matrix3x3::MatrixSubtraction(Matrix3x3* m1, Matrix3x3* m2)
{
	double mat[3][3] = { 0 };
	double(*m1_mat)[3] = m1->GetMatrix();
	double(*m2_mat)[3] = m2->GetMatrix();

	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
		{
			mat[i][j] = m1_mat[i][j] - m2_mat[i][j];
		}

	return new Matrix3x3(mat);
}
Matrix3x3* Matrix3x3::MatrixNegation(Matrix3x3* m1)
{
	double mat[3][3] = { 0 };
	double(*m1_mat)[3] = m1->GetMatrix();

	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
		{
			mat[i][j] = -m1_mat[i][j];
		}

	return new Matrix3x3(mat);
}
Matrix3x3* Matrix3x3::ScalarMultiplication(Matrix3x3* m1, double Scalar)
{
	double mat[3][3] = { 0 };
	double(*m1_mat)[3] = m1->GetMatrix();

	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
		{
			mat[i][j] = Scalar * m1_mat[i][j];
		}

	return new Matrix3x3(mat);
}
Matrix3x3* Matrix3x3::MatrixMultiplication(Matrix3x3* m1, Matrix3x3* m2)
{
	double mat[3][3] = { 0 };
	double(*m1_mat)[3] = m1->GetMatrix();
	double(*m2_mat)[3] = m2->GetMatrix();

	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
		{
			for (int k = 0; k < 3; k++)
			{
				mat[i][j] += m1_mat[i][k] * m2_mat[k][j];
			}
		}

	return new Matrix3x3(mat);
}
Vector3x1* Matrix3x3::Matrix_VectorMultiplication(Matrix3x3* m1, Vector3x1* v1)
{
	double xyz[3] = { 0 };
	double(*m1_mat)[3] = m1->GetMatrix();
	double* v1Coordinate = v1->GetCoordinate();

	for (int i = 0; i < 3; i++)
	{
		for (int k = 0; k < 3; k++)
		{
			xyz[i] += m1_mat[i][k] * v1Coordinate[k];
		}
	}

	return new Vector3x1(xyz[0], xyz[1], xyz[2]);
}
Point Matrix3x3::MultMatPoint(Matrix3x3* m, Point* p)
{
	Point _p;

	_p.p[0] = m->mat[0][0] * p->p[0] + m->mat[1][0] * p->p[1] + m->mat[2][0] * p->p[2];
	_p.p[1] = m->mat[0][1] * p->p[0] + m->mat[1][1] * p->p[1] + m->mat[2][1] * p->p[2];
	_p.p[2] = m->mat[0][2] * p->p[0] + m->mat[1][2] * p->p[1] + m->mat[2][2] * p->p[2];

	return _p;
}
