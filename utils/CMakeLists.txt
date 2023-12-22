cmake_minimum_required(VERSION 3.5)
#project(utils)

set(CMAKE_CXX_STANDARD 17)
set(LIBRARY_OUTPUT_PATH ${PROJECT_DIR}/lib)

add_library(params SHARED params.cpp)

install(TARGETS params DESTINATION ${PROJECT_DIR}/lib)
