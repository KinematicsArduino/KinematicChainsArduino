/*
 * hardwareManager.cpp
 *
 *  Created on: Apr 27, 2021
 *      Author: aksha
 */

#include <hardwareManager.h>
#include<math.h>


	void hardwareManager::StoreValue(int Pin, float Target){
		ValMap[Pin] = Target;
	}


	float hardwareManager::GetStoredVal(int Pin){
		return ValMap[Pin];
	}
