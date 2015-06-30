#ifndef CSE167_House_h
#define CSE167_House_h

#include "Drawable.h"
#include "Vector3.h"


class House : public Drawable
{

public:

	float size;	

	House();
	virtual ~House(void);

	virtual void draw(DrawData&);
	virtual void update(UpdateData&);


};

#endif
