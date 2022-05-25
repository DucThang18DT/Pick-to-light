#include "Task.h"

I2CProtocol Task::m_slave = I2CProtocol();

void _setSendData(){
    Serial.println("interrupt");
    if (*Task::getHandleSlave()->getDataSendToMaster() == CONF_DATA_FALSE){
        I2CProtocol::setConfirm(true);
        Task::getHandleSlave()->setDataSendToMaster(CONF_DATA_TRUE);
    }
}

Task::Task(){
    init();
}

Task::~Task(){

}

void Task::init(){
    //m_slave = new I2CProtocol();
    m_value = 0;
    m_slave.I2C_SlaveInit(I2C_SLAVE_ID);
    Serial.print("m_slave.dataSendToMaster = ");
    Serial.println(*m_slave.getDataSendToMaster());
    pinMode(SH_PIN, OUTPUT);
    pinMode(ST_PIN, OUTPUT);
    pinMode(DS_PIN, OUTPUT);
    m_led7seg = Led7SegMent();
    Serial.println("led 7seg init done");
    m_singleLed = SINGLE_LED;
    pinMode(m_singleLed, OUTPUT);
    digitalWrite(m_singleLed, LOW);
    m_confirmButton = CONFIRM_BUTTON;
    pinMode(m_confirmButton, INPUT);
    attachInterrupt(INTERRUPT_NUM, _setSendData, RISING);
}

int Task::receiveDataFromMaster(){
    Serial.println("receive data from master");
    // if (*(m_slave.getDataReceived()) == -1) return -1;
    return *(m_slave.getDataReceived());
    // m_slave.clearDataReceived();
    // return data;
} 

void Task::showNumber(int inNum){
    Serial.println("show Number");
    Serial.println(inNum);
    if (*(m_slave.getDataSendToMaster()) == CONF_DATA_TRUE){
        m_led7seg.turnOff();
        digitalWrite(m_singleLed, LOW);
        return;
    }
    //if (inNum == -1){
        m_led7seg.showNumber(inNum);
        digitalWrite(m_singleLed, HIGH);
    // }
    // else{
    //     m_value = inNum;
    // }
}

I2CProtocol* Task::getHandleSlave(){
    return &m_slave;
}