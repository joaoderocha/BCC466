cmake_minimum_required(VERSION 3.20)
project (BCC466)

set(CMAKE_CXX_STANDARD 17)

add_executable(main main.cpp)
add_subdirectory(test)
add_subdirectory(src)
target_link_libraries(main PRIVATE BCC466)