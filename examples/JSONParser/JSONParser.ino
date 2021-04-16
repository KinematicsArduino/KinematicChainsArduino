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
  char json[] ="\n"
		  + "{\n"
		  + "  \"Limbs_size\": 1,\n"
		  + "  \"HephaestusArmLimbOne_DH_2\": [\n"
		  + "    0.0,\n"
		  + "    0.0,\n"
		  + "    100.0,\n"
		  + "    1.5707963267948966\n"
		  + "  ],\n"
		  + "  \"HephaestusArmLimbOne_DH_0\": [\n"
		  + "    -1.5707963267948966,\n"
		  + "    40.0,\n"
		  + "    0.0,\n"
		  + "    0.0\n"
		  + "  ],\n"
		  + "  \"LimbNames0\": \"HephaestusArmLimbOne\",\n"
		  + "  \"HephaestusArmLimbOne_DH_1\": [\n"
		  + "    0.0,\n"
		  + "    0.0,\n"
		  + "    100.0,\n"
		  + "    -1.5707963267948966\n"
		  + "  ],\n"
		  + "  \"HephaestusArmLimbOne_size\": 3\n"
		  + "}";
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
  int Limbs_size = doc["Limbs_size"];

  // [Limb][link][parameter]

  for(int i = 0; i < Limbs_size;i++){
	  char* LimbName = doc["LimbName"+String(i)];
	  Serial.println("Limb name: "+String(LimbName));
	  int Limb_size = doc[String(LimbName)+"_size"];
	  Serial.println("Limb Size: "+String(Limb_size));
	  for(int j = 0;j<Limb_size;j++){

		  float* DH = doc[String(LimbName)+"_DH_"+j];
		  Serial.println("Alpha: "+String(DH[0]));
		  Serial.println("D: "+String(DH[1]));
		  Serial.println("R: "+String(DH[2]));
		  Serial.println("Theta: "+String(DH[3]));
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
