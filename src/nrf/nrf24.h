#pragma once
#include <Arduino.h>
#include <SPI.h>
#include <RF24.h>
#include <nRF24L01.h>
#include "port/port.h"

class NRF24{
    public:
        NRF24(const byte* inAddress, int inPort);
        ~NRF24();

        void init();
        char* readData();
    protected:
    private:
        const byte* address;
        int port;
        RF24 radio;
};