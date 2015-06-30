#ifndef CSE167_Texture_h
#define CSE167_Texture_h

#include <iostream>
#include <string>

class Texture
{
    
protected:
    
    const char* filename;
    
    static unsigned char* loadPPM(const char*, int&, int&);
    
public:
    
    unsigned int id;
    
    static Texture* emptyTexture;
    
    int height;
    int width;
    
    Texture(void);
    Texture(const char* filename);
	Texture(const char* filename, int i);
    virtual ~Texture(void);
    
    void bind(void);
    void unbind(void);
    
};

#endif
