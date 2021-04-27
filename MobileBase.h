/*
 * MobileBase.h
 *
 *  Created on: Apr 27, 2021
 *      Author: aksha
 */

#ifndef LIBRARIES_KINEMATICCHAINSARDUINO_MOBILEBASE_H_
#define LIBRARIES_KINEMATICCHAINSARDUINO_MOBILEBASE_H_

#include "Limb.h"
#include "hardwareManager.h"
#include <Geometry.h>
#include <ArduinoJson.h>
#include <SD.h>
#include <SPI.h>


#define MaxLimbs 20
class MobileBase{
	private:
		int numberOfLimbs = 0;
		Limb* limbs[MaxLimbs];
		Transformation gndToFiducial;
		hardwareManager* hwLocal;
	public:
		MobileBase(File* file, hardwareManager* hwptr);


};



#endif /* LIBRARIES_KINEMATICCHAINSARDUINO_MOBILEBASE_H_ */
