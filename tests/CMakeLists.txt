add_executable(test utils_tests.cpp)

target_include_directories(test PUBLIC ${CMAKE_SOURCE_DIR}/utils)

target_link_libraries(test PUBLIC Utils)