#include "stdafx.h"
#include "lighting_with_bunny.h"
#include <iostream>
#include <fstream>

ifstream ifs("bunny_origin.txt");
int pointNum, triangleNum;

GLfloat** gvectorArr;
int** triangleArr;
GLfloat** gnom;
GLfloat** gnomCenter;
GLfloat** subgnom;
GLfloat** VNV;

GLfloat position[4];
int lightsourceFlag;

double theta;
double degree;
double shininess;
bool cut_off_startFlag;
bool dir_rotationFlag;
bool shininess_startFlag;
bool dir_shininessFlag;

void keyboard(unsigned char key, int x, int y);
void RenderScene();
void SetupRC();
void ChangeSize(int w, int h);
void Readfile();
void RotationMatrix(double theta);

void timer(int value)
{

	theta = 2.0 * PI / 180.0;
	if (theta >= 360.0)theta = 0;

	RotationMatrix(theta);
	glutPostRedisplay();
	glutTimerFunc(1000 / 45, timer, 1);
}
void cut_off_angle_timer(int value)
{
	cout << degree << endl;
	if (dir_rotationFlag) {
		degree += 1;
	}
	else if (!dir_rotationFlag) {
		degree -= 1;
	}
	if (degree >= 25)dir_rotationFlag = false;
	else if (degree <= 5)dir_rotationFlag = true;

	glutPostRedisplay();
	if (cut_off_startFlag)glutTimerFunc(1000 / 10, cut_off_angle_timer, 1);
}
void shininess_timer(int value)
{
	cout << shininess << endl;
	if (dir_shininessFlag) {
		shininess += 1;
	}
	else if (!dir_shininessFlag) {
		shininess -= 1;
	}
	if (shininess >= 128)dir_shininessFlag = false;
	else if (shininess <= 0)dir_shininessFlag = true;

	glutPostRedisplay();
	if (shininess_startFlag)glutTimerFunc(1000 / 32, shininess_timer, 1);
}
void Initialize()
{
	lightsourceFlag = 0;
	position[0] = 1; position[1] = 3; position[2] = 1; position[3] = 1;
	cut_off_startFlag = false;
	dir_rotationFlag = true;
	shininess_startFlag = false;
	dir_shininessFlag = true;

	theta = 0.0f; degree = 5; shininess = 64;
	glutTimerFunc(1000 / 45, timer, 1);
}
void Normalize(Point &p)
{
	double d = p.p[0] * p.p[0] + p.p[1] * p.p[1] + p.p[2] * p.p[2];
	if (d > 0)
	{
		float len = (float)(1.0 / sqrt(d));
		p.p[0] *= len;
		p.p[1] *= len;
		p.p[2] *= len;
	}
}
void CrossProduct(Point &a, Point &b, Point &c, Point &r)
{
	r.p[0] = (b.p[1] - a.p[1])*(c.p[2] - a.p[2]) - (b.p[2] - a.p[2])*(c.p[1] - a.p[1]);
	r.p[1] = (b.p[2] - a.p[2])*(c.p[0] - a.p[0]) - (b.p[0] - a.p[0])*(c.p[2] - a.p[2]);
	r.p[2] = (b.p[0] - a.p[0])*(c.p[1] - a.p[1]) - (b.p[1] - a.p[1])*(c.p[0] - a.p[0]);
	Normalize(r);
}
void DrawPoint()
{
	for (int i = 0; i < pointNum; i++)
	{
		glVertex3fv(gvectorArr[i]);
	}
}
void DrawTheBunny()
{
	glBegin(GL_TRIANGLES);
	for (int i = 0; i < triangleNum; i++)
	{
		glNormal3fv(gvectorArr[triangleArr[i][0] - 1]);
		glVertex3fv(gvectorArr[triangleArr[i][0] - 1]);
		glNormal3fv(gvectorArr[triangleArr[i][1] - 1]);
		glVertex3fv(gvectorArr[triangleArr[i][1] - 1]);
		glNormal3fv(gvectorArr[triangleArr[i][2] - 1]);
		glVertex3fv(gvectorArr[triangleArr[i][2] - 1]);

		glEnd();
		glBegin(GL_TRIANGLES);
	}
}
void DrawTheBunnyLINES()
{
	glBegin(GL_LINES);
	for (int i = 0; i < triangleNum; i++)
	{
		glVertex3fv(gvectorArr[triangleArr[i][0] - 1]);
		glVertex3fv(gvectorArr[triangleArr[i][1] - 1]);

		glEnd();
		glBegin(GL_LINES);

		glVertex3fv(gvectorArr[triangleArr[i][1] - 1]);
		glVertex3fv(gvectorArr[triangleArr[i][2] - 1]);

		glEnd();
		glBegin(GL_LINES);

		glVertex3fv(gvectorArr[triangleArr[i][2] - 1]);
		glVertex3fv(gvectorArr[triangleArr[i][0] - 1]);

		glEnd();
		glBegin(GL_LINES);
	}
	glEnd();
}
void DrawVertexNormalVectors()
{
	for (int i = 0; i < triangleNum; i++)
	{
		Point p1(
			gvectorArr[triangleArr[i][0] - 1][0],
			gvectorArr[triangleArr[i][0] - 1][1],
			gvectorArr[triangleArr[i][0] - 1][2]);

		Point p2(
			gvectorArr[triangleArr[i][1] - 1][0],
			gvectorArr[triangleArr[i][1] - 1][1],
			gvectorArr[triangleArr[i][1] - 1][2]);

		Point p3(
			gvectorArr[triangleArr[i][2] - 1][0],
			gvectorArr[triangleArr[i][2] - 1][1],
			gvectorArr[triangleArr[i][2] - 1][2]);

		gnomCenter[i][0] = (gvectorArr[triangleArr[i][0] - 1][0] + gvectorArr[triangleArr[i][1] - 1][0] + gvectorArr[triangleArr[i][2] - 1][0]) / 3;
		gnomCenter[i][1] = (gvectorArr[triangleArr[i][0] - 1][1] + gvectorArr[triangleArr[i][1] - 1][1] + gvectorArr[triangleArr[i][2] - 1][1]) / 3;
		gnomCenter[i][2] = (gvectorArr[triangleArr[i][0] - 1][2] + gvectorArr[triangleArr[i][1] - 1][2] + gvectorArr[triangleArr[i][2] - 1][2]) / 3;

		Point r;
		CrossProduct(p1, p2, p3, r);
		for (int j = 0; j < 3; j++) {
			gnom[i][j] = r.p[j] / 10;
			subgnom[i][j] = gnom[i][j] + gnomCenter[i][j];
		}
	}

	glBegin(GL_LINES);
	for (int i = 0; i < pointNum; i++)
	{
		Point p(0, 0, 0);
		for (int j = 0; j < triangleNum; j++)
		{
			if ((gvectorArr[i][0] == gvectorArr[triangleArr[j][0] - 1][0] && gvectorArr[i][1] == gvectorArr[triangleArr[j][0] - 1][1] && gvectorArr[i][2] == gvectorArr[triangleArr[j][0] - 1][2]) ||
				(gvectorArr[i][0] == gvectorArr[triangleArr[j][1] - 1][0] && gvectorArr[i][1] == gvectorArr[triangleArr[j][1] - 1][1] && gvectorArr[i][2] == gvectorArr[triangleArr[j][1] - 1][2]) ||
				(gvectorArr[i][0] == gvectorArr[triangleArr[j][2] - 1][0] && gvectorArr[i][1] == gvectorArr[triangleArr[j][2] - 1][1] && gvectorArr[i][2] == gvectorArr[triangleArr[j][2] - 1][2]))
			{
				for (int k = 0; k < 3; k++)
				{
					p.p[k] += gnom[j][k];
				}
			}
		}
		Normalize(p);
		for (int j = 0; j < 3; j++) VNV[i][j] = p.p[j] / 10 + gvectorArr[i][j];

		glVertex3fv(gvectorArr[i]);
		glVertex3fv(VNV[i]);
		glEnd();
		glBegin(GL_LINES);
	}

}
void RotationMatrix(double theta)
{

	Point p(1, 1, 1);
	Normalize(p);
	Vector3x1 vector(p.p[0], p.p[1], p.p[2]);

	Matrix3x3 id(1);
	double mat[3][3];
	for (int i = 0; i < 3; i++)for (int j = 0; j < 3; j++)mat[i][j] = (double)1 / 3;
	Matrix3x3* vv_t = new Matrix3x3(mat);
	Matrix3x3* cosa_I_vv_t = Matrix3x3::ScalarMultiplication(Matrix3x3::MatrixSubtraction(&id, vv_t), cos(theta));


	mat[0][0] = 0;                  mat[0][1] = -vector.xyzArr[2];   mat[0][2] = vector.xyzArr[1];
	mat[1][0] = vector.xyzArr[2];   mat[1][1] = 0;                   mat[1][2] = -vector.xyzArr[0];
	mat[2][0] = -vector.xyzArr[1];  mat[2][1] = vector.xyzArr[0];    mat[2][2] = 0;
	Matrix3x3 vx(mat);
	Matrix3x3* sina_vx = Matrix3x3::ScalarMultiplication(&vx, sin(theta));


	Matrix3x3* R = Matrix3x3::MatrixAddtion(Matrix3x3::MatrixAddtion(vv_t, cosa_I_vv_t), sina_vx);
	double p0 = position[0]; double p1 = position[1]; double p2 = position[2];
	position[0] = R->mat[0][0] * p0 + R->mat[0][1] * p1 + R->mat[0][2] * p2;
	position[1] = R->mat[1][0] * p0 + R->mat[1][1] * p1 + R->mat[1][2] * p2;
	position[2] = R->mat[2][0] * p0 + R->mat[2][1] * p1 + R->mat[2][2] * p2;
}


