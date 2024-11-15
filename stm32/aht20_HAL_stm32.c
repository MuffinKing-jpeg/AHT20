#include "aht20.h"
#include "i2c.h"

AHT20_ResponseTypeDef AHT20_WriteCMD(const AHT20_CMD *cmd)
{
    if (HAL_I2C_Master_Transmit(
            &AHT20_I2C,
            AHT20_I2C_SLAVE_ADDR,
            (uint8_t *)cmd,
            AHT20_CMD_LENGTH,
            HAL_MAX_DELAY) == HAL_OK)
    {
        return AHT20_OK;
    }
    else 
    {
        return AHT20_ERROR;
    }
}

AHT20_ResponseTypeDef AHT20_ReadData(AHT20_DATA *payload)
{
    if (HAL_I2C_Master_Receive(
            &AHT20_I2C,
            AHT20_I2C_SLAVE_ADDR,
            (uint8_t *)payload,
            AHT20_DATA_LENGTH,
            HAL_MAX_DELAY) == HAL_OK)
    {
        return AHT20_OK;
    }
    else 
    {
        return AHT20_ERROR;
    }
}

AHT20_ResponseTypeDef AHT20_CheckCRC(AHT20_DATA *payload)
{
     uint8_t crc = AHT20_CRC8_INITIAL_VALUE;

    for (size_t i = 0; i < AHT20_DATA_LENGTH-1; i++) {
        crc ^= (*payload)[i];

        for (uint8_t bit = 0; bit < 8; bit++) {
            if (crc & 0x80) {
                crc = (crc << 1) ^ AHT20_CRC8_POLYNOMIAL;  // Polynomial reduction
            } else {
                crc = crc << 1;
            }
        }
    }
    if ((*payload)[AHT20_DATA_LENGTH-1] != crc)
    {
        
        return AHT20_BAD_CRC;
    }

    return AHT20_OK;
}