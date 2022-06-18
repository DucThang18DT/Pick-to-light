#include <Arduino.h>
#include "task/Task.h"

Task task = Task();

void setup() {
  Serial.begin(9600);
  Serial.println("Begin");
}

void loop() {
  Wire.onRequest(_sendDataToMaster);
  task.showNumber(task.receiveDataFromMaster());
  // for (int i = 0; i < 99; i++){
  //   unsigned long refT = millis();
  //   Serial.println(i);
  //   while ((millis() - refT) < 500)
  //   {
  //     task.showNumber(i);
  //   }
  // }
}