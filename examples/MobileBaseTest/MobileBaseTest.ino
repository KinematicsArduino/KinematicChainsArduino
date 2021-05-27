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

	for (float j = -30; j < 30; j += 5) {
		BLA::Matrix<4, 4> Result = BLA::Identity<4, 4>();
		float R[3] = { j, j, j };
		Result = Robot.FKofLimb(Result, R, 0);
		PrintMatrix(Result, "Result");

		IKResult Error = Robot.MoveToTarget(0, 1000, Result);
		if (Error == IKSuccess) {
			while (!Robot.IsHWDone()) {
				Serial.println("Moving Robot");
				delay(100);
			};
		}else {PrintIKResult(Error);}
	}

}

void loop() {

}
