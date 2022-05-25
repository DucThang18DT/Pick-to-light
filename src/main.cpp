#include <Arduino.h>
#include "task/Task.h"

Task task = Task();

void setup() {
  Serial.begin(9600);
}

void loop() {
  //Wire.onRequest(_sendDataToMaster);
  task.showNumber(task.receiveDataFromMaster());
}