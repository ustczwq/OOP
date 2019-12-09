cmake_minimum_required(VERSION 3.0.0)
project(protobuf_test VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 11)

include(CTest)
enable_testing()

find_package(Protobuf REQUIRED)

FIND_PACKAGE(FLTK REQUIRED)
include_directories(${FLTK_INCLUDE_DIRS}) 
link_directories(${FLTK_LIBRARY_DIRS}) 
add_definitions(${FLTK_DEFINITIONS})

aux_source_directory(. source_list)

add_executable(protobuf_test ${source_list})
target_link_libraries(protobuf_test fltk fltk_images protobuf)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
