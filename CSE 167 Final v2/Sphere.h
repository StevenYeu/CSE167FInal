#ifndef CSE167_Sphere_h
#define CSE167_Sphere_h

#include <stdlib.h>
#include <GLUT/GLUT.h>

#include <iostream>
#include "Geode.h"
#include "boundingBox.h"
#include "Texture.h"
#include "Shader.h"



class Sphere : public Geode
{
    
public:
    
    double radius;
    double dx,dy;
    
    int slices, stacks;
    
    Sphere(double, int, int);
    
    bool toggle;
    bool shade;
    
    void toggleBox();
    void shaderToggle();
    
    boundingBox box;
    
    void updateBox(Vector3);
    
    boundingBox getBbox();
    
    virtual void render();
    virtual void update(UpdateData&);
    
    Texture tex;
    GLUquadric* sphere;
    Shader* glow;
    
    void loadTexture(const char*);
};

#endif
