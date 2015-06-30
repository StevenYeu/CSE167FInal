#ifndef _MATRIXTRANSFORM_H_
#define _MATRIXTRANSFORM_H_

#include "Group.h"
#include "Matrix4.h"

class MatrixTransform : public Group{
public:
	MatrixTransform();
	MatrixTransform(Matrix4 c);
	void setMatrix(Matrix4 c);
	virtual void draw(DrawData&);
	virtual void update(UpdateData&);

	void translate(float, float, float);
	void scale(float, float, float);
	void rotate(float, Vector3&);
	void rotateX(float);
	Matrix4 getMatrix();
private:
	Matrix4 matrix;
	
};

#endif 