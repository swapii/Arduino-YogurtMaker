set(PROJECT_NAME blink)
project(${PROJECT_NAME} C CXX)
set(${PROJECT_NAME}_SRCS blink.cpp)
generate_arduino_firmware(${PROJECT_NAME})
