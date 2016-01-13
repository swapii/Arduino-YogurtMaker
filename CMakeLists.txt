set(ARDUINO_CPU 16MHzatmega328)

set(CMAKE_TOOLCHAIN_FILE cmake/ArduinoToolchain.cmake) # Arduino Toolchain

cmake_minimum_required(VERSION 2.8)

project(ArduinoExample C CXX)

print_board_list()

print_programmer_list()

link_directories(${CMAKE_CURRENT_LIST_DIR}/libs)

add_subdirectory(yogurt)
