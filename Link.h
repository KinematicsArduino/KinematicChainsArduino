/*
 * Link.h
 *
 *  Created on: Apr 27, 2021
 *      Author: aksha
 */

#ifndef LIBRARIES_KINEMATICCHAINSARDUINO_LINK_H_
#define LIBRARIES_KINEMATICCHAINSARDUINO_LINK_H_
#include "hardwareManager.h"
#include <Geometry.h>

class Link {
private:
	int linkIndex;
	float DH_Alpha;
	float DH_D;
	float DH_R;
	float DH_Theta;

	float ScaleActuator;
	float Offset;

	hardwareManager* hwLocal;
	int hardwarePin;
public:
	Link(int index, float DH_alpha, float DH_d, float DH_R, float DH_Theta, int ID, hardwareManager* hwptr, float ScaleActuator, float Offset);
	/*
	 * getAngle returns angle of link in degrees
	 */
	float getAngle();
	void computeStep(Matrix <4,4> &pose);
};

#endif /* LIBRARIES_KINEMATICCHAINSARDUINO_LINK_H_ */
