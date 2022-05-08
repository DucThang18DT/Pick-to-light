#pragma once
#include <Arduino.h>
#include <SPI.h>
#include <RF24.h>
#include <nRF24L01.h>
#include "port/port.h"

class NRF24{
    public:
        NRF24();
        NRF24(const byte* inReadAddress, const byte* inWriteAddress, int inPort);
        ~NRF24();

        void init();
        char* readData();
        void sendData(char* inData);
    protected:
    private:
        const byte* readAddress;
        const byte* writeAddress;
        int port;
        RF24 radio;
};