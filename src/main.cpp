#include "task/task.h"
Task task = Task();

void setup() {
    // Serial.begin(9600);
    task.addValueToData();
    task.sendDataToSlave();
    delay(200);
    task.sendDataToSlave();
}

void loop() {
    
    // Serial.print("size of test = ");
    // Serial.println(test.size());
    if (task.readDataFromGWay() == true){
        task.sendDataToSlave();
    }
    //Serial.println("Send to slave...");
    // task.sendDataToSlave();
}