#include <KinematicChainsArduino.h>
#include <ArduinoJson.h>
#include <SD.h>
#include <SPI.h>
#include <Geometry.h>

hardwareManager hw;
MobileBase Robot(&hw);
String filename;
void setup(){
	  // Open file for reading
	  File file = SD.open(filename.c_str());
	  Robot.parse(&file);

	  Transformation Result;
	  Robot.FKofLimb(&Result, 0);
	  for(int r = 0; r<4; r++) {

	 		  Serial.println("{");
	  	 		for(int k = 0; k<4; k++) {

		  	 		  Serial.print(Result(r,k));
		  	 		  Serial.print(", ");
	  	 		}
	  	 	}
}

void loop(){


}
