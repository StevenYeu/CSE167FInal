#include <iostream>


#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define _USE_MATH_DEFINES
#include <cmath>
#include "Window.h"
#include "Cube.h"
#include "House.h"
#include "Matrix4.h"
#include "vector3.h"
#include "Globals.h"
#include "Skybox.h"
#include "Texture.h"
#include "Camera.h"
#include "Robot.h"
#include "Terrain.h"
#include "MatrixTransform.h"


int Window::width  = 512;   //Set window width in pixels here
int Window::height = 512;   //Set window height in pixels here
bool Window::flag = false;	//-- set toggle flag to true at first
bool Window::collision_switch = false;   //-- set ball flag to false at first
bool Window::rasterize_switch = true;
bool Window::pt_tri = true;

bool explodeMars = false;
bool explodeSun = false;
bool explodeSaturn = false;
int lightup = 1;
float time1 = 0.0;
float time2 = 0.0;
float time3 = 0.0;


float Window::waterL;


Vector3 camera_pos = Vector3(0, 0, 0);


Matrix4 m_x, m_r, sa_x, saturn_r, s_x, s_r, exp_m;
Matrix4 stay;

MatrixTransform* stayTransform = new MatrixTransform();
MatrixTransform* stayTransform2 = new MatrixTransform();
MatrixTransform* stayTransform3 = new MatrixTransform();


MatrixTransform* trans_exp = new MatrixTransform();
MatrixTransform* trans_m = new MatrixTransform();
MatrixTransform* trans_sa = new MatrixTransform();
MatrixTransform* trans_s = new MatrixTransform();

MatrixTransform* trans_mr = new MatrixTransform();
MatrixTransform* trans_sar = new MatrixTransform();
MatrixTransform* trans_sr = new MatrixTransform();

Vector3 lastpoint = Vector3(0.0, 0.0, 0.0);
int movement = 0;

static float* pixels = new float[Window::width * Window::height * 3];

void Window::initialize(void)
{
    
    
    //Initialize skybox matrix:
    Globals::marsSystem->initData();
    Globals::sunSystem->initData();
    Globals::saturnSystem->initData();
    
    Globals::skybox->loadTexture();
    
    Globals::mars->loadTexture("red.ppm");
    //Globals::blue->loadTexture("blue.ppm");
    Globals::saturn->loadTexture("saturn.ppm");
    Globals::sun->loadTexture("sun.ppm");
    
    Globals::asteriod_mars->loadTexture("asteriod.ppm");
    Globals::asteriod_saturn->loadTexture("asteriod.ppm");
    Globals::asteriod_sun->loadTexture("asteriod.ppm");
    
    m_x.identity();
    trans_m->setMatrix(m_x);
    sa_x.identity();
    trans_sa->setMatrix(sa_x);
    s_x.identity();
    trans_s->setMatrix(s_x);
    
    m_r.identity();
    trans_mr->setMatrix(m_r);
    saturn_r.identity();
    trans_sar->setMatrix(saturn_r);
    s_r.identity();
    trans_sr->setMatrix(s_r);
    
    exp_m.identity();
    trans_exp->setMatrix(exp_m);
    
    stay.identity();
    stayTransform->setMatrix(stay);
    stayTransform2->setMatrix(stay);
    stayTransform3->setMatrix(stay);
    
    Globals::drawData.setMatrix(Globals::camera->getInverseMatrix());
    
    // move the world and stuff
    
    Globals::root->addChild(Globals::skybox);
    Globals::root->addChild(stayTransform);
    Globals::root->addChild(stayTransform2);
    Globals::root->addChild(stayTransform3);

    // init explosion
//    Globals::root->addChild(Globals::explosive_c);
//    Globals::root->addChild(trans_exp);
//    trans_exp->addChild(Globals::initSystem);
    
    Globals::root->addChild(Globals::initSystem);
    
    Globals::root->addChild(Globals::camera_c);
    
    //mars
    Globals::root->addChild(Globals::mars_c);
    Globals::root->addChild(trans_m);
    trans_m->addChild(Globals::mars);
    
    // saturn
    Globals::root->addChild(Globals::saturn_c);
    Globals::root->addChild(trans_sa);
    trans_sa->addChild(Globals::saturn);
    
    // sun
    Globals::root->addChild(Globals::sun_c);
    Globals::root->addChild(trans_s);
    trans_s->addChild(Globals::sun);
    
}

