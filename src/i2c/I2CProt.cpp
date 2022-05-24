#include "I2CProt.h"

// int* I2CProtocol::m_DataReceived = new int[I2C_BYTE_RFS];
// int* I2CProtocol::m_DataSend = new int[I2C_BYTE_STS];
int I2CProtocol::m_DataReceived = -1;
int I2CProtocol::m_DataSend = -1;

I2CProtocol::I2CProtocol(){
    
}

I2CProtocol::~I2CProtocol(){
    // clearDataReceived();
    // clearDataSendToMaster();
}

void _receiveData(int ){
    //int* data = new int[I2C_BYTE_STS];
    //int index = 0;
    while (Wire.available() /*&& (index < I2C_BYTE_STS)*/){
        I2CProtocol::setDataReceived(Wire.read());
        // data[index] = Wire.read();
        // ++index;
    }
    // I2CProtocol::setDataReceived(data);
}

void _sendDataToMaster(){
    Serial.print("send to master: ");
    Serial.println(*(I2CProtocol::getDataSendToMaster()));
    Wire.write(*(I2CProtocol::getDataSendToMaster()));
}

void I2CProtocol::I2C_MasterInit(){
    Wire.begin();
}

void I2CProtocol::I2C_SlaveInit(int inID){
    m_ID = inID;
    Wire.begin(m_ID);
    Wire.onRequest(_sendDataToMaster);
    Wire.onReceive(_receiveData);
    Serial.println("slave init done");
}

bool I2CProtocol::I2C_SendDataToSlave(int inID, int inData){
    Wire.beginTransmission(inID);
    //for (int index = 0; index < inLength; index++){
        Wire.write(inData);
    //}
    Wire.endTransmission();
    return true;
}

int I2CProtocol::I2C_ReadDataFromSlave(int inID){
    // int outData;
    Wire.requestFrom(inID, I2C_BYTE_RFS);
    //*outLength = Wire.available();
    // outData = new int[*outLength];
    //for (int index = 0; index < *outLength; index++){
        // outData = Wire.read();
    //}
    return Wire.read();
}

void I2CProtocol::setDataReceived(int inData){
    // if (m_DataReceived != nullptr) delete [] m_DataReceived;
    // m_DataReceived = new int[inLength + 1];
    m_DataReceived = inData;
    //strcpy(m_DataReceived, inData);
}

int* I2CProtocol::getDataReceived(){
    return &m_DataReceived;
}

// void I2CProtocol::setDataSendToMaster(int inData){
//     // if (m_DataSend != nullptr) delete[] m_DataSend;
//     // m_DataSend = new int[I2C_BYTE_STS];
//     m_DataSend = inData;
// }

void I2CProtocol::setDataSendToMaster(int inData){
    // if (m_DataSend != nullptr) delete[] m_DataSend;
    // m_DataSend = new int[inLength + 1];
    m_DataSend = inData;
    // strcpy(m_DataSend, inData);
}

int* I2CProtocol::getDataSendToMaster(){
    return &m_DataSend;
}

void I2CProtocol::clearDataReceived(){
    // if (m_DataReceived != nullptr){
    //     delete [] m_DataReceived;
        m_DataReceived = -1;
    // } 
}

void I2CProtocol::clearDataSendToMaster(){
    // if (m_DataSend != nullptr){
    //     delete [] m_DataSend;
        m_DataSend = -1;
    // }
}