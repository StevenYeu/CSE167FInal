#define _USE_MATH_DEFINES
#include <cmath>
#include "Skybox.h"


#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "Window.h"
#include "vector3.h"
#include "Globals.h"
#include "math.h"
#include "Texture.h"
#include "Geode.h"



Skybox::Skybox(float size)
{
    this->size = size;
    
}


Skybox::~Skybox()
{
}

void Skybox::render()
{
    float halfSize = 950.0 / 2.0;
    
    // left
    left.bind();
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glTexCoord2f(0, 0); glVertex3f(-halfSize, halfSize, halfSize);
    glTexCoord2f(1, 0); glVertex3f(-halfSize, halfSize, -halfSize);
    glTexCoord2f(1, 1); glVertex3f(-halfSize, -halfSize, -halfSize);
    glTexCoord2f(0, 1); glVertex3f(-halfSize, -halfSize, halfSize);
    glEnd();
    left.unbind();
    
    
    // Draw back face:
    back.bind();
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glNormal3f(0.0, 0.0, -1.0);
    glTexCoord2f(0, 0); glVertex3f(-halfSize, halfSize, -halfSize);
    glTexCoord2f(1, 0); glVertex3f(halfSize, halfSize, -halfSize);
    glTexCoord2f(1, 1); glVertex3f(halfSize, -halfSize, -halfSize);
    glTexCoord2f(0, 1); glVertex3f(-halfSize, -halfSize, -halfSize);
    
    glEnd();
    back.unbind();
    
    // Draw right
    right.bind();
    glBegin(GL_QUADS);
    glNormal3f(1.0, 0.0, 0.0);
    glTexCoord2f(1, 0); glVertex3f(halfSize, halfSize, halfSize);
    glTexCoord2f(0, 0); glVertex3f(halfSize, halfSize, -halfSize);
    glTexCoord2f(0, 1); glVertex3f(halfSize, -halfSize, -halfSize);
    glTexCoord2f(1, 1); glVertex3f(halfSize, -halfSize, halfSize);
    glEnd();
    right.unbind();
    
    // draw top
    top.bind();
    glBegin(GL_QUADS);
    glNormal3f(0.0, 1.0, 0.0);
    glTexCoord2f(0, 0); glVertex3f(-halfSize, halfSize, halfSize);
    glTexCoord2f(1, 0); glVertex3f(halfSize, halfSize, halfSize);
    glTexCoord2f(1, 1); glVertex3f(halfSize, halfSize, -halfSize);
    glTexCoord2f(0, 1); glVertex3f(-halfSize, halfSize, -halfSize);
    glEnd();
    top.bind();
    
    // draw bottom
    base.bind();
    glBegin(GL_QUADS);
    // Draw bottom side:
    glNormal3f(0.0, -1.0, 0.0);
    glTexCoord2f(0, 0); glVertex3f(-halfSize, -halfSize, -halfSize);
    glTexCoord2f(1, 0); glVertex3f(halfSize, -halfSize, -halfSize);
    glTexCoord2f(1, 1); glVertex3f(halfSize, -halfSize, halfSize);
    glTexCoord2f(0, 1); glVertex3f(-halfSize, -halfSize, halfSize);
    glEnd();
    base.bind();
    
    front.bind();
    glBegin(GL_QUADS);
    // Draw front face:
    glNormal3f(0.0, 0.0, 1.0);
    glTexCoord2f(1, 0); glVertex3f(-halfSize, halfSize, halfSize);
    glTexCoord2f(0, 0); glVertex3f(halfSize, halfSize, halfSize);
    glTexCoord2f(0, 1); glVertex3f(halfSize, -halfSize, halfSize);
    glTexCoord2f(1, 1); glVertex3f(-halfSize, -halfSize, halfSize);
    glEnd();
    front.unbind();
}

void Skybox::update(UpdateData& data)
{
    //
    
    
}

void Skybox::loadTexture()
{
//    left = Texture("cwd_lf.ppm");
//    right = Texture("cwd_rt.ppm");
//    back = Texture("cwd_bk.ppm");
//    top = Texture("cwd_up.ppm");
//    base = Texture("cwd_dn.ppm");
//    front = Texture("cwd_ft.ppm");
    
//    left = Texture("BlueSpace/left.ppm");
//    right = Texture("BlueSpace/right.ppm");
//    back = Texture("BlueSpace/back.ppm");
//    top = Texture("BlueSpace/up.ppm");
//    base = Texture("BlueSpace/down.ppm");
//    front = Texture("BlueSpace/front.ppm");
//    
//    left = Texture("BluePlanet/left.ppm");
//    right = Texture("BluePlanet/right.ppm");
//    back = Texture("BluePlanet/back.ppm");
//    top = Texture("BluePlanet/up.ppm");
//    base = Texture("BluePlanet/down.ppm");
//    front = Texture("BluePlanet/front.ppm");
//    
    left = Texture("GreenSpace/left.ppm");
    right = Texture("GreenSpace/right.ppm");
    back = Texture("GreenSpace/back.ppm");
    top = Texture("GreenSpace/up.ppm");
    base = Texture("GreenSpace/down.ppm");
    front = Texture("GreenSpace/front.ppm");


    
}