//----------------------------------------------------------------------------
// Callback method called when system is idle.
// This is called at the start of every new "frame" (qualitatively)
void Window::idleCallback()
{
    //Set up a static time delta for update calls
    Globals::updateData.dt = 1.0/60.0;// 60 fps
    
    if (time1 >= 1.0){
        time1 = 0.0;
    }
    
    if (time2 >= 1.0){
        time2 = 0.0;
    }
    
    if (time3 >= 1.0){
        time3 = 0.0;
    }
    
    
    camera_pos = Globals::camera_c->move(time1);
    if (flag == true){
        Globals::camera->e = camera_pos;
        Globals::camera->update();
    }
    
    Vector3 pos = Globals::explosive_c->move(time1);
    Matrix4 newpos_matrix;
    newpos_matrix.makeTranslate(pos[0], pos[1], pos[2]);
    trans_exp->setMatrix(newpos_matrix);
    
    
    if (!explodeMars) {
        calcPos(Globals::mars_c->move(time2), trans_m, Globals::mars);
    }
    if (!explodeSaturn) {
        calcPos(Globals::saturn_c->move(time1), trans_sa, Globals::saturn);
    }
    if (!explodeSun) {
        calcPos(Globals::sun_c->move(time3), trans_s, Globals::sun);
    }
    
    if (collision_switch) {
        calcPos(Globals::mars_ac->move(time2), trans_mr, Globals::asteriod_mars);
        calcPos(Globals::saturn_ac->move(time1), trans_sar, Globals::asteriod_saturn);
        calcPos(Globals::sun_ac->move(time3), trans_sr, Globals::asteriod_sun);
        
        
        if (Globals::mars->getBbox().detectCollision(Globals::mars->getBbox(), Globals::asteriod_mars->getBbox())){
            explodeMars = true;
            trans_m->addChild(Globals::marsSystem);
            trans_m->removeChild(Globals::mars);
            trans_mr->removeChild(Globals::asteriod_mars);
        }
        
        if (Globals::sun->getBbox().detectCollision(Globals::sun->getBbox(), Globals::asteriod_sun->getBbox())){
            explodeSun = true;
            trans_s->addChild(Globals::sunSystem);
            trans_s->removeChild(Globals::sun);
            trans_sr->removeChild(Globals::asteriod_sun);
        }
        
        if (Globals::saturn->getBbox().detectCollision(Globals::saturn->getBbox(), Globals::asteriod_saturn->getBbox())){
            explodeSaturn = true;
            trans_sa->addChild(Globals::saturnSystem);
            trans_sa->removeChild(Globals::saturn);
            trans_sar->removeChild(Globals::asteriod_saturn);
            
        }
        
    }
    
    
    
    
    
    
    
    time1 += 0.005;
    time2 += 0.004;
    time3 += 0.003;

    
    Globals::camera->update();
    
    //Call the display routine to draw the cube
    displayCallback();
}

//----------------------------------------------------------------------------
// Callback method called by GLUT when graphics window is resized by the user
void Window::reshapeCallback(int w, int h)
{
    
    width = w;                                                       //Set the window width
    height = h;                                                      //Set the window height
    float aspect = (float)width / (float)height;
    float FOV = 60.0 / 180.0 * M_PI;
    
    glViewport(0, 0, w, h);                                          //Set new viewport size
    glMatrixMode(GL_PROJECTION);                                     //Set the OpenGL matrix mode to Projection
    glLoadIdentity();                                                //Clear the projection matrix by loading the identity
    gluPerspective(60.0, double(width) / (double)height, 1.0, 1000.0); //Set perspective projection viewing frustum
    
    
}

