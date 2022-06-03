#include "FBRtInteraction.h"


void buildListDevices(char* list){
  Serial.println("\n--build list device---");
  // list->clear();
  memset(list, 0, MAX_LEN);
  int length = fbDatatbase.getInt(TOTAL);
  Serial.print("\nTotal: ");
  Serial.println(length);
  for (int i = 0; i < 2*length; i += 2){
    int confirm = fbDatatbase.getInt(PATH + "/" + String(i/2) + "/" + CONFIRM_KEY);
    Serial.print("\nConfirm: ");
    Serial.println(confirm);
    if (confirm == 0){
      int tempValue = fbDatatbase.getInt(PATH + "/" + String(i/2) + "/" + ID_KEY);
      list[i] = tempValue & 0xFF;
      tempValue = fbDatatbase.getInt(PATH + "/" + String(i/2) + "/" + QUANTITY_KEY);
      list[i+1] = tempValue & 0xFF;
      list[i+2] = 0;
      Serial.print("ID = ");
      Serial.println((int)list[i]);
      Serial.print("Num = ");
      Serial.println((int)list[i+1]);
      // Serial.print("\nList: ");
      // Serial.println(*list);
    }
  }
  Serial.println("\n--End build list device---");
}

// void splitString(std::vector<String> *listKeys,String str = "", char symbol = '/'){
//   // Serial.println("\n(split String) List key:");
//   while (str.length() > 0){
//     if (str.charAt(0) == '/') str = str.substring(1);
//     listKeys->push_back(str.substring(0, str.indexOf('/')));
//     // Serial.println(listKeys->at(listKeys->size()-1));
//     str = str.substring(str.indexOf('/'));
//   }
// }

void streamCallback(StreamData data){
  Serial.printf("\nstream path: %s\nevent path: %s\ndata type: %s\nevent type: %s\n\n",
                data.streamPath().c_str(),
                data.dataPath().c_str(),
                data.dataType().c_str(),
                data.eventType().c_str());
    Serial.println();
    //String path = data.dataPath();
    buildListDevices(listDevices);
    // if (path == TOTAL) buildListDevices(&listDevices);
    // else if (path.length()>1){
    //   std::vector<String> listKeys;
    //   splitString(&listKeys, path, '/');
    //   int positionOfDevice = listKeys.at(1).toInt();

    //   String dataRcv = fbDatatbase.getData(PATH + "/" + listKeys.at(0) + "/" + listKeys.at(1));
      
    //   DeviceItem::updateObject(&listDevices, positionOfDevice, dataRcv);
    // }
}

void streamTimeOutCallback(bool timeOut){
  Serial.println("timeOut founction");
  if (timeOut)
    Serial.println("stream timeout, resuming...\n");
}

// void fbRtStream(FirebaseData *_fbStreamData, String path = "/"){
//     Firebase.beginStream(*_fbStreamData, path);
//     Firebase.setStreamCallback(*_fbStreamData, streamCallback, streamTimeOutCallback);
// }

