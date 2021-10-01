# add include
include_directories(${CMAKE_CURRENT_LIST_DIR}/Third_Party/FreeRTOS/Source/include)
include_directories(${CMAKE_CURRENT_LIST_DIR}/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2)
include_directories(${CMAKE_CURRENT_LIST_DIR}/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F)
# add source
file(GLOB_RECURSE SOURCE_Middlewares ${CMAKE_CURRENT_LIST_DIR}/*.c)
# aux_source_directory(${CMAKE_CURRENT_LIST_DIR}/Third_Party/FreeRTOS/Source SOURCE_Middlewares)
# list(APPEND SOURCE_Middlewares ${CMAKE_CURRENT_LIST_DIR}/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/cmsis_os2.c)
# list(APPEND SOURCE_Middlewares ${CMAKE_CURRENT_LIST_DIR}/Third_Party/FreeRTOS/Source/portable/MemMang/heap_4.c)
# list(APPEND SOURCE_Middlewares ${CMAKE_CURRENT_LIST_DIR}/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F/port.c)
