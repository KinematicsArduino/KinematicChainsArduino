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
		//PrintMatrix(Result, "Result");
		float IkAngles[3] = { -1, -1, -1 };
		IKResult Error = Robot.IKofLimb(Result, IkAngles, 0);
		if (Error == IKSuccess) {
			Serial.println(" \n {");
			for (int i = 0; i < 3; i++) {
				Serial.println("Expected:" + String(R[i]) + "  Got:"+ String(IkAngles[i]));
				hw.StoreValue(i, IkAngles[i]);
			}
			if (!hw.IsMoveDone())
				hw.SynchronizeMove(1000);

		} else {
			PrintIKResult(Error);
		}
	}
}

void loop() {

}
