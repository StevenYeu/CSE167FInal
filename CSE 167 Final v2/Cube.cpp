#include "Cube.h"

#ifdef _WIN32
    #include <GL/glut.h>
#else
    #include <GLUT/glut.h>
#endif

#include "Window.h"
#include "math.h"

Cube::Cube(float s) : Geode()
{
    size = s;
}

Cube::~Cube()
{
    //Delete any dynamically allocated memory/objects here
}



void Cube::render()
{
    materials.apply();
	glColor3f(0.1, 0, 0);
	glutSolidCube(size);


}


void Cube::update(UpdateData& data)
{
    //
}



