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

class Limb {
private:
	int limbIndex;
	int numberOfLinks;
	Link* links;
	Transformation fiducialtoLimbRoot;
	IKSolver ik;

public:
	Limb();
};
#endif /* LIBRARIES_KINEMATICCHAINSARDUINO_LIMB_H_ */

