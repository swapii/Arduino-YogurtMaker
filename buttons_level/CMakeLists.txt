set(PROJECT_NAME buttons_level)
project(${PROJECT_NAME} C CXX)
set(${PROJECT_NAME}_SRCS buttons_level.cpp)
generate_arduino_firmware(${PROJECT_NAME})
