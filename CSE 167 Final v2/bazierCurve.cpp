#include "bazierCurve.h"

#include <GLUT/GLUT.h>

#include <cmath>


bazierCurve::bazierCurve()
{
}

bazierCurve::bazierCurve(vector<Vector3> cparray){
    this->cparray = cparray;
    this->order = cparray.size() - 1;
    this->togglecurve = false;
}


bazierCurve::~bazierCurve()
{
}

void bazierCurve::update(UpdateData& data){
    //
}

Vector3 bazierCurve::move(float t){
    Vector3 cat;
    cat = deCast(cparray, t);
    return cat;
    
}


void bazierCurve::render(){
    if (togglecurve == true){
        glBegin(GL_POINTS);
        glPointSize(100);
        float t = 0.0;
        
        Vector3 cat;
        for (t = 0; t < 1.0; t += 0.001){
            cat = deCast(cparray, t);
            glColor3f(0,0,1);
            glVertex3f(cat[0], cat[1], cat[2]);
            
            
        }
        glEnd();
    }
}

Vector3 bazierCurve::deCast(vector<Vector3> ptr, float t){
    Vector3 sol = Vector3(0,0,0);
    for (int i = 0; i <= order; i++){
        sol = sol + (ptr[i] *  (choose(order,i) * pow(t, i) * pow((1 - t), (order - i))));
        
    }
    return sol;
}

float bazierCurve::factorial(float input){
    if (input <= 1){
        return 1;
    }
    
    return (input * factorial(input-1));
    
}

float bazierCurve::choose(float n, float p){
    
    float temp = factorial(p) * factorial(n - p);
    return (factorial(n)/temp);
    
}

void bazierCurve::toggleCurve(){
    togglecurve = !togglecurve;
}
