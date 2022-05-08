#pragma once
#include "i2c/I2CProt.h"
#include "data/data.h"
#include <Vector.h>
#include "nrf/nrf24.h"

class Task{
    public:
        Task();
        ~Task();
        void init();

        bool readDataFromGWay();
        void sendDataToSlave();
        void readSttFromSlave();
        bool sendSttToGway();
    protected:
        void clearData();
        int checkID(char inID);
    private:
        Vector<Data> data;
        I2CProtocol master;
        NRF24 recei;
};


