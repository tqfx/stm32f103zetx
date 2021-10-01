include(cmake/arm-none-eabi.cmake)

cmake_minimum_required(VERSION 3.10)

project(target)

set(CMAKE_VERBOSE_MAKEFILE OFF)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)
set(ARICHIVE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Debug")
endif(NOT CMAKE_BUILD_TYPE)
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -Og -ggdb -gdwarf-2")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Og -ggdb -gdwarf-2")

include(cmake/check-flag.cmake)

add_compile_definitions(STM32F103xE)
add_compile_definitions(USE_HAL_DRIVER)

list(APPEND OPTIONS -mcpu=cortex-m3)
list(APPEND OPTIONS -mthumb -fdata-sections -ffunction-sections)
add_compile_options(${OPTIONS})
add_link_options(${OPTIONS})
# add_link_options(-u_printf_float)

include(Drivers/FileLists.cmake)
list(APPEND SOURCE ${SOURCE_Drivers})

include(Middlewares/FileLists.cmake)
list(APPEND SOURCE ${SOURCE_Middlewares})

include_directories("Core/Inc")
aux_source_directory("Core/Src" SOURCE_Core)
list(APPEND SOURCE ${SOURCE_Core})

include_directories("bsp")
aux_source_directory("bsp" SOURCE_bsp)
list(APPEND SOURCE ${SOURCE_bsp})

file(GLOB STARTUP startup*.s)
add_executable(${CMAKE_PROJECT_NAME}.elf ${STARTUP} ${SOURCE})

target_link_libraries(${CMAKE_PROJECT_NAME}.elf c m nosys)

file(GLOB LINKER_SCRIPT *.ld)
target_link_options(${CMAKE_PROJECT_NAME}.elf PUBLIC
  -Wl,--gc-sections
  --specs=nano.specs
  -T${LINKER_SCRIPT}
  -Wl,-Map=${CMAKE_PROJECT_NAME}.map,--cref
)

# display the size of the output binary after a build is finished
add_custom_command(TARGET ${CMAKE_PROJECT_NAME}.elf POST_BUILD
  COMMAND ${CMAKE_SIZE} --format=berkeley ${CMAKE_PROJECT_NAME}.elf
)
add_custom_target(${CMAKE_PROJECT_NAME}.hex ALL DEPENDS ${CMAKE_PROJECT_NAME}.elf
  COMMAND ${CMAKE_OBJCOPY} -Oihex ${CMAKE_PROJECT_NAME}.elf ${CMAKE_PROJECT_NAME}.hex
)
add_custom_target(${CMAKE_PROJECT_NAME}.bin ALL DEPENDS ${CMAKE_PROJECT_NAME}.elf
  COMMAND ${CMAKE_OBJCOPY} -Obinary ${CMAKE_PROJECT_NAME}.elf ${CMAKE_PROJECT_NAME}.bin
)

# openocd
file(GLOB FLASH_CONFIG *.cfg)
add_custom_target(flash
  COMMAND openocd -f ${FLASH_CONFIG} -c init -c halt -c \"program ${CMAKE_PROJECT_NAME}.elf verify reset exit\"
)
add_custom_target(reset
  COMMAND openocd -f ${FLASH_CONFIG} -c init -c halt -c reset -c shutdown
)
