cmake_minimum_required(VERSION 3.5)

find_package(Boost REQUIRED COMPONENTS system)
add_executable(server main.cpp)

target_link_libraries(server PRIVATE
    ${Boost_LIBRARIES}
    ${params_LIBRARIES}
)
