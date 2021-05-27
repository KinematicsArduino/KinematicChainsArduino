/*
 * Link.cpp
 *
 *  Created on: Apr 27, 2021
 *      Author: aksha
 */

#include <Link.h>
//
//Matrix<4, 4>& invert(Matrix<4, 4> &poseT){
//	float Tempor[4][4] = {{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}};
//	for(int i = 0; i<3;i++){
//			for(int j = 0; j<3;j++){
//				Tempor[i][j] = poseT(j,i);
//			}
//		}
//	for(int i = 0; i<3;i++){
//			for(int j = 0; j<3;j++){
//				poseT(i,j) = Tempor[i][j];
//			}
//		}
//
//	return poseT;
//}
void PrintMatrix(Matrix<4, 4> MatrixEx, String name) {
	Serial.println(name);
	for (int r = 0; r < 4; r++) {

		Serial.println("{");
		for (int k = 0; k < 4; k++) {

			Serial.print(MatrixEx(r, k));
			Serial.print(", ");
		}

		Serial.println("}");
	}
	Serial.println("{");
}

void PrintTransform(Transformation T, String name) {
	Serial.println(name);
	for (int r = 0; r < 3; r++) {

		Serial.println("{");
		for (int k = 0; k < 3; k++) {

			Serial.print(T.R(r, k));

			Serial.print(", ");
		}

		Serial.print(T.p(r));

		Serial.println("}");
	}
	Serial.println("{");
}

void PrintIKResult(IKResult Error){
	switch(Error){
	case IKSuccess:
		Serial.println("IKSuccess");
		break;
	case JointLimits:
		Serial.println("JointLimits");
		break;
	case ElbowTriangleSingularity:
		Serial.println("ElbowTriangleSingularity");
		break;
	case OutsideOfWorkspace:
		Serial.println("OutsideOfWorkspace");
		break;
	case DHConfigError:
		Serial.println("DHConfigError");
		break;
	case NumberOfLinksError:
		Serial.println("NumberOfLinksError");
		break;
	case Quadrants2and3Unreachable:
	Serial.println("Quadrants2and3Unreachable");
	break;
	}
}

Matrix<4, 4>& RotateZ(Matrix<4, 4> &poseT, float theta) {

	float tmp1, tmp2;
	//poseT = invert(poseT);
	tmp1 = poseT(0, 0) * cos(theta) - poseT(1, 0) * sin(theta);
	tmp2 = poseT(1, 0) * cos(theta) + poseT(0, 0) * sin(theta);
	poseT(0, 0) = tmp1;
	poseT(1, 0) = tmp2;

	tmp1 = poseT(0, 1) * cos(theta) - poseT(1, 1) * sin(theta);
	tmp2 = poseT(1, 1) * cos(theta) + poseT(0, 1) * sin(theta);
	poseT(0, 1) = tmp1;
	poseT(1, 1) = tmp2;

	tmp1 = poseT(0, 2) * cos(theta) - poseT(1, 2) * sin(theta);
	tmp2 = poseT(1, 2) * cos(theta) + poseT(0, 2) * sin(theta);
	poseT(0, 2) = tmp1;
	poseT(1, 2) = tmp2;

	poseT(3, 0) = cos(theta) * poseT(3, 0) - sin(theta) * poseT(3, 1);
	poseT(3, 1) = sin(theta) * poseT(3, 0) + cos(theta) * poseT(3, 1);
	poseT(0, 2) = tmp1;
	poseT(1, 2) = tmp2;
	//poseT = invert(poseT);

	float TempY = cos(theta) * poseT(0, 3) - sin(theta) * poseT(1, 3);
	poseT(0, 3) = sin(theta) * poseT(0, 3) + cos(theta) * poseT(1, 3);
	poseT(1, 3) = TempY;
	return poseT;
}

