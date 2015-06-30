#ifndef CSE167_OBJObject_h
#define CSE167_OBJObject_h

#include <iostream>
#include <vector>
#include <string>
#include <list>
#include "Vector3.h"
#include "Drawable.h"

struct Face
{
	int vs[3];
	int ns[3];
	int ts[3];
};

class OBJObject : public Drawable
{

protected:

	//Storage vectors
	std::vector<Vector3*>* vertices;
	std::vector<Vector3*>* normals;
	std::vector<Vector3*>* texcoords;
	std::vector<Vector3*>* colors;
	//std::vector<Face>* faces;
	std::list<Face>* faces;


	//Helper functions
	std::vector<std::string>& split(const std::string&, char, std::vector<std::string>&);
	std::vector<std::string> split(const std::string&, char);

	//Parse
	void parse(std::string&);

	bool loaded = false;

public:
	OBJObject(std::string);
	virtual ~OBJObject(void);
	virtual void draw(DrawData&);
	virtual void update(UpdateData&);

};

#endif