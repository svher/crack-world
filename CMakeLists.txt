cmake_minimum_required(VERSION 3.16)
project(crack-world)

set(CMAKE_CXX_STANDARD 20)
set(MODULE_NAME cw)

include_directories(. $ENV{DXSDK_DIR}Include)
include_directories(sdk)
include_directories(thirdparty)
include_directories(thirdparty/imgui)

link_directories("$ENV{DXSDK_DIR}/Lib/x86")
add_library(${MODULE_NAME} SHARED "")
target_link_libraries(${MODULE_NAME} d3d9 d3dx9)

aux_source_directory(. DIR_SRC)
message(STATUS ${DIR_SRC})
target_sources(${MODULE_NAME} PRIVATE ${DIR_SRC})

add_subdirectory(thirdparty)