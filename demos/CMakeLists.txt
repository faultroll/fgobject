cmake_minimum_required(VERSION 3.5)

project(demos)

set(CMAKE_BUILD_TYPE MinSizeRel)

set(${PROJECT_NAME}_PRJ_DIR ${PROJECT_SOURCE_DIR})
INCLUDE_DIRECTORIES(${${PROJECT_NAME}_PRJ_DIR}/../dist/include/fgobject)
LINK_DIRECTORIES(${${PROJECT_NAME}_PRJ_DIR}/../dist/lib)

set(CMAKE_C_FLAGS "-Wno-deprecated-declarations")

add_subdirectory(base)
add_subdirectory(shape)