//----------------------------------------------------------------------------
// Callback method called by GLUT when window readraw is necessary or when glutPostRedisplay() was called.
void Window::displayCallback()
{
    
    Globals::drawData.setMatrix(Globals::camera->getInverseMatrix());
    //Clear color and depth buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glMatrixMode(GL_MODELVIEW);
    
    glPushMatrix();
    
    Globals::root->draw(Globals::drawData);
    
    
    glPopMatrix();
    //Tell OpenGL to clear any outstanding commands in its command buffer
    //This will make sure that all of our commands are fully executed before
    //we swap buffers and show the user the freshly drawn frame
    glFlush();
    
    //Swap the off-screen buffer (the one we just drew to) with the on-screen buffer
    glutSwapBuffers();
}


//TODO: Keyboard callbacks!

void Window::keyboardCallback(unsigned char key, int x, int y)
{
    
    switch (key) {
        case 'b':
            Globals::mars->toggleBox();
            Globals::sun->toggleBox();
            Globals::saturn->toggleBox();
            Globals::asteriod_mars->toggleBox();
            Globals::asteriod_saturn->toggleBox();
            Globals::asteriod_sun->toggleBox();
            break;
        case 'c':
            Globals::mars_c->toggleCurve();
            Globals::sun_c->toggleCurve();
            Globals::saturn_c->toggleCurve();
            Globals::mars_ac->toggleCurve();
            Globals::saturn_ac->toggleCurve();
            Globals::sun_ac->toggleCurve();
            break;
        case 'a':
            flag = !flag;
            if (flag == false) {
                Vector3 d = Vector3(3, 0, 200);
                Vector3 e = Vector3(0,0,0);
                Vector3 u = Vector3(0,1,0);
                Globals::camera->set(d , e, u);
                Globals::camera->update();
            }
            break;
        case 's':
            Globals::mars->shaderToggle();
            Globals::sun->shaderToggle();
            Globals::saturn->shaderToggle();
            Globals::asteriod_mars->shaderToggle();
            Globals::asteriod_saturn->shaderToggle();
            Globals::asteriod_sun->shaderToggle();
            break;
        case 'e':
            collision_switch = !collision_switch;
            Globals::root->addChild(Globals::mars_ac);
            Globals::root->addChild(trans_mr);
            trans_mr->addChild(Globals::asteriod_mars);
            
            Globals::root->addChild(Globals::saturn_ac);
            Globals::root->addChild(trans_sar);
            trans_sar->addChild(Globals::asteriod_saturn);
            
            Globals::root->addChild(Globals::sun_ac);
            Globals::root->addChild(trans_sr);
            trans_sr->addChild(Globals::asteriod_sun);
            break;
        case 'q':
            exit(0);
            break;
            
            
    }
    
}

//TODO: Function Key callbacks!

//TODO: Mouse callbacks!
void Window::mouseCallback(int button, int state, int x, int y)
{
    
    lastpoint = trackBallMapping(x, y);
    switch (button){
        case GLUT_LEFT_BUTTON:
            if (state == GLUT_DOWN){
                movement = GLUT_LEFT_BUTTON;
                
            }
            break;
        case GLUT_RIGHT_BUTTON:
            if (state == GLUT_DOWN){
                movement = GLUT_RIGHT_BUTTON;
                
            }
            break;
        case GLUT_MIDDLE_BUTTON:
            if (state == GLUT_DOWN){
                movement = GLUT_MIDDLE_BUTTON;
            }
            break;
            
    }
    
}

