cmake_minimum_required(VERSION 3.21)
project(CPPHM_lesson_7)

set(CMAKE_CXX_STANDARD 17)

find_package(Protobuf REQUIRED)

include_directories(${PROTOBUF_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS fullname.proto)

add_executable(CPPHM_lesson_7 main.cpp fullname.proto ${PROTO_SRCS} ${PROTO_HDRS})

target_link_libraries(CPPHM_lesson_7 ${PROTOBUF_LIBRARY})

