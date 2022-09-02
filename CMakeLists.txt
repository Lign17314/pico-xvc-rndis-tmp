cmake_minimum_required(VERSION 3.13)
include(pico_sdk_import.cmake)
project(test_project C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
pico_sdk_init()

add_executable(test)
include_directories(${CMAKE_SOURCE_DIR}/include)
#include_directories(${CMAKE_SOURCE_DIR}/src/si4735)
#add_subdirectory(src) 

pico_generate_pio_header(test ${CMAKE_CURRENT_LIST_DIR}/tdata.pio)

#add_executable(test  main.c )

target_sources(test PRIVATE
        main.c
        )

pico_enable_stdio_usb(test 1)
pico_enable_stdio_uart(test 0)

target_link_libraries(test pico_stdlib hardware_pio)
pico_add_extra_outputs(test)

