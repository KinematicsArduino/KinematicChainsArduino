/*
 * StepperHardwareManager.cpp
 *
 *  Created on: May 23, 2021
 *      Author: aksha
 */

#include <StepperHardwareManager.h>

StepperHardwareManager::StepperHardwareManager(int *hardwareDirArray,
		int *hardwareStepArray, int size) {
	// TODO Auto-generated constructor stub
	num = size;
	DegreesToHardware = stepsPerRevolution / 360 * GearRatio;
	for (int i = 0; i < num; i++) {
		hardwareDirMap[i] = hardwareDirArray[i];
		hardwareIndexMap[i] = hardwareStepArray[i];
	}

	Initialize();
}

StepperHardwareManager::~StepperHardwareManager() {
	// TODO Auto-generated destructor stub
	DegreesToHardware = stepsPerRevolution / 360 * GearRatio;
	for (int i = 0; i < num; i += 2) {
		hardwareDirMap[i] = i;
		hardwareIndexMap[i] = i + 1;
	}
}

float StepperHardwareManager::getCurrentValue(int Pin) {
	return motors[Pin]->distanceToGo();
}

//Not needed yet, left in in case we want to put stepper motor calibration
bool StepperHardwareManager::isHardwareReady() {
	if (!HardwareReady) {
		Initialize();
		HardwareReady = true;
	}
	return HardwareReady;
}

///blocking?
void StepperHardwareManager::SynchronizeMove(int milSec) {

	for (int i = 0; i < num; i++) {
		motors[i]->moveTo(int(ValMap[i] * DegreesToHardware));
		motors[i]->setSpeed(int(ValMap[i] * DegreesToHardware) / milSec);
	}
	//open thread to make non-blocking
	do {
		SyncStep();
	} while (!IsMoveDone());

}
void StepperHardwareManager::SyncStep() {
	for (int i = 0; i < num; i++) {
		motors[i]->runSpeedToPosition();
	}
}
bool StepperHardwareManager::IsMoveDone() {
	for (int i = 0; i < num; i++) {
		if (motors[i]->distanceToGo() != 0)
			return false;
	}
	return true;
}
void StepperHardwareManager::Initialize() {
	if (IsInitialized)
		return;
	motors = new AccelStepper*[num];
	for (int i = 0; i < num; i++) {
		pinMode(hardwareIndexMap[i], OUTPUT);
		pinMode(hardwareDirMap[i], OUTPUT);
		AccelStepper Temp(hardwareIndexMap[i], hardwareDirMap[i]);
		motors[i] = &Temp;
	}
}
