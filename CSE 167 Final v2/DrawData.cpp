#include "DrawData.h"


DrawData::DrawData(void)
{
    //
}

DrawData::~DrawData(void)
{
    //
}

void DrawData::setMatrix(Matrix4 c) {
	m = &c;
}

Matrix4 DrawData::getMatrix() {
	return *m;
}
//
//Light DrawData::getLight() {
//    return *light;
//}