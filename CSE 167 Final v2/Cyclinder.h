#ifndef _CYCLINDER_H_
#define _CYCLINDER_H_
#define _USE_MATH_DEFINES // for C++
#include <cmath>
#include "Geode.h"
#include <GLUT/glut.h>
#include "Texture.h"



class Cyclinder : public Geode
{

protected:
	GLUquadric* q;
	GLdouble base;
	GLdouble radius;
	GLdouble height;
	GLint slices;
	GLint stacks;
	Texture tex;
public:
	Cyclinder(GLdouble,GLdouble,GLdouble);
	~Cyclinder();
	virtual void render();
	virtual void update(UpdateData&);
	void load();

};
#endif
