/*
 * hardwareManager.h
 *
 *  Created on: Apr 27, 2021
 *      Author: aksha
 */

#ifndef LIBRARIES_KINEMATICCHAINSARDUINO_HARDWAREMANAGER_H_
#define LIBRARIES_KINEMATICCHAINSARDUINO_HARDWAREMANAGER_H_

#include <map>

class hardwareManager {
public:
	hardwareManager(){}

	virtual float getCurrentValue(int Pin) = 0;
	virtual bool isHardwareReady() = 0;
	virtual void SynchronizeMove(int milSec) = 0;
	virtual bool IsMoveDone() = 0;
	virtual void Initialize() = 0;

	void StoreValue(int Pin, float Value);
	float GetStoredVal(int Pin);
	std::map<int, float> ValMap;
	std::map<int, int> hardwareIndexMap;


};



#endif /* LIBRARIES_KINEMATICCHAINSARDUINO_HARDWAREMANAGER_H_ */
