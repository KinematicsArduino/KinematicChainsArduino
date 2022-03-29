/*
 * IKSolver.h
 *
 *  Created on: Apr 27, 2021
 *      Author: aksha
 */

#ifndef LIBRARIES_KINEMATICCHAINSARDUINO_IKSOLVER_H_
#define LIBRARIES_KINEMATICCHAINSARDUINO_IKSOLVER_H_

#include "Link.h"
#include <Geometry.h>

class IKSolver {
public:
	IKSolver();
	virtual ~IKSolver();

	IKResult IK(Matrix<4,4> &Target, float* Result, Link** links, int numberOfLinks);

};

#endif /* LIBRARIES_KINEMATICCHAINSARDUINO_IKSOLVER_H_ */
