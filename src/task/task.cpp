#include "task.h"

Task::Task(){
    init();
}

Task::~Task(){

}

void Task::init(){
    data = {};
    master = I2CProtocol();
    master.I2C_MasterInit();
    recei = NRF24((const byte*)CHANNEL_READ_ADDRESS, (const byte*)CHANNEL_SEND_ADDRESS, CHANEL_PORT);
    recei.init();
}

void Task::clearData(){
    int index = 0;
    while ((data.size() > 0) && (index < data.size())){
        if (data.at(index).confirm == true) data.remove(index);
        else ++index;
    }
}

int Task::checkID(char inID){
    for (int index = 0; index < data.size(); index++)
        if (data.at(index).id == inID) return index;
    return -1;
}

bool Task::readDataFromGWay(){
    clearData();
    char* rcData = recei.readData();
    if (rcData[0] = '\0') return false;
    int index = 0;
    while (rcData[index] != '\0' && rcData[index + 1] != '\0'){
        int isExist = checkID(rcData[index]);
        if (isExist == -1)
            data.push_back(Data(rcData[index], rcData[++index]));
        else
            data.at(isExist).number = rcData[++index];
        ++index;
    }
    delete []rcData;
    return true;
}

void Task::sendDataToSlave(){
    for (int index = 0; index < data.size(); index++){
        master.I2C_SendDataToSlave(data.at(index).id, &data.at(index).number, 
        sizeof(data.at(index).number));
    }
}

void Task::readSttFromSlave(){
    char* confData = new char[I2C_CONF_LEN + 1];
    int confLen;
    for (int index = 0; index < data.size(); index++){
        confData = master.I2C_ReadDataFromSlave(data.at(index).id, &confLen);
        data.at(index).confirm = (confData[0] == CONF_DATA_TRUE)? true: false;
    }
    delete[] confData;
}

bool Task::sendSttToGway(){
    if (data.size() == 0) return false;
    char* _sendData = new char[data.size()*2];
    int index = 0;
    while ((index + 1) < data.size()*2){
        _sendData[index] = data.at(index).id;
        _sendData[++index] = data.at(index -1).id;
        ++index;
    }
    recei.sendData(_sendData);
    delete [] _sendData;
    return true;
}