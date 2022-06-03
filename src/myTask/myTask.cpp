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

// void sendDataSendToCtler(){
//   //buildListDevices(&listDevices);
//   rf24.sendData(listDevices.c_str());
// }

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
  // listConfirm.clear();
  //fbDatatbase.sendData("/Test/ok", 1, Mode::set);
}

void readDataFromCloud(){
  buildListDevices(listDevices);
  Serial.print("\nList device: ");
  Serial.println(listDevices);
}

// void readDataFromCtler(){
//   char* data = rf24.readData();
//   if (strlen(data) > 0){
//     listConfirm = String(data);
//   }
// }
