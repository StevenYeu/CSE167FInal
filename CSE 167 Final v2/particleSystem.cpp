#include "particleSystem.h"


 GLfloat particleSystem::COLORS[12][3]= {     // Rainbow Of Colors
	{ 1.0f, 0.5f, 0.5f }, { 1.0f, 0.75f, 0.5f }, { 1.0f, 1.0f, 0.5f }, { 0.75f, 1.0f, 0.5f },
	{ 0.5f, 1.0f, 0.5f }, { 0.5f, 1.0f, 0.75f }, { 0.5f, 1.0f, 1.0f }, { 0.5f, 0.75f, 1.0f },
	{ 0.5f, 0.5f, 1.0f }, { 0.75f, 0.5f, 1.0f }, { 1.0f, 0.5f, 1.0f }, { 1.0f, 0.5f, 0.75f }
};

particleSystem::particleSystem()
{
    mode = 0;
}

particleSystem::particleSystem(int m, float r, float g, float b)
{
    mode = m;
    red = r;
    green = g;
    blue = b;
}


particleSystem::~particleSystem()
{
}



void particleSystem::render() {
    pTex.bind();
    


    glDisable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	for (int i = 0; i<MAX_PARTICLES; i++) {
		if (g_particle[i].active) {
			float x = g_particle[i].x;
			float y = g_particle[i].y;
			float z = g_particle[i].z + g_zoom;

			glColor4f(g_particle[i].r, g_particle[i].g, g_particle[i].b, g_particle[i].life);

            
			glBegin(GL_TRIANGLE_STRIP);
            glTexCoord2d(1, 1);  glVertex3f(x + 0.5f, y + 0.5f, z);
			glTexCoord2d(0, 1);  glVertex3f(x - 0.5f, y + 0.5f, z);
			glTexCoord2d(1, 0);  glVertex3f(x + 0.5f, y - 0.5f, z);
            glTexCoord2d(0, 0);  glVertex3f(x - 0.5f, y - 0.5f, z);
			glEnd();

			g_particle[i].x += g_particle[i].xi / (g_slowdown * 1000);
			g_particle[i].y += g_particle[i].yi / (g_slowdown * 1000);
			g_particle[i].z += g_particle[i].zi / (g_slowdown * 1000);

			g_particle[i].xi += g_particle[i].xg;
			g_particle[i].yi += g_particle[i].yg;
			g_particle[i].zi += g_particle[i].zg;
			g_particle[i].life -= g_particle[i].fade;

			if (g_particle[i].life < 0.0f) {
				g_particle[i].life = 1.0f;
				g_particle[i].fade = float(rand() % 100) / 1000.0f + 0.003f;
                
			}

			
            
		}
	}
    pTex.unbind();
    
    glDisable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);

    
}

bool particleSystem::initData() {
    pTex = Texture("Particle.ppm");
    

	glShadeModel(GL_SMOOTH);
	glClearDepth(1.0f);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
	for (int i = 0; i<MAX_PARTICLES; i++) {
		g_particle[i].active = true;
		g_particle[i].life = 1.0f;
		g_particle[i].fade = float(rand() % 100) / 1000.0f + 0.003f;
        
        
        if (mode == 0) {
            g_particle[i].r = COLORS[(i + 1) / (MAX_PARTICLES / 12)][0];
            g_particle[i].g = COLORS[(i + 1) / (MAX_PARTICLES / 12)][1];
            g_particle[i].b = COLORS[(i + 1) / (MAX_PARTICLES / 12)][2];	
        }
        else if (mode == 1 || mode == 2) {
            g_particle[i].r = red;
            g_particle[i].g = green;
            g_particle[i].b = blue;

        
        }
        
		
        
        if (mode == 2 ) {
            float x = float((rand() % 50) - 25.0f)*10.0f;
            float y = float((rand() % 50) - 26.0f)*10.0f;
            float z = float((rand() % 50) - 26.0f)*10.0f;
            
            float r = sqrt(x*x+y*y+z*z);
            float theta = acosf(z/r);
            float rho = atanf(y/x);
            g_particle[i].zi = r;
            g_particle[i].xi = theta;
            g_particle[i].yi = rho;
        }
        
        
        if (mode == 1 || mode == 0) {
            g_particle[i].xi = float((rand() % 50) - 25.0f)*5.0f;
            g_particle[i].yi = float((rand() % 50) - 25.0f)*5.0f;
            g_particle[i].zi = float((rand() % 50) - 25.0f)*5.0f;
        }
        
		
		g_particle[i].xg = 0.0f;
		g_particle[i].yg = 0.0f;
		g_particle[i].zg = 0.0f;
	}
	return true;
}

void particleSystem::update(UpdateData& data) {
}