#define Cos(th) cos(M_PI/180*(th))
#define Sin(th) sin(M_PI/180*(th))
#include "Cyclinder.h"


Cyclinder::Cyclinder(GLdouble b, GLdouble r, GLdouble h) 
{
	base = b;
	radius = r;
	height = h;
	slices = 30;
	stacks = 30;
	material = Material();
}


Cyclinder::~Cyclinder()
{
	delete q;
}

void Cyclinder::render() {

	glRotatef(90, 0.0f, 1.0f, 0.0f);


	tex.bind();
	glBegin(GL_QUAD_STRIP);

	for (int i = 0; i <= 360; i++) {
		double u = i / (double)360;
		double x = radius*cos(2 * M_PI*u);
		double z = radius*sin(2 * M_PI*u);
		/* Bottom vertex*/
		glColor3f(1.0, 1.0, 1.0);
		glTexCoord2d(u, 1.0); glVertex3d(x, base, z);
		/* Top vertex*/
		glTexCoord2d(u, 0.0); glVertex3d(x, height, z);
	}
	glEnd();

	for (int i = 1; i >= -1; i -= 2) {
		glBegin(GL_TRIANGLE_FAN);
		glColor3f(1.0, 1.0, 1.0);
		if (i == -1) {
			glVertex3f(0, base, 0);
		}
		else {
			glVertex3f(0, height, 0);
		}
		for (int k = 0; k <= 360; k += 5) {
			glColor3f(1.0, 1.0, 1.0);
			if (i == -1) {
				
				glVertex3f(radius*Cos(k), base, Sin(k));
			}
			else {
				glVertex3f(radius*Cos(k), height, Sin(k));
			}
		}
		glEnd();
	}
}

void Cyclinder::update(UpdateData& d) {
}

void Cyclinder::load() {
	tex = Texture("mask.ppm");

}