#pragma once
#include <Arduino.h>
#include <SPI.h>
#include <RF24.h>
#include <nRF24L01.h>
#include <port/port.h>

const char CHANNEL_READ_ADDRESS[6] = "00002";
const char CHANNEL_SEND_ADDRESS[6] = "00001";

class NRF24{
    public:
        NRF24();
        NRF24(const char* inReadAddress, const char* inWriteAddress, int inPort);
        ~NRF24();

        void init();
        char* readData();
        void sendData(const char* inData);
    protected:
    private:
        // char* readAddress;
        // char* writeAddress;
        int port;
        RF24 radio;
};