cmake_minimum_required(VERSION 3.20)
project(conway)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})


add_executable(${PROJECT_NAME} main.cpp ${sources})

add_subdirectory(utils)
add_subdirectory(game)
add_subdirectory(tests)

target_link_libraries(${PROJECT_NAME} Utils Game ${SDL2_LIBRARIES})