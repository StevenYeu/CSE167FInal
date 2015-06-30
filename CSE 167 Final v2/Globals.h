#ifndef CSE167_Globals_h
#define CSE167_Globals_h

#include "Camera.h"
#include "Cube.h"
#include "Sphere.h"				//add for extra credit
#include "House.h"				//add for pa2
#include "OBJObject.h"			//add for pa2
#include "Light.h"
#include "DrawData.h"
#include "UpdateData.h"
#include "Drawable.h"
#include "Matrix4.h"			//add for pa3
#include "Skybox.h"				//add for pa5
#include "Group.h"				//add for pa5
#include "Robot.h"				//add for pa5
#include "Terrain.h"
#include "MatrixTransform.h"
#include "Vector4.h"

#include "bazierCurve.h"		//add for final
#include "particleSystem.h"


class Globals
{
    
public:
    
    static Camera* camera;
    
    static bazierCurve* explosive_c;
    static bazierCurve* camera_c;
    static bazierCurve* mars_c;
    static bazierCurve* saturn_c;
    static bazierCurve* sun_c;
    static bazierCurve* blue_c;
    static bazierCurve* mars_ac;
    static bazierCurve* saturn_ac;
    static bazierCurve* sun_ac;
    static bazierCurve* blue_ac;
    
    static Group* root;
    
    static Sphere* mars;
    static Sphere* saturn;
    static Sphere* sun;
    static Sphere* blue;
    static Sphere* asteriod_mars;
    static Sphere* asteriod_saturn;
    static Sphere* asteriod_sun;
    static Sphere* asteriod_blue;
    
    static particleSystem* marsSystem;
    static particleSystem* sunSystem;
    static particleSystem* saturnSystem;
    static particleSystem* initSystem;
    
    static Skybox* skybox;
    
    
    
    
    static Light* light;
    static DrawData drawData;
    static UpdateData updateData;
    //Feel free to add more member variables as needed
    
    
};

#endif
