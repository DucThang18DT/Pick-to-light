#pragma once

/// Properties of I2C Protocol
#define I2C_SDA A4 // const
#define I2C_SCL A5 // const
#define I2C_BYTE_RFS    2 // BYTES READ FROM SLAVE
#define I2C_BYTE_STS    2 // BYTES SEND TO SLAVE
#define I2C_CONF_LEN    1
#define I2C_SLAVE_ID    0x01

/// Properties of Module Lamp
/// Pin of led
#define SINGLE_LED     7
/// Pin of Conform Button
#define CONFIRM_BUTTON  2
#define INTERRUPT_NUM   0

/// Pin of led 7-seg
#define LED_7SEG_1  8
#define LED_7SEG_2  9
#define SH_PIN      10
#define ST_PIN      11
#define DS_PIN      12

/// Properties of Data
#define CONF_DATA_TRUE  ((char)0X88)
#define CONF_DATA_FALSE ((char)0X08)