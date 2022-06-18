#pragma once
#include <Arduino.h>
#include "i2c/I2CProt.h"
#include "data/data.h"
#include "nrf/nrf24.h"
#include <Vector.h>

#define MAX_SIZE    100
static Data storageArray[MAX_SIZE];
static Vector<Data> data(storageArray);
// static Data data[MAX_SIZE];

// class Task{
//     public:
        // Task();
        // ~Task();
        void taskInit();
        bool readDataFromGWay();
        void sendDataToSlave();
        void readSttFromSlave();
        bool sendSttToGway();

        // Data* getDataRef();
        Vector<Data>* getDataRef();
        void addValueToData();

        void clearData();

        static bool updateToGWay;
//    protected:
        
        int checkID(char inID);
//    private:
        static I2CProtocol master;
        static NRF24 recei;
//};