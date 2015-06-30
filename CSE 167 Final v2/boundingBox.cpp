#include "boundingBox.h"

#include <GLUT/glut.h>

boundingBox::boundingBox(float s){

	depth = s;
	width = s;
	height = s;
	pos = Vector3(1, 1, 1);
}

boundingBox::boundingBox(){
	
}

boundingBox::~boundingBox()
{
}

void boundingBox::createBbox(float s){
    glColor3f(1, 1, 1);
	glutWireCube(s);

}

bool boundingBox::detectCollision(boundingBox a, boundingBox b){
	return ((fabs(a.pos[0] - b.pos[0])*2 <= (a.width + b.width)) && (fabs(a.pos[1] - b.pos[1])*2 <= (a.height + b.height))
		&& (fabs(a.pos[2] - b.pos[2])*2 <= (a.depth + b.depth)));


}

void boundingBox::setnewPosition(Vector3 v){
	pos = v;


}
