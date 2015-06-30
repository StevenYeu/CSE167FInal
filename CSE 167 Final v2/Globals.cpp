#include "Globals.h"




//Curve camera view
Vector3 cv0 = Vector3(-16, -6, 6)*10;
Vector3 cv1 = Vector3(12, 6, 20)*10;
Vector3 cv2 = Vector3(58, 22, 8)*10;
Vector3 cv3 = Vector3(40, 12, -16)*10;
Vector3 cv4 = Vector3(-44, -18, -8)*10;
vector<Vector3> camerarray = { cv0, cv1, cv2, cv3, cv4, cv0 };



//Curve camera view
Vector3 ev0 = Vector3(-16, -6, 6)*11;
Vector3 ev1 = Vector3(12, 6, 20)*11;
Vector3 ev2 = Vector3(58, 22, 8)*11;
Vector3 ev3 = Vector3(40, 12, -16)*11;
Vector3 ev4 = Vector3(-44, -18, -8)*11;
vector<Vector3> evarray = { ev0, ev1, ev2, ev3, ev4, ev0 };

//Curve mars

Vector3 m0 = Vector3(0, 0, 0)*10;
Vector3 m1 = Vector3(5, 5, 3)*10;
Vector3 m2 = Vector3(-5, 7, 5)*10;
Vector3 m3 = Vector3(-7, -4, 2)*10;
Vector3 m4 = Vector3(3, -3, 1)*10;
Vector3 m5 = Vector3(-5, -5, -3)*10;
vector<Vector3> marsarray = { m0, m1, m2, m3, m4, m5, m0 };
vector<Vector3> mars_r = { m0, m5, m4, m3, m2, m1, m0 };

//Curve saturn
Vector3 sa0 = Vector3(-2, -5, 5)*10;
Vector3 sa1 = Vector3(1, 5, 12)*10;
Vector3 sa2 = Vector3(6, 13, 4)*10;
Vector3 sa3 = Vector3(11, 8, -2)*10;
Vector3 sa4 = Vector3(-5, -15, -2)*10;
vector<Vector3> sa_array = { sa0, sa1, sa2, sa3, sa4, sa0 };
vector<Vector3> sa_r = { sa0, sa4, sa3, sa2, sa1, sa0 };


//Curve sun
Vector3 s0 = Vector3(-5, -5, 0)*10;
Vector3 s1 = Vector3(0, 0, 5)*10;
Vector3 s2 = Vector3(5, 5, 10)*10;
Vector3 s3 = Vector3(0, 7, 5)*10;
Vector3 s4 = Vector3(-5, 5, 0)*10;
Vector3 s5 = Vector3(0, 0, 5)*10;
Vector3 s6 = Vector3(5, 3, 8)*10;
Vector3 s7 = Vector3(0, -5, 3)*10;
Vector3 s8 = Vector3(-10, -10, -5)*10;
vector<Vector3> sun_array = { s0, s1, s2, s3, s4, s5, s6, s7 ,s8, s0};
vector<Vector3> sun_r = { s0, s8, s7, s6, s5, s4, s3, s2, s1, s0 };

//Curve blue
// To be implemented

Camera* Globals::camera = new Camera();

bazierCurve* Globals::explosive_c = new bazierCurve(evarray);

bazierCurve* Globals::mars_c = new bazierCurve(marsarray);
bazierCurve* Globals::saturn_c = new bazierCurve(sa_array);
bazierCurve* Globals::sun_c = new bazierCurve(sun_array);
//bazierCurve* Globals::blue_c = new bazierCurve(blue_array);

bazierCurve* Globals::mars_ac = new bazierCurve(mars_r);
bazierCurve* Globals::saturn_ac = new bazierCurve(sa_r);
bazierCurve* Globals::sun_ac = new bazierCurve(sun_r);

bazierCurve* Globals::camera_c = new bazierCurve(camerarray);

Group* Globals::root = new Group();

Sphere* Globals::mars = new Sphere(3.5, 20, 20);
Sphere* Globals::saturn = new Sphere(3, 20, 20);
Sphere* Globals::sun = new Sphere(1, 20, 20);
Sphere* Globals::blue = new Sphere(0.1, 20, 20);

Sphere* Globals::asteriod_mars = new Sphere(2, 20, 20);
Sphere* Globals::asteriod_saturn = new Sphere(1.5, 20, 20);
Sphere* Globals::asteriod_sun = new Sphere(1, 20, 20);
Sphere* Globals::asteriod_blue = new Sphere(0.1, 20, 20);

particleSystem* Globals::initSystem = new particleSystem();

particleSystem* Globals::marsSystem = new particleSystem(1, 0.7, 0.0, 0.0);
particleSystem* Globals::sunSystem = new particleSystem(1, 1.0, 0.5, 0.0);
particleSystem* Globals::saturnSystem = new particleSystem(1, 0.0, 0.5, 0.5);


//particleSystem* Globals::marsSystem = new particleSystem();
//particleSystem* Globals::sunSystem = new particleSystem();
//particleSystem* Globals::saturnSystem = new particleSystem();

Skybox* Globals::skybox = new Skybox(2000);

Light* Globals::light = new Light();

DrawData Globals::drawData = DrawData();
UpdateData Globals::updateData = UpdateData();

