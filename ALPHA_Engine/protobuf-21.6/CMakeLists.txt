#INCLUDE(FindProtobuf)
set(CMAKE_CXX_FLAGS "-g -Wall -Werror -std=c++11")
set(ProtoBuf "${PROJECT_SOURCE_DIR}/ALPHA_Engine/protobuf-21.6")
set(Protobuf_PREFIX_PATH
    "${ProtoBuf}/bin"            
    "${ProtoBuf}/include"               
    "${ProtoBuf}/lib"      )
list(APPEND CMAKE_PREFIX_PATH "${Protobuf_PREFIX_PATH}")
find_package(Protobuf REQUIRED)
include_directories(${Protobuf_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

set(PROTO_OUTPUT_DIR "${CMAKE_CURRENT_BINARY_DIR}/sources")
PROTOBUF_GENERATE_CPP(PROTO_SRC PROTO_HEADER ${ProtoBuf}/Vector3.proto)

#protobuf_generate(TARGET "${PROTO_NAME_WE}-proto" PROTOC_OUT_DIR "${PROTO_OUTPUT_DIR}/protobuf-21.6/protofiles" IMPORT_DIRS "${CMAKE_CURRENT_LIST_DIR}/src")

#include_directories(${ProtoBuf})
#include_directories(${ProtoBuf}/bin)

#target_link_libraries(ALPHA_Engine 
#${Protobuf_LIBRARIES}
#PRIVATE "${ProtoBuf}/lib/libprotobuf.lib"
#PRIVATE lib/libprotobuf-lite.lib
#PRIVATE lib/libprotoc.lib
#)

add_custom_target(protobuf_compilation DEPENDS ${PROTO_SRCS})

#ADD_LIBRARY("${ProtoBuf}/protofiles" ${PROTO_HEADER} ${PROTO_SRC})

