#include "task.h"


#define MAX_MODULE  5

// Task::Task(){
//     init();
// }

// Task::~Task(){

// }

void taskInit(){
    Serial.begin(9600);
    Serial.println("init");
    updateToGWay = false;
    //memset(data, 0, sizeof(data));
    clearData();
    delay(100);
    master = I2CProtocol();
    master.I2C_MasterInit();
    Serial.println("master init done");
    recei = NRF24(/*(const byte*)CHANNEL_READ_ADDRESS, (const byte*)CHANNEL_SEND_ADDRESS,*/ CHANEL_PORT);
}

void clearData(){
    Serial.println("\nClear data");
    //memset(data, 0, sizeof(data));
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

int checkID(char inID){
    for (int index = 0; index < data.size(); index++)
        if (data.at(index).id == inID) return index;
    return -1;
}

bool readDataFromGWay(){
    Serial.println("\n--- Read data from gate way ---");
    /*
    * Data format: 
    *   rcData = [id1], [num1], [id2], [num2],...,[idn], [numn], '\0', '\0'
    */
    char* rcData = recei.readData();
    Serial.print("\nread size = ");
    Serial.println(strlen(rcData));
    if (strcmp(rcData, "OK") == 0){
        clearData();
        return false;
    }
    if (strlen(rcData) == 0) return false;
    if (data.size() > 0) return false;
    Serial.print("\ndata = ");
    Serial.println(rcData);
    int index = 0;
    while (((rcData[index] != 0) && (rcData[index + 1] != 0)) & (index < strlen(rcData))){
        int isExist = checkID(rcData[index]);
        if (isExist == -1){
            data.push_back(Data(rcData[index], rcData[index + 1]));
            Serial.print("\nID: ");
            Serial.println((int)data.at(data.size() - 1).id);
            Serial.print("\ndata: ");
            Serial.println((int)data.at(data.size() - 1).number);
        }
        else{
            data.at(isExist).number = rcData[index + 1];
            data.at(isExist).confirm = false;
            Serial.print("\ndata: ");
            Serial.println((int)data.at(isExist).number);
        }
        index += 2;
    }
    Serial.println("\n--- End Read data from gate way ---");
    // delete []rcData;
    // rcData = nullptr;
    delay(20);
    return true;
}

void sendDataToSlave(){
    Serial.println("\n--- Send data to slave ---");
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
    Serial.println("\n--- End Read data from gate way ---");
}

void readSttFromSlave(){
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
}

bool sendSttToGway(){
    Serial.println("\nSend data to gate way");
    if (data.size() == 0) return false;
    char* _sendData = new char[data.size()+1];
    memset(_sendData, 0, data.size()+1);
    unsigned int index = 0;
    for (int idx = 0; idx < data.size(); idx++){
        if (data.at(idx).confirm == true){
            _sendData[index] = data.at(idx).id;
            Serial.print("\nid = ");
            Serial.println(_sendData[index]);
            _sendData[index + 1] = 0;
            ++index;
        }
    }
    /*
    * Data format:
    *   _sendData = [id1], [id2], ..., [idn], '\0'
    */
    if (strlen(_sendData) > 0){
        recei.sendData(_sendData);
        Serial.print("\nSend to gateway success");
        delete [] _sendData;
        return true;
    }
    Serial.print("\nSend to gateway failed");
    delete [] _sendData;
    return false;
}

Vector<Data>* getDataRef(){
    return &data;
}

void addValueToData(){
    // while (getDataRef()->size() > 0){
    //     getDataRef()->pop_back();
    // }
    // getDataRef()->push_back(Data(I2C_SLAVE_ID, 12));
    // getDataRef()->push_back(Data(I2C_SLAVE_ID1, 1));
}