#include <Arduino.h>
#include "task/Task.h"

Task task;

void setup() {
  Serial.begin(9600);
  task = Task();
}

void loop() {
  task.showNumber(task.receiveDataFromMaster());
}