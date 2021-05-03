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

void MobileBase::parse(File* file){

		StaticJsonDocument<500> doc;

	  DeserializationError error = deserializeJson(doc, file);
	  if (error) {
	      Serial.print(F("deserializeJson() failed: "));
	      Serial.println(error.f_str());
	      return;
	    }
	  int Limbs_size = doc.getMember("Limbs_size");
	  for(int i = 0; i < Limbs_size;i++){

		  Limb* limb2make = new Limb;
		  limb2make->addIndex(i);
		  //Define LimbRoot transformation
	 	  double limbRoot[16] = {

	 			  			 doc.getMember("limbRoot"+"0"+"0"),
	 						 doc.getMember("limbRoot"+"0"+"1"),
	 						 doc.getMember("limbRoot"+"0"+"2"),
	 						 doc.getMember("limbRoot"+"0"+"3"),
	 			  			 doc.getMember("limbRoot"+"1"+"0"),
	 						 doc.getMember("limbRoot"+"1"+"1"),
	 						 doc.getMember("limbRoot"+"1"+"2"),
	 						 doc.getMember("limbRoot"+"1"+"3"),
	 			  			 doc.getMember("limbRoot"+"2"+"0"),
	 						 doc.getMember("limbRoot"+"2"+"1"),
	 						 doc.getMember("limbRoot"+"2"+"2"),
	 						 doc.getMember("limbRoot"+"2"+"3"),
	 			  			 doc.getMember("limbRoot"+"3"+"0"),
	 						 doc.getMember("limbRoot"+"3"+"1"),
	 						 doc.getMember("limbRoot"+"3"+"2"),
	 						 doc.getMember("limbRoot"+"3"+"3")
	 	  };


	 	  	  //Add transformation to limb pointer
	 	  //limb2make->addTransformation(limbRoot);



	 	  const char* LimbName = doc.getMember("LimbNames"+String(i));
	 	  limb2make->addName(LimbName);
	 	  int Limb_size = doc.getMember(String(LimbName)+"_size");
	 	  limb2make->addSize(Limb_size);
	 	  for(int j = 0;j<Limb_size;j++){
	 		  Link* linkptr = new Link;
	 		  linkptr->addIndex(j);

	 		  //Getting DH parameters
	 		  double DH_alpha = doc.getMember(String(LimbName)+"_DH_"+j)[0];
	 		  double DH_d = doc.getMember(String(LimbName)+"_DH_"+j)[1];
	 		  double DH_r = doc.getMember(String(LimbName)+"_DH_"+j)[2];
	 		  double DH_theta = doc.getMember(String(LimbName)+"_DH_"+j)[3];

	 		  //Putting DH parameters in an array
	 		  double DH[4] = {DH_alpha,DH_d, DH_r, DH_theta};

	 		  //proccess in hardware manager
	 		  hwLocal->initHardware(linkptr);

	 		  //add to link
	 		  linkptr->addDH(DH);

	 		  //add to limb array
	 		  limb2make->addLinkPtr(linkptr,j);

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

