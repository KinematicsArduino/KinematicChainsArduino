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
	//PrintMatrix(Target, "_ Limb 0 IK");
	float x = Target(0,3);
	float y = Target(1,3);
	Serial.println(String(x)+":Xval  "+String(y)+":Yval  ");
	float Link0Angle;

	//Projection on Limb XY
	if((abs(x)<0.1) && (abs(y)<0.1)){return false;}
	if(x<0){return false;}
	Link0Angle = atan2(y,x)+links[0]->DH_Theta;

	Serial.println("Theta0: "+String(Link0Angle));

	//Find link one angle in radians
	Result[0] = Link0Angle*180/3.14159;
	Matrix<4,4> T1 = Identity<4,4>();

	//Find the transfomation from link0 zFrame to link1 zFrame
	T1 = links[0]->computeStep(T1, Result[0]);
	//PrintMatrix(T1, "T1");
	Matrix<4,4> T2 = T1.Inverse()*Target;
	//PrintMatrix(T2, "T2");
	x = T2(0,3);
	y = T2(1,3);
	//Serial.println(String(x)+":Xval  "+String(y)+":Yval  ");

	if(((abs(x)<0.1) && (abs(y)<0.1))){return false;}
	//Cannot access quadrants 2&3, edit to do so
	float TriangleAngle = atan2(y,x);
	//Serial.println("TriangleAngle: "+String(TriangleAngle));
	Matrix<4,4> T3 = Identity<4,4>();
	T3=RotateZ(T3,-1*TriangleAngle);

	//PrintMatrix(T3, "T3");
	Matrix<4,4> T4 =T3*T2;

	//PrintMatrix(T4, "T4");

	float C = T4(0,3);
	float A = links[1]->DH_R;
	float B = links[2]->DH_R;

	if((A+B)< C){ return false;}

	float Link1Theta = acos((pow(B,2)-pow(A,2)-pow(C,2))/(-(2*A*C)));

	//Serial.println("Link1Theta "+String(Link1Theta));
	Link1Theta= Link1Theta+links[1]->DH_Theta-TriangleAngle;

	Link1Theta*=-1;
	//Serial.println("Link1Theta "+String(Link1Theta));
	Result[1] = 180/3.14159*Link1Theta;

	float Link2Theta = acos((pow(C,2)-pow(A,2)-pow(B,2))/(-(2*A*B)));

	//Serial.println("Link2Theta "+String(Link2Theta));
	Link2Theta-= links[2]->DH_Theta;

	//Serial.println("Link2Theta "+String(Link2Theta));

	Link2Theta*=-1;
	Result[2] = 180/3.14159*Link2Theta;

	return true;
}
