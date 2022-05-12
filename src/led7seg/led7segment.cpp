#include "led7segment.h"

Led7SegMent::Led7SegMent(){
    turnOff();
}

Led7SegMent::~Led7SegMent(){

}

void Led7SegMent::turnOff(){
    digitalWrite(LED_7SEG_1, LOW);
    digitalWrite(LED_7SEG_2, LOW);
}

void Led7SegMent::showNumber(uint8_t inNum){
    shiftOut(DS_PIN, SH_PIN, LSBFIRST, Num_Anode[inNum/10]);
    delay(2);
    digitalWrite(LED_7SEG_1, LOW);
    digitalWrite(LED_7SEG_2, HIGH);
    digitalWrite(ST_PIN, HIGH);
    digitalWrite(ST_PIN, LOW);
    delay(10);
    shiftOut(DS_PIN, SH_PIN, LSBFIRST, Num_Anode[inNum%10]);
    delay(2);
    digitalWrite(LED_7SEG_1, HIGH);
    digitalWrite(LED_7SEG_2, LOW);
    digitalWrite(ST_PIN, HIGH);
    digitalWrite(ST_PIN, LOW);
    delay(10);
}