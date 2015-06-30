#ifndef CSE167_boundingBox_h
#define CSE167_boundingBox_h


#include "Vector3.h"
#include <cmath>

class boundingBox
{
public:
	boundingBox();
	boundingBox(float);
	~boundingBox();

	void createBbox(float);
	bool detectCollision(boundingBox, boundingBox);
	void setnewPosition(Vector3);

	float width, height, depth;
	Vector3 pos;

};

#endif

