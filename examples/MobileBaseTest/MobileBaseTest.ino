#include <KinematicChainsArduino.h>
#include <ArduinoJson.h>
#include <SD.h>
#include <SPI.h>
#include <Geometry.h>
#include <BasicLinearAlgebra.h>

hardwareManager hw;
MobileBase Robot(&hw);

void setup() {

	Serial.begin(115200);
	Serial.println("Starting mobile base test");

	// Open file for reading
	Robot.parse();
	for (float j = -40; j < 31; j += 5) {
		BLA::Matrix<4, 4> Result = BLA::Identity<4, 4>();
		float R[3] = { j, j, j };
		Result = Robot.FKofLimb(Result, R, 0);
		PrintMatrix(Result, "Result");
		float IkAngles[3] = { -1, -1, -1 };

		if (Robot.IKofLimb(Result, IkAngles, 0)) {
			Serial.println(" \n {");
			for (int i = 0; i < 3; i++) {
				Serial.println(
						"Expected:" + String(R[i]) + "  Got:"
								+ String(IkAngles[i]));
			}
		} else {
			Serial.println("False");
		}
	}
}

void loop() {

}
