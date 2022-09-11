cmake_minimum_required(VERSION 3.13)
include(pico_sdk_import.cmake)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)


project(test)

pico_sdk_init()

add_executable(test)

set(TOP ${PICO_SDK_PATH})
include(${TOP}/lib/tinyusb/hw/bsp/family_support.cmake)

# Example include
# Make sure TinyUSB can find tusb_config.h

target_include_directories(test PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${TOP}/lib/lwip/src/include
        ${TOP}/lib/lwip/src/include/ipv4
        ${TOP}/lib/lwip/src/include/lwip/apps
        ${TOP}/lib/tinyusb/lib/networking
        )

add_subdirectory(src) 

# Example source
target_sources(test PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/main.c
        )

target_link_libraries(test PUBLIC pico_stdlib tinyusb_device tinyusb_board lib_app)

pico_add_extra_outputs(test)

