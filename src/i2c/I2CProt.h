#pragma once
#include <Arduino.h>
#include "Wire.h"
#include "..\port\port.h"

void _receiveData(int );
void _sendDataToMaster();

class I2CProtocol{
    public:
        I2CProtocol();
        ~I2CProtocol();

        void I2C_MasterInit();
        void I2C_SlaveInit(int inID);
        int I2C_ReadDataFromSlave(int inID);
        bool I2C_SendDataToSlave(int inID, int inData);
        bool I2C_SendDataToMaster(int inData);

        static void clearDataReceived();
        static void setDataReceived(int inData);
        static int* getDataReceived();
        static void clearDataSendToMaster();
        static void setDataSendToMaster(int inData);
        static void setDataSendToMaster(int inData);
        static int* getDataSendToMaster();
    protected:
    private:
        static int m_DataReceived;
        static int m_DataSend;
        int m_ID;
};