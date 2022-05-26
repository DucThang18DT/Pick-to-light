#ifndef _FBRTDATABASE_H_
#define _FBRTDATABASE_H_

#include <Arduino.h>
#include <FirebaseESP32.h>

static String HOST = "quanlysanpham2-e7a54-default-rtdb.asia-southeast1.firebasedatabase.app/";
static String AUTH = "2XvGfHe8s7gh72U6Tb6GZa7GMJIUienwZLlOjHd9";

enum Mode{set, push, update};

class FBRtDatabase
{
private:
    String _firebaseHost;
    String _firebaseAuth;
    String _dataPath;
    String _keyData;
    FirebaseData _firebaseData;
    
public:
    FBRtDatabase(){}
    FBRtDatabase(const FBRtDatabase&){}
    FBRtDatabase(String, String, String, String);
    ~FBRtDatabase(){}

    // setter
    void setFirebaseInfor(String, String);
    void setHost(String);
    void setAuth(String);
    void setDataPath(String);
    void setKeyData(String);
    void connect();

    // getter
    String dataPath(){return _dataPath;}
    String keyData(){return _keyData;}

    void sendData(String, String, Mode);
    void sendData(String, int , Mode);
    String getData(String);
    int getInt(String);
};

#endif