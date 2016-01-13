set(PROJECT_NAME yogurt)
project(${PROJECT_NAME} C CXX)
set(${PROJECT_NAME}_SRCS yogurt.cpp)
generate_arduino_firmware(${PROJECT_NAME})
