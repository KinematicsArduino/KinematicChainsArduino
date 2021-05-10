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
	  Robot.FKofLimb(Result, 0);

		  Serial.println("FinalTransform");
	  for(int r = 0; r<4; r++) {

	 		  Serial.println("{");
	  	 		for(int k = 0; k<4; k++) {

		  	 		  Serial.print(Result(r,k));
		  	 		  Serial.print(", ");
	  	 		}

		 		  Serial.println("}");
	  	 	}
		  Serial.println("{");
}

void loop(){


}
