#include "Vector3.h"
#include <math.h>
#include <iostream>
#include <cstring>
#include "Vector4.h"

Vector3::Vector3()
{
    std::memset(m, 0, sizeof(m));
}

Vector3::Vector3(float m0, float m1, float m2)
{
    m[0] = m0;
    m[1] = m1;
    m[2] = m2;
}

Vector3::~Vector3()
{
    //
}

float* Vector3::ptr()
{
    return &m[0];
}

void Vector3::set(float x, float y, float z)
{
    m[0] = x;
    m[1] = y;
    m[2] = z;
}

void Vector3::set(int index, float value)
{
    m[index] = value;
}

float& Vector3::operator [] (int loc)
{
    return m[loc];
}

Vector3 Vector3::add(Vector3 a)
{
    Vector3 b;
    
	float x = m[0] + a[0];
	float y = m[1] + a[1];
	float z = m[2] + a[2];
	b.set(x, y, z);
    return b;
}

Vector3 Vector3::operator + (Vector3 a)
{
    return add(a);
}

Vector3 Vector3::subtract(Vector3 a)
{
    Vector3 b;
    
	float x = m[0] - a[0];
	float y = m[1] - a[1];
	float z = m[2] - a[2];
	b.set(x, y, z);
    
    return b;
}

Vector3 Vector3::operator - (Vector3 a)
{
    return subtract(a);
}

Vector3 Vector3::negate(void)
{
    Vector3 b;
    
	float x = m[0] * -1;
	float y = m[1] * -1;
	float z = m[2] * -1;
	b.set(x, y, z);
    
    return b;
}

Vector3 Vector3::scale(float s)
{
    Vector3 b;
    
	float x = m[0] * s;
	float y = m[1] * s;
	float z = m[2] * s;
	b.set(x, y, z);
    
    return b;
}

Vector3 Vector3::multiply(float a)
{
    Vector3 b;
    
	float x = m[0] * a;
	float y = m[1] * a;
	float z = m[2] * a;
	b.set(x, y, z);
    
    return b;
}

Vector3 Vector3::operator * (float a)
{
    return multiply(a);
}

Vector3 Vector3::multiply(Vector3 a)
{
    Vector3 b;
    
    //Coomponent-wise multiplication

	float x = m[0] * a[0];
	float y = m[1] * a[1];
	float z = m[2] * a[2];
	b.set(x, y, z);
    
    return b;
}

Vector3 Vector3::operator * (Vector3 a)
{
    return multiply(a);
}


float Vector3::dot(Vector3 a)
{
	float dot_product = m[0] * a[0] + m[1] * a[1] + m[2] * a[2];
    
    return dot_product;
}

Vector3 Vector3::cross(Vector3 a)
{
    Vector3 b;
    
	float x = m[1] * a[2] - m[2] * a[1];
	float y = m[2] * a[0] - m[0] * a[2];
	float z = m[0] * a[1] - m[1] * a[0];
	b.set(x, y, z);
    return b;
}

float Vector3::angle(Vector3 a)
{
	float dot_product = dot(a);
	float mag = magnitude() * a.magnitude();
	float rads = acos(dot_product / mag);
	
    return rads;
}

float Vector3::magnitude(void)
{
	float mag = m[0] * m[0] + m[1] * m[1] + m[2] * m[2];
    
    return sqrt(mag);
}

Vector3 Vector3::normalize(void)
{
    Vector3 b;
    
	float mag = magnitude();

	if (mag == 0) {
		return b;
	}
	else {
		float x = m[0] / mag;
		float y = m[1] / mag;
		float z = m[2] / mag;
		b.set(x, y, z);
	}
    
    return b;
}

Vector4 Vector3::toVector4(float w)
{
    Vector4 b(m[0], m[1], m[2], w);
    return b;
}

void Vector3::print(void)
{
    std::cout << "<x:" << m[0] <<  ", y:" << m[1] << ", z:" << m[2] << ">" << std::endl;
}
