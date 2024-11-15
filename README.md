# AHT20

My implementation of AHT20 driver.

## Usage

1. Init sensor `AHT20_Init();`
2. Start measuring `AHT20_StartMeasurement();`
3. **Make delay about 100ms**
4. Parse data `AHT20_ParseData(&temp,&humidity);`

Note: temp and humidity variables must be **float** type!

### Example

with stm32 HAL

```C
float temp = 0;
float humidity = 0;
void main() {
    HAL_Init();
    /* USER CODE BEGIN Init */
    AHT20_Init();
    /* USER CODE END Init */
    /* Initialize all configured peripherals */
    MX_I2C1_Init();
    /* Infinite loop */
    while (1)
    {
        AHT20_StartMeasurement();
        HAL_Delay(150);
        AHT20_ParseData(&temp,&humidity);
        HAL_Delay(5000);
    }
}
```

## Return type

All functions return `AHT20_ResponseTypeDef`.  
Values:  
    AHT20_OK = 0
    AHT20_ERROR = 1
    AHT20_BUSY = 2
    AHT20_BAD_CRC =3

### Explanation

- AHT20_OK if everything is OK.
- AHT20_ERROR something went wrong.
- AHT20_BUSY You called `AHT20_ParseData` too early, and chip still measuring.
- AHT20_BAD_CRC mismatch of CRC.

## CMAKE

If you are using CMAKE, you can add config to your toolchain.

```cmake
#Default path. Change tou yours.
add_subdirectory(Drivers/AHT20) 
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE
    aht20
)
```

## Hardware

Core functionality is hardware agnostic. You can add your hardware implementation. By default shipped with STM32 HAL implementation.

You can change hardware by toggling build params.  
CMAKE params:

- AHT20_DRIVER_HAL_STM32 - Default, STM32 HAL
*WIP*

## TODO

- [] DMA and INTERRUPT modes
- [] Doxygen
- [] More supported hardware
  - [] CC13xx/CC11xx
  - [] MSP430
  - [] Arduino
  - [] PI nano SDK
  