#ifndef _CUBE_H_
#define _CUBE_H_

#include "Geode.h"
#include "UpdateData.h"


class Cube : public Geode{

public:
	Cube(float s);
	~Cube();
	void render();
	void update(UpdateData&);
private:
	

	double size;
};

#endif