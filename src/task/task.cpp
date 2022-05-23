#include "task.h"


#define MAX_MODULE  5

Task::Task(){
    init();
}

Task::~Task(){

}

void Task::init(){
    //data = Vector<Data>();
    //data = Vector<Data>(storageArray);
    data.push_back(Data((char)I2C_SLAVE_ID, (char)2));
    data.push_back(Data((char)I2C_SLAVE_ID, (char)12));

    Serial.print("data = ");
    Serial.println(data.at(0).number);
    master = I2CProtocol();
    master.I2C_MasterInit();
    Serial.println("master init done");
    //recei = NRF24((const byte*)CHANNEL_READ_ADDRESS, (const byte*)CHANNEL_SEND_ADDRESS, CHANEL_PORT);
    //recei.init();
}

void Task::clearData(){
    unsigned int index = 0;
    while ((data.size() > 0) && (index < data.size())){
        if (data.at(index).confirm == true) data.remove(index);
        else ++index;
    }
}

int Task::checkID(char inID){
    for (unsigned  int index = 0; index < data.size(); index++)
        if (data.at(index).id == inID) return index;
    return -1;
}

bool Task::readDataFromGWay(){
    clearData();
    char* rcData = recei.readData();
    if (rcData[0] == '\0') return false;
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
    Serial.print("data size: ");
    Serial.println(data.size());
    for (unsigned int index = 0; index < data.size(); index++){
        master.I2C_SendDataToSlave(data.at(index).id, &data.at(index).number, 
        sizeof(data.at(index).number));
        Serial.println("\nsend data to  slave");
        Serial.print("id: ");
        Serial.println(data.at(index).id);
        Serial.print("data: ");
        Serial.println(data.at(index).number);
    }
}

void Task::readSttFromSlave(){
    char* confData = new char[I2C_CONF_LEN + 1];
    int confLen;
    for (unsigned int index = 0; index < data.size(); index++){
        confData = master.I2C_ReadDataFromSlave(data.at(index).id, &confLen);
        data.at(index).confirm = (confData[0] == CONF_DATA_TRUE)? true: false;
    }
    delete[] confData;
}

bool Task::sendSttToGway(){
    if (data.size() == 0) return false;
    char* _sendData = new char[data.size()*2];
    unsigned int index = 0;
    while ((index + 1) < data.size()*2){
        _sendData[index] = data.at(index).id;
        _sendData[++index] = data.at(index -1).id;
        ++index;
    }
    recei.sendData(_sendData);
    delete [] _sendData;
    return true;
}

Vector<Data>* Task::getDataRef(){
    return &data;
}

void Task::addValueToData(){
    getDataRef()->push_back(Data((char)I2C_SLAVE_ID, (char)12));
    getDataRef()->push_back(Data((char)I2C_SLAVE_ID, (char)1));
}