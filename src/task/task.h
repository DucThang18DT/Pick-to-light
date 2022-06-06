#pragma once
#include <Arduino.h>
#include "i2c/I2CProt.h"
#include "data/data.h"
#include "nrf/nrf24.h"
#include <Vector.h>

#define MAX_SIZE    100
static Data storageArray[MAX_SIZE];
static Vector<Data> data(storageArray);

class Task{
    public:
        Task();
        ~Task();
        void init();

        bool readDataFromGWay();
        void sendDataToSlave();
        void readSttFromSlave();
        bool sendSttToGway();

        Vector<Data>* getDataRef();
        void addValueToData();

        void clearData();

        bool updateToGWay;
    protected:
        
        int checkID(int inID);
    private:
        I2CProtocol master;
        NRF24 recei;
};