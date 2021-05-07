/*
 * Limb.h
 *
 *  Created on: Apr 27, 2021
 *      Author: aksha
 */

#ifndef LIBRARIES_KINEMATICCHAINSARDUINO_LIMB_H_
#define LIBRARIES_KINEMATICCHAINSARDUINO_LIMB_H_

#include "link.h"
#include "IKSolver.h"
#include <Geometry.h>

#define maxLinks 20

class Limb {
private:
	int limbIndex;
	int numberOfLinks = 0;
	const char* limbName;
	Link* links[maxLinks];
	Transformation* fiducialtoLimbRoot;
	IKSolver ik;
	hardwareManager* hwLocal;

public:
	Limb(int index, const char* Name, Transformation* limbRoot, hardwareManager* hwptr);
	void addLinkPtr(Link* linkPTR);
	void FK(Transformation* GlobalTransform);

};
#endif /* LIBRARIES_KINEMATICCHAINSARDUINO_LIMB_H_ */