//TODO: Mouse Motion callbacks!
void Window::motionCallback(int x, int y)
{
    Vector3 direction;
    float rot_angle;
    Vector3 curPoint;
    float velocity;
    Matrix4 move;
    
    curPoint = trackBallMapping(x, y);
    direction = curPoint - lastpoint;
    
    Vector3 forward = Globals::camera->d - Globals::camera->e;
    forward = forward.normalize();
    Vector3 backward = forward.negate();
    
    Vector3 right = forward.cross(Globals::camera->up);
    Vector3 left = right.negate();
    
    Vector3 up = right.cross(forward);
    up = up.normalize();
    
    Vector3 down = up.negate();
    
    Vector3 lookAt = Globals::camera->d - Globals::camera->e;
    
    
    switch (movement) {
        case GLUT_LEFT_BUTTON:
            
            velocity = direction.magnitude();
            if (velocity > 0.0001){
                Vector3 rotAxis;
                rotAxis = lastpoint.cross(curPoint);
                
                rot_angle = asin(rotAxis.magnitude() / (lastpoint.magnitude() * curPoint.magnitude()));
                rot_angle = rot_angle * 3.1415926 / 180.0;
                rotAxis = rotAxis.normalize();
                
                Matrix4 r;
                r = r.makeRotateArbitrary(rotAxis, 16.0 * rot_angle);
                
                Globals::camera->d = Globals::camera->e + r* lookAt;
                
                lastpoint = curPoint;
            }
            Globals::camera->update();
            
            
            break;
            
        case GLUT_RIGHT_BUTTON:
            
            
            if (direction[0] > 0.0){
                Globals::camera->e = Globals::camera->e + right;
                Globals::camera->d = Globals::camera->d + right;
            }
            if (direction[0] < 0.0){
                Globals::camera->e = Globals::camera->e + left;
                Globals::camera->d = Globals::camera->d + left;
            }
            if (direction[1] > 0.0){
                Globals::camera->e = Globals::camera->e + up;
                Globals::camera->d = Globals::camera->d + up;
            }
            if (direction[1] < 0.0){
                Globals::camera->e = Globals::camera->e + down;
                Globals::camera->d = Globals::camera->d + down;
            }
            Globals::camera->update();
            
            break;
            
        case GLUT_MIDDLE_BUTTON:
            if (direction[1] > 0.0){
                Globals::camera->e = Globals::camera->e + forward;
                Globals::camera->d = Globals::camera->d + forward;
            }
            if (direction[1] < 0.0){
                Globals::camera->e = Globals::camera->e + backward;
                Globals::camera->d = Globals::camera->d + backward;
            }
            Globals::camera->update();
            
            break;
            
    }
    
    
}

Vector3 Window::trackBallMapping(int x, int y)
{
    Vector3 v;    // Vector v is the synthesized 3D position of the mouse location on the trackball
    float d;     // this is the depth of the mouse location: the delta between the plane through the center of the trackball and the z position of the mouse
    v[0] = (2.0*x - width) / width;   // this calculates the mouse X position in trackball coordinates, which range from -1 to +1
    v[1] = (height - 2.0*y) / height;   // this does the equivalent to the above for the mouse Y position
    v[2] = 0.0;   // initially the mouse z position is set to zero, but this will change below
    d = v.magnitude();    // this is the distance from the trackball's origin to the mouse location, without considering depth (=in the plane of the trackball's origin)
    d = (d<1.0) ? d : 1.0;   // this limits d to values of 1.0 or less to avoid square roots of negative values in the following line
    v[2] = sqrtf(1.001 - d*d);  // this calculates the Z coordinate of the mouse position on the trackball, based on Pythagoras: v.z*v.z + d*d = 1*1
    v = v.normalize(); // Still need to normalize, since we only capped d, not v.
    return v;  // return the mouse location on the surface of the trackball
}

void Window::calcPos(Vector3 pos, MatrixTransform* m, Sphere* s){
    
    Matrix4 newpos_matrix;
    newpos_matrix.makeTranslate(pos[0], pos[1], pos[2]);
    s->updateBox(pos);
    m->setMatrix(newpos_matrix);
    
}







