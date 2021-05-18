/*
 * IKSolver.cpp
 *
 *  Created on: Apr 27, 2021
 *      Author: aksha
 */

#include <IKSolver.h>

IKSolver::IKSolver() {
	// TODO Auto-generated constructor stub

}

IKSolver::~IKSolver() {
	// TODO Auto-generated destructor stub
}


bool IKSolver::IK(Matrix<4,4> &Target, float* Result, Link** links, int numberOfLinks){
	PrintMatrix(Target, "_ Limb 0 IK");
	float x = Target(0,3);
	float y = Target(1,3);
	//Serial.println(String(x)+":Xval  "+String(y)+":Yval  ");
	float Link0Angle;

	//Projection on Limb XY
	Link0Angle = atan2(y,x)+links[0]->DH_Theta;
	//Serial.println("Theta0: "+String(Link0Angle));
	Result[0] = Link0Angle*180/3.14159;
	Matrix<4,4> T1 = Identity<4,4>();
	T1 = links[0]->computeStep(T1, Result[0]);
	PrintMatrix(T1, "T1");
	Matrix<4,4> T2 = T1.Inverse()*Target;
	PrintMatrix(T2, "T2");

	return true;
}
