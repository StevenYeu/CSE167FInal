#include "Sphere.h"
#include "Vector3.h"


#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif


Sphere::Sphere(double radius, int slices, int stacks)
{
    this->radius = radius;
    this->slices = slices;
    this->stacks = stacks;
    box = boundingBox(radius * 2);
    this->toggle = false;
    this->shade = false;
}

void Sphere::render()
{
    
    if (toggle == true)
        box.createBbox(radius * 2);
    
    
    //glutSolidSphere(radius, slices, stacks);
    
    //glRotatef(-90, 1.0f, 0.0f, 0.0f);
    //glRotatef(180, 0.0f, 1.0f, 0.0f);
    
    
    tex.bind();
    
    if (shade == true) {
        glow->bind();
        glActiveTexture(GL_TEXTURE0);
        GLint Width = glGetUniformLocationARB(glow->getPid(), "pixelWidth");
        glUniform1f(Width, tex.width);
        GLint height = glGetUniformLocationARB(glow->getPid(), "pixelHeight");
        glUniform1f(height, tex.height);
        GLint Texture = glGetUniformLocationARB(glow->getPid(), "glowTex");
        glUniform1f(Texture, 0);
    }
    
    
    
    
    //gluQuadricDrawStyle(sphere, GLU_FILL);
    //gluQuadricTexture(sphere, TRUE);
    //gluQuadricNormals(sphere, GLU_SMOOTH);
    glColor3f(1, 1, 1);
    gluQuadricTexture(sphere, 1);
    
    
    gluSphere(sphere, radius, slices, stacks);
    tex.unbind();
    if (shade == true) {
        glow->unbind();
    }
    
}

void Sphere::toggleBox(){
    toggle = !toggle;
}


void Sphere::update(UpdateData& data)
{
    //
}


void Sphere::updateBox(Vector3 v) {
    box.setnewPosition(v);
}

boundingBox Sphere::getBbox() {
    return box;
}

void Sphere::loadTexture(const char* str){
    tex = Texture(str);
    sphere = gluNewQuadric();
    glow = new Shader("/Users/stevenyeu/Xcode Projects/CSE 167 Final v2/CSE 167 Final v2/glow.vs", "/Users/stevenyeu/Xcode Projects/CSE 167 Final v2/CSE 167 Final v2/glow.frag", true);
}

void Sphere::shaderToggle() {
    shade = !shade;
}