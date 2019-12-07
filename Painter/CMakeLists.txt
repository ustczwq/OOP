cmake_minimum_required(VERSION 3.0.0)
project(painter VERSION 0.1.0)

include(CTest)
enable_testing()

FIND_PACKAGE(FLTK REQUIRED)  # must use "NO_MODULE" 
include_directories(${FLTK_INCLUDE_DIRS}) 
link_directories(${FLTK_LIBRARY_DIRS}) 
add_definitions(${FLTK_DEFINITIONS})

aux_source_directory(. source_list)

add_executable(painter ${source_list})
target_link_libraries(painter fltk fltk_images)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
