#ifndef __AHT20_H__
#define __AHT20_H__

#include "main.h"

#define AHT20_I2C_SLAVE_ADDR 0x38 << 1
#define AHT20_WAIT_TIME 100

#define AHT20_CRC8_POLYNOMIAL 0x31
#define AHT20_CRC8_INITIAL_VALUE 0xFF

#define AHT20_CMD_LENGTH 3
#define AHT20_DATA_LENGTH 7

typedef uint8_t (AHT20_CMD)[AHT20_CMD_LENGTH];
typedef uint8_t (AHT20_DATA)[AHT20_DATA_LENGTH];

typedef enum
{
    AHT20_OK = 0x00U,
    AHT20_ERROR = 0x01U,
    AHT20_BUSY = 0x02U,
    AHT20_BAD_CRC = 0x03U
} AHT20_ResponseTypeDef;

// Data handling

AHT20_ResponseTypeDef AHT20_Init(void);
AHT20_ResponseTypeDef AHT20_StartMeasurement(void);
AHT20_ResponseTypeDef AHT20_ParseData(float *temp, float *humidity);

// Hardware interaction

AHT20_ResponseTypeDef AHT20_WriteCMD(const AHT20_CMD *);
AHT20_ResponseTypeDef AHT20_ReadData(AHT20_DATA *);
AHT20_ResponseTypeDef AHT20_CheckCRC(AHT20_DATA *);

#endif