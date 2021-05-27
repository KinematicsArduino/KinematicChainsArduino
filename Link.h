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
void PrintMatrix(Matrix<4, 4> MatrixEx, String name);



Matrix<4, 4>& RotateZ(Matrix<4, 4> &poseT, float theta);

Matrix<4, 4>& RotateX(Matrix<4, 4> &poseT, float alpha);

Matrix<4, 4>& TranslateZ(Matrix<4, 4> &poseT, float D);

Matrix<4, 4>& TranslateX(Matrix<4, 4> &poseT, float R);

enum IKResult{ IKSuccess, JointLimits , ElbowTriangleSingularity, OutsideOfWorkspace, DHConfigError, NumberOfLinksError, Quadrants2and3Unreachable};

void PrintIKResult(IKResult Error);

class Link {

	public:
	int linkIndex;
	float DH_Alpha;
	float DH_D;
	float DH_R;
	float DH_Theta;

	float ScaleActuator;
	float Offset;
	float MaxLink, MinLink;


	hardwareManager* hwLocal;
	int hardwarePin;
	Link(int index,
		float DH_alpha, float DH_d, float DH_R, float DH_Theta,
		int ID, hardwareManager* hwptr,
		float ScaleActuator,
		float Offset,
		float MaxLink,
		float MinLink
		 	);
	/*
	 * getAngle returns angle of link in degrees
	 */
	float getAngle();
	Matrix<4,4> &computeStep(Matrix <4,4> &pose, float currAngle);
	IKResult cacheValue(float valueInDegrees);
};

#endif /* LIBRARIES_KINEMATICCHAINSARDUINO_LINK_H_ */
