#include "myTask.h"

void init(){
  connectWifi(mySsid.c_str(), myPass.c_str());
  fbDatatbase.connect();
  // rf24.init();

  Firebase.beginStream(fbStreamData, "/");
  Serial.println("(main) begin Stream");
  Firebase.setStreamCallback(fbStreamData, streamCallback, streamTimeOutCallback);
  Serial.println("(main) set Stream callback: OK");

}

void sendDataSendToCtler(){
  //buildListDevices(&listDevices);
  rf24.sendData(listDevices.c_str());
}

void sendDataToCloud(){
  int length = fbDatatbase.getInt(TOTAL);
  for (int index = 0; index < listConfirm.length(); index++){
    for (int idx = 0; idx < length; idx++){
      int _id = fbDatatbase.getInt(PATH + "/" + String(idx) + "/" + ID_KEY);
      if (_id == (int)listConfirm[index]){
        fbDatatbase.sendData(PATH + "/" + String(idx) + "/" + CONFIRM_KEY, 1, Mode::set);
        break;
      }
    }
  }
  listConfirm.clear();
}

void readDataFromCloud(){
  buildListDevices(&listDevices);
}

void readDataFromCtler(){
  char* data = rf24.readData();
  if (strlen(data) > 0){
    listConfirm = String(data);
  }
}