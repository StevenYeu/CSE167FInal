#ifndef _GROUP_H_
#define _GROUP_H_

#include "Node.h"
#include <list>
class Group : public Node{
public:
	Group();
	~Group();
	virtual void draw(DrawData&);
	virtual void update(UpdateData&);
	void addChild(Node *);
	void removeChild(Node *);
	std::list<Node*> children;
	void addGC(Node*);

protected:
};

#endif