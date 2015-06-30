#include "MatrixTransform.h"


MatrixTransform::MatrixTransform() {
	matrix.identity();
}

MatrixTransform::MatrixTransform(Matrix4 c){
	matrix = c;
}

void MatrixTransform::setMatrix(Matrix4 c){
	matrix = c;
}

Matrix4 MatrixTransform::getMatrix(){
	return matrix;
}

void MatrixTransform::draw(DrawData& d){
	 Matrix4 mm= d.getMatrix() * matrix;
	 DrawData new_d;
	 new_d.setMatrix(mm);
	 Group::draw(new_d);
}

void MatrixTransform::update(UpdateData& d) {

}

void MatrixTransform::translate(float x, float y, float z){
	matrix = matrix.makeTranslate(x, y, z);
}

void MatrixTransform::scale(float sx, float sy, float sz){
	matrix = matrix.makeScale(sx, sy, sz);
}

void MatrixTransform::rotate(float angle, Vector3& axis){
	matrix = matrix.makeRotateArbitrary(axis, angle);
}

void MatrixTransform::rotateX(float angle){
	matrix = matrix.makeRotateX(angle);
}
