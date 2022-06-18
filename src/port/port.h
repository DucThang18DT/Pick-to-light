#pragma once

/// Properties of I2C Protocol
#define I2C_SDA A4 // const
#define I2C_SCL A5 // const
#define I2C_BYTE_RFS    (sizeof(int)) // BYTES READ FROM SLAVE
#define I2C_BYTE_STS    (sizeof(int)) // BYTES SEND TO SLAVE
#define I2C_CONF_LEN    1
#define I2C_SLAVE_ID    0x01
#define I2C_SLAVE_ID1   0x02
/// Pin of led
#define LED     7

/// Properties of nRF24L01
// #define CE_PIN      27
// #define CSN_PIN     15
// #define NUM_PIPE    1
// #define CHANNEL_READ_ADDRESS "00001"
// #define CHANNEL_SEND_ADDRESS "00002"
#define CHANEL_PORT     90
#define TXT_MAX_LEN     100

/// Properties of Data
#define CONF_DATA_TRUE  127
#define CONF_DATA_FALSE 0