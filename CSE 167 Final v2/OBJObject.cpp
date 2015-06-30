#include "OBJObject.h"

#ifdef _WIN32
#include <GL/glut.h>
#else
#include <GLUT/glut.h>
#endif

#include "Window.h"
#include "math.h"
#include <sstream>
#include <fstream>
#include <vector>

#define deleteVector(__vect__) do {\
                                   iter = __vect__->begin();\
                                   end = __vect__->end();\
								                                      while(iter != end) delete (*(iter++));\
                                   delete __vect__;\
							                                  } while(false)

OBJObject::OBJObject(std::string filename) : Drawable()
{
	this->vertices = new std::vector<Vector3*>();
	this->normals = new std::vector<Vector3*>();
	this->texcoords = new std::vector<Vector3*>();
	this->colors = new std::vector<Vector3*>();
	this->faces = new std::list<Face>();


	parse(filename);
}

OBJObject::~OBJObject()
{
	//Delete any dynamically allocated memory/objects here
	std::vector<Vector3*>::iterator iter;
	std::vector<Vector3*>::iterator end;

	deleteVector(vertices);
	deleteVector(normals);
	deleteVector(texcoords);

	delete faces;
}



void OBJObject::draw(DrawData& data)
{
	material.apply();

	glMatrixMode(GL_MODELVIEW);

	glPushMatrix();
	glMultMatrixf(toWorld.ptr());

	glBegin(GL_TRIANGLES);


	//Loop through the faces
	//For each face:
	//  Look up the vertices, normals (if they exists), and texcoords (if they exist)
	//  Draw them as triplets:

	//      glTex(face.ts[0])
	//      glNorm(face.ns[0])
	//      glVert(face.vs[0])

	//      glTex(face.ts[1])
	//      glNorm(face.ns[1])
	//      glVert(face.vs[1])
	//      Etc.
	//

	glColor3f(0.75, 0.75, 0.75);
	for (std::list<Face>::iterator it = faces->begin(), end = faces->end(); it != end; ++it) {
		Vector3* v1;
		Vector3* v2;
		Vector3* v3;
		Vector3* n1;
		Vector3* n2;
		Vector3* n3;
		float x1;
		float x2;
		float x3;
		float y1;
		float y2;
		float y3;
		float z1;
		float z2;
		float z3;

		float nx1;
		float nx2;
		float nx3;
		float ny1;
		float ny2;
		float ny3;
		float nz1;
		float nz2;
		float nz3;
		Face f = (*it);
		v1 = vertices->at((*it).vs[0]);
		v2 = vertices->at((*it).vs[1]);
		v3 = vertices->at((*it).vs[2]);

		n1 = normals->at((*it).ns[0]);
		n2 = normals->at((*it).ns[1]);
		n3 = normals->at((*it).ns[2]);

		x1 = (*v1)[0];
		y1 = (*v1)[1];
		z1 = (*v1)[2];

		x2 = (*v2)[0];
		y2 = (*v2)[1];
		z2 = (*v2)[2];

		x3 = (*v3)[0];
		y3 = (*v3)[1];
		z3 = (*v3)[2];

		nx1 = (*n1)[0];
		ny1 = (*n1)[1];
		nz1 = (*n1)[2];

		nx2 = (*n2)[0];
		ny2 = (*n2)[1];
		nz2 = (*n2)[2];

		nx3 = (*n3)[0];
		ny3 = (*n3)[1];
		nz3 = (*n3)[2];

		glNormal3f(nx1, ny1, nz1);
		glVertex3f(x1, y1, z1);

		glNormal3f(nx2, ny2, nz2);
		glVertex3f(x2, y2, z2);

		glNormal3f(nx3, ny3, nz3);
		glVertex3f(x3, y3, z3);

	}


	glEnd();

	glPopMatrix();
}

void OBJObject::update(UpdateData& data)
{
	//
}

void OBJObject::parse(std::string& filename)
{
	std::ifstream infile(filename);
	std::string line;
	std::vector<std::string> tokens;
	std::string token;

	std::list<double> dubs;

	int lineNum = 0;

	vertices->push_back(new Vector3(0, 0, 0));
	normals->push_back(new Vector3(0, 0, 0));



	std::cout << "Starting parse..." << std::endl;

	//While all your lines are belong to us
	while (std::getline(infile, line))
	{
		//Progress
		if (++lineNum % 10000 == 0)
			std::cout << "At line" << lineNum << std::endl;

		//Split a line into tokens by delimiting it on spaces
		//"Er Mah Gerd" becomes ["Er", "Mah", "Gerd"]
		tokens.clear();
		tokens = split(line, ' ', tokens);

		//If first token is a v then it gots to be a vertex
		if (tokens.size() > 1 && tokens.at(0).compare("v") == 0)
		{
			//Parse the vertex line
			float x = std::stof(tokens.at(1));
			float y = std::stof(tokens.at(2));
			float z = std::stof(tokens.at(3));
			vertices->push_back(new Vector3(x, y, z));

			/*if (tokens.size() > 4) {
				float red = std::stof(tokens.at(4));
				float blue = std::stof(tokens.at(5));
				float green = std::stof(tokens.at(6));
				colors->push_back(new Vector3(red, blue, green));

			}*/
			
		}
		else if (tokens.size() > 1 && tokens.at(0).compare("vn") == 0)
		{
			//Parse the normal line
			float x = std::stof(tokens.at(1));
			float y = std::stof(tokens.at(2));
			float z = std::stof(tokens.at(3));
			Vector3 normal = Vector3(x, y, z);
			normal = normal.normalize();
			normals->push_back(new Vector3(normal[0], normal[1], normal[2]));
		}
		else if (tokens.size() > 1 && tokens.at(0).compare("f") == 0)
		{
			Face obj_face;

			//Parse the face line

			std::vector<std::string> index_0;
			std::vector<std::string> index_1;
			std::vector<std::string> index_2;

			index_0.clear();
			index_1.clear();
			index_2.clear();

			index_0 = split(tokens.at(1), '/', index_0);
			index_1 = split(tokens.at(2), '/', index_1);
			index_2 = split(tokens.at(3), '/', index_2);

			std::vector<std::vector<std::string>> index;
			index.push_back(index_0);
			index.push_back(index_1);
			index.push_back(index_2);

		

			for (int i = 0; i < 3; i++) {
				obj_face.vs[i] = std::stof(index[i].at(0));
				obj_face.ts[i] = std::stof(index[i].at(0));
				obj_face.ns[i] = std::stof(index[i].at(2));
			}

			index.clear();

			faces->push_back(obj_face);
		}
		else if (tokens.size() > 1 && tokens.at(0).compare("how does I are c++?!?!!") == 0)
		{
			//Parse as appropriate
			//There are more line types than just the above listed
			//See the Wavefront Object format specification for details
		}

	}

	std::cout << "Done parsing." << std::endl;
}

//Split functions from the interwebs
//http://stackoverflow.com/questions/236129/split-a-string-in-c
std::vector<std::string>& OBJObject::split(const std::string &s, char delim, std::vector<std::string> &elems)
{
	std::stringstream ss(s);
	std::string item;
	while (std::getline(ss, item, delim))
	{
		elems.push_back(item);
	}
	return elems;
}

std::vector<std::string> OBJObject::split(const std::string &s, char delim)
{
	std::vector<std::string> elems;
	split(s, delim, elems);
	return elems;
}

