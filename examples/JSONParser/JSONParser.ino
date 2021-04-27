// ArduinoJson - arduinojson.org
// Copyright Benoit Blanchon 2014-2021
// MIT License
//
// This example shows how to deserialize a JSON document with ArduinoJson.
//
// https://arduinojson.org/v6/example/parser/

#include <ArduinoJson.h>

void setup() {
  // Initialize serial port
  Serial.begin(115200);
  Serial.println("test");
  //while (!Serial) continue;

  // Allocate the JSON document
  //
  // Inside the brackets, 200 is the capacity of the memory pool in bytes.
  // Don't forget to change this value to match your JSON document.
  // Use arduinojson.org/v6/assistant to compute the capacity.
  StaticJsonDocument<500> doc;

  // StaticJsonDocument<N> allocates memory on the stack, it can be
  // replaced by DynamicJsonDocument which allocates in the heap.
  //
  // DynamicJsonDocument doc(200);

  // JSON input string.
  //
  // Using a char[], as shown here, enables the "zero-copy" mode. This mode uses
  // the minimal amount of memory because the JsonDocument stores pointers to
  // the input buffer.
  // If you use another type of input, ArduinoJson must copy the strings from
  // the input to the JsonDocument, so you need to increase the capacity of the
  // JsonDocument.
  char json[] = "{  \"Limbs_size\": 1,  \"HephaestusArmLimbOne_DH_2\": [    0.0,    0.0,    100.0,    1.5707963267948966  ],  \"HephaestusArmLimbOne_DH_0\": [    -1.5707963267948966,    40.0,    0.0,    0.0  ],  \"LimbNames0\": \"HephaestusArmLimbOne\",  \"HephaestusArmLimbOne_DH_1\": [    0.0,    0.0,    100.0,    -1.5707963267948966  ],  \"HephaestusArmLimbOne_size\": 3}";
  DeserializationError error = deserializeJson(doc, json);

  // Test if parsing succeeds.
  if (error) {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.f_str());
    return;
  }

  // Fetch values.
  //
  // Most of the time, you can rely on the implicit casts.
  // In other case, you can do doc["time"].as<long>();


  int Limbs_size = doc.getMember("Limbs_size");

  // [Limb][link][parameter]

  for(int i = 0; i < Limbs_size;i++){

	  double limbRoot[4][4] = {
			  	 {
			  			 doc.getMember("limbRoot"+String(0)+String(0)),
						 doc.getMember("limbRoot"+String(0)+String(1)),
						 doc.getMember("limbRoot"+String(0)+String(2)),
						 doc.getMember("limbRoot"+String(0)+String(3)),
			  	 }
			  	 ,{
			  			 doc.getMember("limbRoot"+String(1)+String(0)),
						 doc.getMember("limbRoot"+String(1)+String(1)),
						 doc.getMember("limbRoot"+String(1)+String(2)),
						 doc.getMember("limbRoot"+String(1)+String(3)),
			  	 }
			  	 ,{
			  			 doc.getMember("limbRoot"+String(2)+String(0)),
						 doc.getMember("limbRoot"+String(2)+String(1)),
						 doc.getMember("limbRoot"+String(2)+String(2)),
						 doc.getMember("limbRoot"+String(2)+String(3)),
			  	 }
			  	 ,{
			  			 doc.getMember("limbRoot"+String(3)+String(0)),
						 doc.getMember("limbRoot"+String(3)+String(1)),
						 doc.getMember("limbRoot"+String(3)+String(2)),
						 doc.getMember("limbRoot"+String(3)+String(3)),
			  	 }
	  };

	  const char* LimbName = doc.getMember("LimbNames"+String(i));
	  Serial.println("Limb name: "+String(LimbName));
	  int Limb_size = doc.getMember(String(LimbName)+"_size");
	  Serial.println("Limb Size: "+String(Limb_size));

	  for(int j = 0;j<Limb_size;j++){

		  //float* DH = doc[String(LimbName)+"_DH_"+j];
		  double DH_alpha = doc.getMember(String(LimbName)+"_DH_"+j)[0];
		  double DH_d = doc.getMember(String(LimbName)+"_DH_"+j)[1];
		  double DH_r = doc.getMember(String(LimbName)+"_DH_"+j)[2];
		  double DH_theta = doc.getMember(String(LimbName)+"_DH_"+j)[3];
		  Serial.println(String (j)+" Alpha: "+String(DH_alpha));
		  Serial.println(String (j)+" D: "+String(DH_d));
		  Serial.println(String (j)+" R: "+String(DH_r));
		  Serial.println(String (j)+" Theta: "+String(DH_theta));

		  //Serial.println("Alpha: "+String(DH[0]));
		  //Serial.println("D: "+String(DH[1]));
		  //Serial.println("R: "+String(DH[2]));
		  //Serial.println("Theta: "+String(DH[3]));
	  }
  }
}

void loop() {
  // not used in this example
}

// See also
// --------
//
// https://arduinojson.org/ contains the documentation for all the functions
// used above. It also includes an FAQ that will help you solve any
// deserialization problem.
//
// The book "Mastering ArduinoJson" contains a tutorial on deserialization.
// It begins with a simple example, like the one above, and then adds more
// features like deserializing directly from a file or an HTTP request.
// Learn more at https://arduinojson.org/book/
// Use the coupon code TWENTY for a 20% discount â�¤â�¤â�¤â�¤â�¤
