/*
 * Link.cpp
 *
 *  Created on: Apr 27, 2021
 *      Author: aksha
 */

#include <Link.h>

Link::Link(int index, float DH_alpha, float DH_d, float DH_r, float DH_theta, int ID, hardwareManager* hwptr, float scale, float offset){
	linkIndex = index;
	DH_Alpha = DH_alpha;
	DH_D = DH_d;
	DH_R = DH_r;
	DH_Theta = DH_theta;

	Offset = offset;
	ScaleActuator = scale;
	hwLocal = hwptr;
	hardwarePin = ID;
}

float Link::getAngle(){
	return ScaleActuator*(hwLocal->getCurrentValue(hardwarePin)-Offset);
}


void Link::computeStep(Transformation* pose){
	 pose->RotateX(DH_Alpha);
	 pose->Translate(DH_R,0,0);
	 pose->Translate(0,0,DH_D);
	 pose->RotateZ(DH_Theta);
}

