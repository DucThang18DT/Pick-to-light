// #define ARDUINOJSON_ENABLE_COMMENTS 1
// #include <WiFiClient.h>
#include <Arduino.h>
#include <myTask/myTask.h>

//unsigned long referenceTime;

void setup() {
  Serial.begin(9600);
  gWayInit();
  Serial.println("Hello");

  // readDataFromCloud();
  // Serial.printf("\nRunning on core: ");
  // Serial.println(xPortGetCoreID());
}

void loop() {
  readDataFromCloud();
  // if (listDevices.length() > 0){
  //   sendDataSendToCtler();
  // }
  // readDataFromCtler();
  memset(listConfirm, 0, MAX_LEN);
  listConfirm[0] = 1 & 0xFF;
  listConfirm[1] = 2 & 0xFF;
  listConfirm[2] = 4 & 0xFF;
  // listConfirm[3] = '\0';
  // Serial.print("\n-- init confirm list -- ");
  // Serial.println((int)listConfirm[1]);
  sendDataToCloud(listConfirm);
  delay(500);
}