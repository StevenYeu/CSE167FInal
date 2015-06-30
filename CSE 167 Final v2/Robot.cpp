#include "Robot.h"


Robot::Robot()
{
    ident.identity();
    Matrix4 tTrans;
    Matrix4 tScale;
    Matrix4 hTrans;
    Matrix4 hScale;
    Matrix4 rightAT;
    Matrix4 rightAT2;
    Matrix4 rightAR;
    Matrix4 rightAS;
    Matrix4 leftAT;
    Matrix4 leftAT2;
    Matrix4 leftAR;
    Matrix4 leftAS;
    Matrix4 rightLT;
    Matrix4 rightLT2;
    Matrix4 rightLR;
    Matrix4 rightLS;
    Matrix4 leftLT;
    Matrix4 leftLT2;
    Matrix4 leftLR;
    Matrix4 leftLS;
    
    head = new Cyclinder(2.5, 1.0, 5);
    leftArm = new Cube(1);
    rightArm = new Cube(1);
    torso = new Cube(2.5);
    leftLeg = new Cube(1);
    rightLeg = new Cube(1);
    
    
    allTrans = new MatrixTransform(ident);
    allRot = new MatrixTransform(ident);
    allScale = new MatrixTransform(ident);
    
    Matrix4 allT;
    allT.makeTranslate(-12, -10, 10);
    allTrans->setMatrix(allT);
    
    // torso
    tTrans.makeTranslate(0,.3, 0);
    tScale.makeScale(.8, .8, .8);
    bodyTrans = new MatrixTransform(tTrans);
    bodyScale = new MatrixTransform(tScale);
    allTrans->addChild(allScale);
    allScale->addChild(allRot);
    allRot->addChild(bodyTrans);
    bodyTrans->addChild(bodyScale);
    bodyScale->addChild(torso);
    
    // head transfroms
    hTrans.makeTranslate(0, -.2, 0);
    hScale.makeScale(.6, .6, .6);
    headTrans = new MatrixTransform(hTrans);
    headScale = new MatrixTransform(hScale);
    allRot->addChild(headTrans);
    headTrans->addChild(headScale);
    headScale->addChild(head);
    
    // right arm
    rightAT.makeTranslate(0, 1.5, 0);
    rightAR.makeRotateX(angle);
    rightAT2.makeTranslate(1.3, 1.2, 0);
    rightAS.makeScale(.5, 1.5, 1);
    rightArmTrans = new MatrixTransform(rightAT);
    rightArmRot = new MatrixTransform(rightAR);
    rightArmTrans2 = new MatrixTransform(rightAT2);
    rightArmScale = new MatrixTransform(rightAS);
    allRot->addChild(rightArmTrans);
    rightArmTrans->addChild(rightArmRot);
    rightArmRot->addChild(rightArmTrans2);
    rightArmTrans2->addChild(rightArmScale);
    rightArmScale->addChild(rightArm);
    
    
    // left arm
    leftAT.makeTranslate(0, 1.5, 0);
    leftAR.makeRotateX(angle);
    leftAT2.makeTranslate(-1.3, 1.2, 0);
    leftAS.makeScale(.5, 1.5, 1);
    leftArmTrans = new MatrixTransform(leftAT);
    leftArmRot = new MatrixTransform(leftAR);
    leftArmTrans2 = new MatrixTransform(leftAT2);
    leftArmScale = new MatrixTransform(leftAS);
    allRot->addChild(leftArmTrans);
    leftArmTrans->addChild(leftArmRot);
    leftArmRot->addChild(leftArmTrans2);
    leftArmTrans2->addChild(leftArmScale);
    leftArmScale->addChild(leftArm);
    
    // right leg
    
    rightLT.makeTranslate(0.1, 0.3, 0);
    rightLR.makeRotateX(angle);
    rightLT2.makeTranslate(.4, -2.0, 0);
    rightLS.makeScale(.6, 2, 1);
    rightLegTrans = new MatrixTransform(rightLT);
    rightLegRot = new MatrixTransform(rightLR);
    rightLegTrans2 = new MatrixTransform(rightLT2);
    rightLegScale = new MatrixTransform(rightLS);
    allRot->addChild(rightLegTrans);
    rightLegTrans->addChild(rightLegRot);
    rightLegRot->addChild(rightLegTrans2);
    rightLegTrans2->addChild(rightLegScale);
    rightLegScale->addChild(rightLeg);
    
    // left leg
    leftLT.makeTranslate(-0.8, 0.3, 0);
    leftLR.makeRotateX(angle);
    leftLT2.makeTranslate(.4, -2.0, 0);
    leftLS.makeScale(.6, 2.0, 1);
    leftLegTrans = new MatrixTransform(leftLT);
    leftLegRot = new MatrixTransform(leftLR);
    leftLegTrans2 = new MatrixTransform(leftLT2);
    leftLegScale = new MatrixTransform(leftLS);
    allRot->addChild(leftLegTrans);
    leftLegTrans->addChild(leftLegRot);
    leftLegRot->addChild(leftLegTrans2);
    leftLegTrans2->addChild(leftLegScale);
    leftLegScale->addChild(leftLeg);
}


Robot::~Robot()
{
}

void Robot::init() {


}

void Robot::load() {
	// init geodes
	
	head->load();

	

}
MatrixTransform* Robot::getRoot() {
	return allTrans;
}

void Robot::update(float d){
	if (dir){
		angle += 2;
		if (angle > d) dir = !dir;
	}
	else{
		angle -= 2;
		if (angle < -d) dir = !dir;
	}
}

void Robot::move() {
	Matrix4 rA, rL, lA, lL;
	rA.makeRotateX(angle - 180);
	lA.makeRotateX(-(angle - 180));
	rL.makeRotateX(-angle);
	lL.makeRotateX(angle);
	rightArmRot->setMatrix(rA);
	leftArmRot->setMatrix(lA);
	rightLegRot->setMatrix(rL);
	leftLegRot->setMatrix(lL);


}