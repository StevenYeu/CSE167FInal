#include "Light.h"
#include "Window.h"
#include <iostream>

#ifdef _WIN32
#include <GL/glut.h>
#else
#include <GLUT/glut.h>
#endif


Light::Light()
{
    //this->toWolrd.identity();
    ambientColor = Color::ambientDefault();
    diffuseColor = Color::diffuseDefault();
    specularColor = Color::specularDefault();
    
    constantAttenuation = 1.0000;
    linearAttenuation = 0.00;
    quadraticAttenuation = 0.0000;
}

Light::~Light()
{
    //Delete any dynamically allocated memory/objects here
}

void Light::bind(int id)
{
    if(id < 0 || id > 7) {
        std::cout << "ERROR: The light bind ID " << id << " is not valid!" << std::endl;
        return;
    }
    
    //Set the bindID
    bindID = id;
    
    //Configure the light at the bindID
    glEnable(GL_LIGHT0 + bindID);
    
    //Configure the color of the light
    glLightfv(GL_LIGHT0 + bindID, GL_AMBIENT, ambientColor.ptr());
    glLightfv(GL_LIGHT0 + bindID, GL_DIFFUSE, diffuseColor.ptr());
    glLightfv(GL_LIGHT0 + bindID, GL_SPECULAR, specularColor.ptr());
    
    //Configure the attenuation properties of the light
    //Constant Attenuation
    //Linear Attenuation
    glLightf(GL_LIGHT0 + bindID, GL_QUADRATIC_ATTENUATION, quadraticAttenuation);
    glLightf(GL_LIGHT0 + bindID, GL_LINEAR_ATTENUATION, linearAttenuation);
    glLightf(GL_LIGHT0 + bindID, GL_CONSTANT_ATTENUATION, constantAttenuation);
    
   
    
    //Position the light
    glLightfv(GL_LIGHT0 + bindID, GL_POSITION, position.ptr());
    
    //Setup spotlight direction, angle, and exponent here
    if (isSpot) {
        glLightf(GL_LIGHT0 + id, GL_SPOT_EXPONENT, exponent);
        glLightf(GL_LIGHT0 + id, GL_SPOT_CUTOFF, cutOff);
        glLightfv(GL_LIGHT0 + id, GL_SPOT_DIRECTION, spotDirection.ptr());
    }
}

void Light::unbind(void)
{
    glDisable(GL_LIGHT0 + bindID);
    bindID = -1;
}

void Light::move(float x, float y, float z) {
    Vector4 new_pos = Vector4(x, y, z, 0);
    position = position + new_pos;
}

void Light::setCutOff(float cf) {
    cutOff = cf;
}

void Light::setExponent(float exp) {
    exponent = exp;
}

void Light::setSpotLight(Vector3 d) {
    spotDirection = d;
    isSpot = true;
}

void Light::setAttenuation(float c, float l, float q) {
    constantAttenuation = c;
    linearAttenuation = l;
    quadraticAttenuation = q;
}

void Light::setAmbient(Color a) {
    ambientColor = a;
}

void Light::setDiffuse(Color d) {
    diffuseColor= d;
}

void Light::setSpecular(Color s) {
    specularColor = s;
}

void Light::orbitTrack(Vector3 v, float angle) {
    Matrix4 orbit;
    float pi = 3.14159265358979323846;
    float rads = angle * (pi / 180.0);
    orbit = orbit.makeRotateArbitrary(v, rads);
    position = orbit * position;
    //toWolrd = or * toWolrd;
}

void Light::orbitSpotTrack(Vector3 v, float angle) {
    Matrix4 orbit;
    float pi = 3.14159265358979323846;
    float rads = angle * (pi / 180.0);
    orbit.makeRotateArbitrary(v, rads);
    spotDirection = orbit *spotDirection;
}

Vector4 Light::getPosition() {
    Vector4 pos;
    float x, y, z, w;
    x = toWolrd.get(3, 0);
    y = toWolrd.get(3, 1);
    z = toWolrd.get(3, 2);
    w = toWolrd.get(3, 3);
    pos.set(x, y, z, w);
    return pos;
}

void Light::setPosition(float x, float y, float z, float w) {
    position.set(x, y, z, w);
    
}

void Light::render() {
    //s.render(data);
    
//    Color pointAmbientM(.2, .2, .2, 1.0);
//    Color pointDiffuseM(.8, .8, .8, 1);
//    Color pointSpecularM(0, 0, 0, 1.0);
//    
//    material.specularColor = pointDiffuseM;
//    material.ambientColor = pointAmbientM;
//    material.diffuseColor = pointSpecularM;
//    material.shininess = 1.0;
//    
//    materials.apply();
    glColor3f(1, 1, 1);
    glutSolidSphere(10, 25, 25);
}



void Light::setToWorld() {
    toWolrd.set(3, 0, position[0]);
    toWolrd.set(3, 1, position[1]);
    toWolrd.set(3, 2, position[2]);
    toWolrd.set(3, 3, position[3]);
    
    
}

float Light::getCut() {
    return cutOff;
}

void Light::update(UpdateData& data) {
}

float Light::getExp() {
    return exponent;
}