Matrix<4, 4>& RotateX(Matrix<4, 4> &poseT, float alpha) {
	//poseT = invert(poseT);

	float tmp1, tmp2;
	tmp1 = poseT(1, 0) * cos(alpha) - poseT(2, 0) * sin(alpha);
	tmp2 = poseT(2, 0) * cos(alpha) + poseT(1, 0) * sin(alpha);
	poseT(1, 0) = tmp1;
	poseT(2, 0) = tmp2;

	tmp1 = poseT(1, 1) * cos(alpha) - poseT(2, 1) * sin(alpha);
	tmp2 = poseT(2, 1) * cos(alpha) + poseT(1, 1) * sin(alpha);
	poseT(1, 1) = tmp1;
	poseT(2, 1) = tmp2;

	tmp1 = poseT(1, 2) * cos(alpha) - poseT(2, 2) * sin(alpha);
	tmp2 = poseT(2, 2) * cos(alpha) + poseT(1, 2) * sin(alpha);
	poseT(1, 2) = tmp1;
	poseT(2, 2) = tmp2;
	//poseT = invert(poseT);

	float TempY = cos(alpha) * poseT(1, 3) - sin(alpha) * poseT(2, 3);
	poseT(2, 3) = sin(alpha) * poseT(1, 3) + cos(alpha) * poseT(2, 3);
	poseT(1, 3) = TempY;
	return poseT;
}

Matrix<4, 4>& TranslateZ(Matrix<4, 4> &poseT, float D) {
	poseT(2, 3) += D;
	return poseT;
}

Matrix<4, 4>& TranslateX(Matrix<4, 4> &poseT, float R) {
	poseT(0, 3) += R;
	return poseT;
}

Link::Link(int index, float DH_alpha, float DH_d, float DH_r, float DH_theta,
		int ID, hardwareManager *hwptr, float scale, float offset, float maxLink, float minLink) {
	MaxLink = maxLink;
	MinLink = minLink;
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

float Link::getAngle() {
	return ScaleActuator * (hwLocal->getCurrentValue(hardwarePin) - Offset);
}

Matrix<4, 4>& Link::computeStep(Matrix<4, 4> &poseT, float currAngle) {
//	Transformation pose;
//	for (int i = 0; i < 3; i++) {
//		for (int j = 0; j < 3; j++) {
//			pose.R(i, j) = poseT(i, j);
//		}
//		pose.p(i) = poseT(i, 3);
//	}
	Matrix<4, 4> MatrixD = BLA::Identity<4, 4>();
	Matrix<4, 4> MatrixTheta = BLA::Identity<4, 4>();
	Matrix<4, 4> MatrixAlpha = BLA::Identity<4, 4>();
	Matrix<4, 4> MatrixR = BLA::Identity<4, 4>();
	TranslateZ(MatrixD, DH_D);
	poseT *= MatrixD;
	//PrintMatrix(poseT, "D" + String(DH_D) + " " + String(linkIndex));
	RotateZ(MatrixTheta, DH_Theta + (3.14159*currAngle/180.0));
	poseT *= MatrixTheta;
	//PrintMatrix(poseT, "Theta" + String(180*DH_Theta/3.14159+currAngle) + " " + String(linkIndex));
	RotateX(MatrixAlpha, DH_Alpha);
	poseT *= MatrixAlpha;
	//PrintMatrix(poseT, "Alpha" + String(180/3.14159*DH_Alpha) + " " + String(linkIndex));
	TranslateX(MatrixR, DH_R);
	poseT *= MatrixR;
	//PrintMatrix(poseT, "R" + String(DH_R) + " " + String(linkIndex));

//	for (int i = 0; i < 3; i++) {
//		for (int j = 0; j < 3; j++) {
//			poseT(i, j) = pose.R(i, j);
//		}
//		poseT(i, 3) = pose.p(i);
//	}
	return poseT;
}




IKResult Link::cacheValue(float valueInDegrees){
	if((valueInDegrees>MaxLink)||(valueInDegrees<MinLink)){return JointLimits;}
	hwLocal->StoreValue(hardwarePin, (valueInDegrees/ScaleActuator)+Offset);
	return IKSuccess;
}
