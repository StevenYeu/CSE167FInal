#include "House.h"

#ifdef _WIN32
#include <GL/glut.h>
#else
#include <GLUT/glut.h>
#endif

#include "Window.h"
#include "math.h"

House::House() {

}

House::~House()
{
	//Delete any dynamically allocated memory/objects here
}

void House::draw(DrawData& data) {
	// This data structure defines a simple house

	int nVerts = 42;    // your vertex array needs to have this many entries

	// These are the x,y,z coordinates of the vertices of the triangles
	float vertices[] = {
		-4, -4, 4, 4, -4, 4, 4, 4, 4, -4, 4, 4,     // front face
		-4, -4, -4, -4, -4, 4, -4, 4, 4, -4, 4, -4, // left face
		4, -4, -4, -4, -4, -4, -4, 4, -4, 4, 4, -4,  // back face
		4, -4, 4, 4, -4, -4, 4, 4, -4, 4, 4, 4,     // right face
		4, 4, 4, 4, 4, -4, -4, 4, -4, -4, 4, 4,     // top face
		-4, -4, 4, -4, -4, -4, 4, -4, -4, 4, -4, 4, // bottom face

		-20, -4, 20, 20, -4, 20, 20, -4, -20, -20, -4, -20, // grass
		-4, 4, 4, 4, 4, 4, 0, 8, 4,                       // front attic wall
		4, 4, 4, 4, 4, -4, 0, 8, -4, 0, 8, 4,               // left slope
		-4, 4, 4, 0, 8, 4, 0, 8, -4, -4, 4, -4,             // right slope
		4, 4, -4, -4, 4, -4, 0, 8, -4 };                   // rear attic wall

	// These are the RGB colors corresponding to the vertices, in the same order
	float colors[] = {
		1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0,  // front is red
		0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0,  // left is green
		1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0,  // back is red
		0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0,  // right is green
		0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1,  // top is blue
		0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1,  // bottom is blue

		0, 0.5, 0, 0, 0.5, 0, 0, 0.5, 0, 0, 0.5, 0, // grass is dark green
		0, 0, 1, 0, 0, 1, 0, 0, 1,                // front attic wall is blue
		1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0,         // left slope is green
		0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0,         // right slope is red
		0, 0, 1, 0, 0, 1, 0, 0, 1, };              // rear attic wall is red

	// The index data stores the connectivity of the triangles; 
	// index 0 refers to the first triangle defined above
	int indices[] = {
		0, 2, 3, 0, 1, 2,      // front face
		4, 6, 7, 4, 5, 6,      // left face
		8, 10, 11, 8, 9, 10,     // back face
		12, 14, 15, 12, 13, 14,   // right face
		16, 18, 19, 16, 17, 18,   // top face
		20, 22, 23, 20, 21, 22,   // bottom face

		24, 26, 27, 24, 25, 26,   // grass
		28, 29, 30,             // front attic wall
		31, 33, 34, 31, 32, 33,   // left slope
		35, 37, 38, 35, 36, 37,   // right slope
		39, 40, 41 };            // rear attic wall


		//Apply the material properties
		//From here forward anything drawn will be drawn with these material
		material.apply();

		//Set the OpenGL Matrix mode to ModelView (used when drawing geometry)
		glMatrixMode(GL_MODELVIEW);

		//Push a save state onto the matrix stack, and multiply in the toWorld matrix
		glPushMatrix();
		glMultMatrixf(toWorld.ptr());

		glBegin(GL_TRIANGLES);

		int len = 60;
		int index = -1;
		float colorRed = 0;
		float colorBlue = 0;
		float colorGreen = 0;
		float vertex_X = 0;
		float vertex_Y = 0;
		float vertex_Z = 0;


		for (int i = 0; i < 60; i++) {
			index = indices[i];
			colorRed = colors[index * 3];
			colorGreen = colors[index * 3 + 1];
			colorBlue = colors[index * 3 + 2];
			vertex_X = vertices[index * 3];
			vertex_Y = vertices[index * 3 + 1];
			vertex_Z = vertices[index * 3 + 2];
			if (i % 3 == 0) {
				glColor3f(colorRed, colorGreen, colorBlue);
			}
			glVertex3f(vertex_X, vertex_Y, vertex_Z);
		}

		glEnd();
		
		glPopMatrix();
	
}


void House::update(UpdateData& data)
{
	//
}