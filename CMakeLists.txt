cmake_minimum_required(VERSION 3.22)

project(aht20)
add_library(aht20 INTERFACE)

# Enable CMake support for ASM and C languages
enable_language(C ASM)


message("AHT20 driver by

███╗   ███╗██╗   ██╗███████╗███████╗██╗███╗   ██╗██╗  ██╗██╗███╗   ██╗ ██████╗ 
████╗ ████║██║   ██║██╔════╝██╔════╝██║████╗  ██║██║ ██╔╝██║████╗  ██║██╔════╝ 
██╔████╔██║██║   ██║█████╗  █████╗  ██║██╔██╗ ██║█████╔╝ ██║██╔██╗ ██║██║  ███╗
██║╚██╔╝██║██║   ██║██╔══╝  ██╔══╝  ██║██║╚██╗██║██╔═██╗ ██║██║╚██╗██║██║   ██║
██║ ╚═╝ ██║╚██████╔╝██║     ██║     ██║██║ ╚████║██║  ██╗██║██║ ╚████║╚██████╔╝
╚═╝     ╚═╝ ╚═════╝ ╚═╝     ╚═╝     ╚═╝╚═╝  ╚═══╝╚═╝  ╚═╝╚═╝╚═╝  ╚═══╝ ╚═════╝ 
                                                                               
")

file(GLOB AHT20_SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}//Src/*.c)

target_include_directories(aht20 INTERFACE
${CMAKE_CURRENT_SOURCE_DIR}/Inc
)

target_sources(aht20 PUBLIC
    ${AHT20_SRC_FILES}
    # Add user sources here
)

option(AHT20_DRIVER_HAL_STM32 "Use STM32 HAL" ON)

if(AHT20_DRIVER_HAL_STM32)
message("AHT20 using STM32 HAL")
    target_sources(aht20 PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/stm32/aht20_HAL_stm32.c
    )
endif()

target_link_directories(aht20 INTERFACE
)

target_link_libraries(aht20 INTERFACE
)

# Validate that STM32CubeMX code is compatible with C standard
if(CMAKE_C_STANDARD LESS 11)
    message(ERROR "Generated code requires C11 or higher")
endif()