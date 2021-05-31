/*
 * hardwareManager.cpp
 *
 *  Created on: Apr 27, 2021
 *      Author: aksha
 */

#include <hardwareManager.h>
#include<math.h>
#include <Arduino.h>


	void hardwareManager::StoreValue(int Pin, float Target){
		int HWMap = hardwareIndexMap[Pin];
		Serial.println("PIN: " + String(Pin)+ "  HWMap:" +String(HWMap));
		ValMap[HWMap] = Target;

	}


	float hardwareManager::GetStoredVal(int Pin){
		return ValMap[hardwareIndexMap[Pin]];
	}
