#ifndef CSE167_Camera_h
#define CSE167_Camera_h

#include "Matrix4.h"
#include "Vector3.h"

class Camera
{
private:
    
protected:
    
    Matrix4 c;   //Camera Matrix
    Matrix4 ci;  //Inverse of Camera Matrix
    
public:
    
    Vector3 e;   //Center of Projection
    Vector3 d;   //Look At
    Vector3 up;  //Up Vector ^
    Vector3 foward;
    Vector3 left;
    Vector3 right;
    Vector3 backward;
    Vector3 down;
    Vector3 mup;
    
    Camera(void);
    ~Camera(void);
    
    void update(void);
    
    Matrix4& getMatrix(void);
    Matrix4& getInverseMatrix(void);
    
    void set(Vector3& d, Vector3& e, Vector3& up);

	void orbitTrack(Vector3, float);
    void moveFoward(float);
    void moveBackward(float);
    void moveLeft(float);
    void moveRight(float);
    void moveDown(float);
    void moveUp(float);
    
};

#endif
