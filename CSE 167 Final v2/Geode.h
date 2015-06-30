#ifndef _GEODE_H_
#define _GEODE_H_

#include "Node.h"
#include <GLUT/GLUT.h>
#include "DrawData.h"
#include "Material.h"
class Geode : public Node{
public:
	Geode(){};
	void draw(DrawData& d);
	~Geode();

	void scale(float, float, float);
	void translate(float,float,float);
	void rotateX(float);
	void rotateY(float);
	void rotateZ(float);
    Material materials;
	
protected:
	virtual void update(UpdateData&)=0;
	virtual void render() = 0;

};


#endif