int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(600, 600);
	glutCreateWindow("");

	Readfile();
	Initialize();

	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);

	glutKeyboardFunc(keyboard);

	SetupRC();

	glutMainLoop();


	delete[] gvectorArr;
	delete[] triangleArr;
	return 0;
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'p':
		lightsourceFlag = 0;
		break;
	case 'd':
		lightsourceFlag = 1;
		break;
	case 's':
		lightsourceFlag = 2;
		break;
	case 'c':
		if (cut_off_startFlag == false)
		{
			cut_off_startFlag = true;
			glutTimerFunc(1000 / 10, cut_off_angle_timer, 1);
		}
		else cut_off_startFlag = false;
		break;
	case 'n':
		if (shininess_startFlag == false)
		{
			shininess_startFlag = true;
			glutTimerFunc(1000 / 32, shininess_timer, 1);
		}
		else shininess_startFlag = false;

		break;
	}
	glutPostRedisplay();
}

void RenderScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glLineWidth(1);
	gluLookAt(1.0f, 1.0f, 1.0f, 0.f, 0.f, 0.f, 0.f, 1.f, 0.f);
	glBegin(GL_LINES);
	{
		glColor3f(1.f, 0.f, 0.f);
		glVertex3f(0, 0.0, 0.0);
		glVertex3f(200, 0.0, 0.0);

		glColor3f(0.f, 1.f, 0.f);
		glVertex3f(0.0, 0, 0.0);
		glVertex3f(0.0, 200, 0.0);

		glColor3f(0.f, 0.f, 1.f);
		glVertex3f(0.0, 0.0, 0);
		glVertex3f(0.0, 0.0, 100);
	}
	glEnd();

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT2);

	if (lightsourceFlag == 0)
	{
		glDisable(GL_LIGHT1); glDisable(GL_LIGHT2);
		position[3] = 1;
		glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 180);
		glLightfv(GL_LIGHT0, GL_POSITION, position);
	}
	else if (lightsourceFlag == 1)
	{
		glDisable(GL_LIGHT0); glDisable(GL_LIGHT2);
		position[3] = 0;
		glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, position);

		GLfloat ambient[4] = { 0,0,0, 1 };
		GLfloat diffuse[4] = { 1.0, 1.0, 1.0, 1 };
		GLfloat specular[4] = { 1,1,1, 1 };

		glLightfv(GL_LIGHT1, GL_POSITION, position);
		glLightfv(GL_LIGHT1, GL_AMBIENT, ambient);
		glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse);
		glLightfv(GL_LIGHT1, GL_SPECULAR, specular);
	}
	else if (lightsourceFlag == 2)
	{
		glDisable(GL_LIGHT0); glDisable(GL_LIGHT1);

		position[3] = 1;
		GLfloat position2[3];
		position2[0] = -position[0]; position2[1] = -position[1]; position2[2] = -position[2];

		GLfloat ambient[4] = { 0,0,0, 1 };
		GLfloat diffuse[4] = { 1.0, 1.0, 1.0, 1 };
		GLfloat specular[4] = { 1,1,1, 1 };

		glLightfv(GL_LIGHT2, GL_POSITION, position);
		glLightfv(GL_LIGHT2, GL_AMBIENT, ambient);
		glLightfv(GL_LIGHT2, GL_DIFFUSE, diffuse);
		glLightfv(GL_LIGHT2, GL_SPECULAR, specular);

		glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, position2);
		glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, degree);
		glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, shininess);

		glLightf(GL_LIGHT2, GL_CONSTANT_ATTENUATION, 0.2);
		glLightf(GL_LIGHT2, GL_LINEAR_ATTENUATION, 0.1);
		glLightf(GL_LIGHT2, GL_QUADRATIC_ATTENUATION, 0.05);
	}

	glColor3f(1.0f, 0.8f, 0.8f);
	glBegin(GL_TRIANGLES);
	DrawTheBunny();
	glEnd();
	glDisable(GL_LIGHTING);

	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINES);
	DrawTheBunnyLINES();
	glEnd();

	glColor3f(0.8f, 0.7f, 0.6);
	glBegin(GL_LINES);
	DrawVertexNormalVectors();
	glEnd();

	glutSwapBuffers();
}
void SetupRC()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);
}
void ChangeSize(int w, int h)
{
	if (h == 0)
		h = 1;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (w <= h)
	{
		glOrtho(-2.0, 2.0, -2.0*(float)h / (float)w, 2.0*(float)h / (float)w, -10.0, 10.0);
	}
	else
	{
		glOrtho(-2.0, 2.0, -2.0*(float)w / (float)h, 2.0*(float)w / (float)h, -10.0, 10.0);
	}
}
void Readfile()
{
	ifs >> pointNum >> triangleNum;

	gvectorArr = (GLfloat**)malloc(sizeof(GLfloat*)*pointNum);
	for (int i = 0; i < pointNum; i++)
	{
		gvectorArr[i] = (GLfloat*)malloc(sizeof(GLfloat) * 3);
		ifs >> gvectorArr[i][0] >> gvectorArr[i][1] >> gvectorArr[i][2];

		gvectorArr[i][0] *= 2; gvectorArr[i][1] *= 2; gvectorArr[i][2] *= 2;
	}

	gnom = (GLfloat**)malloc(sizeof(GLfloat*)*triangleNum);
	gnomCenter = (GLfloat**)malloc(sizeof(GLfloat*)*triangleNum);
	subgnom = (GLfloat**)malloc(sizeof(GLfloat*)*triangleNum);
	VNV = (GLfloat**)malloc(sizeof(GLfloat*)*triangleNum);
	triangleArr = (int**)malloc(sizeof(int*)*triangleNum);

	for (int i = 0; i < triangleNum; i++)
	{
		gnom[i] = (GLfloat*)malloc(sizeof(int) * 3);
		gnomCenter[i] = (GLfloat*)malloc(sizeof(int) * 3);
		subgnom[i] = (GLfloat*)malloc(sizeof(int) * 3);
		VNV[i] = (GLfloat*)malloc(sizeof(int) * 3);
		triangleArr[i] = (int*)malloc(sizeof(int) * 3);
		ifs >> triangleArr[i][0] >> triangleArr[i][1] >> triangleArr[i][2];
	}
}


