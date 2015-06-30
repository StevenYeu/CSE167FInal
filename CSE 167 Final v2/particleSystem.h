#ifndef CSE167_PARTICLESYSTEM_h
#define CSE167_PARTICLESYSTEM_h

#include "Geode.h"
#include <GLUT/GLUT.h>
#include "Texture.h"
#include "Shader.h"
#include <math.h>

#define	MAX_PARTICLES 3000   // Number Of Particles To Create

class particleSystem : public Geode
{
public:

	
    // 0 init burst
    // 1 explostion
    // 2 streak;
    float mode = 0;
    float red;
    float green;
    float blue;
    
    Texture pTex;
    

	bool    g_rainbow = true;
	float	g_slowdown = 2.0f;
	float   g_xspeed = 0.0f;
	float   g_yspeed = 0.0f;
	float	g_zoom = -40.0f;
	GLuint	g_col = 0;
	GLuint	g_delay = 0;           

	static  GLfloat COLORS[12][3];

	typedef struct {
		bool  active;
		float life;
		float fade;
		float r;
		float g;
		float b;
		float x;
		float y;
		float z;
		float xi;
		float yi;
		float zi;
		float xg;
		float yg;
		float zg;
	} particles;


	particles g_particle[MAX_PARTICLES]; 


	particleSystem();
    particleSystem(int,float,float,float);

	virtual ~particleSystem();

	virtual void render();
	virtual void update(UpdateData&);

	bool initData();
};
#endif