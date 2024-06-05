cmake_minimum_required(VERSION 3.10)
project(hash_tabs)

set (CMAKE_CXX_STANDARD 17)

add_library(hash_tab_lib src/HashTable1.cpp src/HashTable2.cpp src/AVLtree.cpp src/HashTable3.cpp)

add_executable(test "src/main.cpp")

add_executable(simulation "src/simulator")
target_link_libraries(test hash_tab_lib)
target_link_libraries(simulation hash_tab_lib)