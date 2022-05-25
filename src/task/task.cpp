#include "task.h"


#define MAX_MODULE  5

Task::Task(){
    init();
}

Task::~Task(){

}

void Task::init(){
    updateToGWay = false;
    //data = Vector<Data>();
    // //data = Vector<Data>(storageArray);
    // Serial.print("data = ");
    // Serial.println(data.at(0).number);
    master = I2CProtocol();
    master.I2C_MasterInit();
    Serial.println("master init done");
    recei = NRF24((const byte*)CHANNEL_READ_ADDRESS, (const byte*)CHANNEL_SEND_ADDRESS, CHANEL_PORT);
}

void Task::clearData(){
    Serial.println("\nClear data");
    unsigned int index = 0;
    while ((data.size() > 0) && (index < data.size())){
        if (data.at(index).confirm == true) {
            Serial.print("remove index = ");
            Serial.println(index);
            data.remove(index);
            Serial.println(data.at(index).id);
        }
        else ++index;
    }
}

int Task::checkID(int inID){
    for (int index = 0; index < data.size(); index++)
        if (data.at(index).id == inID) return index;
    return -1;
}

bool Task::readDataFromGWay(){
    clearData();
    /*
    * Data format: 
    *   rcData = [id1], [num1], [id2], [num2],...,[idn], [numn], '\0', '\0'
    */
    char* rcData = recei.readData();
    if (rcData[0] == '\0') return false;
    int index = 0;
    while (rcData[index] != '\0' && rcData[index + 1] != '\0'){
        int isExist = checkID(rcData[index]);
        if (isExist == -1)
            data.push_back(Data(rcData[index], rcData[++index]));
        else{
            data.at(isExist).number = rcData[++index];
            data.at(isExist).confirm = false;
        }
        ++index;
    }
    delete []rcData;
    return true;
}

void Task::sendDataToSlave(){
    Serial.print("data size: ");
    Serial.println(data.size());
    for (unsigned int index = 0; index < data.size(); index++){
        if (data.at(index).confirm == false){
            master.I2C_SendDataToSlave(data.at(index).id, data.at(index).number);
            Serial.println("\nsend data to  slave");
            Serial.print("id: ");
            Serial.println(data.at(index).id);
            Serial.print("data: ");
            Serial.println(data.at(index).number);
        }
    }
}

void Task::readSttFromSlave(){
    //char* confData = new char[I2C_CONF_LEN + 1];
    //int confLen;
    for (unsigned int index = 0; index < data.size(); index++){
        //confData = master.I2C_ReadDataFromSlave(data.at(index).id, &confLen);
        //Serial.print("read data - id = ");
        //Serial.println(data.at(index).id);
        if (data.at(index).confirm == false){
            int confData = master.I2C_ReadDataFromSlave(data.at(index).id);
            data.at(index).confirm = (confData == CONF_DATA_TRUE)? true: false;
            updateToGWay = (confData == CONF_DATA_TRUE)? true: updateToGWay;
            Serial.print("confirm = ");
            Serial.println(data.at(index).confirm == true? "true": "false");
        }
        
        //Serial.print("\nread data - confirm = ");
        //Serial.println(data.at(index).confirm == true? "true": "false");
        //Serial.println(confData);
    }
    //delete[] confData;
}

bool Task::sendSttToGway(){
    if (data.size() == 0) return false;
    char* _sendData = new char[data.size()+1];
    memset(_sendData, 0, sizeof(_sendData));
    unsigned int index = 0;
    for (int idx = 0; idx < data.size(); idx++){
        if (data.at(idx).confirm == true){
            _sendData[index] = data.at(idx).id + '0';
            ++index;
        }
    }
    /*
    * Data format:
    *   _sendData = [id1], [id2], ..., [idn], '\0'
    */
    recei.sendData(_sendData);
    delete [] _sendData;
    return true;
}

Vector<Data>* Task::getDataRef(){
    return &data;
}

void Task::addValueToData(){
    while (getDataRef()->size() > 0){
        getDataRef()->pop_back();
    }
    getDataRef()->push_back(Data(I2C_SLAVE_ID, 12));
    getDataRef()->push_back(Data(I2C_SLAVE_ID1, 1));
}