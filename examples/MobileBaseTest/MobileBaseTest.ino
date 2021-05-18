#include <KinematicChainsArduino.h>
#include <ArduinoJson.h>
#include <SD.h>
#include <SPI.h>
#include <Geometry.h>
#include <BasicLinearAlgebra.h>

hardwareManager hw;
MobileBase Robot(&hw);


void setup(){

	Serial.begin(115200);
	Serial.println("Starting mobile base test");

	// Open file for reading
	  Robot.parse();

	  BLA::Matrix<4,4> Result = BLA::Identity<4,4>();
	  float R[3] = {0,0,0};
	  Result = Robot.FKofLimb(Result, R,0);


	  float IkAngles[3] = {-1,-1,-1};
	  Robot.IKofLimb(Result, IkAngles ,0);
	  Serial.println(" \n {");
	  for(int i=0; i<3; i++){
		  Serial.print(IkAngles[i]);
	  }

}

void loop(){


}
