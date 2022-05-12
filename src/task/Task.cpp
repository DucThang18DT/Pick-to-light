#include "Task.h"

void _setSendData(){
    Task::getHandleSlave()->setDataSendToMaster(CONF_DATA_TRUE);
}

Task::Task(){
    init();
}

Task::~Task(){

}

void Task::init(){
    m_slave = I2CProtocol();
    m_slave.I2C_SlaveInit(I2C_SLAVE_ID);
    pinMode(SH_PIN, OUTPUT);
    pinMode(ST_PIN, OUTPUT);
    pinMode(DS_PIN, OUTPUT);
    m_led7seg = Led7SegMent();
    m_singleLed = SINGLE_LED;
    pinMode(m_singleLed, OUTPUT);
    digitalWrite(m_singleLed, LOW);

    m_confirmButton = CONFIRM_BUTTON;
    pinMode(m_confirmButton, INPUT);
    attachInterrupt(INTERRUPT_NUM, _setSendData, RISING);
}

int Task::receiveDataFromMaster(){
    if (m_slave.getDataReceived() == nullptr) return -1;
    int data = m_slave.getDataReceived()[0];
    m_slave.clearDataReceived();
    return data;
} 

void Task::showNumber(int inNum){
    if (inNum == -1){
        m_led7seg.turnOff();
        digitalWrite(m_singleLed, LOW);
    }
    else{
        m_led7seg.showNumber(inNum);
        digitalWrite(m_singleLed, HIGH);
    }
}

I2CProtocol* Task::getHandleSlave(){
    return &m_slave;
}