/*
 * Limb.cpp
 *
 *  Created on: Apr 27, 2021
 *      Author: aksha
 */

#include <Limb.h>

Limb::Limb(int index, const char* Name, Matrix<4,4> limbRoot, hardwareManager* hwptr){

	limbIndex = index;
	fiducialtoLimbRoot = limbRoot;
	limbName = Name;
	hwLocal = hwptr;
}

/*
* Adds a link pointer to the link pointer array
* @param linkPTR, pointer to the link to add
* @param index, the index that the pointer is at
*/
void Limb::addLinkPtr(Link* linkPTR){
	links[numberOfLinks++] = linkPTR;
	Serial.println(String(numberOfLinks));
}

Matrix<4,4> &Limb::FK(Matrix<4,4> &GlobalTransform,float* currAngles){
	GlobalTransform*=fiducialtoLimbRoot;
	for(int i = 0; i < numberOfLinks; i++){
		GlobalTransform = links[i]->computeStep(GlobalTransform, currAngles[i]);
	}
	return GlobalTransform;
}


IKResult Limb::IK(Matrix<4,4> &Target, float* Result){
	if(ik == NULL){
		ik =new IKSolver();}
	Target =  fiducialtoLimbRoot.Inverse()*Target;
	IKResult IKof = ik->IK(Target,Result,links,numberOfLinks);
	if(IKof == IKSuccess){
		for(int i = 0; i < numberOfLinks; i++){
			if((Result[i] >links[i]->MaxLink)||(Result[i] < links[i]->MinLink))return JointLimits;
		}
	}
	return IKof;
}
