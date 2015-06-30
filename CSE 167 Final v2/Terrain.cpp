//
//  Terrain.cpp
//  CSE 167 Project 6
//
//  Created by Steven Yeu on 5/11/15.
//  Copyright (c) 2015 Steven Yeu. All rights reserved.
//

#include "Terrain.h"
#include "Window.h"

Terrain::Terrain() {
    loadData();
    calculateNormals();
    shader = false;
    exFactor = 1;
    p = peak();
    
}

Terrain::~Terrain() {
    
}


void Terrain::loadData() {

    file_data = loadPPM("SanDiegoTerrain.ppm", max_width, max_height);
    for (int xcoor = 0; xcoor < max_width;xcoor++) {
        for (int ycoor = 0; ycoor < max_height; ycoor++) {
            int offset = ycoor*3*max_width + xcoor*3;
            float val = file_data[offset];
            elevation_data[xcoor][ycoor] = val;
            vertexCoords[xcoor][ycoor].set(xcoor,elevation_data[xcoor][ycoor],ycoor);
        }
    }
}

void Terrain::calculateNormals() {
    normals = new Vector3[1024*1024];
    
    for (int xcoor = 0; xcoor < max_width-1;xcoor++) {
        for (int ycoor = 0; ycoor < max_height-1; ycoor++) {
            int offset = ycoor*max_width + xcoor;
            Vector3 v1;
            Vector3 v2;
            Vector3 v3;
            Vector3 v4;
            Vector3 n;
            Vector3 n2;
            v1 = vertexCoords[xcoor][ycoor];
            v2 = vertexCoords[xcoor+1][ycoor];
            v3 = vertexCoords[xcoor][ycoor+1];
            v4 = vertexCoords[xcoor+1][ycoor+1];
            if(xcoor % 2 == 0) {
                n = (v3-v2).cross((v1-v2));
                n = n.normalize();
                normals[offset] = n*-1;
                n2 = (v3-v2).cross((v1-v2));
                n2 = n2.normalize();
                offset = (ycoor+1)*max_width + xcoor;
                normals[offset] = n2*-1;

            }
            else if (xcoor % 2 ==1) {
                n = (v2-v3).cross((v4-v3));
                n = n.normalize();
                normals[offset] = n*-1;
                n2 = (v3-v2).cross((v1-v2));
                n2 = n2.normalize();
                offset = (ycoor+1)*max_width + xcoor;
                normals[offset] = n2*-1;
            }
        }
    }
}


unsigned char* Terrain::loadPPM(const char* filename, int& width, int& height)
{
    const int BUFSIZE = 128;
    FILE* fp;
    size_t read;
    unsigned char* rawData;
    char buf[3][BUFSIZE];
    char* retval_fgets;
    size_t retval_sscanf;
    
    //Open the texture file
    if((fp=fopen(filename, "rb")) == NULL)
    {
        std::cerr << "error reading ppm file, could not locate " << filename << std::endl;
        width = 0;
        height = 0;
        return NULL;
    }
    
    // Read magic number:
    retval_fgets = fgets(buf[0], BUFSIZE, fp);
    
    // Read width and height:
    do
    {
        retval_fgets=fgets(buf[0], BUFSIZE, fp);
    } while (buf[0][0] == '#');
    
    retval_sscanf=sscanf(buf[0], "%s %s", buf[1], buf[2]);
    width  = atoi(buf[1]);
    height = atoi(buf[2]);
    
    // Read maxval:
    do
    {
        retval_fgets=fgets(buf[0], BUFSIZE, fp);
    } while (buf[0][0] == '#');
    
    // Read image data:
    rawData = new unsigned char[width * height * 3];
    read = fread(rawData, width * height * 3, 1, fp);
    fclose(fp);
    if (read != 1)
    {
        std::cerr << "error parsing ppm file, incomplete data" << std::endl;
        delete[] rawData;
        width = 0;
        height = 0;
        return NULL;
    }
    
    return rawData;
}

void Terrain::render() {
    materials.apply();
    
    water->bind();
    setWaterLevel(Window::waterL);
    p = peak();
    GLuint uniformIDy = glGetUniformLocationARB(water->getPid(), "yellow");
    glUniform1f(uniformIDy, .25*(p-Window::waterL)+Window::waterL);
    
    GLuint uniformIDgreen = glGetUniformLocationARB(water->getPid(), "green");
    glUniform1f(uniformIDgreen, .5*(p-Window::waterL)+Window::waterL);
    
    GLuint uniformIDgrey = glGetUniformLocationARB(water->getPid(), "grey");
    glUniform1f(uniformIDgrey, .75*(p-Window::waterL)+Window::waterL);
    
    GLuint uniformIDwhite = glGetUniformLocationARB(water->getPid(), "white");
    glUniform1f(uniformIDwhite,p);
    
    
    for (int rows = 0; rows < 1023; rows++) {
        glBegin(GL_TRIANGLE_STRIP);
        for(int cols = 0; cols < 1023; cols++) {
            
            glNormal3f(normals[cols*max_width+rows][0], exFactor*normals[cols*max_width+rows][1], normals[cols*max_width+rows][2]);
            glVertex3f(vertexCoords[rows][cols][0], exFactor*vertexCoords[rows][cols][1], vertexCoords[rows][cols][2]);
            
            glNormal3f(normals[cols*max_width+rows+1][0], exFactor*normals[cols*max_width+rows+1][1], normals[cols*max_width+rows+1][2]);
            glVertex3f(vertexCoords[rows+1][cols][0], exFactor*vertexCoords[rows+1][cols][1], vertexCoords[rows+1][cols][2]);
        }
        glEnd();

    }
    water->unbind();
    

    

}

void Terrain::update(UpdateData& data) {
    
}


float Terrain::getWaterLevel() {
    return waterLevel;
}

void Terrain::setWaterLevel(float w) {
    GLuint uniformID = glGetUniformLocationARB(water->getPid(), "waterLevel");
    glUniform1f(uniformID, w);

}

void Terrain::loadShader() {
    water = new Shader("/Users/stevenyeu/Xcode Projects/CSE 167 Project 6/water.vs",
                   "/Users/stevenyeu/Xcode Projects/CSE 167 Project 6/terrain.fs",true);
    water->printLog();
}

void Terrain::setExFactor(float e){
    exFactor = e;
}

float Terrain::returnExFactor() {
    return exFactor;
}

void Terrain::toggleShader() {
    shader = !shader;
}


float Terrain::peak() {
    float max;
    max = vertexCoords[0][0][1];
    
    for (int x= 0; x < 1024; x++) {
        for (int y = 0; y <1024; y++) {
            if (vertexCoords[x][y][1]*exFactor > max) {
                max = vertexCoords[x][y][1] * exFactor;
            }
        }
    }
    return max;

}
