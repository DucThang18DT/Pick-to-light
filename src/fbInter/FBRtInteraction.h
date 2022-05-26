#ifndef _FBRTINTERACTION_H_
#define _FBRTINTERACTION_H_

#include <Arduino.h>
// #include <DeviceItem.h>
#include <fbRealtimeDatabase/FBRtDatabase.h>

static String TOTAL = "/count";
static String ID_KEY = "MaSP2";
static String QUANTITY_KEY = "SoLuongMuonLay";
static String CONFIRM_KEY = "DaLay";
static String PATH = "/QuanLyGioHang";
static String KEY = "users";
static FBRtDatabase fbDatatbase = FBRtDatabase(HOST, AUTH, PATH, KEY);
static FirebaseData(fbStreamData);
static String listDevices = {};
static String listConfirm = {};

// void buildListObjects(std::vector<DeviceItem>* , String, String);
void buildListDevices(String* inList);
//void splitString(std::vector<String>*, String, char);
void streamCallback(StreamData);
void streamTimeOutCallback(bool);
//void fbRtStream(FirebaseData*, String);

#endif