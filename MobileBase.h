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
		Matrix<4,4> gndToFiducial=BLA::Identity<4,4>();
	public:

		hardwareManager* hwLocal;
		/*
		 * Constructor function
		 * @param hwptr Pointer to the object that manages the actuators
		 */
		MobileBase(hardwareManager* hwptr);

		/*
		 * Parsing function, reads data from SD card and uses it to construct limbs
		 * @param
		 */
		void parse();

		/*
		 * Adds Limb to mobile base
		 * @param limbPtr, a pointer to the new limb
		 */
		void addLimb(Limb* limbPtr);

		Matrix<4,4> &FKofLimb(Matrix<4,4> &Result, int index);
};



#endif /* LIBRARIES_KINEMATICCHAINSARDUINO_MOBILEBASE_H_ */
