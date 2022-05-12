#pragma once
#include "i2c/I2CProt.h"
#include "led7seg/led7segment.h"

void _setSendData();

class Task{
    public:
        Task();
        ~Task();
        void init();
        int receiveDataFromMaster();
        void showNumber(int inNum);
        static I2CProtocol* getHandleSlave();
    protected:
    private:
        static I2CProtocol m_slave;
        Led7SegMent m_led7seg;
        int m_singleLed;
        int m_confirmButton;
};