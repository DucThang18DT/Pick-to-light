#pragma once
#include <Arduino.h>
#include <port/port.h>

static const uint8_t Num_Anode[] = {0xFC,0x60,0xDA,0xF2,0x66,0xB6,0xBE,0xE0,0xFE,0xF6};

class Led7SegMent{
    public:
        Led7SegMent();
        ~Led7SegMent();
        void showNumber(uint8_t inNum);
        void turnOff();
    protected:
    private:
};