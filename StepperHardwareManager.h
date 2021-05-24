/*
 * StepperHardwareManager.h
 *
 *  Created on: May 23, 2021
 *      Author: aksha
 */

#ifndef LIBRARIES_KINEMATICCHAINSARDUINO_STEPPERHARDWAREMANAGER_H_
#define LIBRARIES_KINEMATICCHAINSARDUINO_STEPPERHARDWAREMANAGER_H_


#include <hardwareManager.h>
  #include "AccelStepper.h"
  #include <MultiStepper.h>
class StepperHardwareManager: public hardwareManager {
public:
	StepperHardwareManager(int* hardwareDirArray, int* hardwareStepArray, int size);
	StepperHardwareManager();
	virtual ~StepperHardwareManager();
	float getCurrentValue(int Pin);
	bool isHardwareReady();
	void SynchronizeMove(int milSec);
	void SyncStep();
	bool IsMoveDone();
	void Initialize();

private:
	bool IsInitialized = false;
	int num = 3;
	std::map<int, int> hardwareDirMap;
	AccelStepper **motors;
	bool HardwareReady = false;

	int stepsPerRevolution = 200;
	float GearRatio = 5;

};

#endif /* LIBRARIES_KINEMATICCHAINSARDUINO_STEPPERHARDWAREMANAGER_H_ */
