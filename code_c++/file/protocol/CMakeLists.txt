cmake_minimum_required(VERSION 3.10)

project("pb_generator")
set(TARGET_NAME pb_generator)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g2 -std=gnu++17 -fPIC -Wall -Wextra")

find_package(Protobuf REQUIRED)
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})
PROTOBUF_GENERATE_CPP(PROTO_SRCS PROTO_HDRS nio_flash.proto)


ADD_EXECUTABLE(${TARGET_NAME} pb_generator.cpp ${PROTO_SRCS} ${PROTO_HDRS})
target_include_directories(${TARGET_NAME} PUBLIC .)

target_link_libraries(${TARGET_NAME} protobuf)









