#ifndef CSE167_Light_h
#define CSE167_Light_h

#include "Matrix4.h"
#include "Vector4.h"
#include "Vector3.h"
#include "Color.h"
#include "Geode.h"
#include <vector>

class Light : public Geode
{
    
protected:
    
    int bindID = -1;
    bool isSpot = false;
    float exponent;
    float cutOff;

public:
    
    Vector4 position;
    Vector3 spotDirection;
    
    
    Color ambientColor;
    Color diffuseColor;
    Color specularColor;
    
    float constantAttenuation;
    float linearAttenuation;
    float quadraticAttenuation;
    Matrix4 toWolrd;
    
public:
    
    Light();
    virtual ~Light(void);
    
    void bind(int);
    void unbind(void);
    void move(float, float, float);
    void setExponent(float);
    void setCutOff(float);
    void setSpotLight(Vector3);
    void setAttenuation(float, float, float);
    void setAmbient(Color a);
    void setDiffuse(Color d);
    void setSpecular(Color s);
    void orbitTrack(Vector3, float);
    void orbitSpotTrack(Vector3, float);
    Vector4 getPosition();
    void setPosition(float,float,float,float);
    void setToWorld();
    float getExp();
    float getCut();
    void render();
    void update(UpdateData&);
    
    
};

#endif
