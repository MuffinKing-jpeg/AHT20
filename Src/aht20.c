#include "aht20.h"

const AHT20_CMD AHT20_CMD_INIT = {0xBE, 0x08, 0x00};
const AHT20_CMD AHT20_CMD_MEASURE = {0xAC, 0x33, 0x00};

AHT20_ResponseTypeDef AHT20_Init(void)
{
    
    return AHT20_WriteCMD(&AHT20_CMD_INIT);
}

AHT20_ResponseTypeDef AHT20_StartMeasurement(void)
{
    return AHT20_WriteCMD(&AHT20_CMD_MEASURE);
}

AHT20_ResponseTypeDef AHT20_ParseData(float *temp, float *humidity)
{
    AHT20_DATA response = {0};

    if (AHT20_ReadData(&response) != AHT20_OK) return AHT20_ERROR;
    if ((response[0] & 0x80) != 0) return AHT20_BUSY;
    if (AHT20_CheckCRC(&response) != AHT20_OK) return AHT20_BAD_CRC;
    
    uint32_t raw_humidity = ((uint32_t)(response[1] << 12) | (response[2] << 4) | (response[3] >> 4)) & 0xFFFFF;
    *humidity = (raw_humidity * 100.0) / 0x100000;

    int32_t raw_temperature = ((uint32_t)(response[3] & 0x0F) << 16) | (response[4] << 8) | response[5];
    *temp = (raw_temperature * 200.0 / 0x100000) - 50.0;

    return AHT20_OK;
}
