/*
 * LewanSoulHardwareManager.h
 *
 *  Created on: May 19, 2021
 *      Author: aksha
 */

#ifndef LIBRARIES_KINEMATICCHAINSARDUINO_LEWANSOULHARDWAREMANAGER_H_
#define LIBRARIES_KINEMATICCHAINSARDUINO_LEWANSOULHARDWAREMANAGER_H_

#include <hardwareManager.h>
#include <lx16a-servo.h>

class LewanSoulHardwareManager: public hardwareManager {
public:
	LewanSoulHardwareManager();
	virtual ~LewanSoulHardwareManager();
	float getCurrentValue(int Pin);
	bool isHardwareReady();
	void SynchronizeMove(int milSec);
	bool IsMoveDone();
	void Initialize();


private:
	bool IsInitialized = false;
	int num = 3;
	int startingAngles[3] = {-9000, 8614, 3371};
	int upperAngles[3] = {9000,10000,6300};
	int lowerAngles[3] = {-9000,-4500,-9000};
	LX16ABus servoBus;
	LX16AServo ** motors;
	bool HardwareReady = false;
	long StartTime;
	long TimeToTake = 0;
	bool IsRunning = false;
};

#endif /* LIBRARIES_KINEMATICCHAINSARDUINO_LEWANSOULHARDWAREMANAGER_H_ */
