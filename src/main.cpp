// #define ARDUINOJSON_ENABLE_COMMENTS 1
// #include <WiFiClient.h>

#include <myTask/myTask.h>

unsigned long referenceTime;

void setup() {
  Serial.begin(115200);
  init();

  readDataFromCloud();
  Serial.printf("\nRunning on core: ");
  Serial.println(xPortGetCoreID());
}

void loop() {
  readDataFromCloud();
  if (listDevices.length() > 0){
    sendDataSendToCtler();
  }
  readDataFromCtler();
  sendDataToCloud();
  delay(100);
}