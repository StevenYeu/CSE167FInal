#ifndef CSE167_Window_h
#define CSE167_Window_h

#include "Vector3.h"
#include "Vector4.h"
#include "MatrixTransform.h"
#include "Matrix4.h"
#include "Sphere.h"

class Window	  // OpenGL output window related routines
{
    
public:
    
    static int width, height; 	            // window size
    static float waterL;
    
    static bool flag;						// -- toggle flag
    static bool collision_switch;						// -- ball flag
    static bool rasterize_switch;			// switch between openGL and my own software rasterizer
    static bool pt_tri;						// switch between drawPoint and drawTriangle
    
    
    static void calcPos(Vector3, MatrixTransform*, Sphere*);
    
    static void initialize(void);
    static void idleCallback(void);
    static void reshapeCallback(int, int);
    static void displayCallback(void);
    
    static void keyboardCallback(unsigned char, int, int);
    static void mouseCallback(int, int, int, int);
    
    static void motionCallback(int, int);
    static Vector3 trackBallMapping(int, int);
    
    static void removeStar();
    static void createStar();
    
};

#endif

