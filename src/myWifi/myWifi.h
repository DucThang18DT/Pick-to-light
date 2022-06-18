#ifndef _MYWIFI_H_
#define _MYWIFI_H_

#include <Arduino.h>
//#include <math.h>
#include <WiFi.h>
// #include <ESP8266WiFi.h>
#include <fbRealtimeDatabase/FBRtDatabase.h>
//#include <ArduinoJson.h>

// static String mySsid = "CLB PIONEER";
// static String myPass = "c121bkdn";
static String mySsid = "Thanh Tung";
static String myPass = "29032009";
bool connectWifi(const char*, const char*);
void disconnect();
bool changeWifi(const char*, const char*);
String localIP();
void wifiStreamTimeOutCallback(bool);
void wifiStreamCallback(StreamData);

#endif