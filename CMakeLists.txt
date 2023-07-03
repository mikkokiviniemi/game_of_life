cmake_minimum_required(VERSION 3.20)
project(conway)

add_executable(${PROJECT_NAME} main.cpp)

add_subdirectory(utils)
add_subdirectory(external)

target_link_libraries(${PROJECT_NAME} Utils imqui)