#include "Group.h"
#include <GLUT/glut.h>
#include "Globals.h"

using namespace std;

Group::Group() {

}

Group::~Group(){
	/*for (list<Node*>::iterator it = children.begin(); it != children.end(); ++it)
		delete *it;*/
}

void Group::addChild(Node * n){
	children.push_back(n);
}

void Group::removeChild(Node *n){
	children.remove(n);
}

void Group::draw(DrawData& d){
	for (list<Node*>::iterator it = children.begin(); it != children.end(); ++it) {
		(*it)->draw(d);
	}
		
}

void Group::update(UpdateData& d) {
	
}

void Group::addGC(Node* n) {
	
}
