#include "Drawable.h"
#include "Window.h"

Drawable::Drawable()
{
    this->toWorld.identity();
}

Drawable::~Drawable()
{
    //
}

void Drawable::draw(DrawData& data)
{
    std::cout << "Warning: draw() is not implemented" << std::endl;
}

void Drawable::update(UpdateData& data)
{
    std::cout << "Warning: update() is not implemented" << std::endl;
}

void Drawable::scale(float s) {
	Matrix4 scaler;
	scaler.makeScale(s, s, s);
	toWorld = toWorld * scaler;
}


void Drawable::translateX(float x) {
	Matrix4 translate;

	translate.makeTranslate(x, 0, 0);

	toWorld = translate * toWorld;
}

void Drawable::translateY(float y) {
	Matrix4 translate;

	translate.makeTranslate(0, y, 0);

	toWorld = translate * toWorld;
}

void Drawable::translateZ(float z) {
	Matrix4 translate;

	translate.makeTranslate(0, 0, z);

	toWorld = translate * toWorld;
}

void Drawable::reset() {
	Matrix4 identity;

	identity.identity();

	toWorld = identity;
}

void Drawable::orbit(float angle) {
	Matrix4 orb;
	float pi = 3.14159265358979323846;
	float rads = angle * (pi / 180.0);
	orb.makeRotateZ(rads);
	toWorld = orb * toWorld;
}

void Drawable::spin(float angle) {
	Matrix4 spin;
	float pi = 3.14159265358979323846;
	float rads = angle * (pi / 180.0);
	spin.makeRotateY(rads);
	toWorld = toWorld * spin;
}



Vector3 Drawable::getLoc() {
	Vector3 r;
	float x = toWorld.get(3, 0);
	float y = toWorld.get(3, 1);
	float z = toWorld.get(3, 2);
	r.set(x, y, z);
	return r;
}