#include <lx16a-servo.h>
#include <KinematicChainsArduino.h>
#include <ArduinoJson.h>
#include <SD.h>
#include <SPI.h>
#include <Geometry.h>
#include <BasicLinearAlgebra.h>
#include <LewanSoulHardwareManager.h>

LewanSoulHardwareManager hw;
MobileBase Robot(&hw);

void setup() {

	Serial.begin(115200);
	Serial.println("Starting mobile base test");
	hw.Initialize();
	while (!hw.isHardwareReady()) {
		Serial.println("Waiting For Hardware");
		delay(1000);
	}
	Serial.println("Starting Parse");
	// Open file for reading
	Robot.parse();

	for (float j = -100; j < 100; j += 3) {
		BLA::Matrix<4, 4> Result = BLA::Identity<4, 4>();
		Result(1,3) =-j;
		Result(0,3) = 100;
		Result(2,3) = 195;

		IKResult Error = Robot.MoveToTarget(0, 10, Result);
		if (Error == IKSuccess) {
			while (!Robot.IsHWDone()) {
				//Serial.println("Moving Robot");
				//delay(100);
			};
		}else {PrintIKResult(Error);}
	}

}

void loop() {

}
