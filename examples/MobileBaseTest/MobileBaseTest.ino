#include <KinematicChainsArduino.h>
#include <ArduinoJson.h>
#include <SD.h>
#include <SPI.h>

hardwareManager hw;
MobileBase Robot(&hw);
String filename;
void setup(){
	  // Open file for reading
	  File file = SD.open(filename.c_str());
	  Robot.parse(&file);
}

void loop(){


}
