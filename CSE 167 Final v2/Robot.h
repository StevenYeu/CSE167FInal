#ifndef _ROBOT_H_
#define _ROBOT_H_
#include "MatrixTransform.h"
#include "Cube.h"
#include "Cyclinder.h"
class Robot
{
public:
	Robot();
	~Robot();
	void load();
	void init();
	void update(float d);
	void move();
	MatrixTransform* getRoot();
	double angle = 0;
	Vector3 vecy;
	bool dir = false;
protected:

	//all
	MatrixTransform* allTrans;
	MatrixTransform* allScale;
	MatrixTransform* allRot;

	// torso
	MatrixTransform* bodyTrans;
	MatrixTransform* bodyScale;

	// head
	MatrixTransform* headScale;
	MatrixTransform* headTrans;


	// left arm
	MatrixTransform* leftArmTrans;
	MatrixTransform* leftArmTrans2;
	MatrixTransform* leftArmScale;
	MatrixTransform* leftArmRot;

	// right arm
	MatrixTransform* rightArmTrans;
	MatrixTransform* rightArmTrans2;
	MatrixTransform* rightArmScale;
	MatrixTransform* rightArmRot;

	// left leg
	MatrixTransform* leftLegTrans;
	MatrixTransform* leftLegTrans2;
	MatrixTransform* leftLegScale;
	MatrixTransform* leftLegRot;

	//right leg
	MatrixTransform* rightLegTrans;
	MatrixTransform* rightLegTrans2;
	MatrixTransform* rightLegScale;
	MatrixTransform* rightLegRot;

	Matrix4 ident;
	Matrix4 trans;
	Matrix4 rot;
    
    Cyclinder* head;
    Cube* leftArm ;
    Cube* rightArm ;
    Cube* torso ;
    Cube* leftLeg;
    Cube* rightLeg;

	

};
#endif

