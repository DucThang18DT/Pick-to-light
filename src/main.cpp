#include <Arduino.h>
#include "task/task.h"

// static Task* task = new Task();

void setup() {
    Serial.begin(9600);
    Serial.print("Hello");
    taskInit();
    // addValueToData();
    // sendDataToSlave();
    delay(200);
    // sendDataToSlave();
}

void loop() {
    
    // Serial.print("size of test = ");
    // Serial.println(test.size());

    if (readDataFromGWay() == true){
        sendDataToSlave();
    }
    // Serial.println("Hello");
    // delay(500);
    // for (int i = 0; i< getDataRef()->size(); i++){
    //     getDataRef()->at(i).confirm = true;
    //     Serial.print("\ndata confirm = ");
    //     Serial.print(getDataRef()->at(i).confirm? 1:0);
    // }
    readSttFromSlave();
    sendSttToGway();
    delay(500);

    //Serial.println("Send to slave...");
    // task.sendDataToSlave();
}