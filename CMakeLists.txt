set(ARDUINO_DEFAULT_BOARD uno)

set(CMAKE_TOOLCHAIN_FILE cmake/ArduinoToolchain.cmake)

cmake_minimum_required(VERSION 2.8)

project(ArduinoExample C CXX)

link_directories(${CMAKE_CURRENT_LIST_DIR}/libs)

add_subdirectory(blink)
add_subdirectory(yogurt)
