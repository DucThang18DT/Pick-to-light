#pragma once
#include "i2c/I2CProt.h"
#include "data/data.h"
#include <Vector.h>
#include "nrf/nrf24.h"

Vector<Data> data = {};
I2CProtocol master;
NRF24 recei;

void Init();
bool receiveDataFromGWay(uint8_t* inData);
void sendDataToSlave();