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
	int numberOfLinks;
	const char* limbName;
	Link* links[maxLinks];
	Transformation fiducialtoLimbRoot;
	IKSolver ik;

public:
	Limb();
	void addIndex(int index);
	void addName(const char* Name);
	void addSize(int size);
	void addTransformation(Transformation limbRoot);
	//void addTransformation(double limbRoot[16]);
		//possibly have the transformation be passed as an array and converted in function
	void addLinkPtr(Link* linkPTR, int index);

};
#endif /* LIBRARIES_KINEMATICCHAINSARDUINO_LIMB_H_ */

