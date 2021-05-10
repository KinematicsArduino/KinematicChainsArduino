/*
 * MobileBase.cpp
 *
 *  Created on: Apr 27, 2021
 *      Author: aksha
 */


#include "MobileBase.h"

MobileBase::MobileBase(hardwareManager* hwptr){
	hwLocal = hwptr;

}


/*
*	reads the SD card configuration file and initializes Mobile base off of it.
* @param file, the JSON config file
*/
void MobileBase::parse(File &file){

		StaticJsonDocument<500> doc;

	  DeserializationError error = deserializeJson(doc, file);
	  if (error) {
	      Serial.print(F("deserializeJson() failed: "));
	      Serial.println(error.f_str());
	      return;
	    }
	  int Limbs_size = doc.getMember("Limbs_size");
	  for(int i = 0; i < Limbs_size;i++){


		  //Define LimbRoot transformation
	 	  BLA::Matrix<4,4> limbRoot;
	 	for(int r = 0; r<4; r++) {
	 		for(int k = 0; k<4; k++) {
	 			limbRoot(r,k) = doc.getMember("limbRoot"+String(i))[r*4+k];
	 		}
	 	}





	 	  const char* LimbName = doc.getMember("LimbNames"+String(i));
	 	  int Limb_size = doc.getMember(String(LimbName)+"_size");
	 	 Limb* limb2make = new Limb(1, LimbName, limbRoot, hwLocal);
	 	  for(int j = 0;j<Limb_size;j++){

	 		  //Getting DH parameters
	 		  double DH_alpha = doc.getMember(String(LimbName)+"_DH_"+String(j))[0];
	 		  double DH_d = doc.getMember(String(LimbName)+"_DH_"+String(j))[1];
	 		  double DH_r = doc.getMember(String(LimbName)+"_DH_"+String(j))[2];
	 		  double DH_theta = doc.getMember(String(LimbName)+"_DH_"+String(j))[3];

	 		 int PinNumber = doc.getMember(String(LimbName)+"HardwareManager"+String(j));
	 		 float offset = doc.getMember(String(LimbName)+"Offset"+String(j));
	 		 float scale = doc.getMember(String(LimbName)+"scale"+String(j));
	 		  Link* linkptr = new Link(j, DH_alpha, DH_d, DH_r, DH_theta, PinNumber, hwLocal, scale, offset);
	 		  //add to limb array
	 		  limb2make->addLinkPtr(linkptr);

	 	  }
	 	  addLimb(limb2make);
	   }
	 }




/*
* Adds Limb to mobile base
* @param limbPtr, a pointer to the new limb
*/
void MobileBase::addLimb(Limb* limbPtr){
	limbs[numberOfLimbs] = limbPtr;
	numberOfLimbs++;
}


void MobileBase::FKofLimb(Matrix<4,4> &Result, int index){
	if(index>= numberOfLimbs) return;
	Result = gndToFiducial;
	limbs[index]->FK(Result);
}

