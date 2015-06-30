#ifndef CSE167_Skybox_h
#define CSE167_Skybox_h

#include "Texture.h"
#include "Geode.h"

class Skybox : public Geode
{
public:
    
    float size;
    Texture left, right, back, top, base, front;
    
    
    Skybox(float);
    virtual ~Skybox();
    
    virtual void render();
    virtual void update(UpdateData&);
    void loadTexture();
};

#endif

