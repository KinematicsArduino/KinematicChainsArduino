// ArduinoJson - arduinojson.org
// Copyright Benoit Blanchon 2014-2021
// MIT License
//
// This example shows how to store your project configuration in a file.
// It uses the SD library but can be easily modified for any other file-system.
//
// The file contains a JSON document with the following content:
// {
//   "hostname": "examples.com",
//   "port": 2731
// }
//
// To run this program, you need an SD card connected to the SPI bus as follows:
// * MOSI <-> pin 11
// * MISO <-> pin 12
// * CLK  <-> pin 13
// * CS   <-> pin 4
//
// https://arduinojson.org/v6/example/config/

#include <ArduinoJson.h>
#include <SD.h>
#include <SPI.h>

// Our configuration structure.
//
// Never use a JsonDocument to store the configuration!
// A JsonDocument is *not* a permanent storage; it's only a temporary storage
// used during the serialization phase. See:
// https://arduinojson.org/v6/faq/why-must-i-create-a-separate-config-object/

const char *filename = "/LimbDefinition.json";  // <- SD library uses 8.3 filenames

// Loads the configuration from a file
void loadConfiguration(const char *filename) {
  // Open file for reading
  File file = SD.open(filename);

  // Allocate a temporary JsonDocument
  // Don't forget to change the capacity to match your requirements.
  // Use arduinojson.org/v6/assistant to compute the capacity.
  StaticJsonDocument<512> doc;

  // Deserialize the JSON document
  DeserializationError error = deserializeJson(doc, file);
  if (error)
    Serial.println(F("Failed to read file, using default configuration"));
  	file.close();
}


// Prints the content of a file to the Serial
void printFile(const char *filename) {
  // Open file for reading
  File file = SD.open(filename);
  if (!file) {
    Serial.println(F("Failed to read file"));
    return;
  }

  // Extract each characters by one by one
  while (file.available()) {
    Serial.print((char)file.read());
  }
  Serial.println();

  // Close the file
  file.close();
}

void setup() {
  // Initialize serial port
  Serial.begin(9600);
  while (!Serial) continue;

  // Initialize SD library
  const int chipSelect = 4;
  while (!SD.begin(chipSelect)) {
    Serial.println(F("Failed to initialize SD library"));
    delay(1000);
  }

  // Should load default config if run for the first time
  Serial.println(F("Loading configuration..."));
  loadConfiguration(filename);


  // Dump config file
  Serial.println(F("Print config file..."));
  printFile(filename);
}

void loop() {
  // not used in this example
}

// Performance issue?
// ------------------
//
// File is an unbuffered stream, which is not optimal for ArduinoJson.
// See: https://arduinojson.org/v6/how-to/improve-speed/

// See also
// --------
//
// https://arduinojson.org/ contains the documentation for all the functions
// used above. It also includes an FAQ that will help you solve any
// serialization or deserialization problem.
//
// The book "Mastering ArduinoJson" contains a case study of a project that has
// a complex configuration with nested members.
// Contrary to this example, the project in the book uses the SPIFFS filesystem.
// Learn more at https://arduinojson.org/book/
// Use the coupon code TWENTY for a 20% discount â�¤â�¤â�¤â�¤â�¤
