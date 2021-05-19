/*
 * LewanSoulHardwareManager.cpp
 *
 *  Created on: May 19, 2021
 *      Author: aksha
 */

#include <LewanSoulHardwareManager.h>

#include <Arduino.h>

LewanSoulHardwareManager::LewanSoulHardwareManager() {
	// TODO Auto-generated constructor stub

}

LewanSoulHardwareManager::~LewanSoulHardwareManager() {
	// TODO Auto-generated destructor stub

}

float LewanSoulHardwareManager::getCurrentValue(int Pin) {
	return motors[Pin]->pos_read();
}


bool LewanSoulHardwareManager::isHardwareReady() {
	if (!HardwareReady) {
		Initialize();
		if (digitalRead(0) == 0) {
			for(int i = 0; i<num; i++){
				motors[i]->calibrate(startingAngles[i],lowerAngles[i],upperAngles[i]);


				int32_t pos = startingAngles[i]-motors[i]->pos_read();
					if(pos!=0){
						Serial.println("Settling Error of"+String(pos));
						return false;
					}
			}
			HardwareReady = true;
		}
	}
	return HardwareReady;
}

void LewanSoulHardwareManager::Initialize() {

	if(IsInitialized)return;
	pinMode(0, INPUT_PULLUP);
	servoBus.beginOnePinMode(&Serial1, 15);
	motors = new LX16AServo*[num];
	for (int i = 0; i < num; i++) {
		hardwareIndexMap[i] = i+1;
		motors[i] = new LX16AServo(&servoBus, i + 1);
		motors[i]->disable();
	}
	IsInitialized = true;


}

void LewanSoulHardwareManager::SynchronizeMove(int milSec) {
	for(int i = 0; i < num; i++){
	motors[i]->move_time_and_wait_for_sync(ValMap[i], milSec);
	}

	servoBus.move_sync_start();
	StartTime = millis();
	TimeToTake = milSec;
	IsRunning = true;
}

bool LewanSoulHardwareManager::IsMoveDone() {
	IsRunning = (millis()-StartTime > TimeToTake);
	return IsRunning;
}
