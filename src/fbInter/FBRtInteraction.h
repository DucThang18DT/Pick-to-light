#ifndef _FBRTINTERACTION_H_
#define _FBRTINTERACTION_H_

#include <Arduino.h>
// #include <DeviceItem.h>
#include <fbRealtimeDatabase/FBRtDatabase.h>

#define MAX_LEN     160

static String TOTAL = "/Count2/cnt2";
static String ID_KEY = "MaSP2";
static String QUANTITY_KEY = "SoLuongMuonLay";
static String CONFIRM_KEY = "DaLay";
static String PATH = "/QuanLyGioHang";
static String KEY = "users";
static FBRtDatabase fbDatatbase = FBRtDatabase(HOST, AUTH, PATH, KEY);
static FirebaseData(fbStreamData);
// static String listDevices = {};

class ListDevice{
    public:
        ListDevice();
        ~ListDevice();
        char* getListDevicesRef();
        char* getListConfirmRef();
    private:
        char listDevices[MAX_LEN];
        char listConfirm[MAX_LEN];
};

// void buildListObjects(std::vector<DeviceItem>* , String, String);
void buildListDevices(char* inList);
//void splitString(std::vector<String>*, String, char);
void streamCallback(StreamData);
void streamTimeOutCallback(bool);
//void fbRtStream(FirebaseData*, String);

#endif