/*
 * hardwareManager.h
 *
 *  Created on: Apr 27, 2021
 *      Author: aksha
 */

#ifndef LIBRARIES_KINEMATICCHAINSARDUINO_HARDWAREMANAGER_H_
#define LIBRARIES_KINEMATICCHAINSARDUINO_HARDWAREMANAGER_H_

class hardwareManager {
public:
	hardwareManager();
	float getCurrentValue(int Pin);
};

#endif /* LIBRARIES_KINEMATICCHAINSARDUINO_HARDWAREMANAGER_H_ */
