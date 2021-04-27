/*
 * MobileBase.cpp
 *
 *  Created on: Apr 27, 2021
 *      Author: aksha
 */


#include "MobileBase.h"

MobileBase::MobileBase(hardwareManager* hwptr){
	hwLocal = hwptr;

}

void MobileBase::parse(File* file){

}


/*
* Adds Limb to mobile base
* @param limbPtr, a pointer to the new limb
*/
void MobileBase::addLimb(Limb* limbPtr){
	limbs[numberOfLimbs] = limbPtr;
	numberOfLimbs++;
}

