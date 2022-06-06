#include "myTask.h"

void gWayInit(){
  connectWifi(mySsid.c_str(), myPass.c_str());
  fbDatatbase.connect();
  // rf24.init();

  if (Firebase.beginStream(fbStreamData, "/")){
    Serial.println("(main) begin Stream");
    Firebase.setStreamCallback(fbStreamData, streamCallback, streamTimeOutCallback);
    Serial.println("(main) set Stream callback: OK");
  }
  else{
    Serial.println("(main) Can not begin Stream");
  } 
}

void sendDataToCloud(char* list){
  Serial.println("\n--- Send to Cloud ---");
  int length = fbDatatbase.getInt(TOTAL);
  Serial.print("\nTotal: ");
  Serial.println(length);
  int len = strlen(list);
  Serial.print("\nTotal Confirm: ");
  Serial.println(len);
  for (int index = 0; index < len; index++){
    for (int idx = 0; idx < length; idx++){
      int _id = fbDatatbase.getInt(PATH + "/" + String(idx) + "/" + ID_KEY);
      Serial.print("\nGet ID: ");
      Serial.println(_id);
      int conf = list[index] & 0xFF;
      Serial.print("\nconfirm ID: ");
      Serial.println(conf);
      if (_id == conf){
        fbDatatbase.sendData(PATH + "/" + String(idx) + "/" + CONFIRM_KEY, 1, Mode::set);
        Serial.print("\nSet conf for ID = ");
        Serial.println(_id);
        break;
      }
    }
  }
  memset(listConfirm, 0, MAX_LEN);
  Serial.println("\n--- End send to cloud ---");
}

void readDataFromCloud(){
  buildListDevices(listDevices);
  Serial.print("\nList device: ");
  Serial.println(listDevices);
}

void sendDataSendToCtler(){
  Serial.println("\n--- Send data to ctler");
  // rf24.sendData("Test list");
  rf24.sendData(listDevices);
  Serial.println("--- End Send data to ctler");
}

void readDataFromCtler(char* list){
  Serial.println("\n--- Read data from ctler");
  char* data = rf24.readData();
  if (strlen(data) > 0){
    Serial.print("\nRead from ctler: ");
    Serial.println(data);
    Serial.print("\nLength data = ");
    Serial.println(strlen(data));
    strcpy(list, data);
    Serial.println(strlen(list));
  }
  Serial.println("\n--- End Read data from ctler");
}
