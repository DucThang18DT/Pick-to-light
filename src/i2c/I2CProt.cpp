#include "I2CProt.h"

I2CProtocol::I2CProtocol(){
    
}

I2CProtocol::~I2CProtocol(){
    if (m_DataSend != nullptr){
        delete [] m_DataSend;
        m_DataSend = nullptr;
    }
    if (m_DataReceived != nullptr){
        delete [] m_DataReceived;
        m_DataReceived = nullptr;
    }
}

void _receiveData(int ){
    char* data = new char[I2C_BYTE_STS];
    int index = 0;
    while (Wire.available() && (index < I2C_BYTE_STS)){
        data[index] = Wire.read();
        ++index;
    }
    I2CProtocol::setDataReceived(data, index + 1);
}

void _sendDataToMaster(){
    Wire.write(I2CProtocol::getDataSendToMaster());
}

void I2CProtocol::I2C_MasterInit(){
    Wire.begin();
}

void I2CProtocol::I2C_SlaveInit(int inID){
    m_ID = inID;
    Wire.begin(m_ID);
    // Wire.onReceive(_receiveData);
    Wire.onReceive(_receiveData);
    Wire.onRequest(_sendDataToMaster);
}

bool I2CProtocol::I2C_SendDataToSlave(uint8_t inID, char* inData, int inLength){
    Wire.beginTransmission(inID);
    for (int index = 0; index < inLength; index++){
        Wire.write(inData[index]);
    }
    Wire.endTransmission();
    return true;
}

char* I2CProtocol::I2C_ReadDataFromSlave(uint8_t inID, int* outLength){
    char* outData;
    Wire.requestFrom(inID, I2C_BYTE_RFS);
    *outLength = Wire.available();
    outData = new char[*outLength];
    for (int index = 0; index < *outLength; index++){
        outData[index] = Wire.read();
    }
    return outData;
}

void I2CProtocol::setDataReceived(char* inData, int inLength){
    if (m_DataReceived != nullptr) delete [] m_DataReceived;
    m_DataReceived = new char[inLength + 1];
    strcpy(m_DataReceived, inData);
}

char* I2CProtocol::getDataReceived(){
    return m_DataReceived;
}

void I2CProtocol::setDataSendToMaster(char* inData, int inLength){
    if (m_DataSend != nullptr) delete[] m_DataSend;
    m_DataSend = new char[inLength + 1];
    strcpy(m_DataSend, inData);
}

char* I2CProtocol::getDataSendToMaster(){
    return m_DataSend;
}