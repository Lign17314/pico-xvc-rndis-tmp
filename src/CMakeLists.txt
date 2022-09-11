# CMakeLists.txt
cmake_minimum_required (VERSION 3.10.2)
project (lib_app)

include_directories(${CMAKE_SOURCE_DIR}/include)

include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${TOP}/lib/lwip/src/include
        ${TOP}/lib/lwip/src/include/ipv4
        ${TOP}/lib/lwip/src/include/lwip/apps
        ${TOP}/lib/tinyusb/lib/networking
        ${TOP}/lib/tinyusb/src
        )
include(${TOP}/lib/tinyusb/hw/bsp/family_support.cmake)

aux_source_directory(. LIB_SRCS)     # 添加当前目录下所有的源文件

add_library(${PROJECT_NAME}  STATIC
        ${TOP}/lib/lwip/src/core/altcp.c
        ${TOP}/lib/lwip/src/core/altcp_alloc.c
        ${TOP}/lib/lwip/src/core/altcp_tcp.c
        ${TOP}/lib/lwip/src/core/def.c
        ${TOP}/lib/lwip/src/core/dns.c
        ${TOP}/lib/lwip/src/core/inet_chksum.c
        ${TOP}/lib/lwip/src/core/init.c
        ${TOP}/lib/lwip/src/core/ip.c
        ${TOP}/lib/lwip/src/core/mem.c
        ${TOP}/lib/lwip/src/core/memp.c
        ${TOP}/lib/lwip/src/core/netif.c
        ${TOP}/lib/lwip/src/core/pbuf.c
        ${TOP}/lib/lwip/src/core/raw.c
        ${TOP}/lib/lwip/src/core/stats.c
        ${TOP}/lib/lwip/src/core/sys.c
        ${TOP}/lib/lwip/src/core/tcp.c
        ${TOP}/lib/lwip/src/core/tcp_in.c
        ${TOP}/lib/lwip/src/core/tcp_out.c
        ${TOP}/lib/lwip/src/core/timeouts.c
        ${TOP}/lib/lwip/src/core/udp.c
        ${TOP}/lib/lwip/src/core/ipv4/autoip.c
        ${TOP}/lib/lwip/src/core/ipv4/dhcp.c
        ${TOP}/lib/lwip/src/core/ipv4/etharp.c
        ${TOP}/lib/lwip/src/core/ipv4/icmp.c
        ${TOP}/lib/lwip/src/core/ipv4/igmp.c
        ${TOP}/lib/lwip/src/core/ipv4/ip4.c
        ${TOP}/lib/lwip/src/core/ipv4/ip4_addr.c
        ${TOP}/lib/lwip/src/core/ipv4/ip4_frag.c
        ${TOP}/lib/lwip/src/netif/ethernet.c
        ${TOP}/lib/lwip/src/netif/slipif.c
        ${TOP}/lib/lwip/src/apps/http/httpd.c
        ${TOP}/lib/lwip/src/apps/http/fs.c
        ${TOP}/lib/tinyusb/lib/networking/dhserver.c
        ${TOP}/lib/tinyusb/lib/networking/dnserver.c
        ${TOP}/lib/tinyusb/lib/networking/rndis_reports.c
        ${TOP}/lib/lwip/src/apps/lwiperf/lwiperf.c
        ${LIB_SRCS}
)
target_compile_definitions(${PROJECT_NAME}  PUBLIC
PBUF_POOL_SIZE=2
TCP_WND=2*TCP_MSS
HTTPD_USE_CUSTOM_FSDATA=0
)

pico_generate_pio_header(${PROJECT_NAME} ${CMAKE_CURRENT_LIST_DIR}/tdata.pio)
pico_generate_pio_header(${PROJECT_NAME} ${CMAKE_CURRENT_LIST_DIR}/tms.pio)
#pico_generate_pio_header(${PROJECT_NAME} ${CMAKE_CURRENT_LIST_DIR}/i2c.pio)

target_link_libraries(${PROJECT_NAME} pico_stdlib hardware_pio tinyusb_device tinyusb_board pico_multicore)
