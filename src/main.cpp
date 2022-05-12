#include <Arduino.h>
#include "task/Task.h"

Task task;

void setup() {
    task = Task();
}

void loop() {
  task.showNumber(task.receiveDataFromMaster());
} 