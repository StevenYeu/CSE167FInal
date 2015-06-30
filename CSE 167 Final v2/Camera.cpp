#include "Camera.h"

Camera::Camera()
{
    c.identity();
    e.set(3.0, 0, 200.0);
    d.set(0.0, 0.0, 0.0);
    up.set(0.0, 1.0, 0.0);
    
    right = foward.cross(up);
    right = right.normalize();
    
    left = right * -1;
    
    foward = d - e;
    foward = foward.normalize();
    
    backward = foward * -1;
    
    mup = right.cross(foward);
    mup = mup.normalize();
    
    down = mup * -1;

    
    //Pre-define a camera matrix (and its inverse) that are shifted 'e' from the origin
    //This is used as a default camera position for Project 1
    c.set(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, e[0], e[1], e[2], 1);
    ci.set(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, -e[0], -e[1], -e[2], 1);
}

Camera::~Camera()
{
    //Delete and dynamically allocated memory/objects here
}

Matrix4& Camera::getMatrix()
{
    return c;
}

Matrix4& Camera::getInverseMatrix()
{
    return ci;
}

void Camera::update()
{
    //Update the Camera Matrix using d, e, and up
    //Solve for the z, x, and y axes of the camera matrix
    //Use these axes and the e vector to create a camera matrix c
    //Use c to solve for an inverse camera matrix ci

	Vector3 z = e - d;
	z = z.normalize();
	Vector3 x = up.cross(z);
	x = x.normalize();
	Vector3 y = z.cross(x);
	c.set(x[0], x[1], x[2], 0,
		  y[0], y[1], y[2], 0,
		  z[0], z[1], z[2], 0,
		  e[0], e[1], e[2], 1);

	Matrix4 r;
	r.identity();
	/*r.set(x[0], y[0], z[0], 0,
		  x[1], y[1], z[1], 0,
		  x[2], y[2], z[2], 0,
		  0, 0, 0, 1);*/
	r.set(x[0], x[1], x[2], 0,
		y[0], y[1], y[2], 0,
		z[0], z[1], z[2], 0,
		0, 0, 0, 1);
	Matrix4 r_inverse;
	r_inverse = r.transpose();

	Matrix4 t_inverse;
	/*t_inverse.set(1, 0, 0, e[0] * -1,
				  0, 1, 0, e[1] * -1,
				  0, 0, 1, e[2] * -1,
				  0, 0, 0, 1);*/
	t_inverse.set(1, 0, 0,0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		e[0]*-1, e[1]*-1, e[2]*-1, 1);
	ci = r_inverse * t_inverse;


}

void Camera::set(Vector3& e, Vector3& d, Vector3& up)
{
    this->e = e;
    this->d = d;
    this->up = up;
    update();
}


void Camera::orbitTrack(Vector3 v, float angle) {
	Matrix4 orb;
	float pi = 3.14159265358979323846;
	float rads = angle * (pi / 180.0);
	orb.makeRotateArbitrary(v, rads);
    Vector3 lookAt = d - e;
    Vector3 newLookAt = orb * lookAt;
    d = e + newLookAt;
    update();
	//ci = orb *ci ;
}


void Camera::moveFoward(float s) {
    foward = d - e;
    foward = foward.normalize();
    e = e + foward*s;
    d = d + foward*s;
    update();

}

void Camera::moveBackward(float s) {
    backward = foward * -1;
    e = e + backward*s;
    d = d + backward*s;
    update();
}

void Camera::moveRight(float s) {
    right = foward.cross(up);
    right = right.normalize();
    e = e + right*s;
    d = d + right*s;
    update();

}

void Camera::moveLeft(float s) {
    left = right * -1;
    e = e + left*s;
    d = d + left*s;
    update();

}

void Camera::moveUp(float s) {
    mup = right.cross(foward);
    mup = mup.normalize();
    e = e + mup*s;
    d = d + mup*s;
    update();
}

void Camera::moveDown(float s) {
    down = mup * -1;
    e = e + down*s;
    d = d + down*s;
    update();}