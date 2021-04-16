#include <Arduino.h>
#include <lx16a-servo.h>
LX16ABus servoBus;
LX16AServo servo(&servoBus, LX16A_BROADCAST_ID);// send these commands to any motor on the bus
int id =3;
void setup() {
	servoBus.beginOnePinMode(&Serial1, 15);// use pin 2 as the TX flag for buffer
	Serial.begin(115200);
}

void loop() {
	// Set any motor plugged in to ID 3
	// this INO acts as an auto-provisioner for any motor plugged in
	servo.id_write(id);
	Serial.println("Setting to ID "+String (id));
	delay(200);

}

