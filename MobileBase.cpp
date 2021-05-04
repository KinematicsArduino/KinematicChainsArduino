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
void MobileBase::parse(File* file){

		StaticJsonDocument<500> doc;

	  DeserializationError error = deserializeJson(doc, file[0]);
	  if (error) {
	      Serial.print(F("deserializeJson() failed: "));
	      Serial.println(error.f_str());
	      return;
	    }
	  int Limbs_size = doc.getMember("Limbs_size");
	  for(int i = 0; i < Limbs_size;i++){

		  Limb* limb2make = new Limb();
		  limb2make->addIndex(i);
		  //Define LimbRoot transformation
	 	  double limbRoot[16];
		 	 limbRoot[0]=doc.getMember("limbRoot00");
		 	 limbRoot[1]=doc.getMember("limbRoot01");
		 	 limbRoot[2]=doc.getMember("limbRoot02");
		 	 limbRoot[3]=doc.getMember("limbRoot03");

		 	 limbRoot[4]=doc.getMember("limbRoot10");
		 	 limbRoot[5]=doc.getMember("limbRoot11");
		 	 limbRoot[6]=doc.getMember("limbRoot12");
		 	 limbRoot[7]=doc.getMember("limbRoot13");

		 	 limbRoot[8]=doc.getMember("limbRoot20");
		 	 limbRoot[9]=doc.getMember("limbRoot21");
		 	 limbRoot[10]=doc.getMember("limbRoot22");
		 	 limbRoot[11]=doc.getMember("limbRoot23");

		 	 limbRoot[12]=doc.getMember("limbRoot30");
		 	 limbRoot[13]=doc.getMember("limbRoot31");
		 	 limbRoot[14]=doc.getMember("limbRoot32");
		 	 limbRoot[15]=doc.getMember("limbRoot33");
	 	  	  //Add transformation to limb pointer
	 	  //limb2make->addTransformation(limbRoot);



	 	  const char* LimbName = doc.getMember("LimbNames"+String(i));
	 	  limb2make->addName(LimbName);
	 	  int Limb_size = doc.getMember(String(LimbName)+"_size");
	 	  limb2make->addSize(Limb_size);
	 	  for(int j = 0;j<Limb_size;j++){
	 		  Link* linkptr = new Link();
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

