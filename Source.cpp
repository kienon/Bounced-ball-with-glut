#include <windows.h>
#include <stdlib.h>
#include <math.h>
#include <gl\gl.h>
#include <gl\glu.h>
#include <gl\freeglut.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800
#define PI 3.1415926535897932384626433832795
#define FPS 30

int X = 0;
int Y = 0;
int dx = 15;
int dy = 20;


void nGon(int x, int y, int r, int n) {
	double inc = (2 * PI) / n;
	glBegin(GL_POLYGON);
	for (double theta = 0.0; theta <= 2 * PI; theta += inc) {
		glVertex2d(r * cos(theta) + x, r * sin(theta) + y);
	}
	glEnd();
}

void rectangle(int x, int y, int w, int h) {
	glBegin(GL_POLYGON);
	glVertex2d(x, y);
	glVertex2d(x + w, y);
	glVertex2d(x + w, y + h);
	glVertex2d(x, y + h);
	glEnd();
}

void house(int x, int y, int w) {
	// draw body 
	glColor3ub(0, 140, 255);
	rectangle(x, y, w, (2.0 / 3.0) * w);
	// draw door
	glColor3ub(255, 140, 0);
	rectangle(x + w / 2 - w / 12, y, w / 6, w / 3);
	// draw left window
	glColor3ub(255, 255, 255);
	rectangle(x + w / 8, y + w / 3, w / 4, w / 6);
	// draw right window
	glColor3ub(255, 255, 255);
	rectangle(x + w - (w / 8 + w / 4), y + w / 3, w / 4, w / 6);
	// draw roof
	glColor3ub(255, 200, 200);
	glBegin(GL_POLYGON);
	glVertex2d(x - w / 8, y + (2.0 / 3.0) * w);
	glVertex2d(x + w + w / 8, y + (2.0 / 3.0) * w);
	glVertex2d(x + w, y + (2.0 / 3.0) * w + w / 4);
	glVertex2d(x, y + (2.0 / 3.0) * w + w / 4);
	glEnd();
}



void display() {
	glClear(GL_COLOR_BUFFER_BIT);

	//house(X,Y, 100);
	nGon(X, Y, 50, 20);
	glFlush();
	glutSwapBuffers();
}

void idle() {
	DWORD start = GetTickCount();
	while (GetTickCount() - start < 1000 / FPS);

	X += dx;
	Y += dy;

	if (X<0 || X>SCREEN_WIDTH) dx *= -1;
	if (Y<0 || Y>SCREEN_HEIGHT) dy *= -1;

	glutPostRedisplay();

}

void initGL() {
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, SCREEN_WIDTH, 0, SCREEN_HEIGHT);

	glPointSize(10.0);
	glLineWidth(5.0);

}


int main(int argc, char** argv) {
	glutInitDisplayMode(GLUT_DOUBLE);
	glutInit(&argc, argv);
	glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	glutCreateWindow("test");
	glutDisplayFunc(display);
	glutIdleFunc(idle);

	initGL();

	glutMainLoop();
}