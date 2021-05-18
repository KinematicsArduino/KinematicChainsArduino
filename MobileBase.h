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
		 *
		 */
		void parse();

		/*
		 * Adds Limb to mobile base
		 * @param limbPtr a pointer to the new limb
		 */
		void addLimb(Limb* limbPtr);

		/*
		 * Solves for the forward kinematics of limb "index"
		 * @param Result  a matrix that stores the resultant transformation
		 * @param currAngles  an array of current angles
		 * @param index  index of limb to solve
		 */
		Matrix<4,4> &FKofLimb(Matrix<4,4> &Result, float* currAngles, int index);

		/*
		 * Solves the inverse kinematics of limb "Index"
		 * @param Target The target transformation
		 * @param Result The resultant angles
		 * @param Index The limb index
		 */
		bool IKofLimb(Matrix<4,4> &Target, float* Result, int Index);

};



#endif /* LIBRARIES_KINEMATICCHAINSARDUINO_MOBILEBASE_H_ */
