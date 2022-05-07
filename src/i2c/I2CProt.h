#pragma once
#include <Arduino.h>
#include "Wire.h"
#include "port/port.h"

void _receiveData(int );
void _sendDataToMaster();

class I2CProtocol{
    public:
        I2CProtocol();
        ~I2CProtocol();

        void I2C_MasterInit();
        void I2C_SlaveInit(int inID);
        char* I2C_ReadDataFromSlave(uint8_t inID, int* outLength);
        bool I2C_SendDataToSlave(uint8_t inID, char* inData, int inLength);
        bool I2C_SendDataToMaster(char* inData, int inLength);

        static void setDataReceived(char* inData, int inLength);
        static char* getDataReceived();
        static void setDataSendToMaster(char* inData, int inLength);
        static char* getDataSendToMaster();
    protected:
    private:
        static char* m_DataReceived;
        static char* m_DataSend;
        uint8_t m_ID;
};