#include "task/task.h"

Task task = Task();

void setup() {
    task.init();
}

void loop() {
    if (task.readDataFromGWay() == true){
        task.sendDataToSlave();
    }
    task.readSttFromSlave();
    task.sendSttToGway();
}