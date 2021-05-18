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
	Matrix<4,4> fiducialtoLimbRoot;
	IKSolver ik;
	hardwareManager* hwLocal;

public:
	Limb(int index, const char* Name, Matrix<4,4> limbRoot, hardwareManager* hwptr);
	void addLinkPtr(Link* linkPTR);
	Matrix<4,4> &FK(Matrix<4,4> &GlobalTransform);

};
#endif /* LIBRARIES_KINEMATICCHAINSARDUINO_LIMB_H_ */

