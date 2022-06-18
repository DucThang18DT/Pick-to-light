#include <Arduino.h>
#include <myTask/myTask.h>

//unsigned long referenceTime;
ListDevice list;

void setup() {
  // Serial.begin(9600);
  Serial.println("Hello");
  gWayInit();
  // Serial.printf("\nRunning on core: ");
  // Serial.println(xPortGetCoreID());
  
}

void loop() {
  readDataFromCloud(list.getListDevicesRef());
  Serial.print("\nSize list device: ");
  Serial.println(strlen(list.getListDevicesRef()));
  if (strlen(list.getListDevicesRef()) > 0){
    sendDataSendToCtler(list.getListDevicesRef());
  }
  readDataFromCtler(list.getListConfirmRef());
  Serial.print("\nSize list confirm: ");
  Serial.println(strlen(list.getListConfirmRef()));
  if (strlen(list.getListConfirmRef()) > 0){
    sendDataToCloud(list.getListConfirmRef());
  }
  delay(500);
}