#include "task/task.h"

Task task = Task();

void setup() {
    Serial.begin(9600);
    //task = Task();
    task.addValueToData();
    task.sendDataToSlave();

    // int storage_array[MAX_SIZE];
    // Vector<int> test(storage_array);
    // test.push_back(5);
    // Serial.print("size of test = ");
    // Serial.println(test.size());
    // Serial.println(test.at(0));
}

void loop() {
    // Serial.print("size of test = ");
    // Serial.println(test.size());
    // if (task.readDataFromGWay() == true){
    //     task.sendDataToSlave();
    // }
    Serial.println("Send to slave...");
    // task.sendDataToSlave();
    task.readSttFromSlave();
    delay(500);
    //task.sendSttToGway();
}