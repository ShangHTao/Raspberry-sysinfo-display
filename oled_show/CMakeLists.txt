cmake_minimum_required(VERSION 2.8)
PROJECT(oled_i2c_show_status)

include_directories(${CMAKE_SOURCE_DIR}/inc)
aux_source_directory(./src ALL_SRCS)


find_library(WIRINGPI_LIBRARIES NAMES wiringPi)

add_executable(oled_i2c_show_status ${ALL_SRCS})

target_link_libraries(oled_i2c_show_status ${WIRINGPI_LIBRARIES})