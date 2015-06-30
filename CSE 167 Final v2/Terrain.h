//
//  Terrain.h
//  CSE 167 Project 6
//
//  Created by Steven Yeu on 5/11/15.
//  Copyright (c) 2015 Steven Yeu. All rights reserved.
//

#ifndef __CSE_167_Project_6__Terrain__
#define __CSE_167_Project_6__Terrain__

#include <stdio.h>
#include "Texture.h"
#include "Drawable.h"
#include "Geode.h"
#include <vector>
#include "Vector3.h"
#include "Vector4.h"
#include "Shader.h"
#include <GLUT/glut.h>


class Terrain : public Geode
{
protected:
    Vector3 vertexCoords[1024][1024];
    int max_height = 1024;
    int max_width = 1024;
    unsigned char elevation_data[1024][1024];
    unsigned char* file_data;
    Vector3* normals;
    float waterLevel = 0;
    Shader* water;
    float exFactor;
    bool shader;
    float p;
    
    
public:
    Terrain();
    ~Terrain();
    void render();
    void update(UpdateData&);
    void loadData();
    void calculateNormals();
    unsigned char* loadPPM(const char* filename, int& width, int& height);
    void setWaterLevel(float);
    float getWaterLevel();
    void loadShader();
    void setExFactor(float);
    float returnExFactor();
    void toggleShader();
    float peak();
    void ex();
    
};


#endif /* defined(__CSE_167_Project_6__Terrain__) */
