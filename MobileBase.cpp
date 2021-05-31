/*
 * MobileBase.cpp
 *
 *  Created on: Apr 27, 2021
 *      Author: aksha
 */

#include "MobileBase.h"

MobileBase::MobileBase(hardwareManager *hwptr) {
	hwLocal = hwptr;

}

StaticJsonDocument<6000> doc;

/*
 *	reads the SD card configuration file and initializes Mobile base off of it.
 * @param file, the JSON config file
 */
void parseStatic(MobileBase *MB) {
	Serial.println("Beginning");
	while (!SD.begin(33)) {

		Serial.println(F("Failed to initialize SD library"));
		delay(1000);
	}
	const char *filename = "/config.json";
	File file = SD.open(filename);

	DeserializationError error = deserializeJson(doc, file);
	Serial.println(error.c_str());
	if (error) {
		Serial.print(F("deserializeJson() failed: "));
		Serial.println(error.c_str());
		return;
	}
	int Limbs_size = doc.getMember("Limbs_size");
	Serial.println("Limbs_size");
	for (int i = 0; i < Limbs_size; i++) {

		//Define LimbRoot transformation
		BLA::Matrix<4, 4> limbRoot;
		for (int r = 0; r < 4; r++) {
			for (int k = 0; k < 4; k++) {
				limbRoot(r, k) =
						doc.getMember("limbRoot" + String(i))[r * 4 + k];
			}
		}

		const char *LimbName = doc.getMember("LimbNames" + String(i));
		Serial.println("LimbNames");
		float Limb_size = doc.getMember(String(i) + "_size");
		Limb *limb2make = new Limb(1, LimbName, limbRoot, MB->hwLocal);

		Serial.println("Limb_size: " + String(Limb_size));

		for (int j = 0; j < Limb_size; j++) {

			double LimitUp = doc.getMember(String(i) + "Limit" + String(j))[0];
			double LimitDown = doc.getMember(String(i) + "Limit" + String(j))[1];

			//Getting DH parameters
			double DH_alpha = doc.getMember(String(i) + "_DH_" + String(j))[0];
			double DH_d = doc.getMember(String(i) + "_DH_" + String(j))[1];
			double DH_r = doc.getMember(String(i) + "_DH_" + String(j))[2];
			double DH_theta = doc.getMember(String(i) + "_DH_" + String(j))[3];

			int PinNumber = doc.getMember(
					String(i) + "HardwareIndex" + String(j));
			float offset = doc.getMember(String(i) + "Offset" + String(j));
			float scale = doc.getMember(String(i) + "scale" + String(j));
			Link *linkptr = new Link(j, DH_alpha, DH_d, DH_r, DH_theta,
					PinNumber, MB->hwLocal, scale, offset, LimitUp, LimitDown);
			//add to limb array
			limb2make->addLinkPtr(linkptr);

		}
		MB->addLimb(limb2make);
	}
}

void MobileBase::parse() {
	parseStatic(this);
}

/*
 * Adds Limb to mobile base
 * @param limbPtr, a pointer to the new limb
 */
void MobileBase::addLimb(Limb *limbPtr) {
	limbs[numberOfLimbs] = limbPtr;
	numberOfLimbs++;
}

Matrix<4, 4>& MobileBase::FKofLimb(Matrix<4, 4> &Result, float *currAngles,
		int index) {
	if (index >= numberOfLimbs)
		return Result;
	Result *= gndToFiducial;
	return limbs[index]->FK(Result, currAngles);
}

IKResult MobileBase::IKofLimb(Matrix<4, 4> &Target, float *Result, int Index) {
	if (Index >= numberOfLimbs)
		return NumberOfLinksError;
	Target = gndToFiducial.Inverse() * Target;
	return limbs[Index]->IK(Target, Result);
}

/*
 * Move a limb to target value
 * @param limbIndex The target limb index
 * @param milliseconds The time to move
 * @param target Target value
 * @return IKResult
 */
IKResult MobileBase::MoveToTarget(int limbIndex, int milliseconds,
		Matrix<4, 4> &Target) {
	int num = limbs[limbIndex]->GetNumberOfLinks();
	Serial.println("MobileBase::MoveToTarget number of links "+String(num));
	float JointValues[num];

	IKResult Error = IKofLimb(Target, JointValues, limbIndex);

	if (Error == IKSuccess) {
		for (int i = 0; i < num && Error == IKSuccess; i++) {
			Serial.println("MobileBase::MoveToTarget JointValue of"+String(i)+ "    "+ String(JointValues[i]));
			Error = limbs[limbIndex]->cacheValue(JointValues[i], i);
		}
		if (Error == IKSuccess) {
			hwLocal->SynchronizeMove(milliseconds);
		}
	}
	return Error;

}

/*
 * @return Is hw manager done
 */
bool MobileBase::IsHWDone() {
	return hwLocal->IsMoveDone();
}
