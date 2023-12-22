cmake_minimum_required(VERSION 3.5)
project(online-value-validator)

list(APPEND CMAKE_PREFIX_PATH "/usr")
list(APPEND CMAKE_PREFIX_PATH "/usr/lib")
list(APPEND CMAKE_PREFIX_PATH "/usr/lib/x86_64-linux-gnu/")


set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)

set(PROJECT_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_CXX_STANDARD 17)

find_library(params_LIBRARIES
    NAMES params
    PATHS ${PROJECT_DIR}/lib
    )

add_subdirectory(utils)
add_subdirectory(server)
add_subdirectory(client)
