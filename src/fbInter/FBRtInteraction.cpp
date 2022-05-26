#include "FBRtInteraction.h"

void buildListDevices(String* list){
  list->clear();
  int length = fbDatatbase.getInt(TOTAL);
  for (int i = 0; i < length; i++){
    int confirm = fbDatatbase.getInt(PATH + "/" + String(i) + "/" + CONFIRM_KEY);
    if (confirm == 0){
      list += (fbDatatbase.getInt(PATH + "/" + String(i) + "/" + ID_KEY) + '0');
      list += (fbDatatbase.getInt(PATH + "/" + String(i) + "/" + QUANTITY_KEY) + '0');
    }
  }
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
    buildListDevices(&listDevices);
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

