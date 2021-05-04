/*
 * hardwareManager.h
 *
 *  Created on: Apr 27, 2021
 *      Author: aksha
 */

#ifndef LIBRARIES_KINEMATICCHAINSARDUINO_HARDWAREMANAGER_H_
#define LIBRARIES_KINEMATICCHAINSARDUINO_HARDWAREMANAGER_H_

#include "Link.h"

class hardwareManager {
public:
	hardwareManager();
	void initHardware(Link* link);
};

#endif /* LIBRARIES_KINEMATICCHAINSARDUINO_HARDWAREMANAGER_H_ */
