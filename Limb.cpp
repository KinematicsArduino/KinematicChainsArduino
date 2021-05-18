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

Matrix<4,4> &Limb::FK(Matrix<4,4> &GlobalTransform){
	GlobalTransform*=fiducialtoLimbRoot;
	for(int i = 0; i < numberOfLinks; i++){
		GlobalTransform = links[i]->computeStep(GlobalTransform);
	}
	return GlobalTransform;
}
