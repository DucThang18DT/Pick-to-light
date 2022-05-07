#include "task.h"

void Init(){
    master = I2CProtocol();
    master.I2C_MasterInit();
    recei = NRF24((const byte*)CHANEL_ADDRESS, CHANEL_PORT);
    recei.init();
}

bool receiveDataFromGWay(uint8_t* inData){
    while (data.size() > 0) data.pop_back();
    char* rcData = recei.readData();
    if (rcData[0] = '\0') return false;
    int index = 0;
    while (rcData[index] != '\0' && rcData[index + 1] != '\0'){
        data.push_back(Data(rcData[index], rcData[++index]));
        ++index;
    }
    delete []rcData;
    return true;
}

void sendDataToSlave(){
    for (int index = 0; index < data.size(); index++){
        master.I2C_SendDataToSlave(data.at(index).id, &data.at(index).number, 
        sizeof(data.at(index).number));
    }
}