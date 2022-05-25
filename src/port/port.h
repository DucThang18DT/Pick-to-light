#pragma once

/// Properties of I2C Protocol
#define I2C_SDA A4 // const
#define I2C_SCL A5 // const
#define I2C_CONFIRM     12
#define I2C_BYTE_RFS    (sizeof(int)) // BYTES READ FROM SLAVE
#define I2C_BYTE_STS    (sizeof(int)) // BYTES SEND TO SLAVE
#define I2C_CONF_LEN    1
#define I2C_SLAVE_ID    0x01
#define I2C_SLAVE_ID1    0x02

/// Properties of Module Lamp
/// Pin of led
#define SINGLE_LED     7
/// Pin of Conform Button
#define CONFIRM_BUTTON  2
#define INTERRUPT_NUM   0

/// Pin of led 7-seg
#define LED_7SEG_1  9
#define LED_7SEG_2  8
#define SH_PIN      6
#define ST_PIN      4
#define DS_PIN      5

/// Properties of Data
#define CONF_DATA_TRUE  127
#define CONF_DATA_FALSE 0