#pragma once

/// Properties of I2C Protocol
#define I2C_SDA A4 // const
#define I2C_SCL A5 // const
#define I2C_BYTE_RFS    2 // BYTES READ FROM SLAVE
#define I2C_BYTE_STS    2 // BYTES SEND TO SLAVE
/// Pin of led
#define LED     7

/// Properties of nRF24L01
#define CE_PIN      8
#define CSN_PIN     9
#define NUM_PIPE    1
#define CHANEL_ADDRESS "00001"
#define CHANEL_PORT     80
#define TXT_MAX_LEN     100