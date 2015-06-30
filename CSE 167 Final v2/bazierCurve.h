#ifndef CSE167_BAZIERCURVE_h
#define CSE167_BAZIERCURVE_h

#include "Vector3.h"
#include "Vector4.h"
#include "Matrix4.h"
#include "Geode.h"
#include <vector>

using namespace std;

class bazierCurve : public Geode
{
public:
    
    vector<Vector3> cparray;
    int order;
    bool togglecurve;
    
    bazierCurve();
    bazierCurve(vector<Vector3>);
    virtual ~bazierCurve();
    
    void render();
    void update(UpdateData&);
    
    void toggleCurve();
    Vector3 deCast(vector<Vector3>, float t);
    float factorial(float);
    float choose(float, float);
    Vector3 move(float);
    float result = 1.0;
    
};

#endif

