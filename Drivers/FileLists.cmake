# add include
include_directories(${CMAKE_CURRENT_LIST_DIR}/CMSIS/Include)
include_directories(${CMAKE_CURRENT_LIST_DIR}/CMSIS/Device/ST/STM32F1xx/Include)
include_directories(${CMAKE_CURRENT_LIST_DIR}/STM32F1xx_HAL_Driver/Inc/Legacy)
include_directories(${CMAKE_CURRENT_LIST_DIR}/STM32F1xx_HAL_Driver/Inc)
# add source
aux_source_directory(${CMAKE_CURRENT_LIST_DIR}/STM32F1xx_HAL_Driver/Src SOURCE_Drivers)
